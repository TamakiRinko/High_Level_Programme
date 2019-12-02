#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "matrix.h"
#include <math.h>
#include <QTextBrowser>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateMatrix_1_clicked();

    void on_generateMatrix_2_clicked();

    void on_calculateButton_clicked();

    void on_transposeButton_clicked();

private:
    Ui::MainWindow *ui;
    Matrix* matrix1;
    Matrix* matrix2;
    Matrix* result;
    Matrix* resultTemp;

    void showMatrix(Matrix* m, QTextBrowser* text, bool isInt);
    void clearMatrix(Matrix* m);
};

#endif // MAINWINDOW_H
