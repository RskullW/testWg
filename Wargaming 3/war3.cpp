/*
3. На языке Python или С/С++, написать функцию, которая быстрее всего 
(по процессорным тикам) отсортирует данный ей массив чисел.
*/

#include <iostream>
#include <random>

template <typename T>
void sorted(T* arr, int size)
{
    int left = 0, right = size - 1, middle = arr[size / 2];

    while (left <= right)
    {

        while (middle > arr[left])
        {
            left++;
        }

        while (middle < arr[right])
        {
            right--;
        }

        if (left <= right)
        {
            std::swap(arr[left++], arr[right--]);
        }
    }

    if (right > 0)
    {
        sorted(arr, right + 1);
    }

    if (left < size)
    {
        sorted(&arr[left], size - left);
    }
}

int main()
{
    srand(time(0));

    int i = 0;
    int sizeArray = rand() % 100 + 1;
    int* arr;

    arr = new int[sizeArray];

    std::cout << "Old array:\n";
    for (i; i < sizeArray; ++i)
    {
        arr[i] = rand() % 100 + 1;
        std::cout << arr[i] << " ";
    }

    sorted(arr, sizeArray);

    std::cout << "\nNew array:\n";
    for (i = 0; i < sizeArray; ++i)
    {
        std::cout << arr[i] << " ";
    }

    delete [] arr;

    return 0;
}