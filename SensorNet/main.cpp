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


    srand(time(NULL));
    engine.rootContext()->setContextProperty("controller", &controller);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    QObject::connect(engine.rootObjects()[0],
                     SIGNAL(create(int)),
                     &controller,
                     SLOT(create(int)));

    return app.exec();
}
