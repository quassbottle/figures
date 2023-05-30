#include <windows.h>
#include <iostream>

const COLORREF BG = RGB(12, 12, 12);
const COLORREF FG = RGB(255, 255, 255);

using namespace std;

class Figure {
public:
    class FigureException : std::exception {
    public:
        string message;

        FigureException(string message) : message(message) {}
    };

    Figure(int x, int y, COLORREF border, COLORREF fill) : _x(x), _y(y), _border(border), _fill(fill) {
        if ((_hwnd = GetConsoleWindow()) == nullptr) {
            throw FigureException("Console window not found");
        }
        if ((_hdc = GetDC(_hwnd)) == nullptr) {
            throw FigureException("Context not found");
        }

        GetWindowRect(_hwnd, &_rect);

        drawException(x, y);
    }

    Figure() {
        _x = 0;
        _y = 0;
        _border = FG;
        _fill = BG;

        if ((_hwnd = GetConsoleWindow()) == nullptr) {
            throw FigureException("Console window not found");
        }
        if ((_hdc = GetDC(_hwnd)) == nullptr) {
            throw FigureException("Context not found");
        }

        GetWindowRect(_hwnd, &_rect);

        drawException(_x, _y);
    }

    virtual void show() = 0;
    virtual void hide() = 0;

    ~Figure() {
        ReleaseDC(_hwnd, _hdc);
    }

    virtual void moveTo(int x, int y) {
        drawException(x, y);
        hide();
        _x = x, _y = y;
        show();
    }

    int getX() {
        return _x;
    }

    int getY() {
        return _y;
    }

protected:
    int _x, _y;
    HWND _hwnd;
    HDC _hdc;
    RECT _rect;
    COLORREF _border;
    COLORREF _fill;

    void drawException(int x, int y) {
        int windowWidth = _rect.right - _rect.left;
        int windowHeight = _rect.bottom - _rect.top;
        if (x > windowWidth|| x < 0 || y > windowHeight || y < 0)
            throw FigureException("Figure is out of border");
    }
};

class Triangle : public Figure {
public:
    Triangle(int x, int y, int size, bool isUpsideDown = false,
             COLORREF border = FG,
             COLORREF fill = BG) : Figure(x, y, border, fill), _size(size), _isUpsideDown(isUpsideDown) {
        setupPoints(x, y);
    }

    Triangle() {
        _x = 0;
        _y = 0;
        _size = 100;
        _isUpsideDown = false;

        setupPoints(_x, _y);
    }

    void show() override {
        drawPoints(_a, _b, _c, _fill, _border);
    }

    void hide() override {
        drawPoints(_a, _b, _c, BG, BG);
    }

    void moveTo(int x, int y) override {
        drawException(x, y);
        setupPoints(x, y);
        Figure::moveTo(x, y);
    }

    int getSize() {
        return _size;
    }

    bool isUpsideDown() {
        return _isUpsideDown;
    }

protected:
    int _size;
    bool _isUpsideDown;
    POINT _a, _b, _c;

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

    void setupPoints(int x, int y) {
        if (_isUpsideDown) {
            _a = {x, y};
            _b = {x + _size, y};
            _c = {x + _size / 2, y + _size};
        }
        else {
            _a = {x + _size / 2, y};
            _b = {x, y + _size };
            _c = {x + _size, y + _size};
        }
    }
};

class Serpinsky : public Figure {
public:
    Serpinsky(Triangle* main, Triangle* center) : _main(main), _center(center) {
        if (center->getX() != main->getX() + (main->getSize() / 4) ||
            center->getY() != main->getY() + (main->getSize() / 2) ||
            main->getSize() == center->getSize() / 2 ||
            !center->isUpsideDown()) {
            throw Figure::FigureException("Wrong center triangle");
        }
    }

    void show() {
        _main->show();
        _center->show();
    }

    void hide() {
        _main->hide();
        _center->hide();
    }

    void moveTo(int x, int y) {
        _main->moveTo(x, y);
        _center->moveTo(x + (_main->getSize() / 4), y + (_main->getSize() / 2));
    }

private:
    Triangle* _main;
    Triangle* _center;
};
