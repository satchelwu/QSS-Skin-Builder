#include "quicreator.h"
#include "ui_quicreator.h"

#include "quiwidget.h"
#include "frmdevice.h"
#include "highlighter.h"

#include "demo/uidemo1.h"
#include "demo/uidemo2.h"
#include "demo/uidemo3.h"
#include "demo/uidemo4.h"
#include "demo/uidemo5.h"
#include "demo/uidemo6.h"
#include "demo/uidemo7.h"
#include "demo/uidemo8.h"

QUICreator::QUICreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QUICreator)
{
    ui->setupUi(this);
    this->initForm();
}

QUICreator::~QUICreator()
{
    delete ui;
}

void QUICreator::initForm()
{
    //引入图形字体
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont = QFont(fontName);

    initTableWidget();
    initTreeWidget();
    initListWidget();
    initNav();
    initOther();

    on_btnNew_clicked();
    QTimer::singleShot(100, this, SLOT(initPanelWidget()));

    ui->tabWidget->setCurrentIndex(7);
}

void QUICreator::initTableWidget()
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

        ui->tableWidget->setItem(i, 0, itemDeviceID);
        ui->tableWidget->setItem(i, 1, itemDeviceName);
        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget->setItem(i, 3, itemContent);
        ui->tableWidget->setItem(i, 4, itemTime);
    }
}

void QUICreator::initTreeWidget()
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

void QUICreator::initListWidget()
{
    QStringList items;
    for (int i = 1; i <= 30; i++) {
        items << QString("元素%1").arg(i);
    }

    ui->listWidget->addItems(items);
    ui->cbox1->addItems(items);
    ui->cbox2->addItems(items);
}

void QUICreator::initNav()
{
    //设置左边按钮菜单
    QList<QPushButton *> btns = ui->widgetLeft->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClicked()));
    }

    ui->btn1->click();
}

void QUICreator::initPanelWidget()
{
    //加载设备面板
    qDeleteAll(frms);
    frms.clear();

    for (int i = 0; i < 50; i++) {
        frmDevice *frm = new frmDevice;
        frm->setFixedHeight(100);
        frm->setDeviceName(QString("温湿度设备 %1").arg(i + 1));
        frm->setDeviceTemp(25.8);
        frm->setDeviceDamp(56.5);
        frms.append(frm);
    }

    ui->widgetPanel->setWidget(frms, 7);
    ui->widgetPanel->setMargin(3);
    ui->widgetPanel->setSpacing(3);

    //加载图形字体面板
    qDeleteAll(labs);
    labs.clear();
    iconFont.setPixelSize(15);

    QStringList list;
    for (int i = 0; i < 740; i++) {
        QChar str = QChar(0xf000 + i);
        QString tip = QString("0xf%1").arg(i, 3, 16, QChar('0'));
        if (!checkFont(str)) {
            list << tip;
            continue;
        }

        QLabel *lab = new QLabel;
        lab->setAlignment(Qt::AlignCenter);
        lab->setFont(iconFont);
        lab->setText(str);
        lab->setToolTip(tip);
        lab->setMinimumSize(30, 30);
        labs.append(lab);
    }

    qDebug() << "no text font" << list.count() << list;

    ui->widgetFontPanel->setWidget(labs, 20);
    ui->widgetFontPanel->setMargin(3);
    ui->widgetFontPanel->setSpacing(3);
}

void QUICreator::initOther()
{
    ui->rbtn1->setChecked(true);
    ui->ck2->setChecked(true);
    ui->ck3->setCheckState(Qt::PartiallyChecked);
    ui->horizontalSlider->setValue(88);

    QList<QPushButton *> btnColors = ui->frameColor->findChildren<QPushButton *>();

    foreach (QPushButton *btn, btnColors) {
        connect(btn, SIGNAL(pressed()), this, SLOT(buttonClick()));
    }

    QList<QLineEdit *> txtColors = ui->frameColor->findChildren<QLineEdit *>();

    foreach (QLineEdit *txt, txtColors) {
        connect(txt, SIGNAL(textChanged(QString)), this, SLOT(textChange(QString)));
    }

    //语法高亮
    new Highlighter(ui->txtMain->document());

    //公开版禁用按钮
#ifdef demo
    ui->btnNew->setEnabled(false);
    ui->btnSave->setEnabled(false);
    ui->btnSaveOther->setEnabled(false);
    ui->btnOpen->setEnabled(false);
    ui->frameColor->setEnabled(false);
    ui->txtMain->clear();
    ui->txtMain->setEnabled(false);
#endif

    ui->tab9->setStyleSheet("QPushButton{font:20pt;}");
    ui->widgetVideo->setStyleSheet("QLabel{font:20pt;}");

    ui->widgetLeft->setProperty("nav", "left");
    ui->widgetBottom->setProperty("form", "bottom");
    ui->widgetTop->setProperty("nav", "top");
    ui->widgetVideo->setProperty("video", true);

    QList<QLabel *> labChs = ui->widgetVideo->findChildren<QLabel *>();
    foreach (QLabel *lab, labChs) {
        lab->setFocusPolicy(Qt::StrongFocus);
    }
}

void QUICreator::btnClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    QString objName = btn->objectName();

    QList<QPushButton *> btns = ui->widgetLeft->findChildren<QPushButton *>();

    foreach (QPushButton *b, btns) {
        if (b == btn) {
            b->setChecked(true);
        } else {
            b->setChecked(false);
        }
    }

    if (objName == "btn1") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (objName == "btn2") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (objName == "btn3") {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void QUICreator::on_btnInfo_clicked()
{
    QUIWidget::showMessageBoxInfo("恭喜你,中了500万大奖!请到飞扬青云处领取大奖!");
}

void QUICreator::on_btnQuestion_clicked()
{
    QUIWidget::showMessageBoxQuestion("确定不要当前的500万大奖吗?");
}

void QUICreator::on_btnError_clicked()
{
    QUIWidget::showMessageBoxError("领取500万大奖发生错误,请重试!");
}

void QUICreator::on_btnInput_clicked()
{
    bool ok;
    QString txt = QUIWidget::showInputBox(ok, "请输入姓名:");

    if (ok) {
        QUIWidget::showMessageBoxInfo(QString("您输入的姓名是 : %1").arg(txt));
    }
}

void QUICreator::on_btnInputPwd_clicked()
{
    bool ok;
    QString txt = QUIWidget::showInputBox(ok, "请输入领取500万大奖密码:", 0, 0, "领取500万大奖密码", true);

    if (ok) {
        QUIWidget::showMessageBoxInfo(QString("您输入的密码是 : %1").arg(txt));
    }
}

void QUICreator::on_btnInputcbox_clicked()
{
    bool ok;
    QStringList defaultValue;

    for (int i = 1; i <= 50; i++) {
        defaultValue.append(QString::number(i));
    }

    QString txt = QUIWidget::showInputBox(ok, "请选择学号:", 1, 0, defaultValue.join("|"));

    if (ok) {
        QUIWidget::showMessageBoxInfo(QString("您选择的学号是 : %1").arg(txt));
    }
}

void QUICreator::on_btnWidget_clicked()
{
    //两种方式弹出都可以
#if 0
    QUIWidget *qui = new QUIWidget;
    qui->setTitle("新窗体测试");
    qui->setAlignment(Qt::AlignCenter);
    qui->setMainWidget(new QWidget);
    qui->show();
#else
    QUIWidget qui;
    qui.setTitle("新窗体测试");
    qui.setAlignment(Qt::AlignCenter);
    qui.setMainWidget(new QWidget);
    qui.setOnlyCloseBtn();
    qui.exec();
#endif
}

void QUICreator::checkColor(const QString &str)
{
    QString flagTextColor = "TextColor:";
    int indexTextColor = str.indexOf(flagTextColor);

    if (indexTextColor >= 0) {
        QString strTextColor = str.mid(indexTextColor + flagTextColor.length(), 7);
        setColor(ui->txtTextColor, strTextColor);
        qDebug() << flagTextColor << strTextColor;
        textColor = strTextColor;
    }

    QString flagPanelColor = "PanelColor:";
    int indexPanelColor = str.indexOf(flagPanelColor);

    if (indexPanelColor >= 0) {
        QString strPanelColor = str.mid(indexPanelColor + flagPanelColor.length(), 7);
        setColor(ui->txtPanelColor, strPanelColor);
        qDebug() << flagPanelColor << strPanelColor;
        panelColor = strPanelColor;
    }

    QString flagBorderColor = "BorderColor:";
    int indexBorderColor = str.indexOf(flagBorderColor);

    if (indexBorderColor >= 0) {
        QString strBorderColor = str.mid(indexBorderColor + flagBorderColor.length(), 7);
        setColor(ui->txtBorderColor, strBorderColor);
        qDebug() << flagBorderColor << strBorderColor;
        borderColor = strBorderColor;
    }

    QString flagNormalColorStart = "NormalColorStart:";
    int indexNormalColorStart = str.indexOf(flagNormalColorStart);

    if (indexNormalColorStart >= 0) {
        QString strNormalColorStart = str.mid(indexNormalColorStart + flagNormalColorStart.length(), 7);
        setColor(ui->txtNormalColorStart, strNormalColorStart);
        qDebug() << flagNormalColorStart << strNormalColorStart;
        normalColorStart = strNormalColorStart;
    }

    QString flagNormalColorEnd = "NormalColorEnd:";
    int indexNormalColorEnd = str.indexOf(flagNormalColorEnd);

    if (indexNormalColorEnd >= 0) {
        QString strNormalColorEnd = str.mid(indexNormalColorEnd + flagNormalColorEnd.length(), 7);
        setColor(ui->txtNormalColorEnd, strNormalColorEnd);
        qDebug() << flagNormalColorEnd << strNormalColorEnd;
        normalColorEnd = strNormalColorEnd;
    }

    QString flagDarkColorStart = "DarkColorStart:";
    int indexDarkColorStart = str.indexOf(flagDarkColorStart);

    if (indexDarkColorStart >= 0) {
        QString strDarkColorStart = str.mid(indexDarkColorStart + flagDarkColorStart.length(), 7);
        setColor(ui->txtDarkColorStart, strDarkColorStart);
        qDebug() << flagDarkColorStart << strDarkColorStart;
        colorDarkStart = strDarkColorStart;
    }

    QString flagDarkColorEnd = "DarkColorEnd:";
    int indexDarkColorEnd = str.indexOf(flagDarkColorEnd);

    if (indexDarkColorEnd >= 0) {
        QString strDarkColorEnd = str.mid(indexDarkColorEnd + flagDarkColorEnd.length(), 7);
        setColor(ui->txtDarkColorEnd, strDarkColorEnd);
        qDebug() << flagDarkColorEnd << strDarkColorEnd;
        darkColorEnd = strDarkColorEnd;
    }

    QString flagHighColor = "HighColor:";
    int indexHighColor = str.indexOf(flagHighColor);

    if (indexHighColor >= 0) {
        QString strHighColor = str.mid(indexHighColor + flagHighColor.length(), 7);
        setColor(ui->txtHighColor, strHighColor);
        qDebug() << flagHighColor << strHighColor;
        highColor = strHighColor;
    }
}

void QUICreator::setStyle(const QString &str)
{
    static QString qss;

    if (qss == str) {
        return;
    }

    qss = str;
    QString paletteColor = str.mid(20, 7);
    qApp->setPalette(QPalette(QColor(paletteColor)));
    qApp->setStyleSheet(str);
    ui->widgetPanel->setStyleSheet(QString("QFrame#boxPanel{border-width:0px;background:%1;}"
                                           "QFrame#gboxDevicePanel,QFrame#gboxDeviceTitle{padding:3px;}")
                                   .arg(paletteColor));

#ifndef demo
    ui->txtMain->setText(str);
#endif
}

void QUICreator::setColor(QPushButton *btn, const QString &strColor)
{
    if (!strColor.startsWith("#") || strColor.length() < 7) {
        return;
    }

    btn->setStyleSheet(QString("QPushButton{background-color:%1}").arg(strColor));

    if (btn == ui->btnTextColor) {
        changeQss(textColor, strColor);
    } else if (btn == ui->btnPanelColor) {
        changeQss(panelColor, strColor);
    } else if (btn == ui->btnBorderColor) {
        changeQss(borderColor, strColor);
    } else if (btn == ui->btnNormalColorStart) {
        changeQss(normalColorStart, strColor);
    } else if (btn == ui->btnNormalColorEnd) {
        changeQss(normalColorEnd, strColor);
    } else if (btn == ui->btnDarkColorStart) {
        changeQss(colorDarkStart, strColor);
    } else if (btn == ui->btnDarkColorEnd) {
        changeQss(darkColorEnd, strColor);
    } else if (btn == ui->btnHighColor) {
        changeQss(highColor, strColor);
    }
}

void QUICreator::setColor(QLineEdit *txt, const QString &strColor)
{
    if (!strColor.startsWith("#") || strColor.length() < 7) {
        return;
    }

    txt->setText(strColor);

    if (txt == ui->txtHighColor) {
        //设置图形字体面板鼠标悬停时的效果
        QString qss = QString("QLabel:hover,QLabel:focus{color:%1;border:1px solid %1;}").arg(strColor);
        ui->widgetFontPanel->setStyleSheet(qss);
    }
}

void QUICreator::changeColor(QLineEdit *txt)
{
    QColor color = QColorDialog::getColor();

    if (!color.isValid()) {
        return;
    }

    QString strColor = QString("#%1%2%3")
                       .arg(decimalToStrHex(color.red()))
                       .arg(decimalToStrHex(color.green()))
                       .arg(decimalToStrHex(color.blue()));
    strColor = strColor.toUpper();
    setColor(txt, strColor);
}

void QUICreator::changeQss(QString &color, const QString &strColor)
{
    if (!color.isEmpty() && color != strColor) {
        currentQSS = currentQSS.replace(color, strColor);
        color = strColor;
        setStyle(currentQSS);
    }
}

void QUICreator::buttonClick()
{
    QPushButton *btn = (QPushButton *)sender();

    if (btn == ui->btnTextColor) {
        changeColor(ui->txtTextColor);
    } else if (btn == ui->btnPanelColor) {
        changeColor(ui->txtPanelColor);
    } else if (btn == ui->btnBorderColor) {
        changeColor(ui->txtBorderColor);
    } else if (btn == ui->btnNormalColorStart) {
        changeColor(ui->txtNormalColorStart);
    } else if (btn == ui->btnNormalColorEnd) {
        changeColor(ui->txtNormalColorEnd);
    } else if (btn == ui->btnDarkColorStart) {
        changeColor(ui->txtDarkColorStart);
    } else if (btn == ui->btnDarkColorEnd) {
        changeColor(ui->txtDarkColorEnd);
    } else if (btn == ui->btnHighColor) {
        changeColor(ui->txtHighColor);
    }
}

void QUICreator::textChange(const QString &arg1)
{
    QLineEdit *txt = (QLineEdit *)sender();

    if (txt == ui->txtTextColor) {
        setColor(ui->btnTextColor, arg1);
    } else if (txt == ui->txtPanelColor) {
        setColor(ui->btnPanelColor, arg1);
    } else if (txt == ui->txtBorderColor) {
        setColor(ui->btnBorderColor, arg1);
    } else if (txt == ui->txtNormalColorStart) {
        setColor(ui->btnNormalColorStart, arg1);
    } else if (txt == ui->txtNormalColorEnd) {
        setColor(ui->btnNormalColorEnd, arg1);
    } else if (txt == ui->txtDarkColorStart) {
        setColor(ui->btnDarkColorStart, arg1);
    } else if (txt == ui->txtDarkColorEnd) {
        setColor(ui->btnDarkColorEnd, arg1);
    } else if (txt == ui->txtHighColor) {
        setColor(ui->btnHighColor, arg1);
    }
}

void QUICreator::newDir(const QString &dirName)
{
    QString name = dirName;

    //如果路径中包含斜杠字符则说明是绝对路径
    //windows系统 路径字符带有 :/  linux系统路径字符带有 /
    if (!dirName.contains(":/") && !dirName.startsWith("/")) {
        name = QString("%1/%2").arg(qApp->applicationDirPath()).arg(dirName);
    }

    QDir dir(name);
    if (!dir.exists()) {
        dir.mkpath(name);
    }
}

void QUICreator::changeDir(const QString &dirName)
{
    //根据文件名称取出当前样式的名字
    QFileInfo info(currentFile);
    QString fileName = info.fileName();
    QString strOld = "/" + fileName.split(".").at(0) + "/";
    QString strNew = "/" + dirName + "/";

    currentQSS = currentQSS.replace(strOld, strNew);
    setStyle(currentQSS);
}

void QUICreator::createAdd(const QString &dir, const QString &name, const QString &color)
{
    QPixmap pix(20, 20);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(QColor(color));
    painter.setBrush(QColor(color));

    iconFont.setPixelSize(28);
    painter.setFont(iconFont);

    if (name == "add_top") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf0d8));
    } else if (name == "add_right") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf0da));
    } else if (name == "add_bottom") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf0d7));
    } else if (name == "add_left") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf0d9));
    }

    painter.end();

    pix.save(QString("%1/%2/%3.png").arg(qApp->applicationDirPath()).arg(dir).arg(name), "png");
}

void QUICreator::createRadioButton(const QString &dir, const QString &name, const QString &borderColor, const QString &pannelColor, const QString &textColor)
{
    QPixmap pix(20, 20);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(QPen(QColor(borderColor), 2));
    painter.setBrush(QColor(pannelColor));

    if (name == "radiobutton_checked") {
        painter.drawEllipse(2, 2, 16, 16);
        painter.setPen(QColor(textColor));
        painter.setBrush(QColor(textColor));
        painter.drawEllipse(6, 6, 8, 8);
    } else if (name == "radiobutton_checked_disable") {
        painter.setOpacity(0.4);
        painter.drawEllipse(2, 2, 16, 16);
        painter.setPen(QColor(textColor));
        painter.setBrush(QColor(textColor));
        painter.drawEllipse(6, 6, 8, 8);
    } else if (name == "radiobutton_unchecked") {
        painter.drawEllipse(2, 2, 16, 16);
    } else if (name == "radiobutton_unchecked_disable") {
        painter.setOpacity(0.4);
        painter.drawEllipse(2, 2, 16, 16);
    }

    painter.end();

    pix.save(QString("%1/%2/%3.png").arg(qApp->applicationDirPath()).arg(dir).arg(name), "png");
}

void QUICreator::createCheckBox(const QString &dir, const QString &name, const QString &borderColor, const QString &pannelColor, const QString &textColor)
{
    QPixmap pix(20, 20);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(QPen(QColor(borderColor), 2));
    painter.setBrush(QColor(pannelColor));

    iconFont.setPixelSize(20);
    painter.setFont(iconFont);

    if (name == "checkbox_checked") {
        painter.drawRect(pix.rect());
        painter.setPen(QColor(textColor));
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf00c));
    } else if (name == "checkbox_checked_disable") {
        painter.setOpacity(0.4);
        painter.drawRect(pix.rect());
        painter.setPen(QColor(textColor));
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf00c));
    } else if (name == "checkbox_parcial") {
        painter.drawRect(pix.rect());
        painter.setPen(QColor(textColor));
        painter.setBrush(QColor(textColor));
        painter.drawRect(5, 5, 10, 10);
    } else if (name == "checkbox_parcial_disable") {
        painter.setOpacity(0.4);
        painter.drawRect(pix.rect());
        painter.setPen(QColor(textColor));
        painter.setBrush(QColor(textColor));
        painter.drawRect(5, 5, 10, 10);
    } else if (name == "checkbox_unchecked") {
        painter.drawRect(pix.rect());
    } else if (name == "checkbox_unchecked_disable") {
        painter.setOpacity(0.4);
        painter.drawRect(pix.rect());
    }

    painter.end();

    pix.save(QString("%1/%2/%3.png").arg(qApp->applicationDirPath()).arg(dir).arg(name), "png");
}

void QUICreator::createBranch(const QString &dir, const QString &name, const QString &color)
{
    QPixmap pix(20, 20);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(QColor(color));
    painter.setBrush(QColor(color));

    iconFont.setPixelSize(20);
    painter.setFont(iconFont);

    if (name == "branch_open") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf067));
    } else if (name == "branch_close") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf068));
    }

    painter.end();

    pix.save(QString("%1/%2/%3.png").arg(qApp->applicationDirPath()).arg(dir).arg(name), "png");
}

void QUICreator::createCalendar(const QString &dir, const QString &name, const QString &color)
{
    QPixmap pix(20, 20);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(QColor(color));
    painter.setBrush(QColor(color));

    iconFont.setPixelSize(20);
    painter.setFont(iconFont);

    if (name == "calendar_prevmonth") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf060));
    } else if (name == "calendar_nextmonth") {
        painter.drawText(pix.rect(), Qt::AlignCenter, QChar(0xf061));
    }

    painter.end();

    pix.save(QString("%1/%2/%3.png").arg(qApp->applicationDirPath()).arg(dir).arg(name), "png");
}

QString QUICreator::decimalToStrHex(int decimal)
{
    QString temp = QString::number(decimal, 16);

    if (temp.length() == 1) {
        temp = "0" + temp;
    }

    return temp.toUpper();
}

bool QUICreator::checkFont(QChar str)
{
    bool exist = false;

    //过滤不存在的图形字体
    QPixmap pix = IconHelper::Instance()->getPixmap("#FF0000", str);
    //对该图片逐个扫描像素点,都是空白则意味着当前图形字体不存在
    QImage img = pix.toImage();
    int width = img.width();
    int height = img.height();

    for (int i = 0; i < height; i++) {
        uchar *lineByte = img.scanLine(i);
        for (int j = 0; j < width; j++) {
            uchar tp = lineByte[j];
            if (tp > 0x00) {
                exist = true;
                break;
            }
        }

        if (exist) {
            break;
        }
    }

    return exist;
}

void QUICreator::on_btnNew_clicked()
{
    QString fileName = ":/qss/psblack.css";

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QFile::ReadOnly)) {
            QString str = file.readAll();
            currentFile = fileName;
            currentQSS = str;
            checkColor(str);
            setStyle(str);
        }
    }
}

void QUICreator::on_btnSave_clicked()
{
    QFile file(currentFile);

    if (file.size() <= 0) {
        return;
    }

    if (file.open(QFile::WriteOnly)) {
        QString str = ui->txtMain->toPlainText();
        str = str.replace("\n", "\r\n");
        file.write(str.toLatin1());
    }
}

void QUICreator::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", qApp->applicationDirPath() + "/qss", "皮肤文件(*.css)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QFile::ReadOnly)) {
            QString str = file.readAll();
            currentFile = fileName;
            currentQSS = str;
            checkColor(str);
            setStyle(str);
        }
    }
}

void QUICreator::on_btnSaveOther_clicked()
{
    //取出当前文件名作为默认文件名
    QFileInfo info(currentFile);
    QString dirName = info.fileName();
    dirName = dirName.split(".").at(0);
    QString fileName = QFileDialog::getSaveFileName(this, "打开文件", QString("%1/%2.css").arg(qApp->applicationDirPath()).arg(dirName), "皮肤文件(*.css)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        //取出另存为文件名
        QFileInfo info(fileName);
        QString dirName = info.fileName();
        dirName = dirName.split(".").at(0);

        //自动生成对应的图片
        newDir(dirName);
        changeDir(dirName);

        //创建四个方向三角形箭头指示器
        createAdd(dirName, "add_top", borderColor);
        createAdd(dirName, "add_right", borderColor);
        createAdd(dirName, "add_bottom", borderColor);
        createAdd(dirName, "add_left", borderColor);

        //创建单选框指示器
        createRadioButton(dirName, "radiobutton_checked", borderColor, panelColor, textColor);
        createRadioButton(dirName, "radiobutton_checked_disable", borderColor, panelColor, textColor);
        createRadioButton(dirName, "radiobutton_unchecked", borderColor, panelColor, textColor);
        createRadioButton(dirName, "radiobutton_unchecked_disable", borderColor, panelColor, textColor);

        //创建复选框指示器
        createCheckBox(dirName, "checkbox_checked", borderColor, panelColor, textColor);
        createCheckBox(dirName, "checkbox_checked_disable", borderColor, panelColor, textColor);
        createCheckBox(dirName, "checkbox_parcial", borderColor, panelColor, textColor);
        createCheckBox(dirName, "checkbox_parcial_disable", borderColor, panelColor, textColor);
        createCheckBox(dirName, "checkbox_unchecked", borderColor, panelColor, textColor);
        createCheckBox(dirName, "checkbox_unchecked_disable", borderColor, panelColor, textColor);

        //创建树状控件伸缩指示器
        createBranch(dirName, "branch_open", textColor);
        createBranch(dirName, "branch_close", textColor);

        //创建月份控件翻页指示器
        createCalendar(dirName, "calendar_prevmonth", textColor);
        createCalendar(dirName, "calendar_nextmonth", textColor);

        //保存当前文本文件
        if (file.open(QFile::WriteOnly)) {
            QString str = ui->txtMain->toPlainText();
            str = str.replace("\n", "\r\n");
            file.write(str.toLatin1());
        }
    }
}

void QUICreator::changeStyle(const QString &qssFile)
{
    QString fileName = qssFile;

    if (!fileName.isEmpty()) {
        QFile file(fileName);

        if (file.open(QFile::ReadOnly)) {
            QString str = file.readAll();
            currentFile = fileName;
            currentQSS = str;
            checkColor(str);
            setStyle(str);
        }
    }
}

void QUICreator::on_tabWidget_currentChanged(int index)
{
    if (index == 1) {
        ui->btnNew->setFocus();
    }
}

void QUICreator::on_btnUIDemo1_clicked()
{
    UIDemo1 w;
    w.exec();
}

void QUICreator::on_btnUIDemo2_clicked()
{
    UIDemo2 w;
    w.exec();
}

void QUICreator::on_btnUIDemo3_clicked()
{
    UIDemo3 w;
    w.exec();
}

void QUICreator::on_btnUIDemo4_clicked()
{
    UIDemo4 w;
    w.exec();
}

void QUICreator::on_btnUIDemo5_clicked()
{
    UIDemo5 w;
    w.exec();
}

void QUICreator::on_btnUIDemo6_clicked()
{
    UIDemo6 w;
    w.exec();
}

void QUICreator::on_btnUIDemo7_clicked()
{
    UIDemo7 w;
    w.exec();
}

void QUICreator::on_btnUIDemo8_clicked()
{
    UIDemo8 w;
    w.exec();
}
