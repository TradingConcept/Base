#pragma once
#include <memory>
#include <iostream>
#include <string>

using namespace std ;

class Cpp17 {

    static void paralell();

    template<typename _Callable>
    static void sub_invoke1(std::string name, _Callable&& __fn, int a, int b);

    static void sub_invoke2(std::string name, int (*fn)(int,int), int a, int b);

    static void invoke();
    
public:    
    static void Run();    
};