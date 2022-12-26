# include <iostream>
using namespace std;
// counting sort implementation

void CountingSort(int input_array[], int s, int r)
{
	int* output_array = (int*)_malloca(s * sizeof(int));
	int* count_array = (int*)_malloca(r * sizeof(int));

	// initialize all elements to 0 in count array
	for (int i = 0; i < r; i++)
	{
		count_array[i] = 0;
	}

	// initialize all elements to 0 in count array
	for (int i = 0; i < r; i++)
	{
		output_array[i] = 0;
	}

	// take a count of all elements in the input array
	for (int i = 0; i < s; i++)
	{
		++count_array[input_array[i]];
	}

	// cumulative count of count array to get the positions of elements to be stored in the output array
	for (int i = 1; i < r; i++)
	{
		count_array[i] = count_array[i] + count_array[i - 1];
	}

	// placing input array elements into output array in proper positions such that the result is in ASC order
	for (int i = 0; i < s; i++)
	{
		output_array[--count_array[input_array[i]]] = input_array[i];
	}

	// copy output array elements to input array
	for (int i = 0; i < s; i++)
	{
		input_array[i] = output_array[i];
	}
}

int main()
{
	int arraySize;
	cout << "Enter the size for the array" << endl;
	cin >> arraySize;

	/*C++ does not support variable length arrays on the stack, but we can use _malloca*/
	int* myArray = (int*)_malloca(arraySize * sizeof(int));

	int range = 10;

	cout << "Enter " << arraySize << "integers in any order with values 0 - 9:" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		cin >> myArray[i];
	}

	cout << "Before Sorting" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		cout << myArray[i] << " ";
	}
	cout << endl;

	CountingSort(myArray, arraySize, range);

	cout << "After Sorting" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		cout << myArray[i] << " ";
	}
	cout << endl;

	return 0;
}