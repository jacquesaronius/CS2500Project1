#include "intersectionpoint.h"

bool IntersectionPoint::add_sensor_in_range(Sensor * s)
{
    float d;

    auto it = sensors_in_range.find(s);


    if (it != sensors_in_range.end())
    {
        return true;
    }

    d = std::sqrt(pow(x() - s->x(), 2) + pow(y() - s->y(), 2));

    if (d < Sensor::RADIUS)
    {
        sensors_in_range.emplace(s);
        return true;
    }

    return false;
}

short IntersectionPoint::active_sensors_in_range() const
{
    short cnt = 0;


    for (auto it = sensors_in_range.begin(); it != sensors_in_range.end(); it++)
    {
        if ((*it)->active()) cnt++;
    }

    return cnt;
}

bool IntersectionPoint::operator ==(const IntersectionPoint & rhs) const
{
    return x() == rhs.x() && y() == rhs.y();
}
