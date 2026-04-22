#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int shared_num = 0;
std::mutex mux;

using namespace std;

void add(int id,int count)
{
    for (int i = 0; i < count; ++i)
    {
        lock_guard<mutex> lock(mux);
        ++shared_num;
        cout<<"Thread ["<<id<<"]["<<this_thread::get_id()<<"]shared_num: "<< shared_num <<endl;
    }
    this_thread::sleep_for(100ms);
}

int main()
{
    thread t1(add,1,10);
    thread t2(add,2,10);

    t1.join();
    t2.join();

    cout << "last shared_num: "<< shared_num << endl;
    return 0;
}

