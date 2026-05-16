#pragma once
#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>
#include <QString>

class AppContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated  READ isAuthenticated  NOTIFY authenticationStateChanged)

private:
    bool m_isAuthenticated = false;
public:
    explicit AppContext(QObject *parent = nullptr);

    /// Выдать статус аутентификации
    bool isAuthenticated() const;

    /// Залогиниться
    Q_INVOKABLE void login(const QString & login, const QString & password);
    /// Разлогиниться
    Q_INVOKABLE void logout();

signals:
    /// сигнал об изменении статуса аутентификации
    void authenticationStateChanged();
};

#endif // APPCONTEXT_H
