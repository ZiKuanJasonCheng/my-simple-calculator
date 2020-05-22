#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVector>
#include <math.h>
using namespace std;

// Revised and referenced from: Qt Calculator GUI Tutorial: https://www.youtube.com/watch?v=FhV1ZEVNK08

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    connect(ui->pushButton_dot, SIGNAL(released()), this, SLOT(pushButton_dot_released()));
    connect(ui->pushButton_clear, SIGNAL(released()), this, SLOT(pushButton_clear_released()));
    connect(ui->pushButton_back, SIGNAL(released()), this, SLOT(pushButton_back_released()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(pushButton_divide_released()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(pushButton_multiply_released()));
    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(pushButton_add_released()));
    connect(ui->pushButton_subtract, SIGNAL(released()), this, SLOT(pushButton_subtract_released()));
    connect(ui->pushButton_mod, SIGNAL(released()), this, SLOT(pushButton_mod_released()));
    connect(ui->pushButton_equal, SIGNAL(released()), this, SLOT(pushButton_equal_released()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkErrString(){
    if(ui->label_digits->text().compare("err") == 0){
        return true;
    }
    else{
        return false;
    }
}


void MainWindow::digit_pressed(){
    QPushButton *button = (QPushButton*)sender();
    qDebug() << "Digit button " + button->text() + " pressed!";

    if(ui->label_digits->text().compare("0") == 0 || checkErrString()){
        ui->label_digits->setText(button->text());
    }
    else if(ui->label_digits->text().size() >= 2 && ui->label_digits->text()[ui->label_digits->text().size()-1] == '0' &&
            (ui->label_digits->text()[ui->label_digits->text().size()-2] == '+'
            || ui->label_digits->text()[ui->label_digits->text().size()-2] == '-'
            || ui->label_digits->text()[ui->label_digits->text().size()-2] == 'x'
            || ui->label_digits->text().right(2).contains("÷")
            )){
        ui->label_digits->setText(ui->label_digits->text().mid(0, ui->label_digits->text().size()-1) + button->text());
    }
    else{
        ui->label_digits->setText(ui->label_digits->text() + button->text());
    }


}

void MainWindow::pushButton_dot_released(){
    if(checkErrString()){
        return;
    }

    bool hasDot = false;
    QString str = ui->label_digits->text();
    int i = str.length() - 1;
    while(i >= 0){
        if(str[i] == '.'){
            hasDot = true;
            break;
        }
        else{
            if(str[i] == '+' || str[i] == '+' || str[i] == 'x' || str.mid(i, 1).contains("÷")){
                break;
            }
        }
        i--;
    }
    if(!hasDot){
        ui->label_digits->setText(ui->label_digits->text() + ".");
    }
}

void MainWindow::pushButton_clear_released(){
    qDebug() << "pushButton_clear_released()";
    ui->label_digits->setText("0");
}

void MainWindow::pushButton_back_released(){
    qDebug() << "pushButton_back_released()";
    if(checkErrString()){
        return;
    }
    QString subString = ui->label_digits->text();
    subString.chop(1);
    if(subString.isEmpty()){
        subString = "0";
    }
    ui->label_digits->setText(subString);
}

void MainWindow::pushButton_divide_released(){
    qDebug() << "pushButton_divide_released()";
    if(checkErrString()){
        return;
    }
    QString subString = ui->label_digits->text();
    if(subString[subString.size()-1] == '+' ||
       subString[subString.size()-1] == '-' ||
       subString[subString.size()-1] == '%' ||
       subString[subString.size()-1] == 'x'){
       subString.chop(1);
       ui->label_digits->setText(subString + "÷");
    }
    else if(!subString.right(1).contains("÷")){
        ui->label_digits->setText(subString + "÷");
    }
}

void MainWindow::pushButton_multiply_released(){
    qDebug() << "pushButton_multiply_released()";
    if(checkErrString()){
        return;
    }
    QString subString = ui->label_digits->text();
    if(subString[subString.size()-1] == '+' ||
       subString[subString.size()-1] == '-' ||
       subString[subString.size()-1] == '%' ||
       subString.right(1).contains("÷")){
       subString.chop(1);
       ui->label_digits->setText(subString + "x");
    }
    else if(subString[subString.size()-1] != 'x'){
        ui->label_digits->setText(subString + "x");
    }
}

void MainWindow::pushButton_add_released(){
    qDebug() << "pushButton_add_released()";
    if(checkErrString()){
        return;
    }
    QString subString = ui->label_digits->text();
    if(subString[subString.size()-1] == '-' ||
       subString[subString.size()-1] == '%' ||
       subString[subString.size()-1] == 'x' ||
       subString.right(1).contains("÷")){
       subString.chop(1);
       ui->label_digits->setText(subString + "+");
    }
    else if(subString[subString.size()-1] != '+'){
        ui->label_digits->setText(subString + "+");
    }
}

void MainWindow::pushButton_subtract_released(){
    qDebug() << "pushButton_subtract_released()";
    if(checkErrString()){
        return;
    }
    QString subString = ui->label_digits->text();
    if(subString[subString.size()-1] == '+' ||
       subString[subString.size()-1] == '%' ||
       subString[subString.size()-1] == 'x' ||
       subString.right(1).contains("÷")){
       subString.chop(1);
       ui->label_digits->setText(subString + "-");
    }
    else if(subString[subString.size()-1] != '-'){
        ui->label_digits->setText(subString + "-");
    }
}

void MainWindow::pushButton_mod_released(){
    qDebug() << "pushButton_mod_released()";
    if(checkErrString()){
        return;
    }
    QString subString = ui->label_digits->text();
    if(subString[subString.size()-1] == '+' ||
       subString[subString.size()-1] == '-' ||
       subString[subString.size()-1] == 'x' ||
       subString.right(1).contains("÷")){
       subString.chop(1);
       ui->label_digits->setText(subString + "%");
    }
    else if(subString[subString.size()-1] != '%'){
        ui->label_digits->setText(subString + "%");
    }
}

void MainWindow::pushButton_equal_released(){
    qDebug() << "pushButton_equal_released()";
    if(checkErrString()){
        return;
    }
    QVector<QString> vec;
    vec.clear();
    QString subString = ui->label_digits->text();
    // Get all operators and numbers in the string
    int j = 0;
    for(int i=0;i<subString.size();i++){
        if(subString[i] == '+' || subString[i] == '-' || subString[i] == 'x' || subString.mid(i, 1).contains("÷") || subString[i] == '%'){
            if(j < i){
                vec.push_back(subString.mid(j, i - j));
                j = i + 1;
            }
            if(subString[i] == '+'){
                vec.push_back("+");
            }
            else if(subString[i] == '-'){
                vec.push_back("-");
            }
            else if(subString[i] == 'x'){
                vec.push_back("*");
            }
            else if(subString.mid(i, 1).contains("÷")){
                vec.push_back("/");
            }
            else if(subString[i] == '%'){
                vec.push_back("%");
            }
        }

        if(i == subString.size()-1 && j <= i){
            vec.push_back(subString.mid(j, i + 1 - j));
            j = i + 1;
        }
    }
    float result = 0;
    int i = 0;
    bool error = false;
    while(i < vec.size()){
        qDebug() << "vec[" << i << "]=" << vec[i];
        if(vec[i][0]!='*' && vec[i][0]!='/' && vec[i][0]!='+' && vec[i][0]!='-' && vec[i][0]!='%'){  // A number
            if(i == 0){
                i++;
            }
            else if((vec[i-1][0] == '+' || vec[i-1][0] == '-') && (i+1 >= vec.size() || vec[i+1][0] == '+' || vec[i+1][0] == '-')){
                // Calculate right now
                float num1 = vec[i-2].toFloat();
                float num2 = vec[i].toFloat();
                if(vec[i-1][0] == '+'){
                    result = num1 + num2;
                }
                else{
                    result = num1 - num2;
                }
                vec.remove(i-2);
                vec.remove(i-2);
                vec.remove(i-2);
                QString temp = QString::number(result);
                vec.insert(i-2, temp);
                i-=2;
            }
            else if((vec[i-1][0] == '+' || vec[i-1][0] == '-') && (i+1 < vec.size() && (vec[i+1][0] == '*' || vec[i+1][0] == '/' || vec[i+1][0] == '%'))){
                i++;
            }
            else if((vec[i-1][0] == '*' || vec[i-1][0] == '/' || vec[i-1][0] == '%')){
                // Calculate right now
                float num1 = vec[i-2].toFloat();
                float num2 = vec[i].toFloat();
                if(vec[i-1][0] == '*'){
                    result = num1 * num2;
                }
                else if(vec[i-1][0] == '/'){
                    if(num2 == 0){
                        // Output error
                        error = true;
                        break;
                    }
                    result = num1 / num2;
                }
                else{  // '%'
                    int num1 = round(vec[i-2].toFloat());
                    int num2 = round(vec[i].toFloat());
                    qDebug() << "num1= " << num1;
                    qDebug() << "num2= " << num2;
                    if(num2 == 0){
                        // Output error
                        error = true;
                        break;
                    }
                    result = num1 % num2;
                }

                vec.remove(i-2);
                vec.remove(i-2);
                vec.remove(i-2);
                QString temp = QString::number(result);
                vec.insert(i-2, temp);
                i-=2;
            }

        }
        else{
            i++;
        }
    }

    if(!error){
        ui->label_digits->setText(vec[0]);
    }
    else{
        ui->label_digits->setText("err");
    }
}
