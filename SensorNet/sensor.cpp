#include "sensor.h"


short Sensor::x() const
{
    return m_x;
}

short Sensor::y() const
{
    return m_y;
}

short Sensor::energy() const
{
    return m_energy;
}

int Sensor::overlap() const
{
    return m_overlap;
}

void Sensor::setoverlap(const int a)
{
    m_overlap=a;
}

bool Sensor::active()
{
    if (m_energy <= 0)
        m_active = false;
    return m_active;
}

void Sensor::activate()
{
    if (m_energy > 0)
        m_active = true;
}

void Sensor::deactivate()
{
    m_active = false;
}

void Sensor::toggle()
{
    active() ? deactivate() : activate();
}

void Sensor::init()
{
    m_x = rand() % Sensor::MAX_X + 1;
    m_y = rand() % Sensor::MAX_Y + 1;

}

float Sensor::area()
{
    return(M_PI * RADIUS * RADIUS);
}

void operator --(Sensor & s)
{
    if (s.active())
        s.m_energy--;
}
