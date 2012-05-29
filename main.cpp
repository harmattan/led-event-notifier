#include <QApplication>
#include <QDBusConnection>

#include "meegohandsetnotificationprovider.h"
#include "lednotificationwatcher.h"

void msg_handler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("DEBUG: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("WARNING: %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt = QString("CRITICAL: %1").arg(msg);
        break;
    case QtFatalMsg:
        txt = QString("FATAL: %1").arg(msg);
        abort();
    }

    QFile logFile("/tmp/led-event-notifier");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&logFile);
    ts << QDateTime::currentDateTime().toString() << " " << txt << endl;
    QTextStream stdOut(stdout);
    stdOut << txt << endl;
    ts.flush();
    logFile.close();
}

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("led-event-notifier");
    QApplication::setApplicationVersion("0.1");
    QApplication::setOrganizationName("MohammadAG");

    QApplication application(argc, argv);

    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.");
    }

    LedNotificationWatcher watcher;
    qDebug() << "LED Event Notifier started";

    return application.exec();
}
