#pragma once
#ifndef SETTINGSSTORE_H
#define SETTINGSSTORE_H

#include <string>
#include <memory>
#include "Source/Database/settingsdb.h"

class SettingsStore
{
    std::unique_ptr<SettingsDB> m_settingsDB;
    bool m_isDarkTheme;
    std::string m_language;

public:
    explicit SettingsStore(std::unique_ptr<SettingsDB> settingsDb);

    // Тема
    bool darkTheme() const;
    void setDarkTheme(bool dark);

    // Язык (например, "ru", "en")
    std::string language() const;
    void setLanguage(const std::string &lang);
private:
    void ensureDefaultSettings();
    bool initDBConnection();
};

#endif // SETTINGSSTORE_H
