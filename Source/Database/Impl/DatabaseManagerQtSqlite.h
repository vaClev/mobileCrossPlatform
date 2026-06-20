#pragma once
#ifndef DATABASEMANAGERQTSQLITE_H
#define DATABASEMANAGERQTSQLITE_H

#include <QString>
#include "Source/Database/IDatabaseManager.h"

class DatabaseManagerQtSqlite : public IDatabaseManager
{
    QString m_databaseName;
    bool m_initialized = false;
public:
    explicit DatabaseManagerQtSqlite(const std::string & databaseName = "lesson0.db");
    ~DatabaseManagerQtSqlite() override;

public:/// IDatabaseManager
    bool initialize() override;
    void closeConnection() override;
    bool saveSetting(const std::string & key, const DbValue & value) override;
    std::optional<DbValue> loadSetting(const std::string & key) const override;
    bool isInitialized() const override;

private:
    QString databasePath() const;
    bool createTablesIfNotExists();

    // Вспомогательные методы для конвертации
    QString dbValueToString(const DbValue & value) const;
    std::optional<DbValue> stringToDbValue(const QString & str, const QString & type) const;
};

#endif // DATABASEMANAGERQTSQLITE_H
