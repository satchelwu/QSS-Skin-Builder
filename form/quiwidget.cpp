#include "quiwidget.h"

int QUIWidget::deskWidth()
{
    return qApp->desktop()->availableGeometry().width();
}

int QUIWidget::deskHeight()
{
    return qApp->desktop()->availableGeometry().height();
}

QString QUIWidget::appName()
{
    QString name = qApp->applicationFilePath();
    QStringList list = name.split("/");
    name = list.at(list.count() - 1).split(".").at(0);
    return name;
}

QString QUIWidget::appPath()
{
#ifdef __arm__
    return "/sdcard/Android/lys";
    //return QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    return qApp->applicationDirPath();
#endif
}

void QUIWidget::newDir(const QString &dirName)
{
    QString strDir = dirName;

    //如果路径中包含斜杠字符则说明是绝对路径
    //linux系统路径字符带有 /  windows系统 路径字符带有 :/
    if (!strDir.startsWith("/") && !strDir.contains(":/")) {
        strDir = QString("%1/%2").arg(QUIWidget::appPath()).arg(strDir);
    }

    QDir dir(strDir);

    if (!dir.exists()) {
        dir.mkpath(strDir);
    }
}

void QUIWidget::writeInfo(const QString &info, const QString &filePath)
{
    QString fileName = QString("%1/%2/%3_runinfo_%4.txt").arg(QUIWidget::appPath())
                       .arg(filePath).arg(QUIWidget::appName()).arg(QDate::currentDate().year());

    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream stream(&file);
    stream << DATETIME << info << NEWLINE;
    file.close();
}

void QUIWidget::setStyle(QUIWidget::Style style)
{
    QString qssFile = ":/qss/blue.css";

    if (style == QUIWidget::Style_Silvery) {
        qssFile = ":/qss/silvery.css";
    } else if (style == QUIWidget::Style_Blue) {
        qssFile = ":/qss/blue.css";
    } else if (style == QUIWidget::Style_LightBlue) {
        qssFile = ":/qss/lightblue.css";
    } else if (style == QUIWidget::Style_DarkBlue) {
        qssFile = ":/qss/darkblue.css";
    } else if (style == QUIWidget::Style_Gray) {
        qssFile = ":/qss/gray.css";
    } else if (style == QUIWidget::Style_LightGray) {
        qssFile = ":/qss/lightgray.css";
    } else if (style == QUIWidget::Style_DarkGray) {
        qssFile = ":/qss/darkgray.css";
    } else if (style == QUIWidget::Style_Black) {
        qssFile = ":/qss/black.css";
    } else if (style == QUIWidget::Style_LightBlack) {
        qssFile = ":/qss/lightblack.css";
    } else if (style == QUIWidget::Style_DarkBlack) {
        qssFile = ":/qss/darkblack.css";
    } else if (style == QUIWidget::Style_PSBlack) {
        qssFile = ":/qss/psblack.css";
    } else if (style == QUIWidget::Style_FlatBlack) {
        qssFile = ":/qss/flatblack.css";
    } else if (style == QUIWidget::Style_FlatWhite) {
        qssFile = ":/qss/flatwhite.css";
    }

    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void QUIWidget::setStyle(const QString &qssFile, QString &paletteColor, QString &textColor)
{
    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        paletteColor = qss.mid(20, 7);
        textColor = qss.mid(49, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void QUIWidget::setStyle(const QString &qssFile, QString &textColor, QString &panelColor, QString &borderColor,
                         QString &normalColorStart, QString &normalColorEnd,
                         QString &darkColorStart, QString &darkColorEnd, QString &highColor)
{
    QFile file(qssFile);

    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        getQssColor(qss, textColor, panelColor, borderColor, normalColorStart, normalColorEnd, darkColorStart, darkColorEnd, highColor);
        qApp->setPalette(QPalette(QColor(panelColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void QUIWidget::getQssColor(const QString &qss, QString &textColor, QString &panelColor, QString &borderColor,
                            QString &normalColorStart, QString &normalColorEnd,
                            QString &darkColorStart, QString &darkColorEnd, QString &highColor)
{
    QString str = qss;

    QString flagTextColor = "TextColor:";
    int indexTextColor = str.indexOf(flagTextColor);

    if (indexTextColor >= 0) {
        textColor = str.mid(indexTextColor + flagTextColor.length(), 7);
    }

    QString flagPanelColor = "PanelColor:";
    int indexPanelColor = str.indexOf(flagPanelColor);

    if (indexPanelColor >= 0) {
        panelColor = str.mid(indexPanelColor + flagPanelColor.length(), 7);
    }

    QString flagBorderColor = "BorderColor:";
    int indexBorderColor = str.indexOf(flagBorderColor);

    if (indexBorderColor >= 0) {
        borderColor = str.mid(indexBorderColor + flagBorderColor.length(), 7);
    }

    QString flagNormalColorStart = "NormalColorStart:";
    int indexNormalColorStart = str.indexOf(flagNormalColorStart);

    if (indexNormalColorStart >= 0) {
        normalColorStart = str.mid(indexNormalColorStart + flagNormalColorStart.length(), 7);
    }

    QString flagNormalColorEnd = "NormalColorEnd:";
    int indexNormalColorEnd = str.indexOf(flagNormalColorEnd);

    if (indexNormalColorEnd >= 0) {
        normalColorEnd = str.mid(indexNormalColorEnd + flagNormalColorEnd.length(), 7);
    }

    QString flagDarkColorStart = "DarkColorStart:";
    int indexDarkColorStart = str.indexOf(flagDarkColorStart);

    if (indexDarkColorStart >= 0) {
        darkColorStart = str.mid(indexDarkColorStart + flagDarkColorStart.length(), 7);
    }

    QString flagDarkColorEnd = "DarkColorEnd:";
    int indexDarkColorEnd = str.indexOf(flagDarkColorEnd);

    if (indexDarkColorEnd >= 0) {
        darkColorEnd = str.mid(indexDarkColorEnd + flagDarkColorEnd.length(), 7);
    }

    QString flagHighColor = "HighColor:";
    int indexHighColor = str.indexOf(flagHighColor);

    if (indexHighColor >= 0) {
        highColor = str.mid(indexHighColor + flagHighColor.length(), 7);
    }
}

void QUIWidget::setFormInCenter(QWidget *frm)
{
    int frmX = frm->width();
    int frmY = frm->height();
    QDesktopWidget w;
    int deskWidth = w.availableGeometry().width();
    int deskHeight = w.availableGeometry().height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    frm->move(movePoint);
}

void QUIWidget::setTranslator(const QString &qmFile)
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(qmFile);
    qApp->installTranslator(translator);
}

void QUIWidget::setCode()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
}

void QUIWidget::sleep(int sec)
{
    QTime dieTime = QTime::currentTime().addMSecs(sec);

    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void QUIWidget::setSystemDateTime(const QString &year, const QString &month, const QString &day, const QString &hour, const QString &min, const QString &sec)
{
#ifdef Q_OS_WIN
    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("date %1-%2-%3\n").arg(year).arg(month).arg(day).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
    p.start("cmd");
    p.waitForStarted();
    p.write(QString("time %1:%2:%3.00\n").arg(hour).arg(min).arg(sec).toLatin1());
    p.closeWriteChannel();
    p.waitForFinished(1000);
    p.close();
#else
    QString cmd = QString("date %1%2%3%4%5.%6").arg(month).arg(day).arg(hour).arg(min).arg(year).arg(sec);
    system(cmd.toLatin1());
    system("hwclock -w");
#endif
}

void QUIWidget::runWithSystem(const QString &strName, const QString &strPath, bool autoRun)
{
#ifdef Q_OS_WIN
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    if (autoRun) {
        reg.setValue(strName, strPath);
    } else {
        reg.setValue(strName, "");
    }
#endif
}

bool QUIWidget::isIP(const QString &ip)
{
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(ip);
}

bool QUIWidget::isMac(const QString &mac)
{
    QRegExp RegExp("^[A-F0-9]{2}(-[A-F0-9]{2}){5}$");
    return RegExp.exactMatch(mac);
}

bool QUIWidget::isTel(const QString &tel)
{
    if (tel.length() != 11) {
        return false;
    }

    if (!tel.startsWith("13") && !tel.startsWith("14") && !tel.startsWith("15") && !tel.startsWith("18")) {
        return false;
    }

    return true;
}

bool QUIWidget::isEmail(const QString &email)
{
    if (!email.contains("@") || !email.contains(".com")) {
        return false;
    }

    return true;
}

int QUIWidget::strHexToDecimal(const QString &strHex)
{
    bool ok;
    return strHex.toInt(&ok, 16);
}

int QUIWidget::strDecimalToDecimal(const QString &strDecimal)
{
    bool ok;
    return strDecimal.toInt(&ok, 10);
}

int QUIWidget::strBinToDecimal(const QString &strBin)
{
    bool ok;
    return strBin.toInt(&ok, 2);
}

QString QUIWidget::strHexToStrBin(const QString &strHex)
{
    uchar decimal = strHexToDecimal(strHex);
    QString bin = QString::number(decimal, 2);
    uchar len = bin.length();

    if (len < 8) {
        for (int i = 0; i < 8 - len; i++) {
            bin = "0" + bin;
        }
    }

    return bin;
}

QString QUIWidget::decimalToStrBin1(int decimal)
{
    QString bin = QString::number(decimal, 2);
    uchar len = bin.length();

    if (len <= 8) {
        for (int i = 0; i < 8 - len; i++) {
            bin = "0" + bin;
        }
    }

    return bin;
}

QString QUIWidget::decimalToStrBin2(int decimal)
{
    QString bin = QString::number(decimal, 2);
    uchar len = bin.length();

    if (len <= 16) {
        for (int i = 0; i < 16 - len; i++) {
            bin = "0" + bin;
        }
    }

    return bin;
}

QString QUIWidget::decimalToStrHex(int decimal)
{
    QString temp = QString::number(decimal, 16);

    if (temp.length() == 1) {
        temp = "0" + temp;
    }

    return temp;
}

QByteArray QUIWidget::intToByte(int i)
{
    QByteArray result;
    result.resize(4);
    result[3] = (uchar)(0x000000ff & i);
    result[2] = (uchar)((0x0000ff00 & i) >> 8);
    result[1] = (uchar)((0x00ff0000 & i) >> 16);
    result[0] = (uchar)((0xff000000 & i) >> 24);
    return result;
}

int QUIWidget::byteToInt(const QByteArray &data)
{
    int i = data.at(3) & 0x000000FF;
    i |= ((data.at(2) << 8) & 0x0000FF00);
    i |= ((data.at(1) << 16) & 0x00FF0000);
    i |= ((data.at(0) << 24) & 0xFF000000);
    return i;
}

QByteArray QUIWidget::ushortToByte(ushort i)
{
    QByteArray result;
    result.resize(2);
    result[1] = (uchar)(0x000000ff & i);
    result[0] = (uchar)((0x0000ff00 & i) >> 8);
    return result;
}

int QUIWidget::byteToUShort(const QByteArray &data)
{
    int i = data.at(1) & 0x000000FF;
    i |= ((data.at(0) << 8) & 0x0000FF00);
    return i;
}

QString QUIWidget::getXorEncryptDecrypt(const QString &str, char key)
{
    QByteArray data = str.toLatin1();
    int size = data.size();

    for (int i = 0; i < size; i++) {
        data[i] = data.at(i) ^ key;
    }

    return QLatin1String(data);
}

uchar QUIWidget::getOrCode(const QByteArray &data)
{
    int len = data.length();
    uchar result = 0;

    for (int i = 0; i < len; i++) {
        result ^= data.at(i);
    }

    return result;
}

uchar QUIWidget::getCheckCode(const QByteArray &data)
{
    int len = data.length();
    uchar temp = 0;

    for (uchar i = 0; i < len; i++) {
        temp += data.at(i);
    }

    return temp % 256;
}

QString QUIWidget::byteArrayToAsciiStr(const QByteArray &data)
{
    QString temp;
    int len = data.size();

    for (int i = 0; i < len; i++) {
        //0x20为空格,空格以下都是不可见字符
        char b = data.at(i);

        if (0x00 == b) {
            temp += QString("\\NUL");
        } else if (0x01 == b) {
            temp += QString("\\SOH");
        } else if (0x02 == b) {
            temp += QString("\\STX");
        } else if (0x03 == b) {
            temp += QString("\\ETX");
        } else if (0x04 == b) {
            temp += QString("\\EOT");
        } else if (0x05 == b) {
            temp += QString("\\ENQ");
        } else if (0x06 == b) {
            temp += QString("\\ACK");
        } else if (0x07 == b) {
            temp += QString("\\BEL");
        } else if (0x08 == b) {
            temp += QString("\\BS");
        } else if (0x09 == b) {
            temp += QString("\\HT");
        } else if (0x0A == b) {
            temp += QString("\\LF");
        } else if (0x0B == b) {
            temp += QString("\\VT");
        } else if (0x0C == b) {
            temp += QString("\\FF");
        } else if (0x0D == b) {
            temp += QString("\\CR");
        } else if (0x0E == b) {
            temp += QString("\\SO");
        } else if (0x0F == b) {
            temp += QString("\\SI");
        } else if (0x10 == b) {
            temp += QString("\\DLE");
        } else if (0x11 == b) {
            temp += QString("\\DC1");
        } else if (0x12 == b) {
            temp += QString("\\DC2");
        } else if (0x13 == b) {
            temp += QString("\\DC3");
        } else if (0x14 == b) {
            temp += QString("\\DC4");
        } else if (0x15 == b) {
            temp += QString("\\NAK");
        } else if (0x16 == b) {
            temp += QString("\\SYN");
        } else if (0x17 == b) {
            temp += QString("\\ETB");
        } else if (0x18 == b) {
            temp += QString("\\CAN");
        } else if (0x19 == b) {
            temp += QString("\\EM");
        } else if (0x1A == b) {
            temp += QString("\\SUB");
        } else if (0x1B == b) {
            temp += QString("\\ESC");
        } else if (0x1C == b) {
            temp += QString("\\FS");
        } else if (0x1D == b) {
            temp += QString("\\GS");
        } else if (0x1E == b) {
            temp += QString("\\RS");
        } else if (0x1F == b) {
            temp += QString("\\US");
        } else if (0x7F == b) {
            temp += QString("\\x7F");
        } else if (0x5C == b) {
            temp += QString("\\x5C");
        } else if (0x20 >= b) {
            temp += QString("\\x%1").arg(decimalToStrHex((quint8)b));
        } else {
            temp += QString("%1").arg(b);
        }
    }

    return temp.trimmed();
}

QByteArray QUIWidget::hexStrToByteArray(const QString &str)
{
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len / 2);
    char lstr, hstr;

    for (int i = 0; i < len;) {
        hstr = str.at(i).toLatin1();

        if (hstr == ' ') {
            i++;
            continue;
        }

        i++;

        if (i >= len) {
            break;
        }

        lstr = str.at(i).toLatin1();
        hexdata = convertHexChar(hstr);
        lowhexdata = convertHexChar(lstr);

        if ((hexdata == 16) || (lowhexdata == 16)) {
            break;
        } else {
            hexdata = hexdata * 16 + lowhexdata;
        }

        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }

    senddata.resize(hexdatalen);
    return senddata;
}

char QUIWidget::convertHexChar(char ch)
{
    if ((ch >= '0') && (ch <= '9')) {
        return ch - 0x30;
    } else if ((ch >= 'A') && (ch <= 'F')) {
        return ch - 'A' + 10;
    } else if ((ch >= 'a') && (ch <= 'f')) {
        return ch - 'a' + 10;
    } else {
        return (-1);
    }
}

QByteArray QUIWidget::asciiStrToByteArray(const QString &str)
{
    QByteArray buffer;
    int len = str.length();
    QString letter;
    QString hex;

    for (int i = 0; i < len; i++) {
        letter = str.at(i);

        if (letter == "\\") {
            i++;
            letter = str.mid(i, 1);

            if (letter == "x") {
                i++;
                hex = str.mid(i, 2);
                buffer.append(strHexToDecimal(hex));
                i++;
                continue;
            } else if (letter == "N") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "L") {           //NUL=0x00
                        buffer.append((char)0x00);
                        continue;
                    }
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "K") {           //NAK=0x15
                        buffer.append(0x15);
                        continue;
                    }
                }
            } else if (letter == "S") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "H") {           //SOH=0x01
                        buffer.append(0x01);
                        continue;
                    } else {                    //SO=0x0E
                        buffer.append(0x0E);
                        i--;
                        continue;
                    }
                } else if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "X") {           //STX=0x02
                        buffer.append(0x02);
                        continue;
                    }
                } else if (hex == "I") {        //SI=0x0F
                    buffer.append(0x0F);
                    continue;
                } else if (hex == "Y") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "N") {           //SYN=0x16
                        buffer.append(0x16);
                        continue;
                    }
                } else if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "B") {           //SUB=0x1A
                        buffer.append(0x1A);
                        continue;
                    }
                }
            } else if (letter == "E") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "X") {           //ETX=0x03
                        buffer.append(0x03);
                        continue;
                    } else if (hex == "B") {    //ETB=0x17
                        buffer.append(0x17);
                        continue;
                    }
                } else if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "T") {           //EOT=0x04
                        buffer.append(0x04);
                        continue;
                    }
                } else if (hex == "N") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "Q") {           //ENQ=0x05
                        buffer.append(0x05);
                        continue;
                    }
                } else if (hex == "M") {        //EM=0x19
                    buffer.append(0x19);
                    continue;
                } else if (hex == "S") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "C") {           //ESC=0x1B
                        buffer.append(0x1B);
                        continue;
                    }
                }
            } else if (letter == "A") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "K") {           //ACK=0x06
                        buffer.append(0x06);
                        continue;
                    }
                }
            } else if (letter == "B") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "E") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "L") {           //BEL=0x07
                        buffer.append(0x07);
                        continue;
                    }
                } else if (hex == "S") {        //BS=0x08
                    buffer.append(0x08);
                    continue;
                }
            } else if (letter == "C") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "R") {               //CR=0x0D
                    buffer.append(0x0D);
                    continue;
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "N") {           //CAN=0x18
                        buffer.append(0x18);
                        continue;
                    }
                }
            } else if (letter == "D") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "L") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "E") {           //DLE=0x10
                        buffer.append(0x10);
                        continue;
                    }
                } else if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "1") {           //DC1=0x11
                        buffer.append(0x11);
                        continue;
                    } else if (hex == "2") {    //DC2=0x12
                        buffer.append(0x12);
                        continue;
                    } else if (hex == "3") {    //DC3=0x13
                        buffer.append(0x13);
                        continue;
                    } else if (hex == "4") {    //DC2=0x14
                        buffer.append(0x14);
                        continue;
                    }
                }
            } else if (letter == "F") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "F") {               //FF=0x0C
                    buffer.append(0x0C);
                    continue;
                } else if (hex == "S") {        //FS=0x1C
                    buffer.append(0x1C);
                    continue;
                }
            } else if (letter == "H") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {               //HT=0x09
                    buffer.append(0x09);
                    continue;
                }
            } else if (letter == "L") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "F") {               //LF=0x0A
                    buffer.append(0x0A);
                    continue;
                }
            } else if (letter == "G") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //GS=0x1D
                    buffer.append(0x1D);
                    continue;
                }
            } else if (letter == "R") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //RS=0x1E
                    buffer.append(0x1E);
                    continue;
                }
            } else if (letter == "U") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //US=0x1F
                    buffer.append(0x1F);
                    continue;
                }
            } else if (letter == "V") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {               //VT=0x0B
                    buffer.append(0x0B);
                    continue;
                }
            } else if (letter == "\\") {
                //如果连着的是多个\\则对应添加\对应的16进制0x5C
                buffer.append(0x5C);
                continue;
            } else {
                //将对应的\[前面的\\也要加入
                buffer.append(0x5C);
                buffer.append(letter.toLatin1());
                continue;
            }
        }

        buffer.append(str.mid(i, 1).toLatin1());

    }

    return buffer;
}

QString QUIWidget::byteArrayToHexStr(const QByteArray &data)
{
    QString temp = "";
    QString hex = data.toHex();

    for (int i = 0; i < hex.length(); i = i + 2) {
        temp += hex.mid(i, 2) + " ";
    }

    return temp.trimmed().toUpper();
}

QString QUIWidget::getFileName(const QString &filter, QString defaultDir)
{
    return QFileDialog::getOpenFileName(0, "选择文件", defaultDir , filter);
}

QStringList QUIWidget::getFileNames(const QString &filter, QString defaultDir)
{
    return QFileDialog::getOpenFileNames(0, "选择文件", defaultDir, filter);
}

QString QUIWidget::getFolderName()
{
    return QFileDialog::getExistingDirectory();;
}

QString QUIWidget::getFileNameWithExtension(const QString &strFilePath)
{
    QFileInfo fileInfo(strFilePath);
    return fileInfo.fileName();
}

QStringList QUIWidget::getFolderFileNames(const QStringList &filter)
{
    QStringList fileList;
    QString strFolder = QFileDialog::getExistingDirectory();

    if (!strFolder.length() == 0) {
        QDir myFolder(strFolder);

        if (myFolder.exists()) {
            fileList = myFolder.entryList(filter);
        }
    }

    return fileList;
}

bool QUIWidget::folderIsExist(const QString &strFolder)
{
    QDir tempFolder(strFolder);
    return tempFolder.exists();
}

bool QUIWidget::fileIsExist(const QString &strFile)
{
    QFile tempFile(strFile);
    return tempFile.exists();
}

bool QUIWidget::copyFile(const QString &sourceFile, const QString &targetFile)
{
    bool ok;
    ok = QFile::copy(sourceFile, targetFile);
    //将复制过去的文件只读属性取消
    ok = QFile::setPermissions(targetFile, QFile::WriteOwner);
    return ok;
}

void QUIWidget::deleteDirectory(const QString &path)
{
    QDir dir(path);

    if (!dir.exists()) {
        return;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();

    foreach (QFileInfo fi, fileList) {
        if (fi.isFile()) {
            fi.dir().remove(fi.fileName());
        } else {
            deleteDirectory(fi.absoluteFilePath());
            dir.rmdir(fi.absoluteFilePath());
        }
    }
}

bool QUIWidget::ipLive(const QString &ip, int port, int timeout)
{
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(ip, port);
    //超时没有连接上则判断不在线
    return tcpClient.waitForConnected(timeout);
}

QString QUIWidget::getHtml(const QString &url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    responseData = reply->readAll();
    return QString(responseData);
}

QString QUIWidget::getNetIP(const QString &webCode)
{
    QString web = webCode;
    web = web.replace(' ', "");
    web = web.replace("\r", "");
    web = web.replace("\n", "");
    QStringList list = web.split("<br/>");
    QString tar = list.at(3);
    QStringList ip = tar.split("=");
    return ip.at(1);
}

QString QUIWidget::getLocalIP()
{
    QString ip;
    QList<QHostAddress> addrs = QNetworkInterface::allAddresses();

    foreach (QHostAddress addr, addrs) {
        ip = addr.toString();

        if (ip != "127.0.0.1") {
            break;
        }
    }

    return ip;
}

QString QUIWidget::urlToIP(const QString &url)
{
    QHostInfo host = QHostInfo::fromName(url);
    return host.addresses().at(0).toString();
}

bool QUIWidget::isWebOk()
{
    //能接通百度IP说明可以通外网
    return ipLive("115.239.211.112", 80);
}

void QUIWidget::showMessageBoxInfo(const QString &info, int closeSec)
{
    QUIMessageBox::Instance()->setMessage(info, 0, closeSec);
    QUIMessageBox::Instance()->show();
}

void QUIWidget::showMessageBoxError(const QString &info, int closeSec)
{
    QUIMessageBox::Instance()->setMessage(info, 2, closeSec);
    QUIMessageBox::Instance()->show();
}

int QUIWidget::showMessageBoxQuestion(const QString &info)
{
    QUIMessageBox msg;
    msg.setMessage(info, 1);
    return msg.exec();
}

QString QUIWidget::showInputBox(bool &ok, const QString &title, int type, int closeSec,
                                QString defaultValue, bool pwd)
{
    QUIInputBox input;
    input.setParameter(title, type, closeSec, defaultValue, pwd);
    ok = input.exec();
    return input.getValue();
}


QUIWidget::QUIWidget(QWidget *parent) : QDialog(parent)
{
    this->initControl();
    this->initForm();
}

QUIWidget::~QUIWidget()
{
    delete widgetMain;
}

bool QUIWidget::eventFilter(QObject *obj, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (!max && mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonDblClick) {
        //以下写法可以将双击识别限定在标题栏
        //if (this->btnMenu_Max->isVisible() && obj == this->widgetTitle) {
        if (this->btnMenu_Max->isVisible()) {
            this->on_btnMenu_Max_clicked();
            return true;
        }
    }

    return QWidget::eventFilter(obj, evt);
}

QLabel *QUIWidget::getLabIco() const
{
    return this->labIco;
}

QLabel *QUIWidget::getLabTitle() const
{
    return this->labTitle;
}

QToolButton *QUIWidget::getBtnMenu() const
{
    return this->btnMenu;
}

QPushButton *QUIWidget::getBtnMenuMin() const
{
    return this->btnMenu_Min;
}

QPushButton *QUIWidget::getBtnMenuMax() const
{
    return this->btnMenu_Max;
}

QPushButton *QUIWidget::getBtnMenuMClose() const
{
    return this->btnMenu_Close;
}

QString QUIWidget::getTitle() const
{
    return this->title;
}

Qt::Alignment QUIWidget::getAlignment() const
{
    return this->alignment;
}

QSize QUIWidget::sizeHint() const
{
    return QSize(600, 450);
}

QSize QUIWidget::minimumSizeHint() const
{
    return QSize(200, 150);
}

void QUIWidget::initControl()
{
    this->setObjectName(QString::fromUtf8("QUIWidget"));
    this->resize(900, 750);
    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setContentsMargins(11, 11, 11, 11);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
    widgetMain->setStyleSheet(QString::fromUtf8(""));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(0);
    verticalLayout2->setContentsMargins(11, 11, 11, 11);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(0, 0, 0, 0);
    widgetTitle = new QWidget(widgetMain);
    widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
    widgetTitle->setSizePolicy(sizePolicy);
    widgetTitle->setMinimumSize(QSize(0, 30));
    horizontalLayout4 = new QHBoxLayout(widgetTitle);
    horizontalLayout4->setSpacing(0);
    horizontalLayout4->setContentsMargins(11, 11, 11, 11);
    horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
    horizontalLayout4->setContentsMargins(0, 0, 0, 0);
    labIco = new QLabel(widgetTitle);
    labIco->setObjectName(QString::fromUtf8("labIco"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labIco->sizePolicy().hasHeightForWidth());
    labIco->setSizePolicy(sizePolicy1);
    labIco->setMinimumSize(QSize(30, 0));
    labIco->setAlignment(Qt::AlignCenter);

    horizontalLayout4->addWidget(labIco);

    labTitle = new QLabel(widgetTitle);
    labTitle->setObjectName(QString::fromUtf8("labTitle"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labTitle->sizePolicy().hasHeightForWidth());
    labTitle->setSizePolicy(sizePolicy2);
    labTitle->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    horizontalLayout4->addWidget(labTitle);

    widgetMenu = new QWidget(widgetTitle);
    widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
    sizePolicy1.setHeightForWidth(widgetMenu->sizePolicy().hasHeightForWidth());
    widgetMenu->setSizePolicy(sizePolicy1);
    horizontalLayout = new QHBoxLayout(widgetMenu);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    btnMenu = new QToolButton(widgetMenu);
    btnMenu->setObjectName(QString::fromUtf8("btnMenu"));
    QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu->sizePolicy().hasHeightForWidth());
    btnMenu->setSizePolicy(sizePolicy3);
    btnMenu->setMinimumSize(QSize(30, 0));
    btnMenu->setMaximumSize(QSize(30, 16777215));
    btnMenu->setFocusPolicy(Qt::NoFocus);
    btnMenu->setPopupMode(QToolButton::InstantPopup);

    horizontalLayout->addWidget(btnMenu);

    btnMenu_Min = new QPushButton(widgetMenu);
    btnMenu_Min->setObjectName(QString::fromUtf8("btnMenu_Min"));
    QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(btnMenu_Min->sizePolicy().hasHeightForWidth());
    btnMenu_Min->setSizePolicy(sizePolicy4);
    btnMenu_Min->setMinimumSize(QSize(30, 0));
    btnMenu_Min->setMaximumSize(QSize(30, 16777215));
    btnMenu_Min->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Min->setFocusPolicy(Qt::NoFocus);

    horizontalLayout->addWidget(btnMenu_Min);

    btnMenu_Max = new QPushButton(widgetMenu);
    btnMenu_Max->setObjectName(QString::fromUtf8("btnMenu_Max"));
    sizePolicy3.setHeightForWidth(btnMenu_Max->sizePolicy().hasHeightForWidth());
    btnMenu_Max->setSizePolicy(sizePolicy3);
    btnMenu_Max->setMinimumSize(QSize(30, 0));
    btnMenu_Max->setMaximumSize(QSize(30, 16777215));
    btnMenu_Max->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Max->setFocusPolicy(Qt::NoFocus);

    horizontalLayout->addWidget(btnMenu_Max);

    btnMenu_Close = new QPushButton(widgetMenu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(30, 0));
    btnMenu_Close->setMaximumSize(QSize(30, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);

    horizontalLayout->addWidget(btnMenu_Close);
    horizontalLayout4->addWidget(widgetMenu);
    verticalLayout2->addWidget(widgetTitle);

    widget = new QWidget(widgetMain);
    widget->setObjectName(QString::fromUtf8("widget"));
    verticalLayout3 = new QVBoxLayout(widget);
    verticalLayout3->setSpacing(0);
    verticalLayout3->setContentsMargins(11, 11, 11, 11);
    verticalLayout3->setObjectName(QString::fromUtf8("verticalLayout3"));
    verticalLayout3->setContentsMargins(0, 0, 0, 0);

    verticalLayout2->addWidget(widget);
    verticalLayout1->addWidget(widgetMain);

    connect(this->btnMenu_Min, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Min_clicked()));
    connect(this->btnMenu_Max, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Max_clicked()));
    connect(this->btnMenu_Close, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIWidget::initForm()
{
    //设置图形字体
    setIcon(QUIWidget::Lab_Ico, QUIConfig::IconMain, 11);
    setIcon(QUIWidget::BtnMenu, QUIConfig::IconMenu);
    setIcon(QUIWidget::BtnMenu_Min, QUIConfig::IconMin);
    setIcon(QUIWidget::BtnMenu_Normal, QUIConfig::IconNormal);
    setIcon(QUIWidget::BtnMenu_Close, QUIConfig::IconClose);

    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->widgetTitle->setProperty("form", "title");
    this->setWindowFlags((Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint));

    //设置标题及对齐方式
    title = "QUI Demo";
    alignment = Qt::AlignLeft | Qt::AlignVCenter;
    minHide = false;
    mainWidget = 0;

    setVisible(QUIWidget::BtnMenu, false);

    //绑定事件过滤器监听鼠标移动
    this->installEventFilter(this);
    this->widgetTitle->installEventFilter(this);

    //添加换肤菜单
    QStringList name;
    name << "银色" << "蓝色" << "浅蓝色" << "深蓝色" << "灰色" << "浅灰色" << "深灰色" << "黑色"
         << "浅黑色" << "深黑色" << "PS黑色" << "黑色扁平" << "白色扁平";

    foreach (QString str, name) {
        QAction *action = new QAction(str, this);
        this->btnMenu->addAction(action);
        connect(action, SIGNAL(triggered(bool)), this, SLOT(changeStyle()));
    }
}

void QUIWidget::changeStyle()
{
    QAction *act = (QAction *)sender();
    QString name = act->text();
    QString qssFile = ":/qss/blue.css";

    if (name == "银色") {
        qssFile = ":/qss/silvery.css";
        setStyle(QUIWidget::Style_Silvery);
    } else if (name == "蓝色") {
        qssFile = ":/qss/blue.css";
        setStyle(QUIWidget::Style_Blue);
    } else if (name == "浅蓝色") {
        qssFile = ":/qss/lightblue.css";
        setStyle(QUIWidget::Style_LightBlue);
    } else if (name == "深蓝色") {
        qssFile = ":/qss/darkblue.css";
        setStyle(QUIWidget::Style_DarkBlue);
    } else if (name == "灰色") {
        qssFile = ":/qss/gray.css";
        setStyle(QUIWidget::Style_Gray);
    } else if (name == "浅灰色") {
        qssFile = ":/qss/lightgray.css";
        setStyle(QUIWidget::Style_LightGray);
    } else if (name == "深灰色") {
        qssFile = ":/qss/darkgray.css";
        setStyle(QUIWidget::Style_DarkGray);
    } else if (name == "黑色") {
        qssFile = ":/qss/black.css";
        setStyle(QUIWidget::Style_Black);
    } else if (name == "浅黑色") {
        qssFile = ":/qss/lightblack.css";
        setStyle(QUIWidget::Style_LightBlack);
    } else if (name == "深黑色") {
        qssFile = ":/qss/darkblack.css";
        setStyle(QUIWidget::Style_DarkBlack);
    } else if (name == "PS黑色") {
        qssFile = ":/qss/psblack.css";
        setStyle(QUIWidget::Style_PSBlack);
    } else if (name == "黑色扁平") {
        qssFile = ":/qss/flatblack.css";
        setStyle(QUIWidget::Style_FlatBlack);
    } else if (name == "白色扁平") {
        qssFile = ":/qss/flatwhite.css";
        setStyle(QUIWidget::Style_FlatWhite);
    }

    emit changeStyle(qssFile);
}

void QUIWidget::setIcon(QUIWidget::Widget widget, QChar str, quint32 size)
{
    if (widget == QUIWidget::Lab_Ico) {
        setIconMain(str, size);
    } else if (widget == QUIWidget::BtnMenu) {
        QUIConfig::IconMenu = str;
        IconHelper::Instance()->setIcon(this->btnMenu, str, size);
    } else if (widget == QUIWidget::BtnMenu_Min) {
        QUIConfig::IconMin = str;
        IconHelper::Instance()->setIcon(this->btnMenu_Min, str, size);
    } else if (widget == QUIWidget::BtnMenu_Max) {
        QUIConfig::IconMax = str;
        IconHelper::Instance()->setIcon(this->btnMenu_Max, str, size);
    } else if (widget == QUIWidget::BtnMenu_Normal) {
        QUIConfig::IconNormal = str;
        IconHelper::Instance()->setIcon(this->btnMenu_Max, str, size);
    } else if (widget == QUIWidget::BtnMenu_Close) {
        QUIConfig::IconClose = str;
        IconHelper::Instance()->setIcon(this->btnMenu_Close, str, size);
    }
}

void QUIWidget::setIconMain(QChar str, quint32 size)
{
    QUIConfig::IconMain = str;
    IconHelper::Instance()->setIcon(this->labIco, str, size);
    QUIMessageBox::Instance()->setIconMain(str, size);
    QUIInputBox::Instance()->setIconMain(str, size);
}

void QUIWidget::setPixmap(QUIWidget::Widget widget, const QString &file, const QSize &size)
{
    QPixmap pix = QPixmap(file);
    //按照宽高比自动缩放
    pix = pix.scaled(size, Qt::KeepAspectRatio);

    if (widget == QUIWidget::Lab_Ico) {
        this->labIco->setPixmap(pix);
    } else if (widget == QUIWidget::BtnMenu) {
        this->btnMenu->setIcon(QIcon(file));
    } else if (widget == QUIWidget::BtnMenu_Min) {
        this->btnMenu_Min->setIcon(QIcon(file));
    } else if (widget == QUIWidget::BtnMenu_Max) {
        this->btnMenu_Max->setIcon(QIcon(file));
    } else if (widget == QUIWidget::BtnMenu_Close) {
        this->btnMenu_Close->setIcon(QIcon(file));
    }
}

void QUIWidget::setVisible(QUIWidget::Widget widget, bool visible)
{
    if (widget == QUIWidget::Lab_Ico) {
        this->labIco->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu) {
        this->btnMenu->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu_Min) {
        this->btnMenu_Min->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu_Max) {
        this->btnMenu_Max->setVisible(visible);
    } else if (widget == QUIWidget::BtnMenu_Close) {
        this->btnMenu_Close->setVisible(visible);
    }
}

void QUIWidget::setOnlyCloseBtn()
{
    this->btnMenu->setVisible(false);
    this->btnMenu_Min->setVisible(false);
    this->btnMenu_Max->setVisible(false);
}

void QUIWidget::setTitleHeight(int height)
{
    this->widgetTitle->setFixedHeight(height);
}

void QUIWidget::setBtnWidth(int width)
{
    this->labIco->setFixedWidth(width);
    this->btnMenu->setFixedWidth(width);
    this->btnMenu_Min->setFixedWidth(width);
    this->btnMenu_Max->setFixedWidth(width);
    this->btnMenu_Close->setFixedWidth(width);
}

void QUIWidget::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        this->labTitle->setText(title);
        this->setWindowTitle(this->labTitle->text());
    }
}

void QUIWidget::setAlignment(Qt::Alignment alignment)
{
    if (this->alignment != alignment) {
        this->alignment = alignment;
        this->labTitle->setAlignment(alignment);
    }
}

void QUIWidget::setMinHide(bool minHide)
{
    if (this->minHide != minHide) {
        this->minHide = minHide;
    }
}

void QUIWidget::setMainWidget(QWidget *mainWidget)
{
    //一个QUI窗体对象只能设置一个主窗体
    if (this->mainWidget == 0) {
        //将子窗体添加到布局
        this->widget->layout()->addWidget(mainWidget);
        //自动设置大小
        resize(mainWidget->width(), mainWidget->height() + this->widgetTitle->height());

        this->mainWidget = mainWidget;
    }
}

void QUIWidget::on_btnMenu_Min_clicked()
{
    if (minHide) {
        hide();
    } else {
        showMinimized();
    }
}

void QUIWidget::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        setIcon(QUIWidget::BtnMenu_Normal, QUIConfig::IconNormal);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        setIcon(QUIWidget::BtnMenu_Max, QUIConfig::IconMax);
    }

    max = !max;
}

void QUIWidget::on_btnMenu_Close_clicked()
{
    emit closing();
    exit(0);
}



QUIMessageBox *QUIMessageBox::self = 0;
QUIMessageBox::QUIMessageBox(QWidget *parent) : QDialog(parent)
{
    this->initControl();
    this->initForm();
}

QUIMessageBox::~QUIMessageBox()
{
    delete widgetMain;
}

void QUIMessageBox::initControl()
{
    this->setObjectName(QString::fromUtf8("QUIMessageBox"));

#ifdef __arm__
    this->resize(300, 160);
#else
    this->resize(280, 150);
#endif

    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
    widgetTitle->setSizePolicy(sizePolicy);
    widgetTitle->setMinimumSize(QSize(0, 30));
    horizontalLayout3 = new QHBoxLayout(widgetTitle);
    horizontalLayout3->setSpacing(0);
    horizontalLayout3->setObjectName(QString::fromUtf8("horizontalLayout3"));
    horizontalLayout3->setContentsMargins(0, 0, 0, 0);
    labIco = new QLabel(widgetTitle);
    labIco->setObjectName(QString::fromUtf8("labIco"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labIco->sizePolicy().hasHeightForWidth());
    labIco->setSizePolicy(sizePolicy1);
    labIco->setMinimumSize(QSize(30, 0));
    labIco->setAlignment(Qt::AlignCenter);

    horizontalLayout3->addWidget(labIco);

    labTitle = new QLabel(widgetTitle);
    labTitle->setObjectName(QString::fromUtf8("labTitle"));
    labTitle->setStyleSheet(QString::fromUtf8(""));
    labTitle->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    horizontalLayout3->addWidget(labTitle);

    labTime = new QLabel(widgetTitle);
    labTime->setObjectName(QString::fromUtf8("labTime"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labTime->sizePolicy().hasHeightForWidth());
    labTime->setSizePolicy(sizePolicy2);
    labTime->setAlignment(Qt::AlignCenter);

    horizontalLayout3->addWidget(labTime);

    widgetMenu = new QWidget(widgetTitle);
    widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
    sizePolicy1.setHeightForWidth(widgetMenu->sizePolicy().hasHeightForWidth());
    widgetMenu->setSizePolicy(sizePolicy1);
    horizontalLayout4 = new QHBoxLayout(widgetMenu);
    horizontalLayout4->setSpacing(0);
    horizontalLayout4->setObjectName(QString::fromUtf8("horizontalLayout4"));
    horizontalLayout4->setContentsMargins(0, 0, 0, 0);
    btnMenu_Close = new QPushButton(widgetMenu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(30, 0));
    btnMenu_Close->setMaximumSize(QSize(30, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);
    btnMenu_Close->setFlat(true);

    horizontalLayout4->addWidget(btnMenu_Close);
    horizontalLayout3->addWidget(widgetMenu);
    verticalLayout1->addWidget(widgetTitle);

    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
    widgetMain->setStyleSheet(QString::fromUtf8(""));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(5);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(5, 5, 5, 5);
    frame = new QFrame(widgetMain);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    verticalLayout4 = new QVBoxLayout(frame);
    verticalLayout4->setObjectName(QString::fromUtf8("verticalLayout4"));
    verticalLayout4->setContentsMargins(-1, 9, -1, -1);
    horizontalLayout1 = new QHBoxLayout();
    horizontalLayout1->setObjectName(QString::fromUtf8("horizontalLayout1"));
    labIcoMain = new QLabel(frame);
    labIcoMain->setObjectName(QString::fromUtf8("labIcoMain"));
    labIcoMain->setMinimumSize(QSize(30, 30));
    labIcoMain->setMaximumSize(QSize(30, 30));
    labIcoMain->setStyleSheet(QString::fromUtf8("border-image: url(:/image/msg_info.png);"));

    horizontalLayout1->addWidget(labIcoMain);

    horizontalSpacer1 = new QSpacerItem(5, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);

    horizontalLayout1->addItem(horizontalSpacer1);

    labInfo = new QLabel(frame);
    labInfo->setObjectName(QString::fromUtf8("labInfo"));
    QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(labInfo->sizePolicy().hasHeightForWidth());
    labInfo->setSizePolicy(sizePolicy4);
    labInfo->setMinimumSize(QSize(0, 33));
    labInfo->setScaledContents(false);
    labInfo->setWordWrap(true);

    horizontalLayout1->addWidget(labInfo);


    verticalLayout4->addLayout(horizontalLayout1);

    horizontalLayout2 = new QHBoxLayout();
    horizontalLayout2->setObjectName(QString::fromUtf8("horizontalLayout2"));
    horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout2->addItem(horizontalSpacer2);

    btnOk = new QPushButton(frame);
    btnOk->setObjectName(QString::fromUtf8("btnOk"));
    btnOk->setMinimumSize(QSize(80, 0));
    btnOk->setFocusPolicy(Qt::StrongFocus);
    btnOk->setStyleSheet(QString::fromUtf8(""));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/image/btn_ok.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnOk->setIcon(icon);

    horizontalLayout2->addWidget(btnOk);

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setMinimumSize(QSize(80, 0));
    btnCancel->setFocusPolicy(Qt::StrongFocus);
    btnCancel->setStyleSheet(QString::fromUtf8(""));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/image/btn_close.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnCancel->setIcon(icon1);

    horizontalLayout2->addWidget(btnCancel);
    verticalLayout4->addLayout(horizontalLayout2);
    verticalLayout2->addWidget(frame);
    verticalLayout1->addWidget(widgetMain);

    widgetTitle->raise();
    widgetMain->raise();
    frame->raise();

    this->btnOk->setText("确定");
    this->btnCancel->setText("取消");

    connect(this->btnOk, SIGNAL(clicked()), this, SLOT(on_btnOk_clicked()));
    connect(this->btnMenu_Close, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Close_clicked()));
    connect(this->btnCancel, SIGNAL(clicked()), this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIMessageBox::initForm()
{
    IconHelper::Instance()->setIcon(labIco, QUIConfig::IconMain, QUIConfig::FontSize + 2);
    IconHelper::Instance()->setIcon(btnMenu_Close, QUIConfig::IconClose, QUIConfig::FontSize);

    this->setProperty("form", true);
    this->widgetTitle->setProperty("form", "title");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(280, 150);
    this->setWindowTitle(this->labTitle->text());

    int width = 80;
    int iconWidth = 18;
    int iconHeight = 18;
    this->labIcoMain->setFixedSize(30, 30);

    QList<QPushButton *> btns1 = this->frame->findChildren<QPushButton *>();

    foreach (QPushButton *btn, btns1) {
        btn->setMinimumWidth(width);
        btn->setIconSize(QSize(iconWidth, iconHeight));
    }

    closeSec = 0;
    currentSec = 0;

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    timer->start();

    this->installEventFilter(this);
}

void QUIMessageBox::checkSec()
{
    if (closeSec == 0) {
        return;
    }

    if (currentSec < closeSec) {
        currentSec++;
    } else {
        this->close();
    }

    QString str = QString("关闭倒计时 %1 s").arg(closeSec - currentSec + 1);
    this->labTime->setText(str);
}

void QUIMessageBox::setMessage(const QString &msg, int type, int closeSec)
{
    this->closeSec = closeSec;
    this->currentSec = 0;
    this->labTime->clear();

    checkSec();

    if (type == 0) {
        this->labIcoMain->setStyleSheet("border-image: url(:/image/msg_info.png);");
        this->btnCancel->setVisible(false);
        this->labTitle->setText("提示");
    } else if (type == 1) {
        this->labIcoMain->setStyleSheet("border-image: url(:/image/msg_question.png);");
        this->labTitle->setText("询问");
    } else if (type == 2) {
        this->labIcoMain->setStyleSheet("border-image: url(:/image/msg_error.png);");
        this->btnCancel->setVisible(false);
        this->labTitle->setText("错误");
    }

    this->labInfo->setText(msg);
    this->setWindowTitle(this->labTitle->text());
}

void QUIMessageBox::closeEvent(QCloseEvent *)
{
    closeSec = 0;
    currentSec = 0;
}

bool QUIMessageBox::eventFilter(QObject *obj, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(obj, evt);
}

void QUIMessageBox::on_btnOk_clicked()
{
    done(QMessageBox::Yes);
    close();
}

void QUIMessageBox::on_btnMenu_Close_clicked()
{
    done(QMessageBox::No);
    close();
}

void QUIMessageBox::setIconMain(QChar str, quint32 size)
{
    IconHelper::Instance()->setIcon(this->labIco, str, size);
}



QUIInputBox *QUIInputBox::self = 0;
QUIInputBox::QUIInputBox(QWidget *parent) : QDialog(parent)
{
    this->initControl();
    this->initForm();
}

QUIInputBox::~QUIInputBox()
{
    delete widgetMain;
}

void QUIInputBox::initControl()
{
    this->setObjectName(QString::fromUtf8("QUIInputBox"));

#ifdef __arm__
    this->resize(300, 160);
#else
    this->resize(280, 150);
#endif

    verticalLayout1 = new QVBoxLayout(this);
    verticalLayout1->setSpacing(0);
    verticalLayout1->setObjectName(QString::fromUtf8("verticalLayout1"));
    verticalLayout1->setContentsMargins(1, 1, 1, 1);
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
    widgetTitle->setSizePolicy(sizePolicy);
    widgetTitle->setMinimumSize(QSize(0, 30));
    horizontalLayout1 = new QHBoxLayout(widgetTitle);
    horizontalLayout1->setSpacing(0);
    horizontalLayout1->setObjectName(QString::fromUtf8("horizontalLayout1"));
    horizontalLayout1->setContentsMargins(0, 0, 0, 0);
    labIco = new QLabel(widgetTitle);
    labIco->setObjectName(QString::fromUtf8("labIco"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(labIco->sizePolicy().hasHeightForWidth());
    labIco->setSizePolicy(sizePolicy1);
    labIco->setMinimumSize(QSize(30, 0));
    labIco->setAlignment(Qt::AlignCenter);

    horizontalLayout1->addWidget(labIco);

    labTitle = new QLabel(widgetTitle);
    labTitle->setObjectName(QString::fromUtf8("labTitle"));
    labTitle->setStyleSheet(QString::fromUtf8(""));
    labTitle->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    horizontalLayout1->addWidget(labTitle);

    labTime = new QLabel(widgetTitle);
    labTime->setObjectName(QString::fromUtf8("labTime"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(labTime->sizePolicy().hasHeightForWidth());
    labTime->setSizePolicy(sizePolicy2);
    labTime->setAlignment(Qt::AlignCenter);

    horizontalLayout1->addWidget(labTime);

    widgetMenu = new QWidget(widgetTitle);
    widgetMenu->setObjectName(QString::fromUtf8("widgetMenu"));
    sizePolicy1.setHeightForWidth(widgetMenu->sizePolicy().hasHeightForWidth());
    widgetMenu->setSizePolicy(sizePolicy1);
    horizontalLayout2 = new QHBoxLayout(widgetMenu);
    horizontalLayout2->setSpacing(0);
    horizontalLayout2->setObjectName(QString::fromUtf8("horizontalLayout2"));
    horizontalLayout2->setContentsMargins(0, 0, 0, 0);
    btnMenu_Close = new QPushButton(widgetMenu);
    btnMenu_Close->setObjectName(QString::fromUtf8("btnMenu_Close"));
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
    btnMenu_Close->setSizePolicy(sizePolicy3);
    btnMenu_Close->setMinimumSize(QSize(30, 0));
    btnMenu_Close->setMaximumSize(QSize(30, 16777215));
    btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
    btnMenu_Close->setFocusPolicy(Qt::NoFocus);
    btnMenu_Close->setFlat(true);

    horizontalLayout2->addWidget(btnMenu_Close);
    horizontalLayout1->addWidget(widgetMenu);
    verticalLayout1->addWidget(widgetTitle);

    widgetMain = new QWidget(this);
    widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
    widgetMain->setStyleSheet(QString::fromUtf8(""));
    verticalLayout2 = new QVBoxLayout(widgetMain);
    verticalLayout2->setSpacing(5);
    verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
    verticalLayout2->setContentsMargins(5, 5, 5, 5);
    frame = new QFrame(widgetMain);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    verticalLayout3 = new QVBoxLayout(frame);
    verticalLayout3->setObjectName(QString::fromUtf8("verticalLayout3"));
    labInfo = new QLabel(frame);
    labInfo->setObjectName(QString::fromUtf8("labInfo"));
    labInfo->setScaledContents(false);
    labInfo->setWordWrap(true);

    verticalLayout3->addWidget(labInfo);

    txtValue = new QLineEdit(frame);
    txtValue->setObjectName(QString::fromUtf8("txtValue"));

    verticalLayout3->addWidget(txtValue);

    cboxValue = new QComboBox(frame);
    cboxValue->setObjectName(QString::fromUtf8("cboxValue"));

    verticalLayout3->addWidget(cboxValue);

    lay = new QHBoxLayout();
    lay->setObjectName(QString::fromUtf8("lay"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    lay->addItem(horizontalSpacer);

    btnOk = new QPushButton(frame);
    btnOk->setObjectName(QString::fromUtf8("btnOk"));
    btnOk->setMinimumSize(QSize(80, 0));
    btnOk->setStyleSheet(QString::fromUtf8(""));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/image/btn_ok.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnOk->setIcon(icon);

    lay->addWidget(btnOk);

    btnCancel = new QPushButton(frame);
    btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
    btnCancel->setMinimumSize(QSize(80, 0));
    btnCancel->setStyleSheet(QString::fromUtf8(""));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/image/btn_close.png"), QSize(), QIcon::Normal, QIcon::Off);
    btnCancel->setIcon(icon1);

    lay->addWidget(btnCancel);
    verticalLayout3->addLayout(lay);
    verticalLayout2->addWidget(frame);
    verticalLayout1->addWidget(widgetMain);

    setTabOrder(txtValue, btnOk);
    setTabOrder(btnOk, btnCancel);

    this->labTitle->setText("输入框");
    this->btnOk->setText("确定");
    this->btnCancel->setText("取消");

    connect(this->btnOk, SIGNAL(clicked()), this, SLOT(on_btnOk_clicked()));
    connect(this->btnMenu_Close, SIGNAL(clicked(bool)), this, SLOT(on_btnMenu_Close_clicked()));
    connect(this->btnCancel, SIGNAL(clicked()), this, SLOT(on_btnMenu_Close_clicked()));
}

void QUIInputBox::initForm()
{
    IconHelper::Instance()->setIcon(labIco, QUIConfig::IconMain, QUIConfig::FontSize + 2);
    IconHelper::Instance()->setIcon(btnMenu_Close, QUIConfig::IconClose, QUIConfig::FontSize);

    this->setProperty("form", true);
    this->widgetTitle->setProperty("form", "title");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(280, 150);
    this->setWindowTitle(this->labTitle->text());

    int width = 80;
    int iconWidth = 18;
    int iconHeight = 18;

    QList<QPushButton *> btns  = this->frame->findChildren<QPushButton *>();

    foreach (QPushButton *btn, btns) {
        btn->setMinimumWidth(width);
        btn->setIconSize(QSize(iconWidth, iconHeight));
    }

    closeSec = 0;
    currentSec = 0;

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkSec()));
    timer->start();

    this->installEventFilter(this);
}

void QUIInputBox::checkSec()
{
    if (closeSec == 0) {
        return;
    }

    if (currentSec < closeSec) {
        currentSec++;
    } else {
        this->close();
    }

    QString str = QString("关闭倒计时 %1 s").arg(closeSec - currentSec + 1);
    this->labTime->setText(str);
}

void QUIInputBox::setParameter(const QString &title, int type, int closeSec,
                               QString defaultValue, bool pwd)
{
    this->closeSec = closeSec;
    this->currentSec = 0;
    this->labTime->clear();
    this->labInfo->setText(title);

    checkSec();

    if (type == 0) {
        this->cboxValue->setVisible(false);
        this->txtValue->setPlaceholderText(defaultValue);

        if (pwd) {
            this->txtValue->setEchoMode(QLineEdit::Password);
        }
    } else if (type == 1) {
        this->txtValue->setVisible(false);
        this->cboxValue->addItems(defaultValue.split("|"));
    }
}

QString QUIInputBox::getValue() const
{
    return this->value;
}

void QUIInputBox::closeEvent(QCloseEvent *)
{
    closeSec = 0;
    currentSec = 0;
}

bool QUIInputBox::eventFilter(QObject *obj, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QWidget::eventFilter(obj, evt);
}

void QUIInputBox::on_btnOk_clicked()
{
    if (this->txtValue->isVisible()) {
        value = this->txtValue->text();
    } else if (this->cboxValue->isVisible()) {
        value = this->cboxValue->currentText();
    }

    done(QMessageBox::Ok);
    close();
}

void QUIInputBox::on_btnMenu_Close_clicked()
{
    done(QMessageBox::Cancel);
    close();
}

void QUIInputBox::setIconMain(QChar str, quint32 size)
{
    IconHelper::Instance()->setIcon(this->labIco, str, size);
}


IconHelper *IconHelper::self = 0;
IconHelper::IconHelper(QObject *) : QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    QStringList fontName = QFontDatabase::applicationFontFamilies(fontId);

    if (fontName.count() > 0) {
        iconFont = QFont(fontName.at(0));
    } else {
        qDebug() << "load fontawesome-webfont.ttf error";
    }
}

void IconHelper::setIcon(QLabel *lab, QChar c, quint32 size)
{
    iconFont.setPointSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}

void IconHelper::setIcon(QAbstractButton *btn, QChar c, quint32 size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}

QPixmap IconHelper::getPixmap(const QString &color, QChar c, quint32 size,
                              quint32 pixWidth, quint32 pixHeight)
{
    QPixmap pix(pixWidth, pixHeight);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(QColor(color));
    painter.setBrush(QColor(color));

    iconFont.setPointSize(size);
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), Qt::AlignCenter, c);
    painter.end();

    return pix;
}

QPixmap IconHelper::getPixmap(QToolButton *btn, bool normal)
{
    QPixmap pix;
    int index = btns.indexOf(btn);

    if (index >= 0) {
        if (normal) {
            pix = pixNormal.at(index);
        } else {
            pix = pixDark.at(index);
        }
    }

    return pix;
}

void IconHelper::setStyle(QWidget *widget, const QString &type, int borderWidth, const QString &borderColor,
                          const QString &normalBgColor, const QString &darkBgColor,
                          const QString &normalTextColor, const QString &darkTextColor)
{
    QString strBorder;
    if (type == "top") {
        strBorder = QString("border-width:%1px 0px 0px 0px;padding:%1px %2px %2px %2px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "right") {
        strBorder = QString("border-width:0px %1px 0px 0px;padding:%2px %1px %2px %2px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "bottom") {
        strBorder = QString("border-width:0px 0px %1px 0px;padding:%2px %2px %1px %2px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "left") {
        strBorder = QString("border-width:0px 0px 0px %1px;padding:%2px %2px %2px %1px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    }

    QStringList qss;
    qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton{border-style:none;border-radius:0px;padding:5px;color:%2;background:%3;}")
               .arg(type).arg(normalTextColor).arg(normalBgColor));

    qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton:hover,"
                       "QWidget[flag=\"%1\"] QAbstractButton:pressed,"
                       "QWidget[flag=\"%1\"] QAbstractButton:checked{"
                       "border-style:solid;%2border-color:%3;color:%4;background:%5;}")
               .arg(type).arg(strBorder).arg(borderColor).arg(darkTextColor).arg(darkBgColor));

    widget->setStyleSheet(qss.join(""));
}

void IconHelper::setStyle(QWidget *widget, QList<QToolButton *> btns, QList<int> pixChar,
                          quint32 iconSize, quint32 iconWidth, quint32 iconHeight,
                          const QString &type, int borderWidth, const QString &borderColor,
                          const QString &normalBgColor, const QString &darkBgColor,
                          const QString &normalTextColor, const QString &darkTextColor)
{
    int btnCount = btns.count();
    int charCount = pixChar.count();
    if (btnCount <= 0 || charCount <= 0 || btnCount != charCount) {
        return;
    }

    QString strBorder;
    if (type == "top") {
        strBorder = QString("border-width:%1px 0px 0px 0px;padding:%1px %2px %2px %2px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "right") {
        strBorder = QString("border-width:0px %1px 0px 0px;padding:%2px %1px %2px %2px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "bottom") {
        strBorder = QString("border-width:0px 0px %1px 0px;padding:%2px %2px %1px %2px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    } else if (type == "left") {
        strBorder = QString("border-width:0px 0px 0px %1px;padding:%2px %2px %2px %1px;")
                    .arg(borderWidth).arg(borderWidth * 2);
    }

    QStringList qss;
    qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton{border-style:none;border-radius:0px;padding:5px;color:%2;background:%3;}")
               .arg(type).arg(normalTextColor).arg(normalBgColor));

    qss.append(QString("QWidget[flag=\"%1\"] QAbstractButton:hover,"
                       "QWidget[flag=\"%1\"] QAbstractButton:pressed,"
                       "QWidget[flag=\"%1\"] QAbstractButton:checked{"
                       "border-style:solid;%2border-color:%3;color:%4;background:%5;}")
               .arg(type).arg(strBorder).arg(borderColor).arg(darkTextColor).arg(darkBgColor));

    qss.append(QString("QWidget#%1{background:%2;}").arg(widget->objectName()).arg(normalBgColor));

    qss.append(QString("QToolButton{border-width:0px;}"));
    qss.append(QString("QToolButton{background-color:%1;color:%2;}")
               .arg(normalBgColor).arg(normalTextColor));
    qss.append(QString("QToolButton:hover,QToolButton:pressed,QToolButton:checked{background-color:%1;color:%2;}")
               .arg(darkBgColor).arg(darkTextColor));

    widget->setStyleSheet(qss.join(""));

    for (int i = 0; i < btnCount; i++) {
        //存储对应按钮对象,方便鼠标移上去的时候切换图片
        QPixmap pixNormal = getPixmap(normalTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);
        QPixmap pixDark = getPixmap(darkTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);

        btns.at(i)->setIcon(QIcon(pixNormal));
        btns.at(i)->setIconSize(QSize(iconWidth, iconHeight));
        btns.at(i)->installEventFilter(this);

        this->btns.append(btns.at(i));
        this->pixNormal.append(pixNormal);
        this->pixDark.append(pixDark);
    }
}

void IconHelper::setStyle(QFrame *frame, QList<QToolButton *> btns, QList<int> pixChar,
                          quint32 iconSize, quint32 iconWidth, quint32 iconHeight,
                          const QString &normalBgColor, const QString &darkBgColor,
                          const QString &normalTextColor, const QString &darkTextColor)
{
    int btnCount = btns.count();
    int charCount = pixChar.count();
    if (btnCount <= 0 || charCount <= 0 || btnCount != charCount) {
        return;
    }

    QStringList qss;
    qss.append(QString("QToolButton{border-width:0px;}"));
    qss.append(QString("QToolButton{background-color:%1;color:%2;}")
               .arg(normalBgColor).arg(normalTextColor));
    qss.append(QString("QToolButton:hover,QToolButton:pressed,QToolButton:checked{background-color:%1;color:%2;}")
               .arg(darkBgColor).arg(darkTextColor));

    frame->setStyleSheet(qss.join(""));

    for (int i = 0; i < btnCount; i++) {
        //存储对应按钮对象,方便鼠标移上去的时候切换图片
        QPixmap pixNormal = getPixmap(normalTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);
        QPixmap pixDark = getPixmap(darkTextColor, QChar(pixChar.at(i)), iconSize, iconWidth, iconHeight);

        btns.at(i)->setIcon(QIcon(pixNormal));
        btns.at(i)->setIconSize(QSize(iconWidth, iconHeight));
        btns.at(i)->installEventFilter(this);

        this->btns.append(btns.at(i));
        this->pixNormal.append(pixNormal);
        this->pixDark.append(pixDark);
    }
}

bool IconHelper::eventFilter(QObject *watched, QEvent *event)
{
    if (watched->inherits("QToolButton")) {
        QToolButton *btn = (QToolButton *)watched;
        int index = btns.indexOf(btn);
        if (index >= 0) {
            if (event->type() == QEvent::Enter) {
                btn->setIcon(QIcon(pixDark.at(index)));
            } else if (event->type() == QEvent::Leave) {
                if (btn->isChecked()) {
                    btn->setIcon(QIcon(pixDark.at(index)));
                } else {
                    btn->setIcon(QIcon(pixNormal.at(index)));
                }
            }
        }
    }

    return QObject::eventFilter(watched, event);
}


QChar QUIConfig::IconMain = QChar(0xf072);
QChar QUIConfig::IconMenu = QChar(0xf0d7);
QChar QUIConfig::IconMin = QChar(0xf068);
QChar QUIConfig::IconMax = QChar(0xf2d2);
QChar QUIConfig::IconNormal = QChar(0xf2d0);
QChar QUIConfig::IconClose = QChar(0xf00d);

#ifdef __arm__
QString QUIConfig::FontName = "Droid Sans Fallback";
int QUIConfig::FontSize = 13;
#else
QString QUIConfig::FontName = "Microsoft Yahei";
int QUIConfig::FontSize = 9;
#endif

QString QUIConfig::ConfigFile = "config.ini";
QString QUIConfig::TextColor = "#F0F0F0";
QString QUIConfig::PanelColor = "#F0F0F0";
QString QUIConfig::BorderColor = "#F0F0F0";
QString QUIConfig::NormalColorStart = "#F0F0F0";
QString QUIConfig::NormalColorEnd = "#F0F0F0";
QString QUIConfig::DarkColorStart = "#F0F0F0";
QString QUIConfig::DarkColorEnd = "#F0F0F0";
QString QUIConfig::HighColor = "#F0F0F0";

void QUIConfig::ReadConfig()
{
    if (!CheckConfig()) {
        return;
    }

    QSettings set(QUIConfig::ConfigFile, QSettings::IniFormat);

    set.beginGroup("BaseConfig");    
    set.endGroup();
}

void QUIConfig::WriteConfig()
{
    QSettings set(QUIConfig::ConfigFile, QSettings::IniFormat);

    set.beginGroup("BaseConfig");    
    set.endGroup();
}

void QUIConfig::NewConfig()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#endif
    WriteConfig();
}

bool QUIConfig::CheckConfig()
{
    //如果配置文件大小为0,则以初始值继续运行,并生成配置文件
    QFile file(QUIConfig::ConfigFile);

    if (file.size() == 0) {
        NewConfig();
        return false;
    }

    //如果配置文件不完整,则以初始值继续运行,并生成配置文件
    if (file.open(QFile::ReadOnly)) {
        bool ok = true;

        while (!file.atEnd()) {
            QString line = file.readLine();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            QStringList list = line.split("=");

            if (list.count() == 2) {
                if (list.at(1) == "") {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            NewConfig();
            return false;
        }
    } else {
        NewConfig();
        return false;
    }

    return true;
}
