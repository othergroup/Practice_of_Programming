#ifndef FOLDER_NAME_H
#define FOLDER_NAME_H

#include <QDialog>

namespace Ui {
class folder_name;
}

class folder_name : public QDialog
{
    Q_OBJECT

public:
    explicit folder_name(QWidget *parent = nullptr);
    ~folder_name();
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    QString name;

private:
    Ui::folder_name *ui;

public slots:
    void finished();
};

#endif // FOLDER_NAME_H
