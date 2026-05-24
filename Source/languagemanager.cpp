#include "languagemanager.h"
#include<QFile>

LanguageManager::LanguageManager(QQmlApplicationEngine * engine, QObject *parent)
    : QObject{parent}
    , m_engine {engine}
    , m_translator(new QTranslator(this))
    , m_currentLanguage{QStringLiteral("en")} // по умолчанию английский
{
}

/// Текущий язык
QString LanguageManager::currentLanguage() const
{
    return m_currentLanguage;
}



Q_INVOKABLE void LanguageManager::setLanguage(const QString &language)
{
    QFile file(":/applesson0_ru.qm");
    qDebug() << "File exists in resources:" << file.exists();

    if(m_currentLanguage == language)
        return;

    /// Удаляем старый перевод
    qApp->removeTranslator(m_translator);

    ///Пробуем загрузить перевод для выбранного языка
    if(language== QStringLiteral("ru"))
    {
        if(m_translator->load(QStringLiteral(":/applesson0_ru.qm")))
        {
            qApp->installTranslator(m_translator);
            changeCurrentLanguage(language);
        }
    }
    else if(language == QStringLiteral("en"))
    {
        //qApp installTranslator для английского языка не требуется. Он по умолчанию.
        changeCurrentLanguage(language);
    }
}


void LanguageManager::changeCurrentLanguage(const QString &language)
{
    m_currentLanguage = language;

    /// Испускаем сигнал "Язык изменен"
    emit languageChanged();

    // Обновляем весь QML (доступно с Qt 6.4)
    m_engine->retranslate();
}
