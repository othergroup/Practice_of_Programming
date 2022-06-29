#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <folder_dialog.h>
#include <item_dialog.h>
#include <display_dialog.h>
#include <vector>
#include <QButtonGroup>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QPoint>
#include <QPushButton>
#include <QLayout>
#include <QScrollArea>
#include <QMenu>
#include "DesktopSprite.h"
#include <utility>
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
    void initLineEdit();
    void initButton();
    void init();
    QPoint dpoint;
    int select = 0;  //所选类别
    int num_folder = 0; //类别个数
    int item_select=0;
    bool is_delete=false;   //是否删除提醒事项
    std::vector<std::vector<Item>> info; //记录提醒事项信息
    std::vector<std::vector<QPushButton *>> item_buttons;   //提醒事项的button列表
    std::vector<QPushButton *> menu;    //类别的button列表
    bool saveFile();
    bool loadFile();
    std::pair<int,int> findEvent(QString cont);
private:
    Ui::MainWindow *ui;
    Folder_Dialog *folder_dialog = nullptr;
    item_dialog *itemDialog = nullptr;
    display_dialog *displayDialog=nullptr;
    DesktopSprite *sprite=nullptr;
    display_dialog *searchDialog=nullptr;
    void on_item_menu_requested();
public slots:
    void minimize();
    void add_folder();
    void display_folder(QString name);
    void add_item();
    void item_delete();
    void item_show();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // MAINWINDOW_H
