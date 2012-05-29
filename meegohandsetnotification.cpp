#include "meegohandsetnotification.h"

MeegoHandsetNotification::MeegoHandsetNotification(const Notification& n, QObject *parent) :
    QObject(parent), _n(n)
{
}

MeegoHandsetNotification::NotificationType MeegoHandsetNotification::type() const
{
    QString eventType = _n.parameters().value("eventType").toString();
    if (eventType == "email.arrived") {
        return EmailNotification;
    } else if (eventType == "x-nokia.call.missed") {
        return MissedCallNotification;
    } else if (eventType == "x-nokia.messaging.im") {
        return ImNotification;
    } else if (eventType == "x-nokia.messaging.sms") {
        return SmsNotification;
    } else if (eventType == "x-nokia.messaging.mms") {
        return MmsNotification;
    } else {
        return OtherNotification;
    }
}

QString MeegoHandsetNotification::typeString() const
{
    return _n.parameters().value("eventType").toString();
}

uint MeegoHandsetNotification::count() const
{
    return _n.parameters().value("count").toUInt();
}

QDateTime MeegoHandsetNotification::dateTime() const
{
    const uint timestamp = _n.parameters().value("timestamp").toUInt();
    return QDateTime::fromTime_t(timestamp);
}

QString MeegoHandsetNotification::title() const
{
    return _n.parameters().value("summary").toString();
}

QString MeegoHandsetNotification::body() const
{
    return _n.parameters().value("body").toString();
}

void MeegoHandsetNotification::activate()
{
    // TODO Actually do something
}

void MeegoHandsetNotification::dismiss()
{
    // TODO Actually dismiss
}

void MeegoHandsetNotification::changeTo(const Notification &notification)
{
    uint oldCount = count();
    QDateTime oldDateTime = dateTime();
    QString oldTitle = title();
    QString oldBody = body();
    _n = notification;
    if (oldCount != count()) {
        emit countChanged();
    }
    if (oldDateTime != dateTime()) {
        emit dateTimeChanged();
        emit displayTimeChanged();
    }
    if (oldTitle != title()) {
        emit titleChanged();
    }
    if (oldBody != body()) {
        emit bodyChanged();
    }
    emit changed();
}

void MeegoHandsetNotification::remove()
{
    emit dismissed();
}
