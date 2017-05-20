#include "uidemo2.h"
#include "ui_uidemo2.h"
#include "quiwidget.h"

UIDemo2::UIDemo2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo2)
{
    ui->setupUi(this);
    this->initForm();
    QUIWidget::setFormInCenter(this);
}

UIDemo2::~UIDemo2()
{
    delete ui;
}

void UIDemo2::initForm()
{
    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->setIcon(ui->labIco, QChar(0xF099), 30);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xF068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xF067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xF00d));

    ui->widgetTitle->setProperty("form", "title");
    ui->widgetLeft->setProperty("nav", "left");
    ui->widgetTop->setProperty("nav", "top");
    ui->labTitle->setText("智能访客管理平台");
    ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->labTitle->text());

    ui->label->setStyleSheet("QLabel{font:30pt;}");

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->btnMain->click();

    //设置左侧导航按钮
    QList<QPushButton *> btns = ui->widgetLeft->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(btnClick()));
    }

    ui->btn1->click();
}

void UIDemo2::buttonClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    QList<QToolButton *> btns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }

    ui->label->setText(QString("你单击了顶部导航菜单\n%1").arg(name));
}

void UIDemo2::btnClick()
{
    QPushButton *b = (QPushButton *)sender();
    QString name = b->text();

    QList<QPushButton *> btns = ui->widgetLeft->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }

    ui->label->setText(QString("你单击了左侧导航菜单\n%1").arg(name));
}

void UIDemo2::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo2::on_btnMenu_Max_clicked()
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

void UIDemo2::on_btnMenu_Close_clicked()
{
    close();
}
