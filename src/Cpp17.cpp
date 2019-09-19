// obtenido de https://www.youtube.com/watch?v=fI2xiUqqH3Q
// https://brycelelbach.github.io/cpp17_features/
// features del c++ 17
#include <map>
#include <vector>
#include <algorithm>
#include <mutex>
#include "Cpp17.hpp"

using namespace std;

template <typename K, typename V, typename F>
void find_and_update(std::map<K, V> &m, F f)
{
    // auto it = m.find(key);
    // if (it != m.end())
    // {
    //     it->second = f(it->first);
    // }
}

// https://github.com/CppCon/CppCon2017/blob/master/Tutorials/C%2B%2B17%20Parallel%20Algorithm/C%2B%2B17%20Parallel%20Algorithm%20-%20Dietmar%20Kühl%20-%20CppCon%202017.pdf
void Cpp17::paralell()
{
    std::cout << "Paralell" << std::endl;

    std::vector<std::string> names = {"hi", "test", "foo"};
    std::vector<tuple<std::string, size_t>> name_sizes;

    std::pair<int, int> p = {1, 2};
    std::cout << "pair " << p.first << "." << p.second << std::endl;

    std::transform(names.begin(), names.end(),
                   std::back_inserter(name_sizes),
                   [](const std::string &n) {
                       return std::tuple(n, n.size());
                   });

    for (auto name_size : name_sizes)
    {
        std::cout << get<0>(name_size) << " : " << get<1>(name_size) << std::endl;
    }
}

int Sum0(int a, int b)
{
    return a + b + 0;
}

int Sum1(int a, int b)
{
    return a + b + 1;
}

int Sum2(int a, int b)
{
    return a + b + 2;
}

template <typename _Callable>
void Cpp17::sub_invoke1(std::string name, _Callable &&fn, int a, int b)
{
    std::cout << "Invoke1 " << name << " " << std::invoke(fn, a, b) << std::endl;
}

void Cpp17::sub_invoke2(std::string name, int (*fn)(int, int), int a, int b)
{
    std::cout << "Invoke2 " << name << " " << std::invoke(fn, a, b) << std::endl;
}

// declaración de delgados (el inline sirve para declararlos en la clase)
int (*del_sum0)(int, int) = &Sum0;
inline int (*del_sum1)(int, int) = &Sum1;
int (*del_sum2)(int, int);

void Cpp17::invoke()
{
    // declaración en clase
    Cpp17::sub_invoke1("Sum0", del_sum0, 1, 2);
    Cpp17::sub_invoke2("Sum0", del_sum0, 1, 2);

    // declaración inline
    Cpp17::sub_invoke1("Sum1", del_sum1, 1, 2);
    Cpp17::sub_invoke2("Sum1", del_sum1, 1, 2);

    // asignación
    del_sum2 = &Sum2;
    Cpp17::sub_invoke1("Sum2", del_sum2, 1, 2);
    Cpp17::sub_invoke2("Sum2", del_sum2, 1, 2);
}

void Cpp17::Run()
{
    // https://stackoverflow.com/questions/2324658/how-to-determine-the-version-of-the-c-standard-used-by-the-compiler
    std::cout << "Initializng C++ 17 samples ..." << __cplusplus << std::endl;

    // Structured bindings
    std::tuple<double, double, double> t;
    // double x, y, z;
    // auto [x,y,z] = t ;

    Cpp17::paralell();
    Cpp17::invoke();

    // Selection statements with initializers

    if (auto a0 = 0; a0 < 10) // inicializamos dentro del paréntesiso, valido en switch
    {
        a0 = 20;
    }
    else if (a0 > 20) // el contexto es válido
    {
        a0 = 10;
    }
    else
    {
        a0 = 30; // el contexto es válido
    }
    // a0 = 30; <- no compila pues el contexto de a0 es tan sólo el IF

    // Compile-time conditional statments
    const int T = 10;
    if constexpr (T == 10)
    {
        std::cout << "compila directo";
    }
    else
    {
        std::cout << "ni siquiera existe directo";
    }

    auto mutex0 = new std::mutex();
    mutex0->lock();
    mutex0->try_lock();
    mutex0->unlock();

    // Fold expressions
    // Class template deduction
    // auto non-type template parameters
    // inline variables
    // constexpr lambdas
    // Unary static_assert
    // Guaranteed copy elision
    // Nested namespace definitions
    // Preprocessor predicate for header testing
}
