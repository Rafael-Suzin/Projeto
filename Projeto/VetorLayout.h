#ifndef VECTORLAYOUT_H
#define VECTORLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QVector>
#include <QDebug>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>

class VectorLayout : public QWidget {
    Q_OBJECT

public:
    VectorLayout(QWidget *parent = nullptr,int size=3,QString title="", int entryWidth=20, int entryHeight=20) : QWidget(parent), size(size) {
        vector.resize(size); // Ajusta o tamanho do vetor conforme necessário
        entryWidth_ = entryWidth;
        entryHeight_ = entryHeight;
        setupUi(title);
    }
    QVector<double> getVector(){
        return vector;
    }
    void setVector(QVector<double>newVector) {
        vector = newVector;
        updateUi();
    }
public slots:
    void resizeVector(int newSize) {
        vector.resize(newSize);
        updateUi();
    }

private slots:
    void entryValueChanged() {
        QLineEdit *changedEntry = qobject_cast<QLineEdit *>(sender());
        if (changedEntry) {
            int row = gridLayout->indexOf(changedEntry) / gridLayout->columnCount();
            vector[row] = changedEntry->text().toDouble();
        }

        printVector(); // Adiciona a chamada para imprimir o vetor quando um valor for alterado
    }

private:
    QVector<double> vector;
    QGridLayout *gridLayout;
    QFrame *frame;
    QLabel *titleLabel;
    QVector<QLineEdit*> inputWidgets;
    int size;
    QHBoxLayout *frameLayout;
    int entryWidth_;
    int entryHeight_;

    void setupUi(const QString& title) {
        QHBoxLayout *mainLayout = new QHBoxLayout(this);

        frame = new QFrame(this);
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(2);

        // Crie um novo QVBoxLayout dentro do frame
        frameLayout = new QHBoxLayout(frame);
        if (!title.isEmpty()) {
            titleLabel = new QLabel(title, frame);
            titleLabel->setAlignment(Qt::AlignCenter);
            frameLayout->addWidget(titleLabel);
        }
        gridLayout = new QGridLayout();
        frame->setLayout(frameLayout);
        frameLayout->addLayout(gridLayout);  // Adicione o QGridLayout ao QVBoxLayout interno do frame
        setFrameFixedSize(100, 200);   // tamanho fixo

        mainLayout->addWidget(frame);

        updateUi(); // Chama a função de atualização inicial

        setLayout(mainLayout);
    }

    void updateUi() {
        // Limpa o layout existente dentro do QFrame
        QLayoutItem *child;
        while ((child = gridLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Adiciona entradas ao layout dentro do QFrame
        for (int i = 0; i < vector.size(); ++i) {
            QLineEdit *entry = new QLineEdit(QString::number(vector[i]), this);
            entry->setFixedSize(entryWidth_, entryHeight_);
            connect(entry, &QLineEdit::textChanged, this, &VectorLayout::entryValueChanged);
            gridLayout->addWidget(entry, i, 1);
        }
    }

    void updateEntries() {
        // Atualiza valores das entradas com base no vetor
        for (int i = 0; i < vector.size(); ++i) {
            QLineEdit *entry = qobject_cast<QLineEdit *>(gridLayout->itemAtPosition(i, 0)->widget());
            if (entry) {
                entry->setText(QString::number(vector[i]));
            }
        }
    }

    void setFrameFixedSize(int width, int height) {
        frame->setFixedSize(width, height);
        frameLayout->setSizeConstraint(QLayout::SetFixedSize);  // Impede o ajuste automático do layout interno
    }

    void printVector() {
        qDebug() << "Current Vector:";
        for (int i = 0; i < vector.size(); ++i) {
            qDebug() << vector[i];
        }
    }
};

#endif // VECTORLAYOUT_H
