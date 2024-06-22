#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , battlefieldController(nullptr,nullptr,nullptr,false)
{
    ui->setupUi(this);

    battlefieldController = BattlefieldController(ui->battlefield, ui->enemyBattlefield, ui->chat, false);

    QObject::connect(battlefieldController.gameInstance, &GameLogic::gameEnded, this, &MainWindow::gameEnded);

    char fieldXContent = 'A';
    QLabel* xIndicator;
    int iIndex = 0;

    for(int j = 1; j < 11; j++, fieldXContent++)
    {
        xIndicator = getLabelFromChar(fieldXContent);
        ui->battlefield->addWidget(xIndicator,iIndex, j);

        xIndicator = getLabelFromChar(fieldXContent);
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

    bool isEnemyGround = true;
    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            ui->battlefield->addWidget(
                battlefieldController.setNew(
                    new MyFrame(i,j), !isEnemyGround), i, j);
            ui->enemyBattlefield->addWidget(
                battlefieldController.setNew(
                    new MyFrame(i,j), isEnemyGround), i, j);
        }
    }
    printHelp();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearBattlefields()
{
    battlefieldController.shipSetter->clearShips();
    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            MyFrame::setEmpty(i,j,ui->battlefield);
            MyFrame::setEmpty(i,j,ui->enemyBattlefield);
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
    battlefieldController.gameInstance->startPlaying();
    ui->chat->clear();
    ui->chat->append("Please place your ships. Keep in mind you can \"/rotate\" them.");
    battlefieldController.shipSetter->setAllShips();
}

void MainWindow::gameEnded(const QString msg)
{
    ui->chat->clear();
    ui->chat->append(msg);
    printHelp();
}

void MainWindow::printHelp()
{
    ui->chat->append("You can choose:\
        \ntype \"/bot\" to start new game agains the computer\
        \ntype \"/rotate\" to change ship orientation during placing ships\
        \ntype \"/listenForConnection\" to wait for another player to join\
        \ntype \"/connect\" to start a game agains player which awaits (require IP:port)\
        \n       eg. /connect 168.192.0.11:6969\
    ");
}

void MainWindow::on_send_clicked()
{
    QString userInput = ui->input->toPlainText();
    if (userInput.startsWith("/rotate"))
    {
        battlefieldController.shipSetter->changeDrawingDirection();
        ui->input->clear();
        return;
    }
    if(userInput.startsWith("/") and !battlefieldController.gameInstance->hasGameStarted())
    {
        qDebug() << "userInput: " << userInput;
        if(userInput.startsWith("/bot"))
        {
            qDebug() << "/bot option was choosen";
            prepareBattlefield();
            battlefieldController.gameInstance->setOpponentInstance(
                new Bot(ui->enemyBattlefield));
        }
        else if(userInput.startsWith("/listenForConnection"))
        {
            qDebug() << "/listenForConnection option was choosen";
            prepareBattlefield();
            std::tuple<QString,int> connectionData =
                battlefieldController.connectionToPlayer->startListening();
            ui->chat->append("Provide IP:port to the second player: "
                             + std::get<0>(connectionData) + ":" + QString::number(std::get<1>(connectionData)));
            //TODO look at below todo
        }
        else if(userInput.startsWith("/connect"))
        {
            qDebug() << "/connect option was choosen";
            prepareBattlefield();
            std::tuple<const QString, const int> ipAndPort = getIpAndPortFromInput(userInput);
            battlefieldController.connectionToPlayer->connectToPlayer(std::get<0>(ipAndPort), std::get<1>(ipAndPort));
            // TODO when connecting to other player or waiting for signal
            // I need to set up other player instance on playerConnected(socket) signal call
            // battlefieldController.gameInstance->setOpponentInstance(new OtherPlayer(socket));
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

std::tuple<QString,int> MainWindow::getIpAndPortFromInput(QString userInput)
{
    QStringList list = userInput.split(" ")[1].split(":");
    return std::make_tuple(list.first(),list.last().toInt());
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

