#include <iostream>
#include "repository.h"

int main() {
    SetConsoleTitle("22VP1_Presnyakov_V15");

    auto repo = FigureRepository();

    auto rect = new MyRectangle(50, 50, 50);
    repo.push(rect);

    auto rect1 = new MyRectangle(100, 100, 50);
    repo.push(rect1);

    while(true) repo.showAll();

    system("pause");
}
