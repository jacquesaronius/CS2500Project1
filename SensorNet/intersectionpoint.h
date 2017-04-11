#ifndef INTERSECTIONPOINT_H
#define INTERSECTIONPOINT_H
#include <set>
#include <cmath>
#include "sensor.h"


class IntersectionPoint
{
    short m_x;
    short m_y;
    std::set<Sensor *> sensors_in_range;
    public:
        IntersectionPoint(const short x, const short y) : m_x(x), m_y(y) { }
        short x() const { return m_x; }
        short y() const { return m_y; }
        bool add_sensor_in_range(Sensor *);
        short active_sensors_in_range() const;
        bool operator ==(const IntersectionPoint & rhs) const;
};

#endif // INTERSECTIONPOINT_H
