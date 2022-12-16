#include <iostream>

using namespace std;

class Node
{
public:
	int key;
	int data;
	Node* next;

	Node() 
		: key(0), data(0), next(nullptr) { }

	Node(int k, int d)
		: key(k), data(d), next(nullptr) { }
};

class CircularLinkedList
{
public:
	Node* head;

	CircularLinkedList()
		: head(nullptr) { }

	//1. Check if node exists using key value
	Node* nodeExists(int k)
	{
		Node* temp = nullptr;
		Node* ptr = head;

		if (ptr == nullptr)
		{
			return temp;
		}
		else
		{
			do
			{
				if (ptr->key == k)
				{
					temp = ptr;
				}
				ptr = ptr->next;

			}while (ptr != head);
			return temp;
		}
	}

	// 2. Append a node to the list
	void appendNode(Node* new_node)
	{
		if (nodeExists(new_node->key) != nullptr)
		{
			cout<<"Node already exists with key value: " << new_node->key <<". Append another node with a different key value" << endl;
		}
		else
		{
			if (head == nullptr)
			{
				head = new_node;
				new_node->next = head;
				cout << "Node appended at first head position" << endl;
			}
			else
			{
				Node* ptr = head;
				while (ptr->next != head)
				{
					ptr = ptr->next;
				}
				ptr->next = new_node;
				new_node->next = head;
				cout << "Node appended" << endl;
			}
		}
	}

	// 3. Prepend Node - Attach a node at the beginning

	void prependNode(Node* new_node)
	{
		if (nodeExists(new_node->key) != nullptr)
		{
			cout << "Node already exists with key value: " << new_node->key << ". Append another node with a different key value" << endl;
		}
		else
		{
			if (head == nullptr)
			{
				head = new_node;	
				new_node->next = head;
				cout << "Node prepended at first head position" << endl;
			}
			else
			{
				Node* ptr = head;
				while (ptr->next != head)
				{
					ptr = ptr->next;
				}

				ptr->next = new_node;
				new_node->next = head;
				head = new_node;
				cout << "Node prepended" << endl;
			}
		}
	}

	// 4.  Insert a Node after a particular node in the list
	
	void insertNodeAfter(int k, Node* new_node)
	{
		Node* ptr = nodeExists(k);
		if (ptr == nullptr)
		{
			cout << "No node exists with key value of: " << k << endl;
		}
		else
		{
			if (nodeExists(new_node->key) != nullptr)
			{
				cout << "Node already exists with key value: " << new_node->key << ". Append another node with a different key value" << endl;
			}
			else
			{
				if (ptr->next == head)
				{
					new_node->next = head;
					ptr->next = new_node;
					cout << "Node inserted at the end" << endl;
				}
				else
				{
					new_node->next = ptr->next;
					ptr->next = new_node;
					cout << "Node inserted in between" << endl;
				}
			}
		}
	}

	// 5. Delete Node by unique key	
	void deleteNodeByKey(int k)
	{
		Node* ptr = nodeExists(k);
		if (ptr == nullptr)
		{
			cout << "Node exists with key value: " << k << endl;
		}
		else
		{
			if (ptr==head)
			{
				if (head->next == head)
				{
					head = nullptr;
					cout << "Head node unlinked... List now empty" << endl;
				}
				else
				{
					Node* ptr1 = head;
					while (ptr1->next != head)
					{
						ptr1 = ptr1->next;
					}
					ptr1->next = head->next;
					head = head->next;
					cout << "Node UNLINKED with keys value : " << k << endl;
				}
			}
			else
			{
				Node* temp = nullptr;
				Node* prevPtr = head;
				Node* currentPtr = head->next;
				while (currentPtr != nullptr)
				{
					if (currentPtr->key == k)
					{
						temp = currentPtr;
						currentPtr = nullptr;
					}
					else
					{
						prevPtr = prevPtr->next;
						currentPtr = currentPtr->next;
					}
				}

				prevPtr->next=temp->next;
				cout << "Node unlinked with keys value" << k << endl;
			}
		}
	}

	// 6. Update Node
	void updateNodeByKey(int k, int new_data)
	{
		Node* ptr = nodeExists(k);
		if (ptr != nullptr)
		{
			ptr->data = new_data;
			cout << "Node data updated successfully" << endl;
		}
		else
		{
			cout << "Node doesn't exist with key value" << k << endl;
		}
	}

	// 7. Print entire list
	void printList()
	{
		if (head == nullptr)
		{
			cout << "No nodes in Circular Linked List" << endl;
		}
		else
		{
			cout << "Address of Head Node" << head << endl;
			cout << "Circular Linked List Values : " << endl;

			Node* temp = head;

			do
			{
				cout << "(" << temp->key << "," << temp->data << "," << temp->next << ") --> ";
				temp = temp->next;
			} while (temp != head);
		}
	}
};

int main()
{
	CircularLinkedList obj;
	int option;
	int key1, k1, data1;
	
	do
	{
		cout << "\nWhat operation to perform? 0 to exit" << endl;
		cout << "1. appendNode()" << endl;
		cout << "2. prependNode()" << endl;
		cout << "3. insertNodeAfter()" << endl;
		cout << "4. deleteNodeByKey()" << endl;
		cout << "5. updateNodeByKey()" << endl;
		cout << "6. printList()" << endl;
		cout << "7. Clear Screen" << endl;

		cin >> option;
		Node* n1 = new Node();

		switch (option)
		{
		case 0:
			break;
		case 1:
			cout << "Append Node Operation \nEnter key and data of the Node to be appended" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			obj.appendNode(n1);
			break;
		case 2:
			cout << "Prepend Node Operation \nEnter key and data of the Node to be prepended" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			obj.prependNode(n1);
			break;
		case 3:
			cout << "Insert Node After Operation \nEnter key of existing node after which to insert" << endl;
			cin >> k1;
			cout << "Enter key and data for new node" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;

			obj.insertNodeAfter(k1, n1);
			break;
		case 4:
			cout << "Delete Node by Key Operation \nEnter key of Node to be deleted" << endl;
			cin >> k1;
			obj.deleteNodeByKey(k1);
			break;
		case 5:
			cout << "Update Node by Key Operation \nEnter key and NEW data to be updated" << endl;
			cin >> key1;
			cin >> data1;
			obj.updateNodeByKey(key1, data1);
			break;	
		case 6:
			obj.printList();
			break;
		case 7:
			system("cls");
			break;
		default:
			cout << "Enter Proper Option Number " << endl;
		}
	} while (option != 0);

	return 0;
}