#ifndef HEALTHPOINTS_H
#define HEALTHPOINTS_H

#include <iostream>

constexpr int MIN_HP = 0;
constexpr int DEFAULT_MAX_HP = 100;

class HealthPoints
{
    private:
        int m_hp;
        int m_maxHp;
    
    public:
        class InvalidArgument {};

        HealthPoints(int hp = DEFAULT_MAX_HP);

        HealthPoints& operator-(int hp);
        HealthPoints& operator+(int hp);
        HealthPoints& operator+=(int hp);
        HealthPoints& operator-=(int hp);

        bool operator==(const HealthPoints& other) const;
        bool operator!=(const HealthPoints& other) const;
        bool operator<(const HealthPoints& other) const;
        bool operator>(const HealthPoints& other) const;
        bool operator<=(const HealthPoints& other) const;
        bool operator>=(const HealthPoints& other) const;

        friend int operator-(int num, const HealthPoints& other);
        friend int operator+(int num, const HealthPoints& other);

        friend std::ostream& operator<<(std::ostream& os, const HealthPoints& hp);
};

#endif