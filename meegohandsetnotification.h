#ifndef MEEGOHANDSETNOTIFICATION_H
#define MEEGOHANDSETNOTIFICATION_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <notificationsystem/notification.h>

class LedNotificationSink;

class MeegoHandsetNotification : public QObject
{
    Q_OBJECT
    Q_ENUMS(NotificationType)

public:
    explicit MeegoHandsetNotification(const Notification& n, QObject *parent = 0);
    enum NotificationType {
        OtherNotification = 0,
        CallNotification,
        MissedCallNotification,
        SmsNotification,
        MmsNotification,
        ImNotification,
        EmailNotification,
        CalendarNotification,
        WeatherNotification,
        TypeCount
    };

    NotificationType type() const;
    QString typeString() const;
    uint count() const;
    QDateTime dateTime() const;
    QString title() const;
    QString body() const;
    void activate();
    void dismiss();

protected:
    void changeTo(const Notification& notification);
    void remove();

protected:
    Notification _n;

signals:
    void countChanged();
    void dateTimeChanged();
    void displayTimeChanged();
    void titleChanged();
    void bodyChanged();
    void changed();
    void dismissed();
    

friend class LedNotificationSink;
};

#endif // MEEGOHANDSETNOTIFICATION_H
