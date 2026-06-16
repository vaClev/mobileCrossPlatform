#pragma once
#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>
#include <QString>

class AppContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated  READ isAuthenticated  NOTIFY authenticationStateChanged)
    Q_PROPERTY(bool isDarkTheme READ isDarkTheme NOTIFY darkThemeChanged)

private:
    bool m_isAuthenticated = false;
    bool m_isDarkTheme = true;   // цветовая тема интерфейса: темная = true, светлая = false.
public:
    explicit AppContext(QObject *parent = nullptr);

    /// Выдать статус аутентификации
    bool isAuthenticated() const;

    /// Залогиниться
    Q_INVOKABLE void login(const QString & login, const QString & password);
    /// Разлогиниться
    Q_INVOKABLE void logout();

    /// Выдать текущую цветовую схему интерфейса
    bool isDarkTheme() const;
    /// Переключить цветовую тему интерфейса
    Q_INVOKABLE void setDarkTheme(bool dark);
signals:
    /// Сигнал об изменении статуса аутентификации
    void authenticationStateChanged();
    /// Сигнал об изменении темы интерфейса светлая/темная
    void darkThemeChanged();
};

#endif // APPCONTEXT_H
