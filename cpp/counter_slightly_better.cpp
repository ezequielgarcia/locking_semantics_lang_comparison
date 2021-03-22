#include <iostream>
#include <thread>
#include <mutex>

struct counter {
	std::mutex mutex;
	int value;

	// Some constructor
	counter():value(0) { }
};

static void worker(struct counter& c)
{
	for (int i = 0; i < 1000000; i++) {
		std::lock_guard<std::mutex> guard(c.mutex);
		c.value++;
	}
}

int main(int argc, char *argv[])
{
	struct counter c;

	// Start two threads
	std::thread t1(worker, std::ref(c));
	std::thread t2(worker, std::ref(c));

	// Wait for both threads to terminate
	t1.join();
	t2.join();

	// How's the counter
	std::cout << c.value << std::endl;
}
