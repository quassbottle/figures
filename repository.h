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

    void showAll() {
        traverse([] (Figure* f) { f->show(); });
    }

    void hideAll() {
        traverse([] (Figure* f) { f->hide(); });
    }

    void clear() {
        while (!_stack.empty()) _stack.pop();
    }

private:
    stack<Figure*, vector<Figure*>> _stack;

    void traverse(void (*action)(Figure*)) {
        if (_stack.empty()) {
            return;
        }
        Figure* figure = _stack.top();

        action(figure);

        _stack.pop();
        traverse(action);
        _stack.push(figure);
    }
};