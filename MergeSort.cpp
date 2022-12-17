#include <iostream>
using namespace std;

// merge sort sorting algorithm

// merge function
void merge(int arr[], int l, int m, int r)
{
	int i = l; // starting index for left sub-array
	int j = m + 1; // starting index for right sub-array
	int k = l; // starting index for temporary array

	int temp[5];

	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j])
		{
			temp[k] = arr[i]; // arr[i] is smaller than arr[j]
			i++;
			k++;
		}
		else
		{
			temp[k] = arr[j]; // arr[j] is smaller than arr[j]
			j++;
			k++;
		}
	}
	while (i <= m)
	{
		temp[k] = arr[i]; // copying all elements from left subarray to temp as it is
		i++;
		k++;
	}
	while (j <= r)
	{
		temp[k] = arr[j]; // copying all elements from right subarray to temp as it is
		j++;
		k++;
	}
	for (int s = l; s <= r; s++)
	{
		arr[s] = temp[s];
	}

}

// merge sort function
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

int main()
{
	cout << "Enter 5 elements for the array: " << endl;

	int myArr[5];
	for (int i = 0; i < 5; i++)
	{
		cin >> myArr[i];
	}
	cout << "Before Merge Sort" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << myArr[i] << " ";
	}

	mergeSort(myArr, 0, 4);

	cout << endl << "After Merge Sort" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << myArr[i] << " ";
	}

	return 0;
}