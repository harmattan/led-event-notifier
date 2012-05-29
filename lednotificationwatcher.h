#ifndef LEDNOTIFICATIONWATCHER_H
#define LEDNOTIFICATIONWATCHER_H

#include <QObject>
#include <QMultiMap>
#include "meegohandsetnotificationprovider.h"
#include "meegohandsetnotification.h"
#include "ledinterface.h"

class LedNotificationWatcher : public QObject
{
    Q_OBJECT
public:
    explicit LedNotificationWatcher(QObject *parent = 0);
    
signals:
    
public slots:

private:
    LEDInterface *m_interface;
    // Assign notification type to led pattern type;
    QMap<QString,int> m_patternUsageCount;
    QMap<QString,QString> m_patternUsageName;
    QString getPatternForType(QString notificationType);
    bool shouldFireForType(QString notificationType);
    void incrementPatternUsageCount(QString pattern);
    int patternUsedCount(QString pattern);
    void decrementPatternUsageCount(QString pattern);

private slots:
    void onNotificationListChanged(QMap<uint,MeegoHandsetNotification*>);
    void onIncomingNotification(MeegoHandsetNotification *notification);
    void onNotificationRemoved(QString notificationType);
};

#endif // LEDNOTIFICATIONWATCHER_H
