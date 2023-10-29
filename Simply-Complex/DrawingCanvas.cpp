/*
MIT License

Copyright (c) 2022 lszl84 @ GitHub

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "DrawingCanvas.h"

DrawingCanvas::DrawingCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
    : wxWindow(parent, id, pos, size) {
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);

    BuildContextMenu();
    this->Bind(wxEVT_CONTEXT_MENU, &DrawingCanvas::OnContextMenuEvent, this);
}

void DrawingCanvas::OnPaint(wxPaintEvent&) {
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc != nullptr) {
        DrawOnContext(gc);
        delete gc;
    }
}

void DrawingCanvas::DrawOnContext(wxGraphicsContext* gc)
{
    for (const auto& s : squiggles) {
        auto pointsVector = s.points;
        if (pointsVector.size() > 1) {
            gc->SetPen(wxPen(s.color, s.width));
            gc->StrokeLines(pointsVector.size(), pointsVector.data());
        }
    }
}

//void DrawingCanvas::ShowSaveDialog() {
//    wxFileDialog saveFileDialog(this, _("Save drawing"), "", "",
//        "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
//
//    if (saveFileDialog.ShowModal() == wxID_CANCEL)
//        return;
//
//    wxBitmap bitmap(this->GetSize() * this->GetContentScaleFactor());
//
//    wxMemoryDC memDC;
//
//    memDC.SetUserScale(this->GetContentScaleFactor(), this->GetContentScaleFactor());
//
//    memDC.SelectObject(bitmap);
//    memDC.SetBackground(*wxWHITE_BRUSH);
//    memDC.Clear();
//
//    wxGraphicsContext* gc = wxGraphicsContext::Create(memDC);
//
//    if (gc) {
//        DrawOnContext(gc);
//        delete gc;
//    }
//
//    bitmap.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
//}

void DrawingCanvas::OnMouseDown(wxMouseEvent&) {
    squiggles.push_back({ {}, currentColor, currentWidth });
    isDrawing = true;
}

void DrawingCanvas::OnMouseMove(wxMouseEvent& event) {
    if (isDrawing) {
        auto pt = event.GetPosition();
        auto& currentSquiggle = squiggles.back();

        currentSquiggle.points.push_back(pt);
        Refresh();
    }
}

void DrawingCanvas::OnMouseUp(wxMouseEvent&) {
    isDrawing = false;
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent&) {
    isDrawing = false;
}

void DrawingCanvas::BuildContextMenu() {
    auto clear = contextMenu.Append(wxID_ANY, "&Clear");
    //auto save = contextMenu.Append(wxID_ANY, "Save &As...");

    this->Bind(
        wxEVT_MENU,
        [this](wxCommandEvent&)
        {
            this->squiggles.clear();
            this->Refresh();
        },
        clear->GetId());
    //
    //    this->Bind(
    //        wxEVT_MENU,
    //        [this](wxCommandEvent&)
    //        {
    //            this->ShowSaveDialog();
    //        },
    //        save->GetId());
}

void DrawingCanvas::OnContextMenuEvent(wxContextMenuEvent& e) {
    auto clientPos = e.GetPosition() == wxDefaultPosition
        ? wxPoint(this->GetSize().GetWidth() / 2, this->GetSize().GetHeight() / 2)
        : this->ScreenToClient(e.GetPosition());
    PopupMenu(&this->contextMenu, clientPos);
}