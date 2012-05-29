#include "lednotificationwatcher.h"
#include "meegohandsetnotification.h"

LedNotificationWatcher::LedNotificationWatcher(QObject *parent) :
    QObject(parent),
    m_interface(new LEDInterface(this))
{
    MeegoHandsetNotificationProvider *provider = new MeegoHandsetNotificationProvider(this);
    connect(provider, SIGNAL(trackedNotificationsChanged(QMap<uint,MeegoHandsetNotification*>)),
            this, SLOT(onNotificationListChanged(QMap<uint,MeegoHandsetNotification*>)));
    connect(provider, SIGNAL(incomingNotification(MeegoHandsetNotification*)),
            this, SLOT(onIncomingNotification(MeegoHandsetNotification*)));
    connect(provider, SIGNAL(notificationRemoved(QString)), this, SLOT(onNotificationRemoved(QString)));
}

void LedNotificationWatcher::onNotificationListChanged(QMap<uint,MeegoHandsetNotification*> map)
{
    if (map.count() == 0) {
        m_interface->deactivateAllLedPatterns();
    }
}

void LedNotificationWatcher::onNotificationRemoved(QString notificationType)
{
    QString ledPattern = getPatternForType(notificationType);
    decrementPatternUsageCount(ledPattern);
}

QString LedNotificationWatcher::getPatternForType(QString notificationType)
{
    QString settingsKey = notificationType + "/mce-pattern-name";

    QString ledPatternName;

    if (QSettings().contains(settingsKey)) {
        ledPatternName = QSettings().value(settingsKey).toString();
    } else {
        ledPatternName = MISC_LED_PATTERN;
    }

    qDebug() << "Pattern for notification type" << notificationType << "is" << ledPatternName;
    return ledPatternName;
}

bool LedNotificationWatcher::shouldFireForType(QString notificationType)
{
    QString activeKey = notificationType + "/active";

    bool shouldFireLED = true;

    if (QSettings().contains(activeKey))
        shouldFireLED = QSettings().value(activeKey, true).toBool();

    qDebug() << "Notification type active:" << shouldFireLED;

    return shouldFireLED;
}

void LedNotificationWatcher::onIncomingNotification(MeegoHandsetNotification *notification)
{
    QString typeString = notification->typeString();
    qDebug() << "Incoming notification" << typeString;

    if (!shouldFireForType(typeString))
        return;

    QString ledPatternName = getPatternForType(typeString);

    incrementPatternUsageCount(ledPatternName);

    if (!m_patternUsageName.contains(typeString))
        m_patternUsageName.insert(typeString, ledPatternName);
}

int LedNotificationWatcher::patternUsedCount(QString pattern)
{
    return m_patternUsageCount.value(pattern);
}

void LedNotificationWatcher::incrementPatternUsageCount(QString pattern)
{
    m_interface->activateLed(pattern);
    int currentValue = patternUsedCount(pattern);
    m_patternUsageCount.insert(pattern, currentValue++);
}

void LedNotificationWatcher::decrementPatternUsageCount(QString pattern)
{
    int currentValue = patternUsedCount(pattern);
    if (currentValue == 0)
        return;

    m_patternUsageCount.insert(pattern, currentValue--);

    if (m_patternUsageCount.value(pattern) == 0)
        m_interface->deactivateLed(pattern);
}
