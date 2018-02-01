/*!Copyright (c) 2017 Cheng Ligang . All rights reserved.
 *
 * \class Controller
 *
 * \brief This class is a bridge between window procedure and the application;
 *
 * \author: Cheng Ligang
 * \mail:   chengligang@buaa.edu.cn
 * \date:   2018/1/30
 */
#ifndef WIN_CONTROLLER_H
#define WIN_CONTROLLER_H
#include <windows.h>

namespace glWindow {
    class Controller
    {
    public:
        Controller();
        ~Controller();

        void setHandle(HWND handle);
        virtual int close();
        virtual int command(int id, int cmd, LPARAM msg);
        virtual int contextMenu(HWND handle, int x, int y);
        virtual int create();
        virtual int destroy();
        virtual int dpiChanged(int x, int y, RECT * rect);
        virtual int enable(bool flag);
        virtual int eraseBkgnd(HDC hdc);
        virtual int hScroll(WPARAM wParam, LPARAM lParam);
        virtual int keyDown(int key, LPARAM lParam);
        virtual int keyUp(int key, LPARAM lParam);
        virtual int lButtonDown(WPARAM state, int x, int y);
        virtual int lButtonUp(WPARAM state, int x, int y);
        virtual int mButtonDown(WPARAM state, int x, int y);
        virtual int mButtonUp(WPARAM state, int x, int y);
        virtual int mouseMove(int ketState, int x, int y);
        virtual int mouseHover(int state, int x, int y);
        virtual int mouseLeave();
        virtual int mouseWheel(int  state, int delta, int x, int y);
        virtual int notify(int id, LPARAM lParam);
        virtual int paint();
        virtual int rButtonDown(WPARAM wParam, int x, int y);
        virtual int rButtonUp(WPARAM wParam, int x, int y);
        virtual int size(int w, int h, WPARAM wParam);
        virtual int timer(WPARAM id, LPARAM lParam);
        virtual int vScroll(WPARAM wParam, LPARAM lParam);
    protected:
        HWND handle;
    private:


    };
    inline void Controller::setHandle(HWND hwnd) { handle = hwnd; }
    inline int Controller::close() { ::DestroyWindow(handle); return 0; }
    inline int Controller::command(int id, int cmd, LPARAM msg) { return 0; }
    inline int Controller::contextMenu(HWND handle, int x, int y) { return 0; }
    inline int Controller::create() { return 0; }
    inline int Controller::destroy() { return 0; }
    inline int Controller::dpiChanged(int x, int y, RECT* rect) { return 0; }
    inline int Controller::enable(bool flag) { return 0; }
    inline int Controller::eraseBkgnd(HDC hdc) { return 0; }
    inline int Controller::hScroll(WPARAM wParam, LPARAM lParam) { return 0; }
    inline int Controller::keyDown(int key, LPARAM lParam) { return 0; }
    inline int Controller::keyUp(int key, LPARAM lParam) { return 0; }
    inline int Controller::lButtonDown(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::lButtonUp(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::mButtonDown(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::mButtonUp(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::mouseHover(int state, int x, int y) { return 0; }
    inline int Controller::mouseLeave() { return 0; }
    inline int Controller::mouseMove(int keyState, int x, int y) { return 0; }
    inline int Controller::mouseWheel(int state, int delta, int x, int y) { return 0; }
    inline int Controller::notify(int id, LPARAM lParam) { return 0; }
    inline int Controller::paint() { return 0; }
    inline int Controller::rButtonDown(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::rButtonUp(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::size(int w, int h, WPARAM type) { return 0; }
    inline int Controller::timer(WPARAM id, LPARAM lParam) { return 0; }
    inline int Controller::vScroll(WPARAM wParam, LPARAM lParam) { return 0; }
}

#endif

