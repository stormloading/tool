#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void onOpenFile();

private:
    Ui::Widget *ui;

    struct SData
    {
        QString AF;
        QString AJ;
        QString AK;
        QString M;
        QString S;
        QString Y;
        QString data;
        int row;

        int equalRow;
        bool checked;
        bool isDelete;

        bool operator ==(const SData other) const
        {
            if (AF.isEmpty() || AJ.isEmpty() || AK.isEmpty())
            {
                return false;
            }
            if (AF == other.AF && AJ == other.AJ && AK == other.AK)
            {
                return true;
            }
            return false;
        }

        bool isEmpry()
        {
            return M.isEmpty() && S.isEmpty() && Y.isEmpty();
        }
    };
};

#endif // WIDGET_H
