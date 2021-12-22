#include<iostream>
#include"Header.h"

int main()
{

	int* test = new int[10];
	for (int i = 0; i < 10; i++)
	{
		test[i] = i;
	}
	deleteElement(test, 10, 2);
	enterElement(test, 10, 44, 3);
	for (int i = 0; i < 9; i++)
	{
		std::cout << test[i] << std::endl;

	}

	
}