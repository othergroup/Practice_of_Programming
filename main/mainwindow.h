#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <folder_dialog.h>
#include <item_dialog.h>
#include <vector>
#include <QButtonGroup>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QPoint>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    QPoint dpoint;
    int select = 0;
    int num_folder = 0;
    std::vector<std::vector<Item>> info;
    std::vector<std::vector<QLabel *>> labels;
    std::vector<QPushButton *> menu;

private:
    Ui::MainWindow *ui;
    Folder_Dialog *folder_dialog = NULL;
    item_dialog *itemDialog = NULL;
public slots:
    void minimize();
    void add_folder();
    void display_folder(QString name);
    void add_item();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // MAINWINDOW_H
