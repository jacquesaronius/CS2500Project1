#include "sensorcontroller.h"

SensorController::SensorController(QObject *parent) : QObject(parent)
{

}

void SensorController::create(int n)
{
    int i = 0;

    while (!sensors.empty())
    {
        Sensor * t = sensors.back();
        sensors.pop_back();
        delete t;
    }
    while (i < n)
    {
        Sensor * t = new Sensor();
        sensors.push_back(t);
        i++;
    }

    update();
}

Sensor * SensorController::get_sensor(int n)
{
    return sensors.at(n);
}

int SensorController::count() const
{
    return sensors.size();
}
