#ifndef item_dialog_H
#define item_dialog_H

#include <QDialog>

namespace Ui {
class item_dialog;
}

class Item
{
public:
    QString name, time, place, other;
    bool remind;
    Item()
        : name(QString(""))
        , time(QString(""))
        , place(QString(""))
        , other(QString(""))
        , remind(false)
    {}
};

class item_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit item_dialog(QWidget *parent = nullptr);
    ~item_dialog();
    Item item;
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::item_dialog *ui;
public slots:
    void finished();
};

#endif // item_dialog_H
