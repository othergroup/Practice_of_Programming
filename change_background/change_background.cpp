#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QtGui>
#include <QString>

/*
使用时在头文件中声明 private slots: void choose_background();
在MainWindow构造函数中把此函数和更改背景的按钮进行connect:
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::choose_background);
*/

void MainWindow::choose_background()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open Image"),".","Image Files(*.jpg *.png");

    //弹出对话框选择文件
    if (path.length() == 0)
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files!"));
    //如果没选择会报错

    //设置背景图片
    QPixmap background(path);
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(background));
    this->setPalette(palette);
    this->setMask(background.mask());
    this->setAutoFillBackground(true);
}
