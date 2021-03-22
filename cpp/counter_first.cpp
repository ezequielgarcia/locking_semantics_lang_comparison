#include <iostream>
#include <thread>
#include <mutex>

static std::mutex mutex;
static int value;

static void worker()
{
	for (int i = 0; i < 1000000; i++) {
		std::lock_guard<std::mutex> guard(mutex);
		value++;
	}
}

int main()
{
	// Start two threads
	std::thread t1(worker);
	std::thread t2(worker);

	// Wait for both threads to terminate
	t1.join();
	t2.join();

	// How's the counter
	std::cout << value << std::endl;
}
