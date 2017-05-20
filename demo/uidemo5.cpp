#include "uidemo5.h"
#include "ui_uidemo5.h"
#include "navlistview.h"
#include "quiwidget.h"

UIDemo5::UIDemo5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo5)
{
    ui->setupUi(this);
    this->initForm();
    QUIWidget::setFormInCenter(this);
    QTimer::singleShot(100, this, SLOT(initIndex()));
}

UIDemo5::~UIDemo5()
{
    delete ui;
}

void UIDemo5::initForm()
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
    qss.append("QListView#listView{background:rgb(52,73,94);border-width:0px;}");    
    this->setStyleSheet(qss.join(""));

    QStringList listItem;
    listItem.append("主界面||0|");

    listItem.append("系统设置||0|");
    listItem.append("防区信息|系统设置||");
    listItem.append("位置调整|系统设置||");
    listItem.append("地图编辑|系统设置||");

    listItem.append("警情查询||0|");
    listItem.append("记录查询|警情查询||");
    listItem.append("图像查询|警情查询||");
    listItem.append("视频查询|警情查询||");
    listItem.append("数据回放|警情查询||");

    listItem.append("信息管理||0|");
    listItem.append("学生管理|信息管理|0|");
    listItem.append("教师管理|信息管理|0|");
    listItem.append("成绩管理|信息管理|0|");

    listItem.append("帮助文档||1|");

    ui->listView->setData(listItem);
    ui->listView->setColorLine(QColor(32, 53, 74));
    ui->listView->setColorBgNormal(QColor(52, 73, 94));
    ui->listView->setColorBgHover(QColor(24, 189, 155));
    ui->listView->setColorBgSelected(QColor(24, 189, 155));
    ui->listView->setColorTextNormal(QColor(250, 250, 250));
    ui->listView->setColorTextHover(QColor(0, 0, 0));
    ui->listView->setColorTextSelected(QColor(252, 252, 252));

    QString items = "会员积分;积分;等级";
    ui->widgetNavTop->setItems(items);
    ui->widgetNavTop->setHorizontal(true);
    ui->widgetNavTop->setLineWidth(5);
    ui->widgetNavTop->setSpace(100);
    ui->widgetNavTop->setLineColor(QColor(255, 107, 107));
    ui->widgetNavTop->setBgColorStart(QColor(255, 255, 255));
    ui->widgetNavTop->setBgColorEnd(QColor(255, 255, 255));
    ui->widgetNavTop->setBarColorStart(QColor(24, 189, 155));
    ui->widgetNavTop->setBarColorEnd(QColor(24, 189, 155));
    ui->widgetNavTop->setTextNormalColor(QColor(80, 80, 80));
    ui->widgetNavTop->setTextSelectColor(QColor(250, 250, 250));
}

void UIDemo5::initIndex()
{
    ui->widgetNavTop->setCurrentIndex(0);    
}

void UIDemo5::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo5::on_btnMenu_Max_clicked()
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

void UIDemo5::on_btnMenu_Close_clicked()
{
    close();
}

void UIDemo5::on_listView_pressed(const QModelIndex &index)
{
    ui->label->setText(index.data().toString());
}
