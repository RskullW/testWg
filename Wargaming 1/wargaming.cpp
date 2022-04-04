#include <iostream>

bool isEven(int value) { return value - value / 2 * 2; }

int main()
{
	// Testing
	std::cout << "-1 = " << isEven(-1) << "\n0 = " << isEven(0) << "\n1 = " << isEven(1) << "\n2 = " << isEven(2) << "\n65535 = " << isEven(65535);
	return 0;
}