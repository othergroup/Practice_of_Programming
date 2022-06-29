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
#include <QFile>
#include <QTextStream>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) //,m_ScrollArea(new QScrollArea(parent))
{
    info.resize(100);
    label_menu.resize(100);
    labels.resize(100);
    menu.resize(100);
    ui->setupUi(this);
    this->installEventFilter(this);
    // qDebug() << this->width() << " " << this->height();
    this->resize(770, 610);
    // ui->line->setStyleSheet("QFrame{color:rgb(20,196,188)}");
    this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    // ui->pushButton 1-3:关闭etc
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
    // ui->pushButton_4:添加folder
    // ui->pushButton_4->installEventFilter(this);
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(add_folder()));
    //点击屏幕新建提醒事项
    // connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(add_item()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(add_item()));
    for (int i = 0; i < menu.size(); i++)
    {
        menu[i] = new QPushButton(this);
        QString temp = "/Users/Apple/Desktop/Qt/Qt/label" + QString::number((i + 1) % 8) + ".png";
        // menu[i]->setIcon(QIcon("/Users/Apple/Desktop/Qt/Qt/label1.png"));
        menu[i]->setIcon(QIcon(temp));
        menu[i]->setIconSize(QSize(30, 30));
        menu[i]->setStyleSheet("QPushButton{"
                               "background-color:rgb(223, 223, 224);"
                               "border:none;"
                               "font: 14pt,Hiragino Sans GB;"
                               "text-align:left;}");
        menu[i]->setVisible(false);
        menu[i]->installEventFilter(this);
        label_menu[i] = new QVBoxLayout();
        label_menu[i]->setGeometry(QRect(300, 90, 441, 491));
    }
    //    m_ScrollArea->setFrameShape(QFrame::NoFrame);
    //    m_ScrollArea->setGeometry(300,90,441,491);
    //    setCentralWidget()
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
    brush.setColor(QColor(223, 223, 224));
    brush.setStyle(Qt::SolidPattern);
    QPainter painter(this);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor(255, 255, 255));
    // painter.drawRect(this->rect());

    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;

    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 13, 13);
    painter.setBrush(brush);
    painter.drawRoundedRect(QRect(0, 0, 282, this->height() - 1), 13, 13);
    painter.drawRect(QRect(270, 0, 12, this->height() - 1));
    // QWidget::paintEvent(event);
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
    switch (event->type())
    {
    case QEvent::HoverEnter:
        if (obj == ui->pushButton || obj == ui->pushButton_2 || obj == ui->pushButton_3)
        {
            ui->pushButton->setText(QString("×"));
            ui->pushButton_2->setText(QString("一"));
        }
        break;
    case QEvent::HoverLeave:
        if (obj == ui->pushButton || obj == ui->pushButton_2 || obj == ui->pushButton_3)
        {
            ui->pushButton->setText(QString(""));
            ui->pushButton_2->setText(QString(""));
        }
        break;
    case QEvent::MouseButtonPress:
    {
        if (obj == ui->lineEdit)
        {
            ui->lineEdit->setFocus();
        }
        if (obj != ui->lineEdit)
        {
            ui->lineEdit->clearFocus();
            this->setFocus();
        }
        if (obj == ui->pushButton)
        {
            ui->pushButton->setStyleSheet("QPushButton{"
                                          "background-color:rgba(181,80,72,255);"
                                          "border:none;"
                                          "border-radius:6px;"
                                          "color:rgb(0,0,0,255);}");
        }
        else if (obj == ui->pushButton_2)
        {
            ui->pushButton_2->setStyleSheet("QPushButton{"
                                            "background-color:rgba(184,143,59,255);"
                                            "border:none;"
                                            "border-radius:6px;"
                                            "color:rgb(0,0,0,255);}");
        }
        else if (obj == ui->pushButton_3)
        {
            ui->pushButton_3->setStyleSheet("QPushButton{"
                                            "background-color:rgba(212,212,211,255);"
                                            "border:none;"
                                            "border-radius:6px;"
                                            "color:rgb(0,0,0,255);}");
        }
        for (int i = 0; i < num_folder; i++)
        {
            if (obj == menu[i])
            {
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
        if (obj == ui->pushButton)
        {
            ui->pushButton->setStyleSheet("QPushButton{"
                                          "background-color:rgba(237,106,94,255);"
                                          "border:none;"
                                          "border-radius:6px;"
                                          "color:rgb(0,0,0,255);}");
        }
        else if (obj == ui->pushButton_2)
        {
            ui->pushButton_2->setStyleSheet("QPushButton{"
                                            "background-color:rgba(245,191,79,255);"
                                            "border:none;"
                                            "border-radius:6px;"
                                            "color:rgb(0,0,0,255);}");
        }
        else if (ui->pushButton == ui->pushButton_3)
        {
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
    // this->setEnabled(false);
    if (folder_dialog == NULL)
        folder_dialog = new Folder_Dialog(this);
    folder_dialog->exec();
    // qDebug() << "NO";
    // qDebug() << folder_dialog->name;
    if (!folder_dialog->name.isEmpty())
    {
        ui->label->setText(folder_dialog->name);
        menu[num_folder]->setText(folder_dialog->name);

        menu[num_folder]->setVisible(true);
        ui->verticalLayout->insertWidget(num_folder++, menu[num_folder - 1]);
        // qDebug()<<num_folder;
        for (int i = 0; i < labels[select].size(); i++)
            labels[select][i]->setVisible(false);
        select = num_folder - 1;

        this->setLayout(label_menu[select]);
    }
    // qDebug() << "Yes";
}

void MainWindow::display_folder(QString name)
{
    ui->label->setText(name);
    this->setLayout(label_menu[select]);
    for (int i = 0; i < labels[select].size(); i++)
        labels[select][i]->setVisible(true);
}

void MainWindow::add_item()
{
    if (itemDialog == NULL)
        itemDialog = new item_dialog(this);
    itemDialog->exec();
    if (!itemDialog->item.name.isEmpty() && !itemDialog->item.time.isEmpty())
    {
        info[select].push_back(itemDialog->item);
        QPushButton *label = new QPushButton(this);
        label->setIcon(QIcon("/Users/Apple/Desktop/Qt/Qt/label_icon.png"));
        label->setIconSize(QSize(25, 25));
        label->setText(info[select].rbegin()->name);
        label->setVisible(true);
        label->setStyleSheet("QPushButton{"
                             "font:16pt,Hiragino Sans GB;"
                             "background-color:rgb(255,255,255);"
                             "text-align:left;"
                             "border:none;}");
        label_menu[select]->addWidget(label);
        // label->setGeometry(300, 100 + 30 * labels[select].size(), 439, 21);
        labels[select].push_back(label);
    }
}

/* To save vector<Item> to dat.txt
 * Author: Zhao Haochen
 * Please test before display, because the author can't run the code before dealing with errors properly.
 */
bool MainWindow::saveFile()
{
    QFile iofile("dat.txt");
    if (!iofile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "error ocurred!";
        // TODO: replace it with some actions in the front.
        return 0;
    }
    QTextStream aStream(&iofile);
    int i = 0;
    for (auto it = info.begin(); i < num_folder; it++, i++)
    {
        aStream << menu[i]->text();
        for (auto it_in = it->begin(); it_in != it->end(); it_in++)
        {
            aStream << it_in->name << it_in->time << it_in->place << it_in->other << it_in->remind;
        }
    }
    iofile.close();
    return 1;
}
/* To load vector<Item> from dat.txt
 * Author: Zhao Haochen
 * Please test before display, because the author can't run the code before dealing with errors properly.
 * I am not sure whether it can work the way it supposed to.
 */
bool MainWindow::loadFile()
{
    QFile iofile("dat.txt");
    if (!iofile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "error occured!";
        // TODO: replace it with some actions in the front.
    }
    QTextStream aStream(&iofile);
    ui->textEditStream->setPlainText(aStream.readAll());
    iofile.close();
    int i = 0;
    vector<Item> tmpv;
    while (aStream >> menu[i++]->text())
    {
        Item tmp;
        while (aStream >> tmp.name >> tmp.time >> tmp.place >> tmp.other >> tmp.remind)
        {
            tmpv.push_back(tmp);
        }
        info.push_back(tmpv);
        tmpv.clear();
    }
    return 1;
}
