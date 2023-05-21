#include <windows.h>
#include <iostream>

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

    virtual void moveTo(int x, int y) {
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
             COLORREF border = RGB(255, 255, 255),
             COLORREF fill = RGB(12, 12, 12)) : Figure(x, y, border, fill), _size(size), _isUpsideDown(isUpsideDown) {
        setupPoints();
    }

    void draw() override {
        HPEN pen = CreatePen(PS_SOLID, 1, _border);
        HBRUSH brush = CreateSolidBrush(_fill);
        SelectObject(_hdc, pen);
        SelectObject(_hdc, brush);
        POINT points[] = {a, b, c};
        Polygon(_hdc, points, 3);
        DeleteObject(pen);
        DeleteObject(brush);
    }

    void erase() override {
        RECT* erase = new RECT;
        erase->top = _y;
        erase->left = _x;
        erase->right = _x + _size;
        erase->bottom = _y + _size;

        InvalidateRect(_hwnd, erase, true);

        delete erase;
    }

    void moveTo(int x, int y) override {
        setupPoints();
        Figure::moveTo(x, y);
    }

protected:
    int _size;
    bool _isUpsideDown;
    POINT a, b, c;

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

class CompositionFigure : public IFigure {
public:
    CompositionFigure(Figure* main, Figure* center) : _main(main), _center(center) {}

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
        _center->moveTo(x, y);
    }
private:
    Figure* _main;
    Figure* _center;
};