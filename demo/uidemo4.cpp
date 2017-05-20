#include "uidemo4.h"
#include "ui_uidemo4.h"
#include "sliderbar.h"
#include "quiwidget.h"
#include "qtimer.h"

UIDemo4::UIDemo4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo4)
{
    ui->setupUi(this);
    this->initForm();
    QUIWidget::setFormInCenter(this);
    QTimer::singleShot(100, this, SLOT(initIndex()));
}

UIDemo4::~UIDemo4()
{
    delete ui;
}

void UIDemo4::initForm()
{
    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    this->setWindowTitle("智能访客管理平台");

    IconHelper::Instance()->setIcon(ui->labTitle, QChar(0xf072), 35);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xF068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xF067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xF00d));

    QStringList qss;
    qss.append("QLabel#labTitle{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2AA2DA, stop:1 #12B5C9);color:#F0F0F0;}");
    qss.append("QWidget#widgetTop{background:#FFFFFF;}");
    qss.append("QWidget#widgetMain{background:#F1F3F6;}");
    qss.append("QLabel#label{color:#202020;font:50pt;}");
    this->setStyleSheet(qss.join(""));

    QString items = "会员管理;商品管理;支付管理;订单管理;系统管理;短信管理";
    ui->widgetNavLeft->setItems(items);
    ui->widgetNavLeft->setHorizontal(false);
    ui->widgetNavLeft->setLineWidth(5);
    ui->widgetNavLeft->setLineColor(QColor("#029FEA"));
    ui->widgetNavLeft->setBgColorStart(QColor("#292F38"));
    ui->widgetNavLeft->setBgColorEnd(QColor("#292F38"));
    ui->widgetNavLeft->setBarColorStart(QColor("#1D2025"));
    ui->widgetNavLeft->setBarColorEnd(QColor("#1D2025"));
    ui->widgetNavLeft->setTextNormalColor(QColor("#54626F"));
    ui->widgetNavLeft->setTextSelectColor(QColor("#FDFDFD"));
    ui->widgetNavLeft->setBarStyle(SliderBar::BarStyle_Line_Left);

    items = "会员积分;积分;等级";
    ui->widgetNavTop->setItems(items);
    ui->widgetNavTop->setHorizontal(true);
    ui->widgetNavTop->setLineWidth(5);
    ui->widgetNavTop->setSpace(100);
    ui->widgetNavTop->setLineColor(QColor("#1CA0E4"));
    ui->widgetNavTop->setBgColorStart(QColor("#FFFFFF"));
    ui->widgetNavTop->setBgColorEnd(QColor("#FFFFFF"));
    ui->widgetNavTop->setBarColorStart(QColor("#FAFBFD"));
    ui->widgetNavTop->setBarColorEnd(QColor("#FAFBFD"));
    ui->widgetNavTop->setTextNormalColor(QColor("#6D7173"));
    ui->widgetNavTop->setTextSelectColor(QColor("#6D7173"));
    ui->widgetNavTop->setBarStyle(SliderBar::BarStyle_Line_Bottom);

    connect(ui->widgetNavLeft, SIGNAL(currentItemChanged(int, QString)),
            this, SLOT(currentItemChanged(int, QString)));
    connect(ui->widgetNavTop, SIGNAL(currentItemChanged(int, QString)),
            this, SLOT(currentItemChanged(int, QString)));
}

void UIDemo4::initIndex()
{
    ui->widgetNavLeft->setCurrentIndex(0);
    ui->widgetNavTop->setCurrentIndex(0);
}

void UIDemo4::currentItemChanged(int , const QString &item)
{
    ui->label->setText(item);
}

void UIDemo4::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo4::on_btnMenu_Max_clicked()
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

void UIDemo4::on_btnMenu_Close_clicked()
{
    close();
}
