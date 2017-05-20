#ifndef PANELWIDGET_H
#define PANELWIDGET_H

/**
 * 面板容器控件 作者:feiyangqingyun(QQ:517216493) 2016-11-20
 * 1:支持所有widget子类对象,自动产生滚动条
 * 2:支持自动拉伸自动填充
 * 3:提供接口获取容器内的所有对象的指针
 */

#include <QWidget>

class QScrollArea;
class QFrame;
class QVBoxLayout;
class QGridLayout;

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT PanelWidget : public QWidget
#else
class PanelWidget : public QWidget
#endif

{
    Q_OBJECT
public:
    explicit PanelWidget(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);

private:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;

public:
    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    void setWidget(QList<QWidget *> widgets, int columnCount);    
    void setMargin(int left, int top, int right, int bottom);
    void setMargin(int margin);
    void setSpacing(int space);    
};

#endif // PANELWIDGET_H
