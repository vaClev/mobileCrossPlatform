#ifndef IDATABASEMANAGER_H
#define IDATABASEMANAGER_H

#include <string>
#include <variant>
#include <optional>

struct IDatabaseManager
{
public:
    // Типы значений, которые может хранить БД таблица настроек
    using DbValue = std::variant<bool, int, double, std::string>;

    virtual ~IDatabaseManager() = default;

    // Инициализация БД
    virtual bool initialize() = 0;

    /////////////////////////////////
    /// Работа с таблицей Settings - настройки приложеия
    /////////////////////////////////
    // Сохранение настройки
    virtual bool saveSetting(const std::string &key, const DbValue &value) = 0;

    // Загрузка настройки (возвращает std::nullopt, если ключ не найден)
    virtual std::optional<DbValue> loadSetting(const std::string &key) const = 0;
    /////////////////////////////////

    // Проверка инициализации
    virtual bool isInitialized() const = 0;
};
#endif // IDATABASEMANAGER_H
