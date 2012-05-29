#include "mnotificationmanagerinterface.h"

/*
 * Implementation of interface class MNotificationManagerInterface
 */

MNotificationManagerInterface::MNotificationManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

MNotificationManagerInterface::~MNotificationManagerInterface()
{
}
