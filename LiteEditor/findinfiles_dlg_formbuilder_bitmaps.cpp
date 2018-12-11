//
// This file was automatically generated by wxrc, do not edit by hand.
//

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include <wx/filesys.h>
#include <wx/fs_mem.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>

#if wxCHECK_VERSION(2,8,5) && wxABI_VERSION >= 20805
    #define XRC_ADD_FILE(name, data, size, mime) \
        wxMemoryFSHandler::AddFileWithMimeType(name, data, size, mime)
#else
    #define XRC_ADD_FILE(name, data, size, mime) \
        wxMemoryFSHandler::AddFile(name, data, size)
#endif

static size_t xml_res_size_0 = 0;
static unsigned char xml_res_file_0[] = {
};

static size_t xml_res_size_1 = 0;
static unsigned char xml_res_file_1[] = {
};

static size_t xml_res_size_2 = 407;
static unsigned char xml_res_file_2[] = {
60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,
110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,63,62,10,60,114,101,
115,111,117,114,99,101,32,120,109,108,110,115,61,34,104,116,116,112,58,
47,47,119,119,119,46,119,120,119,105,100,103,101,116,115,46,111,114,103,
47,119,120,120,114,99,34,62,10,32,32,60,33,45,45,32,72,97,110,100,108,101,
114,32,71,101,110,101,114,97,116,105,111,110,32,105,115,32,79,78,32,45,
45,62,10,32,32,60,111,98,106,101,99,116,32,99,108,97,115,115,61,34,119,
120,66,105,116,109,97,112,34,32,110,97,109,101,61,34,49,54,45,102,105,110,
100,95,105,110,95,102,105,108,101,115,34,62,102,105,110,100,105,110,102,
105,108,101,115,95,100,108,103,95,102,111,114,109,98,117,105,108,100,101,
114,95,98,105,116,109,97,112,115,46,99,112,112,36,46,46,95,98,105,116,109,
97,112,115,95,49,54,45,102,105,110,100,95,105,110,95,102,105,108,101,115,
46,112,110,103,60,47,111,98,106,101,99,116,62,10,32,32,60,111,98,106,101,
99,116,32,99,108,97,115,115,61,34,119,120,66,105,116,109,97,112,34,32,110,
97,109,101,61,34,49,54,45,102,105,110,100,95,105,110,95,102,105,108,101,
115,64,50,120,34,62,102,105,110,100,105,110,102,105,108,101,115,95,100,
108,103,95,102,111,114,109,98,117,105,108,100,101,114,95,98,105,116,109,
97,112,115,46,99,112,112,36,46,46,95,98,105,116,109,97,112,115,95,49,54,
45,102,105,110,100,95,105,110,95,102,105,108,101,115,64,50,120,46,112,110,
103,60,47,111,98,106,101,99,116,62,10,60,47,114,101,115,111,117,114,99,
101,62,10};

void wxCABC4InitBitmapResources()
{

    // Check for memory FS. If not present, load the handler:
    {
        wxMemoryFSHandler::AddFile(wxT("XRC_resource/dummy_file"), wxT("dummy one"));
        wxFileSystem fsys;
        wxFSFile *f = fsys.OpenFile(wxT("memory:XRC_resource/dummy_file"));
        wxMemoryFSHandler::RemoveFile(wxT("XRC_resource/dummy_file"));
        if (f) delete f;
        else wxFileSystem::AddHandler(new wxMemoryFSHandlerBase);
    }

    XRC_ADD_FILE(wxT("XRC_resource/findinfiles_dlg_formbuilder_bitmaps.cpp$.._bitmaps_16-find_in_files.png"), xml_res_file_0, xml_res_size_0, wxT("image/png"));
    XRC_ADD_FILE(wxT("XRC_resource/findinfiles_dlg_formbuilder_bitmaps.cpp$.._bitmaps_16-find_in_files@2x.png"), xml_res_file_1, xml_res_size_1, wxT("image/png"));
    XRC_ADD_FILE(wxT("XRC_resource/findinfiles_dlg_formbuilder_bitmaps.cpp$_home_eran_devl_codelite_formbuilder_findinfiles_dlg_formbuilder_bitmaps.xrc"), xml_res_file_2, xml_res_size_2, wxT("text/xml"));
    wxXmlResource::Get()->Load(wxT("memory:XRC_resource/findinfiles_dlg_formbuilder_bitmaps.cpp$_home_eran_devl_codelite_formbuilder_findinfiles_dlg_formbuilder_bitmaps.xrc"));
}
