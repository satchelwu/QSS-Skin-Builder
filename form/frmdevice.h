#ifndef FRMDEVICE_H
#define FRMDEVICE_H

#include <QWidget>

namespace Ui {
class frmDevice;
}

class frmDevice : public QWidget
{
    Q_OBJECT

public:
    explicit frmDevice(QWidget *parent = 0);
    ~frmDevice();

    void setDeviceName(const QString &deviceName);
    void setDeviceTemp(double tempValue);
    void setDeviceDamp(double dampValue);
    void setCountAll(int countAll);
    void setCountNoRead(int countNoRead);

private:
    Ui::frmDevice *ui;
};

#endif // FRMDEVICE_H
