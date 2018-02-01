#ifndef WIN_PROCEDURE_H
#define WIN_PROCEDURE_H
#include <windows.h>

namespace glWindow{
    LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    INT_PTR CALLBACK dialogProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}



#endif // WIN_PROCEDURE_H

