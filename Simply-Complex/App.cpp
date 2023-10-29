#include <wx/wx.h>
#include "App.h"

bool App::OnInit(void) {
    SimplyComplex::MainFrame* mainFrame = new SimplyComplex::MainFrame("Simply Complex");
    mainFrame->Center();
    mainFrame->Show();
    return true;
}

wxIMPLEMENT_APP(App);