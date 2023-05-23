#include <windows.h>
#include <iostream>

const COLORREF BG = RGB(12, 12, 12);
const COLORREF FG = RGB(255, 255, 255);

using namespace std;

class FigureException : std::exception {
public:
    string message;

    FigureException(string message) : message(message) {}
};

class IDrawable {
public:
    virtual void draw() = 0;
    virtual void erase() = 0;
};

class IColored {
public:
    virtual COLORREF& getBorderColor() = 0;
    virtual COLORREF& getFillColor() = 0;
};

class IFigure {
public:
    virtual void moveTo(int x, int y) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
};

class Figure : public IDrawable, public IColored, public IFigure {
public:
    Figure(int x, int y, COLORREF border, COLORREF fill) : _x(x), _y(y), _border(border), _fill(fill) {
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

    virtual void moveTo(int x, int y) {/*
        int windowWidth = _rect.right - _rect.left;
        int windowHeight = _rect.bottom - _rect.top;
        if (x > windowWidth|| x < 0 || y > windowHeight || y < 0)
            throw FigureException("Figure is out of border");*/
        erase();
        _x = x, _y = y;
        draw();
    }

    virtual void show() {
        draw();
    }

    virtual void hide() {
        erase();
    }

    COLORREF& getBorderColor() {
        return _border;
    }

    COLORREF& getFillColor() {
        return _fill;
    }

protected:
    int _x, _y;
    HWND _hwnd;
    HDC _hdc;
    RECT _rect;
    COLORREF _border;
    COLORREF _fill;
};

class Triangle : public Figure {
public:
    Triangle(int x, int y, int size, bool isUpsideDown = false,
             COLORREF border = FG,
             COLORREF fill = BG) : Figure(x, y, border, fill), _size(size), _isUpsideDown(isUpsideDown) {
        setupPoints();
    }

    void draw() override {
        drawPoints(a, b, c, _fill, _border);
    }

    void erase() override {
        /*RECT* erase = new RECT;
        erase->top = _y;
        erase->left = _x;
        erase->right = _x + _size;
        erase->bottom = _y + _size;

        InvalidateRect(_hwnd, erase, false);*/

        drawPoints(a, b, c, BG, BG);
    }

    void moveTo(int x, int y) override {
        int windowWidth = _rect.right - _rect.left;
        int windowHeight = _rect.bottom - _rect.top;
        if (x > windowWidth || x < 0 || y > windowHeight || y < 0)
            throw FigureException("Figure is out of border");
        setupPoints();
        Figure::moveTo(x, y);
    }

    int getSize() {
        return _size;
    }

protected:
    int _size;
    bool _isUpsideDown;
    POINT a, b, c;

    void drawPoints(POINT a, POINT b, POINT c, COLORREF bg, COLORREF fg) {
        HPEN pen = CreatePen(PS_SOLID, 2, fg);
        HBRUSH brush = CreateSolidBrush(bg);
        SelectObject(_hdc, brush);
        SelectObject(_hdc, pen);
        POINT points[] = {a, b, c};
        Polygon(_hdc, points, 3);
        DeleteObject(pen);
        DeleteObject(brush);
    }

    void setupPoints() {
        if (_isUpsideDown) {
            a = {_x, _y};
            b = {_x + _size, _y};
            c = {_x + _size / 2, _y + _size};
        }
        else {
            a = {_x + _size / 2, _y};
            b = {_x, _y + _size };
            c = {_x + _size, _y + _size};
        }
    }
};

class Serpinsky : public IFigure {
public:
    Serpinsky(Triangle* main, Triangle* center) : _main(main), _center(center) {}

    void show() {
        _main->draw();
        _center->draw();
    }

    void hide() {
        _main->erase();
        _center->erase();
    }

    void moveTo(int x, int y) {
        _main->moveTo(x, y);
        _center->moveTo(x + (_main->getSize() / 4), y + (_main->getSize() / 2));
    }

private:
    Triangle* _main;
    Triangle* _center;
};