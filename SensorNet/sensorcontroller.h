#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include <vector>
#include <cmath>
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
std::vector <Sensor*> findOverlappingSensors(Sensor *a);
public:
    explicit SensorController(QObject *parent = 0);
    ~SensorController() { this->create(0); }
    Q_INVOKABLE Sensor * get_sensor(int n);
    int count() const;
    bool ifOverlap(const Sensor *a, const Sensor *b);
    void findIntersectionPoints(const Sensor* a, const Sensor *b);
signals:
    void update();
public slots:
    void create(int n);
};

#endif // SENSORCONTROLLER_H
