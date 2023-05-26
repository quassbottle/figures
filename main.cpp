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
        auto main = new Triangle(x, y, size);
        auto center = new Triangle(x + (size / 4), y + (size / 2), size / 2, true);

        auto extra = new Triangle(x + 150, y, size * 2, false, RGB(255, 0, 0), RGB(128, 0, 0));
        auto complex = new Serpinsky(main, center);

        repo.push(complex);
        repo.push(extra);

        for (int i = 0; i < 100; i++) {
            repo.showAll();
        }

        Sleep(1000);
        for (int i = 0; i < 100; i++) {
            extra->moveTo(x + 200, y + 50);
        }

        Sleep(1000);
        for (int i = 0; i < 100; i++) {
            repo.hideAll();
        }

        while (true);
    } catch (FigureException& ex) {
        cout << ex.message;
    }
}
