#include "addrbook.h"
#include "ui_addrbook.h"
#include "hash.h"
#include <qmessagebox.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QTextCodec>
HashTable HashTable(40);

addrbook::addrbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addrbook)
{
    ui->setupUi(this);



    //界面属性预处理
    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->setRowCount(7);     //设置行数为10
    tableWidget->setColumnCount(3);   //设置列数为3
    tableWidget->setWindowTitle("QTableWidget & Item");
    tableWidget->resize(412, 230);  //设置表格
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
    tableWidget->setShowGrid(false);//不显示表格线
    tableWidget->setAlternatingRowColors(true);//隔行显示颜色
    tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    QHeaderView *headerView = tableWidget->horizontalHeader();
    headerView->resizeSection(0,78);//设置第一列宽
    headerView->resizeSection(1,110);//设置第二列宽
    headerView->resizeSection(2,205);//设置第三列宽
    headerView->setSectionResizeMode(QHeaderView::Fixed);//列表不能移动
    QStringList header;//表头
    header<<QStringLiteral("姓名")<<QStringLiteral("电话号码")<<QStringLiteral("地址");
    tableWidget->setHorizontalHeaderLabels(header);

    //事件监听处理
    connect(ui->LoadButton,SIGNAL(clicked()),this,SLOT(Load()));
    connect(ui->SaveButton,SIGNAL(clicked()),this,SLOT(Save()));
    connect(ui->InsertButton,SIGNAL(clicked()),this,SLOT(Insert()));
    connect(ui->SearchButton,SIGNAL(clicked()),this,SLOT(Search()));
    connect(ui->CreateButton,SIGNAL(clicked()),this,SLOT(Create()));;
 //   Load(tableWidget);

    Show();
}

addrbook::~addrbook()
{
    delete ui;
}
void addrbook::Show(){
    //表格显示
    int cntItem = 0 ;
    QString Name, Num, Addr,Key;
    for(int i=0;i<HashTable.getSize();i++)
        if(HashTable.table[i]!=NULL)
        {
            Name = QString::fromStdString(HashTable.table[i]->getName());
            Num = QString::fromStdString(HashTable.table[i]->getNum());
            Addr = QString::fromStdString(HashTable.table[i]->getAddr());
            Key = QString::number(i);

            QTableWidgetItem *NameItem = new QTableWidgetItem(Name);
            QTableWidgetItem *NumItem = new QTableWidgetItem(Num);
            QTableWidgetItem *AddrItem = new QTableWidgetItem(Addr);

            NameItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            NumItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
     //     AddrItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

            ui->tableWidget->setItem(cntItem,0,NameItem);
            ui->tableWidget->setItem(cntItem,1,NumItem);
            ui->tableWidget->setItem(cntItem,2,AddrItem);
            cntItem ++ ;
        }
}

void addrbook::Create()
{
    QMessageBox::information(NULL,QStringLiteral("提示"),QStringLiteral("新建成功!          "), QMessageBox::Ok);
    HashTable.Destroy();//清空哈希表
    ui->tableWidget->clearContents ();
}

void addrbook::Load()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(QStringLiteral("加载记录文件"));
    fileDialog->setDirectory(".");
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString LoadPath = fileDialog->selectedFiles()[0];;
        HashTable.Destroy();//清空哈希表
        QFile *file=new QFile(LoadPath);
        file->open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream stream(file);
        QString Name, Num, Addr;

        while(!stream.atEnd())
        {
            stream>>Name;
            stream>>Num;
            stream>>Addr;
            if(!Name.isEmpty()&&!Num.isEmpty()&&!Addr.isEmpty())
                HashTable.Insert(Name.toStdString(),Num.toStdString(),Addr.toStdString());
        }
        file->close();
        QMessageBox::information(NULL,QStringLiteral("提示"),QStringLiteral("读取文件成功!          "), QMessageBox::Ok);
        int RowCount = HashTable.getCnt();
        ui->tableWidget->setRowCount(RowCount);
        Show();
    }
}

void addrbook::Save()
{
    QString SavePath = QFileDialog::getSaveFileName(this,
            QStringLiteral("保存记录"),
            "",
            tr("Text Files (*.txt)"));

    QFile *file = new QFile(SavePath);
    file->open(QIODevice::WriteOnly);
    file->close();

    file->open(QIODevice::WriteOnly|QIODevice::Text);
    if ( file->isOpen() )
    {
        QTextStream stream(file);
        QString Name, Num, Addr;
        for(int i=0;i<HashTable.getSize();i++)
            if(HashTable.table[i]!=NULL)
            {
               Name = QString::fromStdString(HashTable.table[i]->getName());
               Num = QString::fromStdString(HashTable.table[i]->getNum());
               Addr = QString::fromStdString(HashTable.table[i]->getAddr());
               stream<<Name<<" ";
               stream<<Num<<" ";
               stream<<Addr<<" ";
               stream<<endl;
            }
       QMessageBox::information(NULL,QStringLiteral("提示"), QStringLiteral("保存成功"),QMessageBox::Ok);
    }

}

void addrbook::Insert()
{
    AddrDialog dialog;
    if(dialog.exec() == QDialog::Accepted)
    {
        QString Name = dialog.getName();
        QString Num = dialog.getNum();
        QString Addr = dialog.getAddr();
        HashTable.Insert(Name.toStdString(),Num.toStdString(),Addr.toStdString());
        int RowCount = HashTable.getCnt();
        ui->tableWidget->setRowCount(RowCount);
        Show();
        QMessageBox::information(NULL,QStringLiteral("提示"), QStringLiteral("添加成功!"), QMessageBox::Ok);
    }
}

void addrbook::Search(){
   QString Name,Num,Addr;
   QString SearchNum ;
   int key=0 ;
       SearchNum = ui->SearchInput->text();
       if(SearchNum.isEmpty())
           QMessageBox::warning(NULL,QStringLiteral("提示"),QStringLiteral("   请输入查找号码! "), QMessageBox::Ok);
       else{
            key = HashTable.Search(SearchNum.toStdString());
            if(key == -1){
                QMessageBox::warning(NULL,QStringLiteral("提示"),QStringLiteral("   找不到该号码!  "), QMessageBox::Ok);
            }
            else{
                Name = QString::fromStdString(HashTable.table[key]->getName());
                Num = QString::fromStdString(HashTable.table[key]->getNum());
                Addr = QString::fromStdString(HashTable.table[key]->getAddr());
                QString SearchInfo = Num + QStringLiteral("  的信息:    ") + "\n"
                    + QStringLiteral("姓名：     ") + Name + "               \n"
                    + QStringLiteral("号码：     ") + Num + "                 \n"
                    + QStringLiteral("地址：     ") + Addr +"               " ;
                QMessageBox::information(NULL,QStringLiteral("提示"),SearchInfo, QMessageBox::Ok);

            }
       }
}


