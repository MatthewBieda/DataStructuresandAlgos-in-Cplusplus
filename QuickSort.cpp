#include <iostream>
using namespace std;
//quicksort implementation

int Partition(int arr[], int s, int e)
{
	int pivot = arr[e];
	int pIndex = s;

	for (int i = s; i < e; i++)
	{
		if (arr[i] < pivot)
		{
			int temp = arr[i];
			arr[i] = arr[pIndex];
			arr[pIndex] = temp;
			pIndex++;
		}
	}

	int temp = arr[e];
	arr[e] = arr[pIndex];
	arr[pIndex] = temp;

	return pIndex;
}

void quickSort(int arr[], int s, int e)
{
	if (s < e)
	{
		int p = Partition(arr, s, e);
		quickSort(arr, s, (p - 1)); // recursive quicksort call for left partition
		quickSort(arr, (p + 1), e); // recursive quicksort call for right partition
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

	cout << "Before Quick Sort" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		cout << myArray[i] << " ";
	}

	quickSort(myArray, 0, (arraySize - 1));

	cout << endl << "After Quick Sort" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		cout << myArray[i] << " ";
	}

	return 0;
}