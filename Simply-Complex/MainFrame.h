#pragma once
#include <vector>
#include <wx/wx.h>
#include "ColorPane.h"

namespace SimplyComplex {
    constexpr auto APP_WINDOW_WIDTH = 1200;
    constexpr auto APP_WINDOW_HEIGHT = 800;
    constexpr auto INITIAL_FUNCTION_EXPR = "";

    class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
        virtual ~MainFrame(void);
    private:
        const std::vector<std::string> colorCodes = {
            "#fd7f6f", "#7eb0d5", "#b2e061",
            "#bd7ebe", "#ffb55a", "ffee65"
        };
        std::vector<ColorPane*> colorPanes;
        wxLog* logger;
    };
}