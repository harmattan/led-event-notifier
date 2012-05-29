QT       += core gui dbus
QT -= gui

TARGET = led-event-notifier
TEMPLATE = app

CONFIG += notificationsystem

INCLUDEPATH += /usr/include/meegotouch

CONFIG += link_pkgconfig
PKGCONFIG += meegotouch meegotouch-boostable

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/postinst \
    qtc_packaging/debian_harmattan/prerm \
    led-event-notifier.conf

HEADERS += \
    lednotificationsink.h \
    mnotificationmanagerinterface.h \
    meegohandsetnotification.h \
    meegohandsetnotificationprovider.h \
    lednotificationwatcher.h \
    ledinterface.h

SOURCES += \
    lednotificationsink.cpp \
    mnotificationmanagerinterface.cpp \
    meegohandsetnotification.cpp \
    main.cpp \
    meegohandsetnotificationprovider.cpp \
    lednotificationwatcher.cpp \
    ledinterface.cpp

contains(MEEGO_EDITION,harmattan) {
    target.path = /usr/bin
    INSTALLS += target

    autostart.path = /etc/init/apps
    autostart.files = led-event-notifier.conf

    INSTALLS += autostart
}
