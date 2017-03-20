#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    srand(time(NULL));
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
