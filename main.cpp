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

    auto extra = new Triangle(x + 150, y, size * 2, false, RGB(255, 0, 0), RGB(128, 0, 0));
    auto complex = new Serpinsky(main, center);

    repo.push(complex);
    repo.push(extra);

    for(int i = 0; i < 1000; i++) {
        try {
            repo.showAll();
        }
        catch (FigureException& ex) {
            system("cls");
            cout << ex.message;
        }
    }

    Sleep(1000);
    repo.hideAll();

    while (true);

    system("pause");
}
