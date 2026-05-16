#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "languagemanager.h"

#include<QDirIterator>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    LanguageManager langManager(&engine);
    // Установить язык на основе системной локали
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        if (locale.startsWith(QStringLiteral("ru"))) {
            langManager.setLanguage(QStringLiteral("ru"));
            break;
        }
    }
    // Устанавливаем контекстное свойство до загрузки QML
    engine.rootContext()->setContextProperty("languageManager", &langManager);

    // Загружаем QML через модуль (предполагается, что Main.qml зарегистрирован в qt_add_qml_module)
    engine.loadFromModule("lesson0", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        if(it.fileName().contains("i18n"))
            qDebug() << it.next();

        else
            it.next();
    }

    return app.exec();
}
