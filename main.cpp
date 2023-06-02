#include <iostream>
#include "repository.h"

/*
 Вариант 15. Стек как динамический массив. Базовый абстрактный класс. Агрегация.
 */

int main() {
    SetConsoleTitle("22VP1_Presnyakov_V15");

    auto repo = FigureRepository();

    int x = 150;
    int y = 100;
    int size = 100;
    try {
        auto main = new Triangle(x, y, size, false);
        auto center = new Triangle(x, y + size, size / 2, true);
        auto extra = new Triangle(x + 300, y, size * 2, false, RGB(255, 0, 0), RGB(128, 0, 0));

        auto complex = new Serpinsky(main, center);

        //repo.push(center);
        //repo.push(main);
        repo.push(complex);
        repo.push(extra);

        for (int i = 0; i < 1000; i++) {
            repo.showAll();
        }

        Sleep(1000);

        for (int i = 0; i < 1000; i++) {
            extra->hide();
        }

        Sleep(1000);

        for (int i = 0; i < 1000; i++) {
            extra->moveTo(x + 500, y + 50);
        }
    } catch (Figure::FigureException& ex) {
        cout << ex.message;
    }

    while (true);
}
