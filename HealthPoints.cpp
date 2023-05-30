#include "HealthPoints.h"

HealthPoints::HealthPoints(int hp)
{
    if(hp <= 0) {
        throw HealthPoints::InvalidArgument();
    }

    m_maxHp = hp;
    m_hp = hp;
}

HealthPoints& HealthPoints::operator-(int hp)
{
    m_hp -= hp;

    if(m_hp < MIN_HP) {
        m_hp = MIN_HP;
    }

    if(m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }

    return *this;
}

HealthPoints& HealthPoints::operator+(int hp)
{
    m_hp += hp;

    if(m_hp < MIN_HP) {
        m_hp = MIN_HP;
    }

    if(m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }

    return *this;
}

HealthPoints& HealthPoints::operator+=(int hp)
{
    m_hp += hp;

    if(m_hp < MIN_HP) {
        m_hp = MIN_HP;
    }

    if(m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }

    return *this;
}

HealthPoints& HealthPoints::operator+=(int hp)
{
    m_hp += hp;

    if(m_hp < MIN_HP) {
        m_hp = MIN_HP;
    }

    if(m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }

    return *this;
}

bool HealthPoints::operator==(const HealthPoints& other) const
{
    return m_hp == other.m_hp;
}

bool HealthPoints::operator!=(const HealthPoints& other) const
{
    return m_hp != other.m_hp;
}

bool HealthPoints::operator<(const HealthPoints& other) const
{
    return m_hp < other.m_hp;
}

bool HealthPoints::operator>(const HealthPoints& other) const
{
    return m_hp > other.m_hp;
}

bool HealthPoints::operator<=(const HealthPoints& other) const
{
    return m_hp <= other.m_hp;
}

bool HealthPoints::operator>=(const HealthPoints& other) const
{
    return m_hp >= other.m_hp;
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
    os << hp.m_hp << "(" << hp.m_maxHp << ")";
    return os;
}