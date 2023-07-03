#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qsizepolicy.h>
#include <QRandomGenerator>
#include <QDateTime>
#include "clickablelabel.h"
#include <QObject>

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
    ClickableLabel *userRockLabel = new ClickableLabel(1);
    ClickableLabel *userPaperLabel = new ClickableLabel(2);
    ClickableLabel *userScissorLabel = new ClickableLabel(3);
    userRockLabel->setPixmap(QPixmap(":/icons/Rock-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    userPaperLabel->setPixmap(QPixmap(":/icons/Paper-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    userScissorLabel->setPixmap(QPixmap(":/icons/Scissor-Icon-Enabled.png").scaled(90,90,Qt::KeepAspectRatio));
    userRockLabel->setMinimumSize(90,90);
    userPaperLabel->setMinimumSize(90,90);
    userScissorLabel->setMinimumSize(90,90);
    userRockLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    userPaperLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    userScissorLabel->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    ui->userIconsLayout->addWidget(userRockLabel);
    ui->userIconsLayout->addWidget(userPaperLabel);
    ui->userIconsLayout->addWidget(userScissorLabel);
    userRockLabel->setAlignment(Qt::AlignCenter);
    userPaperLabel->setAlignment(Qt::AlignCenter);
    userScissorLabel->setAlignment(Qt::AlignCenter);
    QObject::connect(userRockLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    QObject::connect(userPaperLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);
    QObject::connect(userScissorLabel, &ClickableLabel::clicked, this, &MainWindow::handleLabelClicked);

    ClickableLabel *computerRockLabel = new ClickableLabel(1);
    ClickableLabel *computerPaperLabel = new ClickableLabel(2);
    ClickableLabel *computerScissorLabel = new ClickableLabel(3);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    ui->newGameButton->setDisabled(true);
    ui->mainGridLayout->setEnabled(true);
}

void MainWindow::handleLabelClicked(int id) {
    if(isUserTurn==true){
        qDebug() << "Icon "<<id<<" clicked";
        userChoice=id;
        computerChoice = randomInt(1, 3);
    }
}
