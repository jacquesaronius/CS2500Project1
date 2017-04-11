#include "sensorcontroller.h"

SensorController::SensorController(QObject *parent) : QObject(parent)
{

}

void SensorController::add_intersection(short x, short y)
{
    IntersectionPoint * p = new IntersectionPoint(x, y);
    for (unsigned int i = 0; i < intersections.size(); i ++)
        if (p)
    intersections.push_back(p);
}

void SensorController::create(int n)
{
    int i = 0;
    sensor_grid.clear();

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
    int distance=sqrt(pow((a->x() - x),2) + pow((a->y() - y), 2));

    if (distance < 2*(a->RADIUS))
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
    BoundingBox Box=calc_bounding_box(a->x(), a->y(), 2*Sensor::RADIUS);
    std::vector <Sensor*> Overlaps;

    for(int i=Box.left; i<Box.right+1;i++)
    {
        for(int j=Box.top; i<Box.bottom+1;i++)
        {
            if(sensor_grid[i][j]!=NULL)
                if(ifOverlap(a, i, j) == true)
                    Overlaps.push_back(sensor_grid[i][j]);
        }
    }
    return Overlaps;
}

void SensorController::RandomTopDown()
{

    for(auto it=sensors.begin(); it != sensors.end(); it++)
    {
        (*it)->activate();
    }
    do
    {
        int randomNumber=rand() % sensors.size();
        if(is_sensor_redundant(sensors[randomNumber])==true)
            sensors[randomNumber]->deactivate();

    }while(hasEnergy()==true && has_active()==true);
}

void SensorController::RandomBottomUp()
{

    do
    {
        int randomNumber=rand() % sensors.size();
        if(is_sensor_redundant(sensors[randomNumber])==true)
            sensors[randomNumber]->activate();

    }while(hasEnergy()==true && has_active()==true);
}

int SensorController::areaCovered()
{
    int AreaCovered=0;
    for(int i=0; i<50 ;i++)
    {
        for(int j=0; j<50;j++)
        {
            BoundingBox b=calc_bounding_box(i, j, Sensor::RADIUS);
            for(int k=b.left; k<b.right;k++)
            {
                for(int l=b.top; l<b.bottom; l++)
                {
                    if(sensor_grid[k][l] !=NULL && ifOverlap(sensor_grid[k][l], i, j)==true)
                        AreaCovered++;
                }
            }
        }
    }
    return AreaCovered;
}

bool SensorController::hasEnergy()
{
    bool energy=false;
    for(int i=0; (i<sensors.size()) ; i++){
        if(sensors[i]->energy()>0){
            energy=true;
        }
    }
    return energy;
}

void SensorController::run()
{
    if (mode() == ALL_ACTIVE)
    {
        //QtConcurrent::run((void)all_active);
    }
}

bool SensorController::is_sensor_redundant(const Sensor * sensor) const
{
    bool is_redundant = true;
    auto box = calc_bounding_box(sensor->x(),
                                 sensor->y(),
                                 Sensor::RADIUS);

    for (int i = box.left; i < box.right + 1 && is_redundant; i++)
    {
        for (int j = box.top; j < box.bottom + 1 && is_redundant; i++)
        {
            auto it = intersections.begin();

            for (; it != intersections.end() && is_redundant; it++)
            {
                is_redundant = (*it)->active_sensors_in_range() > 1;
            }
        }
    }

    return is_redundant;
}

void SensorController::callback()
{
    m_rounds++;
}

void SensorController::all_active()
{
    while(hasEnergy())
    {
        for (auto it = sensors.begin(); it != sensors.end(); it++)
        {
            (*it)->activate();
        }
    }
}

bool SensorController::has_active()
{
    bool active = false;
    for (auto it = sensors.begin(); it != sensors.end() && !active; it++)
    {
        active = (*it)->active();
    }

    return active;
}
