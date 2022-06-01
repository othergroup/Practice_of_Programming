使用时在头文件中声明 `private slots: void choose_background();`

在MainWindow构造函数中把此函数和更改背景的按钮进行connect:
```C++
connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::choose_background);
```
