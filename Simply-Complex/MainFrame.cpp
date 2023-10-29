#define _CRT_SECURE_NO_WARNINGS

#include "MainFrame.h"
#include "DrawingCanvas.h"
#include "ColorPane.h"

#include <iostream>

SimplyComplex::MainFrame::MainFrame(const wxString& title) : wxFrame(
    nullptr,
    wxID_ANY,
    title,
    wxDefaultPosition,
    wxDefaultSize,
    wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER
) {
    this->logger = new wxLogWindow(this, "Log", true, false);
    wxLog::SetActiveTarget(logger);
    this->SetSize(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
    auto panel = new wxPanel(this);
    auto functionTextField = new wxTextCtrl(panel, wxID_ANY, INITIAL_FUNCTION_EXPR, wxPoint(500, 50));
    auto functionInputCanvas = new DrawingCanvas(panel, wxID_ANY, wxPoint(0, 0), wxSize(300, 300));

    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    wxLogMessage("HELLO");

    //std::cout << "TEST" <<_CRT_SECURE_NO_WARNINGS std::endl;
    for (int i = 0; i < this->colorCodes.size(); i++) {
        wxLogMessage("TEST %d", i);
        auto colorPane = new ColorPane(panel, wxID_ANY, wxColour(this->colorCodes[i]), wxPoint(i * 50, 350), wxSize(50, 50));
        this->colorPanes.push_back(colorPane);
        sizer->Add(colorPane);
    }
    //panel->SetSizer(sizer);
    //auto singleColorPane = new ColorPane(panel, wxID_ANY, wxColour(100, 100, 200), wxPoint(100, 400), wxSize(50, 50));
}

SimplyComplex::MainFrame::~MainFrame(void) {
    for (auto cp : this->colorPanes) {
        delete cp;
    }
    wxLog::SetActiveTarget(nullptr);
    delete this->logger;
}