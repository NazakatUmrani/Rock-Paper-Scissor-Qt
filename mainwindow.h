#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void enableItems(bool);

private slots:
    void on_newGameButton_clicked();
    void handleLabelClicked(int id);

private:
    Q_OBJECT
    bool isHumanTurn=false;
    int computerChoice;
    int humanChoice;
    int computerScore=0;
    int humanScore=0;
    int triesRemaining=5;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
