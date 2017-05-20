#ifndef UIDEMO4_H
#define UIDEMO4_H

#include <QDialog>

namespace Ui {
class UIDemo4;
}

class UIDemo4 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo4(QWidget *parent = 0);
    ~UIDemo4();

private:
    Ui::UIDemo4 *ui;
    bool max;
    QRect location;

private slots:
    void initForm();
    void initIndex();
    void currentItemChanged(int, const QString &item);

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO4_H
