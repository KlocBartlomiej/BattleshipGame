#include "mainwindow.h"
#include "battlefieldcontroller.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BattlefieldController battlefiedController =
        BattlefieldController(ui->battlefield, ui->enemyBattlefield);
    bool isEnemyGround = true;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            ui->battlefield->addWidget(battlefiedController.setNew(new MyFrame(i,j), !isEnemyGround), i, j);
            ui->enemyBattlefield->addWidget(battlefiedController.setNew(new MyFrame(i,j), isEnemyGround), i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_send_clicked()
{
    ui->chat->append(ui->input->toPlainText());
    ui->input->clear();
}


//TODO create my own keyPressed(QEvent::KeyPress *event)
void MainWindow::on_input_cursorPositionChanged()
{   //it's used to detect when enter was used inside input TextEdit
    if(ui->input->textCursor().positionInBlock() == 0
        //clicking on the send button will also trigger this function
        //so it's important to check if there's anything to append to chat from input field
        and ui->input->toPlainText() != "")
    {
        ui->send->animateClick();
    }
}

