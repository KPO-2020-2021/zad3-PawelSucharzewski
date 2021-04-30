#pragma once

#include "size.hh"
#include "vector.hh"
#include "rectangle.hh"
#include <iostream>
#include <cstdlib>

class Matrix
{

private:
    double value[SIZE][SIZE]; // Wartosci macierzy

public:
    Matrix(double[SIZE][SIZE]); // Konstruktor klasy

    Matrix(); // Konstruktor klasy

    Vector operator*(Vector tmp); // Operator mnożenia przez wektor

    Rectangle operator*(Rectangle tmp);

    Matrix operator+(Matrix tmp);

    double &operator()(unsigned int row, unsigned int column);

    const double &operator()(unsigned int row, unsigned int column) const;

    void rotation(double angle, Rectangle &tmp);
    void determinant()
    {
Matrix a=*this;
double ratio;
     for(int i=0;i<2;i++)
	 {
		  if(a(i,i) == 0.0)
		  {
			   std::cout<<"Mathematical Error!";
			   exit(0);
		  }
		  for(int j=2;j<2;j++)
		  {
			   ratio = a(j,i)/a(i,i);

			   for(int k=0;k<2;k++)
			   {
			  		a(j,k) = a(j,k) - ratio*a(i,k);
			   }
		  }
	 }
    }
};

std::istream &operator>>(std::istream &in, Matrix &mat);

std::ostream &operator<<(std::ostream &out, Matrix const &mat);

/******************************************************************************
 |  Konstruktor klasy Matrix.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Macierz wypelnione wartoscia 0.                                       |
 */
Matrix::Matrix()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            value[i][j] = 0;
        }
    }
}

/******************************************************************************
 |  Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
 */
Matrix::Matrix(double tmp[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            value[i][j] = tmp[i][j];
        }
    }
}

/******************************************************************************
 |  Realizuje mnozenie macierzy przez wektor.                                 |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik mnozenia,                     |
 |      v - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wektor.                    |
 */
void Matrix::rotation(double angle, Rectangle &tmp)
{
    double angle_r = angle * M_PI / 180;
    value[0][0] = cos(angle_r);
    value[0][1] = -sin(angle_r);
    value[1][0] = sin(angle_r);
    value[1][1] = cos(angle_r);

    tmp=*this*tmp;
}
Vector Matrix::operator*(Vector tmp)
{
    Vector result;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            result[i] += value[i][j] * tmp[j];
        }
    }
    return result;
}

Rectangle Matrix::operator*(Rectangle tmp)
{
    Rectangle result;
    for (int i = 0; i < SIZE_R; ++i)
    {

        result[i] = *this * tmp[i];
    }
    return result;
}
/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy.                             |
 */
double &Matrix::operator()(unsigned int row, unsigned int column)
{

    if (row >= SIZE)
    {
      throw "Error: Wektor jest poza zasiegiem!" ;
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE)
    {
        throw "Error: Wektor jest poza zasiegiem!" ;
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
const double &Matrix::operator()(unsigned int row, unsigned int column) const
{

    if (row >= SIZE)
    {
        throw "Error: Wektor jest poza zasiegiem!" ;
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= SIZE)
    {
         throw "Error: Wektor jest poza zasiegiem!" ;
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

/******************************************************************************
 |  Przeciążenie dodawania macierzy                                                          |
 |  Argumenty:                                                                |
 |      this - macierz, czyli pierwszy skladnik dodawania,                     |
 |      v - wektor, czyli drugi skladnik dodawania.                                               |
 |  Zwraca:                                                                   |
 |      Macierz - iloczyn dwóch podanych macierzy.                  |
 */
Matrix Matrix::operator+(Matrix tmp)
{
    Matrix result;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                         |
 */
std::istream &operator>>(std::istream &in, Matrix &mat)
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            in >> mat(i, j);
        }
    }
    return in;
}

/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      mat - macierz.                                                        |
 */
std::ostream &operator<<(std::ostream &out, const Matrix &mat)
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            out << "| " << mat(i, j) << " | "; //warto ustalic szerokosc wyswietlania dokladnosci liczb
        }
        std::cout << std::endl;
    }
    return out;
}
