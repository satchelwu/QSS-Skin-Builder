#include "uidemo6.h"
#include "ui_uidemo6.h"
#include "quiwidget.h"

UIDemo6::UIDemo6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo6)
{
    ui->setupUi(this);
    this->initForm();
    QUIWidget::setFormInCenter(this);
}

UIDemo6::~UIDemo6()
{
    delete ui;
}

void UIDemo6::initForm()
{
    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    ui->labTitle->setText("智能访客管理平台");
    this->setWindowTitle("智能访客管理平台");

    QStringList qss;
    qss.append("QLabel#label{color:#F0F0F0;font:50pt;}");
    qss.append("QWidget#widgetLeft>QAbstractButton{background:none;border-radius:0px;}");
    qss.append("QWidget#widgetMenu>QAbstractButton{border:0px solid #FF0000;border-radius:0px;padding:0px;margin:0px;}");
    this->setStyleSheet(qss.join(""));

    //添加自定义属性,用于切换ico用
    ui->btnInfoExtend->setProperty("icoName", "infoextend");
    ui->btnTroubleCheck->setProperty("icoName", "troublecheck");
    ui->btnWifiTest->setProperty("icoName", "wifitest");
    ui->btnSpeedTest->setProperty("icoName", "speedtest");
    ui->btnWebsiteTest->setProperty("icoName", "websitetest");

    QList<QToolButton *> btns = ui->widgetLeft->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {
        btn->setMaximumHeight(80);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClick()));
    }

    ui->btnInfoExtend->click();
}

void UIDemo6::buttonClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString text = b->text();    

    QList<QToolButton *> btns = ui->widgetLeft->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {
        QString icoName = btn->property("icoName").toString();
        if (btn != b) {
            btn->setChecked(false);
            btn->setIcon(QIcon(QString(":/image/%1.png").arg(icoName)));
        } else {
            btn->setChecked(true);
            btn->setIcon(QIcon(QString(":/image/%1_focus.png").arg(icoName)));
        }
    }

    ui->label->setText(text);
}

void UIDemo6::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo6::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        this->setProperty("canMove", true);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        this->setProperty("canMove", false);
    }

    max = !max;
}

void UIDemo6::on_btnMenu_Close_clicked()
{
    close();
}
