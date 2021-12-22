#include"Header.h"
void deleteElement(int*& array, int size, int index)
{
	int* newArray = new int[size - 1];
	for (int i = 0; i < size; i++)
	{
		if (i == index)
		{
			while (i < size)
			{

				array[i] = array[i + 1];
				i++;
			}
		}

	}
	for (int i = 0; i < size; i++)
	{
		newArray[i] = array[i];
	}
	newArray = array;

}
void enterElement(int*& array, int size, int element, int index)
{
	int* newArray = new int[size + 1];
	for (int i = 0; i < size + 1; i++)
	{
		if (i == index)
		{
			newArray[i] = element;
			i++;
		}
		newArray[i] = array[i];

	}
}