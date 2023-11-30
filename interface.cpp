#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>
#include <QDebug>

using namespace Qt;

class MatrixSolver : public QWidget {
public:
    MatrixSolver(QWidget *parent = nullptr) : QWidget(parent) {
        // Configuração inicial
        numRows = 1;
        numCols = 1;
        initialize();

        // Layout principal
        layout = new QGridLayout(this);

        // Entradas para o número de linhas e colunas
        lineEditL = new QLineEdit(QString::number(numRows));
        QLabel *spacerLabel = new QLabel("x");
        lineEditC = new QLineEdit(QString::number(numCols));

        layout->addWidget(lineEditL, 0, 0);
        layout->addWidget(spacerLabel, 0, 1);
        layout->addWidget(lineEditC, 0, 2);

        connect(lineEditL, &QLineEdit::textChanged, this, &updateMatrixSize);
        connect(lineEditC, &QLineEdit::textChanged, this, &updateMatrixSize);

        // Frame para matriz de coeficientes
        coefFrame = createMatrixFrame(matrix, "Matriz de Coeficientes");
        layout->addWidget(coefFrame, 1, 0, 2, 2);

        // Vetor de variáveis
        varFrame = createVectorFrame(var, "Variáveis");
        layout->addWidget(varFrame, 1, 2);

        // Vetor de igualdade
        igualFrame = createVectorFrame(igual, "Igual");
        layout->addWidget(igualFrame, 1, 3);

        // Botão OK
        okButton = new QPushButton("OK", this);
        connect(okButton, &QPushButton::clicked, this, &OkClick);
        layout->addWidget(okButton, 3, 3);
    }

private slots:
    void updateMatrixSize() {
        // Atualizar o tamanho da matriz com base nas entradas L e C
        numRows = lineEditL->text().toInt();
        numCols = lineEditC->text().toInt();
        qDebug() << "NumRows: " << numRows << " NumCols: " << numCols;
        initialize();
        updateFrames();
    }

    void OkClick() {
        //
        qDebug() << "OK button clicked";
    }
    void OkClick() {
        //
        qDebug() << "OK button clicked";
    }

private:
    int numRows;
    int numCols;
    QVector<QVector<double>> matrix;
    QVector<QChar> var;
    QVector<double> igual;

    QLineEdit *lineEditL; //linhas, numero de equações
    QLineEdit *lineEditC; //colunas, numero de variaveis

    QFrame *coefFrame;
    QFrame *varFrame;
    QFrame *igualFrame;

    QPushButton *okButton;

    QGridLayout *layout;

    void initialize() {
        matrix.resize(numRows);
        for (int i = 0; i < numRows; ++i) {
            matrix[i].resize(numCols);
        }
        var.resize(numRows);
        igual.resize(numRows);
        for (int i = 0; i < numRows; ++i) {
            var[i] = 'a' + i;
        }
    }

    void updateFrames() {
        // Atualiza os frames com os novos dados da matriz
        qDebug() << "Updating Frames";

        // Remover os widgets antigos do layout principal
        layout->removeWidget(coefFrame);
        layout->removeWidget(varFrame);
        layout->removeWidget(igualFrame);

        delete coefFrame;
        delete varFrame;
        delete igualFrame;

        // Frame para matriz de coeficientes
        coefFrame = createMatrixFrame(matrix, "Matriz de Coeficientes");
        layout->addWidget(coefFrame, 1, 0, 2, 2);

        // Vetor de variáveis
        varFrame = createVectorFrame(var, "Variáveis");
        layout->addWidget(varFrame, 1, 2);

        // Vetor de igualdade
        igualFrame = createVectorFrame(igual, "Igual");
        layout->addWidget(igualFrame, 1, 3);

        update();
        qDebug() << "Frames Updated";
    }

    QFrame *createVectorFrame(QVector<double> vector, QString title) {
        QFrame *frame = new QFrame(this);
        frame->setFrameShape(QFrame::Box);

        QVBoxLayout *layout = new QVBoxLayout(frame);

        QLabel *titleLabel = new QLabel(title, frame);
        titleLabel->setAlignment(AlignTop | AlignHCenter);
        layout->addWidget(titleLabel);

        for (int i = 0; i < vector.size(); ++i) {
            QLineEdit *entry = new QLineEdit(QString::number(vector[i]), frame);
            entry->setAlignment(AlignTop | AlignHCenter);
            layout->addWidget(entry);
        }

        return frame;
    }

    QFrame *createVectorFrame(QVector<QChar> vector, QString title) {
        QFrame *frame = new QFrame(this);
        frame->setFrameShape(QFrame::Box);

        QVBoxLayout *layout = new QVBoxLayout(frame);
        QLabel *titleLabel = new QLabel(title, frame);
        titleLabel->setAlignment(AlignTop | AlignHCenter);
        layout->addWidget(titleLabel);

        for (int i = 0; i < vector.size(); ++i) {
            QLineEdit *entry = new QLineEdit(QString(vector[i]), frame);
            entry->setAlignment(AlignTop | AlignHCenter);
            layout->addWidget(entry);
            connect(lineEditC, &QLineEdit::textChanged, this, &updateMatrixSize);
        }

        return frame;
    }

    QFrame *createMatrixFrame(QVector<QVector<double>> matrix, QString title) {
        QFrame *frame = new QFrame(this);
        frame->setFrameShape(QFrame::Box);

        QVBoxLayout *layout = new QVBoxLayout(frame);

        QLabel *titleLabel = new QLabel(title, frame);
        titleLabel->setAlignment(AlignTop | AlignHCenter);
        layout->addWidget(titleLabel);

        // Adicionar entradas da matriz
        for (int i = 0; i < numRows; ++i) {
            QHBoxLayout *rowLayout = new QHBoxLayout();
            for (int j = 0; j < numCols; ++j) {
                QLineEdit *entry = new QLineEdit(QString::number(matrix[i][j]), frame);
                entry->setAlignment(AlignTop);
                rowLayout->addWidget(entry);
            }
            layout->addLayout(rowLayout);
        }
        return frame;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MatrixSolver solver;
    solver.setGeometry(0, 0, 0, 0);
    solver.show();

    return app.exec();
}
