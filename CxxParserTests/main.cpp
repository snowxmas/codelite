#include <stdio.h>
#include "tester.h"
#include "fileutils.h"
#include <wx/init.h>
#include <iostream>
#include "ctags_manager.h"
#include "CxxVariableScanner.h"

static wxString InputFile(const wxString& name)
{
    wxFileName fn("../Tests", name);
    wxString content;
    FileUtils::ReadFileContent(fn, content);
    return content;
}

TEST_FUNC(test_cxx_normalize_signature)
{
    wxString buffer = "const std::map<int, int>& m = std::map<int, int>(), int number = -1, const "
                      "std::vector<std::pair<int, int> >& v";
    wxString res =
        TagsManagerST::Get()->NormalizeFunctionSig(buffer, Normalize_Func_Name | Normalize_Func_Default_value);
    return true;
}

TEST_FUNC(test_cxx_local_variables)
{
    wxString buffer = "(struct wxString *pstr, const std::string& name)"
                      "std::vector<int> numbers = {1,2,3};"
                      "std::vector<int> numbers2 {1,2,3};"
                      "std::vector<std::pair<int, int>>::iterator myIter;";
    CxxVariableScanner scanner(buffer, eCxxStandard::kCxx11, wxStringTable_t());
    CxxVariable::Map_t vars = scanner.GetVariablesMap();
    CHECK_BOOL(vars.count("pstr") == 1);
    CHECK_BOOL(vars.count("name") == 1);
    CHECK_BOOL(vars.count("numbers") == 1);
    CHECK_BOOL(vars.count("numbers2") == 1);
    CHECK_BOOL(vars.count("myIter") == 1);
    return true;
}

TEST_FUNC(test_cxx_class_method_impl)
{
    wxString buffer = "void MainFrame::OnFoo() {}";
    CxxVariableScanner scanner(buffer, eCxxStandard::kCxx11, wxStringTable_t());
    CxxVariable::Map_t vars = scanner.GetVariablesMap();
    CHECK_BOOL(vars.count("MainFrame") == 0);
    return true;
}

TEST_FUNC(test_cxx_c11_template)
{
    wxString buffer = "std::vector<std::pair<int, int>> v;";
    CxxVariableScanner scanner(buffer, eCxxStandard::kCxx11, wxStringTable_t());
    CxxVariable::Map_t vars = scanner.GetVariablesMap();
    CHECK_BOOL(vars.count("v") == 1);
    return true;
}

TEST_FUNC(test_cxx_multiple_variables)
{
    wxString buffer = "wxBitmap bmp(1,1);\n"
                      "std::vector<int> foo, bar, baz;";

    CxxVariableScanner scanner(buffer, eCxxStandard::kCxx11, wxStringTable_t());
    CxxVariable::Map_t vars = scanner.GetVariablesMap();
    CHECK_BOOL(vars.count("foo") == 1);
    CHECK_BOOL(vars.count("bar") == 1);
    CHECK_BOOL(vars.count("baz") == 1);
    return true;
}

TEST_FUNC(test_cxx_decltype_template_variable)
{
    wxString buffer =
        "auto comp = [&](std::shared_ptr<int> a, std::shared_ptr<int> b) { return (*a) < (*b);}\n"
        "std::priority_queue<std::shared_ptr<int>, std::vector<std::shared_ptr<int>>,  decltype(comp)> queue(comp);";

    CxxVariableScanner scanner(buffer, eCxxStandard::kCxx11, wxStringTable_t());
    CxxVariable::Map_t vars = scanner.GetVariablesMap();
    CHECK_BOOL(vars.count("queue") == 1);
    CxxVariable::Ptr_t var = vars["queue"];
    std::cout << "Type:" << var->GetTypeAsCxxString() << std::endl;
    return true;
}

int main(int argc, char** argv)
{
    wxInitializer initializer(argc, argv);
    Tester::Instance()->RunTests();
    return 0;
}
