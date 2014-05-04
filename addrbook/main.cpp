#include "addrbook.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);

    addrbook w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground, true);
//    w.setStyleSheet("background:rgba(0,0,0,0);");
    w.show();

    return a.exec();
}
