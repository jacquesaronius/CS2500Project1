#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include <vector>
#include "sensor.h"

class SensorController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count)

std::vector<Sensor *> sensors;
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
