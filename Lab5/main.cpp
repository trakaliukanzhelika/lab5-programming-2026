// Trakaliuk Anzhelika K-28
// Variant 14

#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <syncstream>
#include <thread>


constexpr std::chrono::seconds SLOW{ 7 };
constexpr std::chrono::seconds QUICK{ 1 };

void compute(const std::string& name, const std::chrono::seconds duration)
{
    std::this_thread::sleep_for(duration);
    std::osyncstream(std::cout) << name << "\n";
}


void work()
{
    const auto start = std::chrono::steady_clock::now();

    std::future<void> a2_c1 = std::async(std::launch::async, []
        {
            compute("A2", QUICK);
            compute("C1", QUICK);
        });

    std::future<void> c2_d2 = std::async(std::launch::async, []
        {
            compute("C2", SLOW);
            compute("D2", QUICK);
        });

    compute("A1", SLOW);
    a2_c1.get();
    compute("B", QUICK);
    compute("D1", QUICK);
    c2_d2.get();

    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::osyncstream(std::cout) << "Time: " << elapsed.count() << " s\n" << "Work is done!\n";
}

int main()
{
    work();
    return 0;
}