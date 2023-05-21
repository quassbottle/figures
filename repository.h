#include <stack>
#include <vector>
#include "figure.h"

class FigureRepository {
public:
    FigureRepository() {
        _stack = stack<IFigure*, vector<IFigure*>>();
    }

    void push(IFigure* figure) {
        _stack.push(figure);
    }

    void pop() {
        _stack.pop();
    }

    void showAll() {
        traverse([] (IFigure*& f) { f->show(); });
    }

    void hideAll() {
        traverse([] (IFigure*& f) { f->hide(); });
    }

    void destroy() {
        while (!_stack.empty()) _stack.pop();
    }

private:
    stack<IFigure*, vector<IFigure*>> _stack;

    void traverse(void (*action)(IFigure*&)) {
        if (_stack.empty()) {
            return;
        }
        IFigure* figure = _stack.top();

        action(figure);

        _stack.pop();
        showAll();
        _stack.push(figure);
    }
};