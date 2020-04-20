#include "Widget.h"
#include "ui_Widget.h"
#include <QFileDialog>
#include <QTextCodec>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pBtn_File, SIGNAL(clicked(bool)), this, SLOT(onOpenFile()));
}

Widget::~Widget()
{
    delete ui;
}

#include <QDebug>
void Widget::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite))
    {
        return;
    }
    QByteArray arr = file.readAll();
    file.close();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

//    QString arr = QString::fro file.readAll();
    QStringList listArr = string.split("\n");

    QList<SData> vecData;
    int equalCount = 0;
    for (int i=3; i < listArr.size(); i++)
    {
        QString rec = listArr.at(i);
        QStringList strList = listArr.at(i).split(",");
        if (strList.size() >= 39)
        {
            SData data;
            data.row = i;
            data.M = strList.at(12);
            data.S = strList.at(18);
            data.Y = strList.at(24);
            data.AF = strList.at(31);
            data.AJ = strList.at(35);
            data.AK = strList.at(36);
            data.data = listArr.at(i);
            data.checked = false;
            data.equalRow = -1;
            data.isDelete = false;
            if (vecData.contains(data))
            {
                data.checked = true;
                int index = vecData.indexOf(data);
                data.equalRow = vecData[index].row;
                equalCount++;
                QString log;
                qDebug()<<QString::fromLocal8Bit("重复：%1行和%2行").arg(vecData[index].row+1).arg(data.row+1);
                log = QString::fromLocal8Bit("重复：%1行和%2行").arg(vecData[index].row+1).arg(data.row+1);
                if (vecData[index].isEmpry() && !data.isEmpry())
                {
                   qDebug()<<QString::fromLocal8Bit("%1行待删除").arg(index+3+1);
                   log += QString::fromLocal8Bit(" %1行待删除").arg(index+3+1);
                   vecData.removeAt(index);
                }
                else if (!vecData[index].isEmpry() && data.isEmpry())
                {
                   qDebug()<<QString::fromLocal8Bit("%1行待删除").arg(data.row+1);
                   log += QString::fromLocal8Bit("%1行待删除").arg(data.row+1);
                   continue;
                }
                else if (!vecData[index].isEmpry() && !data.isEmpry())
                {
                    qDebug()<<QString::fromLocal8Bit("两行均有数据");
                    log += QString::fromLocal8Bit("两行均有数据");
                }
                else if(vecData[index].isEmpry() && data.isEmpry())
                {
                    qDebug()<<QString::fromLocal8Bit("两行均无数据");
                    log += QString::fromLocal8Bit("两行均无数据");
                    continue;
                }
                ui->textEdit->append(log);
                qDebug()<<"count"<<equalCount<<i;
            }
            vecData.push_back(data);
        }
    }
    QFile out("out.csv");
    if (!out.open(QIODevice::ReadWrite))
    {
        qDebug()<<"open failed";
        return;
    }
    if (listArr.size() >=3)
    {
        out.write(listArr.at(0).toLocal8Bit());
        out.write(listArr.at(1).toLocal8Bit());
        out.write(listArr.at(2).toLocal8Bit());
    }
    for (int i=0; i < vecData.size(); i++)
    {
        out.write(vecData.at(i).data.toLocal8Bit());
    }
    out.close();
}
