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
    ui->lineEdit_SortColumn->setText("AF;AJ;AK");
    ui->lineEdit_DataColumn->setText("M;S;Y");
    ui->lineEdit_Out->setText("out.csv");

    ui->lineEdit_FolderSplit->setText("A;B");
    ui->lineEdit_TableSplit->setText("A;B;D");
    initHash();
    connect(ui->pBtn_SelectFile, SIGNAL(clicked(bool)), this, SLOT(onSelectFile()));
    connect(ui->pBtn_SelectSplitFile, SIGNAL(clicked(bool)), this, SLOT(onSelectSplitFile()));
    connect(ui->pBtn_Proc, SIGNAL(clicked(bool)), this, SLOT(onProc()));
    connect(ui->pBtn_Split, SIGNAL(clicked(bool)), this, SLOT(onSplit()));
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
//                   qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，均无数据，不追加").arg(listData.at(index).row+1).arg(data.row+1);
//                   continue;
//               }
//               else if (!data.isEmpty() && !listData.at(index).isEmpty())
//               {
//                   qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，均有数据").arg(listData.at(index).row+1).arg(data.row+1);
//               }
//               else if (data.isEmpty() && !listData.at(index).isEmpty())
//               {
//                   qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，前有数据，后无数据，不追加").arg(listData.at(index).row+1).arg(data.row+1);
//                   continue;
//               }
//               else if (!data.isEmpty() && listData.at(index).isEmpty())
//               {
//                   qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，前无数据，后有数据，删前者，追加").arg(listData.at(index).row+1).arg(data.row+1);
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
//                listData[i].data += QString::fromLocal8Bit("重复");
//                listData[i].data += ",";
//                listData[i].data += QString::fromLocal8Bit("与%1行重复").arg(j+3+1);
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
        QStringList rec = tmp.split(",");
        if (rec.size() >= 39)
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
                        qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，均无数据，不追加").arg(row+1).arg(data.row+1);
//                        ui->textEdit->append(QString::fromLocal8Bit("重复：行%1和行%2，均无数据，不追加").arg(row+1).arg(data.row+1));
                        continue;
                    }
                    else if (!data.isEmpty() && !ite.key().isEmpty())
                    {
                        qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，均有数据").arg(row+1).arg(data.row+1);
                        ui->textEdit->append(QString::fromLocal8Bit("重复：行%1和行%2，均有数据").arg(row+1).arg(data.row+1));
                    }
                    else if (data.isEmpty() && !ite.key().isEmpty())
                    {
                        qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，前有数据，后无数据，不追加").arg(row+1).arg(data.row+1);
                        continue;
                    }
                    else if (!data.isEmpty() && ite.key().isEmpty())
                    {
                        int index = listData.indexOf(data);
                        qDebug()<<QString::fromLocal8Bit("重复：行%1和行%2，前无数据，后有数据，删前者，追加").arg(row+1).arg(data.row+1);
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
            qDebug()<<QString::fromLocal8Bit("行%1列数少于39").arg(i);
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
                    listData[i].data += QString::fromLocal8Bit("重复");
                    listData[i].data += ",";
                    listData[i].data += QString::fromLocal8Bit("与%1行重复").arg(j+3+1);
                    listData[i].data += "\r";

                    listData[j].data.replace("\r", "");
                    listData[j].data += ",";
                    listData[j].data += QString::fromLocal8Bit("重复");
                    listData[j].data += ",";
                    listData[j].data += QString::fromLocal8Bit("与%1行重复").arg(i+3+1);
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

    QMap<QString, QHash<QString, QList<SData> > > hashData;//文件夹-表-记录
    QStringList list = string.split("\n");
    for (int i=3; i < list.size(); i++)
    {
        ui->progressBar_Split->setValue(50*i/list.size());
        SData data;
        QString tmp = list.at(i);
        QStringList rec = tmp.split(",");
        if (rec.size() >= 39)
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
            qDebug()<<QString::fromLocal8Bit("行%1列数少于39").arg(i);
        }

    }

    //遍历输出文件
    QMap<QString, QHash<QString, QList<SData> > >::iterator iteFolder = hashData.begin();
    for ( ;iteFolder != hashData.end(); iteFolder++)
    {
        QString folderName = iteFolder.key();
        QDir dir(folderName);
        if (!dir.exists())
        {
			bool ok = dir.mkpath(folderName);
            if (!ok)
            {
                qDebug()<<QString("mkdir %1 fail!").arg(folderName);
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
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请选择文件！"), QMessageBox::Ok);
        return false;
    }
    QString outFile = ui->lineEdit_Out->text();
    if (outFile.isEmpty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请指定输出文件名字！"), QMessageBox::Ok);
        return false;
    }
    QString filterColumn = ui->lineEdit_SortColumn->text();
    QString dataColumn = ui->lineEdit_DataColumn->text();
    filterColumn.replace("；",";");
    dataColumn.replace("；",";");
    if (!filterColumn.contains(";"))
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请填写匹配列！"), QMessageBox::Ok);
        return false;
    }
    if (!dataColumn.contains(";"))
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请填写数据列！"), QMessageBox::Ok);
        return false;
    }
    QStringList filtList = filterColumn.split(";");
    g_keyList.clear();
    for (int i=0; i < filtList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(filtList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString::fromLocal8Bit("未识别的匹配列:%1！").arg(filtList.at(i));
            QMessageBox::warning(this, QString::fromLocal8Bit("警告"), err, QMessageBox::Ok);
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
            QString err = QString::fromLocal8Bit("未识别的数据列:%1！").arg(dataList.at(i));
            QMessageBox::warning(this, QString::fromLocal8Bit("警告"), err, QMessageBox::Ok);
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
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请选择文件！"), QMessageBox::Ok);
        return false;
    }

    QString splitSymbol = ui->lineEdit_Split->text();
    if (splitSymbol.isEmpty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请填写分隔符！"), QMessageBox::Ok);
        return false;
    }
    m_splitSymbol = splitSymbol;

    QString folderColumn = ui->lineEdit_FolderSplit->text();
    folderColumn.replace("；",";");
    if (!folderColumn.contains(";"))
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请填写文件夹匹配列！"), QMessageBox::Ok);
        return false;
    }

    QString tableColumn = ui->lineEdit_TableSplit->text();
    tableColumn.replace("；",";");
    if (!tableColumn.contains(";"))
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请填写表匹配列！"), QMessageBox::Ok);
        return false;
    }

    QStringList folderList = folderColumn.split(";");

    g_keyList.clear();
    for (int i=0; i < folderList.size(); i++)
    {
        QHash<QString, int>::iterator ite = g_hashColumn.find(folderList.at(i));
        if (ite == g_hashColumn.end())
        {
            QString err = QString::fromLocal8Bit("未识别的匹配列:%1！").arg(folderList.at(i));
            QMessageBox::warning(this, QString::fromLocal8Bit("警告"), err, QMessageBox::Ok);
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
            QString err = QString::fromLocal8Bit("未识别的数据列:%1！").arg(dataList.at(i));
            QMessageBox::warning(this, QString::fromLocal8Bit("警告"), err, QMessageBox::Ok);
            return false;
        }
        g_dataList.push_back(ite.value());
    }
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
                m_list[i].data += QString::fromLocal8Bit("重复");
                m_list[i].data += ",";
                m_list[i].data += QString::fromLocal8Bit("与%1行重复").arg(j+3+1);
                m_list[i].data += "\r";

                m_list[j].data.replace("\r", "");
                m_list[j].data += ",";
                m_list[j].data += QString::fromLocal8Bit("重复");
                m_list[j].data += ",";
                m_list[j].data += QString::fromLocal8Bit("与%1行重复").arg(i+3+1);
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
