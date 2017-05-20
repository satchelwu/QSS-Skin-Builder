#include "uidemo8.h"
#include "ui_uidemo8.h"

UIDemo8::UIDemo8(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo8)
{
    ui->setupUi(this);
}

UIDemo8::~UIDemo8()
{
    delete ui;
}
