/*!Copyright (c) 2017 Cheng Ligang . All rights reserved.
*
* \class Window
*
* \brief A class of Window for MS Windows
*
* \author: Cheng Ligang
* \mail:   chengligang@buaa.edu.cn
* \date:   2018/1/29
*/
#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#include <windows.h>
#include "Controller.h"

namespace glWindow {
    class Window
    {
    public:
        Window(HINSTANCE hInst, const wchar_t * name, HWND hParent, Controller * ctrl);
        ~Window();

        void printSelf() const;
        HWND create();
        void show(int cmdShow = SW_SHOWDEFAULT);
        HWND getHandle()                            { return handle; };

        //setters for WNDCLASSEX
        void setClassStyle(UINT style)              { winClass.style = style; };
        void setIcon(int id)                        { winClass.hIcon = loadIcon(id); };
        void setIconSmall(int id)                   { winClass.hIconSm = loadIcon(id); }; 
        void setCursor(int id)                      { winClass.hCursor = loadCursor(id); };
        void setBackground(int color)               { winClass.hbrBackground = (HBRUSH)::GetStockObject(color); };
        void setMenuName(LPCTSTR name)              { winClass.lpszClassName = name; };

        void setWindowStyle( DWORD style )          { winStyle = style; };
        void setWindowStyleEx(DWORD style)          { winStyleEx = style; };
        void setPosition(int x, int y)              { this->x = x; this->y = y; };
        void setWidth(int x)                        { width = x; };
        void setHeight(int y)                       { height = y; };
        void setParent(HWND handle)                 { parentHandle = handle; };
        void setMenu(HMENU handle)                  { menuHandle = handle; };
    private:
        enum { MAX_STRING = 256 };

        void registerClass();
        HICON loadIcon(int id);
        HCURSOR loadCursor(int id);

        HWND handle;
        WNDCLASSEX winClass;
        DWORD winStyle;
        DWORD winStyleEx;
        wchar_t title[MAX_STRING];
        wchar_t className[MAX_STRING];
        int x;
        int y;
        int width;
        int height;
        HWND parentHandle;
        HMENU menuHandle;
        HINSTANCE instance;
        glWindow::Controller * controller;

    };
}
#endif // !WIN_WINDOW_H
