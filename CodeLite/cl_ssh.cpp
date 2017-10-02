//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 Eran Ifrah
// file name            : cl_ssh.cpp
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#if USE_SFTP

#include <wx/string.h>
#include <wx/translation.h>
#include <wx/textdlg.h>
#include <wx/thread.h>
#ifdef __WXMSW__
#include "wx/msw/winundef.h"
#endif
#include "cl_ssh.h"
#include <libssh/libssh.h>

wxDEFINE_EVENT(wxEVT_SSH_COMMAND_OUTPUT, clCommandEvent);
wxDEFINE_EVENT(wxEVT_SSH_COMMAND_COMPLETED, clCommandEvent);
wxDEFINE_EVENT(wxEVT_SSH_COMMAND_ERROR, clCommandEvent);
wxDEFINE_EVENT(wxEVT_SSH_CONNECTED, clCommandEvent);

#if 0
class SSHConnectThread : public wxThread
{
    size_t m_seconds;
    SSHSession_t m_session;
    clSSH* m_handler;

public:
    SSHConnectThread(clSSH* handler, SSHSession_t session, size_t seconds)
        : wxThread(wxTHREAD_JOINABLE)
        , m_handler(handler)
        , m_session(session)
        , m_seconds(seconds)
    {
    }
    virtual ~SSHConnectThread() {}

    void* Entry()
    {
        size_t retries = m_seconds * 100;
        while(retries) {
            int rc = ssh_connect(m_session);
            if(rc == SSH_AGAIN) {
                wxThread::Sleep(10);
                --retries;
                continue;
            }
            if(rc == SSH_OK) {
                m_handler->CallAfter(&clSSH::OnConnectSuccess);
                return NULL;
            } else {
                break;
            }
        }
        m_handler->CallAfter(&clSSH::OnConnectError);
        return NULL;
    }
};
#endif

clSSH::clSSH(const wxString& host, const wxString& user, const wxString& pass, int port)
    : m_host(host)
    , m_username(user)
    , m_password(pass)
    , m_port(port)
    , m_connected(false)
    , m_session(NULL)
    , m_channel(NULL)
    , m_timer(NULL)
    , m_owner(NULL)
{
    m_timer = new wxTimer(this);
    Bind(wxEVT_TIMER, &clSSH::OnCheckRemoteOutut, this, m_timer->GetId());
}

clSSH::clSSH()
    : m_port(22)
{
}

clSSH::~clSSH() { Close(); }

void clSSH::Connect(int seconds) throw(clException)
{
    m_session = ssh_new();
    if(!m_session) {
        throw clException("ssh_new failed!");
    }
    
    ssh_set_blocking(m_session, 0);
    int verbosity = SSH_LOG_NOLOG;
    ssh_options_set(m_session, SSH_OPTIONS_HOST, m_host.mb_str(wxConvUTF8).data());
    ssh_options_set(m_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(m_session, SSH_OPTIONS_PORT, &m_port);
    ssh_options_set(m_session, SSH_OPTIONS_USER, GetUsername());
    
    // Connect the session
    int retries = seconds * 100;
    if(retries < 0) {
        retries = 1;
    }
    DoConnectWithRetries(retries);
    ssh_set_blocking(m_session, 1);
}

bool clSSH::AuthenticateServer(wxString& message) throw(clException)
{
    int state;
    unsigned char* hash = NULL;
    char* hexa = NULL;

    message.Clear();
    state = ssh_is_server_known(m_session);

#if LIBSSH_VERSION_INT < SSH_VERSION_INT(0, 6, 1)
    int hlen = 0;
    hlen = ssh_get_pubkey_hash(m_session, &hash);
    if(hlen < 0) {
        throw clException("Unable to obtain server public key!");
    }
#else
    size_t hlen = 0;
    ssh_key key = NULL;
    ssh_get_publickey(m_session, &key);
    ssh_get_publickey_hash(key, SSH_PUBLICKEY_HASH_SHA1, &hash, &hlen);
    if(hlen == 0) {
        throw clException("Unable to obtain server public key!");
    }
#endif

    switch(state) {
    case SSH_SERVER_KNOWN_OK:
        free(hash);
        return true;

    case SSH_SERVER_KNOWN_CHANGED:
        hexa = ssh_get_hexa(hash, hlen);
        message << _("Host key for server changed: it is now:\n") << hexa << "\n" << _("Accept server authentication?");
        free(hexa);
        free(hash);
        return false;

    case SSH_SERVER_FOUND_OTHER:
        message << _("The host key for this server was not found but another type of key exists.\n")
                << _("An attacker might change the default server key to confuse your client into thinking the key "
                     "does not exist\n") << _("Accept server authentication?");
        free(hash);
        return false;

    case SSH_SERVER_FILE_NOT_FOUND:
        message << _("Could not find known host file.\n")
                << _("If you accept the host key here, the file will be automatically created.\n");
    /* fallback to SSH_SERVER_NOT_KNOWN behavior */
    case SSH_SERVER_NOT_KNOWN:
        hexa = ssh_get_hexa(hash, hlen);
        message << _("The server is unknown. Do you trust the host key?\n") << _("Public key hash: ") << hexa << "\n"
                << _("Accept server authentication?");
        free(hexa);
        free(hash);
        return false;

    default:
    case SSH_SERVER_ERROR:
        throw clException(wxString() << "An error occurred: " << ssh_get_error(m_session));
    }
    return false;
}

void clSSH::AcceptServerAuthentication() throw(clException)
{
    if(!m_session) {
        throw clException("NULL SSH session");
    }
    ssh_write_knownhost(m_session);
}

#define THROW_OR_FALSE(msg)     \
    if(throwExc) {              \
        throw clException(msg); \
    }                           \
    return false;

bool clSSH::LoginPassword(bool throwExc) throw(clException)
{
    if(!m_session) {
        THROW_OR_FALSE("NULL SSH session");
    }

    int rc;
    // interactive keyboard method failed, try another method
    rc = ssh_userauth_password(m_session, NULL, GetPassword());
    if(rc == SSH_AUTH_SUCCESS) {
        return true;

    } else if(rc == SSH_AUTH_DENIED) {
        THROW_OR_FALSE("Login failed: invalid username/password");

    } else {
        THROW_OR_FALSE(wxString() << _("Authentication error: ") << ssh_get_error(m_session));
    }
    return false;
}

bool clSSH::LoginInteractiveKBD(bool throwExc) throw(clException)
{
    if(!m_session) {
        THROW_OR_FALSE("NULL SSH session");
    }

    int rc;
    rc = ssh_userauth_kbdint(m_session, NULL, NULL);
    if(rc == SSH_AUTH_INFO) {
        while(rc == SSH_AUTH_INFO) {
            const char* name, *instruction;
            int nprompts, iprompt;
            name = ssh_userauth_kbdint_getname(m_session);
            instruction = ssh_userauth_kbdint_getinstruction(m_session);
            nprompts = ssh_userauth_kbdint_getnprompts(m_session);
            wxUnusedVar(name);
            wxUnusedVar(instruction);
            for(iprompt = 0; iprompt < nprompts; iprompt++) {
                const char* prompt;
                char echo;
                prompt = ssh_userauth_kbdint_getprompt(m_session, iprompt, &echo);
                if(echo) {
                    wxString answer = ::wxGetTextFromUser(prompt, "SSH");
                    if(answer.IsEmpty()) {
                        THROW_OR_FALSE(wxString() << "Login error: " << ssh_get_error(m_session));
                    }
                    if(ssh_userauth_kbdint_setanswer(m_session, iprompt, answer.mb_str(wxConvUTF8).data()) < 0) {
                        THROW_OR_FALSE(wxString() << "Login error: " << ssh_get_error(m_session));
                    }
                } else {
                    if(ssh_userauth_kbdint_setanswer(m_session, iprompt, GetPassword().mb_str(wxConvUTF8).data()) < 0) {
                        THROW_OR_FALSE(wxString() << "Login error: " << ssh_get_error(m_session));
                    }
                }
            }
            rc = ssh_userauth_kbdint(m_session, NULL, NULL);
        }
        return true; // success
    }
    THROW_OR_FALSE("Interactive Keyboard is not enabled for this server");
    return false;
}

bool clSSH::LoginPublicKey(bool throwExc) throw(clException)
{
    if(!m_session) {
        THROW_OR_FALSE("NULL SSH session");
    }

    int rc;
    rc = ssh_userauth_autopubkey(m_session, NULL);
    if(rc != SSH_AUTH_SUCCESS) {
        THROW_OR_FALSE(wxString() << _("Public Key error: ") << ssh_get_error(m_session));
    }
    return true;
}

void clSSH::Close()
{
    m_timer->Stop();
    Unbind(wxEVT_TIMER, &clSSH::OnCheckRemoteOutut, this, m_timer->GetId());
    wxDELETE(m_timer);

    DoCloseChannel();

    if(m_session && m_connected) {
        ssh_disconnect(m_session);
    }

    if(m_session) {
        ssh_free(m_session);
    }

    m_connected = false;
    m_session = NULL;
    m_channel = NULL;
}

void clSSH::Login() throw(clException)
{
    int rc;

    rc = ssh_userauth_none(m_session, NULL);
    if(rc == SSH_AUTH_SUCCESS) {
        return;
    }

    // Try the following 3 methods in order
    // if non succeeded, this function will throw an exception

    try {
        LoginPublicKey();

    } catch(clException& e) {
        try {
            LoginPassword();

        } catch(clException& e2) {
            LoginInteractiveKBD();
        }
    }
}

void clSSH::ExecuteShellCommand(wxEvtHandler* owner, const wxString& command) throw(clException)
{
    DoOpenChannel();

    m_owner = owner;
    if(!m_owner) {
        throw clException(wxString() << "No owner specified for output");
    }

    wxCharBuffer buffer = command.mb_str(wxConvUTF8);
    int rc = ssh_channel_write(m_channel, buffer.data(), buffer.length());
    if(rc != (int)buffer.length()) {
        throw clException("SSH Socket error");
    }

    // Start a timer to check for the output on 10ms intervals
    if(!m_timer->IsRunning()) {
        m_timer->Start(50);
    }
}

void clSSH::OnCheckRemoteOutut(wxTimerEvent& event)
{
    if(!m_channel) return;

    char buffer[1024];
    int nbytes = ssh_channel_read_nonblocking(m_channel, buffer, sizeof(buffer), 0);
    if(nbytes > 0) {
        wxString strOutput = wxString::FromUTF8((const char*)buffer, nbytes);
        clCommandEvent sshEvent(wxEVT_SSH_COMMAND_OUTPUT);
        sshEvent.SetString(strOutput);
        m_owner->AddPendingEvent(sshEvent);

    } else if(nbytes == SSH_ERROR) {
        m_timer->Stop();
        DoCloseChannel();
        clCommandEvent sshEvent(wxEVT_SSH_COMMAND_ERROR);
        sshEvent.SetString(ssh_get_error(m_session));
        m_owner->AddPendingEvent(sshEvent);

    } else {
        // nbytes == 0
        if(ssh_channel_is_eof(m_channel)) {
            m_timer->Stop();
            DoCloseChannel();
            // EOF was sent, nothing more to read
            clCommandEvent sshEvent(wxEVT_SSH_COMMAND_COMPLETED);
            m_owner->AddPendingEvent(sshEvent);
        } else {
            // Nothing to read, no error
        }
    }
}

void clSSH::DoCloseChannel()
{
    // Properly close the channel
    if(m_channel) {
        ssh_channel_close(m_channel);
        ssh_channel_send_eof(m_channel);
        ssh_channel_free(m_channel);
    }
    m_channel = NULL;
}

void clSSH::DoOpenChannel() throw(clException)
{
    if(m_channel) return;

    m_channel = ssh_channel_new(m_session);
    if(!m_channel) {
        throw clException(ssh_get_error(m_session));
    }

    int rc = ssh_channel_open_session(m_channel);
    if(rc != SSH_OK) {
        throw clException(ssh_get_error(m_session));
    }

    rc = ssh_channel_request_pty(m_channel);
    if(rc != SSH_OK) {
        throw clException(ssh_get_error(m_session));
    }

    rc = ssh_channel_change_pty_size(m_channel, 80, 24);
    if(rc != SSH_OK) {
        throw clException(ssh_get_error(m_session));
    }

    rc = ssh_channel_request_shell(m_channel);
    if(rc != SSH_OK) {
        throw clException(ssh_get_error(m_session));
    }
}

void clSSH::DoConnectWithRetries(int retries) throw(clException)
{
    while(retries) {
        int rc = ssh_connect(m_session);
        if(rc == SSH_AGAIN) {
            if(wxThread::IsMain()) {
                ::wxSafeYield();
            }
            wxThread::Sleep(10);
            --retries;
            continue;
        }
        if(rc == SSH_OK) {
            m_connected = true;
            return;
        } else {
            throw clException(ssh_get_error(m_session));
        }
    }
    throw clException("Connect timeout");
}

#endif // USE_SFTP
