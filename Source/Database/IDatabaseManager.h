#ifndef IDATABASEMANAGER_H
#define IDATABASEMANAGER_H

#include <string>
#include <variant>
#include <vector>
#include <optional>

// Типы значений, которые может хранить БД таблица настроек
using DbValue = std::variant<bool, int, double, std::string>;

struct IDatabaseManager
{
public:
    virtual ~IDatabaseManager() = default;

    // Инициализация БД
    virtual bool initialize() = 0;

    // Закрыть соединение
    virtual void closeConnection() = 0;

    // Выполнить запрос без возврата данных (INSERT, UPDATE, DELETE, CREATE)
    virtual bool executeQuery(const std::string &sql,
                              const std::vector<DbValue> &params = {}) = 0;

    using SelectResult = std::optional<std::vector<std::vector<DbValue>>>;
    // Выполнить запрос с возвратом данных (SELECT)
    virtual SelectResult fetchQuery(const std::string &sql, const std::vector<DbValue> &params = {}) = 0;

    // Проверка инициализации
    virtual bool isInitialized() const = 0;
};
#endif // IDATABASEMANAGER_H
