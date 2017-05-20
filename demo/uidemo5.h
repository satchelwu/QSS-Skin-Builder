#ifndef UIDEMO5_H
#define UIDEMO5_H

#include <QDialog>

namespace Ui {
class UIDemo5;
}

class UIDemo5 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo5(QWidget *parent = 0);
    ~UIDemo5();

private:
    Ui::UIDemo5 *ui;
    bool max;
    QRect location;

private slots:
    void initForm();
    void initIndex();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
    void on_listView_pressed(const QModelIndex &index);
};

#endif // UIDEMO5_H
