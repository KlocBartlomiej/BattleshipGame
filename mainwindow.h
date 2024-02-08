#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "battlefieldcontroller.h"
#include "bot.h"

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui{ class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    BattlefieldController battlefieldController;

private slots:
    void on_send_clicked();
    void on_input_cursorPositionChanged();

    void gameEnded(const QString);

private:
    Ui::MainWindow *ui;

    void prepareBattlefield();
    void clearBattlefields();
    void printHelp();

    QLabel* getLabelFromChar(char);
    QLabel* getLabelFromInt(int);
};
#endif // MAINWINDOW_H
