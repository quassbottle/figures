#include <stack>
#include <vector>
#include "figure.h"

class FigureRepository {
public:
    FigureRepository() {
        _stack = stack<Figure*, vector<Figure*>>();
    }

    void push(Figure* figure) {
        _stack.push(figure);
    }

    void pop() {
        _stack.pop();
    }

    void showAll() {
        if (_stack.empty()) {
            return;
        }
        Figure* x = _stack.top();

        x->show();

        _stack.pop();
        showAll();
        _stack.push(x);
    }

    void hideAll() {
        if (_stack.empty()) {
            return;
        }
        Figure* x = _stack.top();

        x->hide();

        _stack.pop();
        showAll();
        _stack.push(x);
    }

private:
    stack<Figure*, vector<Figure*>> _stack;

    void traverse(void (*action)(Figure* f)) {
        if (_stack.empty()) {
            return;
        }
        Figure* x = _stack.top();

        action(x);

        _stack.pop();
        showAll();
        _stack.push(x);
    }
};