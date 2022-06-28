#ifndef display_dialog_H
#define display_dialog_H

#include <QDialog>
#include "item_dialog.h"

namespace Ui {
class display_dialog;
}

class display_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit display_dialog(Item item_,QWidget *parent = nullptr);
    ~display_dialog();
    Item item;
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::display_dialog *ui;
public slots:
    void finished();
};

#endif // display_dialog_H
