﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
#include <QFileDialog>
#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>
#include <QMutex>
#include <QThread>
#include <QReadWriteLock>
#include <QTimer>
#include <QAxObject>

extern QList<int> g_keyList;
extern QList<int> g_dataList;

struct SData
{
    int row;
    QStringList list;
    QString data;

    bool isChecked;

    //match
    bool isAbsolute;
    bool canDel;

    bool operator == (const SData other) const
    {
        for (int i=0; i < g_keyList.size(); i++)
        {
            if (g_keyList.at(i) >= list.size())
            {
                qDebug()<<"err 0";
                return false;
            }
            if (list.at(g_keyList.at(i)).isEmpty())
            {
                return false;
            }
        }

        for (int i=0; i < g_keyList.size(); i++)
        {
            if (g_keyList.at(i) >= other.list.size())
            {
                qDebug()<<"err 1";
                return false;
            }
            if (list.at(g_keyList.at(i)) != other.list.at(g_keyList.at(i)))
            {
                return false;
            }
        }

        return true;
    }

    bool operator <(const SData other) const
    {
        for (int i=0; i < g_keyList.size(); i++)
        {
            if (g_keyList.at(i) >= list.size() || g_keyList.at(i) >= other.list.size())
            {
                qDebug()<<"err 2";
                return false;
            }
            if (list.at(g_keyList.at(i)) < other.list.at(g_keyList.at(i)))
            {
                return true;
            }
            if (list.at(g_keyList.at(i)) == other.list.at(g_keyList.at(i)))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    bool isEmpty() const
    {
        for (int i=0; i < g_dataList.size(); i++)
        {
            if (g_dataList.at(i) >= list.size())
            {
                qDebug()<<"err 3";
                continue;
            }
            if (!list.at(g_dataList.at(i)).isEmpty())
            {
                return false;
            }
        }
        return true;
    }

    bool isValidKey()
    {
        for (int i=0; i < g_keyList.size(); i++)
        {
            if (g_keyList.at(i) >= list.size())
            {
                qDebug()<<"err 4";
                return false;
            }
            if (list.at(g_keyList.at(i)).isEmpty())
            {
                return false;
            }
        }
        return true;
    }
};

struct SCompare
{
    bool exist;

    QList<SData> list;
};

struct SMatch
{
    QList<int> inTimeList;
    QList<int> muchList;
    int maxLevel;
    int minInTime;
    int NameColNum;
    int payColNum;
    int maxCol;
};


class Widget : public QWidget
{
    Q_OBJECT
friend class matchTask;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void add(QString txt);
public slots:
    void onAdd(QString txt);

    void onClicked();
    void onSelectFile();
    void onProc();

    void onSelectSplitFile();
    void onSplit();

    void onCompare();
    void onSelectFile1();
    void onSelectFile2();

    void onTest();


    //匹配
    void onSelectMatchFile();
    void onMatch();
    void onOrderCheck();
    void onMatch1();

    void onSplitFFile();
    void onSplitF();

    void onCat();

    void onSelectFind();
    void onFind();

private:
    void initHash();
    bool checkInput();

    bool checkSplit();


    bool checkCompare();

    void orderMisMatch(SMatch m, QList<SData> &list);
    bool matchSCal(float v);
    void rescMatch(SMatch m, QList<SData> &list);
    void rescCat(SMatch m, QList<SData> &list);
    void adjustMCol(SMatch m, QList<SData> &list);
    void matchOtherLine(SMatch m, QList<SData> &list, float val);

    void convertMuch(QString &str);

    bool getColList(QString cols, QList<int> &list);
    bool getCol(QString col, int &colNum);

private:
    Ui::Widget *ui;


    QString m_inFile;
    QString m_inSplitFile;
    QString m_splitSymbol;

    QString m_file1;
    QString m_file2;
};
#include <QRunnable>
class matchTask : public QRunnable
{
public:
    matchTask(SMatch m, QList<SData> &list, Widget *p);
    ~matchTask(){}
    void run();
    SMatch m_m;
    QList<SData> &m_list;
    Widget *m_p;
};

class CheckThread : public QThread
{
    Q_OBJECT
public:
    CheckThread(int index, QList<SData> &list, QReadWriteLock &locker, QWidget *parent = nullptr);
    ~CheckThread(){}
    bool isBusy();
signals:
    void begin();
public slots:
    void onBegin();
private:
    int m_index;
    QList<SData> &m_list;
    QReadWriteLock &m_locker;
    bool m_busy;
};
#endif // WIDGET_H
