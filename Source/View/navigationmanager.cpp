#include "navigationmanager.h"

NavigationManager::NavigationManager(QObject *parent)
    : QObject{parent}
{}

void NavigationManager::navigateTo(const QString &screenId)
{
    emit navigationRequested(screenId);
}

void NavigationManager::goBack()
{
    emit backRequested();
}
