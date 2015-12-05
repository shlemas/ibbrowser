#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    ui->webView->load(QUrl("http://www.google.com/"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
