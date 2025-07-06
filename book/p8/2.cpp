#include <iostream>
#include <string.h>

class String
{
private:

	static const int SZ = 80;

	char str[SZ];
public:
	String()
		{ str[0] = '\0'; }
	String(const char* s)
	{
		strcpy(str, s);

	}
	void display() const
		{ std::cout << str; }

	String operator+= (String s)
	{
		if (strnlen(str, SZ) + strnlen(s.str, SZ) < SZ)
		{
			strcat(str, s.str);

		}
		else
		{
			std::cout << "\nПереполнение!";
			exit(1);
		}
		return *this;
	}
};

int main()
{
	String s1 = "С Рождеством! ";
	String s2 = "С Новым годом!";
	String s3;
	s1.display(); std::cout << std::endl;
	s2.display(); std::cout << std::endl << std::endl;

	s1 += s2;
	s1.display(); std::cout << std::endl;

	return 0;
}
