#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "languagemanager.h"
#include "View/appcontext.h"
#include "View/navigationmanager.h"
#include "View/ListModels/newslistmodel.h"

#include<QDirIterator>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    LanguageManager * langManager = new LanguageManager(&engine, &app);
    // Установить язык на основе системной локали
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        if (locale.startsWith(QStringLiteral("ru"))) {
            langManager->setLanguage(QStringLiteral("ru"));
            break;
        }
    }
    // Устанавливаем контекстное свойство язык до загрузки QML
    engine.rootContext()->setContextProperty("languageManager", langManager);

    // Создаем и регистрируем контекст
    AppContext * appContext = new AppContext(&app);
    engine.rootContext()->setContextProperty("AppContext", appContext);

    // Создаем менеджер навигации
    NavigationManager * navManager = new NavigationManager(&engine, &app);
    engine.rootContext()->setContextProperty("NavManager", navManager);

    // Создаём модель новостей
    NewsListModel newsModel;
    engine.rootContext()->setContextProperty("newsModel", &newsModel);

    // Загружаем QML через модуль (предполагается, что Main.qml зарегистрирован в qt_add_qml_module)
    engine.loadFromModule("lesson0", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    int ret = app.exec();
    engine.clearComponentCache();
    app.processEvents();
    return ret;
}
