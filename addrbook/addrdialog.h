#ifndef ADDRDIALOG_H
#define ADDRDIALOG_H

#include <QDialog>

namespace Ui {
class AddrDialog;
}

class AddrDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddrDialog(QWidget *parent = 0);
    ~AddrDialog();
    QString getName();
    QString getNum();
    QString getAddr();

public slots:
     void Submit();
     void Cancel();

private:
    Ui::AddrDialog *ui;
};

#endif // ADDRDIALOG_H
