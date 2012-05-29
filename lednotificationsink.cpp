#include "lednotificationsink.h"

#include "meegohandsetnotificationprovider.h"

LedNotificationSink::LedNotificationSink(MeegoHandsetNotificationProvider *parent) :
    NotificationSink(parent)
{

}

void LedNotificationSink::addNotification(const Notification &notification)
{
    const uint notificationId = notification.notificationId();

    if (_trackedNotifications.contains(notificationId)) {
        MeegoHandsetNotification* n = _trackedNotifications[notificationId];
        n->changeTo(notification);
    } else {
        MeegoHandsetNotification* n = new MeegoHandsetNotification(notification, this);
        _trackedNotifications[notificationId] = n;
        emit incomingNotification(n);
    }

    emit trackedNotificationsChanged(_trackedNotifications);
}

void LedNotificationSink::removeNotification(uint notificationId)
{
    if (_trackedNotifications.contains(notificationId)) {
        MeegoHandsetNotification* n = _trackedNotifications[notificationId];
        _trackedNotifications.remove(notificationId);
        emit notificationRemoved(n->typeString());
        n->remove();
        n->deleteLater();
    }
    emit trackedNotificationsChanged(_trackedNotifications);
}

void LedNotificationSink::addGroup(uint groupId, const NotificationParameters &parameters)
{
    // We do not care about notification groups
    Q_UNUSED(groupId);
    Q_UNUSED(parameters);
}

void LedNotificationSink::removeGroup(uint groupId)
{
    Q_UNUSED(groupId);
}
