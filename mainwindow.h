#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_send_clicked();
    void on_input_cursorPositionChanged();

private:
    Ui::MainWindow *ui;
    QLabel* getLabelFromChar(char);
    QLabel* getLabelFromInt(int);
};
#endif // MAINWINDOW_H
