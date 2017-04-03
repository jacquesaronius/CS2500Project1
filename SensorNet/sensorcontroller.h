#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include <vector>
#include "sensor.h"

class SensorController : public QObject
{
    Q_OBJECT

std::vector<Sensor *> sensors;
public:
    explicit SensorController(QObject *parent = 0);
    ~SensorController() { this->create(0); }
    Sensor * get_sensor(int n);
    int Count() const;
signals:
    void update();
public slots:
    void create(int n);
};

#endif // SENSORCONTROLLER_H
