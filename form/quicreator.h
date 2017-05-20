#ifndef QUICREATOR_H
#define QUICREATOR_H

#include <QMainWindow>

class QPushButton;
class QLineEdit;

namespace Ui
{
class QUICreator;
}

class QUICreator : public QMainWindow
{
    Q_OBJECT

public:
    explicit QUICreator(QWidget *parent = 0);
    ~QUICreator();

private:
    Ui::QUICreator *ui;

    QFont iconFont;             //图形字体
    QList<QWidget *> frms;      //设备面板对象集合
    QList<QWidget *> labs;      //图形字体对象集合

    QString currentFile;        //当前QSS文件
    QString currentQSS;         //当前QSS文本
    QString textColor;          //文本颜色
    QString panelColor;         //面板颜色
    QString borderColor;        //边框颜色
    QString normalColorStart;   //普通渐变开始颜色
    QString normalColorEnd;     //普通渐变结束颜色
    QString colorDarkStart;     //加深渐变开始颜色
    QString darkColorEnd;       //加深渐变结束颜色
    QString highColor;          //边缘高亮颜色

private slots:
    void initForm();
    void initTableWidget();
    void initTreeWidget();
    void initListWidget();    
    void initPanelWidget();
    void initNav();
    void initOther();
    void btnClicked();

    void checkColor(const QString &str);
    void setStyle(const QString &str);
    void setColor(QPushButton *btn, const QString &strColor);
    void setColor(QLineEdit *txt, const QString &strColor);
    void changeColor(QLineEdit *txt);
    void changeQss(QString &color, const QString &strColor);

    void buttonClick();
    void textChange(const QString &arg1);

    //新建目录
    void newDir(const QString &dirName);
    //更改QSS文件中对应目录名称
    void changeDir(const QString &dirName);

    //创建png图片文件
    void createAdd(const QString &dir, const QString &name, const QString &color);
    void createRadioButton(const QString &dir, const QString &name, const QString &borderColor, const QString &pannelColor, const QString &textColor);
    void createCheckBox(const QString &dir, const QString &name, const QString &borderColor, const QString &pannelColor, const QString &textColor);
    void createBranch(const QString &dir, const QString &name, const QString &color);
    void createCalendar(const QString &dir, const QString &name, const QString &color);

private:
    QString decimalToStrHex(int decimal);
    bool checkFont(QChar str);

private slots:
    void on_btnInfo_clicked();
    void on_btnQuestion_clicked();
    void on_btnError_clicked();
    void on_btnInput_clicked();
    void on_btnInputPwd_clicked();
    void on_btnInputcbox_clicked();
    void on_btnWidget_clicked();

private slots:
    void on_btnNew_clicked();
    void on_btnSave_clicked();
    void on_btnOpen_clicked();
    void on_btnSaveOther_clicked();
    void on_tabWidget_currentChanged(int index);

    void on_btnUIDemo1_clicked();
    void on_btnUIDemo2_clicked();
    void on_btnUIDemo3_clicked();
    void on_btnUIDemo4_clicked();
    void on_btnUIDemo5_clicked();
    void on_btnUIDemo6_clicked();
    void on_btnUIDemo7_clicked();
    void on_btnUIDemo8_clicked();

public slots:
    //当QUI样式改变时自动应用颜色值
    void changeStyle(const QString &qssFile);
};

#endif // QUICREATOR_H
