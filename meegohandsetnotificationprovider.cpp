#include <QtDBus/QDBusConnection>
#include <notificationsystem/metatypedeclarations.h>
#include <notificationsystem/notificationsinkadaptor.h>
#include "lednotificationsink.h"
#include "mnotificationmanagerinterface.h"
#include "meegohandsetnotificationprovider.h"

MeegoHandsetNotificationProvider::MeegoHandsetNotificationProvider(QObject *parent) :
    QObject(parent),
    m_manager(new MNotificationManagerInterface("com.meego.core.MNotificationManager", "/notificationsinkmanager", QDBusConnection::sessionBus(), this)),
    m_sink(new LedNotificationSink(this))
{
    qDBusRegisterMetaType<Notification >(); // Avoid a name collision with Notification
    qDBusRegisterMetaType<QList<Notification > >();
    qDBusRegisterMetaType<NotificationGroup>();
    qDBusRegisterMetaType<QList<NotificationGroup> >();
    qDBusRegisterMetaType<NotificationParameters>();

    new NotificationSinkAdaptor(m_sink);
    QDBusConnection::sessionBus().registerService("com.mohammadag.led-event-notifier.MeegoHandsetNotificationSink");
    QDBusConnection::sessionBus().registerObject("/meegohandsetnotificationsink", m_sink);

    connect(m_sink, SIGNAL(incomingNotification(MeegoHandsetNotification*)),
            SLOT(newNotification(MeegoHandsetNotification*)));
    connect(m_sink, SIGNAL(trackedNotificationsChanged(QMap<uint,MeegoHandsetNotification*>)),
            this, SIGNAL(trackedNotificationsChanged(QMap<uint,MeegoHandsetNotification*>)));
    connect(m_sink, SIGNAL(notificationRemoved(QString)), this, SIGNAL(notificationRemoved(QString)));

    qDebug() << "Registering sink";
    m_manager->registerSink("com.mohammadag.led-event-notifier.MeegoHandsetNotificationSink", "/meegohandsetnotificationsink");
}

MeegoHandsetNotificationProvider::~MeegoHandsetNotificationProvider()
{

}


void MeegoHandsetNotificationProvider::newNotification(MeegoHandsetNotification* n)
{
    emit incomingNotification(n);
}
