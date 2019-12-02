#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    matrix1 = nullptr;
    matrix2 = nullptr;
    result = nullptr;
    resultTemp = nullptr;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_generateMatrix_1_clicked(){
    int row = ui->row_1->value();
    int col = ui->col_1->value();
    if(row == 0 || col == 0){
        return;
    }
    if(ui->floatButton->isChecked()){
        clearMatrix(matrix1);
        matrix1 = new Matrix(row, col, false);
        showMatrix(matrix1, ui->text_1, false);
    }else if(ui->intButton->isChecked()){
        clearMatrix(matrix1);
        matrix1 = new Matrix(row, col, true);
        showMatrix(matrix1, ui->text_1, true);
    }else{
        return;
    }

}

void MainWindow::on_generateMatrix_2_clicked()
{
    int row = ui->row_2->value();
    int col = ui->col_2->value();
    if(row == 0 || col == 0){
        return;
    }
    if(ui->floatButton->isChecked()){
        clearMatrix(matrix2);
        matrix2 = new Matrix(row, col, false);
        showMatrix(matrix2, ui->text_2, false);
    }else if(ui->intButton->isChecked()){
        clearMatrix(matrix2);
        matrix2 = new Matrix(row, col, true);
        showMatrix(matrix2, ui->text_2, true);
    }else{
        return;
    }
}

void MainWindow::on_calculateButton_clicked(){
    if(matrix1 == nullptr && matrix2 == nullptr){
        return;
    }
    if(ui->minuxButton->isChecked()){
        clearMatrix(result);
        result = (*matrix1) - (*matrix2);
        if(result != nullptr){
            showMatrix(result, ui->text_3, result->getIsInt());
        }
    }else if(ui->plusButton->isChecked()){
        clearMatrix(result);
        result = (*matrix1) + (*matrix2);
        if(result != nullptr){
            showMatrix(result, ui->text_3, result->getIsInt());
        }
    }else if(ui->multiplyButton->isChecked()){
        clearMatrix(result);
        result = (*matrix1) * (*matrix2);
        if(result != nullptr){
            showMatrix(result, ui->text_3, result->getIsInt());
        }
    }
}

void MainWindow::on_transposeButton_clicked(){
    if(result != nullptr){
        resultTemp = result;
        result = result->transpose();
        clearMatrix(resultTemp);
        showMatrix(result, ui->text_3, result->getIsInt());
    }
}

void MainWindow::showMatrix(Matrix* m, QTextBrowser* text, bool isInt){
    text->clear();
    for(int i = 0; i < m->getRow(); ++i){
        string str = "";
        for(int j = 0; j < m->getCol(); ++j){
            if(isInt){
                str = str + to_string(m->getInt(i, j)) + " ";
            }else{
                str = str + to_string(m->getDouble(i, j)) + " ";
            }
        }
        str += "\n";
        text->append(QString::fromStdString(str));
    }
}

void MainWindow::clearMatrix(Matrix* m){
    if(m != nullptr){
        delete m;
        m = nullptr;
    }
}

