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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    info.resize(100);
    labels.resize(100);
    menu.resize(100);
    ui->setupUi(this);
    this->installEventFilter(this);
    //qDebug() << this->width() << " " << this->height();
    this->resize(770, 610);
    //ui->line->setStyleSheet("QFrame{color:rgb(20,196,188)}");
    this->setAttribute(Qt::WA_TranslucentBackground);
    //this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    //ui->pushButton 1-3:关闭etc
    ui->pushButton->setAttribute(Qt::WA_Hover);
    ui->pushButton_2->setAttribute(Qt::WA_Hover);
    ui->pushButton_3->setAttribute(Qt::WA_Hover);
    ui->pushButton->setStyleSheet("QPushButton{"
                                  "background-color:rgba(237,106,94,255);"
                                  "border:none;"
                                  "border-radius:6px;"
                                  "color:rgba(0,0,0,255);"
                                  "text-align:bottom;}");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
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

    QAction *action = new QAction(this);

    action->setIcon(QIcon("/Users/muzhancun/Desktop/Qt/WWW/untitled/query.png"));
    ui->lineEdit->addAction(action, QLineEdit::LeadingPosition);
    ui->lineEdit->setAttribute(Qt::WA_Hover);
    ui->lineEdit->setAttribute(Qt::WA_MacShowFocusRect, false);
    ui->lineEdit->setStyleSheet("QLineEdit{"
                                "background-color:rgb(220,218,218);"
                                "border:none;"
                                "border-radius:8px;"
                                "color:rgb(100,100,100);"
                                "text-align:left;}"
                                "QLineEdit::focus{"
                                "border-style:outset;"
                                "background-color:rgb(220,218,218);"
                                "border:none;"
                                "border-radius:8px;"
                                "color:rgb(100,100,100);"
                                "text-align:left;}");
    ui->lineEdit->setPlaceholderText("搜索");
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit->clearFocus();
    this->setFocus();
    //ui->pushButton_4:添加folder
    //ui->pushButton_4->installEventFilter(this);
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(add_folder()));
    //点击屏幕新建提醒事项
    //connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(add_item()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(add_item()));
    for (int i = 0; i < menu.size(); i++) {
        menu[i] = new QPushButton(this);
        menu[i]->setVisible(false);
        menu[i]->installEventFilter(this);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //    QPen pen;
    //    pen.setColor(QColor(238, 238, 238));
    QBrush brush;
    brush.setColor(QColor(232, 231, 231));
    brush.setStyle(Qt::SolidPattern);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(255, 255, 255));
    //painter.drawRect(this->rect());

    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;

    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 13, 13);
    painter.setBrush(brush);
    painter.drawRoundedRect(QRect(0, 0, 282, this->height() - 1), 13, 13);
    painter.drawRect(QRect(270, 0, 12, this->height() - 1));
    //QWidget::paintEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point_now = this->pos();
    QPoint point_next = event->globalPos();
    this->dpoint = point_next - point_now;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dpoint);
}

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
        for (int i = 0; i < num_folder; i++) {
            if (obj == menu[i]) {
                ui->label->setText(menu[i]->text());
                for (int j = 0; j < labels[select].size(); j++)
                    labels[select][j]->setVisible(false);
                select = i;
                for (int j = 0; j < labels[select].size(); j++)
                    labels[select][j]->setVisible(true);
                break;
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

void MainWindow::minimize()
{
    QWidget::showMinimized();
}

void MainWindow::add_folder()
{
    //this->setEnabled(false);
    if (folder_dialog == NULL)
        folder_dialog = new Folder_Dialog(this);
    folder_dialog->exec();
    //qDebug() << "NO";
    //qDebug() << folder_dialog->name;
    if (!folder_dialog->name.isEmpty()) {
        ui->label->setText(folder_dialog->name);
        menu[num_folder]->setText(folder_dialog->name);
        menu[num_folder]->setVisible(true);
        ui->verticalLayout->insertWidget(num_folder++, menu[num_folder - 1]);
        for (int i = 0; i < labels[select].size(); i++)
            labels[select][i]->setVisible(false);

        select = num_folder - 1;
    }
    //qDebug() << "Yes";
}

void MainWindow::display_folder(QString name)
{
    ui->label->setText(name);
    for (int i = 0; i < labels[select].size(); i++)
        labels[select][i]->setVisible(true);
}

void MainWindow::add_item()
{
    if (itemDialog == NULL)
        itemDialog = new item_dialog(this);
    itemDialog->exec();
    if (!itemDialog->item.name.isEmpty() && !itemDialog->item.time.isEmpty()) {
        info[select].push_back(itemDialog->item);
        QLabel *label = new QLabel(this);
        label->setText(info[select].rbegin()->name);
        label->setVisible(true);
        label->setGeometry(300, 100 + 30 * labels[select].size(), 439, 21);
        QFont font;
        font.setPointSize(16);
        font.setFamily("Hiragino Sans GB");
        label->setFont(font);
        labels[select].push_back(label);
        //ui->verticalLayout_2->insertWidget(info[select].size() - 1, label);
    }
}
