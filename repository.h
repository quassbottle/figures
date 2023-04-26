#include <stack>
#include "figure.h"

class FigureRepository {
public:
    FigureRepository() {
        _stack = stack<Figure, Figure*>();
    }

    void add(Figure figure) {

    }

    void remove(Figure figure) {

    }

    void showAll() {

    }

private:
    void* _stack;
};