#ifndef UIDEMO8_H
#define UIDEMO8_H

#include <QDialog>

namespace Ui {
class UIDemo8;
}

class UIDemo8 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo8(QWidget *parent = 0);
    ~UIDemo8();

private:
    Ui::UIDemo8 *ui;
};

#endif // UIDEMO8_H
