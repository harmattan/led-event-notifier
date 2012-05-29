#ifndef MEEGOHANDSETNOTIFICATIONPROVIDER_H
#define MEEGOHANDSETNOTIFICATIONPROVIDER_H

#include <QObject>
#include <mnotificationmanagerinterface.h>

#include <notificationsystem/notification.h>

class LedNotificationSink;
class MeegoHandsetNotification;

class MeegoHandsetNotificationProvider : public QObject
{
    Q_OBJECT
public:
    explicit MeegoHandsetNotificationProvider(QObject *parent = 0);
    ~MeegoHandsetNotificationProvider();

protected:
    MNotificationManagerInterface *m_manager;
    LedNotificationSink *m_sink;

protected slots:
    void newNotification(MeegoHandsetNotification *n);

signals:
    void incomingNotification(MeegoHandsetNotification *n);
    void trackedNotificationsChanged(QMap<uint,MeegoHandsetNotification*>);
    void notificationRemoved(QString);

friend class LedNoficationSink;
};

#endif // MEEGOHANDSETNOTIFICATIONPROVIDER_H
