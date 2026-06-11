#ifndef NEWSLISTMODEL_H
#define NEWSLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QList>


// Структура для одной новости //TODO DTO
//////////////////////////////
struct NewsItem
{
    QString title;
    QString date;
    QString summary;
    int id;
};


// Структура для одной новости //TODO DTO
//////////////////////////////
class NewsListModel : public QAbstractListModel
{
    Q_OBJECT

    QList<NewsItem> m_news; ///<Список новостей

    // Это свойство будет доступно в QML
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    // Роли данных (как колонки в БД)
    enum NewsRoles {
        TitleRole = Qt::UserRole + 1,
        DateRole,
        SummaryRole,
        IdRole
    };
    Q_ENUM(NewsRoles)

    ///Конструктор
    explicit NewsListModel(QObject * parent = nullptr);

public:// Обязательные методы QAbstractListModel
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public:// Метод для обновления данных
    Q_INVOKABLE void fetchNews();

signals:
    /// при изменении количества элементов
    void countChanged();
    /// когда данные готовы
    void dataLoaded();
    /// при возникновении ошибки
    void errorOccurred(const QString &errorMessage);

private:
    // Функция-заглушка, которая имитирует загрузку с сервера
    void loadStaticData();
};

#endif // NEWSLISTMODEL_H
