#ifndef SETTINGSDB_H
#define SETTINGSDB_H

#include <memory>
#include "Source/Database/IDatabaseManager.h"

class SettingsDB
{
    std::shared_ptr<IDatabaseManager> m_db;

public:
    explicit SettingsDB(std::shared_ptr<IDatabaseManager> db);

    bool lazyOpenConnection();
    bool saveSetting(const std::string &key, const DbValue &value);
    std::optional<DbValue> loadSetting(const std::string &key) const;

private:
    /// Создание таблицы в БД
    bool createTableIfNotExists();
    /// Преобразовать DbValue в строку
    std::pair<std::string, std::string> dbValueToString(const DbValue &value) const;
};

#endif // SETTINGSDB_H
