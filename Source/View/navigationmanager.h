#pragma once
#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>
class QQmlApplicationEngine;

class NavigationManager : public QObject
{
    Q_OBJECT

private:
    QQmlApplicationEngine * m_engine = nullptr;

public:
    explicit NavigationManager(QQmlApplicationEngine * engine, QObject *parent = nullptr);

    /// перейти на экран
    Q_INVOKABLE void navigateTo(const QString & screenId);
    /// вернуться к предыдущему экрану
    Q_INVOKABLE void goBack();
    /// Свернуть приложение Android / ios - заглушка
    Q_INVOKABLE void minimizeApp();

    /// Закрыть приложение
    Q_INVOKABLE void shutdownApp();
signals:
    void navigationRequested(const QString &screenId);
    void backRequested();
};

#endif // NAVIGATIONMANAGER_H
