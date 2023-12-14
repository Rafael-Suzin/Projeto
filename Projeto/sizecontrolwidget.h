// sizecontrolwidget.h
#ifndef SIZECONTROLWIDGET_H
#define SIZECONTROLWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QFrame>

class SizeControlWidget : public QWidget {
    Q_OBJECT

public:
    explicit SizeControlWidget( QWidget *parent = nullptr,int initialRows = 3, int initialColumns = 3)
        : QWidget(parent), initialRows(initialRows), initialColumns(initialColumns) {
        setupUi();
    }

signals:
    void sizeChanged(int rows, int columns);

private slots:
    void updateSize() {
        int rows = lineEditL->text().toInt();
        int columns = lineEditC->text().toInt();

        emit sizeChanged(rows, columns);
    }

private:
    QVBoxLayout *mainLayout;
    QFrame *mainFrame;  // Adicionado mainFrame
    QHBoxLayout *frameLayout;  // Alterado para QHBoxLayout
    QFrame *frameL;
    QVBoxLayout *layoutL;
    QLabel *labelL;
    QLineEdit *lineEditL;
    QVBoxLayout *layoutX;
    QLabel *labelX;
    QFrame *frameC;
    QVBoxLayout *layoutC;
    QLabel *labelC;
    QLineEdit *lineEditC;

    int initialRows;
    int initialColumns;

    void setupUi() {
        mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(0);
        mainFrame = new QFrame(this);
        mainFrame->setFrameShape(QFrame::Box);
        mainFrame->setMinimumSize(10, 10);  // Tamanho mínimo
        mainFrame->setFixedSize(200, 100);  // Tamanho fixo

        frameLayout = new QHBoxLayout(mainFrame);

        frameL = new QFrame(mainFrame);
        frameL->setFrameShape(QFrame::Box);

        layoutL = new QVBoxLayout(frameL);
        layoutL->setSpacing(0);
        labelL = new QLabel("Linhas:", frameL);
        lineEditL = new QLineEdit(QString::number(initialRows), frameL);
        lineEditL->setValidator(new QIntValidator(0, 100, this));
        lineEditL->setFixedWidth(50);  // Tamanho fixo
        connect(lineEditL, &QLineEdit::textChanged, this, &SizeControlWidget::updateSize);

        labelX = new QLabel("X", this);
        layoutX = new QVBoxLayout();  // Removido QVBoxLayout para QLabel "X" do frameL
        layoutX->addWidget(labelX);

        frameC = new QFrame(mainFrame);
        frameC->setFrameShape(QFrame::Box);
        layoutC = new QVBoxLayout(frameC);
        layoutC->setSpacing(0);
        labelC = new QLabel("Colunas:", frameC);
        lineEditC = new QLineEdit(QString::number(initialColumns), frameC);
        lineEditC->setValidator(new QIntValidator(0, 100, this));
        lineEditC->setFixedWidth(50);  // Tamanho fixo
        connect(lineEditC, &QLineEdit::textChanged, this, &SizeControlWidget::updateSize);

        layoutL->addWidget(labelL);
        layoutL->addWidget(lineEditL);
        layoutC->addWidget(labelC);
        layoutC->addWidget(lineEditC);

        frameLayout->addWidget(frameL);
        frameLayout->addLayout(layoutX);  // Adicionado QLabel "X" diretamente ao frameLayout
        frameLayout->addWidget(frameC);

        mainLayout->addWidget(mainFrame);
    }
};

#endif // SIZECONTROLWIDGET_H
