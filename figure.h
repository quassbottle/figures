#include <windows.h>
#include <iostream>

using namespace std;

class Figure {
public:
    class FigureException {
    public:
        string message;

        FigureException(string message) : message(message) {}
    };

    Figure(int x, int y) : _x(x), _y(y) {
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

};

class MyRectangle : public Figure {
public:
    MyRectangle(int x, int y, int size) : Figure(x, y), _size(size) {}

    void show() override {
        HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        SelectObject(_hdc, pen);
        Rectangle(_hdc, _x, _y, _x + _size, _y + _size);
        DeleteObject(pen);
    }

    void hide() override {

    }

protected:
    int _size;
};

class Triangle : Figure {
public:
    Triangle(int x, int y, int size, bool upsideDown = false) : Figure(x, y), _size(size) {
        if (upsideDown) {
            a = {x, y};
            b = {x + size, y};
            c = {x + size / 2, y + size};
        }
        else {
            a = {x + size / 2, y};
            b = {x, y + size };
            c = {x + size, y + size};
        }
    }

    void show() override {

    }

    void hide() override {

    }

    POINT getA() {
        return a;
    }

    POINT getB() {
        return b;
    }

    POINT getC() {
        return c;
    }

protected:
    int _size;

    POINT a, b, c;
};

class Serpinsky : Figure {
    Serpinsky(int x, int y, int size) : Figure(x, y), _size(size) {
        mainTriangle = new Triangle(x, y, size);

    }

    void show() override {

    }

    void hide() override {

    }
protected:
    Triangle* centerTriangle;
    Triangle* mainTriangle;

    int _size;
};
