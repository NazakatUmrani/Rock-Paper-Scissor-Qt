#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qsizepolicy.h>
#include <QRandomGenerator>
#include <QDateTime>
#include "clickablelabel.h"
#include <QObject>
#include <QTime>

//Function for delay
void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//Function to enable and disable mainGridLayout
void MainWindow::enableItems(bool b){
    ui->triesRemainingLabel->setDisabled(!b);
    ui->computerScoreLabel->setDisabled(!b);
    ui->humanScoreLabel->setDisabled(!b);
    ui->humanVSComputerLabel->setDisabled(!b);
    ui->humanIconsLayout->itemAt(0)->widget()->setDisabled(!b);
    ui->humanIconsLayout->itemAt(1)->widget()->setDisabled(!b);
    ui->humanIconsLayout->itemAt(2)->widget()->setDisabled(!b);
    ui->computerIconsLayout->itemAt(0)->widget()->setDisabled(!b);
    ui->computerIconsLayout->itemAt(1)->widget()->setDisabled(!b);
    ui->computerIconsLayout->itemAt(2)->widget()->setDisabled(!b);
}

// Generate a random number between a minimum and maximum value (inclusive)
int randomInt(int min, int max){
    // Create a local QRandomGenerator
    QRandomGenerator generator;
    // Seed the generator with a random value based on the current time
    generator.seed(static_cast<quint64>(QDateTime::currentMSecsSinceEpoch()));
    // Generate the random number within the specified range
    return generator.bounded(min, max + 1);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Set Human Labels
    ClickableLabel *humanRockLabel = new ClickableLabel(1);
    ClickableLabel *humanPaperLabel = new ClickableLabel(2);
    ClickableLabel *humanScissorLabel = new ClickableLabel(3);
    humanRockLabel->setPixmap(QPixmap(":/icons/Rock-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    humanPaperLabel->setPixmap(QPixmap(":/icons/Paper-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    humanScissorLabel->setPixmap(QPixmap(":/icons/Scissor-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    humanRockLabel->setMinimumSize(90,90);
    humanPaperLabel->setMinimumSize(90,90);
    humanScissorLabel->setMinimumSize(90,90);
    humanRockLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    humanPaperLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    humanScissorLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    ui->humanIconsLayout->addWidget(humanRockLabel);
    ui->humanIconsLayout->addWidget(humanPaperLabel);
    ui->humanIconsLayout->addWidget(humanScissorLabel);
    humanRockLabel->setAlignment(Qt::AlignCenter);
    humanPaperLabel->setAlignment(Qt::AlignCenter);
    humanScissorLabel->setAlignment(Qt::AlignCenter);
    QObject::connect(humanRockLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    QObject::connect(humanPaperLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    QObject::connect(humanScissorLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    //Set COmputer Labels
    ClickableLabel *computerRockLabel = new ClickableLabel(4);
    ClickableLabel *computerPaperLabel = new ClickableLabel(5);
    ClickableLabel *computerScissorLabel = new ClickableLabel(6);
    computerRockLabel->setPixmap(QPixmap(":/icons/Rock-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    computerPaperLabel->setPixmap(QPixmap(":/icons/Paper-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    computerScissorLabel->setPixmap(QPixmap(":/icons/Scissor-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    computerRockLabel->setBaseSize(90,90);
    computerPaperLabel->setBaseSize(90,90);
    computerScissorLabel->setBaseSize(90,90);
    computerRockLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    computerPaperLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    computerScissorLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    ui->computerIconsLayout->addWidget(computerRockLabel);
    ui->computerIconsLayout->addWidget(computerPaperLabel);
    ui->computerIconsLayout->addWidget(computerScissorLabel);
    computerRockLabel->setAlignment(Qt::AlignCenter);
    computerPaperLabel->setAlignment(Qt::AlignCenter);
    computerScissorLabel->setAlignment(Qt::AlignCenter);
    QObject::connect(computerRockLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    QObject::connect(computerPaperLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    QObject::connect(computerScissorLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    enableItems(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    ui->newGameButton->setDisabled(true);
    ui->humanVSComputerLabel->setDisabled(false);
    ui->messageLabel->setText("Wait... Loading");
    ui->humanVSComputerLabel->setPixmap(QPixmap(":/icons/count3.png").scaled(70,70,Qt::KeepAspectRatio));
    delay(1000);
    ui->humanVSComputerLabel->setPixmap(QPixmap(":/icons/count2.png").scaled(70,70,Qt::KeepAspectRatio));
    delay(1000);
    ui->humanVSComputerLabel->setPixmap(QPixmap(":/icons/count1.png").scaled(70,70,Qt::KeepAspectRatio));
    delay(1000);
    ui->messageLabel->setText("Your Turn, Click on one, Rock Paper Scissor");
    ui->humanVSComputerLabel->setText("Human VS Computer");
    ui->humanScoreLabel->setText("Your Score: 0");
    ui->computerScoreLabel->setText("Computer Score: 0");
    enableItems(true);
    isHumanTurn=true;
}

void MainWindow::handleLabelClicked(int id) {
    if(isHumanTurn && (0<id && id<4)){
        //Reset Turn
        isHumanTurn=false;
        //Set Human and Computer Choice
        humanChoice=id;
        computerChoice = randomInt(1, 3);
        //Print choices
        qDebug() << "Your Choice "<<id;
        qDebug() << "Computer Choice "<<computerChoice;

        //Disable Circles
        if(id==1)
            ui->humanIconsLayout->itemAt(id - 1)->widget()->setDisabled(true);//clickableLabel->setPixmap(QPixmap(":/icons/Rock-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(id==2)
            ui->humanIconsLayout->itemAt(id - 1)->widget()->setDisabled(true);//clickableLabel->setPixmap(QPixmap(":/icons/Paper-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(id==3)
            ui->humanIconsLayout->itemAt(id - 1)->widget()->setDisabled(true);//clickableLabel->setPixmap(QPixmap(":/icons/Scissor-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));
        if(computerChoice==1)
            ui->computerIconsLayout->itemAt(computerChoice - 1)->widget()->setDisabled(true);//clickableLabel->setPixmap(QPixmap(":/icons/Rock-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(computerChoice==2)
            ui->computerIconsLayout->itemAt(computerChoice - 1)->widget()->setDisabled(true);//clickableLabel->setPixmap(QPixmap(":/icons/Paper-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(computerChoice==3)
            ui->computerIconsLayout->itemAt(computerChoice - 1)->widget()->setDisabled(true);//clickableLabel->setPixmap(QPixmap(":/icons/Scissor-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));

        //update message to wait
        ui->messageLabel->setText("wait");

        //Check choices
        if(humanChoice==1){
            if(computerChoice==1){
                ui->humanVSComputerLabel->setText("      Draw       ");
            }
            else if(computerChoice==2){
                ui->humanVSComputerLabel->setText("  Computer wins  ");
                computerScore++;
            }
            else if(computerChoice==3){
                ui->humanVSComputerLabel->setText("     You win     ");
                humanScore++;
            }
        }
        else if(humanChoice==2){
            if(computerChoice==1){
                ui->humanVSComputerLabel->setText("     You win     ");
                humanScore++;
            }
            else if(computerChoice==2){
                ui->humanVSComputerLabel->setText("      Draw       ");
            }
            else if(computerChoice==3){
                ui->humanVSComputerLabel->setText("  Computer wins  ");
                computerScore++;
            }
        }
        else if(humanChoice==3){
            if(computerChoice==1){
                ui->humanVSComputerLabel->setText("  Computer wins  ");
                computerScore++;
            }
            else if(computerChoice==2){
                ui->humanVSComputerLabel->setText("     You win     ");
                humanScore++;
            }
            else if(computerChoice==3){
                ui->humanVSComputerLabel->setText("      Draw       ");
            }
        }

        //wait for 1 second
        delay(1000);

        //Enable Circles
        if(id==1)
            ui->humanIconsLayout->itemAt(id - 1)->widget()->setDisabled(false);//clickableLabel->setPixmap(QPixmap(":/icons/Rock-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(id==2)
            ui->humanIconsLayout->itemAt(id - 1)->widget()->setDisabled(false);//clickableLabel->setPixmap(QPixmap(":/icons/Paper-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(id==3)
            ui->humanIconsLayout->itemAt(id - 1)->widget()->setDisabled(false);//clickableLabel->setPixmap(QPixmap(":/icons/Scissor-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
        if(computerChoice==1)
            ui->computerIconsLayout->itemAt(computerChoice - 1)->widget()->setDisabled(false);//clickableLabel->setPixmap(QPixmap(":/icons/Rock-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(computerChoice==2)
            ui->computerIconsLayout->itemAt(computerChoice - 1)->widget()->setDisabled(false);//clickableLabel->setPixmap(QPixmap(":/icons/Paper-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));
        else if(computerChoice==3)
            ui->computerIconsLayout->itemAt(computerChoice - 1)->widget()->setDisabled(false);//clickableLabel->setPixmap(QPixmap(":/icons/Scissor-Icon-Disabled.png").scaled(90,90,Qt::KeepAspectRatio));

        ui->humanVSComputerLabel->setText(QString::fromStdString("Human VS Computer"));
        ui->computerScoreLabel->setText(QString::fromStdString("Computer Score: "+std::to_string(computerScore)));
        ui->humanScoreLabel->setText(QString::fromStdString("Your Score: "+std::to_string(humanScore)));
        triesRemaining--;
        ui->triesRemainingLabel->setText(QString::fromStdString(std::to_string(triesRemaining)+" Tries Remaining"));
        computerChoice=0;
        humanChoice=0;
        if(triesRemaining==0){
            if(computerScore>humanScore){
                ui->humanVSComputerLabel->setText("Computer Wins");
                ui->messageLabel->setText("Better luck next time");
            }
            else if(humanScore>computerScore){
                ui->humanVSComputerLabel->setText("You Wins");
                ui->messageLabel->setText("Congratulations");
            }
            else{
                ui->humanVSComputerLabel->setText("It is Draw");
                ui->messageLabel->setText("Better luck next time");
            }
            triesRemaining=5;
            humanScore=0;
            computerScore=0;
            enableItems(false);
            delay(2000);
            ui->triesRemainingLabel->setText(QString::fromStdString(std::to_string(triesRemaining)+" Tries Remaining"));
            ui->computerScoreLabel->setText("Computer");
            ui->humanScoreLabel->setText("Human");
            ui->messageLabel->setText("Press Button to Start Game");
            ui->humanVSComputerLabel->setText("Human VS Computer");
            ui->newGameButton->setEnabled(true);
            return;
        }
        delay(2000);
        ui->messageLabel->setText("Your Turn, Click on one, Rock Paper Scissor");
        isHumanTurn=true;
    }
}
