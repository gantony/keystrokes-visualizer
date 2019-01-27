#include "mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QFrame>
#include <QListView>
#include <QApplication>
#include <QCheckBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new Model(this);

    QApplication::instance()->installEventFilter(model);

    QCheckBox *checkbox = new QCheckBox("Limit to 30?", this);
    QListView *lv = new QListView(this);

    resize(150, 450);
    lv->resize(150, 400);
    lv->move(0, 30);

    lv->setModel(model);

    connect(checkbox, &QCheckBox::stateChanged, this, &MainWindow::onCbStateChanged);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onCbStateChanged(int state)
{
    if (state == Qt::Checked) {
        model->limitToLast(30);
    } else {
        model->showEverything();
    }
}
