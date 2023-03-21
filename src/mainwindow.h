#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTreeWidget>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populate();
    void populateTreeWidget(QTreeWidgetItem* parentItem, const QJsonArray& json_array);
    //void fillTreeWidget(QTreeWidget* treeWidget, QByteArray json_data);
    //void fillTreeWidgetRecursively(QTreeWidgetItem* parentItem, const QJsonArray& childrenArray);

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionConnect_triggered();

    void on_textBox_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
