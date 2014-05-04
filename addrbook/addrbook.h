#ifndef ADDRBOOK_H
#define ADDRBOOK_H

#include <QMainWindow>
#include <QTableWidget>
#include "hash.h"
#include "addrdialog.h"
#include "ui_addrbook.h"

namespace Ui {
class addrbook;
}

class addrbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit addrbook(QWidget *parent = 0);
    ~addrbook();
    void Show();

public slots:
    void Load();
    void Save();
    void Search();
    void Insert();
    void Create();
    void Close();
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::addrbook *ui;
};

#endif // ADDRBOOK_H
