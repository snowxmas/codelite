//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: wxcrafter.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "wxcrafter.h"


// Declare the bitmap loading function
extern void wxC9A94InitBitmapResources();

static bool bBitmapLoaded = false;


SpellCheckerSettings_base::SpellCheckerSettings_base(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9A94InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* bSizer5 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer5);

    wxBoxSizer* bSizer51 = new wxBoxSizer(wxHORIZONTAL);

    bSizer5->Add(bSizer51, 0, wxEXPAND, 5);

    m_staticText2 = new wxStaticText(this, wxID_ANY, _("Dictionary path:"), wxDefaultPosition, wxSize(-1, -1), 0);

    bSizer51->Add(m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);

    m_pDirPicker = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, _("Select a folder"), wxDefaultPosition, wxSize(-1, -1), wxDIRP_DEFAULT_STYLE|wxDIRP_USE_TEXTCTRL);
    m_pDirPicker->SetToolTip(_("Select the location of the installed dictionaries"));

    bSizer51->Add(m_pDirPicker, 1, wxALL, 2);

    m_pHyperlink = new wxHyperlinkCtrl(this, wxID_ANY, _("Find dictionaries on the web.."), wxT("http://wiki.services.openoffice.org/wiki/Dictionaries"), wxDefaultPosition, wxSize(-1, -1), wxHL_DEFAULT_STYLE);

    bSizer5->Add(m_pHyperlink, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);

    wxBoxSizer* bSizer6 = new wxBoxSizer(wxHORIZONTAL);

    bSizer5->Add(bSizer6, 1, wxEXPAND, 5);

    wxBoxSizer* boxSizer9 = new wxBoxSizer(wxVERTICAL);

    bSizer6->Add(boxSizer9, 1, wxALL|wxEXPAND, 5);

    wxBoxSizer* bSizer7 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer9->Add(bSizer7, 0, wxEXPAND, 5);

    m_staticText4 = new wxStaticText(this, wxID_ANY, _("Dictionary base name:"), wxDefaultPosition, wxSize(-1, -1), 0);

    bSizer7->Add(m_staticText4, 0, wxALL, 5);

    m_pCurrentLanguage = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(60,-1), wxTE_READONLY|wxTE_CENTRE);
    wxFont m_pCurrentLanguageFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Tahoma"));
    m_pCurrentLanguage->SetFont(m_pCurrentLanguageFont);
    #if wxVERSION_NUMBER >= 3000
    m_pCurrentLanguage->SetHint(wxT(""));
    #endif

    bSizer7->Add(m_pCurrentLanguage, 1, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, 3);

    wxArrayString m_pLanguageListArr;
    m_pLanguageList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200,-1), m_pLanguageListArr, wxLB_SINGLE);

    boxSizer9->Add(m_pLanguageList, 1, wxALL|wxEXPAND, 3);
    m_pLanguageList->SetMinSize(wxSize(200,-1));

    wxStaticBoxSizer* staticBoxSizer17 = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _("Check The Following:")), wxVERTICAL);

    bSizer6->Add(staticBoxSizer17, 0, wxALL|wxEXPAND, 5);

    m_pStrings = new wxCheckBox(this, wxID_ANY, _("Strings"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_pStrings->SetValue(false);

    staticBoxSizer17->Add(m_pStrings, 0, wxALL, 2);

    m_pCppComments = new wxCheckBox(this, wxID_ANY, _("CPP comments"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_pCppComments->SetValue(false);

    staticBoxSizer17->Add(m_pCppComments, 0, wxALL, 2);

    m_pC_Comments = new wxCheckBox(this, wxID_ANY, _("C comments"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_pC_Comments->SetValue(false);

    staticBoxSizer17->Add(m_pC_Comments, 0, wxALL, 2);

    m_pDox1 = new wxCheckBox(this, wxID_ANY, _("doxygen */"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_pDox1->SetValue(false);

    staticBoxSizer17->Add(m_pDox1, 0, wxALL, 2);

    m_pDox2 = new wxCheckBox(this, wxID_ANY, _("doxygen ///"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_pDox2->SetValue(false);

    staticBoxSizer17->Add(m_pDox2, 0, wxALL, 2);

    m_pCaseSensitiveUserDictionary = new wxCheckBox(this, wxID_ANY, _("User dictionary and ignored words are case sensitive"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    m_pCaseSensitiveUserDictionary->SetValue(true);

    bSizer5->Add(m_pCaseSensitiveUserDictionary, 0, wxALL, 5);

    m_buttonClearIgnoreList = new wxButton(this, wxID_CLEAR, _("Clear ignore list"), wxDefaultPosition, wxSize(-1,-1), 0);
    m_buttonClearIgnoreList->SetToolTip(_("Clear the ignore list"));

    bSizer5->Add(m_buttonClearIgnoreList, 0, wxALL|wxEXPAND, 5);

    m_stdBtnSizer12 = new wxStdDialogButtonSizer();

    bSizer5->Add(m_stdBtnSizer12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    m_buttonOK = new wxButton(this, wxID_OK, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonOK->SetDefault();
    m_stdBtnSizer12->AddButton(m_buttonOK);

    m_buttonCancel = new wxButton(this, wxID_CANCEL, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_stdBtnSizer12->AddButton(m_buttonCancel);
    m_stdBtnSizer12->Realize();

    SetName(wxT("SpellCheckerSettings_base"));
    SetSize(-1,-1);
    if (GetSizer()) {
         GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent();
    } else {
        CentreOnScreen();
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    this->Connect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(SpellCheckerSettings_base::OnInitDialog), NULL, this);
    m_pDirPicker->Connect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(SpellCheckerSettings_base::OnDirChanged), NULL, this);
    m_pLanguageList->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(SpellCheckerSettings_base::OnLanguageSelected), NULL, this);
    m_buttonClearIgnoreList->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SpellCheckerSettings_base::OnClearIgnoreList), NULL, this);
    m_buttonOK->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SpellCheckerSettings_base::OnOk), NULL, this);
    m_buttonOK->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SpellCheckerSettings_base::OnUpdateOk), NULL, this);

}

SpellCheckerSettings_base::~SpellCheckerSettings_base()
{
    this->Disconnect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(SpellCheckerSettings_base::OnInitDialog), NULL, this);
    m_pDirPicker->Disconnect(wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler(SpellCheckerSettings_base::OnDirChanged), NULL, this);
    m_pLanguageList->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(SpellCheckerSettings_base::OnLanguageSelected), NULL, this);
    m_buttonClearIgnoreList->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SpellCheckerSettings_base::OnClearIgnoreList), NULL, this);
    m_buttonOK->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SpellCheckerSettings_base::OnOk), NULL, this);
    m_buttonOK->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SpellCheckerSettings_base::OnUpdateOk), NULL, this);

}

CorrectSpellingDlg_base::CorrectSpellingDlg_base(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC9A94InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* bSizer5 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer5);

    wxBoxSizer* bSizer6 = new wxBoxSizer(wxHORIZONTAL);

    bSizer5->Add(bSizer6, 0, wxEXPAND, 5);

    m_staticText1 = new wxStaticText(this, wxID_ANY, _("Misspelling:"), wxDefaultPosition, wxSize(-1, -1), 0);

    bSizer6->Add(m_staticText1, 0, wxLEFT|wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 5);

    m_pMisspelling = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    #if wxVERSION_NUMBER >= 3000
    m_pMisspelling->SetHint(wxT(""));
    #endif

    bSizer6->Add(m_pMisspelling, 1, wxALL|wxEXPAND, 5);

    wxBoxSizer* bSizer7 = new wxBoxSizer(wxHORIZONTAL);

    bSizer5->Add(bSizer7, 1, wxEXPAND, 5);

    wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);

    bSizer7->Add(bSizer2, 1, wxALL|wxEXPAND, 5);

    m_staticText2 = new wxStaticText(this, wxID_ANY, _("Suggestions:"), wxDefaultPosition, wxSize(-1, -1), wxBORDER_STATIC);

    bSizer2->Add(m_staticText2, 0, wxLEFT|wxRIGHT|wxTOP|wxEXPAND, 3);

    wxArrayString m_pSuggestionsArr;
    m_pSuggestions = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200,-1), m_pSuggestionsArr, 0);

    bSizer2->Add(m_pSuggestions, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 3);

    wxBoxSizer* bSizer12 = new wxBoxSizer(wxVERTICAL);

    bSizer7->Add(bSizer12, 0, wxALL|wxEXPAND, 5);

    wxFlexGridSizer* fgSizer4 = new wxFlexGridSizer(2, 2, 0, 0);
    fgSizer4->SetFlexibleDirection( wxBOTH );
    fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

    bSizer12->Add(fgSizer4, 1, wxEXPAND, 5);

    m_button1 = new wxButton(this, wxID_ANY, _("Change"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_button1->SetDefault();

    fgSizer4->Add(m_button1, 0, wxALL, 3);

    m_button2 = new wxButton(this, wxID_ANY, _("Ignore"), wxDefaultPosition, wxSize(-1, -1), 0);

    fgSizer4->Add(m_button2, 0, wxALL, 3);

    m_button4 = new wxButton(this, wxID_ANY, _("Add"), wxDefaultPosition, wxSize(-1, -1), 0);

    fgSizer4->Add(m_button4, 0, wxALL, 3);

    m_button5 = new wxButton(this, wxID_ANY, _("Suggest"), wxDefaultPosition, wxSize(-1, -1), 0);

    fgSizer4->Add(m_button5, 0, wxALL, 3);

    m_button3 = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxSize(-1, -1), 0);

    bSizer12->Add(m_button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    SetName(wxT("CorrectSpellingDlg_base"));
    SetSize(-1,-1);
    if (GetSizer()) {
         GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent();
    } else {
        CentreOnScreen();
    }
    // Connect events
    this->Connect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(CorrectSpellingDlg_base::OnInitDialog), NULL, this);
    m_pSuggestions->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(CorrectSpellingDlg_base::OnSuggestionSelected), NULL, this);
    m_pSuggestions->Connect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnDblClickSuggestions), NULL, this);
    m_button1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnChangeClick), NULL, this);
    m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnIgnoreClick), NULL, this);
    m_button4->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnAddClick), NULL, this);
    m_button5->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnSuggestClick), NULL, this);

}

CorrectSpellingDlg_base::~CorrectSpellingDlg_base()
{
    this->Disconnect(wxEVT_INIT_DIALOG, wxInitDialogEventHandler(CorrectSpellingDlg_base::OnInitDialog), NULL, this);
    m_pSuggestions->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(CorrectSpellingDlg_base::OnSuggestionSelected), NULL, this);
    m_pSuggestions->Disconnect(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnDblClickSuggestions), NULL, this);
    m_button1->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnChangeClick), NULL, this);
    m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnIgnoreClick), NULL, this);
    m_button4->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnAddClick), NULL, this);
    m_button5->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CorrectSpellingDlg_base::OnSuggestClick), NULL, this);

}
