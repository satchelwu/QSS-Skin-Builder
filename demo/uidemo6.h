#ifndef UIDEMO6_H
#define UIDEMO6_H

#include <QDialog>

namespace Ui {
class UIDemo6;
}

class UIDemo6 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo6(QWidget *parent = 0);
    ~UIDemo6();

private:
    Ui::UIDemo6 *ui;
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

#endif // UIDEMO6_H
