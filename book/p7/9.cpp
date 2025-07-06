#include <iostream>

class queue {
public:
	void put(int var);
	int get();
private:
	static const int MAX = 10;

	int q[MAX];
	ssize_t head = 0;
	ssize_t tail = -1;

	size_t len = 0;
};

int main()
{
	queue q;

    try {
	    q.put(1);
	    q.put(2);
	    std::cout << "1: " << q.get() << std::endl;
	    std::cout << "2: " << q.get() << std::endl;
	    q.put(3);
	    std::cout << "3: " << q.get() << std::endl;
	    q.put(4);
	    q.put(5);
	    q.put(6);
	    std::cout << "4: " << q.get() << std::endl;
	    std::cout << "5: " << q.get() << std::endl;
	    std::cout << "6: " << q.get() << std::endl;
	    std::cout << "None: " << q.get() << std::endl;
	    q.put(1);
	    q.put(2);
	    q.put(3);
	    q.put(4);
	    q.put(5);
	    q.put(6);
	    q.put(7);
	    q.put(8);
	    q.put(9);
	    q.put(10);
	    q.put(11);
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

	return 0;
}

void queue::put(int var)
{

	if (len == MAX)
	{
        throw std::runtime_error("Queue cannot contain more than " + std::to_string(MAX) + " elements!");
	}

	if (tail == MAX - 1)
		tail = -1;

	q[++tail] = var;
	len++;
}

int queue::get()
{

	if (tail < head)
	{
		throw std::runtime_error("Attempted to dequeue from an empty queue!");
	}

	int var = q[head++];
	len--;

	if (head == MAX)
		head = 0;

	return var;
}
