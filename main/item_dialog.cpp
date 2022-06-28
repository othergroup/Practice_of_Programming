#include "item_dialog.h"
#include "ui_item_dialog.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QRegExpValidator>
item_dialog::item_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::item_dialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setModal(true);
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(finished()));
    ui->lineEdit_2->setInputMask("0000/00/00-00:00:00");
    //    QRegExp regx("[0-9]+$");
    //    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit);
    //ui->lineEdit_2->setValidator(validator);

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit_3->installEventFilter(this);
    ui->lineEdit_4->installEventFilter(this);
    ui->pushButton_3->setDefault(true);

    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->lineEdit, &QLineEdit::textChanged, [=]() {
        if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()) {
            ui->pushButton_3->setDefault(true);
            ui->pushButton_4->setDefault(false);
        } else {
            ui->pushButton_4->setDefault(true);
            ui->pushButton_3->setDefault(false);
        }
    });

    connect(ui->pushButton, &QPushButton::clicked, [&]() { this->item.remind = true; });
    connect(ui->pushButton_2, &QPushButton::clicked, [&]() { this->item.remind = false; });
}

item_dialog::~item_dialog()
{
    delete ui;
}

void item_dialog::paintEvent(QPaintEvent *event)
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
}

bool item_dialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->lineEdit) {
            ui->lineEdit->setFocus();
        } else if (obj == ui->lineEdit_2) {
            ui->lineEdit_2->setFocus();
        } else if (obj == ui->lineEdit_3) {
            ui->lineEdit_3->setFocus();
        } else if (obj == ui->lineEdit_4) {
            ui->lineEdit_4->setFocus();
        } else {
            ui->lineEdit->clearFocus();
            ui->lineEdit_2->clearFocus();
            ui->lineEdit_3->clearFocus();
            ui->lineEdit_4->clearFocus();
            this->setFocus();
        }
    }
    return QWidget::eventFilter(obj, event);
}

void item_dialog::finished()
{
    this->item.name = ui->lineEdit->text();
    this->item.time = ui->lineEdit_2->text();
    this->item.place = ui->lineEdit_3->text();
    this->item.other = ui->lineEdit_4->text();
    this->close();
}
