// containerlayout.h
#ifndef CONTAINERLAYOUT_H
#define CONTAINERLAYOUT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include "matrizlayout.h"
#include "vetorlayout.h"
#include "veCtorlayoutc.h"
#include "sizecontrolwidget.h"
#include "solverinterface.h"
class ContainerLayout : public QWidget {
    Q_OBJECT

public:
    explicit ContainerLayout(QWidget *parent = nullptr) : QWidget(parent) {
        setupUi();
    }

private slots:
    void adjustSizes(int rows, int columns) {
        matrizLayout->setMatrixSize(rows, columns);
        vetorLayout->resizeVector(rows);
        vetorLayoutString->resizeVector(rows);
    }

    void handleOKButtonClicked() {
        // Obtém os dados das três entradas
        QVector<QVector<double>> matriz = matrizLayout->getMatrix();
        QVector<QString> var = vetorLayoutString->getVector();
        QVector<double> vetor = vetorLayout->getVector();

        // Cria uma instância da SolverInterface que deve fazer todo o resto
        SolverInterface solverInterface(matriz, var, vetor);
    }

private:
    QVBoxLayout *mainLayout;
    QFrame *outerFrame;
    QFrame *mainFrame;
    MatrizLayout *matrizLayout;
    VectorLayout *vetorLayout;
    VetorLayoutString *vetorLayoutString;
    SizeControlWidget *sizeControlWidget;
    QPushButton *okButton;

    void setupUi() {
        outerFrame = new QFrame(this);
        outerFrame->setFrameShape(QFrame::Box);
        outerFrame->setLineWidth(2);

        mainLayout = new QVBoxLayout(outerFrame);

        sizeControlWidget = new SizeControlWidget(this, 3, 3);
        connect(sizeControlWidget, &SizeControlWidget::sizeChanged, this, &ContainerLayout::adjustSizes);

        mainFrame = new QFrame(outerFrame);
        mainFrame->setFrameShape(QFrame::Box);
        mainFrame->setLineWidth(2);
        mainFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        QHBoxLayout *innerLayout = new QHBoxLayout(mainFrame);

        matrizLayout = new MatrizLayout(mainFrame, 3, 3, "cof");
        vetorLayoutString = new VetorLayoutString(mainFrame, 3, "Var");
        vetorLayout = new VectorLayout(mainFrame, 3, "igual");

        innerLayout->addWidget(matrizLayout);

        QLabel *multiplicationLabel = new QLabel("X", mainFrame);
        multiplicationLabel->setAlignment(Qt::AlignCenter);
        innerLayout->addWidget(multiplicationLabel);

        innerLayout->addWidget(vetorLayoutString);

        QLabel *equalsLabel = new QLabel("=", mainFrame);
        equalsLabel->setAlignment(Qt::AlignCenter);
        innerLayout->addWidget(equalsLabel);

        innerLayout->addWidget(vetorLayout);

        mainLayout->addWidget(sizeControlWidget);
        mainLayout->addWidget(mainFrame);

        okButton = new QPushButton("OK", outerFrame);
        okButton->setFixedSize(50, 30);
        okButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border: none; border-radius: 5px; }"
                                "QPushButton:hover { background-color: #45a049; }");
        okButton->setCursor(Qt::PointingHandCursor);

        // Conecta o clique do botão à função handleOKButtonClicked
        connect(okButton, &QPushButton::clicked, this, &ContainerLayout::handleOKButtonClicked);

        setLayout(new QVBoxLayout(this));
        layout()->addWidget(outerFrame);

        mainLayout->addWidget(okButton, 0, Qt::AlignBottom | Qt::AlignRight);
    }
};

#endif // CONTAINERLAYOUT_H
