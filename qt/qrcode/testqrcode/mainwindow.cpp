#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQuickWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QQuickWidget *view = new QQuickWidget;
    view->setGeometry(0, 0, 640, 480);
    view->setSource(QUrl("qrc:/qml/qrcodereader.qml"));
    ui->verticalLayout->addWidget(view, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
