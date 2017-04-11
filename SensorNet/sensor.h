        #ifndef SENSOR_H
        #define SENSOR_H
        #include <cstdlib>
        #include <cmath>
        #include <QObject>
        class Sensor : public QObject
        {
            short m_x; // X position of sensor
            short m_y; // Y position of sensor
            short m_energy; // Current energy reserve
            bool m_active; // Active sensors status
            void init();

            Q_OBJECT
            Q_PROPERTY(short x READ x)
            Q_PROPERTY(short y READ y)
            Q_PROPERTY(short energy READ energy)
            Q_PROPERTY(bool active READ active)
            Q_PROPERTY(float area READ area)
            public:
                static const short INITIAL_ENERGY = 300;  //Initial energy of sensor
                static const short MAX_X = 50; // Max coordinate on X axis
                static const short MAX_Y = 50; // Max coordinate on Y axis
                static const short MIN_X = 0; // Min coordinate on X axis
                static const short MIN_Y = 0; // Min coordinate on Y axis
                static const short RADIUS = 5; // Radius of sensor coverage
                short x() const;
                short y() const;
                short energy() const;
                bool active();
                float area();
                Q_INVOKABLE void activate();
                Q_INVOKABLE void deactivate();
                Q_INVOKABLE void toggle();
                friend void operator --(Sensor &);

                explicit Sensor(QObject *parent = 0):
                    QObject(parent),
                    m_energy(Sensor::INITIAL_ENERGY),
                    m_active(false)
                {
                    init();
                }

                ~Sensor()
                {
                    qDebug("Sensor object destroyed");
                }

        };

        #endif // SENSOR_H
