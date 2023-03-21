#include "dialogaboutqt.h"
#include "ui_dialogaboutqt.h"

DialogAboutQt::DialogAboutQt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAboutQt)
{
    ui->setupUi(this);
}

DialogAboutQt::~DialogAboutQt()
{
    delete ui;
}
