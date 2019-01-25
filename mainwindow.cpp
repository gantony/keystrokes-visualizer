#include "mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QFrame>
#include <QListView>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new Model(this);

    QApplication::instance()->installEventFilter(model);

    QListView *lv = new QListView(this);

    resize(150, 400);
    lv->resize(150, 400);

    lv->setModel(model);
}

MainWindow::~MainWindow()
{

}

