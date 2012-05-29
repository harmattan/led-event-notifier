#ifndef LEDNOTIFICATIONSINK_H
#define LEDNOTIFICATIONSINK_H

#include <notificationsystem/notificationsink.h>
#include <QMap>
#include "meegohandsetnotification.h"

class MeegoHandsetNotificationProvider;

class LedNotificationSink : public NotificationSink
{
    Q_OBJECT
public:
    explicit LedNotificationSink(MeegoHandsetNotificationProvider* parent);

    void addNotification(const Notification &notification);
    void removeNotification(uint notificationId);

    void addGroup(uint groupId, const NotificationParameters &parameters);
    void removeGroup(uint groupId);

signals:
    void incomingNotification(MeegoHandsetNotification* notification);
    void trackedNotificationsChanged(QMap<uint,MeegoHandsetNotification*> map);
    void notificationRemoved(QString typeString);

protected:
    QMap<uint, MeegoHandsetNotification*> _trackedNotifications;
};

#endif // LEDNOTIFICATIONSINK_H
