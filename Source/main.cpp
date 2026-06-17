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
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    LanguageManager * langManager = new LanguageManager(&engine, &app);

    //Создаем контроллер базы данных SqLite
    auto db = std::make_shared<DatabaseManagerQtSqlite>();
    db->initialize();
    // создаем сервис сохранения настроек
    auto settingsStore = std::make_shared<SettingsStore>(db);

    // Создаем и регистрируем контекст
    AppContext * appContext = new AppContext(settingsStore, langManager, &app);
    engine.rootContext()->setContextProperty("AppContext", appContext);

    // Создаем менеджер навигации
    NavigationManager * navManager = new NavigationManager(&engine, &app);
    engine.rootContext()->setContextProperty("NavManager", navManager);

    // Создаём модель новостей
    NewsListModel * newsModel = new NewsListModel(&app);
    engine.rootContext()->setContextProperty("newsModel", newsModel);

    // Загружаем QML через модуль (предполагается, что Main.qml зарегистрирован в qt_add_qml_module)
    engine.loadFromModule("lesson0", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    int ret = app.exec();
    engine.clearComponentCache();
    app.processEvents();
    return ret;
}
