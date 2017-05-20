#ifndef UIDEMO3_H
#define UIDEMO3_H

#include <QDialog>

namespace Ui {
class UIDemo3;
}

class UIDemo3 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo3(QWidget *parent = 0);
    ~UIDemo3();

private:
    Ui::UIDemo3 *ui;
    bool max;
    QRect location;
    QList<QWidget *> frms;

private slots:
    void initForm();
    void initTreeWidget();
    void initPanelWidget();
    void initTableWidget();
    void initMenu();
    void doMenu();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // UIDEMO3_H
