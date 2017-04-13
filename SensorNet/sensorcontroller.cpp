#include "sensorcontroller.h"

SensorController::SensorController(QObject *parent) : QObject(parent)
{

}

bool SensorController::network_is_alive()
{
    const short THRESHOLD = 50;
    short percentage = (static_cast<float>(areaCovered())
                        / (Sensor::MAX_X * Sensor::MAX_Y) * 100);

    return percentage >= THRESHOLD;
}

void SensorController::discharge_all()
{
    for (auto it = active_sensors.begin(); it != active_sensors.end(); it++)
    {
        --(*(*it));
    }
}

void SensorController::add_intersection(short x, short y)
{
    IntersectionPoint * p = new IntersectionPoint(x, y);
    std::vector<Sensor *> t;
    for (unsigned int i = 0; i < intersections.size(); i ++)
        if (*p == *intersections[i])
            return;
    t = pos_coverage(x, y);
    for (auto i = t.begin(); i != t.end(); i++)
        p->add_sensor_in_range(*i);
    intersections.push_back(p);
}

void SensorController::create(int n)
{
    int i = 0;
    sensor_grid.clear();
    reports.clear();
    for (int j = 0; j < REPORT_ENERGY + 1; j++)
    {
        QString r;
        reports.push_back(r);
    }

    for (int j = 0; j < Sensor::MAX_X + 1; j++)
    {

        std::vector<Sensor *> y;
        for (int k = 0; k < Sensor::MAX_Y + 1; k++)
            y.push_back(NULL);

        sensor_grid.push_back(y);
    }

    while (!intersections.empty())
    {
        IntersectionPoint * p = intersections.back();
        intersections.pop_back();
        delete p;
    }
    while (!sensors.empty())
    {
        Sensor * t = sensors.back();
        sensors.pop_back();
        delete t;
    }
    while (i < n)
    {
        Sensor * t = new Sensor(this);
        sensor_grid[t->x()][t->y()] = t;
        sensors.push_back(t);
        i++;
    }

    update();
}

Sensor * SensorController::get_sensor(int n)
{
    return sensors.at(n);
}

int SensorController::count() const
{
    return sensors.size();
}

void SensorController::findIntersectionPoints(const Sensor *a, const Sensor* b)
{
    float distance=sqrt(pow((a->x() - b->x()),2) + pow((a->y() - b->y()), 2))/2;
    float height=sqrt(pow(a->RADIUS, 2)-pow(distance, 2));
    float x_temp=(static_cast<float>(b->x()-a->x())/2)+a->x();
    float y_temp=(static_cast<float>(b->y()-a->y())/2)+a->y();
    float x1=x_temp+height*static_cast<float>(b->y()-a->y())/(distance*2);
    float y1=y_temp-height*static_cast<float>(b->x()-a->x())/(distance*2);
    float x2=x_temp-height*static_cast<float>(b->y()-a->y())/(distance*2);
    float y2=y_temp+height*static_cast<float>(b->x()-a->x())/(distance*2);

    add_intersection(x1, y1);
    add_intersection(x2, y2);

    return;
}

bool SensorController::ifOverlap(const Sensor *a, const int x, const int y)
{
    float distance=sqrt(static_cast<float>(pow((a->x() - x),2) + pow((a->y() - y), 2)));

    if (distance < 2*(Sensor::RADIUS))
        return true;
    else
        return false;
}


BoundingBox SensorController::calc_bounding_box(const short x,
                                                const short y,
                                                const short radius) const
{
    BoundingBox b;
    b.left = x - radius >= Sensor::MIN_X ? x - radius : Sensor::MIN_X;
    b.right = x + radius <= Sensor::MAX_X ? x + radius : Sensor::MAX_X;
    b.top =  y - radius >= Sensor::MIN_Y ? y - radius : Sensor::MIN_Y;
    b.bottom = y + radius <= Sensor::MAX_Y ? y + radius : Sensor::MAX_Y;

    return b;
}

std::vector <Sensor*> SensorController::findOverlappingSensors(Sensor *a)
{
    std::vector <Sensor*> Overlaps;

    for (auto i = active_sensors.begin(); i != active_sensors.end(); i++)

    if((*i)->active() && ifOverlap(a, (*i)->x(), (*i)->y()) == true)
          Overlaps.push_back(*i);

    return Overlaps;
}

int SensorController::numOverlap(Sensor *a)
{
    int Overlaps;

    for (auto i = active_sensors.begin(); i != active_sensors.end(); i++)
    {
        if(ifOverlap(a, (*i)->x(), (*i)->y()) == true)
            Overlaps++;
    }
    return Overlaps;
}

void SensorController::RandomTopDown()
{



    activate_all_sensors();
    do
    {

        find_all_intersections();
        int randomNumber=rand() % active_sensors.size();
        if(is_sensor_redundant(active_sensors[randomNumber])==true)
            active_sensors[randomNumber]->deactivate();
        discharge_all();
        if (!network_is_alive())
            activate_all_sensors();
        callback(true);

    }while(network_is_alive());

    callback(false);
}

void SensorController::RandomBottomUp()
{

    bool start_tracking_life = false;
    bool alive = true;
    do
    {

        if (!start_tracking_life && network_is_alive())
            start_tracking_life = true;
        if (start_tracking_life)
            alive = network_is_alive();
        int randomNumber=rand() % active_sensors.size();
        if(is_sensor_redundant(active_sensors[randomNumber])==false)
            active_sensors[randomNumber]->activate();
        discharge_all();
        callback(true);

    }while(hasEnergy() && has_active() && alive);

    callback(false);
}

int SensorController::areaCovered()
{
    int AreaCovered=0;
    for(int i=0; i<Sensor::MAX_X;i++)
    {
        for(int j=0; j<Sensor::MAX_Y; j++)
        {
            if (pos_is_covered(i, j)) AreaCovered++;
        }
    }
    return AreaCovered;
}

bool SensorController::hasEnergy()
{
    bool energy=false;
    for(uint i=0; (i<sensors.size()) ; i++){
        if(sensors[i]->energy()>0){
            energy=true;
        }
    }
    return energy;
}

void SensorController::run()
{

    m_rounds = 0;
    m_status = "Simulation Started.";

    if (m_mode == ALL_ACTIVE)
    {
        QtConcurrent::run(this, &SensorController::all_active);
    }
    else if (m_mode == TOP_DOWN_RANDOM)
    {
        QtConcurrent::run(this, &SensorController::RandomTopDown);
    }
    else if (m_mode == BOTTOM_UP_RANDOM)
    {
        QtConcurrent::run(this, &SensorController::RandomBottomUp);
    }
    else if (m_mode == GREEDY)
    {
        QtConcurrent::run(this, &SensorController::Greedy);
    }
}

bool SensorController::is_sensor_redundant(const Sensor * sensor) const
{
    unsigned int is_redundant = 0;

    std::vector<IntersectionPoint *> candidates;

    auto it = intersections.begin();
    for (; it != intersections.end(); it++)
    {
        int d = sqrt(pow((sensor->x() - (*it)->x()),2)
            + pow((sensor->y() - (*it)->y()), 2));
        if (d < Sensor::RADIUS)
        {
            candidates.push_back(*it);
        }
    }



    for (auto it = candidates.begin(); it != candidates.end(); it++)
    {
        if ((*it)->active_sensors_in_range() > 1)
            is_redundant++;
    }


    return candidates.size() > 0 && candidates.size() == is_redundant;
}

void SensorController::callback(bool running)
{

    if(running)
    {
        m_rounds++;
        update_all_reports();
        m_status = QString("Simulation Started: %1 intersections created")
                .arg(intersections.size());
        update();
        QThread::msleep(m_delay);
    }
    else
    {
        write_all_reports();
        m_status = "Simulation complete.";
        update();

    }

}

void SensorController::Greedy()
{


    activate_all_sensors();
    do
    {
        short index = -1;
        unsigned short max = 0;
        find_all_intersections();
        for (unsigned short i = 0; i < active_sensors.size(); i++)
        {
            auto s = active_sensors[i];
            if((s)->active() &&
                    findOverlappingSensors(s).size() > max
                    && is_sensor_redundant(s))
            {
                max = findOverlappingSensors(s).size();
                index = i;
            }
        }
        if (index > -1 && max > 0)
            active_sensors[index]->deactivate();
        discharge_all();
        if (!network_is_alive())
        {
            activate_all_sensors();

        }
        callback(true);
    } while ((network_is_alive()));
    callback(false);
}

void SensorController::all_active()
{
    activate_all_sensors();

    while (hasEnergy())
    {

        discharge_all();
        callback(true);
    }
    callback(false);
}

bool SensorController::has_active()
{
    bool active = false;
    for (auto it = active_sensors.begin(); it != active_sensors.end() && !active; it++)
    {
        active = (*it)->active();
    }

    return active;
}

void SensorController::find_all_intersections()
{
    clear_intersections();
    for(auto i=active_sensors.begin(); i != active_sensors.end(); i++)
    {
        if ((*i)->active())
        {
            auto ov = findOverlappingSensors(*i);
            for (auto j = ov.begin(); j != ov.end(); j++)
            {
                findIntersectionPoints(*i, *j);
            }
        }
    }
}

void SensorController::activate_all_sensors()
{
    active_sensors.clear();
    for(auto i=sensors.begin(); i != sensors.end(); i++)
    {

        (*i)->activate();
        if ((*i)->active())
            active_sensors.push_back(*i);
    }

}

void SensorController::update_report_data(short id)
{
    switch (id)
    {
        case REPORT_ALIVE_SENSORS:
        {
            short count = 0;
            for (auto i = sensors.begin(); i != sensors.end(); i++)
            {
                if ((*i)->energy() > 0)
                    count++;
            }
            reports[id].append(QString("%1,%2\n")
                .arg(m_rounds)
                .arg(static_cast<float>(count)));

            break;
        }
        case REPORT_ACTIVE_SENSORS:
        {
            short count = 0;
            for (auto i = sensors.begin(); i != sensors.end(); i++)
            {
                if ((*i)->active())
                    count++;
            }
            reports[id].append(QString("%1,%2\n")
                    .arg(m_rounds)
                    .arg(static_cast<float>(count)));
            break;
        }
        case REPORT_COVERAGE:
        {
            int coverage = areaCovered();
            reports[id].append(QString("%1,%2\n")
                    .arg(m_rounds)
                    .arg((static_cast<float>(coverage)
                         / (Sensor::MAX_X * Sensor::MAX_Y)) * 100));
            break;

        }
        case REPORT_ENERGY:
        {
            float energy = 0;
            for (auto i = sensors.begin(); i != sensors.end(); i++)
            {
                energy = energy + (*i)->energy();
            }
            energy = energy / sensors.size();

            reports[id].append(QString("%1,%2\n")
                    .arg(m_rounds)
                    .arg(energy));
            break;
        }
    }

}

void SensorController::write_report(short id)
{
    auto t = time(NULL);
    QString mode_names[4]
    {
        "all_active",
        "top_down",
        "bottom_up",
        "greedy"
    };

    QString file_names[4] =
    {
        "report_alive_sensors",
        "report_active_sensors",
        "report_coverage",
        "report_energy"
    };

    QString file_name = QString("%1_%2_%3.csv")
            .arg(t)
            .arg(mode_names[m_mode])
            .arg(file_names[id]);

    QFile file(file_name);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(& file);
        stream << reports[id];
        file.close();
    }
}

void SensorController::update_all_reports()
{
    for (int i = REPORT_ALIVE_SENSORS; i < REPORT_ENERGY + 1; i++)
    {
        update_report_data(i);
    }
}

void SensorController::write_all_reports()
{
    for (int i = REPORT_ALIVE_SENSORS; i < REPORT_ENERGY + 1; i++)
    {
        write_report(i);
    }
}

std::vector<Sensor *> SensorController::pos_coverage(short x, short y, bool first)
{
    std::vector<Sensor *> coverage;
    for (auto i = active_sensors.begin(); i != active_sensors.end(); i++)
    {
        auto s = (*i);
        if (s->active())
        {
            int distance = sqrt(pow((s->x() - x),2) + pow((s->y() - y), 2));

            if (distance < Sensor::RADIUS)
            {
                coverage.push_back(s);
                if (first)
                    return coverage;
            }
        }

    }
    return coverage;
}

bool SensorController::pos_is_covered(short x, short y)
{
    return pos_coverage(x, y, true).size() > 0;
}

void SensorController::clear_intersections()
{
    while (!intersections.empty())
    {
        auto p = intersections.back();
        delete p;
        intersections.pop_back();
    }
}
