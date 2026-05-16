#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QObject>

class LanguageManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentLanguage READ currentLanguage NOTIFY languageChanged)

private:
    QQmlApplicationEngine * m_engine;//
    QTranslator *m_translator;       // переводчик
    QString m_currentLanguage;       // туекущий язык (по умолчанию английский)

public:
    /// Конструктор
    explicit LanguageManager(QQmlApplicationEngine *engine, QObject *parent = nullptr);

    /// Текущий язык
    QString currentLanguage() const;

    /// Установить язык  //Q_INVOKABLE вызываемый из QML файла
    Q_INVOKABLE void setLanguage(const QString &language);

signals:
    void languageChanged();

private:
    void changeCurrentLanguage(const QString &language);

};

#endif // LANGUAGEMANAGER_H
