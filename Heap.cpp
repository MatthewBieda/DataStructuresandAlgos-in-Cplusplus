#include <iostream>

using namespace std;

class MinHeap
{
public:
	int* heapArray; // Pointer to array of elements in Heap
	int capacity; // Maximum possible size of heap
	int heapSize; // Current number of elements in min heap

	MinHeap(int cap)
	{
		heapSize = 0;
		capacity = cap;
		heapArray = new int[cap];
	}

	void swap(int& x, int& y)
	{
		int temp = x;
		x = y;
		y = temp;
	}

	void linearSearch(int val)
	{
		for (int i = 0; i < heapSize; i++)
		{
			if (heapArray[i] == val)
			{
				cout << "Value Found!";
				return;
			}
		}
		cout << "Value NOT Found!";
	}

	void printArray()
	{
		for (int i = 0; i < heapSize; i++)
		{
			cout << heapArray[i] << " ";
		}
		cout << endl;
	}

	int height()
	{
		return ceil(log2(heapSize + 1)) - 1;
	}

	int parent(int i)
	{
		return(i - 1) / 2;
	}

	int left(int i)
	{
		return(2 * i + 1);
	}

	int right(int i)
	{
		return(2 * i + 2);
	}

	int getMin()
	{
		return heapArray[0];
	}

	void insertKey(int k)
	{
		if (heapSize == capacity)
		{
			cout << "Overflow: Unable to insert key" << endl;
			return;
		}

		// First inser the new key at the end
		heapSize++;
		int i = heapSize - 1;
		heapArray[i] = k;

		// Maintain the min heap invariant
		while (i != 0 && heapArray[parent(i)] > heapArray[i])
		{
			swap(heapArray[i], heapArray[parent(i)]);
			i = parent(i);
		}
	}

	void MinHeapify(int i)
	{
		int l = left(i);
		int r = right(i);
		int smallest = i;
		if (l < heapSize && heapArray[l] < heapArray[i])
		{
			smallest = l;
		}
		if (r < heapSize && heapArray[r] < heapArray[smallest])
		{
			smallest = r;
		}
		if (smallest != i)
		{
			swap(heapArray[i], heapArray[smallest]);
			MinHeapify(smallest);
		}
	}

	// Method to remove minimum element (or root) from min heap	
	int extractMin()
	{
		if (heapSize <= 0)
		{
			return INT_MAX;
		}
		if (heapSize == 1)
		{
			heapSize--;
			return heapArray[0];
		}

		// Store the minimum value, and remove it from the heap
		int root = heapArray[0];
		heapArray[0] = heapArray[heapSize - 1];
		heapSize--;
		MinHeapify(0);

		return root;
	}

	void decreaseKey(int i, int newVal)
	{
		heapArray[i] = newVal;
		while (i != 0 && heapArray[parent(i)] > heapArray[i])
		{
			swap(heapArray[i], heapArray[parent(i)]);
			i = parent(i);
		}
	}

	void deleteKey(int i)
	{
		decreaseKey(i, INT_MIN);
		extractMin();
	}

};

int main()
{
	int s;
	cout << "Enter size of min heap" << endl;
	cin >> s;	
	MinHeap obj(s);
	cout << "Min heap created" << endl;

	int option, val;
	do 
	{
		cout << "What operation do you wish to perform? 0 to exit" << endl;
		cout << "1. Insert Key/Node" << endl;
		cout << "2. Search Key/Node" << endl;
		cout << "3. Delete Key/Node" << endl;
		cout << "4. Get Min" << endl;
		cout << "5. Extract Min" << endl;
		cout << "6. Height of Heap" << endl;
		cout << "7. Print/Traverse Heap values" << endl;
		cout << "8. Clear Screen" << endl;
		cout << "0. Exit Program" << endl;

		cin >> option;
		switch (option)
		{
		case 0:
			break;
		case 1:
			cout << "Insert Operation" << endl;
			cout << "Enter value to insert in heap: ";
			cin >> val;
			obj.insertKey(val);
			cout << endl;
			break;
		case 2:
			cout << "Search Operation" << endl;
			cout << "Enter value to search in heap: ";
			cin >> val;
			obj.linearSearch(val);
			break;
		case 3:
			cout << "Delete Operation" << endl;
			cout << "Enter index of Heap Array to DELETE: ";
			cin >> val;
			obj.deleteKey(val);
			break;
		case 4:
			cout << "GET Min Value" << endl;
			cout << obj.getMin() << endl;
			cout << endl;
			break;
		case 5:
			cout << "EXTRACT Min Value: " << endl;
			cout<<obj.extractMin()<<endl;
			cout << endl;
			break;
		case 6:
			cout << "HEAP TREE HEIGHT: " << endl;
			cout << obj.height() << endl;
			break;
		case 7:
			cout << "PRINT Heap Array: " << endl;
			obj.printArray();
			cout << endl;
			break;
		case 8:
			system("cls");
			break;
		default:
			cout << "Enter valid option number" << endl;
		}

	} while (option != 0);



	return 0;
}