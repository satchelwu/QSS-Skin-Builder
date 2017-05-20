#ifndef UIDEMO2_H
#define UIDEMO2_H

#include <QDialog>

namespace Ui {
class UIDemo2;
}

class UIDemo2 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo2(QWidget *parent = 0);
    ~UIDemo2();

private:
    Ui::UIDemo2 *ui;
    bool max;
    QRect location;

private slots:
    void initForm();
    void buttonClick();
    void btnClick();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO2_H
