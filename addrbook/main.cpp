#include "addrbook.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

  //  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
  //  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
  //  QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    addrbook w;
    w.show();

    return a.exec();
}
