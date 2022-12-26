// C++ implementation of Radix Sort
#include <iostream>;
using namespace std;

int GetMax(int arr[], int size)
{
	int max = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	return max;
}

void CountingSort(int arr[], int size, int div)
{
	int* output = (int*)_malloca(size * sizeof(int));
	int count[10] = { 0 };

	for (int i = 0; i < size; i++)
	{
		count[(arr[i] / div) % 10]++;
	}

	for (int i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = size - 1; i >= 0; i--)
	{
		output[count[(arr[i] / div % 10)] - 1] = arr[i];
		count[(arr[i] / div) % 10]--;
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = output[i];
	}
}

void RadixSort(int arr[], int size)
{
	int m = GetMax(arr, size);
	for (int div = 1; m / div > 0; div *= 10)
	{
		CountingSort(arr, size, div);
	}
}

int main()
{
	int arraySize;
	cout << "Enter the size for the array" << endl;
	cin >> arraySize;

	/*C++ does not support variable length arrays on the stack, but we can use _malloca*/
	int* myArray = (int*)_malloca(arraySize * sizeof(int));

	cout << "Enter " << arraySize << " integers in any order" << endl;

	for (int i = 0; i < arraySize; i++)
	{
		cin >> myArray[i];
	}

	cout << "Before Sorting" << endl;

	for (int i = 0; i < arraySize; i++)
	{
		cout << myArray[i] << " ";
	}

	RadixSort(myArray, arraySize);

	cout << endl << "After Sorting" << endl;

	for (int i = 0; i < arraySize; i++)
	{
		cout << myArray[i] << " ";
	}

	return 0;
}