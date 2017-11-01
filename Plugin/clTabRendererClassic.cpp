#include "clTabRendererClassic.h"
#include <wx/font.h>
#include <wx/settings.h>
#include <wx/dcmemory.h>
#include <wx/settings.h>
#include "drawingutils.h"

#define DRAW_LINE(__p1, __p2) \
    dc.DrawLine(__p1, __p2);  \
    dc.DrawLine(__p1, __p2);  \
    dc.DrawLine(__p1, __p2);  \
    dc.DrawLine(__p1, __p2);

clTabRendererClassic::clTabRendererClassic()
{
    bottomAreaHeight = 3;
    majorCurveWidth = 15;
    smallCurveWidth = 4;
    overlapWidth = 20;
    verticalOverlapWidth = 3;
}

clTabRendererClassic::~clTabRendererClassic() {}

void clTabRendererClassic::InitDarkColours(clTabColours& colours)
{
    colours.activeTabTextColour = "WHITE";
    colours.activeTabBgColour = wxColour("rgb(52, 61, 70)");
    colours.activeTabPenColour = wxColour("rgb(75, 81, 88)");
    colours.activeTabInnerPenColour = wxColour("rgb(46, 55, 63)");
    colours.inactiveTabTextColour = wxColour("rgb(200, 200, 200)");
    colours.inactiveTabBgColour = wxColour("rgb(77, 85, 92)");
    colours.inactiveTabPenColour = wxColour("rgb(88,95,101)");
    colours.inactiveTabInnerPenColour = wxColour("rgb(73,81,87)");
    colours.tabAreaColour = wxColour("rgb(117, 123, 129)");
}


void clTabRendererClassic::InitLightColours(clTabColours& colours)
{
    colours.activeTabTextColour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
    colours.inactiveTabTextColour = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
    colours.activeTabBgColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
    colours.inactiveTabBgColour = colours.activeTabBgColour.ChangeLightness(90); // darker
    colours.activeTabPenColour = colours.inactiveTabPenColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW);
    colours.activeTabInnerPenColour = colours.inactiveTabInnerPenColour =
        colours.inactiveTabPenColour.ChangeLightness(180);
    colours.tabAreaColour = wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE).ChangeLightness(80);
}

void clTabRendererClassic::Draw(wxDC& dc, const clTabInfo& tabInfo, const clTabColours& colors, size_t style)
{
    const int TOP_SMALL_HEIGHT = 2;

    clTabColours colours;

    // Initialise the colours
    if(colors.IsDarkColours()) {
        InitDarkColours(colours);

    } else {
        InitLightColours(colours);
    }

    wxColour bgColour(tabInfo.IsActive() ? colours.activeTabBgColour : colours.inactiveTabBgColour);
    wxColour penColour(tabInfo.IsActive() ? colours.activeTabPenColour : colours.inactiveTabPenColour);
    wxFont font = GetTabFont();
    dc.SetTextForeground(tabInfo.IsActive() ? colours.activeTabTextColour : colours.inactiveTabTextColour);
    dc.SetFont(font);

    if(style & kNotebook_BottomTabs) {
        // Bottom tabs
        {
            wxPoint points[6];
            points[0] = tabInfo.m_rect.GetTopLeft();

            points[1].x = points[0].x + majorCurveWidth;
            points[1].y = tabInfo.m_rect.GetBottomLeft().y - TOP_SMALL_HEIGHT;

            points[2].x = points[1].x + smallCurveWidth;
            points[2].y = points[1].y + TOP_SMALL_HEIGHT;

            points[3].x = points[0].x + (tabInfo.m_rect.GetWidth() - (majorCurveWidth + smallCurveWidth));
            points[3].y = points[2].y;

            points[4].x = points[3].x + smallCurveWidth;
            points[4].y = points[1].y;

            points[5] = tabInfo.m_rect.GetTopRight();

            dc.SetPen(penColour);
            dc.SetBrush(bgColour);
            dc.DrawPolygon(6, points);
        }
        {
            wxPoint points[6];
            points[0] = tabInfo.m_rect.GetTopLeft();
            points[0].x += 1;

            points[1].x = points[0].x + majorCurveWidth;
            points[1].y = tabInfo.m_rect.GetBottomLeft().y - TOP_SMALL_HEIGHT - 1;

            points[2].x = points[1].x + smallCurveWidth;
            points[2].y = points[1].y + TOP_SMALL_HEIGHT;

            points[3].x = points[0].x + (tabInfo.m_rect.GetWidth() - 2 - (majorCurveWidth + smallCurveWidth));
            points[3].y = points[2].y;

            points[4].x = points[3].x + smallCurveWidth;
            points[4].y = points[1].y;

            points[5] = tabInfo.m_rect.GetTopRight();
            points[5].x -= 2;

            dc.SetPen(tabInfo.IsActive() ? colours.activeTabInnerPenColour : colours.inactiveTabInnerPenColour);
            dc.SetBrush(bgColour);
            dc.DrawPolygon(6, points);
        }
    } else if(IS_VERTICAL_TABS(style)) {

        // Left side tabs
        wxRect rotatedRect(0, 0, tabInfo.m_rect.GetHeight(), tabInfo.m_rect.GetWidth());
        wxBitmap b(rotatedRect.GetSize());

        wxMemoryDC tmpDC(b);
        tmpDC.SetPen(colours.tabAreaColour);
        tmpDC.SetBrush(colours.tabAreaColour);
        tmpDC.DrawRectangle(rotatedRect);
        tmpDC.SetFont(font);
        tmpDC.SetTextForeground(tabInfo.IsActive() ? colours.activeTabTextColour : colours.inactiveTabTextColour);

        tmpDC.SetPen(penColour);
        tmpDC.SetBrush(bgColour);
        if(tabInfo.IsActive()) {
            {
                wxPoint points[6];
                points[0] = rotatedRect.GetBottomLeft();

                points[1].x = points[0].x + majorCurveWidth;
                points[1].y = rotatedRect.GetLeftTop().y + TOP_SMALL_HEIGHT;

                points[2].x = points[1].x + smallCurveWidth;
                points[2].y = points[1].y - TOP_SMALL_HEIGHT;

                points[3].x = points[0].x + (rotatedRect.GetWidth() - (majorCurveWidth + smallCurveWidth));
                points[3].y = points[2].y;

                points[4].x = points[3].x + smallCurveWidth;
                points[4].y = points[3].y + TOP_SMALL_HEIGHT;

                points[5] = rotatedRect.GetBottomRight();

                tmpDC.SetPen(penColour);
                tmpDC.SetBrush(bgColour);
                tmpDC.DrawPolygon(6, points);
            }

            {
                wxPoint points[6];
                points[0] = rotatedRect.GetBottomLeft();
                points[0].x += 1;

                points[1].x = points[0].x + majorCurveWidth;
                points[1].y = rotatedRect.GetLeftTop().y + TOP_SMALL_HEIGHT + 1;

                points[2].x = points[1].x + smallCurveWidth;
                points[2].y = points[1].y - TOP_SMALL_HEIGHT;

                points[3].x = points[0].x + (rotatedRect.GetWidth() - 2 - (majorCurveWidth + smallCurveWidth));
                points[3].y = points[2].y;

                points[4].x = points[3].x + smallCurveWidth;
                points[4].y = points[3].y + TOP_SMALL_HEIGHT;

                points[5] = rotatedRect.GetBottomRight();
                points[5].x -= 2;

                tmpDC.SetPen(tabInfo.IsActive() ? colours.activeTabInnerPenColour : colours.inactiveTabInnerPenColour);
                tmpDC.SetBrush(bgColour);
                tmpDC.DrawPolygon(6, points);
            }
        } else {
            // Inactive tabs
            wxDirection direction = wxNORTH;
            wxPoint basePoint = ((style & kNotebook_LeftTabs) ? rotatedRect.GetLeftTop() : rotatedRect.GetRightTop());
            {
                wxPoint pt = basePoint;
                pt.x -= 1;
                wxRect gr(pt, wxSize(1, rotatedRect.GetHeight()));
                tmpDC.SetPen(*wxTRANSPARENT_PEN);
                tmpDC.GradientFillLinear(gr, colours.inactiveTabPenColour, bgColour, direction);
            }
            {
                wxPoint pt = basePoint;
                wxRect gr(pt, wxSize(1, rotatedRect.GetHeight()));
                tmpDC.SetPen(*wxTRANSPARENT_PEN);
                tmpDC.GradientFillLinear(gr, colours.inactiveTabInnerPenColour, bgColour, direction);
            }
            {
                wxPoint pt = basePoint;
                pt.x += 1;
                wxRect gr(pt, wxSize(1, rotatedRect.GetHeight()));
                tmpDC.SetPen(*wxTRANSPARENT_PEN);
                tmpDC.GradientFillLinear(gr, colours.inactiveTabPenColour, bgColour, direction);
            }
        }

        // Vertical tabs
        // Draw bitmap
        if(tabInfo.m_bitmap.IsOk()) {
            tmpDC.DrawBitmap(tabInfo.m_bitmap, tabInfo.m_bmpY, tabInfo.m_bmpX);
        }

        tmpDC.DrawText(tabInfo.m_label, tabInfo.m_textY, tabInfo.m_textX);
        if(tabInfo.IsActive() && (style & kNotebook_CloseButtonOnActiveTab)) {
            DrawButton(tmpDC, wxRect(tabInfo.m_bmpCloseY, tabInfo.m_bmpCloseX, CLOSE_BUTTON_SIZE, CLOSE_BUTTON_SIZE),
                       colours, eButtonState::kNormal);
        }
        tmpDC.SelectObject(wxNullBitmap);
        wxImage img = b.ConvertToImage();
        img = img.Rotate90((style & kNotebook_RightTabs));
        b = wxBitmap(img);
        dc.DrawBitmap(b, tabInfo.m_rect.GetTopLeft());

    } else {
        // Default tabs (placed at the top)
        {
            wxPoint points[6];
            points[0] = tabInfo.m_rect.GetBottomLeft();

            points[1].x = points[0].x + majorCurveWidth;
            points[1].y = tabInfo.m_rect.GetLeftTop().y + TOP_SMALL_HEIGHT;

            points[2].x = points[1].x + smallCurveWidth;
            points[2].y = points[1].y - TOP_SMALL_HEIGHT;

            points[3].x = points[0].x + (tabInfo.m_rect.GetWidth() - (majorCurveWidth + smallCurveWidth));
            points[3].y = points[2].y;

            points[4].x = points[3].x + smallCurveWidth;
            points[4].y = points[3].y + TOP_SMALL_HEIGHT;

            points[5] = tabInfo.m_rect.GetBottomRight();

            dc.SetPen(penColour);
            dc.SetBrush(bgColour);
            dc.DrawPolygon(6, points);
        }

        {
            wxPoint points[6];
            points[0] = tabInfo.m_rect.GetBottomLeft();
            points[0].x += 1;

            points[1].x = points[0].x + majorCurveWidth;
            points[1].y = tabInfo.m_rect.GetLeftTop().y + TOP_SMALL_HEIGHT + 1;

            points[2].x = points[1].x + smallCurveWidth;
            points[2].y = points[1].y - TOP_SMALL_HEIGHT;

            points[3].x = points[0].x + (tabInfo.m_rect.GetWidth() - 2 - (majorCurveWidth + smallCurveWidth));
            points[3].y = points[2].y;

            points[4].x = points[3].x + smallCurveWidth;
            points[4].y = points[3].y + TOP_SMALL_HEIGHT;

            points[5] = tabInfo.m_rect.GetBottomRight();
            points[5].x -= 2;

            dc.SetPen(tabInfo.IsActive() ? colours.activeTabInnerPenColour : colours.inactiveTabInnerPenColour);
            dc.SetBrush(bgColour);
            dc.DrawPolygon(6, points);
        }
    }

    if(!IS_VERTICAL_TABS(style)) {
        // Draw bitmap
        if(tabInfo.m_bitmap.IsOk()) {
            dc.DrawBitmap(tabInfo.m_bitmap, tabInfo.m_bmpX + tabInfo.m_rect.GetX(), tabInfo.m_bmpY);
        }
        dc.DrawText(tabInfo.m_label, tabInfo.m_textX + tabInfo.m_rect.GetX(), tabInfo.m_textY);
        if(tabInfo.IsActive() && (style & kNotebook_CloseButtonOnActiveTab)) {
            DrawButton(dc, wxRect(tabInfo.m_bmpCloseX + tabInfo.m_rect.GetX(), tabInfo.m_bmpCloseY, CLOSE_BUTTON_SIZE,
                                  CLOSE_BUTTON_SIZE),
                       colours, eButtonState::kNormal);
        }
    }
}

void clTabRendererClassic::DrawBottomRect(clTabInfo::Ptr_t tabInfo, const wxRect& clientRect, wxDC& dc,
                                          const clTabColours& colors, size_t style)
{
    clTabColours colours;

    // Initialise the colours
    if(colors.IsDarkColours()) {
        InitDarkColours(colours);

    } else {
        InitLightColours(colours);
    }

    if(style & kNotebook_LeftTabs) {
        // Draw 3 lines on the right
        dc.SetPen(colours.activeTabPenColour);
        dc.SetBrush(colours.activeTabBgColour);
        wxPoint topLeft = clientRect.GetTopRight();
        wxSize rectSize(bottomAreaHeight + 2, clientRect.height);
        topLeft.x -= bottomAreaHeight;
        wxRect bottomRect(topLeft, rectSize);

        // We intentionally move the rect out of the client rect
        // so the top and bottom lines will be drawn out of screen
        bottomRect.y -= 1;
        bottomRect.height += 2;
        dc.DrawRectangle(bottomRect);

        // Draw a line under the active tab
        // that will erase the line drawn by the above rect
        wxPoint from, to;
        from = tabInfo->GetRect().GetTopRight();
        to = tabInfo->GetRect().GetBottomRight();
        from.x = bottomRect.GetTopLeft().x;
        to.x = bottomRect.GetTopLeft().x;
        from.y += 2;
        to.y -= 2;

        dc.SetPen(colours.activeTabBgColour);
        DRAW_LINE(from, to);
    } else if(style & kNotebook_RightTabs) {
        // Draw 3 lines on the right
        dc.SetPen(colours.activeTabPenColour);
        dc.SetBrush(colours.activeTabBgColour);
        wxPoint topLeft = clientRect.GetTopLeft();
        wxSize rectSize(bottomAreaHeight + 2, clientRect.height);
        wxRect bottomRect(topLeft, rectSize);

        // We intentionally move the rect out of the client rect
        // so the top and bottom lines will be drawn out of screen
        bottomRect.y -= 1;
        bottomRect.height += 2;
        dc.DrawRectangle(bottomRect);

        // Draw a line under the active tab
        // that will erase the line drawn by the above rect
        wxPoint from, to;
        from = tabInfo->GetRect().GetTopLeft();
        to = tabInfo->GetRect().GetBottomLeft();
        from.x = bottomRect.GetTopRight().x;
        to.x = bottomRect.GetTopRight().x;
        from.y += 2;
        to.y -= 2;

        dc.SetPen(colours.activeTabBgColour);
        DRAW_LINE(from, to);

    } else if(style & kNotebook_BottomTabs) {
        // Draw 3 lines at the top
        dc.SetPen(colours.activeTabPenColour);
        dc.SetBrush(colours.activeTabBgColour);
        wxPoint topLeft = clientRect.GetTopLeft();
        wxSize rectSize(clientRect.width, bottomAreaHeight);
        topLeft.y = 0;
        wxRect bottomRect(topLeft, rectSize);
        // We intentionally move the rect out of the client rect
        // so the left and right lines will be drawn out of screen
        bottomRect.x -= 1;
        bottomRect.width += 2;
        dc.DrawRectangle(bottomRect);

        // Draw a line under the active tab
        // that will erase the line drawn by the above rect
        wxPoint from, to;
        from = tabInfo->GetRect().GetTopLeft();
        to = tabInfo->GetRect().GetTopRight();
        from.y += bottomAreaHeight - 1;
        from.x += 2;
        to.y += bottomAreaHeight - 1;
        to.x -= 2;

        dc.SetPen(colours.activeTabBgColour);
        dc.DrawLine(from, to);
        DRAW_LINE(from, to);

    } else {
        // Draw 3 lines at the bottom
        dc.SetPen(colours.activeTabPenColour);
        dc.SetBrush(colours.activeTabBgColour);
        wxPoint topLeft = clientRect.GetBottomLeft();
        wxSize rectSize(clientRect.width, bottomAreaHeight);
        topLeft.y -= rectSize.GetHeight() - 1;
        wxRect bottomRect(topLeft, rectSize);
        // We intentionally move the rect out of the client rect
        // so the left and right lines will be drawn out of screen
        bottomRect.x -= 1;
        bottomRect.width += 2;
        dc.DrawRectangle(bottomRect);

        // Draw a line under the active tab
        // that will erase the line drawn by the above rect
        wxPoint from, to;
        from = tabInfo->GetRect().GetBottomLeft();
        to = tabInfo->GetRect().GetBottomRight();
        from.y -= bottomAreaHeight - 1;
        from.x += 2;
        to.y -= bottomAreaHeight - 1;
        to.x -= 2;

        dc.SetPen(colours.activeTabBgColour);
        dc.DrawLine(from, to);
        DRAW_LINE(from, to);
    }
}
