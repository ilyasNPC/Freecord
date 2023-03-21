#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("..\\imgs\\LeikaMiniBanner.png"); // Default logo for now, later change it to custom for servers
    pix.scaled(100, 100, Qt::KeepAspectRatio);
    ui->banner->setPixmap(pix);

    //ui->label_5->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

