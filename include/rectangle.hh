#pragma once

#include "vector.hh"

class Rectangle
{

private:
    Vector size[SIZE_R]; //Tablica wektora

public:
    Rectangle();

    Rectangle(Vector, double, double);

    Rectangle operator+(const Vector &v);

    Rectangle operator-(const Vector &v);

    Rectangle operator*(const double &tmp);

    Rectangle operator/(const double &tmp);

    const Vector &operator[](int index) const;

    Vector &operator[](int index);

    void move(const Vector &v);

    void compare();

};
 void Rectangle::compare()
 {
     double a1=size[0].size_vector(size[1]);
     double a2=size[2].size_vector(size[3]);
     double b1=size[0].size_vector(size[3]);
     double b2=size[2].size_vector(size[1]);
     if(a1==a2)
     {
         std::cout << "rowne" << std::endl; 
     }
     else
     {
               std::cout << "nie" << std::endl; 
     }
       if(b1==b2)
     {
         std::cout << "rowne" << std::endl; 
     }
     else
     {
               std::cout << "nie" << std::endl; 
     }
    std::cout << a1<<std::endl;
     std::cout << a2<<std::endl;
       std::cout << b1<<std::endl;
         std::cout << b2<<std::endl;       
 }
Rectangle::Rectangle()
{
    size[1][0] += 100;

    size[2][0] += 100;
    size[2][1] += 100;

    size[3][1] += 100;
}

Rectangle::Rectangle(Vector v, double h, double s)
{
    for (int i = 0; i < SIZE_R; i++)
        size[i] = v;

    size[1][0] += s;

    size[2][0] += s;
    size[2][1] += h;

    size[3][1] += h;
}

Rectangle Rectangle::operator+(const Vector &v)
{
    Rectangle result;
    for (int i = 0; i < SIZE_R; i++)
        result[i] = size[i] + v;
    return result;
}

Rectangle Rectangle::operator-(const Vector &v)
{
    Rectangle result;
    for (int i = 0; i < SIZE_R; i++)
        result[i] = size[i] - v;
    return result;
}

Rectangle Rectangle::operator*(const double &tmp)
{
    Rectangle result;
    for (int i = 0; i < SIZE_R; i++)
        result[i] = size[i] * tmp;
    return result;
}

Rectangle Rectangle::operator/(const double &tmp)
{
    Rectangle result;
    for (int i = 0; i < SIZE_R; i++)
        result[i] = size[i] / tmp;
    return result;
}

const Vector &Rectangle::operator[](int index) const
{
    return size[index];
}

Vector &Rectangle::operator[](int index)
{
    return size[index];
}

void Rectangle::move(const Vector &v)
{
    *this = *this + v;
}

std::ostream &operator<<(std::ostream &out, Rectangle const &tmp)
{
    for (int i = 0; i < SIZE_R; ++i)
    {
        out << tmp[i] << std::endl;
    }
    return out;
}