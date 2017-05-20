#ifndef UIDEMO1_H
#define UIDEMO1_H

#include <QDialog>

namespace Ui {
class UIDemo1;
}

class UIDemo1 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo1(QWidget *parent = 0);
    ~UIDemo1();

private:
    Ui::UIDemo1 *ui;
    bool max;
    QRect location;

private slots:
    void initForm();
    void buttonClick();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO1_H
