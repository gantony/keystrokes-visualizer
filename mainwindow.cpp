#include "mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QFrame>
#include <QListView>
#include <QApplication>
#include <QCheckBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGroupBox>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGroupBox * masterBox = new QGroupBox(this);
    QGroupBox * listGroup = new QGroupBox();

    model = new Model(this);

    QApplication::instance()->installEventFilter(model);

    QCheckBox *checkbox = new QCheckBox("Limit to 30?");
    QListView *lv = new QListView();

    resize(800, 800);
    listGroup->resize(150, 500);
    lv->resize(150, 400);
    lv->move(0, 30);

    lv->setModel(model);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(checkbox);
    vbox->addWidget(lv);
    vbox->addStretch(1);
    listGroup->setLayout(vbox);

    connect(checkbox, &QCheckBox::stateChanged, this, &MainWindow::onCbStateChanged);



    QGraphicsScene*  scene = new QGraphicsScene;
    scene->addText("Hello, world!");

    QGraphicsView * view = new QGraphicsView(scene);
    view->resize(500, 200);



    //Create the layout.
    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    //Add widgets to the layout.
    horizontalLayout->addWidget(listGroup);
    horizontalLayout->addWidget(view);

    masterBox->setLayout(horizontalLayout);

    masterBox->resize(800, 800);


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
