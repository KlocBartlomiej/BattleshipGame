#include "mainwindow.h"
#include "battlefieldcontroller.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , battlefiedController(nullptr,nullptr)
{
    ui->setupUi(this);

    battlefiedController = BattlefieldController(ui->battlefield, ui->enemyBattlefield);

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

    QLabel* yIndicator;
    int jIndex = 0;

    for(int i = 1; i < 11; i++)
    {
        yIndicator = getLabelFromInt(i);
        ui->battlefield->addWidget(yIndicator, i, jIndex);

        yIndicator = getLabelFromInt(i);
        ui->enemyBattlefield->addWidget(yIndicator, i, jIndex);
    }

    clearBattlefields();
    printHelp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearBattlefields()
{
    bool isEnemyGround = true;
    //TODO clear list of ships for backend when clearing UI
    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            ui->battlefield->addWidget(battlefiedController.setNew(new MyFrame(i,j), !isEnemyGround), i, j);
            ui->enemyBattlefield->addWidget(battlefiedController.setNew(new MyFrame(i,j), isEnemyGround), i, j);
        }
    }
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

void MainWindow::prepareBattlefield()
{
    clearBattlefields();
    ui->chat->clear();
    ui->chat->append("Please place your ships. Keep in mind you can \"/rotate\" them.");
    battlefiedController.shipSetter->setAllShips();
}

void MainWindow::printHelp()
{
    ui->chat->append("You can choose:\
        \ntype \"/bot\" to start new game agains the computer\
        \ntype \"/connect\" to start a game agains player which will connect to you\
        \ntype \"/newGameWithTheSamePlayer\" to start another game with the same player without connecting\
        \ntype \"/rotate\" to change ship orientation\
    ");
}

void MainWindow::on_send_clicked()
{
    QString userInput = ui->input->toPlainText();
    if (userInput == "/rotate" || userInput == "/rotate\n")
    {
        battlefiedController.shipSetter->changeDrawingDirection();
        return;
    }
    if(userInput.startsWith("/") and !battlefiedController.isGameStarted)
    {
        qDebug() << "userInput: " << userInput;
        if(userInput == "/bot" || userInput == "/bot\n")
        {
            qDebug() << "/bot option was choosen";
            prepareBattlefield();
            battlefiedController.isGameStarted = true;
            //startGameWithBot();
        }
        else if(userInput == "/connect" || userInput == "/connect\n")
        {
            prepareBattlefield();
            battlefiedController.isGameStarted = true;
            //establishConnection(); or wait for player to connect (print ip and port in the chat)
            //startGameWithPlayer;
        }
        else if(userInput == "/newGameWithTheSamePlayer" || userInput == "/newGameWithTheSamePlayer\n")
        {
            prepareBattlefield();
            battlefiedController.isGameStarted = true;
            //startGameWithPlayer;
        }
        else
        {
            printHelp();
        }
        ui->input->clear();
        return;
    }
    ui->chat->append(userInput);
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

