// solutionwidget.h
#ifndef SOLUTIONWIDGET_H
#define SOLUTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include "vetorlayout.h"
#include "veCtorlayoutc.h"

class SolutionWidget : public QWidget {
    Q_OBJECT

public:
    SolutionWidget(QWidget *parent = nullptr) : QWidget(parent), solutionLayout(nullptr), stringLayout(nullptr) {
        setupUi();
    }

    QVector<double> getNumericVector() {
        return solutionLayout ? solutionLayout->getVector() : QVector<double>();
    }

    QVector<QString> getStringVector() {
        return stringLayout ? stringLayout->getVector() : QVector<QString>();
    }

    void setSolution(QVector<QString> var, QVector<double> solution) {
        if (solutionLayout) {
            solutionLayout->setVector(solution);
        }
        if (stringLayout) {
            stringLayout->setVector(var);
        }
    }

private:
    VectorLayout *solutionLayout;
    VetorLayoutString *stringLayout;

    void setupUi() {
        QHBoxLayout *mainLayout = new QHBoxLayout(this);

        // String Vector Layout
        stringLayout = new VetorLayoutString(this,3, "variaveis");
        mainLayout->addWidget(stringLayout);

        // Numeric Vector Layout
        solutionLayout = new VectorLayout(this,3, "valor");
        mainLayout->addWidget(solutionLayout);

        setLayout(mainLayout);
    }
};

#endif // SOLUTIONWIDGET_H
