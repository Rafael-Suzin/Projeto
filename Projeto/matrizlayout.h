// matrizlayout.h
#ifndef MATRIZLAYOUT_H
#define MATRIZLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QVector>
#include <QDebug>
#include <QFrame>
#include <QLabel>

class MatrizLayout : public QWidget {
    Q_OBJECT

public:
    MatrizLayout(QWidget *parent = nullptr,int L=3, int C=3,QString title = "",int entryWidth=20,int entryHeight=20) : QWidget(parent) {
        createMatrixLayout(L, C, title,entryWidth,entryHeight);
    }

    QVector<QVector<double>> getMatrix() {
        return matrix;
    }
    int getLinha() {
        return matrix.size();
    }
    int getColuna() {
        return matrix[0].size();
    }
    void printMatrix() {
        qDebug() << "Matriz Atual:";
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                qDebug() << matrix[i][j];
            }
            qDebug() << "-----";
        }
    }

    void setMatrixSize(int L, int C) {
        resizeMatrix(L, C,entryWidth,entryHeight);
        updateMatrixLayout(L, C);
    }
    void setFrameFixedSize(int width, int height) {
        frame->setFixedSize(width, height);
        frameLayout->setSizeConstraint(QLayout::SetFixedSize);  // Impede o ajuste automático do layout interno
    }

private slots:
    void valueChanged() {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                matrix[i][j] = inputWidgets[i][j]->text().toDouble();
            }
        }
        printMatrix();
    }

private:
    QGridLayout *gridLayout;
    QVector<QVector<double>> matrix;
    QVector<QVector<QLineEdit*>> inputWidgets;

    QFrame *frame;
    QLabel *titleLabel;
    int entryWidth;
    int entryHeight;

    QVBoxLayout *frameLayout;

    void createMatrixLayout(int L, int C, QString title, int entryWidth, int entryHeight) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        frame = new QFrame(this);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);

        // Crie um novo QVBoxLayout dentro do frame
        frameLayout = new QVBoxLayout(frame);

        if (!title.isEmpty()) {
            titleLabel = new QLabel(title, frame);
            titleLabel->setAlignment(Qt::AlignCenter);
            frameLayout->addWidget(titleLabel);
        }

        gridLayout = new QGridLayout();
        frameLayout->addLayout(gridLayout);  // Adicione o QGridLayout ao QVBoxLayout interno do frame
        setFrameFixedSize(100, 200);   // tamanho fixo
        frame->setLayout(frameLayout);
        mainLayout->addWidget(frame);


        resizeMatrix(L, C, entryWidth, entryHeight);
        updateMatrixLayout(L, C);

        setLayout(mainLayout);
    }


    void resizeMatrix(int L, int C, int entryWidth_=20, int entryHeight_=20) {
        matrix.resize(L);
        for (int i = 0; i < L; ++i) {
            matrix[i].resize(C);
        }
        entryWidth = entryWidth_;
        entryHeight = entryHeight_;
    }

    void updateMatrixLayout(int L, int C) {
        // Clear the existing layout
        QLayoutItem* item;
        while ((item = gridLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        // Create a new layout with the updated size
        inputWidgets.clear();
        for (int i = 0; i < L; ++i) {
            QVector<QLineEdit*> rowInputs;
            for (int j = 0; j < C; ++j) {
                QLineEdit *lineEdit = new QLineEdit(frame);
                lineEdit->setText(QString::number(matrix[i][j]));
                lineEdit->setFixedSize(entryWidth, entryHeight);
                connect(lineEdit, &QLineEdit::textChanged, this, &MatrizLayout::valueChanged);
                gridLayout->addWidget(lineEdit, i, j);
                rowInputs.push_back(lineEdit);
            }
            inputWidgets.push_back(rowInputs);
        }
    }
};

#endif // MATRIZLAYOUT_H
