#include <iostream>
using namespace std;

class Node {
public:
	int key;
	int data;
	Node* next;

	Node()
	{
		key = 0;
		data = 0;
		next = nullptr;
	}
	Node(int k, int d)
	{
		key = k;
		data = d;
		next = nullptr;
	}
};

class SinglyLinkedList
{
public:
	Node* head;

	SinglyLinkedList()
	{
		head = nullptr;
	}
	SinglyLinkedList(Node* n)
	{
		head = n;
	}

	// 1. Check if node exists using key value
	Node* nodeExists(int k)
	{
		Node* temp = nullptr;

		Node* ptr = head;
		while (ptr != nullptr)
		{
			if (ptr->key == k)
			{
				temp = ptr;
			}
			ptr = ptr->next;
		}
		return temp;
	}

	// 2. Append a node to the list
	void appendNode(Node* n)
	{
		if (nodeExists(n->key) != nullptr)
		{
			cout << "Node already exists with key value : " << n->key << ". Append another node with different key value" << endl;
		}
		else
		{
			if (head == nullptr)
			{
				head = n;
				cout << "Node Appended" << endl;
			}
			else
			{
				Node* ptr = head;
				while (ptr->next != nullptr)
				{
					ptr = ptr->next;
				}
				ptr->next = n;
				cout << "Node appended" << endl;
			}
		}
	}

	// 3. Prepend node - Attach a node at the start
	void prependNode(Node* n)
	{
		if (nodeExists(n->key) != nullptr)
		{
			cout << "Node already exists with key value : " << n->key << ". Append another node with different key value" << endl;
		}
		else
		{
			n->next = head;
			head = n;
			cout << "Node prepended" << endl;
		}
	}

	//4. Insert a Node after a particular node in the list
	void insertNodeAfter(int k, Node* n)
	{
		Node* ptr = nodeExists(k);
		if (ptr == nullptr)
		{
			cout << "No node exists with key value: " << k << endl;
		}
		else
		{
			if (nodeExists(n->key) != nullptr)
			{
				cout << "Node already exists with key value : " << n->key << ". Append another node with different key value" << endl;
			}
			else
			{
				n->next = ptr->next;
				ptr->next = n;
				cout << "Node inserted" << endl;
			}
		}
	}

	//5. Delete node by unique key
	void deleteNodeByKey(int k)
	{
		if (head == nullptr)
		{
			cout << "Singly Linked List already empty. Cannot delete" << endl;	
		}
		else if (head != nullptr)
		{
			if (head->key == k)
			{
				head = head->next;
				cout << "Node UNLINKED with keys value: " << k << endl;
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
				if (temp != nullptr)
				{
					prevPtr->next = temp->next;
					cout << "Node Unlinked with keys value: " << k << endl;
				}
				else
				{
					cout << "Node does not exist with key value " << k << endl;
				}
			}
		}
	}

	//6. Update a node by key
	void updateNodeByKey(int k, int d)
	{
		Node* ptr = nodeExists(k);
		if (ptr != nullptr)
		{
			ptr->data = d;
			cout << "Node data updated successfully" << endl;
		}
		else
		{
			cout << "Node does not exist with key value: " << k << endl;
		}
	}

	//7. Printing the entire linked list
	void printList() {
		if (head == nullptr)
		{
			cout << "No nodes in the linked list" << endl;
		}
		else
		{
			cout << "Singly Linked List values: ";
			Node* temp = head;

			while (temp != nullptr)
			{
				cout << "("<<temp->key<<","<<temp->data<<") --> ";
				temp = temp->next;
			}
		}
	}
};


int main() 
{
	SinglyLinkedList s;
	int option;
	int key1, k1, data1;
	do
	{
		cout << "What operation do you want to perform? 0 to exit" << endl;
		cout << "1. appendNode()" << endl;
		cout << "2. prependNode()" << endl;
		cout << "3. insertNodeAfter()" << endl;
		cout << "4. deleteNodeByKey()" << endl;
		cout << "5. updateNodeByKey()" << endl;
		cout << "6. printList()" << endl;
		cout << "7. Clear the screen" << endl;

		cin >> option;
		Node* n1 = new Node();

		switch (option)
		{
		case 0:
			break;
		case 1:
			cout << "Append Node Operation \n Enter key & data of the Node to be appended" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			s.appendNode(n1);
			break;
		case 2:
			cout << "Prepend Node Operation \n Enter key & data of the Node to be Prepended" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			s.prependNode(n1);
			break;
		case 3:
			cout << "Insert Node After Operation \n Enter key of existing Node after which you want to insert this new Node" << endl;
			cin >> k1;
			cout << "Enter key & data of the New Node first: " << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;

			s.insertNodeAfter(k1, n1);
			break;
		case 4:
			cout << "Delete Node by key operation - \n Enter key of the Node to be deleted" << endl;
			cin >> k1;
			s.deleteNodeByKey(k1);
			break;
		case 5:
			cout << "Update Node by key operation - \n Enter key & NEW data to be updated" << endl;
			cin >> key1;
			cin >> data1;
			s.updateNodeByKey(key1, data1);
			break;
		case 6:
			s.printList();
			break;
		case 7: 
			system("cls");
			break;
		default:
			cout << "Enter a valid option number" << endl;
		}


	} while (option != 0);

	return 0;
}