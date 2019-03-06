//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: clResizableTooltipBase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "clResizableTooltipBase.h"
#include "codelite_exports.h"


// Declare the bitmap loading function
extern void wxC126AInitBitmapResources();

static bool bBitmapLoaded = false;


clResizableTooltipBase::clResizableTooltipBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxMiniFrame(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC126AInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* boxSizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizer2);

    m_treeCtrl = new clThemedTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), wxTR_DEFAULT_STYLE);

    boxSizer2->Add(m_treeCtrl, 1, wxEXPAND, WXC_FROM_DIP(5));

    SetName(wxT("clResizableTooltipBase"));
    SetSize(wxDLG_UNIT(this, wxSize(300,200)));
    if (GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
    // Connect events
    m_treeCtrl->Connect(wxEVT_COMMAND_TREE_ITEM_EXPANDING, wxTreeEventHandler(clResizableTooltipBase::OnItemExpanding), NULL, this);
    m_treeCtrl->Connect(wxEVT_COMMAND_TREE_KEY_DOWN, wxTreeEventHandler(clResizableTooltipBase::OnKeyDown), NULL, this);

}

clResizableTooltipBase::~clResizableTooltipBase()
{
    m_treeCtrl->Disconnect(wxEVT_COMMAND_TREE_ITEM_EXPANDING, wxTreeEventHandler(clResizableTooltipBase::OnItemExpanding), NULL, this);
    m_treeCtrl->Disconnect(wxEVT_COMMAND_TREE_KEY_DOWN, wxTreeEventHandler(clResizableTooltipBase::OnKeyDown), NULL, this);

}
