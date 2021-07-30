#include "CalculatingPiByMonteKarloMethod.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CalculatingPiByMonteKarloMethod window;

    window.show();

    //Параметры:
    //1-й: вещественное число. R круга (размер окна анимации будет увеличен на 20 пикселей во все стороны)
    //2-й: unsigned long long: результирующее кол-во точек
    //3-й: unsigned int: длительность анимации в мс
    window.startAnimation(100.0, 100000, 15000);

    return app.exec();
}
