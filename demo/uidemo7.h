#ifndef UIDEMO7_H
#define UIDEMO7_H

#include <QDialog>

class QToolButton;

namespace Ui
{
    class UIDemo7;
}

class UIDemo7 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo7(QWidget *parent = 0);
    ~UIDemo7();

private:
    Ui::UIDemo7 *ui;
    bool max;
    QRect location;

    QList<int> pixCharLeft;
    QList<QPixmap> pixNormalLeft;
    QList<QPixmap> pixDarkLeft;
    QList<QToolButton *> tbtnLeft;

    QList<int> pixCharTop;
    QList<QPixmap> pixNormalTop;
    QList<QPixmap> pixDarkTop;
    QList<QToolButton *> tbtnTop;

private slots:
    void initForm();
    void buttonClickedLeft();
    void buttonClickedTop();
    void initNavLeft();
    void initNavTop();
    void setStyle(QWidget *widget, int borderWidth = 3, QString borderColor = "#029FEA",
                  QString normalBgColor = "#292F38", QString selectBgColor = "#1D2025",
                  QString normalTextColor = "#54626F", QString selectTextColor = "#FDFDFD");

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO7_H
