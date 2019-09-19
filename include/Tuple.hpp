#pragma once
#include <memory>
#include <iostream>
#include <string>

// using namespace std;

class Tuple
{
    static int compute(int, int);
    static void RunAsyncFutures(int);
    
    static void Thread(int, int, std::mutex*);
    static void RunThreads(int);

public:
    static void Run();
};