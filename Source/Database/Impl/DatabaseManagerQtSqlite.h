#pragma once
#ifndef DATABASEMANAGERQTSQLITE_H
#define DATABASEMANAGERQTSQLITE_H

#include <QString>
#include "Source/Database/IDatabaseManager.h"
#include <QMutex>
#include <QSqlQuery>

class DatabaseManagerQtSqlite : public IDatabaseManager
{
    QString m_databaseName;
    bool m_initialized = false;
    mutable QMutex m_mutex;

public:
    explicit DatabaseManagerQtSqlite(const std::string & databaseName = "lesson0.db");
    ~DatabaseManagerQtSqlite() override;

public:/// IDatabaseManager
    bool initialize() override;
    void closeConnection() override;
    bool executeQuery(const std::string &sql, const std::vector<DbValue> &params = {}) override;
    SelectResult fetchQuery(const std::string &sql, const std::vector<DbValue> &params = {}) override;
    bool isInitialized() const override;

private:
    QString databasePath() const;
    void bindParameters(QSqlQuery &query, const std::vector<DbValue> &params);
    DbValue variantToDbValue(const QVariant &var) const;
};

#endif // DATABASEMANAGERQTSQLITE_H
