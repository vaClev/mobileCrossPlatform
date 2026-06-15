#include "navigationmanager.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>

#ifdef Q_OS_ANDROID
#include <QJniObject>
#endif

///////////////////////////////////////////
// common - кроссплатформенные методы
NavigationManager::NavigationManager(QQmlApplicationEngine * engine, QObject *parent)
    : QObject{parent}
    ,m_engine{engine}
{}

void NavigationManager::navigateTo(const QString &screenId)
{
    emit navigationRequested(screenId);
}


void NavigationManager::goBack()
{
    emit backRequested();
}


///////////////////////////////////////////
// Android специфичный метод сворачивания приложения
void NavigationManager::minimizeApp()
{
#ifdef Q_OS_ANDROID
    // Способ, работающий на реальных устройствах (через QJniObject)
    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;"
        );
    if (activity.isValid()) {
        // Создаём Intent с действием MAIN и категорией HOME (эмуляция кнопки Home)
        QJniObject intent("android/content/Intent",
                          "(Ljava/lang/String;)V",
                          QJniObject::fromString("android.intent.action.MAIN").object());
        if (intent.isValid()) {
            intent.callObjectMethod("addCategory",
                                    "(Ljava/lang/String;)Landroid/content/Intent;",
                                    QJniObject::fromString("android.intent.category.HOME").object());
            activity.callMethod<void>("startActivity", "(Landroid/content/Intent;)V", intent.object());
        }
        else
        {
            shutdownApp();
        }
    }
    else
    {
        shutdownApp();
    }
#endif
}

void NavigationManager::shutdownApp()
{
    if (m_engine) {
        m_engine->clearComponentCache();
        qApp->processEvents();
    }
    qApp->quit();
}
