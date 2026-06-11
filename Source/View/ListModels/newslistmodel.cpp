#include "newslistmodel.h"

NewsListModel::NewsListModel(QObject * parent):
    QAbstractListModel(parent)
{
    loadStaticData();
}


/////////////////////////////////////
// override методы QAbstractListModel
/////////////////////////////////////
int NewsListModel::rowCount(const QModelIndex & parent) const
{
    return parent.isValid() ? 0 : m_news.count();
}


QVariant NewsListModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid() || index.row() >= m_news.count())
        return QVariant();

    const NewsItem &item = m_news.at(index.row());
    switch (role)
    {
      case TitleRole:
        return item.title;

      case DateRole:
        return item.date;

      case SummaryRole:
        return item.summary;

      case IdRole:
        return item.id;

      default:
        return QVariant();
    }
}


QHash<int, QByteArray> NewsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole]   = "title";
    roles[DateRole]    = "date";
    roles[SummaryRole] = "summary";
    roles[IdRole]      = "newsId";

    return roles;
}


/////////////////////////////////////
// Собственные методы NewsListModel
/////////////////////////////////////
void NewsListModel::fetchNews()
{
    beginResetModel(); // Сигнализируем, что модель сейчас полностью обновится
    m_news.clear();

    // В будущем здесь будет HTTP-запрос на сервер
    // Пока просто перезагружаем статические данные
    // Добавляем чуть больше новостей, чем в QML-версии
    //////////////////////////////////////////////////
    NewsItem item;

    item.id = 1;
    item.title = "Вышла Qt 6.10";
    item.date = "10 июня 2026";
    item.summary = "Релиз с новыми возможностями для мобильной разработки и улучшенной производительностью.";
    m_news.append(item);

    item.id = 2;
    item.title = "Обновление Android 16";
    item.date = "8 июня 2026";
    item.summary = "Google анонсировала Android 16 Beta 3 с улучшенной системой разрешений.";
    m_news.append(item);

    item.id = 3;
    item.title = "WWDC 2026";
    item.date = "5 июня 2026";
    item.summary = "Apple представила новые инструменты для разработчиков и обновления SwiftUI.";
    m_news.append(item);

    item.id = 4;
    item.title = "Советы по QML";
    item.date = "1 июня 2026";
    item.summary = "10 советов по оптимизации ListView и работе с большими моделями данных.";
    m_news.append(item);

    item.id = 5;
    item.title = "Кроссплатформенная разработка";
    item.date = "28 мая 2026";
    item.summary = "Сравнение Flutter, React Native и Qt Quick в 2026 году.";
    m_news.append(item);

    item.id = 6;
    item.title = "Безопасность мобильных приложений";
    item.date = "25 мая 2026";
    item.summary = "Как защитить данные пользователей в мобильных приложениях на Qt.";
    m_news.append(item);
    ///////////////////////////////////

    endResetModel();   // Модель обновлена
    emit dataLoaded();
}

void NewsListModel::loadStaticData()
{
    fetchNews();   // Просто вызываем тот же метод
}
