#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QQmlApplicationEngine>

class MyClass : public QObject
{
    Q_OBJECT

public:
    explicit MyClass(QQmlApplicationEngine &engine, QObject *parent = 0);
    static MyClass *instance();

protected:
    static MyClass *s_instance;

private:
    QQmlApplicationEngine *m_engine;

public slots:
    void slotQml2Qt();

signals:
    void signalQt2Qml();
};

#endif // MYCLASS_H
