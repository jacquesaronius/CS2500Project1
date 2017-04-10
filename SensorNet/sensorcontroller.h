#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include <vector>
#include "sensor.h"
#include "intersectionpoint.h"
#include "boundingbox.h"

class SensorController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count)

std::vector<Sensor *> sensors;
std::vector<IntersectionPoint *> intersections;
std::vector< std::vector< Sensor *> >  sensor_grid;
void add_intersection(short x, short y);
BoundingBox calc_bounding_box(short x, short y, short radius);
public:
    explicit SensorController(QObject *parent = 0);
    ~SensorController() { this->create(0); }
    Q_INVOKABLE Sensor * get_sensor(int n);
    int count() const;
signals:
    void update();
public slots:
    void create(int n);
};

#endif // SENSORCONTROLLER_H
