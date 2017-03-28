#ifndef SENSOR_H
#define SENSOR_H
#include <cstdlib>
#include <cmath>
#include <QObject>
class Sensor : QObject
{
    short m_x; // X position of sensor
    short m_y; // Y position of sensor
    short m_energy; // Current energy reserve
    bool m_active; // Active sensors status
    void init();


    public:
        static const short INITIAL_ENERGY = 300;  //Initial energy of sensor
        static const short MAX_X = 250; // Max coordinate on X axis
        static const short MAX_Y = 250; // Max coordinate on Y axis
        static const short MIN_X = 0; // Min coordinate on X axis
        static const short MIN_Y = 0; // Min coordinate on Y axis
        static const short RADIUS = 5; // Radius of sensor coverage
        static Sensor * create(const short n, bool active = false);
        short x() const;
        short y() const;
        short energy() const;
        bool active();
        void activate();
        void deactivate();
        void toggle();
        float area();
        friend void operator ++(Sensor);
        Sensor():m_energy(Sensor::INITIAL_ENERGY),m_active(false)
        {
            init();
        }

};

#endif // SENSOR_H
