#include "folder_dialog.h"
#include "ui_folder_dialog.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
Folder_Dialog::Folder_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Folder_Dialog)
{
    ui->setupUi(this);
    this->name = QString("");
    //this->setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    //this->resize(470, 230);
    this->setModal(true);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(finished()));
    ui->lineEdit->installEventFilter(this);
    ui->pushButton_1->setDefault(true);
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->lineEdit, &QLineEdit::textChanged, [=]() {
        if (ui->lineEdit->text().isEmpty()) {
            ui->pushButton_1->setDefault(true);
            ui->pushButton_2->setDefault(false);
        } else {
            ui->pushButton_2->setDefault(true);
            ui->pushButton_1->setDefault(false);
        }
    });
    //    connect(this, &Folder_Dialog::change_focus, [=]() {
    //        ui->pushButton_1->setDefault(true);
    //        ui->pushButton_2->setDefault(false);
    //    });
    //    Folder_Dialog::is_empty();
}

Folder_Dialog::~Folder_Dialog()
{
    delete ui;
}

void Folder_Dialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QBrush brush;
    brush.setColor(QColor(232, 231, 231));
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
    painter.setPen(QColor(232, 231, 231));
    //qDebug() << this->rect();
    painter.drawLine(QPointF(20, 90), QPointF(400, 90));
    //    painter.drawRoundedRect(QRect(0, 0, 282, this->height() - 1), 13, 13);
    //    painter.drawRect(QRect(270, 0, 12, this->height() - 1));
}

bool Folder_Dialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->lineEdit)
            ui->lineEdit->setFocus();
        else {
            ui->lineEdit->clearFocus();
            this->setFocus();
        }
    }
    return QWidget::eventFilter(obj, event);
}

void Folder_Dialog::finished()
{
    this->name = ui->lineEdit->text();
    //qDebug() << this->name;
    this->close();
}
