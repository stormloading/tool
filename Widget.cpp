#include "widget.h"
#include "ui_widget.h"
#include <QDate>

QList<int> g_keyList;
QList<int> g_dataList;
QHash<QString, int> g_hashColumn;
QList<QString> g_Task;
QMutex g_mutex;
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

    connect(ui->pBtn_SelectFileMatch, SIGNAL(clicked(bool)), this, SLOT(onSelectMatchFile()));
    connect(ui->pBtn_Match, SIGNAL(clicked(bool)), this, SLOT(onMatch()));

    connect(ui->pBtn_SelectSplit, SIGNAL(clicked(bool)), this, SLOT(onSplitFFile()));
    connect(ui->pBtn_SplitF, SIGNAL(clicked(bool)), this, SLOT(onSplitF()));
    connect(ui->pBtn_CatLine, SIGNAL(clicked(bool)), this, SLOT(onCat()));
    connect(this, SIGNAL(add(QString)), this, SLOT(onAdd(QString)));

    connect(ui->pBtn_SelectFind, SIGNAL(clicked(bool)), this, SLOT(onSelectFind()));
    connect(ui->pBtn_Find, SIGNAL(clicked(bool)), this, SLOT(onFind()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onAdd(QString txt)
{
    ui->textEdit_Match->append(txt);
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

    float sum = 0.0;
    int delCount = 0;
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
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，均无数据，不追加%3").arg(row+1).arg(data.row+1).arg(data.list.at(g_keyList.at(0)));
                        sum += data.list.at(g_keyList.at(0)).toFloat();
                        delCount++;
//                        ui->textEdit->append(QString/*::fromLocal8Bit*/("重复：行%1和行%2，均无数据，不追加").arg(row+1).arg(data.row+1));
                        continue;
                    }
                    else if (!data.isEmpty() && !ite.key().isEmpty())
                    {
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，均有数据%3").arg(row+1).arg(data.row+1).arg(data.list.at(g_keyList.at(0)));
                        ui->textEdit->append(QString/*::fromLocal8Bit*/("重复：行%1和行%2，均有数据").arg(row+1).arg(data.row+1));
                        sum += data.list.at(g_keyList.at(0)).toFloat();
                        for (int j=0; j < data.list.size(); j++)
                        {
                            if (g_keyList.contains(j))
                            {
                                data.list[j] = "";
                            }
                        }
                        QString tmp;
                        for (int j=0; j < data.list.size(); j++)
                        {
                            if (j > 0)
                            {
                                tmp += ",";
                            }
                            tmp += data.list.at(j);
                        }
//                        tmp += "\r";
                        data.data = tmp;
//                        delCount++;
                        listData.push_back(data);
                    }
                    else if (data.isEmpty() && !ite.key().isEmpty())
                    {
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，前有数据，后无数据，不追加%3").arg(row+1).arg(data.row+1).arg(data.list.at(g_keyList.at(0)));
                        sum += data.list.at(g_keyList.at(0)).toFloat();
                        delCount++;
                        continue;
                    }
                    else if (!data.isEmpty() && ite.key().isEmpty())
                    {
                        int index = listData.indexOf(data);
                        qDebug()<<QString/*::fromLocal8Bit*/("重复：行%1和行%2，前无数据，后有数据，删前者，追加%3").arg(row+1).arg(data.row+1).arg(data.list.at(g_keyList.at(0)));
                        sum += data.list.at(g_keyList.at(0)).toFloat();

                        if (index != -1)
                        {
                            listData.removeAt(index);
                            delCount++;
                        }

                        listData.push_back(data);
                    }
                }
                else
                {
                    hashData.insert(data, data.row);
                    listData.push_back(data);
                }
            }
            else
            {
                listData.push_back(data);
            }
//            listData.push_back(data);
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(g_keyList.last());
        }

    }


    hashData.clear();
    //输出至文件
//    for (int i=0; i < listData.size(); i++)
//    {
//        ui->progressBar->setValue(50+50*i/listData.size());
//        QApplication::processEvents();
//        QMap<SData, int>::iterator ite = hashData.find(listData.at(i));
//        if (ite != hashData.end())
//        {
//            for (int j=0; j < listData.size(); j++)
//            {
////                qDebug()<<"cycle"<<i;
//                if (i == j)
//                {
//                    continue;
//                }
//                if (listData.at(i).isChecked)
//                {
//                    continue;
//                }
//                if (listData.at(i) == listData.at(j))
//                {

//                    listData[i].data.replace("\r", "");
//                    listData[i].data += ",";
//                    listData[i].data += QString/*::fromLocal8Bit*/("重复");
//                    listData[i].data += ",";
//                    listData[i].data += QString/*::fromLocal8Bit*/("与%1行重复").arg(j+3+1);
//                    listData[i].data += "\r";

//                    listData[j].data.replace("\r", "");
//                    listData[j].data += ",";
//                    listData[j].data += QString/*::fromLocal8Bit*/("重复");
//                    listData[j].data += ",";
//                    listData[j].data += QString/*::fromLocal8Bit*/("与%1行重复").arg(i+3+1);
//                    listData[j].data += "\r";
//                }
//            }
//        }
//        else
//        {
//          hashData.insert(listData.at(i), i);
//        }
//        listData[i].isChecked = true;
//        qDebug()<<"check"<<i;
//    }

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
    qDebug()<<QString/*::fromLocal8Bit*/("共删除%1行，总金额为：%2").arg(delCount).arg(sum);
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

void Widget::onSelectMatchFile()
{
    QString matchFile = QFileDialog::getOpenFileName(this);
    if (matchFile.isEmpty())
    {
        qDebug()<<"matchFile is empty";
        ui->lineEdit_FileNameMatch->setText("");
        return;
    }
    ui->lineEdit_FileNameMatch->setText(matchFile);
}
#define TimeFormate "yyyy-M-d"
#define TimeFormate2 "yyyy/M/d"
#include <QThreadPool>
void Widget::onMatch()
{
    QDateTime begin = QDateTime::currentDateTime();
    ui->textEdit_Match->append(QString("开始匹配，时间：%1").arg(begin.toString()));
    QString matchFile = ui->lineEdit_FileNameMatch->text();
    QString outFile = ui->lineEdit_OutMatch->text();
    if (outFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("请填写输出文件名！"), QMessageBox::Ok);
        return;
    }

    QString nameCol = ui->lineEdit_NameMatch->text();

    QString muchCol = ui->lineEdit_MuchMatch->text();
    QString inTimeCol = ui->lineEdit_InTimeMatch->text();
    QString payCol = ui->lineEdit_PayMatch->text();
    QList<int> muchList;
    if (!getColList(muchCol, muchList))
    {
        return;
    }
    if (muchList.size() != 2)
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("金额列必须为两列！"), QMessageBox::Ok);
        return;
    }
    QList<int> inTimeList;
    if (!getColList(inTimeCol, inTimeList))
    {
        return;
    }
    int minInTime = inTimeList.at(0);
    for (int i=1; i < inTimeList.size(); i++)
    {
        if (inTimeList.at(i) < minInTime)
        {
            minInTime = inTimeList.at(i);
        }
    }
    int NameColNum = -1;
    if (!getCol(nameCol, NameColNum))
    {
        return;
    }

    int payColNum = -1;
    if (!getCol(payCol, payColNum))
    {
        return;
    }

    int maxCol = NameColNum;
    if (payColNum > maxCol)
    {
        maxCol = payColNum;
    }
    for (int i=0; i < muchList.size(); i++)
    {
        if (muchList.at(i) > maxCol)
        {
            maxCol = muchList.at(i);
        }
    }
    for (int i=0; i < inTimeList.size(); i++)
    {
        if (inTimeList.at(i) > maxCol)
        {
            maxCol = inTimeList.at(i);
        }
    }

    SMatch m;
    m.maxCol = maxCol;
    m.muchList = muchList;
    m.minInTime = minInTime;
    m.payColNum = payColNum;
    m.NameColNum = NameColNum;
    m.inTimeList = inTimeList;
    m.maxLevel = ui->lineEdit_Level->text().toUInt();
    g_keyList.clear();
    g_keyList.push_back(NameColNum);
    g_keyList.push_back(muchList.at(1));

    QFile file(matchFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open matchFile failed";
        return;
    }

    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

    QList<SData> listData;
    QList<SData> tmpListData;
    QMap<SData, int> hashData;
    QStringList list = string.split("\n");
    QMap<QString, QList<SData> > splitData;
    QList<QString> orderList;
    for (int i=3; i < list.size(); i++)
    {
//        ui->progressBar->setValue(50*i/list.size());
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > maxCol)
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.canDel = false;
            float val = data.list.at(muchList.at(0)).toFloat() + data.list.at(muchList.at(1)).toFloat();
            if (qAbs(val) < 0.000001)
            {
                data.isChecked = true;
            }
            else
            {
                data.isChecked = false;
            }
            listData.push_back(data);

            QMap<QString, QList<SData> >::iterator ite = splitData.find(data.list.at(NameColNum));
            if (ite == splitData.end())
            {
                QList<SData> l;
                l.push_back(data);
                orderList.push_back(data.list.at(NameColNum));
                splitData.insert(data.list.at(NameColNum), l);
            }
            else
            {
                ite.value().push_back(data);
            }
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(maxCol);
        }
    }

    QMap<QString, QList<SData> >::iterator ite = splitData.begin();
    QThreadPool::globalInstance()->setMaxThreadCount(8);
    for (int i=0; i < orderList.size(); i++)
    {
        QMap<QString, QList<SData> >::iterator ite = splitData.find(orderList.at(i));
        if (ite != splitData.end())
        {
            //        QDateTime time = QDateTime::currentDateTime();
            //        qDebug()<<QString("开始匹配%1,时间%2").arg(ite.key()).arg(time.toString());
            matchTask *task = new matchTask(m, ite.value(), this);
            QThreadPool::globalInstance()->start(task);
//                    rescMatch(m, ite.value());
            //        QDateTime time2 = QDateTime::currentDateTime();
            //        qDebug()<<QString("匹配结束%1,时间%2,耗时%3秒").arg(ite.key()).arg(time.toString()).arg(time.secsTo(time2));
        }
    }

    while (QThreadPool::globalInstance()->activeThreadCount() != 0)
    {
        QThread::msleep(1000);
        ui->listWidget->clear();
        g_mutex.lock();
        for (int i=0; i < g_Task.size(); i++)
        {
            ui->listWidget->addItem(g_Task.at(i));
        }
        g_mutex.unlock();
        QApplication::processEvents();
    }

    //输出文件
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


    int delCount = 0;
    int saveCount = 0;
    for (int i=0; i < orderList.size(); i++)
    {
        ite = splitData.find(orderList.at(i));
        if (ite == splitData.end())
        {
            qDebug()<<QString/*::fromLocal8Bit*/("不该出现此错误，请检查！");
            continue;
        }
        for (int i=0; i < ite.value().size(); i++)
        {
            if (ite.value().at(i).canDel)
            {
                delCount++;
                continue;
            }
            QString line;
            for (int j=0; j < ite.value().at(i).list.size(); j++)
            {
                if (j > 0)
                {
                    line += ",";
                }
                line += ite.value().at(i).list.at(j);
            }
            if (!ite.value().at(i).isChecked)
            {
                line.replace("\r", "");
                line += QString/*::fromLocal8Bit*/(",未匹配");
            }
            line += "\n";
            saveCount++;
            out.write(line.toLocal8Bit());
        }
    }

//    for (int i=0; i < g_tmpData.size(); i++)
//    {
//        QString line;
//        for (int j=0; j < g_tmpData.at(i).list.size(); j++)
//        {
//            if (j > 0)
//            {
//                line += ",";
//            }
//            line += g_tmpData.at(i).list.at(j);
//        }
//        if (!g_tmpData.at(i).isChecked)
//        {
//            line.replace("\r", "");
//            line += QString/*::fromLocal8Bit*/(",未匹配");
//        }
//        line += "\n";
//        out.write(line.toLocal8Bit());
//    }

    file.close();

    QDateTime end = QDateTime::currentDateTime();
    ui->textEdit_Match->append(QString("匹配结束，时间：%1").arg(end.toString()));
    qDebug()<<"done!";
}

void Widget::onOrderCheck()
{

}



void Widget::onMatch1()
{
    QString matchFile = ui->lineEdit_FileNameMatch->text();
    QString outFile = ui->lineEdit_OutMatch->text();
    if (outFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("请填写输出文件名！"), QMessageBox::Ok);
        return;
    }

    QString nameCol = ui->lineEdit_NameMatch->text();

    QString muchCol = ui->lineEdit_MuchMatch->text();
    QString inTimeCol = ui->lineEdit_InTimeMatch->text();
    QString payCol = ui->lineEdit_PayMatch->text();
    QList<int> muchList;
    if (!getColList(muchCol, muchList))
    {
        return;
    }
    if (muchList.size() != 2)
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("金额列必须为两列！"), QMessageBox::Ok);
        return;
    }
    QList<int> inTimeList;
    if (!getColList(inTimeCol, inTimeList))
    {
        return;
    }
    int minInTime = inTimeList.at(0);
    for (int i=1; i < inTimeList.size(); i++)
    {
        if (inTimeList.at(i) < minInTime)
        {
            minInTime = inTimeList.at(i);
        }
    }
    int NameColNum = -1;
    if (!getCol(nameCol, NameColNum))
    {
        return;
    }

    int payColNum = -1;
    if (!getCol(payCol, payColNum))
    {
        return;
    }

    g_keyList.clear();
    g_keyList.push_back(NameColNum);
    g_keyList.push_back(muchList.at(1));

    QFile file(matchFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open matchFile failed";
        return;
    }

    int maxCol = NameColNum;
    if (payColNum > maxCol)
    {
        maxCol = payColNum;
    }
    for (int i=0; i < muchList.size(); i++)
    {
        if (muchList.at(i) > maxCol)
        {
            maxCol = muchList.at(i);
        }
    }
    for (int i=0; i < inTimeList.size(); i++)
    {
        if (inTimeList.at(i) > maxCol)
        {
            maxCol = inTimeList.at(i);
        }
    }

    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

    QList<SData> listData;
    QList<SData> tmpListData;
    QMap<SData, int> hashData;
    QStringList list = string.split("\n");
    for (int i=3; i < list.size(); i++)
    {
//        ui->progressBar->setValue(50*i/list.size());
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > maxCol)
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            float val = data.list.at(muchList.at(0)).toFloat() + data.list.at(muchList.at(1)).toFloat();
            if (qAbs(val) < 0.000001)
            {
                data.isChecked = true;
            }
            else
            {
                data.isChecked = false;
            }
            listData.push_back(data);
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(maxCol);
        }

    }


    QHash<int, int> hashDel;
    //匹配数据
    for (int i=0; i < listData.size(); i++)
    {
        if (!listData.at(i).isChecked)//需要匹配
        {
            for (int j=0; j < listData.size(); j++)
            {
                if (i == j || listData.at(j).isChecked)
                {
                    continue;
                }

//                float val1 = listData.at(i).list.at(muchList.at(0)).toFloat();
//                float val2 = listData.at(i).list.at(muchList.at(0)).toFloat();
                if (listData.at(j).list.at(muchList.at(1)).isEmpty())
                {
                    continue;
                }
                float val = listData.at(i).list.at(muchList.at(0)).toFloat() + listData.at(j).list.at(muchList.at(1)).toFloat();
                if (qAbs(val) > 0.000001)
                {
                    continue;
                }
                if (listData.at(i).list.at(NameColNum) == listData.at(j).list.at(NameColNum))//匹配到
                {
                    //判断是否存在金额一样的
                    bool match = true;
                    int lastIndex = listData.lastIndexOf(listData.at(j));
                    if (lastIndex != j)
                    {
                        QString info = QString/*::fromLocal8Bit*/("检测到非唯一数据，将进行时间匹配。行%1，行%2，行%3").arg(listData.at(i).row+1).arg(listData.at(j).row+1).arg(listData.at(lastIndex).row+1);
                        qDebug()<<info;
                        ui->textEdit_Match->append(info);
                        //日期校验
                        QDate payDate = QDate::fromString(listData.at(j).list.at(payColNum), TimeFormate);

                        for (int k=0; k < inTimeList.size(); k++)
                        {
                            QDate inTimeDate = QDate::fromString(listData.at(i).list.at(inTimeList.at(k)), TimeFormate);
                            if (inTimeDate.daysTo(payDate) > 31)
                            {
                                match = false;
                            }
                        }
                    }
                    if (match)
                    {
                        listData[i].isChecked = true;
                        listData[j].isChecked = true;
                        //判断是否会覆盖数据
                        if (!listData.at(i).list.at(muchList.at(1)).isEmpty())
                        {
                            //保存临时数据
                            SData tmp = listData.at(i);
                            for (int m=minInTime-1; m < muchList.at(1); m++)
                            {
                                tmp.list[m] = "";
                            }
                            tmp.isChecked = false;
                            tmpListData.push_back(tmp);
                            QString info = QString/*::fromLocal8Bit*/("检测到错行数据。行%1.").arg(listData.at(i).row+1);
                            qDebug()<<info;
                            ui->textEdit_Match->append(info);
                        }
                        //挪数据
                        for (int m=muchList.at(1); m < listData[i].list.size(); m++)
                        {
                            if (m < listData.size())
                            {
                                listData[i].list[m] = listData[j].list[m];
                            }
                        }
                        //删除付款金额
                        listData[j].list[muchList.at(1)] = "";
//                        QString info = QString/*::fromLocal8Bit*/("行%1和行%2数据匹配成功！复制数据。").arg(listData.at(i).row+1).arg(listData.at(j).row+1);
//                        qDebug()<<info;
                        //是否删除行
                        bool canDel = true;
                        for (int m=0; m < inTimeList.size(); m++)
                        {
                            if (!listData.at(j).list.at(inTimeList.at(m)).isEmpty())
                            {
                                canDel = false;
                                break;
                            }
                        }
                        if (canDel)
                        {
//                            qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间为空，删除。").arg(listData.at(j).row+1);;
                            hashDel.insert(j, j);
                        }
                        else
                        {
                            qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间非空，不删除。").arg(listData.at(j).row+1);;
                        }
                    }
                    else
                    {
                        QString info = QString/*::fromLocal8Bit*/("时间相差超过一个月，不匹配！行%1，行%2").arg(listData.at(i).row+1).arg(listData.at(j).row+1);
                        qDebug()<<info;
                    }
                }
            }
        }
    }

    qDebug()<<QString/*::fromLocal8Bit*/("匹配临时数据");
    ui->textEdit_Match->append(QString/*::fromLocal8Bit*/("匹配临时数据"));
    //匹配临时数据
    for (int i=0; i < listData.size(); i++)
    {
        if (!listData.at(i).isChecked)//需要匹配
        {
            for (int j=0; j < tmpListData.size(); j++)
            {
                if (tmpListData.at(j).isChecked)
                {
                    continue;
                }

//                float val1 = listData.at(i).list.at(muchList.at(0)).toFloat();
//                float val2 = listData.at(i).list.at(muchList.at(0)).toFloat();
                if (tmpListData.at(j).list.at(muchList.at(1)).isEmpty())
                {
                    continue;
                }
                float val = listData.at(i).list.at(muchList.at(0)).toFloat() + tmpListData.at(j).list.at(muchList.at(1)).toFloat();
                if (qAbs(val) > 0.000001)
                {
                    continue;
                }
                if (listData.at(i).list.at(NameColNum) == tmpListData.at(j).list.at(NameColNum))//匹配到
                {
                    //判断是否存在金额一样的
                    bool match = true;
                    int lastIndex = tmpListData.lastIndexOf(tmpListData.at(j));
                    if (tmpListData.at(j).row != tmpListData.at(lastIndex).row)
                    {
                        QString info = QString/*::fromLocal8Bit*/("检测到非唯一数据，将进行时间匹配。行%1，行%2，行%3").arg(listData.at(i).row+1).arg(tmpListData.at(j).row+1).arg(tmpListData.at(lastIndex).row+1);
                        qDebug()<<info;
                        ui->textEdit_Match->append(info);
                        //日期校验
                        QDate payDate = QDate::fromString(tmpListData.at(j).list.at(payColNum), TimeFormate);

                        for (int k=0; k < inTimeList.size(); k++)
                        {
                            QDate inTimeDate = QDate::fromString(listData.at(i).list.at(inTimeList.at(k)), TimeFormate);
                            if (inTimeDate.daysTo(payDate) > 31)
                            {
                                match = false;
                            }
                        }
                    }
                    if (match)
                    {
                        listData[i].isChecked = true;
                        //判断是否会覆盖数据
                        if (!listData.at(i).list.at(muchList.at(1)).isEmpty())
                        {
                            //保存临时数据
                            SData tmp = listData.at(i);
                            for (int m=minInTime-1; m < muchList.at(1); m++)
                            {
                                tmp.list[m] = "";
                            }
                            tmpListData.push_back(tmp);
                            QString info = QString/*::fromLocal8Bit*/("------------检测到错行数据。行%1.").arg(listData.at(i).row+1);
                            qDebug()<<info;
                            ui->textEdit_Match->append(info);
                        }
                        //挪数据
                        for (int m=muchList.at(1); m < listData[i].list.size(); m++)
                        {
                            if (m < listData.size())
                            {
                                listData[i].list[m] = tmpListData[j].list[m];
                            }
                        }
                        //删除付款金额
                        tmpListData[j].list[muchList.at(1)] = "";
                        QString info = QString/*::fromLocal8Bit*/("行%1和临时行%2数据匹配成功！复制数据。").arg(listData.at(i).row+1).arg(listData.at(j).row+1);
                        qDebug()<<info;
                        tmpListData.removeAt(j);
                        j--;
                    }
                    else
                    {
                        QString info = QString/*::fromLocal8Bit*/("时间相差超过一个月，不匹配！行%1，行%2").arg(listData.at(i).row+1).arg(listData.at(j).row+1);
                        qDebug()<<info;
                    }
                }
            }
        }
    }

    //输出文件
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
        QHash<int, int>::iterator ite = hashDel.find(i);
        if (ite == hashDel.end())
        {
            QString line;
            for (int j=0; j < listData.at(i).list.size(); j++)
            {
                if (j > 0)
                {
                    line += ",";
                }
                line += listData.at(i).list.at(j);
            }
            line += "\n";
            out.write(line.toLocal8Bit());
        }
    }

    if (tmpListData.size() > 0)
    {
        qDebug()<<QString/*::fromLocal8Bit*/("剩余临时数据%1行").arg(tmpListData.size());
    }
    for (int i=0; i < tmpListData.size(); i++)
    {
        QString line;
        for (int j=0; j < tmpListData.at(i).list.size(); j++)
        {
            if (j > 0)
            {
                line += ",";
            }
            line += tmpListData.at(i).list.at(j);

        }
        line.replace("\r", "");
        line += ",";
        line += QString/*::fromLocal8Bit*/("临时行\n");
        out.write(line.toLocal8Bit());
    }
//    ui->progressBar->setValue(100);
    file.close();
    qDebug()<<"done!";
}

void Widget::onSplitFFile()
{
    QString matchFile = QFileDialog::getOpenFileName(this);
    if (matchFile.isEmpty())
    {
        qDebug()<<"splitFFile is empty";
        ui->lineEdit_FileNameSplit->setText("");
        return;
    }
    ui->lineEdit_FileNameSplit->setText(matchFile);
}

void Widget::onSplitF()
{
    QString matchFile = ui->lineEdit_FileNameSplit->text();
    QString outFile = ui->lineEdit_OutSplit->text();
    if (outFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("请填写输出文件名！"), QMessageBox::Ok);
        return;
    }

//    QString keyColStr = "G";
    QString keyColStr = ui->lineEdit_G->text();
    int keyCol;
    if (!getCol(keyColStr, keyCol))
    {
        return;
    }

//    QString ColListStr = "H;I;D";
    QString ColListStr = ui->lineEdit_HID->text();
    QList<int> colList;
    if (!getColList(ColListStr, colList))
    {
        return;
    }
    if (colList.size() > 10)
    {
        qDebug()<<"超过10列";
        return;
    }

//    QString addListStr = "E;F";
    QString addListStr = ui->lineEdit_EF->text();;
    QList<int> addList;
    if (!getColList(addListStr, addList))
    {
        return;
    }

    int maxCol = keyCol;
    if (keyCol > maxCol)
    {
        maxCol = keyCol;
    }
    for (int i=0; i < colList.size(); i++)
    {
        if (colList.at(i) > maxCol)
        {
            maxCol = colList.at(i);
        }
    }
    for (int i=0; i < addList.size(); i++)
    {
        if (addList.at(i) > maxCol)
        {
            maxCol = addList.at(i);
        }
    }


    QFile file(matchFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open matchFile failed";
        return;
    }

    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

    QList<SData> listData;
    QStringList list = string.split("\n");
    QMap<QString, QList<SData> > splitData;
    QList<QString> orderList;
    for (int i=1; i < list.size(); i++)
    {
//        ui->progressBar->setValue(50*i/list.size());
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > maxCol)
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.canDel = false;
            listData.push_back(data);
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(maxCol);
        }
    }

    for (int i=0; i < listData.size(); i++)
    {
        QString tmpKeyStr = listData.at(i).list.at(keyCol);
        QStringList keyList = tmpKeyStr.split("|");
        if (keyList.size() <= 1)
        {
            continue;
        }
        if (listData.at(i).list.at(0).isEmpty())
        {
            continue;
        }
        bool hasDiff = false;
        for (int j=1; j < keyList.size(); j++)
        {
            if (keyList.at(0) != keyList.at(j))
            {
                hasDiff = true;
                break;
            }
        }
        if (!hasDiff)
        {
            continue;
        }
        QStringList list[10];
        for (int j=0; j < colList.size(); j++)
        {
            SData &d = listData[i];
            QString tmpStr = listData.at(i).list.at(colList.at(j));
            QStringList spList = listData.at(i).list.at(colList.at(j)).split("|");
            list[j] = spList;
            if (list[j].size() != keyList.size())
            {
                qDebug()<<QString("行%1各列个数不对应！").arg(listData.at(i).row + 1);
                return;
            }
        }
        qDebug()<<QString("行%1进行拆分！").arg(listData.at(i).row + 1);
        QList<QString> listRow;
        QList<QList<int> >listSperate;
        for (int j=0; j < keyList.size(); j++)
        {
            bool exist = false;
            for (int k=0; k < listRow.size(); k++)
            {
                if (keyList.at(j) == listRow.at(k))
                {
                    exist = true;
                    listSperate[k].push_back(j);
                }
            }
            if (!exist)
            {
                listRow.push_back(keyList.at(j));
                QList<int> tmpList;
                tmpList.push_back(j);
                listSperate.push_back(tmpList);
            }
        }
        SData data = listData.at(i);
        //?????????
        for (int j=maxCol+1; j < data.list.size(); j++)
        {
            data.list[j] = "";
        }
        SData tmpData = data;
        for (int j=0; j < listRow.size(); j++)
        {
            if (j == 0)
            {
                QString tmpStr;
                for (int k=0; k < listSperate.at(j).size(); k++)
                {
                    if (k > 0)
                    {
                        tmpStr += "|";
                    }
                    tmpStr += listRow.at(j);
                }
                listData[i].list[keyCol] = tmpStr;
                for (int k=0; k < colList.size(); k++)
                {
                    QString newStr;
                    for (int m=0; m < listSperate.at(j).size(); m++)
                    {
                        if (m > 0)
                        {
                            newStr += "|";
                        }
                        newStr += list[k].at(listSperate.at(j).at(m));
                    }
                    listData[i].list[colList.at(k)] = newStr;
                }
                for (int k=0; k < addList.size(); k++)
                {
                    float v = 0.0;
                    for (int m=0; m < listSperate.at(j).size(); m++)
                    {
                        v += list[k].at(listSperate.at(j).at(m)).toFloat();
                    }
                    listData[i].list[addList.at(k)] = QString::number(v);
                }
            }
            else
            {
                QString tmpStr;
                for (int k=0; k < listSperate.at(j).size(); k++)
                {
                    if (k > 0)
                    {
                        tmpStr += "|";
                    }
                    tmpStr += listRow.at(j);
                }
                data.list[keyCol] = tmpStr;
                for (int k=0; k < colList.size(); k++)
                {
                    QString newStr;
                    for (int m=0; m < listSperate.at(j).size(); m++)
                    {
                        if (m > 0)
                        {
                            newStr += "|";
                        }
                        newStr += list[k].at(listSperate.at(j).at(m));
                    }
                    data.list[colList.at(k)] = newStr;
                }
                for (int k=0; k < addList.size(); k++)
                {
                    float v = 0.0;
                    for (int m=0; m < listSperate.at(j).size(); m++)
                    {
                        v += list[k].at(listSperate.at(j).at(m)).toFloat();
                    }
                    data.list[addList.at(k)] = QString::number(v);
                }
                listData.insert(i+1, data);
                i++;
            }
        }
    }

    //输出文件
    QFile out(outFile);
    if (!out.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open out file failed!";
        return;
    }
    if (list.size() >=1)
    {
        out.write(list.at(0).toLocal8Bit());
    }


    for (int i=0; i < listData.size(); i++)
    {
        QString line;
        for (int j=0; j < listData.at(i).list.size(); j++)
        {
            if (j > 0)
            {
                line += ",";
            }
            line += listData.at(i).list.at(j);
        }
        line += "\n";
        out.write(line.toLocal8Bit());
    }
    file.close();
    qDebug()<<"done!";
}

void Widget::onCat()
{
    QString matchFile = ui->lineEdit_FileNameMatch->text();
    QString outFile = ui->lineEdit_OutMatch->text();
    if (outFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("请填写输出文件名！"), QMessageBox::Ok);
        return;
    }

    QString nameCol = ui->lineEdit_NameMatch->text();

    QString muchCol = ui->lineEdit_MuchMatch->text();
    QString inTimeCol = ui->lineEdit_InTimeMatch->text();
    QString payCol = ui->lineEdit_PayMatch->text();
    QList<int> muchList;
    if (!getColList(muchCol, muchList))
    {
        return;
    }
    if (muchList.size() != 2)
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("金额列必须为两列！"), QMessageBox::Ok);
        return;
    }
    QList<int> inTimeList;
    if (!getColList(inTimeCol, inTimeList))
    {
        return;
    }
    int minInTime = inTimeList.at(0);
    for (int i=1; i < inTimeList.size(); i++)
    {
        if (inTimeList.at(i) < minInTime)
        {
            minInTime = inTimeList.at(i);
        }
    }
    int NameColNum = -1;
    if (!getCol(nameCol, NameColNum))
    {
        return;
    }

    int payColNum = -1;
    if (!getCol(payCol, payColNum))
    {
        return;
    }

    int maxCol = NameColNum;
    if (payColNum > maxCol)
    {
        maxCol = payColNum;
    }
    for (int i=0; i < muchList.size(); i++)
    {
        if (muchList.at(i) > maxCol)
        {
            maxCol = muchList.at(i);
        }
    }
    for (int i=0; i < inTimeList.size(); i++)
    {
        if (inTimeList.at(i) > maxCol)
        {
            maxCol = inTimeList.at(i);
        }
    }

    SMatch m;
    m.maxCol = maxCol;
    m.muchList = muchList;
    m.minInTime = minInTime;
    m.payColNum = payColNum;
    m.NameColNum = NameColNum;
    m.inTimeList = inTimeList;
    m.maxLevel = ui->lineEdit_Level->text().toUInt();
    g_keyList.clear();
    g_keyList.push_back(NameColNum);
    g_keyList.push_back(muchList.at(1));

    QFile file(matchFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open matchFile failed";
        return;
    }

    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

    QList<SData> listData;
    QList<SData> tmpListData;
    QMap<SData, int> hashData;
    QStringList list = string.split("\n");
    QMap<QString, QList<SData> > splitData;
    QList<QString> orderList;
    for (int i=3; i < list.size(); i++)
    {
//        ui->progressBar->setValue(50*i/list.size());
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > maxCol)
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.canDel = false;
            data.isChecked = false;
            QMap<QString, QList<SData> >::iterator ite = splitData.find(data.list.at(NameColNum));
            if (ite == splitData.end())
            {
                QList<SData> l;
                l.push_back(data);
                orderList.push_back(data.list.at(NameColNum));
                splitData.insert(data.list.at(NameColNum), l);
            }
            else
            {
                ite.value().push_back(data);
            }
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(maxCol);
        }
    }

    QMap<QString, QList<SData> >::iterator ite = splitData.begin();
    QThreadPool::globalInstance()->setMaxThreadCount(8);
    for (int i=0; i < orderList.size(); i++)
    {
        QMap<QString, QList<SData> >::iterator ite = splitData.find(orderList.at(i));
        if (ite != splitData.end())
        {
            rescCat(m, ite.value());
        }
    }

    //输出文件
    QFile out(outFile);
    if (!out.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open out file failed!";
        return;
    }
    if (list.size() >=3)
    {
        out.write(list.at(0).toLocal8Bit().replace("\r", "\n\r"));
        out.write(list.at(1).toLocal8Bit().replace("\r", "\n\r"));
        out.write(list.at(2).toLocal8Bit().replace("\r", "\n\r"));
    }


    int delCount = 0;
    int saveCount = 0;
    for (int i=0; i < orderList.size(); i++)
    {
        ite = splitData.find(orderList.at(i));
        if (ite == splitData.end())
        {
            qDebug()<<QString/*::fromLocal8Bit*/("不该出现此错误，请检查！");
            continue;
        }
        for (int i=0; i < ite.value().size(); i++)
        {
            if (ite.value().at(i).canDel)
            {
                delCount++;
                continue;
            }
            QString line;
            for (int j=0; j < ite.value().at(i).list.size(); j++)
            {
                if (j > 0)
                {
                    line += ",";
                }
                line += ite.value().at(i).list.at(j);
            }
//            if (!ite.value().at(i).isChecked)
//            {
//                line.replace("\r", "");
//                line += QString/*::fromLocal8Bit*/(",未匹配");
//            }
            line += "\n";
            saveCount++;
            out.write(line.toLocal8Bit());
        }
    }
    file.close();

    qDebug()<<"done!";
}

void Widget::onSelectFind()
{
    QString matchFile = QFileDialog::getOpenFileName(this);
    if (matchFile.isEmpty())
    {
        qDebug()<<"FindFile is empty";
        ui->lineEdit_Find->setText("");
        return;
    }
    ui->lineEdit_Find->setText(matchFile);
}

void Widget::onFind()
{
    QString matchFile = ui->lineEdit_Find->text();
    QString outFile = ui->lineEdit_OutFind->text();
    if (outFile.isEmpty())
    {
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"),
                             QString/*::fromLocal8Bit*/("请填写输出文件名！"), QMessageBox::Ok);
        return;
    }

//    QString nameColStr = ui->lineEdit_NameMatch->text();
    QString nameColStr = "H";
    int nameCol = 0;
//    QString muchColStr = ui->lineEdit_MuchMatch->text();
    QString muchColStr = "E";
    int muchCol = 0;
    if (!getCol(nameColStr, nameCol))
    {
        return;
    }
    if (!getCol(muchColStr, muchCol))
    {
        return;
    }

    QString slaveColStr = "I";
    int slaveCol = 0;
    if (!getCol(slaveColStr, slaveCol))
    {
        return;
    }

    int maxCol = nameCol;
    if (muchCol > maxCol)
    {
        maxCol = muchCol;
    }
    if (slaveCol > maxCol)
    {
        maxCol = slaveCol;
    }


    QFile file(matchFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open matchFile failed";
        return;
    }

    QByteArray arr = file.readAll();
    QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QString string = codec->toUnicode(arr);

    QList<SData> listData;
    QStringList list = string.split("\n");
    for (int i=1; i < list.size(); i++)
    {
        SData data;
        QString tmp = list.at(i);
        convertMuch(tmp);
        QStringList rec = tmp.split(",");
        if (rec.size() > maxCol)
        {
            data.row = i;
            data.list = rec;
            data.data = tmp;
            data.canDel = false;
            data.isChecked = false;
            listData.push_back(data);
        }
        else
        {
            qDebug()<<QString/*::fromLocal8Bit*/("行%1列数少于%2").arg(i+1).arg(maxCol);
        }
    }

    for (int i=0; i < listData.size(); i++)
    {
        if (listData.at(i).isChecked)
        {
            continue;
        }
        for (int j=0; j < listData.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (listData.at(j).isChecked)
            {
                continue;
            }
            if (listData.at(i).list.at(nameCol) != listData.at(j).list.at(nameCol))
            {
                continue;
            }
            float sum = listData.at(i).list.at(muchCol).toFloat() + listData.at(j).list.at(muchCol).toFloat();
            if (sum == 0)
            {
                //符合
                listData[i].list.last().replace("\r", "");
                listData[i].list.append(QString("匹配,与第%1行匹配").arg(listData.at(j).row+1));
                listData[j].list.last().replace("\r", "");
                listData[j].list.append(QString("匹配,与第%1行匹配").arg(listData.at(i).row+1));
                listData[i].isChecked = true;
                listData[j].isChecked = true;
                break;
            }
        }
    }

    //输出文件
    QFile out(outFile);
    if (!out.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open out file failed!";
        return;
    }
    if (list.size() >=1)
    {
        out.write(list.at(0).toLocal8Bit());
    }


    for (int i=0; i < listData.size(); i++)
    {
        QString line;
        for (int j=0; j < listData.at(i).list.size(); j++)
        {
            if (j > 0)
            {
                line += ",";
            }
            line += listData.at(i).list.at(j);
        }
        line += "\n";
        out.write(line.toLocal8Bit());
    }

    file.close();
    qDebug()<<"done!";
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

void Widget::orderMisMatch(SMatch m, QList<SData> &list)
{
    QList<int> sortList;
    for (int i=0; i < list.size(); i++)
    {
        float v1 = list.at(i).list.at(m.inTimeList.at(1)-1).toFloat();
        float v2 = list.at(i).list.at(m.inTimeList.at(2)-1).toFloat();
        if (v1 != 0 && v2 != 0)
        {
            float v3 = v1/v2;
            if (matchSCal(v3))
            {

            }
            else
            {
                sortList.push_back(i);
            }
        }
        if (list.at(i).isChecked)
        {
            continue;
        }
        bool absoluteMatch = true;
        QDate baseDate = QDate::fromString(list.at(i).list.at(0), TimeFormate);
        for (int j=1; j < m.inTimeList.size(); j++)
        {
            if (list.at(i).list.at(m.inTimeList.at(j)).isEmpty())
            {
                absoluteMatch = false;
//                listRandom.push_back(QStringList()<<list.at(i).list.at(j-1)
//                                     <<list.at(i).list.at(j)
//                                     <<list.at(i).list.at(j+1)
//                                     <<list.at(i).list.at(j+2));
                break;
            }

            QDate Date = QDate::fromString(list.at(i).list.at(m.inTimeList.at(j)), TimeFormate);
            if (qAbs(Date.daysTo(baseDate)) > 7)
            {
                absoluteMatch = false;
                qDebug()<<QString/*::fromLocal8Bit*/("行%1入账日期间隔超过一周,怀疑错行.").arg(list.at(i).row+1);
                break;
            }
        }
        list[i].isAbsolute = absoluteMatch;
    }

    for (int i=0; i < sortList.size(); i++)
    {
        for (int j=0; j < sortList.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (list.at(sortList.at(j)).list.at(m.inTimeList.at(1)) ==
                    list.at(sortList.at(i)).list.at(m.inTimeList.at(1)))
            {
                //比例符合就调换
                float v1 = list.at(sortList.at(i)).list.at(m.inTimeList.at(1)-1).toFloat();
                float v2 = list.at(sortList.at(j)).list.at(m.inTimeList.at(2)-1).toFloat();
                float v3 = v1/v2;
                if (matchSCal(v3))
                {
                    QString val = list.at(sortList.at(i)).list.at(m.inTimeList.at(2)-1);
                    QStringList tmpList;
                    tmpList << list.at(sortList.at(i)).list.at(m.inTimeList.at(2)-1)
                            <<list.at(sortList.at(i)).list.at(m.inTimeList.at(2))
                            <<list.at(sortList.at(i)).list.at(m.inTimeList.at(2)+1)
                            <<list.at(sortList.at(i)).list.at(m.inTimeList.at(2)+2);
                    list[sortList.at(i)].list[m.inTimeList.at(2)-1] = list.at(sortList.at(j)).list.at(m.inTimeList.at(2)-1);
                    list[sortList.at(i)].list[m.inTimeList.at(2)] = list.at(sortList.at(j)).list.at(m.inTimeList.at(2));
                    list[sortList.at(i)].list[m.inTimeList.at(2)+1] = list.at(sortList.at(j)).list.at(m.inTimeList.at(2)+1);
                    list[sortList.at(i)].list[m.inTimeList.at(2)+2] = list.at(sortList.at(j)).list.at(m.inTimeList.at(2)+2);
                    list[sortList.at(j)].list[m.inTimeList.at(2)-1] = tmpList.at(0);
                    list[sortList.at(j)].list[m.inTimeList.at(2)] = tmpList.at(1);
                    list[sortList.at(j)].list[m.inTimeList.at(2)+1] = tmpList.at(2);
                    list[sortList.at(j)].list[m.inTimeList.at(2)+2] = tmpList.at(3);
                    //重新计算AC列的和
                    float vv1 = list.at(sortList.at(i)).list.at(m.inTimeList.at(0)-1).toFloat();
                    float vv2 = list.at(sortList.at(i)).list.at(m.inTimeList.at(1)-1).toFloat();
                    float vv3 = list.at(sortList.at(i)).list.at(m.inTimeList.at(2)-1).toFloat();
                    list[sortList.at(i)].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);

                    vv1 = list.at(sortList.at(j)).list.at(m.inTimeList.at(0)-1).toFloat();
                    vv2 = list.at(sortList.at(j)).list.at(m.inTimeList.at(1)-1).toFloat();
                    vv3 = list.at(sortList.at(j)).list.at(m.inTimeList.at(2)-1).toFloat();
                    list[sortList.at(j)].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);
                    qDebug()<<QString("行%1和行%2符合错行,调换.").arg(list.at(sortList.at(i)).row+1).arg(list.at(sortList.at(j)).row+1);
                }
            }
        }
    }
}
#define delta 0.000001
bool Widget::matchSCal(float v)
{
    if ((v > (1.05-delta) && v < (1.05+delta))
            || (v > (0.8-delta) && v < (0.8+delta))
            || (v > (0.925-delta) && v < (0.925+delta))
            || (v > (1.68-delta) && v < (1.68+delta))
            || (v > (0.45-delta) && v < (0.45+delta)))
    {
        return true;
    }
        return false;
}

class CIndex
{
public:
    CIndex(int resclevel, QList<SData> &list, QList<int> muchCol, QList<int> inTimeList);
    ~CIndex();
    virtual bool add();
    virtual float sum();
    virtual bool checkDate(QDate date);
    QDate baseTime();
    void setChecked();
    virtual void orderData();
    virtual bool hasTmpData(QList<int> matchIndex);
    virtual QList<SData> getTmpData(QList<int> matchIndex);
    QString getLine();
    QString getIndex();
    QString getTmpLine();
    SData &data(int i);
    int getCurCount();
    QList<int> getMatchIndex();
protected:
    bool addOne();
    virtual bool check();
    int index[10];
    QList<SData> &m_list;
    int curCount;
    int col;
    int payCol;
    QList<int> inTime;
    int minCol;
    int rowCount;//匹配到行数
    int MaxCount;
};

class CRIndex : public CIndex
{
public:
    CRIndex(int resclevel, QList<SData> &list, QList<int> muchCol, QList<int> inTimeList);
    ~CRIndex();
    void reset();
    bool add();
    float sum();
    bool checkDate(QDate date);
    bool hasTmpData(QList<int> matchIndex);
    QList<SData> getTmpData(QList<int> matchIndex);
//    QString getLine();
//    QString getIndex();
//    QString getTmpLine();
//    SData &data();
    int getCurIndex(int i);
//    QList<int> getMatchIndex();
private:
    bool check();
};

CIndex::CIndex(int resclevel, QList<SData> &list, QList<int> muchCol, QList<int> inTimeList)
 : m_list(list)
{
    MaxCount = resclevel;
    rowCount = 0;
    curCount = 1;
    col = muchCol.at(0);
    payCol = muchCol.at(1);
    inTime = inTimeList;
//    index = new int[MaxCount];
    for (int i=0; i < 10; i++)
    {
        index[i] = -1;
    }
    minCol = inTimeList.at(0);
    for (int i=1; i < inTimeList.size(); i++)
    {
        minCol = minCol<inTimeList.at(i)?minCol:inTimeList.at(i);
    }
}

CIndex::~CIndex()
{
//    delete [] index;
}

bool CIndex::add()
{
    if (!addOne())
    {
        return false;
    }
    while (!check())
    {
        if (!addOne())
        {
            return false;
        }
    }
    return true;
}

float CIndex::sum()
{
    float ret = 0;
    for (int i=0; i < curCount; i++)
    {
        ret += m_list.at(index[i]).list.at(col).toFloat();
    }
    return ret;
}

bool CIndex::checkDate(QDate date)
{
    for (int i=0; i < curCount; i++)
    {
        for (int j=0; j < inTime.size(); j++)
        {
            QDate tmp = QDate::fromString(m_list.at(index[i]).list.at(j), TimeFormate);
            if (tmp.daysTo(date) > 7)
            {
                qDebug()<<"over 7 days";
                return false;
            }
        }
    }
    return true;
}

QDate CIndex::baseTime()
{
    for (int i=0; i < curCount; i++)
    {
         if (!m_list.at(index[i]).list.at(inTime.at(0)).isEmpty())
         {
            return QDate::fromString(m_list.at(index[i]).list.at(inTime.at(0)), TimeFormate);
         }
         if (!m_list.at(index[i]).list.at(inTime.at(1)).isEmpty())
         {
            return QDate::fromString(m_list.at(index[i]).list.at(inTime.at(1)), TimeFormate);
         }
         if (!m_list.at(index[i]).list.at(inTime.at(2)).isEmpty())
         {
            return QDate::fromString(m_list.at(index[i]).list.at(inTime.at(2)), TimeFormate);
         }
    }

}

void CIndex::setChecked()
{
    for (int i=0; i < curCount; i++)
    {
        m_list[index[i]].isChecked = true;
    }
}

void CIndex::orderData()
{
    qDebug()<<QString/*::fromLocal8Bit*/("匹配到数据,index %1-%2").arg(getIndex()).arg(getLine());
    QList<SData> data;
    //排序
    QList<int> BitToSmall;
    int base = index[0];
    BitToSmall.push_back(base);
    for (int i=1; i < curCount; i++)
    {
        for (int j=0; j < BitToSmall.size(); j++)
        {
            if (BitToSmall.first() < index[i])
            {
                BitToSmall.push_front(index[i]);
                break;
            }
            else if (BitToSmall.last() > index[i])
            {
                BitToSmall.push_back(index[i]);
                break;
            }
            else if (BitToSmall.at(j) > index[i] && BitToSmall.at(j+1) < index[i])
            {
                BitToSmall.insert(j+1, index[i]);
                break;
            }
        }
    }

    for (int i=0; i < curCount; i++)
    {
        data.push_back(m_list[index[i]]);
    }
    for (int i=0; i < BitToSmall.size(); i++)
    {
        m_list.removeAt(BitToSmall.at(i));
    }
    for (int i=0; i < data.size(); i++)
    {
        m_list.insert(i, data.at(i));
    }
    rowCount += BitToSmall.size();

    //重置index;
    for (int i=0; i < curCount; i++)
    {
//        if (rowCount == m_list.size())
//        {
//            index[i] = rowCount-1;
//        }
//        else
//        {
//           index[i] = rowCount;
//        }
        index[i] = rowCount-1;
    }
    qDebug()<<QString/*::fromLocal8Bit*/("匹配到数据,从index %1开始匹配").arg(getIndex());
}

bool CIndex::hasTmpData(QList<int> matchIndex)
{
    for (int i=0; i < curCount; i++)
    {
        if (!matchIndex.contains(index[i]) && !m_list[index[i]].list.at(payCol).isEmpty())
        {
            return true;
        }
    }
    return false;
//    if (curCount == 1)
//    {
//        if (matchIndex.size() == 1)
//        {
//            if (index[0] == matchIndex.at(0))
//            {
//                return false;
//            }
//        }
//        else
//        {
//            if (index[0] == matchIndex.at(0) || index[0] == matchIndex.at(1))
//            {
//                return false;
//            }
//        }
//    }
//    else
//    {
//        if (matchIndex.size() == 1)
//        {
//            if (index[0] == matchIndex.at(0))
//            {
//                return false;
//            }
//        }
//        else
//        {
//            if (matchIndex.contains(index[0]) && matchIndex.contains(index[1]))
//            {
//                return false;
//            }
//        }
//    }

//    for (int i=0; i < curCount; i++)
//    {
//        if (!m_list[index[i]].list.at(payCol).isEmpty())
//        {
//            return true;
//        }
//    }
//    return false;
}

QList<SData> CIndex::getTmpData(QList<int> matchIndex)
{
    QList<SData> ret;
    for (int i=0; i < curCount; i++)
    {
        if (!matchIndex.contains(index[i]) && !m_list[index[i]].list.at(payCol).isEmpty())
        {
            SData tmp = m_list[index[i]];
            for (int n=minCol-1; n < payCol; n++)
            {
                tmp.list[n] = "";
            }
            tmp.isChecked = false;
            tmp.list.last().replace("\r", "");
            tmp.list.push_back(QString/*::fromLocal8Bit*/("临时列"));
            if (i != 0)
            {
                m_list[index[i]].list[payCol] = "";
            }
            ret.push_back(tmp);
        }
    }
    return ret;
}

QString CIndex::getLine()
{
    QString ret;
    for (int i=0; i < curCount; i++)
    {
        if (i > 0)
        {
            ret += ",";
        }
        if (curCount > 6)
        {
            qDebug()<<QString/*::fromLocal8Bit*/("匹配到多于6项！！！！！！！！！！！！！！！！！！！！！");
        }
        ret += QString::number(m_list.at(index[i]).row+1);
    }
    return ret;
}

QString CIndex::getIndex()
{
    QString ret;
    for (int i=0; i < curCount; i++)
    {
        if (i > 0)
        {
            ret += ",";
        }
        ret += QString::number(index[i]);
    }
    return ret;
}

QString CIndex::getTmpLine()
{
    QString ret;
    for (int i=0; i < curCount; i++)
    {
        if (!m_list[index[i]].list.at(col).isEmpty())
        {
            if (!ret.isEmpty())
            {
                ret += ",";
            }
            ret += QString::number(m_list.at(index[i]).row+1);
        }
    }
    return ret;
}

SData &CIndex::data(int i)
{
    return m_list[index[i]];
}

int CIndex::getCurCount()
{
    return curCount;
}

QList<int> CIndex::getMatchIndex()
{
    QList<int> ret;
    for (int i=0; i < curCount; i++)
    {
        ret.push_back(index[i]);
    }
    return ret;
}

//QString CIndex::copyData(SData data)
//{
//    for (int n=payCol; n < data.list.size(); n++)
//    {
//        if (n < m_list[index[0]].list.size())
//        {
//            m_list[index[0]].list[n] = data.list[n];
//        }
//    }
//}

bool CIndex::addOne()
{
//    for (int i=0; i < 5; i++)
//    {
//        index[i]++;
//        if (index[i] == m_list.size())
//        {

//        }
//        index[i] = 0;
//        index[i+1]++;
//    }
    if (curCount > m_list.size())
    {
        return false;
    }
    int i=0;
    while((++index[i]) == m_list.size())
    {
        index[i] = 0;
        if (++i == curCount)
        {
            if (curCount == MaxCount)
            {
                return false;
            }
            else
            {
                curCount++;
            }
        }
    }
    return true;
//    index[0]++;
//    if (index[0] >= m_list.size())
//    {
//        index[0] = 0;
//        index[1]++;
//        if (index[1] >= m_list.size())
//        {
//            index[1] = 0;
//            index[2]++;
//            if (index[2] >= m_list.size())
//            {
//                index[2] = 0;
//                index[3]++;
//                if (index[3] >= m_list.size())
//                {
//                    index[3] = 0;
//                    index[4]++;
//                    if (index[4] == m_list.size())
//                    {
//                        return false;
//                    }
//                }
//            }
//        }
//    }
//    return true;
}

bool CIndex::check()
{
    if (curCount > m_list.size())
    {
        return false;
    }
    //不能存在相同的index
    for (int i=0; i < curCount; i++)
    {
        for (int j=0; j < curCount; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (index[i] == index[j])
            {
                return false;
            }
        }
    }
    for (int i=0; i < curCount; i++)
    {
        if (m_list.at(index[i]).isChecked)
        {
            return false;
        }
    }
    return true;
}

void Widget::rescMatch(const SMatch m, QList<SData> &list)
{
    float scaleVal = -1;
    for (int i=0; i < list.size(); i++)
    {
        if (list.at(i).isChecked &&
                !list.at(m.inTimeList.at(1)-1).isEmpty() &&
                !list.at(m.inTimeList.at(2)-1).isEmpty())
        {
            scaleVal = list.at(i).list.at(m.inTimeList.at(1)-1).toFloat()/list.at(i).list.at(m.inTimeList.at(2)-1).toFloat();
        }
    }
    orderMisMatch(m, list);
    matchOtherLine(m, list, scaleVal);

    //匹配金额列直接对应（多行相加对应）

    CIndex cindex(m.maxLevel, list, m.muchList, m.inTimeList);
    CRIndex crindex(m.maxLevel, list, m.muchList, m.inTimeList);
    qDebug()<<QString("开始匹配 %1,共有%2行").arg(list.at(0).list.at(0)).arg(list.size());
    while(cindex.add())
    {
//        qDebug()<<QString("匹配行:%1-%2").arg(cindex.getIndex()).arg(cindex.getLine());
        crindex.reset();
        while (crindex.add())
        {
            float val = cindex.sum() + crindex.sum();
            if (qAbs(val) > 0.001)//判断是否存在金额一样的
            {
                continue;
            }

            if (crindex.getCurCount() == 1)
            {
                int index = crindex.getCurIndex(0);
                QList<int> ununiqueList;
                ununiqueList.push_back(index);
                while (list.indexOf(list.at(index), index+1) != -1)
                {
                    ununiqueList.push_back(index);
                    index++;
                }
                int matchIndex = index;
                if (ununiqueList.size() != 1)
                {
                    qDebug()<<QString/*::fromLocal8Bit*/("检测到相同付款数据,匹配时间,个数为%1.").arg(ununiqueList.size());
                    int minDate = cindex.baseTime().daysTo(QDate::fromString(list.at(index).list.at(m.payColNum), TimeFormate));
                    for (int k=1; k < ununiqueList.size(); k++)
                    {
                        int days = cindex.baseTime().daysTo(QDate::fromString(list.at(ununiqueList.at(k)).list.at(m.payColNum), TimeFormate));
                        if (days < minDate)
                        {
                            minDate = days;
                            matchIndex = k;//匹配时间最近的
                        }
                    }
                }
                cindex.setChecked();
                //判断是否会覆盖数据
                QList<int> matchList;
                matchList.push_back(matchIndex);
                if (cindex.hasTmpData(matchList))
                {
                    //保存临时数据
                    list.append(cindex.getTmpData(matchList));//直接加入循环
                    QString info = QString/*::fromLocal8Bit*/("匹配到付款数据,但源数据付款栏非空。行%1.").arg(cindex.getTmpLine());
                    qDebug()<<info;
                    //                        ui->textEdit_Match->append(info);
                }
                if (matchIndex != cindex.getMatchIndex().at(0))
                {
                    //挪数据
                    for (int n=m.muchList.at(1); n < list.at(matchIndex).list.size(); n++)
                    {
                        if (n < cindex.data(0).list.size())
                        {
                            cindex.data(0).list[n] = list.at(matchIndex).list[n];
                        }
                    }
                    //删除付款金额
                    for (int n=m.muchList.at(1); n < list[matchIndex].list.size(); n++)
                    {
                        list[matchIndex].list[n] = "";
                    }

                    QString info = QString/*::fromLocal8Bit*/("行%1和行%2数据匹配成功！复制数据。").arg(cindex.getLine()).arg(list.at(matchIndex).row+1);
                    qDebug()<<info;
                    //是否删除行
                    bool canDel = true;
                    for (int n=0; n < m.inTimeList.size(); n++)
                    {
                        if (!list.at(matchIndex).list.at(m.inTimeList.at(n)).isEmpty())
                        {
                            canDel = false;
                            break;
                        }
                    }
                    if (canDel)
                    {
                        //                            qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间为空，删除。").arg(listData.at(j).row+1);;
                        //                hashDel.insert(matchIndex, matchIndex);
                        list[matchIndex].canDel = true;
                        list[matchIndex].isChecked = true;
                    }
                    else
                    {
                        list[matchIndex].canDel = false;
                        qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间非空，不删除。").arg(list.at(matchIndex).row+1);;
                    }
                }

                cindex.orderData();
                break;
            }
            else
            {
                cindex.setChecked();
                //判断是否会覆盖数据
                if (cindex.hasTmpData(crindex.getMatchIndex()) || crindex.hasTmpData(cindex.getMatchIndex()))
                {
                    //保存临时数据
                    list.append(cindex.getTmpData(crindex.getMatchIndex()));//直接加入循环
                    list.append(crindex.getTmpData(cindex.getMatchIndex()));
    //                QString info = QString/*::fromLocal8Bit*/("匹配到付款数据,但源数据付款栏非空。行%1.").arg(cindex.getTmpLine());
    //                qDebug()<<info;
    //                        ui->textEdit_Match->append(info);
                }

                //挪数据
                QList<SData> ldata;
                for (int n=0; n < crindex.getCurCount(); n++)
                {
                    ldata.push_back(crindex.data(n));
                }
                if (cindex.getCurCount() == 1)
                {
                    if (!crindex.getMatchIndex().contains(cindex.getMatchIndex().at(0)))
                    {
                        for (int n=m.muchList.at(1); n < ldata.at(0).list.size(); n++)
                        {
                            if (n < cindex.data(0).list.size())
                            {
                                cindex.data(0).list[n] = ldata.at(0).list[n];
                                cindex.data(0).list[n].replace("\r", "");
                            }
                        }
                        for (int n=m.muchList.at(1); n < list[crindex.getCurIndex(0)].list.size(); n++)
                        {
                            list[crindex.getCurIndex(0)].list[n] = "";
                        }

                        for (int i = 0; i < crindex.getCurCount(); i++)
                        {
                            list[crindex.getCurIndex(i)].isChecked = true;
                            list[crindex.getCurIndex(i)].canDel = true;
                        }
                    }
                    else
                    {
                        int index = -1;
                        for (int i = 0; i < crindex.getCurCount(); i++)
                        {
                            list[crindex.getCurIndex(i)].isChecked = true;
                            if (crindex.getCurIndex(i) == cindex.getMatchIndex().at(0))
                            {
                                index = crindex.getCurIndex(i);
                                list[crindex.getCurIndex(i)].canDel = false;
                            }
                            else
                            {
                                ldata.removeLast();
                                ldata.push_back(list[crindex.getCurIndex(i)]);
                                list[crindex.getCurIndex(i)].canDel = true;
                            }
                        }
                    }
//                    qDebug()<<QString("1111111111111111111111111111111111111111111111111111111111");
                }
                else
                {
                    //删除付款金额
                    for (int i=0; i < crindex.getCurCount(); i++)
                    {
                        for (int n=m.muchList.at(1); n < list[crindex.getCurIndex(i)].list.size(); n++)
                        {
                            list[crindex.getCurIndex(i)].list[n] = "";
                        }

                        list[crindex.getCurIndex(i)].isChecked = true;
                        if (!cindex.getMatchIndex().contains(crindex.getCurIndex(i)))
                        {
                            list[crindex.getCurIndex(i)].canDel = true;
                        }
                    }
                    for (int i=0; i < ldata.size(); i++)
                    {
                        for (int n=m.muchList.at(1); n < ldata.at(i).list.size(); n++)
                        {
                            if (n < cindex.data(i).list.size())
                            {
                                cindex.data(i).list[n] = ldata.at(i).list[n];
                                cindex.data(i).list[n].replace("\r", "");
                            }
                        }
                    }
                }


                QString info = QString/*::fromLocal8Bit*/("行%1和行%2数据匹配成功！复制数据。").arg(cindex.getLine()).arg(crindex.getLine());
                qDebug()<<info;
                //是否删除行

//                for (int n=0; n < m.inTimeList.size(); n++)
//                {
//                    if (!list.at(matchIndex).list.at(m.inTimeList.at(n)).isEmpty())
//                    {
//                        canDel = false;
//                        break;
//                    }
//                }
//                if (canDel)
//                {
//    //                            qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间为空，删除。").arg(listData.at(j).row+1);;
//    //                hashDel.insert(matchIndex, matchIndex);
//                    list[matchIndex].canDel = true;
//                    list[matchIndex].isChecked = true;
//                }
//                else
//                {
//                    list[matchIndex].canDel = false;
//                    qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间非空，不删除。").arg(list.at(matchIndex).row+1);;
//                }
                cindex.orderData();
                if (crindex.getCurCount() > cindex.getCurCount())
                {
                    list.insert(1, ldata.at(1));
                    list[1].isChecked = true;
                    for (int n=m.minInTime-1; n < m.muchList.at(0); n++)
                    {
                        if (n < list[1].list.size())
                        {
                            list[1].list[n] = "";
                        }
                    }
                    qDebug()<<QString/*::fromLocal8Bit*/("付款多于账单----------%1-%2").arg(cindex.getTmpLine()).arg(crindex.getLine());
                }
                break;
            }
        }
    }

    adjustMCol(m, list);
//        for (int j=0; j < list.size(); j++)
//        {
//            if (list.at(j).isChecked)
//            {
//                continue;
//            }

//            if (list.at(j).list.at(m.muchList.at(1)).isEmpty())
//            {
//                continue;
//            }
//            float val = cindex.sum() + list.at(j).list.at(m.muchList.at(1)).toFloat();
//            if (qAbs(val) > 0.001)//判断是否存在金额一样的
//            {
//                continue;
//            }

//            int index = j+1;
//            QList<int> ununiqueList;
//            ununiqueList.push_back(j);
//            while (list.indexOf(list.at(j), index) != -1)
//            {
//                ununiqueList.push_back(index);
//                index++;
//            }
//            int matchIndex = j;
//            if (ununiqueList.size() != 1)
//            {
//                qDebug()<<QString/*::fromLocal8Bit*/("检测到相同付款数据,匹配时间,个数为%1.").arg(ununiqueList.size());
//                int minDate = cindex.baseTime().daysTo(QDate::fromString(list.at(j).list.at(m.payColNum), TimeFormate));
//                for (int k=1; k < ununiqueList.size(); k++)
//                {
//                    int days = cindex.baseTime().daysTo(QDate::fromString(list.at(ununiqueList.at(k)).list.at(m.payColNum), TimeFormate));
//                    if (days < minDate)
//                    {
//                        minDate = days;
//                        matchIndex = k;//匹配时间最近的
//                    }
//                }
//            }

//            //procMatchData(m, );
//            cindex.setChecked();
//            //判断是否会覆盖数据
//            if (cindex.hasTmpData(matchIndex))
//            {
//                //保存临时数据
//                list.append(cindex.getTmpData(matchIndex));//直接加入循环
//                QString info = QString/*::fromLocal8Bit*/("匹配到付款数据,但源数据付款栏非空。行%1.").arg(cindex.getTmpLine());
//                qDebug()<<info;
////                        ui->textEdit_Match->append(info);
//            }
//            //挪数据
//            for (int n=m.muchList.at(1); n < list.at(matchIndex).list.size(); n++)
//            {
//                if (n < cindex.data().list.size())
//                {
//                    cindex.data().list[n] = list.at(matchIndex).list[n];
//                }
//            }
//            //删除付款金额
//            list[matchIndex].list[m.muchList.at(1)] = "";
//            QString info = QString/*::fromLocal8Bit*/("行%1和行%2数据匹配成功！复制数据。").arg(cindex.getLine()).arg(list.at(matchIndex).row+1);
//            qDebug()<<info;
//            //是否删除行
//            bool canDel = true;
//            for (int n=0; n < m.inTimeList.size(); n++)
//            {
//                if (!list.at(matchIndex).list.at(m.inTimeList.at(n)).isEmpty())
//                {
//                    canDel = false;
//                    break;
//                }
//            }
//            if (canDel)
//            {
////                            qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间为空，删除。").arg(listData.at(j).row+1);;
////                hashDel.insert(matchIndex, matchIndex);
//                list[matchIndex].canDel = true;
//                list[matchIndex].isChecked = true;
//            }
//            else
//            {
//                list[matchIndex].canDel = false;
//                qDebug()<<QString/*::fromLocal8Bit*/("行%1入账时间非空，不删除。").arg(list.at(matchIndex).row+1);;
//            }
//            cindex.orderData();
//            break;
//        }
//    }

    //剩余数据匹配

}

void Widget::rescCat(SMatch m, QList<SData> &list)
{
    for (int i=0; i < list.size(); i++)
    {
        if (list.at(i).list.at(m.inTimeList.at(0)).isEmpty() || list.at(i).canDel || list.at(i).isChecked)
        {
            continue;
        }
        QString strTime0 = list.at(i).list.at(m.inTimeList.at(0));

        int col1 = 0;
        int line1 = -1;
        QList<int> list1;
        for (int j=0; j < list.size(); j++)
        {
            if (list.at(j).list.at(m.inTimeList.at(0)).isEmpty() || list.at(j).canDel || list.at(j).isChecked)
            {
                continue;
            }
            if (list.at(j).list.at(m.inTimeList.at(0)) == strTime0)
            {
                col1++;
                line1 = j;
                list1.push_back(j);
            }
        }

        int col2 = 0;
        int line2 = -1;
        QList<int> list2;
        for (int j=0; j < list.size(); j++)
        {
            if (list.at(j).list.at(m.inTimeList.at(1)).isEmpty() || list.at(j).canDel || list.at(j).isChecked)
            {
                continue;
            }
            if (list.at(j).list.at(m.inTimeList.at(1)) == strTime0)
            {
                col2++;
                line2 = j;
                list2.push_back(j);
            }
        }
        if (col2 == 1)
        {
            qDebug()<<QString("SSSS行%1与行%2匹配日期成功。").arg(list.at(i).row+1).arg(list.at(line2).row+1);
            list[i].list[m.inTimeList.at(1) - 1] = list.at(line2).list.at(m.inTimeList.at(1)-1);
            list[i].list[m.inTimeList.at(1)] = list.at(line2).list.at(m.inTimeList.at(1));
            list[i].list[m.inTimeList.at(1) + 1] = list.at(line2).list.at(m.inTimeList.at(1)+1);
            list[i].list[m.inTimeList.at(1) + 2] = list.at(line2).list.at(m.inTimeList.at(1)+2);
            list[line2].canDel = true;
        }

        int col3 = 0;
        int line3 = -1;
        QList<int> list3;
        for (int j=0; j < list.size(); j++)
        {
            if (list.at(j).list.at(m.inTimeList.at(2)).isEmpty() || list.at(j).canDel || list.at(j).isChecked)
            {
                continue;
            }
            if (list.at(j).list.at(m.inTimeList.at(2)) == strTime0)
            {
                col3++;
                line3 = j;
                list3.push_back(j);
            }
        }
        if (col3 == 1)
        {
            qDebug()<<QString("YYYY行%1与行%2匹配日期成功。").arg(list.at(i).row+1).arg(list.at(line3).row+1);
            list[i].list[m.inTimeList.at(2) - 1] = list.at(line3).list.at(m.inTimeList.at(2)-1);
            list[i].list[m.inTimeList.at(2)] = list.at(line3).list.at(m.inTimeList.at(2));
            list[i].list[m.inTimeList.at(2) + 1] = list.at(line3).list.at(m.inTimeList.at(2)+1);
            list[i].list[m.inTimeList.at(2) + 2] = list.at(line3).list.at(m.inTimeList.at(2)+2);
            list[line3].canDel = true;
        }

        if (col3 == 1 || col2 == 1)
        {
            list[i].isChecked = true;
        }


        if (col1 > 1 && col1 == col2 && col1 == col3)
        {
            for (int j=0; j < list1.size(); j++)
            {
                if (list1.at(j) == list2.at(j) && list1.at(j) == list3.at(j))
                {
                    continue;
                }
                list[list1.at(j)].list[m.inTimeList.at(1) - 1] = list.at(list2.at(j)).list.at(m.inTimeList.at(1)-1);
                list[list1.at(j)].list[m.inTimeList.at(1)] = list.at(list2.at(j)).list.at(m.inTimeList.at(1));
                list[list1.at(j)].list[m.inTimeList.at(1) + 1] = list.at(list2.at(j)).list.at(m.inTimeList.at(1)+1);
                list[list1.at(j)].list[m.inTimeList.at(1) + 2] = list.at(list2.at(j)).list.at(m.inTimeList.at(1)+2);
                if (list1.at(j) != list2.at(j))
                {
                    list[list2.at(j)].canDel = true;
                }

                list[list1.at(j)].list[m.inTimeList.at(2) - 1] = list.at(list3.at(j)).list.at(m.inTimeList.at(2)-1);
                list[list1.at(j)].list[m.inTimeList.at(2)] = list.at(list3.at(j)).list.at(m.inTimeList.at(2));
                list[list1.at(j)].list[m.inTimeList.at(2) + 1] = list.at(list3.at(j)).list.at(m.inTimeList.at(2)+1);
                list[list1.at(j)].list[m.inTimeList.at(2) + 2] = list.at(list3.at(j)).list.at(m.inTimeList.at(2)+2);

                if (list1.at(j) != list3.at(j))
                {
                    list[list3.at(j)].canDel = true;
                }

                list[list1.at(j)].isChecked = true;
                qDebug()<<QString("匹配到多个日期一致的列。%1-%2-%3").arg(list.at(list1.at(j)).row+1).arg(list.at(list2.at(j)).row+1).arg(list.at(list3.at(j)).row+1);
            }
        }

//        int col4 = 0;
//        int line4 = -1;
//        for (int j=0; j < list.size(); j++)
//        {
//            if (list.at(j).list.at(m.payColNum).isEmpty())
//            {
//                continue;
//            }
//            if (list.at(j).list.at(m.payColNum) == strTime0)
//            {
//                col4++;
//                line4 = j;
//            }
//        }
//        if (col4 == 1)
//        {
//            qDebug()<<QString("行%1与行%2匹配日期成功。").arg(list.at(i).row+1).arg(list.at(line4).row+1);
//            for (int j=0; j < list.at(line4).list.size(); j++)
//            {
//                list[i].list[j] = list.at(line4).list.at(j);
//            }
//            list[line4].canDel = true;
//        }
//        else if(col4 > 1)
//        {
//            qDebug()<<QString("行%1存在%2个相同日期，无法匹配。").arg(list.at(i).row+1).arg(col4);
//        }

        //累加AC
        float vv1 = list.at(i).list.at(m.inTimeList.at(0)-1).toFloat();
        float vv2 = list.at(i).list.at(m.inTimeList.at(1)-1).toFloat();
        float vv3 = list.at(i).list.at(m.inTimeList.at(2)-1).toFloat();
        list[i].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);
    }
}

void Widget::adjustMCol(SMatch m, QList<SData> &list)
{
    for (int i=0; i < list.size(); i++)
    {
        if (list.at(i).list.at(m.muchList.at(0)).isEmpty())
        {
            continue;
        }
        if (list.at(i).list.at(m.muchList.at(0)) == "0")
        {
            continue;
        }
        if (list.at(i).list.at(m.muchList.at(1)).isEmpty())
        {
            continue;
        }
        if (list.at(i).list.at(m.muchList.at(1)) == "0")
        {
            continue;
        }

        float var = list.at(i).list.at(m.muchList.at(0)).toFloat()
                + list.at(i).list.at(m.muchList.at(1)).toFloat();
        if (var > -0.0001 && var < 0.0001)//0
        {
            continue;
        }

        if (i+1 >= list.size())
        {
            continue;
        }
        int j = i+1;

        if (list.at(j).list.at(m.muchList.at(0)).isEmpty())
        {
            continue;
        }
        if (list.at(j).list.at(m.muchList.at(0)) == "0")
        {
            continue;
        }
        if (list.at(j).list.at(m.muchList.at(1)).isEmpty())
        {
            continue;
        }
        if (list.at(j).list.at(m.muchList.at(1)) == "0")
        {
            continue;
        }

        float var2 = list.at(j).list.at(m.muchList.at(0)).toFloat()
                + list.at(j).list.at(m.muchList.at(1)).toFloat();
        if (var2 > -0.0001 && var2 < 0.0001)//0
        {
            continue;
        }

        float sum = var + var2;
        if (sum < -0.0001 || sum > 0.0001)//非0
        {
            continue;
        }
        float sum1 = list.at(i).list.at(m.inTimeList.at(0)-1).toFloat()
                + list.at(j).list.at(m.inTimeList.at(1)-1).toFloat()
                + list.at(j).list.at(m.inTimeList.at(2)-1).toFloat();
        float sum2 = list.at(j).list.at(m.inTimeList.at(0)-1).toFloat()
                + list.at(i).list.at(m.inTimeList.at(1)-1).toFloat()
                + list.at(i).list.at(m.inTimeList.at(2)-1).toFloat();
        float af1 = list.at(i).list.at(m.muchList.at(1)).toFloat();
        float af2 = list.at(j).list.at(m.muchList.at(1)).toFloat();
        if ((((sum1 + af1) > -0.0001 && (sum1 + af1) < 0.0001)
             && ((sum2 + af2) > -0.0001 && (sum2 + af2) < 0.0001)))
        {
            qDebug()<<QString("发现行%1和行%2第一列金额错位，调换").arg(i+3).arg(j+3);
            QStringList listTmp;
            listTmp<<list.at(i).list.at(m.inTimeList.at(1)-1)
                  <<list.at(i).list.at(m.inTimeList.at(1))
                 <<list.at(i).list.at(m.inTimeList.at(1)+1)
                <<list.at(i).list.at(m.inTimeList.at(1)+2)
               <<list.at(i).list.at(m.inTimeList.at(2)-1)
              <<list.at(i).list.at(m.inTimeList.at(2))
             <<list.at(i).list.at(m.inTimeList.at(2)+1)
            <<list.at(i).list.at(m.inTimeList.at(2)+2);
            list[i].list[m.inTimeList.at(1)-1] = list[j].list[m.inTimeList.at(1)-1];
            list[i].list[m.inTimeList.at(1)] = list[j].list[m.inTimeList.at(1)-1];
            list[i].list[m.inTimeList.at(1)+1] = list[j].list[m.inTimeList.at(1)-1];
            list[i].list[m.inTimeList.at(1)+2] = list[j].list[m.inTimeList.at(1)-1];
            list[i].list[m.inTimeList.at(2)-1] = list[j].list[m.inTimeList.at(2)-1];
            list[i].list[m.inTimeList.at(2)] = list[j].list[m.inTimeList.at(2)-1];
            list[i].list[m.inTimeList.at(2)+1] = list[j].list[m.inTimeList.at(2)-1];
            list[i].list[m.inTimeList.at(2)+2] = list[j].list[m.inTimeList.at(2)-1];
            float sumAC1 = list[i].list[m.inTimeList.at(0)-1].toFloat()
                    + list[i].list[m.inTimeList.at(1)-1].toFloat()
                    + list[i].list[m.inTimeList.at(2)-1].toFloat();
            list[i].list[m.muchList.at(0)] = QString::number(sumAC1);


            list[j].list[m.inTimeList.at(1)-1] = listTmp.at(0);
            list[j].list[m.inTimeList.at(1)] = listTmp.at(1);
            list[j].list[m.inTimeList.at(1)+1] = listTmp.at(2);
            list[j].list[m.inTimeList.at(1)+2] = listTmp.at(3);
            list[j].list[m.inTimeList.at(2)-1] = listTmp.at(4);
            list[j].list[m.inTimeList.at(2)] = listTmp.at(5);
            list[j].list[m.inTimeList.at(2)+1] = listTmp.at(6);
            list[j].list[m.inTimeList.at(2)+2] = listTmp.at(7);
            float sumAC2 = list[j].list[m.inTimeList.at(0)-1].toFloat()
                    + list[j].list[m.inTimeList.at(1)-1].toFloat()
                    + list[j].list[m.inTimeList.at(2)-1].toFloat();
            list[j].list[m.muchList.at(0)] = QString::number(sumAC2);
        }
        else if ((((sum1 + af2) > -0.0001 && (sum1 + af2) < 0.0001)
                  && ((sum2 + af1) > -0.0001 && (sum2 + af1) < 0.0001)))
        {
            qDebug()<<QString("发现行%1和行%2第一列金额错位，调换").arg(i+3).arg(j+3);
            QStringList listTmp;
            listTmp<<list.at(i).list.at(m.inTimeList.at(0)-1)
                  <<list.at(i).list.at(m.inTimeList.at(0))
                 <<list.at(i).list.at(m.inTimeList.at(0)+1)
                <<list.at(i).list.at(m.inTimeList.at(0)+2);
            list[i].list[m.inTimeList.at(0)-1] = list[j].list[m.inTimeList.at(0)-1];
            list[i].list[m.inTimeList.at(0)] = list[j].list[m.inTimeList.at(0)-1];
            list[i].list[m.inTimeList.at(0)+1] = list[j].list[m.inTimeList.at(0)-1];
            list[i].list[m.inTimeList.at(0)+2] = list[j].list[m.inTimeList.at(0)-1];
            float sumAC1 = list[i].list[m.inTimeList.at(0)-1].toFloat()
                    + list[i].list[m.inTimeList.at(1)-1].toFloat()
                    + list[i].list[m.inTimeList.at(2)-1].toFloat();
            list[i].list[m.muchList.at(0)] = QString::number(sumAC1);

            list[j].list[m.inTimeList.at(0)-1] = listTmp.at(0);
            list[j].list[m.inTimeList.at(0)] = listTmp.at(1);
            list[j].list[m.inTimeList.at(0)+1] = listTmp.at(2);
            list[j].list[m.inTimeList.at(0)+2] = listTmp.at(3);
            float sumAC2 = list[j].list[m.inTimeList.at(0)-1].toFloat()
                    + list[j].list[m.inTimeList.at(1)-1].toFloat()
                    + list[j].list[m.inTimeList.at(2)-1].toFloat();
            list[j].list[m.muchList.at(0)] = QString::number(sumAC2);
        }
    }
}

void Widget::matchOtherLine(SMatch m, QList<SData> &list, float val)
{
    for (int i=0; i < list.size(); i++)
    {
        if (list.at(i).isChecked)
        {
            continue;
        }
        if (list.at(i).isAbsolute)
        {
            continue;
        }
        for (int j=0; j < list.size(); j++)
        {
            if (list.at(j).isChecked)
            {
                continue;
            }
            if (list.at(j).isAbsolute)
            {
                continue;
            }
            if (i == j)
            {
                continue;//是否存在bc列在一行的情况?
            }
            if (list.at(i).list.at(m.inTimeList.at(1)-1).isEmpty() || list.at(j).list.at(m.inTimeList.at(2)-1).isEmpty())
            {
                continue;
            }
            if (list.at(i).list.at(m.inTimeList.at(2)-1) == list.at(j).list.at(m.inTimeList.at(2)-1))
            {
                continue;
            }
            //比例符合就调换
            float v1 = list.at(i).list.at(m.inTimeList.at(1)-1).toFloat();
            float v2 = list.at(j).list.at(m.inTimeList.at(2)-1).toFloat();

            float v3 = v1/v2;
            if (val > 0 && qAbs(v3 - val)>0.001)
            {
                continue;
            }
            if (matchSCal(v3))
            {
                if (val < 0)
                {
                    val = v3;
                }
                assert(qAbs(v3 - val) < 0.001);
                QDate date2;
                if (list.at(i).list.at(m.inTimeList.at(1)).contains("-"))
                {
                    date2 = QDate::fromString(list.at(i).list.at(m.inTimeList.at(1)), TimeFormate);
                }
                else
                {
                    date2 = QDate::fromString(list.at(i).list.at(m.inTimeList.at(1)), TimeFormate2);
                }

                QDate date3;
                if (list.at(j).list.at(m.inTimeList.at(2)).contains("-"))
                {
                    date3 = QDate::fromString(list.at(j).list.at(m.inTimeList.at(2)), TimeFormate);
                }
                else
                {
                    date3 = QDate::fromString(list.at(j).list.at(m.inTimeList.at(2)), TimeFormate2);
                }

                if (qAbs(date2.daysTo(date3)) < 7)
                {
                    qDebug()<<QString("行%1和行%2符合比例关系,合并.%3").arg(list.at(i).row+1).arg(list.at(j).row+1).arg(list.at(i).list.at(m.inTimeList.at(2)));
                    emit add(QString("行%1和行%2符合比例关系,合并.%3").arg(list.at(i).row+1).arg(list.at(j).row+1).arg(list.at(i).list.at(m.inTimeList.at(2))));
                    assert(list.at(i).list.at(m.inTimeList.at(2)).isEmpty());
                    list[i].list[m.inTimeList.at(2)-1] = list.at(j).list.at(m.inTimeList.at(2)-1);
                    list[i].list[m.inTimeList.at(2)] = list.at(j).list.at(m.inTimeList.at(2));
                    list[i].list[m.inTimeList.at(2)+1] = list.at(j).list.at(m.inTimeList.at(2)+1);
                    list[i].list[m.inTimeList.at(2)+2] = list.at(j).list.at(m.inTimeList.at(2)+2);
                    float vv1 = list.at(i).list.at(m.inTimeList.at(0)-1).toFloat();
                    float vv2 = list.at(i).list.at(m.inTimeList.at(1)-1).toFloat();
                    float vv3 = list.at(i).list.at(m.inTimeList.at(2)-1).toFloat();
                    list[i].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);

                    list[j].list[m.inTimeList.at(2)-1] = "";
                    list[j].list[m.inTimeList.at(2)] = "";
                    list[j].list[m.inTimeList.at(2)+1] = "";
                    list[j].list[m.inTimeList.at(2)+2] = "";
                    vv1 = list.at(j).list.at(m.inTimeList.at(0)-1).toFloat();
                    vv2 = list.at(j).list.at(m.inTimeList.at(1)-1).toFloat();
                    vv3 = list.at(j).list.at(m.inTimeList.at(2)-1).toFloat();
                    list[j].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);
                    if (list.at(j).list.at(m.inTimeList.at(0)).isEmpty() &&
                            list.at(j).list.at(m.inTimeList.at(1)).isEmpty() &&
                            list.at(j).list.at(m.inTimeList.at(2)).isEmpty() &&
                            list.at(j).list.at(m.payColNum).isEmpty())
                    {
                        list[j].isChecked = true;
                        list[j].canDel = true;
                    }
                    QList<int> listInTime1;
                    for (int k=0; k < list.size(); k++)
                    {
                        if (list.at(k).isChecked)
                        {
                            continue;
                        }
                        QDate date1;
                        if (list.at(k).list.at(m.inTimeList.at(0)).contains("-"))
                        {
                            date1 = QDate::fromString(list.at(k).list.at(m.inTimeList.at(0)), TimeFormate);
                        }
                        else
                        {
                            date1 = QDate::fromString(list.at(k).list.at(m.inTimeList.at(0)), TimeFormate2);
                        }
                        if (date1 == date2 || date1 == date3)
                        {
                            listInTime1.push_back(k);
                        }
                    }
                    if (listInTime1.size() == 0)
                    {
                        qDebug()<<QString("未找到可以匹配的首列数据.");
                    }
                    else if (listInTime1.size() == 1)
                    {
                        qDebug()<<QString("行%1和行%2-%3日期相同且只有一个,合并.").arg(list.at(listInTime1.at(0)).row+1).arg(list.at(i).row+1).arg(list.at(j).row+1);

                        emit add(QString("行%1和行%2-%3日期相同且只有一个,合并.").arg(list.at(listInTime1.at(0)).row+1).arg(list.at(i).row+1).arg(list.at(j).row+1));
                        if (listInTime1.at(0) == i)
                        {
                            vv1 = list.at(i).list.at(m.inTimeList.at(0)-1).toFloat();
                            vv2 = list.at(i).list.at(m.inTimeList.at(1)-1).toFloat();
                            vv3 = list.at(i).list.at(m.inTimeList.at(2)-1).toFloat();
                            list[i].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);
                        }
                        else
                        {
                            if (!list.at(i).list.at(m.inTimeList.at(0)).isEmpty())
                            {
                                SData data = list.at(i);
                                for (int k=m.inTimeList.at(1)-1; k < data.list.size(); k++)
                                {
                                    data.list[k] = "";
                                }
                                data.list[m.muchList.at(0)] = list.at(i).list.at(m.inTimeList.at(0));
                                list.push_back(data);
                            }
                            list[i].list[m.inTimeList.at(0)-1] = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(0)-1);
                            list[i].list[m.inTimeList.at(0)] = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(0));
                            list[i].list[m.inTimeList.at(0)+1] = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(0)+1);
                            list[i].list[m.inTimeList.at(0)+2] = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(0)+2);
//                            list[i].list[m.inTimeList.at(0)] = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(0));
                            vv1 = list.at(i).list.at(m.inTimeList.at(0)-1).toFloat();
                            vv2 = list.at(i).list.at(m.inTimeList.at(1)-1).toFloat();
                            vv3 = list.at(i).list.at(m.inTimeList.at(2)-1).toFloat();
                            list[i].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);

                            list[listInTime1.at(0)].list[m.inTimeList.at(0)-1] = "";
                            list[listInTime1.at(0)].list[m.inTimeList.at(0)] = "";
                            list[listInTime1.at(0)].list[m.inTimeList.at(0)+1] = "";
                            list[listInTime1.at(0)].list[m.inTimeList.at(0)+2] = "";
                            vv1 = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(0)-1).toFloat();
                            vv2 = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(1)-1).toFloat();
                            vv3 = list.at(listInTime1.at(0)).list.at(m.inTimeList.at(2)-1).toFloat();
                            list[listInTime1.at(0)].list[m.muchList.at(0)] = QString::number(vv1 + vv2 + vv3);

                        }
                    }
                    else
                    {
                        qDebug()<<QString("--------------------发现多个同一日期的M列,无法处理!");
                        emit add(QString("发现多个同一日期的M列,无法处理!"));
                    }
                }
            }
        }
    }
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

bool Widget::getColList(QString cols, QList<int> &list)
{
    cols.replace("；",";");
    QStringList strList = cols.split(";");

    list.clear();
    for (int i=0; i < strList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(strList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString/*::fromLocal8Bit*/("未识别的匹配列:%1！").arg(strList.at(i));
            QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
            return false;
        }
        list.push_back(ite.value());
    }
    return true;
}

bool Widget::getCol(QString col, int &colNum)
{
    QHash<QString, int>::iterator ite = g_hashColumn.find(col);
    if (ite == g_hashColumn.end())
    {
        QString err = QString/*::fromLocal8Bit*/("未识别的匹配列:%1！").arg(col);
        QMessageBox::warning(this, QString/*::fromLocal8Bit*/("警告"), err, QMessageBox::Ok);
        return false;
    }
    colNum = ite.value();
    return true;
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

matchTask::matchTask(SMatch m, QList<SData> &list, Widget *p)
    : m_m(m), m_list(list), m_p(p)
{

}

void matchTask::run()
{
    g_mutex.lock();
    g_Task.push_back(m_list.at(0).list.at(m_m.NameColNum));
    g_mutex.unlock();
    m_p->rescMatch(m_m, m_list);
    g_mutex.lock();
    g_Task.removeOne(m_list.at(0).list.at(m_m.NameColNum));
    g_mutex.unlock();
}

CRIndex::CRIndex(int resclevel, QList<SData> &list, QList<int> muchCol, QList<int> inTimeList)
    : CIndex(resclevel, list, muchCol, inTimeList)
{
    MaxCount = 2;
}

CRIndex::~CRIndex()
{

}

void CRIndex::reset()
{
    curCount = 1;
    for (int i=0; i < 10; i++)
    {
        index[i] = 0;
    }
}

bool CRIndex::add()
{
    if (!addOne())
    {
        return false;
    }
    while (!CRIndex::check())
    {
        if (!addOne())
        {
            return false;
        }
    }
    return true;
}

float CRIndex::sum()
{
    float ret = 0;
    for (int i=0; i < curCount; i++)
    {
        ret += m_list.at(index[i]).list.at(payCol).toFloat();
    }
    return ret;
}

bool CRIndex::checkDate(QDate date)
{
    for (int i=0; i < curCount; i++)
    {
        QDate tmp = QDate::fromString(m_list.at(index[i]).list.at(payCol+4), TimeFormate);
        if (tmp.daysTo(date) > 3)
        {
            qDebug()<<"over 3 days";
            return false;
        }
    }
    return true;
}

bool CRIndex::hasTmpData(QList<int> matchIndex)
{
    for (int i=0; i < curCount; i++)
    {
        if (matchIndex.contains(index[i]))
        {
            continue;
        }
        for (int j=0; j < inTime.size(); j++)
        {
            if (!m_list[index[i]].list.at(inTime.at(j)).isEmpty())
            {
                return true;
            }
        }
    }
    return false;
}

QList<SData> CRIndex::getTmpData(QList<int> matchIndex)
{
    QList<SData> ret;
    for (int i=0; i < curCount; i++)
    {
        bool allEmpty = true;
        for (int j=0; j < inTime.size(); j++)
        {
            if (!matchIndex.contains(index[i]) && !m_list[index[i]].list.at(inTime.at(j)).isEmpty())
            {
                allEmpty = false;
                break;
            }
        }
        if (allEmpty)
        {
            continue;
        }
        SData tmp = m_list[index[i]];
        for (int n=payCol-1; n < tmp.list.size(); n++)
        {
            tmp.list[n] = "";
        }
        tmp.isChecked = false;
        tmp.list.last().replace("\r", "");
        tmp.list.push_back(QString/*::fromLocal8Bit*/("临时列"));
        ret.push_back(tmp);
        for (int n=minCol-1; n < payCol-1; n++)
        {
            m_list[index[i]].list[n] = "";
        }
    }
    return ret;
}

int CRIndex::getCurIndex(int i)
{
    return index[i];
}

//QList<int> CRIndex::getMatchIndex()
//{
//    QList<int> ret;
//    for (int i=0; i < curCount; i++)
//    {
//        ret.push_back(index[i]);
//    }
//}

bool CRIndex::check()
{
    if (curCount > m_list.size())
    {
        return false;
    }
    //不能存在相同的index
    for (int i=0; i < curCount; i++)
    {
        for (int j=0; j < curCount; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (index[i] == index[j])
            {
                return false;
            }
        }
    }
    for (int i=0; i < curCount; i++)
    {
        if (m_list.at(index[i]).isChecked)
        {
            return false;
        }
    }
    for (int i=0; i < curCount; i++)
    {
        if (m_list.at(index[i]).list.at(payCol).isEmpty()
                || m_list.at(index[i]).list.at(payCol).contains("-"))
        {
            return false;
        }
    }
    return true;
}
