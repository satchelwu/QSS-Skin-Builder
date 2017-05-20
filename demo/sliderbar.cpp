#include "sliderbar.h"
#include "qevent.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

SliderBar::SliderBar(QWidget *parent) :	QWidget(parent)
{
    bgColorStart = QColor(121, 121, 121);
    bgColorEnd = QColor(78, 78, 78);
    old_bgColorEnd = bgColorEnd;

    barColorStart = QColor(46, 132, 243);
    barColorEnd = QColor(39, 110, 203);
    old_barColorEnd = barColorEnd;

    textNormalColor = QColor(230, 230, 230);
    textSelectColor = QColor(255, 255, 255);

    items = "";
    currentIndex = -1;
    currentItem = "";

    bgRadius = 0;
    barRadius = 0;
    space = 25;

    lineWidth = 3;
    lineColor = QColor(255, 107, 107);

    barStyle = BarStyle_Rect;

    keyMove = false;
    horizontal = true;
    flat = false;

    initLen = 10;
    step = 0;

    isForward = true;
    isVirgin = true;

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(slide()));
}

SliderBar::~SliderBar()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void SliderBar::resizeEvent(QResizeEvent *)
{
    int index = 0;
    int count = listItem.count();

    if (count == 0) {
        return;
    }

    if (count > 0 && currentItem.isEmpty()) {
        currentIndex = 0;
        currentItem = listItem.at(0).first;
    }

    for (int i = 0; i < count; i++) {
        if (listItem.at(i).first == currentItem) {
            index = i;
            break;
        }
    }

    moveTo(index);
}

void SliderBar::mousePressEvent(QMouseEvent *e)
{
    moveTo(e->pos());
}

void SliderBar::keyPressEvent(QKeyEvent *keyEvent)
{
    if (!keyMove) {
        return;
    }

    if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Up) {
        movePrevious();
    } else if (keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Down) {
        moveNext();
    }
}

void SliderBar::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景色
    drawBg(&painter);
    //绘制当前条目选中背景
    drawBar(&painter);
    //绘制条目文字
    drawText(&painter);
}

void SliderBar::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0, 0), QPoint(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRoundedRect(rect(), bgRadius, bgRadius);
    painter->restore();
}

void SliderBar::drawBar(QPainter *painter)
{
    painter->save();
    QPen pen = painter->pen();

    QLinearGradient barGradient(barRect.topLeft(), barRect.bottomLeft());
    barGradient.setColorAt(0.0, barColorStart);
    barGradient.setColorAt(1.0, barColorEnd);
    painter->setBrush(barGradient);

    if (barStyle == BarStyle_Rect) {
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(barRect, barRadius, barRadius);
        painter->restore();
        return;
    } else {
        pen.setWidthF(lineWidth);
        pen.setBrush(barGradient);
        painter->setPen(pen);
        painter->drawRoundedRect(barRect, barRadius, barRadius);
    }

    pen.setColor(lineColor);
    painter->setPen(pen);

    double offset = (double)lineWidth / 2;

    if (barStyle == BarStyle_Line_Top) {
        painter->drawLine(barRect.left(), barRect.top() + offset, barRect.right(), barRect.top() + offset);
    } else if (barStyle == BarStyle_Line_Right) {
        painter->drawLine(barRect.right() - offset, barRect.top(), barRect.right() - offset, barRect.bottom());
    } else if (barStyle == BarStyle_Line_Bottom) {
        painter->drawLine(barRect.left(), barRect.bottom() - offset, barRect.right(), barRect.bottom() - offset);
    } else if (barStyle == BarStyle_Line_Left) {
        painter->drawLine(barRect.left() + offset, barRect.top(), barRect.left() + offset, barRect.bottom());
    }

    //这里还可以增加右边倒三角形

    painter->restore();
}

void SliderBar::drawText(QPainter *painter)
{
    painter->save();

    QFont textFont;
    textFont.setBold(true);
    painter->setFont(textFont);

    int count = listItem.count();
    double textLen = 0;
    QString strText;
    initLen = 0;

    //横向导航时,字符区域取条目元素中最长的字符宽度
    QString longText = "";
    QStringList list = items.split(";");
    foreach (QString str, list) {
        if (str.length() > longText.length()) {
            longText = str;
        }
    }

    if (horizontal) {
        textLen  = painter->fontMetrics().width(longText);
    } else {
        textLen  = painter->fontMetrics().height();
    }

    //逐个绘制元素队列中的文字及文字背景
    for (int i = 0; i < count; i++) {
        strText = listItem.at(i).first;

        QPointF left(initLen, 0);
        QPointF right(initLen + textLen + space, height());

        if (!horizontal) {
            left = QPointF(0, initLen);
            right = QPointF(width(), initLen + textLen + space);
        }

        QRectF textRect(left, right);

        listItem[i].second = textRect;

        if (isVirgin) {
            barRect = textRect;
            isVirgin = false;
        }

        //当前选中区域的文字显示选中文字颜色
        if (textRect == listItem.at(currentIndex).second) {
            painter->setPen(textSelectColor);
        } else {
            painter->setPen(textNormalColor);
        }

        painter->drawText(textRect, Qt::AlignCenter, strText);
        initLen += textLen + space;
    }

    painter->restore();
}

int SliderBar::initStep(int distance)
{
    int n = 1;

    while (1) {
        if (n * n > distance) {
            break;
        } else {
            n++;
        }
    }

    return n * 1.4;
}

void SliderBar::slide()
{
    if (step > 1) {
        step--;
    }

    if (horizontal) {
        barLen = barRect.topLeft().x();
    } else {
        barLen = barRect.topLeft().y();
    }

    if (isForward) {
        barLen += step;

        if (barLen >= targetLen) {
            barLen = targetLen;
            timer->stop();
        }
    } else {
        barLen -= step;

        if (barLen <= targetLen) {
            barLen = targetLen;
            timer->stop();
        }
    }

    if (horizontal) {
        barRect = QRectF(QPointF(barLen, 0), QPointF(barLen + barRect.width(), height()));
    } else {
        barRect = QRectF(QPointF(0, barLen), QPointF(width(), barLen + barRect.height()));
    }

    update();
}

QColor SliderBar::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor SliderBar::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor SliderBar::getBarColorStart() const
{
    return this->barColorStart;
}

QColor SliderBar::getBarColorEnd() const
{
    return this->barColorEnd;
}

QColor SliderBar::getTextNormalColor() const
{
    return this->textNormalColor;
}

QColor SliderBar::getTextSelectColor() const
{
    return this->textSelectColor;
}

QString SliderBar::getItems() const
{
    return this->items;
}

int SliderBar::getCurrentIndex() const
{
    return this->currentIndex;
}

QString SliderBar::getCurrentItem() const
{
    return this->currentItem;
}

int SliderBar::getBgRadius() const
{
    return this->bgRadius;
}

int SliderBar::getBarRadius() const
{
    return this->barRadius;
}

int SliderBar::getSpace() const
{
    return this->space;
}

int SliderBar::getLineWidth() const
{
    return this->lineWidth;
}

QColor SliderBar::getLineColor() const
{
    return this->lineColor;
}

SliderBar::BarStyle SliderBar::getBarStyle() const
{
    return this->barStyle;
}

bool SliderBar::getKeyMove() const
{
    return this->keyMove;
}

bool SliderBar::getHorizontal() const
{
    return this->horizontal;
}

bool SliderBar::getFlat() const
{
    return this->flat;
}

QSize SliderBar::sizeHint() const
{
    return QSize(500, 30);
}

QSize SliderBar::minimumSizeHint() const
{
    return QSize(30, 30);
}

void SliderBar::clearItem()
{
    listItem.clear();
    update();
}

void SliderBar::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        update();
    }
}

void SliderBar::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        this->old_bgColorEnd = bgColorEnd;
        update();
    }
}

void SliderBar::setBarColorStart(const QColor &barColorStart)
{
    if (this->barColorStart != barColorStart) {
        this->barColorStart = barColorStart;
        update();
    }
}

void SliderBar::setBarColorEnd(const QColor &barColorEnd)
{
    if (this->barColorEnd != barColorEnd) {
        this->barColorEnd = barColorEnd;
        this->old_barColorEnd = barColorEnd;
        update();
    }
}

void SliderBar::setTextNormalColor(const QColor &textNormalColor)
{
    if (this->textNormalColor != textNormalColor) {
        this->textNormalColor = textNormalColor;
        update();
    }
}

void SliderBar::setTextSelectColor(const QColor &textSelectColor)
{
    if (this->textSelectColor != textSelectColor) {
        this->textSelectColor = textSelectColor;
        update();
    }
}

void SliderBar::setItems(const QString &items)
{
    this->items = items;
    this->listItem.clear();

    QStringList list = items.split(";");
    foreach (QString str, list) {
        this->listItem.push_back(qMakePair(str, QRectF()));
    }

    update();
}

void SliderBar::setCurrentIndex(int index)
{
    moveTo(index);
}

void SliderBar::setCurrentItem(const QString &item)
{
    moveTo(item);
}

void SliderBar::setBgRadius(int bgRadius)
{
    if (this->bgRadius != bgRadius) {
        this->bgRadius = bgRadius;
        update();
    }
}

void SliderBar::setBarRadius(int barRadius)
{
    if (this->barRadius != barRadius) {
        this->barRadius = barRadius;
        update();
    }
}

void SliderBar::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        update();
    }
}

void SliderBar::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        update();
    }
}

void SliderBar::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void SliderBar::setBarStyle(SliderBar::BarStyle barStyle)
{
    if (this->barStyle != barStyle) {
        this->barStyle = barStyle;
        update();
    }
}

void SliderBar::setKeyMove(bool keyMove)
{
    if (this->keyMove != keyMove) {
        this->keyMove = keyMove;

        if (keyMove) {
            setFocusPolicy(Qt::StrongFocus);
        } else {
            setFocusPolicy(Qt::NoFocus);
        }
    }
}

void SliderBar::setHorizontal(bool horizontal)
{
    if (this->horizontal != horizontal) {
        this->horizontal = horizontal;
        update();
    }
}

void SliderBar::setFlat(bool flat)
{
    if (this->flat != flat) {
        //扁平后将初始颜色赋值给结束颜色达到扁平的效果,如果取消扁平则再次恢复原有的颜色
        if (flat) {
            bgColorEnd = bgColorStart;
            barColorEnd = barColorStart;
        } else {
            bgColorEnd = old_bgColorEnd;
            barColorEnd = old_barColorEnd;
        }

        this->flat = flat;
        update();
    }
}

void SliderBar::moveFirst()
{
    int index = 0;

    if (currentIndex != index) {
        moveTo(index);
    }
}

void SliderBar::moveLast()
{
    int index = listItem.count() - 1;

    if (currentIndex != index) {
        moveTo(index);
    }
}

void SliderBar::movePrevious()
{
    if (currentIndex > 0) {
        currentIndex--;
        moveTo(currentIndex);
    }
}

void SliderBar::moveNext()
{
    if (currentIndex < listItem.count() - 1) {
        currentIndex++;
        moveTo(currentIndex);
    }
}

void SliderBar::moveTo(int index)
{
    if (listItem.count() > index) {
        QRectF rec = listItem.at(index).second;
        QPoint pos = QPoint(rec.x(), rec.y());
        moveTo(pos);
    }
}

void SliderBar::moveTo(const QString &item)
{
    int count = listItem.count();

    for (int i = 0; i < count; i++) {
        if (listItem.at(i).first == item) {
            moveTo(i);
            break;
        }
    }
}

void SliderBar::moveTo(const QPointF &point)
{
    int count = listItem.count();

    for (int i = 0; i < count; i++) {
        if (listItem.at(i).second.contains(point)) {
            currentIndex = i;
            currentItem = listItem.at(i).first;
            emit currentItemChanged(currentIndex, currentItem);

            targetRect = listItem.at(i).second;

            if (horizontal) {
                targetLen = targetRect.topLeft().x();
                barLen = barRect.topLeft().x();
            } else {
                targetLen = targetRect.topLeft().y();
                barLen = barRect.topLeft().y();
            }

            isForward = (targetLen > barLen);
            int distance = targetLen - barLen;
            distance = qAbs(distance);

            //重新获取每次移动的步长
            step = initStep(distance);
            timer->start();
        }
    }
}
