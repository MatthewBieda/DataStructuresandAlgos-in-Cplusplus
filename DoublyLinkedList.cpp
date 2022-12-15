#include <iostream>
using namespace std;

class Node
{
public:
	int key;
	int data;
	Node* next = nullptr;	
	Node* previous = nullptr;

	Node()
		: key(0), data(0) {}

	Node(int k, int d) 
		: key(k), data(d) {}
};

class DoublyLinkedList
{
public:
	Node* head;

	DoublyLinkedList()
		: head(nullptr) {}

	DoublyLinkedList(Node* n)
		: head(n) {}

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
			cout << "Node with key value" << n->key << "already exists. Please enter a different value." << endl;
		}
		else
		{
			if (head == nullptr)
			{
				head = n;
				cout << "Node appended as head node" << endl;
			}
			else
			{
				Node* ptr = head;
				while (ptr->next != nullptr)
				{
					ptr = ptr->next;
				}
				ptr->next = n;
				n->previous = ptr;
				cout << "Node appended" << endl;
			}
		}
	}

	// 3. Prepend node - Attach a node at the start

	void prePendNode(Node * n)
	{
		if (nodeExists(n->key)!=nullptr)
		{
			cout << "Node with key value" << n->key << "already exists. Please enter a different value." << endl;
		}
		else
		{
			if (head == nullptr)
			{
				head = n;
				cout << "Node prepended as head node" << endl;
			}
			else
			{
				head->previous = n;
				n->next = head;
				head = n;
				cout << "Node prepended" << endl;
			}
		}
	}

	// 4. Insert a Node after a particular node in the list

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
				cout << "Node already exists with key value: " << n->key << ". Append another node with different key value" << endl;
			}
			else
			{
				Node* nextNode = ptr->next;
				// inserting at the end
				if (nextNode == nullptr)
				{
					ptr->next = n;
					n->previous = ptr;
					cout << "Node inserted at the END" << endl;
				}

				// inserting in between
				else
				{
					n->next = nextNode;
					nextNode->previous = n;
					n->previous = ptr;
					ptr->next = n;	

					cout << "Node inserted in between" << endl;
				}
			}
		}
	}

	// 5. Delete node by unique key. Basically de-link not deletion

	void deleteNodeByKey(int k)
	{
		Node* ptr = nodeExists(k);
		if (ptr == nullptr)
		{
			cout << "No node exists with key value: " << k << endl;
		}
		else
		{
			if (head == nullptr) 
			{
				cout << "Doubly Linked List already empty. Cannot delete" << endl;
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
					Node* nextNode = ptr->next;
					Node* prevNode = ptr->previous;
					// deleting at the end
					if (nextNode == nullptr)
					{
						prevNode->next = nullptr;
						cout << "Node deleted at the END" << endl;
					}
						
					//deleting in between
					else
					{
						prevNode->next = nextNode;
						nextNode->previous = prevNode;
						cout << "Node deleted in between" << endl;
					}
				}
			}
		}
	}

	// 6. Update Node
	void updateNodeByKey(int k, int d)
	{
		Node* ptr = nodeExists(k);
		if (ptr != nullptr)
		{
			ptr->data = d;
			cout << "Node data successfully updated" << endl;
		}
		else
		{
			cout << "Node doesn't exists with key value" << k << endl;
		}
	}

	// 7. Printing the entire list
	void printList()
	{
		if (head == nullptr)
		{
			cout << "No nodes present in Doubly Linked List" << endl;
		}
		else
		{
			cout << "Doubly Linked List values : ";
			Node* temp = head;

			while (temp != nullptr)
			{
				cout << "(" << temp->key << "," << temp->data << ") <--> ";
				temp = temp->next;
			}
		}
	}
};


int main()
{
	DoublyLinkedList obj;
	int option;
	int key1, k1, data1;
	
	do
	{
		cout << "\nWhat operation do you want to perform? Select option number. 0 to exit." << endl;
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
			cout << "Append node operation - Enter key & data of node to be appended" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			obj.appendNode(n1);
			break;
		case 2:
			cout << "Prepend node operation - Enter key & data of node to be appended" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			obj.prePendNode(n1);
			break;
		case 3:
			cout << "Insert Node after operation - Enter key of existing Node after which you want to insert this new Node" << endl;
			cin >> k1;
			cout << "Enter key & data of new Node" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;

			obj.insertNodeAfter(k1, n1);
			break;
		case 4:
			cout << "Delete Node by key operation - Enter key of the node to be deleted" << endl;
			cin >> k1;
			obj.deleteNodeByKey(k1);
			break;
		case 5:
			cout << "Update Node by key operation - Enter key & NEW data to be updated" << endl;
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
			cout << "Enter a valid option number" << endl;
		}

	} while (option != 0);


	return 0;
}