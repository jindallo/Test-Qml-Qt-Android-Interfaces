#include "myclass.h"

#include <QDebug>
#include <QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>

MyClass* MyClass::s_instance = 0;

static void callAndroid2Qt(JNIEnv */*env*/, jobject /*obj*/)
{
    qDebug() << "TEST: Qt received!";
    qDebug() << "TEST: Qt is signaling Qml...";
    MyClass::instance()->signalQt2Qml();
}

static JNINativeMethod methods[] =
{
    {"callAndroid2Qt", "()V", (void *)callAndroid2Qt}
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
{
    JNIEnv* env;

    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;

    jclass javaClass = env->FindClass("org/qtproject/example/NativeFunctions");
    if (!javaClass)
        return JNI_ERR;

    if (env->RegisterNatives(javaClass, methods, sizeof(methods) / sizeof(methods[0])) < 0)
        return JNI_ERR;

    return JNI_VERSION_1_6;
}

MyClass::MyClass(QQmlApplicationEngine &engine, QObject *parent) : QObject(parent)
{
    s_instance = this;

    m_engine = &engine;
    connect(m_engine->rootObjects().first(), SIGNAL(signalQml2Qt()), this, SLOT(slotQml2Qt()));
    connect(this, SIGNAL(signalQt2Qml()), m_engine->rootObjects().first(), SLOT(slotQt2Qml()));
}

MyClass *MyClass::instance()
{
    return s_instance;
}

void MyClass::slotQml2Qt()
{
    qDebug() << "TEST: Qt received!";
    qDebug() << "TEST: Qt is calling Android...";
    QtAndroid::androidActivity().callMethod<void>("callQt2Android");
}

