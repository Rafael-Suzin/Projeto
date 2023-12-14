#include <QApplication>
#include "containerlayout.h"
//#include "solutionwidget.h"

//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    ContainerLayout container;
//    container.show();

//    ContainerLayout container;
//    container.show();
//    return a.exec();
//}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Criação de um ContainerLayout para simular a interface gráfica

    ContainerLayout containerLayout;
    containerLayout.show();


//    // Criação de um SolutionWidget para simular a exibição da solução
//    SolutionWidget solutionWidget;
//    QVector<double> numericSolution = {1, 56, 1};
//    QVector<QString> stringSolution = {"x", "y", "z"};
//    solutionWidget.setSolution(stringSolution,numericSolution);

//    solutionWidget.show();

    return a.exec();
}
