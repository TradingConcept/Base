// obtenido de https://www.youtube.com/watch?v=JhgWFYfdIho
// ejemplo para hacer tuplas
#include <future>
#include <vector>
#include <thread>
#include <sched.h>

#include "Tuple.hpp"

// using namespace std;

void Tuple::Run()
{
    std::cout << "Initializng Tuples..." << std::endl;

    auto t0 = new std::tuple<std::string, int>();

    int a;
    char b;
    std::string c;

    tie(a, b, c) = std::tuple(1, '2', "3");
    std::cout << a << " " << b << " " << c << std::endl;

    Tuple::RunAsyncFutures(500);
    Tuple::RunThreads(1000);

    std::cout << "press a key and then enter to continue" << std::endl;
    char cin;
    std::cin >> cin;
}

void Tuple::RunAsyncFutures(int duration)
{
    // FUTURES - https://www.youtube.com/watch?v=D7fiNQX7P5w7

    std::future<int> work1 = std::async([duration] { return Tuple::compute(1, duration); });
    std::future<int> work2 = std::async([duration] { return Tuple::compute(2, duration); });

    auto result1 = work1.get();
    auto result2 = work2.get();

    std::cout << "1: " << result1 << " 2: " << result2 << std::endl;
}

int Tuple::compute(int job, int duration)
{
    std::cout << "running job " << job << std::endl;
    auto count = 1000 * 1000 * duration;
    for (size_t i = 0; i < count; i++)
    {
        /* code */
        double t = i / 1.2345;
    }

    return count;
}

void Tuple::Thread(int t, int duration, std::mutex *iomutex)
{

    std::cout << "running thread #" << t << " on CPU " << sched_getcpu() << std::endl;

    // Simulate important work done by the tread by sleeping for a bit...
    // std::this_thread::sleep_for(std::chrono::milliseconds(t * 618));
    Tuple::compute(t, duration);

    std::cout << "finishing thread #" << t << std::endl;
}

// https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/
void Tuple::RunThreads(int duration)
{

    // damos afinidad con $ taskset -c 5,6 ./launch-threads-report-cpu

    unsigned num_cpus = std::thread::hardware_concurrency();

    std::cout << "Launching " << num_cpus << " threads\n";

    // A mutex ensures orderly access to std::cout from multiple threads.
    std::mutex iomutex;
    std::vector<std::thread> threads(num_cpus);

    for (unsigned i = 0; i < num_cpus; i++)
    {
        threads[i] = std::thread([&iomutex, i, duration] {
            // interesante: en c++ los locks van dentro del contexto
            {
                // Use a lexical scope and lock_guard to safely lock the mutex only for the duration of std::cout usage.
                std::lock_guard<std::mutex> iolock(iomutex);
                std::cout << "starting hread #" << i << std::endl;
            }

            Tuple::Thread(i, duration, &iomutex);
        });
    }

    // esperamos a que todas terminen (el foreach de c++ 17)
    for (auto &t : threads)
    {
        t.join();
    }
}