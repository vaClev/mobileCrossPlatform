#include "deepseekclient.h"
#include <QNetworkAccessManager>

DeepSeekClient::DeepSeekClient(QObject *parent)
    : QObject{parent}
    , m_manager{new QNetworkAccessManager(this)}
{}
