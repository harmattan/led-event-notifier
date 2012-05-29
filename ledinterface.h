#ifndef LEDINTERFACE_H
#define LEDINTERFACE_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDebug>
#include <QStringList>
#include <mce/mode-names.h>
#include <mce/dbus-names.h>

#define MISC_LED_PATTERN "PatternCommunication"

class LEDInterface : public QObject
{
    Q_OBJECT
public:
    explicit LEDInterface(QObject *parent = 0);
    ~LEDInterface();

public slots:
    void activateLed(QString ledPatternName);
    void deactivateLed(QString ledPatternName);
    void deactivateAllLedPatterns();

private:
    QDBusInterface *m_interface;
    bool m_isLedActivated;

    QStringList m_activatedLedPatterns;
};

#endif // LEDINTERFACE_H
