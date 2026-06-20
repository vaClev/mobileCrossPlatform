#include <memory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "languagemanager.h"
#include "View/appcontext.h"
#include "View/navigationmanager.h"
#include "View/ListModels/newslistmodel.h"

#include "Database/Impl/DatabaseManagerQtSqlite.h"
#include "Database/settingsdb.h"
#include "Services/settingsstore.h"

int main(int argc, char *argv[])
{
    //QT GUI APP
    ////////////////////////////////////////////////////////////////////
    // Выделение на стеке — стандартный и самый безопасный подход для Qt
    QGuiApplication app(argc, argv);
    // Движок отрисовки .qml файлов
    QQmlApplicationEngine engine;
    // Языковой менеджер - для перевода строковых ресурсов
    LanguageManager * langManager = new LanguageManager(&engine, &app);


    //Database - слой
    ////////////////////////////////////////////////////////////////////////
    /// Создаем БД менеджер. shared_ptr, нужен на перспективу нескольких таблиц
    auto db = std::make_shared<DatabaseManagerQtSqlite>();
    /// Закрываем соединение c БД строго при выходе из цикла приложения,
    /// пока движок engine еще существует на стеке, но уже остановил отрисовку
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [db]() {
        db->closeConnection();
    });
    ///создаем БД-помощника таблицы "Настройки"
    auto settingsDB = std::make_unique<SettingsDB>(db);
    ///////////////////////////////////////////////////////////////////////


    //Services - слой
    ////////////////////////////////////////////////////////////////////////
    /// Создаем сервис настроек - отдаем ему во владение settingsDB
    /// Сервис кеширует насройки у себя. Чтобы не лазить лишний раз в БД
    auto settingsStore = std::make_unique<SettingsStore>(std::move(settingsDB));
    ////////////////////////////////////////////////////////////////////////


    // View - слой
    ///////////////////////////////////////////////////////////////////////
    // ПРАВИЛО: Все C++ менеджеры привязываем к родителю &engine.
    // Когда 'engine' выйдет из области видимости, она сама корректно удалит их.
    AppContext * appContext = new AppContext(std::move(settingsStore), langManager, &engine);
    engine.rootContext()->setContextProperty("AppContext", appContext);

    NavigationManager * navManager = new NavigationManager(&engine, &engine);
    engine.rootContext()->setContextProperty("NavManager", navManager);

    NewsListModel * newsModel = new NewsListModel(&engine);
    engine.rootContext()->setContextProperty("newsModel", newsModel);

    /// Загрузка начального qml (Main.qml)
    engine.loadFromModule("lesson0", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    ///Запуск приложения
    return app.exec();
    // Здесь управление передается C++, стек очищается снизу вверх:
    // 1. Сначала уничтожается engine -> уничтожает appContext, navManager, newsModel.
    // 2. Внутри appContext безопасно уничтожается settingsStore и settingsDB.
    // 3. Уничтожается shared_ptr db (счетчик ссылок падает до 0, память чистится).
    // 4. Уничтожается QGuiApplication app.
}
