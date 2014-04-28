#include "addrdialog.h"
#include "ui_addrdialog.h"
#include <QMessageBox>

AddrDialog::AddrDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddrDialog)
{
    ui->setupUi(this);
    connect(ui->SubmitButton,SIGNAL(clicked()),this,SLOT(Submit()));
    connect(ui->CancelButton,SIGNAL(clicked()),this,SLOT(Cancel()));
    setWindowTitle(tr("添加记录"));
}

AddrDialog::~AddrDialog()
{
    delete ui;
}

void AddrDialog::Submit()
{
    QString Name = ui->NameInput->text();
    QString Num = ui->NumInput->text();
    QString Addr = ui->AddrInput->text();

    if(Name.isEmpty())
    {
        QMessageBox::information(this,tr("添加错误"),
        tr("请输入姓名!"));
    }
    else if(Num.isEmpty())
    {
        QMessageBox::information(this,tr("添加错误"),
        tr("请输入号码!"));
    }
    else if(Addr.isEmpty())
    {
        QMessageBox::information(this,tr("添加错误"),
        tr("请输入地址!"));
    }
    else{
        accept();
    }
}

void AddrDialog::Cancel()
{
    reject();
}

QString AddrDialog::getName()
{
    return ui->NameInput->text();
}

QString AddrDialog::getNum()
{
    return ui->NumInput->text();
}

QString AddrDialog::getAddr()
{
    return ui->AddrInput->text();
}
