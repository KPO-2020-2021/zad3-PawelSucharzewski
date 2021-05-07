#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../tests/doctest/doctest.h"
#include "rectangle.hh"
#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "matrix.hh"
TEST_CASE("test wektora kostruktor")
{
    Vector tmp; 
    CHECK(tmp[0]== 0);
    CHECK(tmp[1]== 0); 
}

TEST_CASE("test wektora kostruktor parametycznego")
{
    double wek[]={2,3};
    Vector tmp(wek);
    CHECK(tmp[0]== 2); 
    CHECK(tmp[1]== 3); 
} 

TEST_CASE("test wektora +")
{
    double wek[]={2,3}; 
    Vector tmp(wek); 
    Vector tmp2(wek); 
    tmp2 = tmp2 + tmp; 
    CHECK(tmp2[0]== 4); 
    CHECK(tmp2[1]== 6); 
}

TEST_CASE("sprawdzenie []") 
{
    double wek[]={2,3}; 
    Vector tmp(wek); 
    WARN_THROWS(tmp[10]); 
}

TEST_CASE("wektor - wyswietlanie standard") 
{
    double wek[]={2,3}; 
    Vector tmp(wek); 
    std::ostringstream out; 
    out <<tmp; 
    CHECK( "2 3 " == out.str() ); 
}

TEST_CASE("wektor - wczytywanie standard") 
{ 
    Vector tmp;
    std::istringstream in("3 4"); 
    in >> tmp; 
    std::ostringstream out; 
    out <<tmp;
    CHECK( "3 4 " == out.str() ); 
} 

TEST_CASE("test wektora ==") 
{ 
    Vector tmp,tmp2; 
    CHECK( tmp==tmp2 );
}




TEST_CASE("test macierzy kostruktor")
{ 
    Matrix tmp;
    for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
    CHECK(tmp(i,j)== 0); 
}

TEST_CASE("test macierzy kostruktor parametycznego")
{
    double x[2][2]={{1,1},{1,1}};
    Matrix tmp(x);
    for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
    CHECK(tmp(i,j)== 1);
}

TEST_CASE("test wektora *")
{
    Matrix tmp;
    double wek[]={2,3};
    Vector tmp2(wek);
    tmp2 = tmp * tmp2;
    CHECK(tmp2[0]== 0);
    CHECK(tmp2[1]== 0);
} 

TEST_CASE("sprawdzenie ()")
{
    Matrix tmp;
    WARN_THROWS(tmp(12,31));
}





TEST_CASE("test prostokata kostruktor parametycznego")
{
    double wek[]={0,0};
    Rectangle tmp(Vector(wek),10,10);
    CHECK(tmp[0][0]== 0);
    CHECK(tmp[0][1]== 0);
}

TEST_CASE("prostokata - wyswietlanie standard") 
{
    double wek[]={0,0};
    Rectangle tmp(Vector(wek),10,10);
    std::ostringstream out;
    out <<tmp; 
    CHECK( "0 0 \n10 0 \n10 10 \n0 10 \n" == out.str() ); 
}

TEST_CASE("test prostokata kostruktor parametycznego")
{
    double wek[]={0,0};
    Rectangle tmp(Vector(wek),10,10);
    double wek2[]={10,10};
    tmp.move(Vector(wek2));
    CHECK(tmp[0][0]== 10);
    CHECK(tmp[0][1]== 10); 
}

TEST_CASE("test prostokata kostruktor parametycznego")
{
    Matrix tmpM3;
    double wek[]={0,0};
    Rectangle tmp(Vector(wek),10,10);
    tmpM3.rotation(90,tmp);
    CHECK(tmp[0][0]== 0);
    CHECK(tmp[0][1]== 0);
}
// This is all that is needed to compile a test-runner executable.
// More tests can be added here, or in a new tests/*.cpp file.
