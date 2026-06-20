#include "DatabaseManagerQtSqlite.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>

DatabaseManagerQtSqlite::DatabaseManagerQtSqlite(const std::string & databaseName)
    : m_databaseName(QString::fromStdString(databaseName))
{
}

DatabaseManagerQtSqlite::~DatabaseManagerQtSqlite()
{
    //if (QSqlDatabase::contains("qt_sql_default_connection")) {
    //    QSqlDatabase::database().close();
    //    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    //}
}

/// IDatabaseManager
/// /////////////////////////////////////
bool DatabaseManagerQtSqlite::initialize()
{
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

    if (!createTablesIfNotExists()) {
        qWarning() << "Failed to create tables";
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

/// Создание таблиц
bool DatabaseManagerQtSqlite::createTablesIfNotExists()
{
    QSqlQuery query;

    // Таблица для настроек settings
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS settings ("
        "  key   TEXT PRIMARY KEY,"
        "  value TEXT,"
        "  type  TEXT DEFAULT 'string'"
        ")"
        );
    if (!ok) {
        qWarning() << "Failed to create settings table:" << query.lastError().text();
        return false;
    }

    return true;
}

/// Закрыть соединение с БД
void DatabaseManagerQtSqlite::closeConnection()
{
    /*if(!m_initialized)
        return;

    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::database().close();
    }
    m_initialized = false;*/
}

/// Сохранение настройки в базу данных
bool DatabaseManagerQtSqlite::saveSetting(const std::string & key, const DbValue & value)
{
  if (!m_initialized)
    return false;

  QSqlQuery query;
  query.prepare(
      "INSERT OR REPLACE INTO settings (key, value, type) "
      "VALUES (:key, :value, :type)"
      );

  query.bindValue(":key", QString::fromStdString(key));
  query.bindValue(":value", dbValueToString(value));

  /// TODO выести в функцию getType
  QString type;
  if (std::holds_alternative<bool>(value)) type = "bool";
  else if (std::holds_alternative<int>(value)) type = "int";
  else if (std::holds_alternative<double>(value)) type = "double";
  else if (std::holds_alternative<std::string>(value)) type = "string";
  query.bindValue(":type", type);

  /// Выполняем запрос
  if (!query.exec()) {
      qWarning() << "Failed to save setting:" << query.lastError().text();
      return false;
  }
  return true;
}

/// Конвертировать из DbValue в строку
QString DatabaseManagerQtSqlite::dbValueToString(const DbValue &value) const
{
    if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value) ? "true" : "false";
    }
    else if (std::holds_alternative<int>(value)) {
        return QString::number(std::get<int>(value));
    }
    else if (std::holds_alternative<double>(value)) {
        return QString::number(std::get<double>(value));
    }
    else if (std::holds_alternative<std::string>(value)) {
        return QString::fromStdString(std::get<std::string>(value));
    }
    return QString();
}

///Чтение настройки из базы данных
std::optional<IDatabaseManager::DbValue> DatabaseManagerQtSqlite::loadSetting(const std::string & key) const
{
    if (!m_initialized)
      return std::nullopt;

    QSqlQuery query;
    query.prepare("SELECT value, type FROM settings WHERE key = :key");
    query.bindValue(":key", QString::fromStdString(key));

    if (query.exec() && query.next())
    {
      QString value = query.value(0).toString();
      QString type = query.value(1).toString();

      return stringToDbValue(value, type);
    }

    return std::nullopt;
}

/// Конвертировать вычитанные настройки в DbValue
std::optional<IDatabaseManager::DbValue> DatabaseManagerQtSqlite::stringToDbValue(
    const QString & str, const QString & type) const
{
    if (type == QStringLiteral("bool")) {
        // Булево значение: true или false (регистронезависимо)
        return str.compare(QStringLiteral("true"), Qt::CaseInsensitive) == 0;
    }
    else if (type == QStringLiteral("int")) {
        bool ok = false;
        int v = str.toInt(&ok);
        if (ok) return v;

        qWarning() << "Failed to convert" << str << "to int";
        return std::nullopt;
    }
    else if (type == QStringLiteral("double")) {
        bool ok = false;
        double v = str.toDouble(&ok);
        if (ok) return v;

        qWarning() << "Failed to convert" << str << "to double";
        return std::nullopt;
    }
    else if (type == QStringLiteral("string"))
    {
        return str.toStdString();
    }

    qWarning() << "Unknown type" << type << "for value" << str;
    return std::nullopt;
}

/// Вернуть статус инициализации
bool DatabaseManagerQtSqlite::isInitialized() const
{
  return m_initialized;
}
