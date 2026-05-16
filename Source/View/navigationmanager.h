#pragma once
#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>
class AppContext;

class NavigationManager : public QObject
{
    Q_OBJECT

public:
    explicit NavigationManager(QObject *parent = nullptr);

    /// перейти на экран
    Q_INVOKABLE void navigateTo(const QString & screenId);
    /// вернуться к предыдущему экрану
    Q_INVOKABLE void goBack();

signals:
    void navigationRequested(const QString &screenId);
    void backRequested();
};

#endif // NAVIGATIONMANAGER_H
