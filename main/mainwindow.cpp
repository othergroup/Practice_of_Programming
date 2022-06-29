#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QBrush>
#include <QDebug>
#include <QDialog>
#include <QEvent>
#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QPicture>
#include <QScrollArea>
#include <QLayout>
#include <QMenu>
#include <QTimer>
#include <QFile>
#include<QTextStream>
#include <QTime>
#include <QMessageBox>
#define MZC "Mu Zhancun"
/*
    主窗口构造函数
    Author:MZC
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    info.resize(100);
    item_buttons.resize(100);
    menu.resize(100);
    ui->setupUi(this);
    //setFocusPolicy(Qt::StrongFocus);
    this->installEventFilter(this);
    this->resize(770, 610);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->initLineEdit();
    this->initButton();
    QTimer *reminder=new QTimer(this);
    reminder->start(1000);
    connect(reminder,&QTimer::timeout,[=](){
        QDateTime datetime=QDateTime::currentDateTime();
        QString str=datetime.toString("yyyy/MM/dd-hh:mm:ss");
        //qDebug()<<str;
        for(int i=0;i<num_folder;i++) {
            for(int j=0;j<info[i].size();j++) {
                if(info[i][j].time==str&&info[i][j].remind) {
                    if(sprite==nullptr) {
                        sprite=new DesktopSprite(this);
                    }
                    sprite->exec();
                    if(sprite->is_close) {
                        int temp_num=select;
                        item_select=j;
                        select=i;
                        item_delete();
                        select=temp_num;
                    } else {
                        QPalette temp_pal=item_buttons[i][j]->palette();
                        temp_pal.setColor(QPalette::ButtonText,Qt::red);
                        item_buttons[i][j]->setPalette(temp_pal);
                    }
                }
            }
        }
    });
    init();
}

/*
    主窗口析构函数
    Author:MZC
*/
MainWindow::~MainWindow()
{
    delete ui,folder_dialog,itemDialog,displayDialog,sprite;
}

/*
    绘制主窗口样式
    Author:Mu Zhancun
*/
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QBrush brush;
    brush.setColor(QColor(223, 223, 224));
    brush.setStyle(Qt::SolidPattern);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(255, 255, 255));
    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 13, 13);
    painter.setBrush(brush);
    painter.drawRoundedRect(QRect(0, 0, 282, this->height() - 1), 13, 13);
    painter.drawRect(QRect(270, 0, 12, this->height() - 1));
}

/*
    获取鼠标位置
    Author:MZC
*/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point_now = this->pos();
    QPoint point_next = event->globalPos();
    this->dpoint = point_next - point_now;
}

/*
    控制窗口移动
    Author:MZC
*/
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dpoint);
}

/*
    自定义eventFilter
    Author:MZC
*/
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        if (obj == ui->pushButton || obj == ui->pushButton_2 || obj == ui->pushButton_3) {
            ui->pushButton->setText(QString("×"));
            ui->pushButton_2->setText(QString("一"));
        }
        break;
    case QEvent::HoverLeave:
        if (obj == ui->pushButton || obj == ui->pushButton_2 || obj == ui->pushButton_3) {
            ui->pushButton->setText(QString(""));
            ui->pushButton_2->setText(QString(""));
        }
        break;
    case QEvent::MouseButtonPress: {
        if (obj == ui->lineEdit) {
            ui->lineEdit->setFocus();
        }
        if (obj != ui->lineEdit) {
            ui->lineEdit->clearFocus();
            this->setFocus();
        }
        if (obj == ui->pushButton) {
            ui->pushButton->setStyleSheet("QPushButton{"
                                          "background-color:rgba(181,80,72,255);"
                                          "border:none;"
                                          "border-radius:6px;"
                                          "color:rgb(0,0,0,255);}");
        } else if (obj == ui->pushButton_2) {
            ui->pushButton_2->setStyleSheet("QPushButton{"
                                            "background-color:rgba(184,143,59,255);"
                                            "border:none;"
                                            "border-radius:6px;"
                                            "color:rgb(0,0,0,255);}");
        } else if (obj == ui->pushButton_3) {
            ui->pushButton_3->setStyleSheet("QPushButton{"
                                            "background-color:rgba(212,212,211,255);"
                                            "border:none;"
                                            "border-radius:6px;"
                                            "color:rgb(0,0,0,255);}");
        }
        QMouseEvent *qme=(QMouseEvent*)event;
        if(qme->button()==Qt::LeftButton)
        {
            for (int i = 0; i < num_folder; i++) {
                if (obj == menu[i]) {
                    ui->label->setText(menu[i]->text());
                    for (int j = 0; j < item_buttons[select].size(); j++)
                    {
                        item_buttons[select][j]->setVisible(false);
                        ui->verticalLayout_2->removeWidget(item_buttons[select][j]);
                    }
                    select = i;
                    for (int j = 0; j < item_buttons[select].size(); j++)
                    {
                        item_buttons[select][j]->setVisible(true);
                        ui->verticalLayout_2->insertWidget(j,item_buttons[select][j]);
                    }
                    break;
                }
            }
            for(int i=0;i<item_buttons[select].size();i++){
                if(obj==item_buttons[select][i]) {
                    item_select=i;
                    if(!is_delete){
                        is_delete=true;
                        QPalette temp_pal=item_buttons[select][i]->palette();
                        temp_pal.setColor(QPalette::ButtonText,Qt::blue);
                        item_buttons[select][i]->setPalette(temp_pal);
                        QTimer *timer=new QTimer(this);
                        timer->start(2000);
                        timer->setSingleShot(true);
                        connect(timer,&QTimer::timeout,[=](){
                           if(is_delete){
                               item_delete();
                               is_delete=false;
                           }
                        });
                    } else {
                        is_delete=false;
                        QPalette temp_pal2=item_buttons[select][i]->palette();
                        temp_pal2.setColor(QPalette::ButtonText,Qt::black);
                        item_buttons[select][i]->setPalette(temp_pal2);
                    }
                }
            }
        }
        else if(qme->button()==Qt::RightButton)
        {
            for (int i = 0; i < item_buttons[select].size(); i++) {
                if (obj == item_buttons[select][i]) {
                    item_select=i;
                    on_item_menu_requested();
                    break;
                }
            }
        }
        break;
    }
    case QEvent::MouseButtonRelease:
        if (obj == ui->pushButton) {
            ui->pushButton->setStyleSheet("QPushButton{"
                                          "background-color:rgba(237,106,94,255);"
                                          "border:none;"
                                          "border-radius:6px;"
                                          "color:rgb(0,0,0,255);}");
        } else if (obj == ui->pushButton_2) {
            ui->pushButton_2->setStyleSheet("QPushButton{"
                                            "background-color:rgba(245,191,79,255);"
                                            "border:none;"
                                            "border-radius:6px;"
                                            "color:rgb(0,0,0,255);}");
        } else if (ui->pushButton == ui->pushButton_3) {
            ui->pushButton_3->setStyleSheet("QPushButton{"
                                            "background-color:rgba(212,212,211,255);"
                                            "border:none;"
                                            "border-radius:6px;"
                                            "color:rgb(0,0,0,255);}");
        }
        ui->pushButton->setText(QString(""));
        ui->pushButton_2->setText(QString(""));
        break;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

/*
    最小化
    Author:MZC
*/
void MainWindow::minimize()
{
    QWidget::showMinimized();
}

/*
    新建类别
    Author:MZC
*/
void MainWindow::add_folder()
{
    if (folder_dialog == nullptr)
        folder_dialog = new Folder_Dialog(this);
    folder_dialog->exec();
    if (!folder_dialog->name.isEmpty()) {
        ui->label->setText(folder_dialog->name);
        menu[num_folder]->setText(folder_dialog->name);
        menu[num_folder]->setVisible(true);
        //menu[num_folder]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        //ui->verticalLayout->addWidget(menu[num_folder]);
        //num_folder++;
        ui->verticalLayout->insertWidget(num_folder++, menu[num_folder - 1]);
        for (int i = 0; i < item_buttons[select].size(); i++)
        {
            item_buttons[select][i]->setVisible(false);
            ui->verticalLayout->removeWidget(item_buttons[select][i]);
        }
        select = num_folder - 1;
    }

}

/*
    展示类别内提醒事项
    Author:MZC
*/
void MainWindow::display_folder(QString name)
{
    ui->label->setText(name);
    //this->setLayout(label_menu[select]);
    for (int i = 0; i < item_buttons[select].size(); i++)
        item_buttons[select][i]->setVisible(true);
}

/*
    新增提醒事项
    Author:MZC
*/
void MainWindow::add_item()
{
    if(num_folder==0)
        return;
    if (itemDialog == nullptr)
        itemDialog = new item_dialog(this);
    itemDialog->exec();
    if (!itemDialog->item.name.isEmpty() && !itemDialog->item.time.isEmpty()) {
        info[select].push_back(itemDialog->item);
        //qDebug()<<itemDialog->item.time;
        QPushButton *item_button = new QPushButton(this);
        item_button->setIcon(QIcon(":/img/label_icon.png"));
        item_button->setIconSize(QSize(25,25));
        item_button->setText(info[select].rbegin()->name);
        item_button->setVisible(true);
        item_button->installEventFilter(this);
        item_button->setContextMenuPolicy(Qt::CustomContextMenu);
        item_button->setStyleSheet("QPushButton{"
                                   "font:17pt,Songti SC;"
                                   "background-color:rgb(255,255,255);"
                                   "text-align:left;"
                                   "border:none;"
                                   "border-bottom:1px solid rgb(230,230,230);}");
        ui->verticalLayout_2->insertWidget(item_buttons[select].size(),item_button);
        item_buttons[select].push_back(item_button);
    }
}

/*
    初始化搜索栏样式
    Author:MZC
*/
void MainWindow::initLineEdit()
{
    QAction *action = new QAction(this);
    action->setIcon(QIcon("/Users/Apple/Desktop/Qt/Qt/query.png"));
    ui->lineEdit->addAction(action, QLineEdit::LeadingPosition);
    ui->lineEdit->setAttribute(Qt::WA_Hover);
    ui->lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
    ui->lineEdit->setStyleSheet("QLineEdit{"
                                "background-color:rgb(211,211,211);"
                                "border:none;"
                                "border-radius:8px;"
                                "color:rgb(100,100,100);"
                                "text-align:left;}"
                                "QLineEdit::focus{"
                                "border-style:outset;"
                                "background-color:rgb(211,211,211);"
                                "border:none;"
                                "border-radius:8px;"
                                "color:rgb(100,100,100);"
                                "text-align:left;}");
    ui->lineEdit->setPlaceholderText("搜索");
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit->clearFocus();
    this->setFocus();
    connect(ui->lineEdit,&QLineEdit::editingFinished,[=](){
        if(!ui->lineEdit->hasFocus())
            return;
        int folder_find=-1,item_find=-1;
        //folder_find,item_find=find(ui->lineEdit->text());
        folder_find=0,item_find=0;
        if(folder_find==-1&&item_find==-1) {
            ui->lineEdit->clear();
            QMessageBox msgBox;
            msgBox.setText("no results found!");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setStandardButtons(QMessageBox::Close);
            msgBox.exec();
        } else {
            if (searchDialog == nullptr)
                searchDialog = new display_dialog(info[folder_find][item_find],true,this);
            searchDialog->exec();
            info[folder_find][item_find]=searchDialog->item;
            item_buttons[folder_find][item_find]->setText(searchDialog->item.name);

        }
    });
}

/*
    初始化按钮样式
    Author:MZC
*/
void MainWindow::initButton()
{
    ui->pushButton->setAttribute(Qt::WA_Hover);
    ui->pushButton_2->setAttribute(Qt::WA_Hover);
    ui->pushButton_3->setAttribute(Qt::WA_Hover);
    ui->pushButton->setStyleSheet("QPushButton{"
                                  "background-color:rgba(237,106,94,255);"
                                  "border:none;"
                                  "border-radius:6px;"
                                  "color:rgba(0,0,0,255);"
                                  "text-align:bottom;}");
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        saveFile();
        this->close();
    });
    ui->pushButton->installEventFilter(this);
    ui->pushButton_2->setStyleSheet("QPushButton{"
                                    "background-color:rgba(245,191,79,255);"
                                    "border:none;"
                                    "border-radius:6px;"
                                    "color:rgba(0,0,0,255);"
                                    "text-align:center;}");
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(minimize()));
    ui->pushButton_2->installEventFilter(this);
    ui->pushButton_3->setStyleSheet("QPushButton{"
                                    "background-color:rgba(212,212,211,255);"
                                    "border:none;"
                                    "border-radius:6px;"
                                    "color:rgba(0,0,0,255);}");
    ui->pushButton_3->installEventFilter(this);
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(add_folder()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(add_item()));
    for (int i = 0; i < menu.size(); i++) {
        menu[i] = new QPushButton(this);
        QString temps=":/img/label"+QString::number((i+1)%8)+".png";
        menu[i]->setIcon(QIcon(temps));
        menu[i]->setIconSize(QSize(30,30));
        menu[i]->setStyleSheet("QPushButton{"
                               "background-color:rgb(223, 223, 224);"
                               "border:none;"
                               "font: 14pt,Hiragino Sans GB;"
                               "text-align:left;}");
        menu[i]->setVisible(false);
        menu[i]->setContextMenuPolicy(Qt::CustomContextMenu);
        //connect(menu[i],&QPushButton::customContextMenuRequested,this,&MainWindow::on_item_menu_requested);
        menu[i]->installEventFilter(this);
    }
}

/*
    右键唤出菜单
    author:MZC
*/
void MainWindow::on_item_menu_requested()
{
    QMenu *item_menu=new QMenu(item_buttons[select][item_select]);
    QAction *action1=new QAction(tr("删除"),this);
    connect(action1,&QAction::triggered,this,&MainWindow::item_delete);
    QAction *action2=new QAction(tr("查看信息"),this);
    connect(action2,&QAction::triggered,this,&MainWindow::item_show);
    item_menu->addAction(action1);
    item_menu->addAction(action2);
    item_menu->exec(QCursor::pos());
}

/*
    删除注意事项
    author:MZC
*/
void MainWindow::item_delete()
{

    ui->verticalLayout_2->removeWidget(item_buttons[select][item_select]);
    item_buttons[select][item_select]->deleteLater();
    info[select].erase(info[select].begin()+item_select);
    item_buttons[select].erase(item_buttons[select].begin()+item_select);
}

/*
    展示提醒事项
    author:MZC
*/
void MainWindow::item_show()
{
    if (displayDialog == nullptr)
        displayDialog = new display_dialog(info[select][item_select],this);
    displayDialog->exec();
    info[select][item_select]=displayDialog->item;
    item_buttons[select][item_select]->setText(displayDialog->item.name);
}

/* Name: saveFile()
 * Author: Zhao Haochen
 * Description: To save info to dat.txt, using QFile and QTextStream method.
 * Warnings: Please test before display, because the author can't run the code before dealing with errors properly.
 */
bool MainWindow::saveFile()
{
    QFile iofile("/Users/apple/Desktop/Qt/Qt/dat.txt");
    if (!iofile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "error ocurred!";
        // TODO: replace it with some actions in the front.
        return 0;
    }
    QTextStream aStream(&iofile);
    aStream << num_folder;
    for(int i=0;i<num_folder;i++) {
        aStream<<" "<<info[i].size()<<" "<<menu[i]->text()<<" ";
        for(int j=0;j<info[i].size();j++) {
            aStream<<info[i][j].name<<" "<<info[i][j].time<<" "<<info[i][j].place<<" "<<info[i][j].other<< " "<<info[i][j].remind;
        }
    }
//    for (auto it = info.begin(); i < num_folder; it++, i++)
//    {
//        aStream << " "<<info[i].size() << " "<<menu[i]->text()<<" ";
//        for (auto it_in = it->begin(); it_in != it->end(); it_in++)
//        {
//            aStream << it_in->name <<" "<< it_in->time <<" "<<it_in->place << " "<<it_in->other<<" "<< it_in->remind;
//        }
//    }
    iofile.close();
    return 1;
}

/* Name: loadFile()
 * Author: Zhao Haochen
 * Description: To load info from dat.txt, using QFile and QTextStream method.
 * Warnings: Please test before display, because the author can't run the code before dealing with configeration errors properly.
 */
bool MainWindow::loadFile()
{
    QFile iofile("/Users/apple/Desktop/Qt/Qt/dat.txt");
    if (!iofile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "error occured!";
        // TODO: replace it with some actions in the front.
    }
    QTextStream aStream(&iofile);
    aStream.setAutoDetectUnicode(true);
    int i = 0;
    std::vector<Item> tmpv;
    QString temp_name,temp_num;
    aStream >> temp_num;
    num_folder=temp_num.toInt();
    for (; i < num_folder; ++i)
    {
        int foldersize;
        tmpv.clear();
        QString tempn;
        aStream >> foldersize >> tempn;
        //qDebug()<<foldersize<<" "<<tempn;
        menu[i]->setText(tempn);
        menu[i]->setVisible(true);
        ui->verticalLayout->insertWidget(i, menu[i]);
        QString tempr;
        for (int j = 0; j < foldersize; ++j)
        {
            Item tmp;
            aStream >> tmp.name >> tmp.time >> tmp.place >> tmp.other >> tempr;
            //qDebug()<<tmp.name<<" "<<tmp.time<<" "<<tmp.place<<" "<<tmp.other<<" "<<tempr;
            tmp.remind=tempr.toInt();
            tmpv.push_back(tmp);
            QPushButton *item_button = new QPushButton(this);
            item_button->setIcon(QIcon(":/img/label_icon.png"));
            item_button->setIconSize(QSize(25,25));
            item_button->setText(tmp.name);
            item_button->setVisible(false);
            item_button->installEventFilter(this);
            item_button->setContextMenuPolicy(Qt::CustomContextMenu);
            item_button->setStyleSheet("QPushButton{"
                                       "font:17pt,Songti SC;"
                                       "background-color:rgb(255,255,255);"
                                       "text-align:left;"
                                       "border:none;"
                                       "border-bottom:1px solid rgb(230,230,230);}");
            item_buttons[i].push_back(item_button);
        }
        info[i]=tmpv;
        //qDebug()<<info[i].size();
    }

    iofile.close();
    return 1;
}

void MainWindow::init()
{
    if(!loadFile()) {
        qDebug()<<"Failed!";
        return;
    }
    if(num_folder==0) {
        return;
    }
    select=0;
    ui->label->setText(menu[select]->text());
    for (int j = 0; j < item_buttons[select].size(); j++)
    {
        item_buttons[select][j]->setVisible(true);
        ui->verticalLayout_2->insertWidget(j,item_buttons[select][j]);
    }
}
