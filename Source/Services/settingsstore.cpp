#include "settingsstore.h"
#include <QLocale>
#include <QStringList>

SettingsStore::SettingsStore(std::shared_ptr<IDatabaseManager> db)
    : m_db(std::move(db))
{
    ensureDefaultSettings();
}

/// 1 запуск приложения - Сохранение в БД умолчательных значений -
/// В другие запуски - загрузка текущих настроек из БД
void SettingsStore::ensureDefaultSettings()
{
    if(!initDBConnection())
        return;

    // Тема
    auto themeSetting = m_db->loadSetting("darkTheme");
    if (!themeSetting.has_value()) //в БД еще нет такой настройки
    {
        setDarkTheme(true); // по умолчанию темная
        m_isDarkTheme = true;
    }
    else if (std::holds_alternative<bool>(*themeSetting))
    {
        m_isDarkTheme =  std::get<bool>(*themeSetting);;
    }


    // Язык по умолчанию определяется по системной локали устройства
    auto langSetting = m_db->loadSetting("language");
    if (!langSetting.has_value()) //в БД еще нет такой настройки
    {
        std::string defaultLang = "en"; // резервное значение
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString &locale : uiLanguages)
        {
            if (locale.startsWith(QStringLiteral("ru")))
            {
                defaultLang = "ru";
                break;
            }
        }
        setLanguage(defaultLang);
    }
    else if(std::holds_alternative<std::string>(*langSetting))
    {
        m_language = std::get<std::string>(*langSetting);
    }
}

bool SettingsStore::initDBConnection() const
{
    if(!m_db)
        return false;

    if(m_db->isInitialized())
        return true;

    return m_db->initialize();
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
///  выдаем текущие закешированные
////////////////////////////////////////////////////////////////////////
bool SettingsStore::darkTheme() const
{
    return m_isDarkTheme;
}


void SettingsStore::setDarkTheme(bool dark)
{
  if(m_isDarkTheme == dark)
    return;

  m_isDarkTheme = dark;
  if(m_db)
    m_db->saveSetting("darkTheme", dark);
}


std::string SettingsStore::language() const
{
    return m_language;
}


void SettingsStore::setLanguage(const std::string &lang)
{
  if(m_language==lang)
        return;

  m_language = lang;
  if(m_db)
    m_db->saveSetting("language", lang);
}
