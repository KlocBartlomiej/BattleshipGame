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

    char fieldXIndicator = 'A';
    QLabel* xIndicator;
    int iIndex = 0;

    for(int j = 1; j < 11; j++, fieldXIndicator++)
    {
        xIndicator = getLabelFromChar(fieldXIndicator);
        ui->battlefield->addWidget(xIndicator,iIndex, j);

        xIndicator = getLabelFromChar(fieldXIndicator);
        ui->enemyBattlefield->addWidget(xIndicator,iIndex, j);
    }

    bool isEnemyGround = true;
    QLabel* yIndicator;

    for(int i = 1; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(j == 0)
            {
                yIndicator = getLabelFromInt(i);
                ui->battlefield->addWidget(yIndicator, i, j);

                yIndicator = getLabelFromInt(i);
                ui->enemyBattlefield->addWidget(yIndicator, i, j);

                continue;
            }
            ui->battlefield->addWidget(battlefiedController.setNew(new MyFrame(i,j), !isEnemyGround), i, j);
            ui->enemyBattlefield->addWidget(battlefiedController.setNew(new MyFrame(i,j), isEnemyGround), i, j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QLabel* MainWindow::getLabelFromChar(char c)
{
    QLabel* label = new QLabel();
    label->setText(QString(c));
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    return label;
}

QLabel* MainWindow::getLabelFromInt(int i)
{
    QLabel* label = new QLabel();
    label->setText(QString::number(i));
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    return label;
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

