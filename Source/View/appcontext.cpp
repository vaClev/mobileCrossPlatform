#include "appcontext.h"
#include "Source/Services/settingsstore.h"
#include "Source/languagemanager.h"

//Конструктор
AppContext::AppContext(std::shared_ptr<SettingsStore> settingsStore,
                       LanguageManager *languageManager,
                       QObject *parent)
    : QObject(parent)
    , m_settings(std::move(settingsStore))
    , m_languageManager(languageManager)
{
    loadSettings();
}

///загрузка сохраненных настроек
void AppContext::loadSettings()
{
    if (!m_settings) return;

    m_isDarkTheme = m_settings->darkTheme();

    if(m_languageManager)
    {
        QString currentLanguage = QString::fromStdString(m_settings->language());
        m_languageManager->setLanguage(currentLanguage);
    }
}

bool AppContext::isAuthenticated() const
{
    return m_isAuthenticated;
}

void AppContext::login(const QString &login, const QString &password)
{
    // Надо бы отправить запрос на север
    // TODO тут можно передать управление сервису который
    // пока просто эмулируем успешный вход
    bool isSucces = true;
    if(isSucces)
    {
        m_isAuthenticated = true;
        emit authenticationStateChanged();
    }
}

void AppContext::logout()
{
    // некоторые действия
    // возможно разрыв сессии
    m_isAuthenticated = false;
    emit authenticationStateChanged();
}

// Методы работы с сотоянием темы интерфейса
////////////////////////////////////
bool AppContext::isDarkTheme() const
{
    return m_isDarkTheme;
}


void AppContext::setDarkTheme(bool dark)
{
    if(m_isDarkTheme == dark)
        return;

    if (m_settings) {
        m_settings->setDarkTheme(dark);
        m_isDarkTheme = dark;
        emit darkThemeChanged();
    }
}


QString AppContext::language() const
{
    // Берём текущий язык из LanguageManager
    if (m_languageManager)
        return m_languageManager->currentLanguage();

    return QStringLiteral("en");
}


void AppContext::setLanguage(const QString &lang)
{
  if (!m_languageManager || m_languageManager->currentLanguage() == lang)
    return;

  m_languageManager->setLanguage(lang);
  if (m_settings)
    m_settings->setLanguage(lang.toStdString());

  emit languageChanged();
}
