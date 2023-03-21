#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialogaboutqt.h"
#include "dialogconnect.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("..\\imgs\\LeikaMiniBanner.png"); // Default logo for now, later change it to custom for servers
    pix.scaled(100, 100, Qt::KeepAspectRatio);
    ui->banner->setPixmap(pix);

    QPixmap pix1("..\\imgs\\icons\\avatar.png");
    pix1.scaled(50, 50, Qt::KeepAspectRatio);
    ui->avatar->setPixmap(pix1);

    QPixmap pix2("..\\imgs\\icons\\online.png");
    pix2.scaled(29, 29, Qt::KeepAspectRatio);
    ui->status->setPixmap(pix2);


    //ui->label_5->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    this->close();
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    DialogAboutQt daqt;
    daqt.setModal(true);
    daqt.exec();
}


void MainWindow::on_actionConnect_triggered()
{
    DialogConnect dacon;
    dacon.setModal(true);
    dacon.exec();
}

