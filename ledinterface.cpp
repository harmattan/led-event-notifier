#include "ledinterface.h"

LEDInterface::LEDInterface(QObject *parent) :
    QObject(parent)
{
    m_interface = new QDBusInterface(MCE_SERVICE, MCE_REQUEST_PATH, MCE_REQUEST_IF,
                                     QDBusConnection::systemBus(), this);
}

LEDInterface::~LEDInterface()
{
    deactivateAllLedPatterns();
}

void LEDInterface::activateLed(QString ledPatternName)
{
    if (m_activatedLedPatterns.contains(ledPatternName))
        return;

    qDebug() << "Activating LED pattern:" << ledPatternName;
    m_interface->call(MCE_ACTIVATE_LED_PATTERN, ledPatternName);

    m_activatedLedPatterns.append(ledPatternName);
}

void LEDInterface::deactivateLed(QString ledPatternName)
{
    if (!m_activatedLedPatterns.contains(ledPatternName))
        return;

    qDebug() << "Deactivating LED pattern:" << ledPatternName;
    m_interface->call(MCE_DEACTIVATE_LED_PATTERN, ledPatternName);

    m_activatedLedPatterns.removeOne(ledPatternName);
}

void LEDInterface::deactivateAllLedPatterns()
{
    qDebug() << "Deactivating all LED patterns";
    foreach (QString patternName, m_activatedLedPatterns) {
        deactivateLed(patternName);
        m_activatedLedPatterns.removeOne(patternName);
    }
}
