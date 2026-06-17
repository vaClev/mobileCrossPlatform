#pragma once
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

private:
    QQmlApplicationEngine * m_engine;//
    QTranslator *m_translator;       // переводчик
    QString m_currentLanguage;       // текущий язык (по умолчанию английский)

public:
    /// Конструктор
    explicit LanguageManager(QQmlApplicationEngine *engine, QObject *parent = nullptr);

    /// Текущий язык
    QString currentLanguage() const;

    /// Установить язык
    void setLanguage(const QString &language);

signals:
    void languageChanged();

private:
    void changeCurrentLanguage(const QString &language);

};

#endif // LANGUAGEMANAGER_H
