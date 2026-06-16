#include "appcontext.h"

//Конструктор по умолчанию
AppContext::AppContext(QObject *parent)
    : QObject{parent}
{}

bool AppContext::isAuthenticated() const
{
    return m_isAuthenticated;
}

void AppContext::login(const QString &login, const QString &password)
{
    // Надо бы отправить запрос на север
    // TODO тут можно передать управление сервису который
    // пока просто эмулируем успешный вход
    bool isSucces = true;
    if(isSucces)
    {
        m_isAuthenticated = true;
        emit authenticationStateChanged();
    }
}

void AppContext::logout()
{
    // некоторые действия
    // возможно разрыв сессии
    m_isAuthenticated = false;
    emit authenticationStateChanged();
}

// Методы работы с сотоянием темы интерфейса
////////////////////////////////////
bool AppContext::isDarkTheme() const
{
    return m_isDarkTheme;
}


void AppContext::setDarkTheme(bool dark)
{
    if(m_isDarkTheme == dark)
        return;

    m_isDarkTheme = dark;
    emit darkThemeChanged();
}
