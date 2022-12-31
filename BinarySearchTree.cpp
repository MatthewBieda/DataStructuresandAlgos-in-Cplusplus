#include <iostream>
#define SPACE 10

using namespace std;

class TreeNode
{
public:
	int value;
	TreeNode* left;
	TreeNode* right;

	TreeNode()
	{
		value = 0;
		left = nullptr;
		right = nullptr;
	}
	TreeNode(int v)
	{
		value = v;
		left = nullptr;
		right = nullptr;
	}
};

class BST
{
public:
	TreeNode* root;

	BST()
	{
		root = nullptr;
	}

	bool isEmpty()
	{
		if (root == nullptr)
			return true;

		else
			return false;
	}

	void insertNode(TreeNode *new_node)
	{
		if (root == nullptr)
		{
			root = new_node;
			cout << "Value inserted at root node!" << endl;
		}
		else
		{
			TreeNode* temp = root;
			while (temp != nullptr)
			{
				if (new_node->value == temp->value)
				{
					cout << "Value already exists, try another value" << endl;
					return;
				}
				else if ((new_node->value < temp->value) && (temp->left == nullptr))
				{
					temp->left = new_node;
					cout << "Value Inserted to the left!" << endl;
					break;
				}
				else if (new_node->value < temp->value)
				{
					temp = temp->left;
				}
				else if ((new_node->value > temp->value) && (temp->right == nullptr))
				{
					temp->right = new_node;
					cout << "Value Inserted to the right!" << endl;
					break;
				}
				else
				{
					temp = temp->right;
				}
			}
		}
	}

	TreeNode* insertRecursive(TreeNode* r, TreeNode* new_node)
	{
		if (r == nullptr)
		{
			r = new_node;	
			return r;
		}

		if (new_node->value < r->value)
		{
			r->left = insertRecursive(r->left, new_node);
		}
		else if (new_node->value > r->value)
		{
			r->right = insertRecursive(r->right, new_node);
		}
		else
		{
			cout << "No duplicate values allowed!" << endl;
			return r;
		}
		return r;
	}

	void print2D(TreeNode* r, int space)
	{
		if (r == nullptr) // Base Case
		{
			return;
		}
		space += SPACE; // increase distance between levels
		print2D(r->right, space); // process right child first
		cout << endl;
		for (int i = SPACE; i < space; i++) // print current node after space count
		{
			cout << " ";
		}
		cout << r->value << "\n";
		print2D(r->left, space); // process left child
	}

	void printPreorder(TreeNode* r) // (Current Node, Left, Right)
	{
		if (r == nullptr)
		{
			return;
		}
		// First print the value of the node
		cout << r->value << " ";
		// Then recur on left subtree
		printPreorder(r->left);
		// Now recur on right subtree
		printPreorder(r->right);
	}

	void printInOrder(TreeNode* r) // (Left, Current Node, Right)
	{
		if (r == nullptr)
		{
			return;
		}
		// First recur on left subtree
		printInOrder(r->left);
		// Then print the value of the node
		cout << r->value << " ";
		// Now recur on right subtree
		printInOrder(r->right);
	}

	void printPostOrder(TreeNode* r) // (Left, Right, Current Node)
	{
		if (r == nullptr)
		{
			return;
		}
		// First recur on left subtree
		printPostOrder(r->left);
		// Then recur on right subtree
		printPostOrder(r->right);
		// Now print the value of the node
		cout << r->value << " ";
	}

	TreeNode* iterativeSearch(int val)
	{
		if (root == nullptr)
		{
			return root;
		}
		else
		{
			TreeNode* temp = root;
			while (temp != nullptr)
			{
				if (val == temp->value)
				{
					return temp;
				}
				else if (val < temp->value)
				{
					temp = temp->left;
				}
				else
				{
					temp = temp->right;
				}
			}
			return nullptr;
		}
	}

	int height(TreeNode* r)
	{
		if (r == nullptr)
		{
			return -1;
		}
		else
		{
			// Compute the height of each subtree
			int lheight = height(r->left);
			int rheight = height(r->right);

			// Use the larger one
			if (lheight > rheight)
			{
				return(lheight + 1);
			}
			else return(rheight + 1);
		}
	}

	// Print nodes at a given level 
	void printGivenLevel(TreeNode* r, int level)
	{
		if (r == nullptr)
		{
			return;
		}
		else if (level == 0)
		{
			cout << r->value << " ";
		}
		else // Level 0
		{
			printGivenLevel(r->left, level - 1);
			printGivenLevel(r->right, level - 1);
		}
	}
	void printLevelOrderBFS(TreeNode* r)
	{
		int h = height(r);
		for (int i = 0; i <= h; i++)
		{
			printGivenLevel(r, i);
		}
	}



	TreeNode* minValueNode(TreeNode* node)
	{
		TreeNode* current = node;
		// Loop down to find the leftmost leaf
		while (current->left != nullptr)
		{
			current = current->left;	
		}
		return current;
	}

	TreeNode* deleteNode(TreeNode* r, int v)
	{
		// Base Case
		if (r == nullptr)
		{
			return nullptr;
		}
		// If the key to be deleted is smaller than the root's key, 
		// then it lies in the left subtree
		else if (v < r->value)
		{
			r->left = deleteNode(r->left, v);
		}
		// If the key to be deleted is greater than the root's key, 
		// then it lies in the right subtree
		else if (v > r->value)
		{
			r->right = deleteNode(r->right, v);
		}
		// If the key is the same as the root's key, then this node shall be deleted
		else
		{
			// Node with only one child or no child
			if (r->left == nullptr)
			{
				TreeNode* temp = r->right;
				delete r;
				return temp;
			}
			else if (r->right == nullptr)
			{
				TreeNode* temp = r->left;
				delete r;
				return temp;
			}
			else
			{
				// Node with two children; get the inorder successor in the right subtree
				TreeNode* temp = minValueNode(r->right);
				// Copy the inorder successor's value to this node
				r->value = temp->value;
				// Delete the inorder successor 
				r->right = deleteNode(r->right, temp->value);
			}
		}
		return r;

	}
};

int main()
{
	BST obj;
	int option, val;

	do
	{
		cout << "What operation do you want to perform? 0 to exit" << endl;
		cout << "1. Insert Node" << endl;
		cout << "2. Search Node" << endl;
		cout << "3. Delete Node" << endl;
		cout << "4. Print BST values" << endl;
		cout << "5. Height of tree" << endl;
		cout << "6. Clear Screen" << endl;
		cout << "0. Exit Program" << endl;

		cin >> option;
		TreeNode *new_node = new TreeNode();

		switch (option)
		{
		case 0:
			break;
		case 1:
			cout << "INSERT" << endl;
			cout << "Enter VALUE of TreeNode to insert in the BST: " << endl;
			cin >> val;
			new_node->value = val;
			//obj.insertNode(new_node);
			obj.root = obj.insertRecursive(obj.root, new_node);
			cout << endl;
			break;
		case 2:
			cout << "SEARCH" << endl;
			cout << "Enter VALUE of TREE NODE to SEARCH in BST: ";
			cin >> val;
			new_node = obj.iterativeSearch(val);
			if (new_node != NULL)
			{
				cout << "Value found!" << endl;
			}
			else
			{
				cout << "Value not found" << endl;
			}
			break;
		case 3:
			cout << "DELETE" << endl;
			cout << "Enter VALUE of TREE NODE to DELETE in BST: " << endl;
			cin >> val;
			new_node = obj.iterativeSearch(val);
			if (new_node != nullptr)
			{
				obj.deleteNode(obj.root, val);
				cout << "Value Deleted" << endl;
			}
			else
			{
				cout << "Value NOT found" << endl;
			}
			break;
		case 4:
			cout << "PRINT" << endl;
			obj.print2D(obj.root, 5);
			cout << "PRE-ORDER" << endl;
			obj.printPreorder(obj.root);
			cout << endl;
			cout << "IN-ORDER" << endl;
			obj.printInOrder(obj.root);
			cout << endl;
			cout << "POST-ORDER" << endl;
			obj.printPostOrder(obj.root);
			cout << endl;
			cout << "LEVEL-ORDER" << endl;
			obj.printLevelOrderBFS(obj.root);
			cout << endl;
			break;
		case 5:
			cout << "TREE HEIGHT" << endl;
			cout << "Height: " << obj.height(obj.root) << endl;
			break;
		case 6:
			system("cls");
			break;
		default:
			cout << "Invalid option number entered" << endl;
		}

	} while (option != 0);

	return 0;
}