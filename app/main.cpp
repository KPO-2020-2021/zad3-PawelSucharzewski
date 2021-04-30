// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "rectangle.hh"
#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "matrix.hh"
#include "../include/lacze_do_gnuplota.hh"

/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i macierzy plus obsluga lacza do gnuplota
 */

#define DL_KROTKI_BOK 100
#define DL_DLUGI_BOK 150

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy, Rectangle rec)
{
       StrmWy << rec;
}

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool ZapisWspolrzednychDoPliku(const char *sNazwaPliku,
                                        Rectangle rec)
{
       std::ofstream StrmPlikowy;

       StrmPlikowy.open(sNazwaPliku);
       if (!StrmPlikowy.is_open())
       {
              std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
                        << ":(  nie powiodla sie." << std::endl;
              return false;
       }

       ZapisWspolrzednychDoStrumienia(StrmPlikowy, rec);
       StrmPlikowy << rec[0];
       StrmPlikowy.close();
       return !StrmPlikowy.fail();
}

int main()
{
       std::cout << "Project Rotation 2D based on C++ Boiler Plate v"
                 << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
                 << "."
                 << PROJECT_VERSION_MINOR /* istotne zmiany */
                 << "."
                 << PROJECT_VERSION_PATCH /* naprawianie bugów */
                 << "."
                 << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
                 << std::endl;
       // std::system("cat ../LICENSE");
       // do zadania Rotacja 2D
       std::cout << "Vector:" << std::endl;
       Vector tmpV1 = Vector();
       std::cout << "Vector - konstruktor bezparametryczny:\n"
                 << tmpV1 << std::endl;
       double argumentsV[] = {1.0, 2.0};
       Vector tmpV2 = Vector(argumentsV);
       std::cout << "Vector - konstruktor parametryczny:\n"
                 << tmpV2 << std::endl;

       std::cout << "Matrix:" << std::endl;
       Matrix tmpM1 = Matrix();
       std::cout << "Matrix - konstruktor bezparametryczny:\n"
                 << tmpM1 << std::endl;
       double argumentsM[][SIZE] = {{1.0, 2.0}, {3.0, 4.0}};
       Matrix tmpM2 = Matrix(argumentsM);
       std::cout << "Matrix - konstruktor parametryczny:\n"
                 << tmpM2 << std::endl;

       PzG::LaczeDoGNUPlota Lacze; // Ta zmienna jest potrzebna do wizualizacji
                                   // rysunku prostokata

       //-------------------------------------------------------
       //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
       //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
       //  na dwa sposoby:
       //   1. Rysowane jako linia ciagl o grubosci 2 piksele
       //
       Lacze.DodajNazwePliku("../datasets/prostokat.dat", PzG::RR_Ciagly, 2);
       //
       //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
       //      których połowa długości boku wynosi 2.
       //
       Lacze.DodajNazwePliku("../datasets/prostokat.dat", PzG::RR_Punktowy, 2);
       //
       //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
       //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
       //  jako wspolrzedne punktow podajemy tylko x,y.
       //
       Lacze.ZmienTrybRys(PzG::TR_2D);
       char op;
       Rectangle re;
       int n;
       double angle;
       double argumentsV_T[2];
       Matrix m;
       std::cout << "o - obrot prostokata o zadany kat" << std::endl;
       std::cout << "p - przesuniecie prostokata o zadany wektor" << std::endl;
       std::cout << "w - wyswietlenie wspolrzednych wierzcholkow" << std::endl;
       std::cout << "m - wyswietl menu" << std::endl;
       std::cout << "k - koniec dzialania programu" << std::endl;
            ZapisWspolrzednychDoStrumienia(std::cout, re);
                     if (!ZapisWspolrzednychDoPliku("../datasets/prostokat.dat", re))
                            return 1;
                     Lacze.Rysuj();
       while (1)
       {
              re.compare();
              std::cout << "Twoj wybor? (m - menu) >" << std::endl;
              std::cin >> op;
              switch (op)
              {
              case 'o':
              {
                     std::cout << "Podaj wartosc kata obrotu w stopniach" << std::endl;
                     std::cin>>angle;
                     std::cout << "Ile razy operacja obrotu ma byc powtorzona?" << std::endl;
                     std::cin>>n;
                     for(int i=0; i<n; i++)
                     {
m.rotation(angle,re);
        
                     if (!ZapisWspolrzednychDoPliku("../datasets/prostokat.dat", re))
                            return 1;
                 
                     }
                     
                     Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
       
              }
              break;
              case 'p':
              {
                     std::cout << "Wprowadz wspolrzedne wektora translacji w postaci dwoch liczbtzn. wspolrzednej x oraz wspolrzednej y   " << std::endl;
                     std::cin >> argumentsV_T[0] >> argumentsV_T[1];
                     Vector tmpV_T = Vector(argumentsV_T);
                     re.move(tmpV_T);
                    
                     if (!ZapisWspolrzednychDoPliku("../datasets/prostokat.dat", re))
                            return 1;
                     Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku 
           
              }
              break;
              case 'w':
              {
                     ZapisWspolrzednychDoStrumienia(std::cout, re);
              }
              break;
              case 'm':
              {
                     std::cout << "o - obrot prostokata o zadany kat" << std::endl;
                     std::cout << "p - przesuniecie prostokata o zadany wektor" << std::endl;
                     std::cout << "w - wyswietlenie wspolrzednych wierzcholkow" << std::endl;
                     std::cout << "m - wyswietl menu" << std::endl;
                     std::cout << "k - koniec dzialania programu" << std::endl;
              }
              break;
              case 'k':
              {
                     return 0;
              }
              break;
              default:
                     break;
              }
       }

       Dummy d = Dummy();
       return d.doSomething() ? 0 : -1;
}
