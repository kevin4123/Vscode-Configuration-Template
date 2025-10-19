#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 连接按钮点击事件
    connect(ui->pushButton, &QPushButton::clicked, this, [] {
        QMessageBox::information(nullptr, "Hello", "Hello, World!");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
