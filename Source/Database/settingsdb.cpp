#include "settingsdb.h"


SettingsDB::SettingsDB(std::shared_ptr<IDatabaseManager> db)
    : m_db{std::move(db)}
{
    createTableIfNotExists();
}

bool SettingsDB::lazyOpenConnection()
{
    if(!m_db)
        return false;

    if(m_db->isInitialized())
        return true;

    return m_db->initialize();
}


bool SettingsDB::createTableIfNotExists()
{
    if(!lazyOpenConnection())
        return false;

    return m_db->executeQuery(
        "CREATE TABLE IF NOT EXISTS settings ("
        "  key   TEXT PRIMARY KEY,"
        "  value TEXT,"
        "  type  TEXT DEFAULT 'string'"
        ")"
        );

    //TODO можно и закрыть после соединение.
}


bool SettingsDB::saveSetting(const std::string & key, const DbValue &value)
{
    auto [valueStr, type] = dbValueToString(value);
    if(type == "undefined")
        return false;

    return m_db->executeQuery(
        "INSERT OR REPLACE INTO settings (key, value, type) VALUES (?, ?, ?)",
        {std::string(key), valueStr, type}
        );
}


std::pair<std::string, std::string> SettingsDB::dbValueToString(const DbValue &value) const
{
    if (std::holds_alternative<bool>(value))
        return { std::get<bool>(value) ? "true" : "false", "bool" };
    else if (std::holds_alternative<int>(value))
        return { std::to_string(std::get<int>(value)), "int" };
    else if (std::holds_alternative<double>(value))
        return { std::to_string(std::get<double>(value)), "double" };
    else if (std::holds_alternative<std::string>(value))
        return { std::get<std::string>(value), "string" };

    return { {}, "undefined" };  // на случай неизвестного типа
}


std::optional<DbValue> SettingsDB::loadSetting(const std::string &key) const
{
    auto rows = m_db->fetchQuery(
        "SELECT value, type FROM settings WHERE key = ?",
        {std::string(key)}
        );

    /// ожидаемо вернется одна строка с двумя полями - [0]value, [1]type
    if (rows.has_value() && !rows->empty() && rows->at(0).size() == 2)
    {
        const auto &row = rows->at(0);
        std::string value = std::get<std::string>(row[0]);
        std::string type  = std::get<std::string>(row[1]);

        if (type == "bool")
            return (value == "true");
        if (type == "int")
            return std::stoi(value);
        if (type == "double")
            return std::stod(value);

        return value;//else type==string
    }

    return std::nullopt;
}


