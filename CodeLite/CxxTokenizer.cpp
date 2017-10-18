#include "CxxTokenizer.h"

CxxTokenizer::CxxTokenizer()
    : m_scanner(nullptr)
{
}

CxxTokenizer::~CxxTokenizer()
{
    if(m_scanner) {
        ::LexerDestroy(&m_scanner);
    }
}

bool CxxTokenizer::NextToken(CxxLexerToken& token)
{
    if(!m_scanner) return false;
    return ::LexerNext(m_scanner, token);
}

void CxxTokenizer::Reset(const wxString& buffer)
{
    if(m_scanner) {
        ::LexerDestroy(&m_scanner);
    }
    if(!buffer.empty()) {
        m_buffer = buffer;
        m_scanner = ::LexerNew(buffer, 0);
    }
}

bool CxxTokenizer::ReadUntilClosingBracket(int delim, wxString& bufferRead)
{
    CxxLexerToken tok;
    int depth = 0;
    while(NextToken(tok)) {
        switch(tok.type) {
        case '<':
        case '(':
        case '[':
        case '{':
            depth++;
            bufferRead << tok.text << " ";
            break;
        case '>':
        case ')':
        case ']':
        case '}':
            if((tok.type == delim) && (depth == 0)) {
                ::LexerUnget(m_scanner);
                return true;
            }
            depth--;
            bufferRead << tok.text << " ";
            break;
        default:
            bufferRead << tok.text << " ";
            break;
        }
    }
    return false;
}
