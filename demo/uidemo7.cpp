#include "uidemo7.h"
#include "ui_uidemo7.h"
#include "quiwidget.h"

UIDemo7::UIDemo7(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo7)
{
    ui->setupUi(this);
    this->initForm();
    this->initNavLeft();
    this->initNavTop();
    QUIWidget::setFormInCenter(this);
}

UIDemo7::~UIDemo7()
{
    delete ui;
}

void UIDemo7::initForm()
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

    ui->widgetNavLeft->setProperty("flag", "left");
    ui->widgetNavTop->setProperty("flag", "bottom");

    //应用样式
    QStringList qss;
    qss.append("QLabel#labTitle{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2AA2DA, stop:1 #12B5C9);color:#F0F0F0;}");
    qss.append("QWidget#widgetTop{background:#FFFFFF;}");
    qss.append("QWidget#widgetMain{background:#F1F3F6;}");
    qss.append("QLabel#label{color:#202020;font:50pt;}");
    qss.append("QWidget#widgetNavLeft{background:#292F38;}");
    this->setStyleSheet(qss.join(""));
}

void UIDemo7::buttonClickedLeft()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = tbtnLeft.count();
    for (int i = 0; i < count; i++) {
        if (tbtnLeft.at(i) == b) {
            tbtnLeft.at(i)->setIcon(QIcon(pixDarkLeft.at(i)));
            tbtnLeft.at(i)->setChecked(true);
        } else {
            tbtnLeft.at(i)->setIcon(QIcon(pixNormalLeft.at(i)));
            tbtnLeft.at(i)->setChecked(false);
        }
    }

    ui->label->setText(name);
}

void UIDemo7::buttonClickedTop()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = tbtnTop.count();
    for (int i = 0; i < count; i++) {
        if (tbtnTop.at(i) == b) {
            tbtnTop.at(i)->setIcon(QIcon(pixDarkTop.at(i)));
            tbtnTop.at(i)->setChecked(true);
        } else {
            tbtnTop.at(i)->setIcon(QIcon(pixNormalTop.at(i)));
            tbtnTop.at(i)->setChecked(false);
        }
    }

    ui->label->setText(name);
}

void UIDemo7::initNavLeft()
{
    int borderWidth = 3;
    QString borderColor = "#029FEA";
    QString normalBgColor = "#292F38";
    QString selectBgColor = "#1D2025";
    QString normalTextColor = "#54626F";
    QString selectTextColor = "#FDFDFD";

    setStyle(ui->widgetNavLeft, borderWidth, borderColor, normalBgColor, selectBgColor, normalTextColor, selectTextColor);

    int size = 25;
    int pixWidth = 30;
    int pixHeight = 30;
    pixCharLeft << 0xf042 << 0xf045 << 0xf179 << 0xf056 << 0xf123 << 0xf099;
    tbtnLeft << ui->tbtn1 << ui->tbtn2 << ui->tbtn3 << ui->tbtn4 << ui->tbtn5 << ui->tbtn6;

    int count = tbtnLeft.count();
    for (int i = 0; i < count; i++) {
        pixNormalLeft.append(IconHelper::Instance()->getPixmap(normalTextColor, QChar(pixCharLeft.at(i)), size, pixWidth, pixHeight));
        pixDarkLeft.append(IconHelper::Instance()->getPixmap(selectTextColor, QChar(pixCharLeft.at(i)), size, pixWidth, pixHeight));
        tbtnLeft.at(i)->setIcon(QIcon(pixNormalLeft.at(i)));
        tbtnLeft.at(i)->setIconSize(QSize(size, size));
        tbtnLeft.at(i)->setCheckable(true);
        tbtnLeft.at(i)->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(tbtnLeft.at(i), SIGNAL(clicked(bool)), this, SLOT(buttonClickedLeft()));
    }

    ui->tbtn1->click();
}

void UIDemo7::initNavTop()
{
    int borderWidth = 5;
    QString borderColor = "#1CA0E4";
    QString normalBgColor = "#FFFFFF";
    QString selectBgColor = "#FAFBFD";
    QString normalTextColor = "#6D7173";
    QString selectTextColor = "#6D7173";

    setStyle(ui->widgetNavTop, borderWidth, borderColor, normalBgColor, selectBgColor, normalTextColor, selectTextColor);

    int size = 20;
    int pixWidth = 25;
    int pixHeight = 25;
    pixCharTop << 0xf042 << 0xf045 << 0xf179;
    tbtnTop << ui->btn1 << ui->btn2 << ui->btn3;

    int count = tbtnTop.count();
    for (int i = 0; i < count; i++) {
        pixNormalTop.append(IconHelper::Instance()->getPixmap(normalTextColor, QChar(pixCharTop.at(i)), size, pixWidth, pixHeight));
        pixDarkTop.append(IconHelper::Instance()->getPixmap(selectTextColor, QChar(pixCharTop.at(i)), size, pixWidth, pixHeight));
        tbtnTop.at(i)->setIcon(QIcon(pixNormalTop.at(i)));
        tbtnTop.at(i)->setIconSize(QSize(size, size));
        tbtnTop.at(i)->setCheckable(true);
        tbtnTop.at(i)->setToolButtonStyle(Qt::ToolButtonTextOnly);
        //tbtnTop.at(i)->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        connect(tbtnTop.at(i), SIGNAL(clicked(bool)), this, SLOT(buttonClickedTop()));
    }

    ui->btn1->click();
}

void UIDemo7::setStyle(QWidget *widget, int borderWidth, QString borderColor,
                       QString normalBgColor, QString selectBgColor,
                       QString normalTextColor, QString selectTextColor)
{
    QStringList qss;

    qss.append(QString("QWidget[flag=\"left\"] QAbstractButton{"
                       "border-style:none;"
                       "border-radius:0px;"
                       "padding:5px;"
                       "color:%1;"
                       "background:%2;}")
               .arg(normalTextColor)
               .arg(normalBgColor));

    qss.append(QString("QWidget[flag=\"left\"] QAbstractButton:hover,"
                       "QWidget[flag=\"left\"] QAbstractButton:pressed,"
                       "QWidget[flag=\"left\"] QAbstractButton:checked{"
                       "border-style:solid;"
                       "border-width:0px 0px 0px %1px;"
                       "padding:%2px %2px %2px %1px;"
                       "border-color:%3;"
                       "color:%4;"
                       "background:%5;}")
               .arg(borderWidth)
               .arg(borderWidth * 2)
               .arg(borderColor)
               .arg(selectTextColor)
               .arg(selectBgColor));

    qss.append(QString("QWidget[flag=\"bottom\"] QAbstractButton{"
                       "border-style:none;"
                       "border-radius:0px;"
                       "padding:5px;"
                       "color:%1;"
                       "background:%2;}")
               .arg(normalTextColor)
               .arg(normalBgColor));

    qss.append(QString("QWidget[flag=\"bottom\"] QAbstractButton:hover,"
                       "QWidget[flag=\"bottom\"] QAbstractButton:pressed,"
                       "QWidget[flag=\"bottom\"] QAbstractButton:checked{"
                       "border-style:solid;"
                       "border-width:0px 0px %1px 0px;"
                       "padding:%2px %2px %1px %2px;"
                       "border-color:%3;"
                       "color:%4;"
                       "background:%5;}")
               .arg(borderWidth)
               .arg(borderWidth * 2)
               .arg(borderColor)
               .arg(selectTextColor)
               .arg(selectBgColor));

    widget->setStyleSheet(qss.join(""));
}


void UIDemo7::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo7::on_btnMenu_Max_clicked()
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

void UIDemo7::on_btnMenu_Close_clicked()
{
    close();
}
