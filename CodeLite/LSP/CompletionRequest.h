#ifndef COMPLETIONREQUEST_H
#define COMPLETIONREQUEST_H

#include "LSP/basic_types.h"
#include "LSP/Request.h"

namespace LSP
{

class WXDLLIMPEXP_CL CompletionRequest : public LSP::Request
{
public:
    CompletionRequest(const LSP::TextDocumentIdentifier& textDocument, const LSP::Position& position);
    virtual ~CompletionRequest();
    void OnResponse(const LSP::ResponseMessage& response, wxEvtHandler* owner);
    bool IsPositionDependantRequest() const { return true; }
    bool IsValidAt(const wxFileName& filename, size_t line, size_t col) const;
};
};     // namespace LSP
#endif // COMPLETIONREQUEST_H
