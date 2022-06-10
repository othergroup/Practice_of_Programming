#ifndef FOLDER_DIALOG_H
#define FOLDER_DIALOG_H

#include <QDialog>

namespace Ui {
class Folder_Dialog;
}

class Folder_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Folder_Dialog(QWidget *parent = nullptr);
    ~Folder_Dialog();
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    QString name;

private:
    Ui::Folder_Dialog *ui;

public slots:
    void finished();
    //void is_empty();
};

#endif // FOLDER_DIALOG_H
