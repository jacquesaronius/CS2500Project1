#include "sensor.h"


short Sensor::x() const
{
    return m_x;
}

short Sensor::y() const
{
    return m_y;
}

short Sensor::energy() const
{
    return m_energy;
}

bool Sensor::active()
{
    if (m_energy <= 0)
        m_active = false;
    return m_active;
}

void Sensor::activate()
{
    if (m_energy > 0)
        m_active = true;
}

void Sensor::deactivate()
{
    m_active = false;
}

void Sensor::toggle()
{
    active() ? deactivate() : activate();
}

void Sensor::init()
{
    m_x = rand() % Sensor::MAX_X + 1;
    m_y = rand() % Sensor::MAX_Y + 1;

}

float Sensor::area()
{
    float Area=(M_PI) * RADIUS * RADIUS;
    float Alpha;
    float Beta;
    float CW;
    float CL;
    float CornerA;
    if(m_x-RADIUS<MIN_X && m_y-RADIUS>=MIN_Y && m_y+RADIUS<=MAX_Y){
        Area=Area-pow(RADIUS, 2)/2 *(2*acos(1-(static_cast<float>(RADIUS-m_x)/RADIUS))-sin(2*acos(1-(static_cast<float>(RADIUS-m_x)/RADIUS))));
    }

    if(m_x+RADIUS>MAX_X && m_y-RADIUS>=MIN_Y && m_y+RADIUS<=MAX_Y){
        Area=Area-pow(RADIUS, 2)/2 *(2*acos(1-(static_cast<float>(m_x+RADIUS-MAX_X)/RADIUS))-sin(2*acos(1-(static_cast<float>(m_x+RADIUS-MAX_X)/RADIUS))));
    }

    if(m_y-RADIUS<MIN_Y && m_x-RADIUS>=MIN_X && m_x+RADIUS<=MAX_X){
        Area=Area-(pow(RADIUS, 2)/2 *(2*acos(1-(static_cast<float>(RADIUS-m_y)/RADIUS))-sin(2*acos(1-(static_cast<float>(RADIUS-m_y)/RADIUS)))));
    }

    if(m_y+RADIUS>MAX_Y && m_x-RADIUS>=MIN_X && m_x+RADIUS<=MAX_X){
        Area=Area-pow(RADIUS, 2)/2 *(2*acos(1-(static_cast<float>(m_y+RADIUS-MAX_Y)/RADIUS))-sin(2*acos(1-(static_cast<float>(m_y+RADIUS-MAX_Y)/RADIUS))));
    }

    if(m_x-RADIUS<MIN_X && m_y-RADIUS<MIN_Y)
    {
        Alpha=2*acos(1-(static_cast<float>(RADIUS-m_x)/RADIUS));
        Beta=2*acos(1-(static_cast<float>(RADIUS-m_y)/RADIUS));
        CW=RADIUS*sin(Alpha/2)-m_x;
        CL=RADIUS*sin(Beta/2)-m_y;
        if(CW<0)
            CornerA=0;
        else
            CornerA=CW*CL/2*(M_PI/2 *atan((CW-CL)*sin(M_PI)/(CW+CL+((CW-CL)*cos(M_PI)))));

        Area=Area-(pow(RADIUS, 2)/2*((Alpha)-sin(Alpha)))-(pow(RADIUS, 2)/2*((Beta)-sin(Beta)))+CornerA;
    }
    if(m_x+RADIUS>MAX_X && m_y-RADIUS<MIN_Y)
    {
        Alpha=2*acos(1-(static_cast<float>(m_x+RADIUS-MAX_X)/RADIUS));
        Beta=2*acos(1-(static_cast<float>(RADIUS-m_y)/RADIUS));
        CW=RADIUS*sin(Alpha/2)-(MAX_X-m_x);
        CL=RADIUS*sin(Beta/2)-m_y;
        if(CW<0)
            CornerA=0;
        else
            CornerA=CW*CL/2*(M_PI/2 *atan((CW-CL)*sin(M_PI)/(CW+CL+((CW-CL)*cos(M_PI)))));

        Area=Area-(pow(RADIUS, 2)/2*((Alpha)-sin(Alpha)))-(pow(RADIUS, 2)/2*((Beta)-sin(Beta)))+CornerA;
    }
    if(m_x-RADIUS<MIN_X && m_y+RADIUS>MAX_Y)
    {
        Alpha=2*acos(1-(static_cast<float>(RADIUS-m_x)/RADIUS));
        Beta=2*acos(1-(static_cast<float>(m_y+RADIUS-MAX_Y)/RADIUS));
        CW=RADIUS*sin(Alpha/2)-m_x;
        CL=RADIUS*sin(Alpha/2)-(MAX_Y-m_y);
        if(CW<0)
            CornerA=0;
        else
            CornerA=CW*CL/2*(M_PI/2 *atan((CW-CL)*sin(M_PI)/(CW+CL+((CW-CL)*cos(M_PI)))));

        Area=Area-(pow(RADIUS, 2)/2*((Alpha)-sin(Alpha)))-(pow(RADIUS, 2)/2*((Beta)-sin(Beta)))+CornerA;
    }
    if(m_x+RADIUS>MAX_X && m_y+RADIUS>MAX_Y)
    {
        Alpha=2*acos(1-(static_cast<float>(m_x+RADIUS-MAX_X)/RADIUS));
        Beta=2*acos(1-(static_cast<float>(m_y+RADIUS-MAX_Y)/RADIUS));
        CW=RADIUS*sin(Alpha/2)-(MAX_X-m_x);
        CL=RADIUS*sin(Beta/2)-(MAX_Y-m_y);
        if(CW<0)
            CornerA=0;
        else
            CornerA=CW*CL/2*(M_PI/2 *atan((CW-CL)*sin(M_PI)/(CW+CL+((CW-CL)*cos(M_PI)))));

        Area=Area-(pow(RADIUS, 2)/2*((Alpha)-sin(Alpha)))-(pow(RADIUS, 2)/2*((Beta)-sin(Beta)))+CornerA;
    }
    return Area;
}


void operator ++(Sensor s)
{
    if (s.active())
        s.m_energy--;
}
