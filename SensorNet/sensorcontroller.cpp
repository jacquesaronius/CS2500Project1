#include "sensorcontroller.h"

SensorController::SensorController(QObject *parent) : QObject(parent)
{

}

void SensorController::add_intersection(short x, short y)
{
    IntersectionPoint * p = new IntersectionPoint(x, y);
    intersections.push_back(p);
}

void SensorController::create(int n)
{
    int i = 0;
    for (int j = 0; j < Sensor::MAX_X + 1; j++)
        for (int k = 0; k < Sensor::MAX_Y + 1; k++)
            grid_layout[j][k] = 0;

    while (!intersections.empty())
    {
        IntersectionPoint * p = intersections.back();
        intersections.pop_back();
        delete p;
    }
    while (!sensors.empty())
    {
        Sensor * t = sensors.back();
        sensors.pop_back();
        delete t;
    }
    while (i < n)
    {
        Sensor * t = new Sensor(this);
        grid_layout[t->x()][t->y()] = 1;
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
