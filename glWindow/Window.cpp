/*!Copyright (c) 2017 Cheng Ligang . All rights reserved.
 *
 * \class Window
 *
 * \brief this file is implement of Window class. 
 *
 * \author: Cheng Ligang
 * \mail:   chengligang@buaa.edu.cn
 * \date:   2018/1/30
 */
#include <sstream>
#include <iostream>
#include <cstring>

#include "Window.h"
#include "procedure.h"
using std::wstringstream;
using namespace glWindow;

Window::Window(HINSTANCE hInst, const wchar_t * name, HWND hParent, Controller * ctrl)
{
    wcsncpy(this->title, name, MAX_STRING-1);
    wcsncpy(this->className, name, MAX_STRING-1);

    winClass.cbSize                 = sizeof(WNDCLASSEX);
    winClass.style                  = 0 ;
    winClass.lpfnWndProc            = glWindow::windowProcedure;
    winClass.cbClsExtra             = 0 ;
    winClass.cbWndExtra             = 0 ;
    winClass.hInstance              = instance;
    winClass.hIcon                  = LoadIcon(instance, IDI_APPLICATION);
    winClass.hCursor                = LoadCursor(0, IDC_ARROW);
    winClass.hIconSm                = 0;
    winClass.hbrBackground          = (HBRUSH)GetStockObject(WHITE_BRUSH);
    winClass.lpszClassName          = className;
    winClass.hIconSm                = LoadIcon(instance, IDI_APPLICATION);

}

Window::~Window()
{
    ::UnregisterClass(className, instance);
}


HWND Window::create()
{
    if(!::RegisterClassEx(&winClass)) return 0;

    handle = ::CreateWindowEx(  winStyleEx, 
                                className,
                                title,
                                winStyle, 
                                x, 
                                y, 
                                width,
                                height,
                                parentHandle, 
                                menuHandle,
                                instance,
                                (LPVOID)controller);
    return handle;

}
void Window::show(int cmdShow)
{
    ::ShowWindow(handle, cmdShow);
    ::UpdateWindow(handle);
}

HICON Window::loadIcon(int id)
{
    return (HICON)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
}

HICON Window::loadCursor(int id)
{
    return (HCURSOR)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
}


