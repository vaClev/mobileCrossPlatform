#include "DatabaseManagerQtSqlite.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QDir>
#include <QMutexLocker>

DatabaseManagerQtSqlite::DatabaseManagerQtSqlite(const std::string & databaseName)
    : m_databaseName(QString::fromStdString(databaseName))
{
}

DatabaseManagerQtSqlite::~DatabaseManagerQtSqlite()
{
    DatabaseManagerQtSqlite::closeConnection();
}

/// IDatabaseManager
/// /////////////////////////////////////
bool DatabaseManagerQtSqlite::initialize()
{
    QMutexLocker locker(&m_mutex);

    if (m_initialized)
        return true;

    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        // Соединение уже существует (после закрытия) – берём его
        db = QSqlDatabase::database();
    }
    else
    {
        // Первый запуск – создаём новое соединение
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(databasePath());
    }

    if (!db.open()) {
        qWarning() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    m_initialized = true;
    qDebug() << "Database initialized at:" << databasePath();
    return true;
}


/// Путь к файлу базы данных. Расположение файла .db
QString DatabaseManagerQtSqlite::databasePath() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dir.filePath(m_databaseName);
}


/// Закрыть соединение с БД - !!подключать к сигналу закрытия приложения!!
void DatabaseManagerQtSqlite::closeConnection()
{
    QMutexLocker locker(&m_mutex);

    if(!m_initialized)
        return;

    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::database().close();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    m_initialized = false;
}


bool DatabaseManagerQtSqlite::executeQuery(const std::string &sql, const std::vector<DbValue> &params)
{
    QMutexLocker locker(&m_mutex);

    if (!m_initialized) {
        qWarning() << "Database not initialized";
        return false;
    }

    QSqlQuery query;
    query.prepare(QString::fromStdString(sql));
    bindParameters(query, params);

    if (!query.exec()) {
        qWarning() << "Query failed:" << query.lastError().text()
        << "\nSQL:" << QString::fromStdString(sql);
        return false;
    }
    return true;
}


void DatabaseManagerQtSqlite::bindParameters(QSqlQuery &query, const std::vector<DbValue> &params)
{
    for (size_t i = 0; i < params.size(); ++i) {
        const auto &param = params[i];
        if (std::holds_alternative<bool>(param))
            query.bindValue(i, std::get<bool>(param));
        else if (std::holds_alternative<int>(param))
            query.bindValue(i, std::get<int>(param));
        else if (std::holds_alternative<double>(param))
            query.bindValue(i, std::get<double>(param));
        else if (std::holds_alternative<std::string>(param))
            query.bindValue(i, QString::fromStdString(std::get<std::string>(param)));
    }
}


IDatabaseManager::SelectResult DatabaseManagerQtSqlite::fetchQuery(const std::string &sql, const std::vector<DbValue> &params)
{
    QMutexLocker locker(&m_mutex);

    if (!m_initialized) {
        qWarning() << "Database not initialized";
        return std::nullopt;
    }

    QSqlQuery query;
    query.prepare(QString::fromStdString(sql));
    bindParameters(query, params);

    if (!query.exec()) {
        qWarning() << "Query failed:" << query.lastError().text();
        return std::nullopt;
    }

    std::vector<std::vector<DbValue>> rows;
    while (query.next()) {
        std::vector<DbValue> row;
        for (int i = 0; i < query.record().count(); ++i) {
            row.push_back(variantToDbValue(query.value(i)));
        }
        rows.push_back(row);
    }
    return rows;
}


DbValue DatabaseManagerQtSqlite::variantToDbValue(const QVariant &var) const
{
    switch (var.typeId()) {
    case QMetaType::Bool:
        return var.toBool();
    case QMetaType::Int:
    case QMetaType::LongLong:
        return var.toInt();
    case QMetaType::Double:
        return var.toDouble();
    default:
        return var.toString().toStdString();
    }
}

/// Вернуть статус инициализации
bool DatabaseManagerQtSqlite::isInitialized() const
{
  QMutexLocker locker(&m_mutex);
  return m_initialized;
}
