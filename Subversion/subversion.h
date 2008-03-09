#ifndef SUBVERSION_H
#define SUBVERSION_H

#include "svnxmlparser.h"
#include "plugin.h"
#include "wx/html/htmlwin.h"
#include "map"
#include "list"
#include "wx/timer.h"
#include "wx/treectrl.h"
#include "svnoptions.h"

class SvnDriver;
class VdtcTreeItemBase;

class SubversionPlugin : public IPlugin
{
	wxMenu *m_svnMenu;
	SvnDriver *m_svn;
	wxEvtHandler *topWin;
	wxTreeItemId m_firstVisibleItem;
	SvnOptions m_options;	
	friend class SvnDriver;
	bool m_isValid;
	bool m_initIsDone;
	wxMenuItem *m_sepItem;
	
public:
	SubversionPlugin(IManager *manager);
	virtual ~SubversionPlugin();
	const SvnOptions& GetOptions() const{return m_options;}

	//--------------------------------------------
	//Abstract methods
	//--------------------------------------------
	virtual wxToolBar *CreateToolBar(wxWindow *parent);
	virtual void CreatePluginMenu(wxMenu *pluginsMenu);
	virtual void HookPopupMenu(wxMenu *menu, MenuType type);
	virtual void UnHookPopupMenu(wxMenu *menu, MenuType type);
	virtual void UnPlug();
	
protected:
	wxMenu *CreatePopMenu();
	wxMenu *CreateEditorPopMenu();
	
	//
	//Helper functions
	///////////////////////////////////////////////////////
	wxString FormatRaws(const wxArrayString &lines, const wxString &basePath, SvnXmlParser::FileState state);
	
	// event handlers
	///////////////////////////////////////////////////////
	void OnUpdate(wxCommandEvent &event);
	void OnCommit(wxCommandEvent &event);
	void OnDiff(wxCommandEvent &event);
	void OnCleanup(wxCommandEvent &event);
	void OnFileSaved(wxCommandEvent &event);
	void OnRefreshFolderStatus(wxCommandEvent &event);
	void OnFileExplorerInitDone(wxCommandEvent &event);
	void OnOptions(wxCommandEvent &event);
	void OnChangeLog(wxCommandEvent &event);
	void OnSvnAbort(wxCommandEvent &event);
	void OnSvnAdd(wxCommandEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnRevert(wxCommandEvent &event);
	void OnProjectFileAdded(wxCommandEvent &event);
	void OnAppInitDone(wxCommandEvent &event);
	void OnCommitFile(wxCommandEvent &e);
	void OnUpdateFile(wxCommandEvent &e);
	void OnDiffFile(wxCommandEvent &e);
	void OnRevertFile(wxCommandEvent &e);
	void DoGenerateReport(const wxArrayString &output, const wxString &basePath);
	void OnLinkClicked(wxHtmlLinkEvent &e);
};

#endif //SUBVERSION_H

