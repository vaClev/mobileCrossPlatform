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


// Класс модели данных списка новостей
//////////////////////////////
class NewsListModel : public QAbstractListModel
{
    Q_OBJECT

    QList<NewsItem> m_news; ///<Список новостей
    bool m_loading = false; ///<Состояние - "идет загрузка данных"

    // Эти свойства будут доступны в QML
    Q_PROPERTY(bool isLoading READ isLoading NOTIFY loadingChanged)
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

public:// Обязательные методы по контракту QAbstractListModel
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public:// Собственные методы NewsListModel
    /// Происходит загрузка данных?
    bool isLoading() const;
    /// Метод для обновления данных
    Q_INVOKABLE void fetchNews();

signals:
    /// при изменении состояния загрузки
    void loadingChanged();
    /// при изменении количества элементов
    void countChanged();
    /// когда данные готовы
    void dataLoaded();
    /// при возникновении ошибки
    void errorOccurred(const QString &errorMessage);

private:
    void finalizeUpdate();
};

#endif // NEWSLISTMODEL_H
