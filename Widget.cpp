#include "widget.h"
#include "ui_widget.h"

QList<int> g_keyList;
QList<int> g_dataList;


QHash<QString, int> g_hashColumn;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    ui->progressBar_Split->setMaximum(100);
    ui->progressBar_Split->setMinimum(0);
    ui->progressBar_Split->setValue(0);

    ui->progressBar_Compare->setMaximum(100);
    ui->progressBar_Compare->setMinimum(0);
    ui->progressBar_Compare->setValue(0);

    ui->lineEdit_SortColumn->setText("AF;AJ;AK");
    ui->lineEdit_DataColumn->setText("M;S;Y");
    ui->lineEdit_Out->setText("out.csv");

    ui->lineEdit_FolderSplit->setText("A;B");
    ui->lineEdit_TableSplit->setText("A;B;D");
    ui->lineEdit_Split->setText("_");

    ui->lineEdit_Name1->setText("A");
    ui->lineEdit_SAP1->setText("O;U;AA;AK");
    ui->lineEdit_Name2->setText("L");
    ui->lineEdit_SAP2->setText("C");
    initHash();
    connect(ui->pBtn_SelectFile, SIGNAL(clicked(bool)), this, SLOT(onSelectFile()));
    connect(ui->pBtn_SelectSplitFile, SIGNAL(clicked(bool)), this, SLOT(onSelectSplitFile()));
    connect(ui->pBtn_Proc, SIGNAL(clicked(bool)), this, SLOT(onProc()));
    connect(ui->pBtn_Split, SIGNAL(clicked(bool)), this, SLOT(onSplit()));

    connect(ui->pBtn_SelectFile1, SIGNAL(clicked(bool)), this, SLOT(onSelectFile1()));
    connect(ui->pBtn_SelectFile2, SIGNAL(clicked(bool)), this, SLOT(onSelectFile2()));
    connect(ui->pBtn_Compare, SIGNAL(clicked(bool)), this, SLOT(onCompare()));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onTest()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onClicked()
{
//    QString fileName = QFileDialog::getOpenFileName(this);
//    if (fileName.isEmpty())
//    {
//        qDebug()<<"file is empty";
//        return;
//    }
//    QFile file(fileName);
//    if (!file.open(QIODevice::ReadOnly))
//    {
//        qDebug()<<"open file failed";
//        return;
//    }
//    QByteArray arr = file.readAll();
//    QTextCodec *codec = QTextCodec::codecForName("GB18030");
//    QString string = codec->toUnicode(arr);

//    QList<SData> listData;
//    QStringList list = string.split("\n");
//    for (int i=3; i < list.size(); i++)
//    {
//        SData data;
//        QString tmp = list.at(i);
//        QStringList rec = tmp.split(",");
//        if (rec.size() >= 39)
//        {
//           data.row = i;
//           data.M = rec.at(12) ;
//           data.S = rec.at(18);
//           data.Y = rec.at(24);
//           data.AF = rec.at(31);
//           data.AJ = rec.at(35);
//           data.AK = rec.at(36);
//           data.data = tmp;
//           data.isChecked = false;

//           int index = listData.indexOf(data);
//           if (index!= -1)
//           {
//               if (data.isEmpty() && listData.at(index).isEmpty())
//               {
//                   qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，均无数据，不追加").arg(listData.at(index).row+1).arg(data.row+1);
//                   continue;
//               }
//               else if (!data.isEmpty() && !listData.at(index).isEmpty())
//               {
//                   qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，均有数据").arg(listData.at(index).row+1).arg(data.row+1);
//               }
//               else if (data.isEmpty() && !listData.at(index).isEmpty())
//               {
//                   qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，前有数据，后无数据，不追加").arg(listData.at(index).row+1).arg(data.row+1);
//                   continue;
//               }
//               else if (!data.isEmpty() && listData.at(index).isEmpty())
//               {
//                   qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，前无数据，后有数据，删前者，追加").arg(listData.at(index).row+1).arg(data.row+1);
//                   listData.removeAt(index);
//               }
//           }
//        }
//        listData.push_back(data);
//    }

//    for (int i=0; i < listData.size(); i++)
//    {
//        for (int j=0; j < listData.size(); j++)
//        {
//            if (i == j)
//            {
//                continue;
//            }
//            if (listData.at(i).isChecked)
//            {
//                continue;
//            }
//            if (listData.at(i) == listData.at(j))
//            {
//                listData[i].data.replace("\r", "");
//                listData[i].data += ",";
//                listData[i].data += QString/*::fromLocal8Bit*/("重复");
//                listData[i].data += ",";
//                listData[i].data += QString/*::fromLocal8Bit*/("与%1行重复").arg(j+3+1);
//                listData[i].data += "\r";
//            }
//        }
//        listData[i].isChecked = true;
//        qDebug()<<"check"<<i;
//    }

//    QFile out("out.csv");
//    if (!out.open(QIODevice::ReadWrite))
//    {
//        qDebug()<<"open out file failed!";
//        return;
//    }
//    if (list.size() >=3)
//    {
//        out.write(list.at(0).toLocal8Bit());
//        out.write(list.at(1).toLocal8Bit());
//        out.write(list.at(2).toLocal8Bit());
//    }
//    for (int i=0; i < listData.size(); i++)
//    {
//        out.write(listData.at(i).data.toLocal8Bit());
//    }
//    file.close();
}

void Widget::onSelectFile()
{
    m_inFile = QFileDialog::getOpenFileName(this);
    if (m_inFile.isEmpty())
    {
        qDebug()<<"fileName is empty";
        ui->lineEdit_FileName->setText("");
        return;
    }
    ui->lineEdit_FileName->setText(m_inFile);
}

void Widget::onProc()
{
    ui->progressBar->setValue(0);
    if (!checkInput())
    {
        return;
    }

    QFile file(m_inFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open file failed";
        return;
    }
    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

    QList<SData> listData;
    QMap<SData, int> hashData;
    QStringList list = string.split("\n");
    for (int i=3; i < list.size(); i++)
    {
        ui->progressBar->setValue(50*i/list.size());
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > g_keyList.last())
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.isChecked = false;

            if (data.isValidKey())
            {
                QMap<SData, int>::iterator ite = hashData.find(data);
                if (ite != hashData.end())
                {
                    int row = ite.value();

                    if (data.isEmpty() && ite.key().isEmpty())
                    {
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，均无数据，不追加").arg(row+1).arg(data.row+1);
//                        ui->textEdit->append(QString/*::fromLocal8Bit*/("重复：行%1和行%2，均无数据，不追加").arg(row+1).arg(data.row+1));
                        continue;
                    }
                    else if (!data.isEmpty() && !ite.key().isEmpty())
                    {
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，均有数据").arg(row+1).arg(data.row+1);
                        ui->textEdit->append(QString/*::fromLocal8Bit*/("重复：行%1和行%2，均有数据").arg(row+1).arg(data.row+1));
                    }
                    else if (data.isEmpty() && !ite.key().isEmpty())
                    {
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，前有数据，后无数据，不追加").arg(row+1).arg(data.row+1);
                        continue;
                    }
                    else if (!data.isEmpty() && ite.key().isEmpty())
                    {
                        int index = listData.indexOf(data);
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，前无数据，后有数据，删前者，追加").arg(row+1).arg(data.row+1);
                        listData.removeAt(index);
                    }
                }
                else
                {
                    hashData.insert(data, data.row);
                }
            }
            listData.push_back(data);
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(g_keyList.last());
        }

    }


    hashData.clear();
    //输出至文件
    for (int i=0; i < listData.size(); i++)
    {
        ui->progressBar->setValue(50+50*i/listData.size());
        QApplication::processEvents();
        QMap<SData, int>::iterator ite = hashData.find(listData.at(i));
        if (ite != hashData.end())
        {
            for (int j=0; j < listData.size(); j++)
            {
//                qDebug()<<"cycle"<<i;
                if (i == j)
                {
                    continue;
                }
                if (listData.at(i).isChecked)
                {
                    continue;
                }
                if (listData.at(i) == listData.at(j))
                {

                    listData[i].data.replace("\r", "");
                    listData[i].data += ",";
                    listData[i].data += QString/*::fromLocal8Bit*/("重复");
                    listData[i].data += ",";
                    listData[i].data += QString/*::fromLocal8Bit*/("与%1行重复").arg(j+3+1);
                    listData[i].data += "\r";

                    listData[j].data.replace("\r", "");
                    listData[j].data += ",";
                    listData[j].data += QString/*::fromLocal8Bit*/("重复");
                    listData[j].data += ",";
                    listData[j].data += QString/*::fromLocal8Bit*/("与%1行重复").arg(i+3+1);
                    listData[j].data += "\r";
                }
            }
        }
        else
        {
          hashData.insert(listData.at(i), i);
        }
        listData[i].isChecked = true;
        qDebug()<<"check"<<i;
    }

    QString outFile = ui->lineEdit_Out->text();
    QFile out(outFile);
    if (!out.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open out file failed!";
        return;
    }
    if (list.size() >=3)
    {
        out.write(list.at(0).toLocal8Bit());
        out.write(list.at(1).toLocal8Bit());
        out.write(list.at(2).toLocal8Bit());
    }
    for (int i=0; i < listData.size(); i++)
    {
        out.write(listData.at(i).data.toLocal8Bit());
    }
    ui->progressBar->setValue(100);
    file.close();
    qDebug()<<"done!";
}

void Widget::onSelectSplitFile()
{
    m_inSplitFile = QFileDialog::getOpenFileName(this);
    if (m_inSplitFile.isEmpty())
    {
        qDebug()<<"split fileName is empty";
        ui->lineEdit_FileNameSplit->setText("");
        return;
    }
    ui->lineEdit_FileNameSplit->setText(m_inSplitFile);
}

void Widget::onSplit()
{
    ui->progressBar_Split->setValue(0);
    if (!checkSplit())
    {
        return;
    }

    QFile file(m_inSplitFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open split file failed";
        return;
    }
    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);
    file.close();

    QMap<QString, QHash<QString, QList<SData> > > hashData;//文件夹-表-记录
    QStringList list = string.split("\n");
    for (int i=3; i < list.size(); i++)
    {
        ui->progressBar_Split->setValue(100*i/list.size());
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > g_keyList.last())
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.isChecked = false;

            QString folderName;
            for (int j=0; j < g_keyList.size(); j++)
            {
                if (j >= data.list.size())
                {
                    qDebug()<<"err onSplit";
                    continue;
                }
                if (j > 0 && !folderName.isEmpty())
                {
                    folderName += m_splitSymbol;
                }
                folderName += data.list.at(g_keyList.at(j));
            }

            QString tableName;
            for (int j=0; j < g_dataList.size(); j++)
            {
                if (j >= data.list.size())
                {
                    qDebug()<<"err onSplit";
                    continue;
                }
                if (j > 0 && !tableName.isEmpty())
                {
                    tableName += m_splitSymbol;
                }
                tableName += data.list.at(g_dataList.at(j));
            }

            QMap<QString, QHash<QString, QList<SData> > >::iterator ite = hashData.find(folderName);
            if (ite == hashData.end())
            {
                QHash<QString, QList<SData> > hashTmp;
                QList<SData> list;
                list.append(data);
                hashTmp.insert(tableName, list);
                hashData.insert(folderName, hashTmp);
            }
            else
            {
                QHash<QString, QList<SData> >::iterator iteTable = ite.value().find(tableName);
                if (iteTable == ite.value().end())
                {
                    QList<SData> list;
                    list.append(data);
                    ite.value().insert(tableName, list);
                }
                else
                {
                    iteTable.value().push_back(data);
                }
            }
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(g_keyList.last());
        }

    }

    //遍历输出文件
    QMap<QString, QHash<QString, QList<SData> > >::iterator iteFolder = hashData.begin();
    for ( ;iteFolder != hashData.end(); iteFolder++)
    {
        QString folderName = iteFolder.key();
        QString path = QDir::currentPath() + "/" + folderName;
        QDir dir(path);
        if (!dir.exists())
        {
            bool ok = dir.mkpath(path);
            if (!ok)
            {
                qDebug()<<QString("mkdir %1 fail!").arg(path);
                continue;
            }
        }

        QHash<QString, QList<SData> >::iterator iteTable = iteFolder.value().begin();
        for ( ;iteTable != iteFolder.value().end(); iteTable++)
        {
            QString outFile = dir.absolutePath()+"/" + iteTable.key() + ".csv";
            QFile out(outFile);
            if (!out.open(QIODevice::ReadWrite | QIODevice::Truncate))
            {
                qDebug()<<"open out file failed!";
                return;
            }
            if (list.size() >=3)
            {
                out.write(list.at(0).toLocal8Bit());
                out.write(list.at(1).toLocal8Bit());
                out.write(list.at(2).toLocal8Bit());
            }
            for (int i=0; i < iteTable.value().size(); i++)
            {
                out.write(iteTable.value().at(i).data.toLocal8Bit());
            }
			out.close();
        }
    }
    ui->progressBar_Split->setValue(100);
}

void Widget::onCompare()
{
    ui->progressBar_Compare->setValue(0);
    QFile file(m_file1);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open m_file1 file failed";
        return;
    }
    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

    file.close();

    QList<int> listSAP;
    QString SAP1 = ui->lineEdit_SAP1->text();
    SAP1.replace("；",";");

    QStringList sap1List = SAP1.split(";");

    for (int i=0; i < sap1List.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(sap1List.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的匹配列:%1！").arg(sap1List.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return;
        }
        listSAP.push_back(ite.value());
    }

    QList<int> outColumnlist;
    QString outColumn = ui->lineEdit_OutColumn->text();
    outColumn.replace("；",";");

    QStringList outList = outColumn.split(";");

    for (int i=0; i < outList.size(); i++)
    {
		QHash<QString, int>::iterator ite = g_hashColumn.find(outList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的输出列:%1！").arg(outList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return;
        }
        outColumnlist.push_back(ite.value());
    }

    int nameCol1 = -1;
    QHash<QString, int>::iterator ite = g_hashColumn.find(ui->lineEdit_Name1->text());
    if (ite == g_hashColumn.end())
    {
        QString err = QString/*::fromLocal8Bit*/("未识别的名字列1！");
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
        return;
    }
    nameCol1 = ite.value();

    int nameCol2 = -1;
    ite = g_hashColumn.find(ui->lineEdit_Name2->text());
    if (ite == g_hashColumn.end())
    {
        QString err = QString/*::fromLocal8Bit*/("未识别的名字列2！");
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
        return;
    }
    nameCol2 = ite.value();
    int SAP2 = -1;
    ite = g_hashColumn.find(ui->lineEdit_SAP2->text());
    if (ite == g_hashColumn.end())
    {
        QString err = QString/*::fromLocal8Bit*/("未识别的名字列2！");
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
        return;
    }
    SAP2 = ite.value();
//    g_keyList.clear();
//    g_keyList.push_back(nameCol2);
//    g_keyList.push_back(SAP2);


    ui->progressBar_Compare->setValue(1);
    QList<SData> listData1;
    QStringList list = string.split("\n");
    for (int i=3; i < list.size(); i++)
    {
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > listSAP.last())
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.isChecked = false;
            listData1.push_back(data);
        }
        else
        {
            qDebug()<<QString("row %1< %2").arg(i+1).arg(listSAP.last());
        }
    }
    ui->progressBar_Compare->setValue(5);


    //读取file2
    QFile file2(m_file2);
    if (!file2.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open m_file2 file failed";
        return;
    }
    QByteArray arr2 = file2.readAll();
    QTextCodec *codec2 = QTextCodec::codecForName("GB18030");
    QString string2 = codec2->toUnicode(arr2);

    QList<SData> listData2;
//    QMap<SData, int> mapData;
    string2.replace("\r", "");
    QStringList list2 = string2.split("\n");
    QHash<QString, SCompare> hashData;
    for (int i=1; i < list2.size(); i++)
    {
        ui->progressBar_Compare->setValue(5+5*i/list2.size());
        SData data;
        QString tmp = list2.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > (nameCol2>SAP2?nameCol2:SAP2))
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.isChecked = false;
            listData2.push_back(data);
            QHash<QString, SCompare>::iterator ite = hashData.find(data.list.at(nameCol2));
            if (ite == hashData.end())
            {
                SCompare com;
                com.exist = false;
                com.list.push_back(data);
                hashData.insert(data.list.at(nameCol2), com);
            }
            else
            {
                ite.value().list.push_back(data);
            }
//            mapData.insert(data, i-1);//list的index
        }
        else
        {
            qDebug()<<QString("row %1< %2").arg(i+1).arg((nameCol2>SAP2?nameCol2:SAP2));
        }
    }
    file2.close();

    ui->progressBar_Compare->setValue(11);
    //交叉比对

    for (int i=0; i < listData1.size(); i++)
    {
        ui->progressBar_Compare->setValue(11+80*i/listData1.size());
        QApplication::processEvents();
        for (int j=0; j < listSAP.size(); j++)
        {
            SData data = listData1.at(i);
            QString name = listData1.at(i).list.at(nameCol1);
			QHash<QString, SCompare>::iterator ite = hashData.find(name);
            if (ite == hashData.end())
            {
                qDebug()<<"table 1 exist, table2 not exist!";
                if (!listData1[i].data.contains(QString/*::fromLocal8Bit*/("未匹配到名字")))
                {
					listData1[i].data.replace("\r", "");
                    listData1[i].data += ",";
                    listData1[i].data += QString/*::fromLocal8Bit*/("未匹配到名字");
                    listData1[i].data += "\r";
                }
//                listData1[i].data += ",";
//                listData1[i].data += QString/*::fromLocal8Bit*/("第%1个SAP").arg(j+1);
//                listData1[i].data += "\r";
            }
            else
            {
                ite.value().exist = true;
                bool exist = false;
                QString sap = listData1.at(i).list.at(listSAP.at(j));
                if (sap.isEmpty())
                {
                    continue;
                }
                for (int k=0; k < ite.value().list.size(); k++)
                {
                    if (ite.value().list.at(k).list.at(SAP2) == listData1.at(i).list.at(listSAP.at(j)))
                    {
                        ite.value().list[k].isChecked = true;
                        listData2[ite.value().list[k].row-1].isChecked = true;
                        exist = true;
                        break;
                    }
                }
                if (!exist)
                {
                    listData1[i].data.replace("\r", "");
                    if (!listData1[i].data.contains(QString/*::fromLocal8Bit*/("未匹配")))
                    {
                        listData1[i].data += ",";
                        listData1[i].data += QString/*::fromLocal8Bit*/("未匹配");
                    }
                    listData1[i].data += ",";
                    listData1[i].data += QString/*::fromLocal8Bit*/("第%1个SAP").arg(j+1);
                    listData1[i].data += "\r";
                }
            }
//            data.list[nameCol2] = listData1.at(i).list.at(nameCol1);
//            data.list[SAP2] = listData1.at(i).list.at(listSAP.at(j));
//            QMap<SData, int>::iterator ite = mapData.find(data);
//            if (ite == mapData.end())
//            {
//                qDebug()<<"table 1 exist, table2 not exist!";
//            }
//            else
//            {
//                listData2[ite.value()].isChecked = true;//已比对
//                qDebug()<<"exist!";
//            }
        }
    }

    ui->progressBar_Compare->setValue(92);
    QFile source(QString/*::fromLocal8Bit*/("表1未匹配数据.csv"));
    if (!source.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open out file failed!";
        return;
    }
    if (list.size() >=3)
    {
        source.write(list.at(0).toLocal8Bit());
        source.write(list.at(1).toLocal8Bit());
        source.write(list.at(2).toLocal8Bit());
    }
    for (int i=0; i < listData1.size(); i++)
    {
        source.write(listData1.at(i).data.toLocal8Bit());
    }
    source.close();

    ui->progressBar_Compare->setValue(94);
    QFile out(QString/*::fromLocal8Bit*/("表2未匹配数据.csv"));
    if (!out.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open out file1 failed!";
        return;
    }
    if (list2.size() >=1)
    {
        out.write(list2.at(0).toLocal8Bit());
        out.write(QString("\n").toLocal8Bit());
    }
    for (int i=0; i < listData2.size(); i++)
    {
        if (!listData2.at(i).isChecked)
        {
            out.write(listData2.at(i).data.toLocal8Bit());
            out.write(QString("\n").toLocal8Bit());
        }
    }
    out.close();

    ui->progressBar_Compare->setValue(96);
//    int colName = -1;
//    int colMuch = -1;
//    int colDate = -1;
//    int colSAP = -1;
//    int colText = -1;
//    QStringList listHeader = list2.at(0).split(",");
//    for (int i=0; i < listHeader.size(); i++)
//    {
//        if (listHeader.at(i).contains(QString/*::fromLocal8Bit*/("名称")))
//        {
//            colName    = i;
//        }
//        if (listHeader.at(i).contains(QString/*::fromLocal8Bit*/("金额")))
//        {
//            colMuch    = i;
//        }
//        if (listHeader.at(i).contains(QString/*::fromLocal8Bit*/("日期")))
//        {
//            colDate    = i;
//        }
//        if (listHeader.at(i).contains(QString/*::fromLocal8Bit*/("编号")))
//        {
//            colSAP    = i;
//        }
//        if (listHeader.at(i).contains(QString/*::fromLocal8Bit*/("文本")))
//        {
//            colText    = i;
//        }
//    }

//    if (colName == -1 || colMuch == -1
//        || colDate == -1 || colSAP == -1 || colText == -1  )
//    {
//        qDebug()<<"parse out file2 failed!";
//        return;
//    }

    ui->progressBar_Compare->setValue(98);
    QFile out2(QString/*::fromLocal8Bit*/("表2未匹配筛选数据.csv"));
    if (!out2.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open out file2 failed!";
        return;
    }
//    QString arrHeader = QString/*::fromLocal8Bit*/("名称,金额,日期,编号,文本");
    QString arrHeader;
    for (int i=0; i < outColumnlist.size(); i++)
    {
        if (i > 0)
        {
            arrHeader += ",";
        }
        arrHeader += list2.at(0).at(outColumnlist.at(i));
    }
    if (list2.size() >=1)
    {
        out2.write(arrHeader.toLocal8Bit());
        out2.write(QString("\n").toLocal8Bit());
    }
    for (int i=0; i < listData2.size(); i++)
    {
        QString key = listData2.at(i).list.at(nameCol2);

        QHash<QString, SCompare>::iterator ite = hashData.find(key);
        if (ite == hashData.end())
        {
            continue;
        }
        if (ite.value().exist)
        {
            for (int j=0; j < ite.value().list.size(); j++)
            {
                if (!ite.value().list.at(j).isChecked && ite.value().list.at(j).row == i+1)
                {
                    SData data = ite.value().list.at(j);
                    QString content;
                    for (int k = 0; k < outColumnlist.size(); k++)
                    {
                        if (k > 0)
                        {
                            content += ",";
                        }
                        content += ite.value().list.at(j).list.at(outColumnlist.at(k));
                    }
                    content += "\n";
					out2.write(content.toLocal8Bit());
                }
            }
        }
    }
    out2.close();
    ui->progressBar_Compare->setValue(100);
//    for (int i=0; i < listData2.size(); i++)
//    {
//        if (!listData2.at(i).isChecked)
//        {
////            qDebug()<<QString/*::fromLocal8Bit*/("行%1未发现匹配项。").arg(i+1);
//        }
//        else
//        {
//            qDebug()<<QString/*::fromLocal8Bit*/("行%1发现匹配项。").arg(i+1);
//        }
//    }
}

void Widget::onSelectFile1()
{
    m_file1 = QFileDialog::getOpenFileName(this);
    if (m_file1.isEmpty())
    {
        qDebug()<<"m_file1 is empty";
        ui->lineEdit_FileName1->setText("");
        return;
    }
    ui->lineEdit_FileName1->setText(m_file1);
}

void Widget::onSelectFile2()
{
    m_file2 = QFileDialog::getOpenFileName(this);
    if (m_file2.isEmpty())
    {
        qDebug()<<"m_file2 is empty";
        ui->lineEdit_FileName2->setText("");
        return;
    }
    ui->lineEdit_FileName2->setText(m_file2);
}

void Widget::onTest()
{
    QStringList listNames = QFileDialog::getOpenFileNames(this);
    if (listNames.size() == 0)
    {
        qDebug()<<"listNames is empty";
        return;
    }

    QAxObject *excel = NULL;
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;
    excel = new QAxObject("Excel.Application");
    if (!excel)
    {
        qDebug() << "EXCEL对象丢失!";
    }
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");
    //        QString FileName = "C:/Users/storm/Desktop/test/汇总表-2.xlsx";

    QVariantList header;
    QList<QList<QVariant> > allDataList;
    for (int i=0; i < listNames.size(); i++)
    {
        QString FileName = listNames.at(i);
        qDebug()<<QString/*::fromLocal8Bit*/("打开文件:%1").arg(FileName);
        workbook = workbooks->querySubObject("Open(QString, QVariant)", FileName);

        qDebug()<<QString/*::fromLocal8Bit*/("读取文件内容");
        QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);//打开第一个sheet
        QAxObject * usedrange = worksheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
        QAxObject * rows = usedrange->querySubObject("Rows");
        QAxObject * columns = usedrange->querySubObject("Columns");
        int intRows = rows->property("Count").toInt();
        int intCols = columns->property("Count").toInt();
        qDebug() << "xls行数："<<intRows;
        qDebug() << "xls列数："<<intCols;

        QString Range;
        if (i == 0)
        {
            Range = "A1:K" +QString::number(intRows);
        }
        else
        {
            Range = "A2:K" +QString::number(intRows);
        }

        QAxObject *fileData = worksheet->querySubObject("Range(QString)", Range);
        QVariant docDataQVariant = fileData->property("Value");
        qDebug()<<QString/*::fromLocal8Bit*/("处理文件内容");
        QVariantList docDataList = docDataQVariant.toList();
        QList<QVariant> oneRecord;
//        QList<QList<QVariant> > oneFile;
        for (int i=0; i < docDataList.size(); i++)
        {
            oneRecord = docDataList.at(i).toList();
            QFileInfo info(FileName);
            oneRecord.append(QVariant(info.fileName()));
            allDataList.append(oneRecord);
//            QList<>docDataList.at(i).toList().append(QVariant(FileName));
        }
        if (i == 0 && allDataList.size() > 0)
        {
            QList<QVariant> first = allDataList.first();
            first.removeLast();
            first.append(QString/*::fromLocal8Bit*/("文件名"));
            allDataList.removeFirst();
            allDataList.push_front(first);
//            header = docDataList.at(0).toList();
//            qDebug()<<"header"<<header;
        }
//        allDataList.append(oneFile);

        qDebug()<<QString/*::fromLocal8Bit*/("关闭文件");
        workbook->dynamicCall("Close (Boolean)", false);
    }
//    qDebug()<<"data"<<allEnvDataList;
    qDebug()<<QString/*::fromLocal8Bit*/("所有文件读取完毕，处理中");


    //处理数据
    for (int i=0; i < allDataList.size(); i++)
    {
        if (allDataList.at(i).at(2).toString().isEmpty())
        {
            allDataList.removeAt(i);
            i--;
        }
    }

    //输出文件
    qDebug()<<QString/*::fromLocal8Bit*/("回写文件");
    QString xlsFile = QDir::currentPath() + QString/*::fromLocal8Bit*/("/合并.xlsx");
    QFile file(xlsFile);
    while(file.exists())
    {
        bool ok = file.remove(xlsFile);
        if (!ok)
        {
            qDebug()<<QString/*::fromLocal8Bit*/("删除文件%1失败！").arg(xlsFile);
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                                 QString/*::fromLocal8Bit*/("请先删除文件后点击确定重试！"), QMessageBox::Ok);
        }
    }

    qDebug()<<QString/*::fromLocal8Bit*/("打开文件:%1").arg(xlsFile);
    workbooks->dynamicCall("Add");   //添加一个新的工作薄
    workbook = excel->querySubObject("ActiveWorkBook");

    QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
    QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);//获取工作表集合的工作表1，即sheet1

    int row = allDataList.size();
    int col = allDataList.at(0).size();
    QString rangStr = "A1:L" +QString::number(row);
    qDebug()<<rangStr;
    QAxObject *range = worksheet->querySubObject("Range(const QString&)",rangStr);
    if(NULL == range || range->isNull())
    {
        return;
    }
    bool succ = false;
    QVariant vars;
    QVariantList list;
    for (int i=0; i < allDataList.size(); i++)
    {
        list.append(QVariant(allDataList.at(i)));
    }
    vars = QVariant(list);
    succ = range->setProperty("Value", vars);
//    delete range;
    workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(xlsFile));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
    workbook->dynamicCall("Close()");

    workbooks->dynamicCall("Close()");
    delete excel;
    qDebug()<<QString/*::fromLocal8Bit*/("合并结束！");
}

void Widget::initHash()
{
    QString symbol[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","AA","AB","AC","AD","AE","AF","AG","AH","AI","AJ","AK","AL","AM","AN","AO","AP","AQ","AR","AS","AT","AU","AV","AW","AX","AY","AZ"};
    for (int i=0; i < 52; i++)
    {
       g_hashColumn.insert(symbol[i], i);
    }
}

bool Widget::checkInput()
{
    if (m_inFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请选择文件！"), QMessageBox::Ok);
        return false;
    }
    QString outFile = ui->lineEdit_Out->text();
    if (outFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请指定输出文件名字！"), QMessageBox::Ok);
        return false;
    }
    QString filterColumn = ui->lineEdit_SortColumn->text();
    QString dataColumn = ui->lineEdit_DataColumn->text();
    filterColumn.replace("；",";");
    dataColumn.replace("；",";");
    if (!filterColumn.contains(";"))
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写匹配列！"), QMessageBox::Ok);
        return false;
    }
    if (!dataColumn.contains(";"))
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写数据列！"), QMessageBox::Ok);
        return false;
    }
    QStringList filtList = filterColumn.split(";");
    g_keyList.clear();
    for (int i=0; i < filtList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(filtList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的匹配列:%1！").arg(filtList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return false;
        }
        g_keyList.push_back(ite.value());
    }

    QStringList dataList = dataColumn.split(";");
    g_dataList.clear();
    for (int i=0; i < dataList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(dataList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的数据列:%1！").arg(dataList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return false;
        }
        g_dataList.push_back(ite.value());
    }
    return true;
}

bool Widget::checkSplit()
{
    if (m_inSplitFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请选择文件！"), QMessageBox::Ok);
        return false;
    }

    QString splitSymbol = ui->lineEdit_Split->text();
    if (splitSymbol.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写分隔符！"), QMessageBox::Ok);
        return false;
    }
    m_splitSymbol = splitSymbol;

    QString folderColumn = ui->lineEdit_FolderSplit->text();
    folderColumn.replace("；",";");
    if (!folderColumn.contains(";"))
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写文件夹匹配列！"), QMessageBox::Ok);
        return false;
    }

    QString tableColumn = ui->lineEdit_TableSplit->text();
    tableColumn.replace("；",";");
    if (!tableColumn.contains(";"))
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写表匹配列！"), QMessageBox::Ok);
        return false;
    }

    QStringList folderList = folderColumn.split(";");

    g_keyList.clear();
    for (int i=0; i < folderList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(folderList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的匹配列:%1！").arg(folderList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return false;
        }
        g_keyList.push_back(ite.value());
    }

    QStringList dataList = tableColumn.split(";");
    g_dataList.clear();
    for (int i=0; i < dataList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(dataList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的数据列:%1！").arg(dataList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return false;
        }
        g_dataList.push_back(ite.value());
    }
    return true;
}

bool Widget::checkCompare()
{
    if (m_inSplitFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请选择文件！"), QMessageBox::Ok);
        return false;
    }

    QString splitSymbol = ui->lineEdit_Split->text();
    if (splitSymbol.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写分隔符！"), QMessageBox::Ok);
        return false;
    }
    m_splitSymbol = splitSymbol;

    QString folderColumn = ui->lineEdit_FolderSplit->text();
    folderColumn.replace("；",";");
    if (!folderColumn.contains(";"))
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写文件夹匹配列！"), QMessageBox::Ok);
        return false;
    }

    QString tableColumn = ui->lineEdit_TableSplit->text();
    tableColumn.replace("；",";");
    if (!tableColumn.contains(";"))
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), QString/*::fromLocal8Bit*/("请填写表匹配列！"), QMessageBox::Ok);
        return false;
    }

    QStringList folderList = folderColumn.split(";");

    g_keyList.clear();
    for (int i=0; i < folderList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(folderList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的匹配列:%1！").arg(folderList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return false;
        }
        g_keyList.push_back(ite.value());
    }

    QStringList dataList = tableColumn.split(";");
    g_dataList.clear();
    for (int i=0; i < dataList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(dataList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的数据列:%1！").arg(dataList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return false;
        }
        g_dataList.push_back(ite.value());
    }
    return true;
}

void Widget::convertMuch(QString &str)
{
    while (str.indexOf(",\"") != -1 && str.indexOf("\",") != -1)
    {
        int index1 = str.indexOf(",\"");
        int index2 = str.indexOf("\",");
        int index = str.indexOf(",", index1+1);
        if (index > index2)
        {
            //没有逗号
            str = str.remove(index2, 1);
            str = str.remove(index1 + 1, 1);
        }
        else
        {
            //有逗号
            str = str.remove(index2, 1);
            str = str.remove(index, 1);
            str = str.remove(index1 + 1, 1);
        }
    }

}



CheckThread::CheckThread(int index, QList<SData> &list, QReadWriteLock &locker, QWidget *parent)
    : m_index(index),m_list(list),m_locker(locker),QThread(parent)
{
    QTimer::singleShot(300, this, SLOT(onBegin()));
}

void CheckThread::onBegin()
{
    m_locker.lockForRead();
    int max = (m_index*10000 + 9999)>m_list.size()?(m_index*10000 + 9999):m_list.size();
    for (int i=m_index*10000; i < max; i++)
    {
        for (int j=0; j < m_list.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (m_list.at(i).isChecked)
            {
                continue;
            }
            if (m_list.at(i) == m_list.at(j))
            {

                m_list[i].data.replace("\r", "");
                m_list[i].data += ",";
                m_list[i].data += QString/*::fromLocal8Bit*/("重复");
                m_list[i].data += ",";
                m_list[i].data += QString/*::fromLocal8Bit*/("与%1行重复").arg(j+3+1);
                m_list[i].data += "\r";

                m_list[j].data.replace("\r", "");
                m_list[j].data += ",";
                m_list[j].data += QString/*::fromLocal8Bit*/("重复");
                m_list[j].data += ",";
                m_list[j].data += QString/*::fromLocal8Bit*/("与%1行重复").arg(i+3+1);
                m_list[j].data += "\r";
            }
        }
        m_locker.lockForWrite();
        m_list[i].isChecked = true;
        m_locker.unlock();
        qDebug()<<"check"<<i;
    }
    m_locker.lockForRead();
}
