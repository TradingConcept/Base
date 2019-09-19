#include <bits/stdc++.h>
#include <iostream>
#include <thread>
#include "QuickStart.hpp"
#include "Dog.hpp"
#include "MulticastSender.hpp"
#include "MulticastReceiver.hpp"
#include "Tuple.hpp"
#include "Cpp17.hpp"

using namespace std;

void ArrayTests()
{
    std::cout << "Arrays..." << std::endl;

    // diferentes formas de inicializar un arreglo
    auto arr0 = {1, 2, 3, 4};
    int arr1[] = {1, 2, 3, 4};
    int arr2[4] = {1, 2, 3, 4};
}

// aquí no puedo mandar el const
void PushValueToVector(vector<int> &vec, int value)
{
    // y como es una referencia, puedo tocarla (si no le pongo el & se hace una copia)
    vec.push_back(value);
}

// con el const y el & hacemos por mandar una referencia, pero que no puede modificarse dentro de la f()
void PrintVector(const vector<int> &vec)
{
    std::cout << "in = ";

    // foreach de c++ 17
    for (auto i : vec)
    {
        std::cout << i << ',';
    }

    std::cout << "\b" << std::endl
              << std::endl;
}

// con el const y el & hacemos por mandar una referencia, pero que no puede modificarse dentro de la f()
void PrintIterator(const vector<int> &vec)
{
    auto it0 = vec.begin();
    auto it1 = vec.end();

    for (auto i = it0; i != it1; i++)
    {
        std::cout << "i = " << *i << std::endl;
    }
}

void VectorTest()
{
    std::cout << "Vectors..." << std::endl;

    auto arr0 = {1, 2, 3, 4};

    vector<int> m_vec0;
    for (auto a : arr0)
    {
        m_vec0.push_back(a);
    }

    PrintVector(m_vec0);
    PrintIterator(m_vec0);

    // otra forma de inicializar vectores
    vector m_vec1 = {0, 2, 3, 4};
    PrintVector(m_vec1);

    vector m_vec2{0, 2, 3, 4};
    for (auto &a : m_vec2)
    {
        a++; // changes the values in vector pues estoy iterando por las referencias
    }
    PrintVector(m_vec2);

    auto m_vec3 = &m_vec2;
    for (auto &a : *m_vec3)
    {
        a++; // changes the values in vector pues estoy iterando por las referencias
    }
    PushValueToVector(*m_vec3, 99);
    PushValueToVector(m_vec2, 100);

    PrintVector(*m_vec3);
    PrintVector(m_vec2);
}

class Entity 
{
    float X, Y ;

    public:

    Entity()
    {
        this->X = 0.0f ;
        this->Y = 0.0f ;
    }

    void Print()
    {
        std::cout << "X = " << X << ", Y = " <<  Y << std::endl ;
    }
};

int main(int argc, char *argv[])
{   
    std::cout << "Initializng the beast..." << std::endl;

    Entity e0 ;
    e0.Print();

    auto e1 = new Entity() ;
    e1->Print();

    ArrayTests();
    VectorTest();

    int *pointer0 = nullptr; // este es mas nuevo para no confundir llamadas
    int *pointer1 = NULL;

    // enums
    enum pera
    {
        pera_verde,
        pera_roja
    };
    enum manzana
    {
        manzana_chica,
        manzana_grande
    };
    pera pera0 = pera_roja;
    pera pera1 = pera_verde;
    manzana m = manzana_grande;

    // incluso siendo enums y valor en cero, no puedes compararlas pues no son de la misma fruta
    // cout << ( pera0 == m ? "iguales" : "diferentes" ) << std::endl ;
    cout << (pera0 == pera1 ? "iguales" : "diferentes") << std::endl;

    enum class apple
    {
        green_apple,
        red_apple
    };
    enum class orange
    {
        big_orange,
        small_orange
    };
    apple a = apple::green_apple;
    orange o = orange::big_orange;

    // incluso siendo enums y valor en cero, no puedes compararlas pues no son de la misma fruta
    // cout << ( a == o ? "the same" : "different" ) << std::endl ;

    std::cout << "Press enter...";
    cin.ignore();

    QuickStart::Run();
    Dog::Run();
    Tuple::Run();
    Cpp17::Run();

    auto treceiver0 = std::thread(MulticastReceiver::Run);
    auto treceiver1 = std::thread(MulticastReceiver::Run);
    auto treceiver2 = std::thread(MulticastReceiver::Run);
    std::this_thread::sleep_for(1s);

    auto tsender = std::thread(MulticastSender::Run);
    std::this_thread::sleep_for(1s);

    tsender.join();

    treceiver0.join();
    treceiver1.join();
    treceiver2.join();

    char c;
    do
    {
        std::cout << "Exit? [Y/N]";
        std::cin >> c;
    } while (c != 'y' && c != 'Y');

    return 0;
}
