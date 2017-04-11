#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include <vector>
#include "sensor.h"
#include "intersectionpoint.h"
#include "boundingbox.h"
#include <QDebug>


class SensorController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(short rounds READ rounds)
    Q_PROPERTY(short delay READ delay WRITE setDelay)
    Q_PROPERTY(short mode READ mode WRITE setMode)
    Q_PROPERTY(QString status READ status)


    short m_rounds = 0;
    short m_delay = 0;
    short m_mode = ALL_ACTIVE;
    QString m_status;
    std::vector<Sensor *> sensors;
    std::vector<IntersectionPoint *> intersections;
    std::vector< std::vector< Sensor *> >  sensor_grid;
    void add_intersection(short x, short y);
    BoundingBox calc_bounding_box(short x, short y, short radius);
    void callback();
public:
    static const short ALL_ACTIVE = 0;
    static const short TOP_DOWN_RANDOM = 1;
    static const short BOTTOM_UP_RANDOM = 2;
    static const short GREEDY = 3;

    explicit SensorController(QObject *parent = 0);
    ~SensorController() { this->create(0); }
    Q_INVOKABLE Sensor * get_sensor(int n);
    int count() const;
    short rounds() const { return m_rounds; }
    short delay() const { return m_delay; }
    void setDelay(const short delay) { m_delay = delay; }
    short mode() const { return m_mode; }
    void setMode(const short mode) { m_mode = mode; }
    QString status() const { return QString(m_status); }
    bool is_sensor_redundant(const Sensor *) const;
signals:
    void update();
public slots:
    void create(int n);
    void run();
};

#endif // SENSORCONTROLLER_H
