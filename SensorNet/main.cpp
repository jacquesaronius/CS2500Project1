#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ctime>
#include <cstdlib>
#include <QQmlContext>
#include "sensorcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    SensorController controller;
    QObject * page1;
    qRegisterMetaType<Sensor *>("Sensor *");


    srand(time(NULL));
    engine.rootContext()->setContextProperty("controller", &controller);
    engine.rootContext()->setContextProperty("RADIUS", Sensor::RADIUS);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    page1 = engine.rootObjects()[0]->findChild<QObject *>("page1");
    QObject::connect(page1,
                     SIGNAL(create(int)),
                     &controller,
                     SLOT(create(int)));

    return app.exec();
}
