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

void findIntersectionPoints(const Sensor *a, const Sensor* b)
{
    float distance=sqrt(pow((a->x() - b->x()),2) + pow((a->y() - b->y()), 2))/2;
    float height=sqrt(pow(a->RADIUS, 2)-pow(distance, 2));
    float x_temp=(static_cast<float>(b->x()-a->x())/2)+a->x();
    float y_temp=(static_cast<float>(b->y()-a->y())/2)+a->y();
    float x1=x_temp+height*static_cast<float>(b->y()-a->y())/(distance*2);
    float y1=y_temp-height*static_cast<float>(b->x()-a->x())/(distance*2);
    float x2=x_temp-height*static_cast<float>(b->y()-a->y())/(distance*2);
    float y2=y_temp+height*static_cast<float>(b->x()-a->x())/(distance*2);

    return ;
}

bool SensorController::ifOverlap(const Sensor *a, const Sensor *b)
{
    int distance=sqrt(pow((a->x() - b->x()),2) + pow((a->y() - b->y()), 2));

    if (distance < 2*(a->RADIUS) && distance <2*(b->RADIUS))
        return true;
    else
        return false;
}
