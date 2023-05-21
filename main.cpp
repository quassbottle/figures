#include <iostream>
#include "repository.h"



int main() {
    SetConsoleTitle("22VP1_Presnyakov_V15");

    auto repo = FigureRepository();

    int x = 150;
    int y = 100;
    int size = 100;

    auto main = new Triangle(x, y, size);
    auto center = new Triangle(x + (size / 4), y + (size / 2), size / 2, true);

    auto compose = new CompositionFigure(main, center);

    //repo.push(center);
    //repo.push(compose);

    float delta = 0;
    while(true) {
        compose->show();
        compose->moveTo(x + (int)delta, y + (int)delta);
        //delta+= 0.01;
    }

    system("pause");
}
