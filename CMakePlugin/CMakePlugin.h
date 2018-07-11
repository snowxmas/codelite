//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 Eran Ifrah
// file name            : CMakePlugin.h
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

/* ************************************************************************ */
/*                                                                          */
/* CMakePlugin for Codelite                                                 */
/* Copyright (C) 2013 Jiří Fatka <ntsfka@gmail.com>                         */
/*                                                                          */
/* This program is free software: you can redistribute it and/or modify     */
/* it under the terms of the GNU General Public License as published by     */
/* the Free Software Foundation, either version 3 of the License, or        */
/* (at your option) any later version.                                      */
/*                                                                          */
/* This program is distributed in the hope that it will be useful,          */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             */
/* GNU General Public License for more details.                             */
/*                                                                          */
/* You should have received a copy of the GNU General Public License        */
/* along with this program. If not, see <http://www.gnu.org/licenses/>.     */
/*                                                                          */
/* ************************************************************************ */

#ifndef CMAKE_PLUGIN_H_
#define CMAKE_PLUGIN_H_

/* ************************************************************************ */
/* INCLUDES                                                                 */
/* ************************************************************************ */

// wxWidgets
#include <wx/scopedptr.h>

// CodeLite
#include "plugin.h"
#include "project.h"
#include "build_config.h"
#include "cl_command_event.h"

// CMakePlugin
#include "CMakeConfiguration.h"

/* ************************************************************************ */
/* FORWARD DECLARATIONS                                                     */
/* ************************************************************************ */

class CMake;
class CMakeSettingsManager;
class CMakeProjectSettings;
class CMakeGenerator;
class CMakeHelpTab;

/* ************************************************************************ */
/* CLASSES                                                                  */
/* ************************************************************************ */

/**
 * @brief CMake plugin for CodeLite.
 *
 * Here is an explanation how the plugin works. For each project a makefile
 * is generated with code that calls cmake if there is no Makefile in build
 * directory (create directory if missing). Then is generated code built by
 * calling make in build directory. Changes in CMakeLists.txt is detected
 * by Makefile generated by cmake. Some CMakeLists.txt can contains code that
 * takes all source files in specific directory and doesn't list them
 * directly. In this case if a source file is added or removed the plugin
 * doesn't regenerate CMake files because it's not able to detect changes.
 * For this purpose there is a button that marks configuration dirty and
 * forces plugin to regenerate CMake files.
 */
class CMakePlugin : public IPlugin
{

    // Public Constants
public:
    /**
     * @brief Name of the output file - CMakeLists.txt
     */
    static const wxString CMAKELISTS_FILE;

    // Public Ctors & Dtors
public:
    /**
     * @brief Create plugin.
     *
     * @param manager
     */
    explicit CMakePlugin(IManager* manager);

    /**
     * @brief Destructor.
     */
    virtual ~CMakePlugin();

    // Public Accessors
public:
    /**
     * @brief Returns a pointer to the manager object.
     *
     * @return
     */
    IManager* GetManager() const { return m_mgr; }

    /**
     * @brief Returns CMake application pointer.
     *
     * @return
     */
    CMake* GetCMake() const { return m_cmake.get(); }

    /**
     * @brief Returns CMake configuration.
     *
     * @return
     */
    CMakeConfiguration* GetConfiguration() const { return m_configuration.get(); }

    /**
     * @brief Returns directory where is workspace project stored.
     *
     * @return Path to workspace
     */
    wxFileName GetWorkspaceDirectory() const;

    /**
     * @brief Returns directory where is the given project stored.
     *
     * @param projectName
     *
     * @return Project directory.
     */
    wxFileName GetProjectDirectory(const wxString& projectName) const;

    /**
     * @brief Returns seleted project.
     *
     * @return Pointer to project.
     */
    ProjectPtr GetSelectedProject() const { return m_mgr->GetSelectedProject(); }

    /**
     * @brief Returns currently selected config for seleted project.
     *
     * @return
     */
    wxString GetSelectedProjectConfig() const;

    /**
     * @brief Returns currently selected build config.
     *
     * @return
     */
    BuildConfigPtr GetSelectedBuildConfig() const;

    /**
     * @brief Returns a list of supported generators.
     *
     * Plugin supports only generators that generate directly buildable
     * output like Unix Makefile or MinGW Makefile.
     *
     * @return List.
     */
    wxArrayString GetSupportedGenerators() const;

    /**
     * @brief Check if Help pane is detached.
     *
     * @return
     */
    bool IsPaneDetached() const;

    // Public Operations
public:
    /**
     * @brief Creates a tool bar.
     *
     * @param parent Parent window.
     *
     * @return Codelite tool bar or NULL.
     */
    void CreateToolBar(clToolBar* toolbar);

    /**
     * @brief Creates a menu for plugin.
     *
     * @param pluginsMenu
     */
    void CreatePluginMenu(wxMenu* pluginsMenu);

    /**
     * @brief Unplug plugin.
     */
    void UnPlug();

    /**
     * @brief Check if CMakeLists.txt exists in given directory.
     *
     * @param directory Directory where CMakeLists.txt should be located.
     *
     * @return If CMakeLists.txt exists in directory.
     */
    bool ExistsCMakeLists(wxFileName directory) const;

    /**
     * @brief Open CMakeLists.txt in given directory.
     *
     * @param directory Directory where CMakeLists.txt should be located.
     */
    void OpenCMakeLists(wxFileName directory) const;

    // Public Events
public:
    /**
     * @brief add our 'Run CMake' command to the menu
     */
    void OnProjectContextMenu(clContextMenuEvent& event);
    /**
     * @brief edit the workspace context menu
     */
    void OnWorkspaceContextMenu(clContextMenuEvent& event);

    /**
     * @brief Run CMake for the selected project
     */
    void OnRunCMake(wxCommandEvent& event);

    /**
     * @brief Open the selected projects' CMakeLists.txt
     */
    void OnOpenCMakeLists(wxCommandEvent& event);
    /**
     * @brief export CMakeLists.txt file for the selected project
     */
    void OnExportCMakeLists(wxCommandEvent& event);

    void OnToggleHelpTab(clCommandEvent& event);
    /**
     * @brief On setting dialog.
     *
     * @param event
     */
    void OnSettings(wxCommandEvent& event);

    /**
     * @brief capture cmake output
     */
    void OnCMakeOutput(clProcessEvent& event);
    /**
     * @brief cmake process terminated
     */
    void OnCMakeTerminated(clProcessEvent& event);

    /**
     * @brief a file has been removed from the project, re-generate CMakeLists.txt
     */
    void OnFileRemoved(clCommandEvent& event);
    /**
     * @brief a file has been added from the project, re-generate CMakeLists.txt
     */
    void OnFileAdded(clCommandEvent& event);

protected:
    void DoRunCMake(ProjectPtr p);

    // Private Operations
private:
    /// CMake configuration.
    wxScopedPtr<CMakeConfiguration> m_configuration;

    /// CMake application
    wxScopedPtr<CMake> m_cmake;

    CMakeHelpTab* m_helpTab;
};

/* ************************************************************************ */

#endif // CMAKE_PLUGIN_H_
