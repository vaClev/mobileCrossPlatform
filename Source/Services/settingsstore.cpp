#include "settingsstore.h"
#include <QLocale>
#include <QStringList>

SettingsStore::SettingsStore(std::shared_ptr<IDatabaseManager> db)
    : m_db(std::move(db))
{
    ensureDefaultSettings();
}

void SettingsStore::ensureDefaultSettings()
{
    if (!m_db) return;

    // Тема по умолчанию темная
    auto themeSetting = m_db->loadSetting("darkTheme");
    if (!themeSetting.has_value()) {
        setDarkTheme(true);
    }

    // Язык по умолчанию определяется по системной локали устройства
    auto langSetting = m_db->loadSetting("language");
    if (!langSetting.has_value())
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
}


bool SettingsStore::darkTheme() const
{
    auto val = m_db->loadSetting("darkTheme");
    if (val.has_value() && std::holds_alternative<bool>(*val))
        return std::get<bool>(*val);

    return true;
}


void SettingsStore::setDarkTheme(bool dark)
{
    m_db->saveSetting("darkTheme", dark);
}


std::string SettingsStore::language() const
{
    auto val = m_db->loadSetting("language");
    if (val.has_value() && std::holds_alternative<std::string>(*val))
        return std::get<std::string>(*val);

    return "en";
}


void SettingsStore::setLanguage(const std::string &lang)
{
    m_db->saveSetting("language", lang);
}
