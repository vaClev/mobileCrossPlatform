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

///загрузка сохраненных настроек из БД
void AppContext::loadSettings()
{
    if (!m_settings) return;

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

/////////////////////////////////////////////////////////////////////////
/// Методы работы с настройками приложения
///
/// Настройки хранятся в БД, кашируются в переменные хранилища.
/// m_languageManager->currentLanguage() - язык выдаем текущий из языкового менеджера.
///
/// Общий подход:
/// SET:
///  При изменении настроек пользователем новые значения сразу пишутся в БД
/// GET:
///  При завпросе от UI элементов текущих настроек в БД не лазием.
///  выдаем текущие закешированные из SettingsStore и m_languageManager
////////////////////////////////////////////////////////////////////////
bool AppContext::isDarkTheme() const
{
    if (m_settings)
        return m_settings->darkTheme();

    return true;
}


void AppContext::setDarkTheme(bool dark)
{
    if (m_settings) {
        m_settings->setDarkTheme(dark);
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

void AppContext::closeSettings()
{
  if (m_settings)
    m_settings->closeSettings();
}
