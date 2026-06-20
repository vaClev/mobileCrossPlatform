#include <memory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "languagemanager.h"
#include "View/appcontext.h"
#include "View/navigationmanager.h"
#include "View/ListModels/newslistmodel.h"

#include "Database/Impl/DatabaseManagerQtSqlite.h"
#include "Services/settingsstore.h"

int main(int argc, char *argv[])
{
    // Фикс для Android-эмулятора (hwuiTask1). Принудительно запускает OpenGL/Vulkan бэкенд
    // вместо дефолтных системных оберток, которые ломают мьютексы при закрытии.
    qputenv("QSG_RHI_BACKEND", "opengl");

    QGuiApplication app(argc, argv);

    // Выделение на стеке — стандартный и самый безопасный подход для Qt
    QQmlApplicationEngine engine;

    LanguageManager * langManager = new LanguageManager(&engine, &app);

    // Создаем БД. Оставляем shared_ptr, раз он нужен на перспективу
    auto db = std::make_shared<DatabaseManagerQtSqlite>();

    // Закрываем соединение строго при выходе из цикла приложения,
    // пока движок engine еще существует на стеке, но уже остановил отрисовку
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [db]() {
        db->closeConnection();
    });

    // Создаем сервис настроек
    auto settingsStore = std::make_unique<SettingsStore>(db);

    // ПРАВИЛО: Все C++ менеджеры привязываем к родителю &engine.
    // Когда 'engine' выйдет из области видимости, она сама корректно удалит их.
    AppContext * appContext = new AppContext(std::move(settingsStore), langManager, &engine);
    engine.rootContext()->setContextProperty("AppContext", appContext);

    NavigationManager * navManager = new NavigationManager(&engine, &engine);
    engine.rootContext()->setContextProperty("NavManager", navManager);

    NewsListModel * newsModel = new NewsListModel(&engine);
    engine.rootContext()->setContextProperty("newsModel", newsModel);

    engine.loadFromModule("lesson0", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
    // Здесь управление передается C++, стек очищается снизу вверх:
    // 1. Сначала уничтожается engine -> уничтожает appContext, navManager, newsModel.
    // 2. Внутри appContext безопасно уничтожается settingsStore.
    // 3. Уничтожается shared_ptr db (счетчик ссылок падает до 0, память чистится).
    // 4. Уничтожается QGuiApplication app.
}
