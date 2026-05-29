#ifndef DEEPSEEKCLIENT_H
#define DEEPSEEKCLIENT_H

#include <QObject>
#include <QString>

class QNetworkAccessManager;

class DeepSeekClient : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager * m_manager;

public:
    explicit DeepSeekClient(QObject *parent = nullptr);
    void sendMessage(const QString & userMessage);

signals:
    void DeepSeekResponsed(const QString & responseText);
};

#endif // DEEPSEEKCLIENT_H
