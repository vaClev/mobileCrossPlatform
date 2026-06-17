#pragma once
#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QObject>
#include <QString>

class SettingsStore;
class LanguageManager;

class AppContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isAuthenticated  READ isAuthenticated  NOTIFY authenticationStateChanged)
    Q_PROPERTY(bool isDarkTheme READ isDarkTheme NOTIFY darkThemeChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)

private:
    bool m_isAuthenticated = false;
    bool m_isDarkTheme = true;   // цветовая тема интерфейса: темная = true, светлая = false.
    std::shared_ptr<SettingsStore> m_settings;
    LanguageManager * m_languageManager = nullptr;

public:
    AppContext(std::shared_ptr<SettingsStore> settingsStore,
               LanguageManager * languageManager = nullptr,
               QObject *parent = nullptr);

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

    /// Текущий язык
    QString language() const;
    /// Установить язык
    Q_INVOKABLE void setLanguage(const QString &lang);
signals:
    /// Сигнал об изменении статуса аутентификации
    void authenticationStateChanged();
    /// Сигнал об изменении темы интерфейса светлая/темная
    void darkThemeChanged();
    /// Сигнал об изменении языка
    void languageChanged();

private:
    /// Установка настроек
    void loadSettings();
};

#endif // APPCONTEXT_H
