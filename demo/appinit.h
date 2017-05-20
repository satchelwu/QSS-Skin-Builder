#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>
#include <QMutex>

class AppInit : public QObject
{
    Q_OBJECT
public:
    explicit AppInit(QObject *parent = 0);
    static AppInit *Instance() {
        static QMutex mutex;
        if (!self) {
            QMutexLocker locker(&mutex);
            if (!self) {
                self = new AppInit;
            }
        }
        return self;
    }

    void start();

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    static AppInit *self;

signals:

public slots:
};

#endif // APPINIT_H
