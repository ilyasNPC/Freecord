#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialogaboutqt.h"
#include "dialogconnect.h"

#include <QChar>
#include <QDebug>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Temporary
    ui->chatLog->clear();
    ui->treeWidget->clear();
    populate();
    ui->treeWidget->expandAll();
    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->treeWidget->header()->setSectionResizeMode(1, QHeaderView::Interactive);

    ui->chatLog->verticalScrollBar()->setValue(ui->chatLog->verticalScrollBar()->maximum());

    // Make sure the chat log stays at the bottom as new messages are added
    connect(ui->chatLog->document(), &QTextDocument::contentsChanged, [=]() {
        ui->chatLog->verticalScrollBar()->setValue(ui->chatLog->verticalScrollBar()->maximum());
    });

    QPixmap pix("..\\imgs\\LeikaMiniBanner.png"); // Default logo for now, later change it to custom for servers
    pix.scaled(100, 100, Qt::KeepAspectRatio);
    ui->banner->setPixmap(pix);

    QPixmap pix1("..\\imgs\\icons\\avatar.png");
    pix1 = pix1.scaled(40, 40, Qt::KeepAspectRatio);
    ui->avatar->setPixmap(pix1);

    QPixmap pix2("..\\imgs\\icons\\online.png");
    pix2 = pix2.scaled(14, 14, Qt::KeepAspectRatio);
    ui->status->setPixmap(pix2);

    //ui->label_5->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populate()
{
    QFile file("..\\example.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QJsonDocument json_doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    int imageWidth, imageHeight;

    QJsonArray json_array = json_doc.array();
    for (const QJsonValue& json_value : json_array) {
        QJsonObject json_obj = json_value.toObject();
        QString name = json_obj.value("name").toString();
        int type = json_obj.value("type").toInt();

        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, name);

        switch(type) {
            case 0: {
                item->setTextAlignment(0, Qt::AlignLeft | Qt::AlignVCenter);
                item->setData(0, Qt::UserRole, QPixmap("../imgs/icons/nottalking.png"));
                item->setTextAlignment(1, Qt::AlignRight | Qt::AlignVCenter);
                item->setData(1, Qt::DecorationRole, QPixmap("../imgs/icons/nottalking.png").scaled(QSize(15, 15), Qt::KeepAspectRatio));
                int imageWidth, imageHeight;
                item->setSizeHint(1, QSize(imageWidth, imageHeight).scaled(QSize(15, 15), Qt::KeepAspectRatio));
                ui->treeWidget->setColumnWidth(1, 15);
                break;
            }
            case 1: {
                QChar first = name.at(0);
                if(name.contains(first)) {
                    name = QString(first).repeated(30);
                }
                //item->setData(0, Qt::TextWordWrap, QVariant(Qt::TextWrapAnywhere));
                break;
            }
        }




        //item->setTextAlignment(0, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextFlag::TextWrapAnywhere);
        switch (type) {
            //case 0: item->setIcon(0, QIcon("../imgs/icons/nottalking.png")); break;
            case 0: {
                item->setIcon(0, QIcon("../imgs/icons/nottalking.png"));
                item->setTextAlignment(0, Qt::AlignLeft | Qt::AlignVCenter);
                item->setTextAlignment(1, Qt::AlignRight | Qt::AlignVCenter);
                item->setData(1, Qt::DecorationRole, QPixmap("../imgs/icons/nottalking.png").scaled(QSize(15, 15), Qt::KeepAspectRatio));
                item->setSizeHint(1, QSize(imageWidth, imageHeight).scaled(QSize(15, 15), Qt::KeepAspectRatio));
                ui->treeWidget->setColumnWidth(1, 15);
                break;
            }
            case 2: {

                    if(json_obj.value("password").toString().length() > 2) {
                        item->setIcon(0, QIcon("../imgs/icons/891399_30.png"));
                    } else {
                        item->setIcon(0, QIcon("../imgs/icons/2058142_30.png"));
                    }
                    break;
            }
            case 3: item->setIcon(0, QIcon("../imgs/icons/7183999_30.png")); break;
        }
        if (json_obj.contains("children")) {
            QJsonArray children = json_obj.value("children").toArray();
            populateTreeWidget(item, children);
        }
        ui->treeWidget->addTopLevelItem(item);
        //ui->treeWidget->setColumnWidth(1, imageWidth);
        item->setSizeHint(1, QSize(15, 15));
        ui->treeWidget->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    }
}

void MainWindow::populateTreeWidget(QTreeWidgetItem* parentItem, const QJsonArray& json_array) {
    for (const QJsonValue& json_value : json_array) {
        QJsonObject json_obj = json_value.toObject();
        QString name = json_obj.value("name").toString();
        int type = json_obj.value("type").toInt();
        QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
        //item->setFlags(item->flags() | Qt::ItemIsTristate);
        item->setText(0, name);
        switch (type) {
            case 0: item->setIcon(0, QIcon("../imgs/icons/nottalking.png")); break;
            //case 1: item->setIcon(0, QIcon("../imgs/icons/online_s.png")); break;
            case 2: {

                    if(json_obj.value("password").toString().length() > 2) {
                        item->setIcon(0, QIcon("../imgs/icons/891399_30.png"));
                    } else {
                        item->setIcon(0, QIcon("../imgs/icons/2058142_30.png"));
                    }
                    break;
            }
            case 3: item->setIcon(0, QIcon("../imgs/icons/7183999_30.png")); break;

        }
        if (json_obj.contains("children")) {
            QJsonArray children = json_obj.value("children").toArray();
            populateTreeWidget(item, children);
        }
    }
    ui->treeWidget->setColumnWidth(1, 15);
}

void MainWindow::on_actionQuit_triggered() { this->close(); }
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


void MainWindow::on_textBox_returnPressed()
{
    QString message = ui->textBox->text();
    if (message.length() <= 0)
        return;

    bool containsNonSpaceChar = false;

    for (int i = 0; i < message.length(); i++) {
        if (!message[i].isSpace()) {
            containsNonSpaceChar = true;
            break;
        }
    }

    if (!containsNonSpaceChar)
        return;

    QDateTime current_time = QDateTime::currentDateTime();
    QString formatted_time = current_time.toString("hh:mm:ss");

    QString time = "[" + formatted_time + "] ";
    QString role = "(Admin) ";
    QString username = "ilyasNPC: ";

    QTextCharFormat format;
    QTextCursor cursor = ui->chatLog->textCursor();

    cursor.movePosition(QTextCursor::End);

    format.setFontWeight(QFont::Bold);
    format.setForeground(QColor("#2B2BFF"));
    cursor.setCharFormat(format);
    cursor.insertText(time);

    format.setFontWeight(QFont::Normal);

    format.setForeground(QColor("#55AA2B"));
    cursor.setCharFormat(format);
    cursor.insertText(role);

    format.setForeground(QColor("#FFAA00"));
    cursor.setCharFormat(format);
    cursor.insertText(username);

    format.setForeground(QColor("#5A5A5A"));
    cursor.setCharFormat(format);
    cursor.insertText(message);

    cursor.insertBlock();

    ui->textBox->clear();
}

