#include <windows.h>
#include <iostream>

using namespace std;

class Figure {
public:
    Figure(int x, int y) : _x(x), _y(y) {
        _hwnd = nullptr;

        if ((_hwnd = GetConsoleWindow()) == nullptr) {
            throw FigureException("Console window not found");
        }
        if ((_hdc = GetDC(_hwnd)) == nullptr) {
            throw FigureException("Context not found");
        }

        GetWindowRect(_hwnd, &_rect);
    }
    ~Figure() {
        ReleaseDC(_hwnd, _hdc);
    }

    virtual void show() = 0;
    virtual void hide() = 0;

    void moveTo(int x, int y) {
        hide();
        _x = x, _y = y;
        show();
    }

protected:
    int _x, _y;
    HWND _hwnd;
    HDC _hdc;
    RECT _rect;

    class FigureException {
    public:
        string message;

        FigureException(string message) : message(message) {}
    };
};

class MyRectangle : public Figure {
public:
    MyRectangle(int x, int y, int size) : Figure(x, y), _size(size) {}

    void show() override {
        HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(_hdc, pen);
        Rectangle(_hdc, 0, 0, 50, 50);
        //DeleteObject(pen);
    }

    void hide() override {

    }

protected:
    int _size;
};