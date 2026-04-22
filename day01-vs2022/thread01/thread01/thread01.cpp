#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;
int shared_data = 0;

using namespace std;

void add(int id, int count)
{
	for (int i = 0; i < count; ++i)
	{
		lock_guard<mutex> lock(mtx);
		++shared_data ;
		std::cout << "Thread [" << id <<"][" << std::this_thread::get_id() << "]:incremented shared_data to " << shared_data << endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
}

int main()
{
	std::thread t1(add, 1, 10);
	std::thread t2(add, 2, 10);

	t1.join();
	t2.join();
 
	cout << "last shared_data: " << shared_data << endl;
	system("pause");
	return 0;
}