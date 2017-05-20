#include "uidemo3.h"
#include "ui_uidemo3.h"
#include "quiwidget.h"
#include "frmdevice.h"
#include "qtimer.h"

UIDemo3::UIDemo3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo3)
{
    ui->setupUi(this);
    this->initForm();
    this->initTreeWidget();
    this->initTableWidget();
    this->initMenu();
    QUIWidget::setFormInCenter(this);
    QTimer::singleShot(100, this, SLOT(initPanelWidget()));
}

UIDemo3::~UIDemo3()
{
    delete ui;
}

void UIDemo3::initForm()
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
    ui->widgetTop->setProperty("nav", "top");
    ui->labTitle->setText("智能访客管理平台");
    ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->labTitle->text());

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
    }

    QList<int> widths;
    widths << 170 << 650;
    ui->splitterH->setSizes(widths);

    QList<int> heights;
    heights << 400 << 200;
    ui->splitterV->setSizes(heights);
}

void UIDemo3::initTreeWidget()
{
    ui->treeWidget->clear();
    ui->treeWidget->setHeaderLabel(" 树状列表控件");

    QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, "父元素1");
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group1->setCheckState(0, Qt::PartiallyChecked);

    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setText(0, "子元素1");
    subItem11->setCheckState(0, Qt::Checked);

    QTreeWidgetItem *subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setText(0, "子元素2");
    subItem12->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setText(0, "子元素3");
    subItem13->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *group2 = new QTreeWidgetItem(ui->treeWidget);
    group2->setText(0, "父元素2");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group2->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setText(0, "子元素1");
    subItem21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem211 = new QTreeWidgetItem(subItem21);
    subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem211->setText(0, "子子元素1");
    subItem211->setCheckState(0, Qt::Unchecked);

    ui->treeWidget->expandAll();
}

void UIDemo3::initPanelWidget()
{
    //加载设备面板
    qDeleteAll(frms);
    frms.clear();

    for (int i = 0; i < 100; i++) {
        frmDevice *frm = new frmDevice;
        frm->setFixedHeight(100);
        frm->setDeviceName(QString("温湿度设备 %1").arg(i + 1));
        frm->setDeviceTemp(25.8);
        frm->setDeviceDamp(56.5);
        frm->setCountAll(1024);
        frm->setCountNoRead(1);
        frms.append(frm);
    }

    ui->widgetPanel->setWidget(frms, 7);
    ui->widgetPanel->setMargin(3);
    ui->widgetPanel->setSpacing(3);
}

void UIDemo3::initTableWidget()
{
    //设置列数和列宽
    int width = qApp->desktop()->availableGeometry().width() - 120;
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, width * 0.06);
    ui->tableWidget->setColumnWidth(1, width * 0.10);
    ui->tableWidget->setColumnWidth(2, width * 0.06);
    ui->tableWidget->setColumnWidth(3, width * 0.10);
    ui->tableWidget->setColumnWidth(4, width * 0.15);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "设备编号" << "设备名称" << "设备地址" << "告警内容" << "告警时间";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tableWidget->setRowCount(300);

    for (int i = 0; i < 300; i++) {
        ui->tableWidget->setRowHeight(i, 24);

        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        itemDeviceID->setTextAlignment(Qt::AlignCenter);
        itemDeviceName->setTextAlignment(Qt::AlignCenter);
        itemDeviceAddr->setTextAlignment(Qt::AlignCenter);
        itemContent->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(i, 0, itemDeviceID);
        ui->tableWidget->setItem(i, 1, itemDeviceName);
        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget->setItem(i, 3, itemContent);
        ui->tableWidget->setItem(i, 4, itemTime);
    }
}

void UIDemo3::initMenu()
{
    QMenu *menu = new QMenu(this);
    menu->addAction("端口管理", this, SLOT(doMenu()));
    menu->addAction("设备管理", this, SLOT(doMenu()));
    menu->addAction("告警设置", this, SLOT(doMenu()));
    menu->addSeparator();
    menu->addAction("系统设置", this, SLOT(doMenu()));
    menu->addAction("修改密码", this, SLOT(doMenu()));
    menu->addSeparator();
    menu->addAction("同步间隔", this, SLOT(doMenu()));

    ui->btnMain->setPopupMode(QToolButton::InstantPopup);
    ui->btnMain->setMenu(menu);
}

void UIDemo3::doMenu()
{
    QAction *action = (QAction *)sender();
    QUIWidget::showMessageBoxInfo(QString("你选择了菜单 [%1]").arg(action->text()), 5);
}

void UIDemo3::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo3::on_btnMenu_Max_clicked()
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

void UIDemo3::on_btnMenu_Close_clicked()
{
    close();
}
