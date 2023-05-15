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
        traverse([] (Figure*& f) { f->show(); });
    }

    void hideAll() {
        traverse([] (Figure*& f) { f->hide(); });
    }

    void destroy() {
        while (!_stack.empty()) _stack.pop();
    }

private:
    stack<Figure*, vector<Figure*>> _stack;

    void traverse(void (*action)(Figure*&)) {
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