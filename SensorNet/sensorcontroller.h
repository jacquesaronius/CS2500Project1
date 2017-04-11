#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include <QObject>
#include <vector>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include "sensor.h"
#include "intersectionpoint.h"
#include "boundingbox.h"
#include <QDebug>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QString>
class SensorController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(short rounds READ rounds)
    Q_PROPERTY(short delay READ delay WRITE setDelay)
    Q_PROPERTY(short mode READ mode WRITE setMode)
    Q_PROPERTY(QString status READ status)



    std::vector <Sensor*> findOverlappingSensors(Sensor *a);
    bool hasEnergy();
    short m_rounds = 0;
    short m_delay = 0;
    short m_mode = ALL_ACTIVE;

    void RandomBottomUp();
    void RandomTopDown();
    QString m_status;
    std::vector<QString> reports;
    std::vector<Sensor *> sensors;
    std::vector<IntersectionPoint *> intersections;
    std::vector< std::vector< Sensor *> >  sensor_grid;
    std::vector<Sensor *> pos_coverage(short x, short y);
    void add_intersection(short x, short y);
    BoundingBox calc_bounding_box(const short x,
                                  const short y,
                                  const short radius) const;
    void callback(bool);
    void discharge_all();

    void all_active();
    void find_all_intersections();
    void activate_all_sensors();
    void update_report_data(short id);
    void write_report(short id);
    void update_all_reports();
    void write_all_reports();
    bool pos_is_covered(short x, short y);
    bool network_is_alive();
public:
    static const short ALL_ACTIVE = 0;
    static const short TOP_DOWN_RANDOM = 1;
    static const short BOTTOM_UP_RANDOM = 2;
    static const short GREEDY = 3;
    static const short REPORT_ALIVE_SENSORS = 0;
    static const short REPORT_ACTIVE_SENSORS = 1;
    static const short REPORT_COVERAGE = 2;
    static const short REPORT_ENERGY = 3;

    explicit SensorController(QObject *parent = 0);
    ~SensorController() { this->create(0); }
    Q_INVOKABLE Sensor * get_sensor(int n);
    int count() const;
    int areaCovered();
    bool ifOverlap(const Sensor *a, const int x, const int y);
    bool has_active();

    bool ifOverlap(const Sensor *a, const Sensor *b);
    void findIntersectionPoints(const Sensor* a, const Sensor *b);
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
