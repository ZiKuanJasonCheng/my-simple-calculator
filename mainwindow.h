#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_pressed();

    void pushButton_dot_released();
    void pushButton_clear_released();
    void pushButton_back_released();
    void pushButton_divide_released();
    void pushButton_multiply_released();
    void pushButton_add_released();
    void pushButton_subtract_released();
    void pushButton_mod_released();
    void pushButton_equal_released();
    bool checkErrString();
};
#endif // MAINWINDOW_H
