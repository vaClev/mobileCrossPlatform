#pragma once
#ifndef SETTINGSSTORE_H
#define SETTINGSSTORE_H

#include <memory>
#include <string>
#include "Source/Database/IDatabaseManager.h"

class SettingsStore
{
    mutable std::shared_ptr<IDatabaseManager> m_db;
    bool m_isDarkTheme;
    std::string m_language;

public:
    explicit SettingsStore(std::shared_ptr<IDatabaseManager> db);

    // Тема
    bool darkTheme() const;
    void setDarkTheme(bool dark);

    // Язык (например, "ru", "en")
    std::string language() const;
    void setLanguage(const std::string &lang);
private:
    void ensureDefaultSettings();
    bool initDBConnection() const;
};

#endif // SETTINGSSTORE_H
