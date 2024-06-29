#include "mainwindow.h"
#include"login.h"
#include"user.h"
#include"listenapp.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    listenapp w;
    return a.exec();
}
