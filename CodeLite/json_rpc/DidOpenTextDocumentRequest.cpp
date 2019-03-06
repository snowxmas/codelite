#include "DidOpenTextDocumentRequest.h"
#include "json_rpc_params.h"

json_rpc::DidOpenTextDocumentRequest::DidOpenTextDocumentRequest(const wxFileName& filename, const wxString& text,
                                                                 const wxString& langugage)
{
    SetMethod("textDocument/didOpen");
    m_params.reset(new DidOpenTextDocumentParams());
    m_params->As<DidOpenTextDocumentParams>()->SetTextDocument(TextDocumentItem(filename, langugage, text));
}

json_rpc::DidOpenTextDocumentRequest::~DidOpenTextDocumentRequest() {}
