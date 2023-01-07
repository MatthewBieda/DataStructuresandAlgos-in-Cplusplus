#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

class Edge
{
public:
	int DestinationVertexID;
	int weight;

	Edge(){}

	Edge(int destVID, int w)
	{
		DestinationVertexID = destVID;
		weight = w;
	}

	void setEdgeValues(int destVID, int w)
	{
		DestinationVertexID = destVID;
		weight = w;
	}

	void setWeight(int w)
	{
		weight = w;
	}

	int getDestinationVertexID()
	{
		return DestinationVertexID;
	}

	int getWeight()
	{
		return weight;
	}
};

class Vertex
{
public: 
	int state_id;
	string state_name;

	list<Edge> edgeList;

	Vertex()
	{
		state_id = 0;
		state_name = "";
	}

	Vertex(int id, string name)
	{
		state_id = id;
		state_name = name;
	}

	int getStateID()
	{
		return state_id;
	}

	string getStateName()
	{
		return state_name;
	}

	void setID(int id)
	{
		state_id = id;
	}

	void setStateName(string sname)
	{
		state_name = sname;
	}

	list<Edge> getEdgeList()
	{
		return edgeList;
	}

	void printEdgeList()
	{
		cout << "[";
		for (auto it = edgeList.begin(); it != edgeList.end(); it++)
		{
			cout<<it->getDestinationVertexID()<<"("<<it->getWeight()<<") --> ";
		}
		cout << "]";
		cout << endl;
	}
};

class Graph
{
public:
	vector<Vertex> vertices;

	Vertex getVertexByID(int vid)
	{
		Vertex temp;
		for (int i = 0; i < vertices.size(); i++)
		{
			temp = vertices.at(i);
			if (temp.getStateID() == vid)
			{
				return temp;
			}
		}
		return temp;
	}

	void addVertex(Vertex newVertex)
	{
		bool check = checkIfVertexExistByID(newVertex.getStateID());
		if (check == true)
		{
			cout << "Vertex with this ID already exists" << endl;
		}
		else
		{
			vertices.push_back(newVertex);
			cout << "New Vertex Added Successfully" << endl;
		}
	}

	bool checkIfVertexExistByID(int vid)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices.at(i).getStateID() == vid)
			{
				return true;
			}
		}
		return false;
	}

	bool checkIfEdgeExistByID(int fromVertex, int toVertex)
	{
		Vertex v = getVertexByID(fromVertex);
		list <Edge> e;
		e = v.getEdgeList();
		bool flag = false;
		for (auto it = e.begin(); it != e.end(); it++)
		{
			if (it->getDestinationVertexID() == toVertex)
			{
				return true;
				break;
			}
		}
		return false;
	}

	void addEdgeByID(int fromVertex, int toVertex, int weight)
	{
		bool check1 = checkIfVertexExistByID(fromVertex);
		bool check2 = checkIfVertexExistByID(toVertex);

		if ((check1 && check2 == true))
		{
			bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
			if (check3 == true)
			{
				cout << "Edge exists between " << getVertexByID(fromVertex).getStateID() << " and " << getVertexByID(toVertex).getStateID() << endl;
			}
			else
			{
				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices.at(i).getStateID() == fromVertex)
					{
						Edge e(toVertex, weight);
						vertices.at(i).edgeList.push_back(e);
					}
					else if (vertices.at(i).getStateID() == toVertex)
					{
						Edge e(fromVertex, weight);
						vertices.at(i).edgeList.push_back(e);
					}
				}
				cout << "Edge created between " << fromVertex << " and " << toVertex << endl;
			}
		}
		else
		{
			cout << "Invalid Vertex ID entered." << endl;
		}
	}

	void updateEdgeByID(int fromVertex, int toVertex, int newWeight)
	{
		bool check = checkIfEdgeExistByID(fromVertex, toVertex);
		if (check == true)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices.at(i).getStateID() == fromVertex)
				{
					for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++)
					{
						if (it->getDestinationVertexID() == toVertex)
						{
							it->setWeight(newWeight);
							break;
						}
					}
				}
				else if (vertices.at(i).getStateID() == toVertex)
				{
					for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++)
					{
						if (it->getDestinationVertexID() == fromVertex)
						{
							it->setWeight(newWeight);
							break;
						}
					}
				}
			}
			cout << "Edge Weight Updated Successfully" << endl;
		}
		else
		{
			cout << "Edge between " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") DOES NOT Exist" << endl;
		}
	}

	void deleteEdgeByID(int fromVertex, int toVertex)
	{
		bool check = checkIfEdgeExistByID(fromVertex, toVertex);
		{
			if (check == true)
			{
				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices.at(i).getStateID() == fromVertex)
					{
						for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++)
						{
							if (it->getDestinationVertexID() == toVertex)
							{
								vertices.at(i).edgeList.erase(it);
								break;
							}
						}
					}

					if (vertices.at(i).getStateID() == toVertex)
					{
						for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++)
						{
							if (it->getDestinationVertexID() == fromVertex)
							{
								vertices.at(i).edgeList.erase(it);
								break;
							}
						}
					}
				}
				cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
			}
			else
			{
				cout << "Edge doesn't exist" << endl;
			}
		}
	}

	void deleteVertexByID(int vid)
	{
		int vIndex = 0;
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices.at(i).getStateID() == vid)
			{
				vIndex = i;
				break;
			}
		}
		int end = vertices.at(vIndex).edgeList.size();

		for (int i = 0; i < end; i++)
		{
			auto it = vertices.at(vIndex).edgeList.begin();
			deleteEdgeByID(it->getDestinationVertexID(), vid);
		}

		vertices.erase(vertices.begin() + vIndex);
		cout << "Vertex Deleted Successfully" << endl;
	}

	void printGraph()
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			Vertex temp;
			temp = vertices.at(i);
			cout << temp.getStateName() << " (" << temp.getStateID() << ") --> ";
			temp.printEdgeList();
		}
	}

	void updateVertex(int VID, string vname)
	{
		bool check = checkIfVertexExistByID(VID);
		if (check == true)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				if (vertices.at(i).getStateID() == VID)
				{
					vertices.at(i).setStateName(vname);
					break;
				}
			}
			cout << "Vertex Updated Successfully" << endl;
		}
	}
};

int main()
{
	int option, id1, id2, w;
	Graph g;
	string sname;
	Vertex v1;

	do {
		cout << "What operation do you want to perform? 0 to exit" << endl;
		cout << "1. Add Vertex" << endl;
		cout << "2. Update Vertex" << endl;
		cout << "3. Delete Vertex" << endl;
		cout << "4. Add Edge" << endl;
		cout << "5. Update Edge" << endl;
		cout << "6. Delete Edge" << endl;
		cout << "7. Check if 2 Vertices are neighbours" << endl;
		cout << "8. Print all neighbours of a Vertex" << endl;
		cout << "9. Print Graph" << endl;
		cout << "10. Clear Screen" << endl;
		cout << "0. Exit Program" << endl;

		cin >> option;

		switch (option)
		{
		case 0:
			break;
		case 1:
			cout << "Add Vertex Operation" << endl;
			cout << "Enter State ID" << endl;
			cin >> id1;
			cout << "Enter State Name: ";
			cin >> sname;
			v1.setID(id1);
			v1.setStateName(sname);
			g.addVertex(v1);

			break;
		case 2:
			cout << "Update Vertex Operation" << endl;
			cout << "Enter State ID of Vertex to update: ";
			cin >> id1;
			cout << "Enter State Name :";
			cin >> sname;
			g.updateVertex(id1, sname);

			break;
		case 3:
			cout << "Delete Vertex Operation" << endl;
			cout << "Enter ID of Vertex to delete: ";
			cin >> id1;
			g.deleteVertexByID(id1);
			break;
		case 4:
			cout << "Add Edge Operation" << endl;
			cout << "Enter ID of Source Vertex: ";
			cin >> id1;
			cout << "Enter ID of Destination Vertex: ";
			cin >> id2;
			cout << "Enter Weight of Edge: ";
			cin >> w;
			g.addEdgeByID(id1, id2, w);

			break;
		case 5:
			cout << "Update Edge Operation" << endl;
			cout << "Enter ID of Source Vertex(State): ";
			cin >> id1;
			cout << "Enter ID of Destination Vertex(State): ";
			cin >> id2;
			cout << "Enter UPDATED Weight of Edge: ";
			cin >> w;
			g.updateEdgeByID(id1, id2, w);

			break;
		case 6:
			cout << "Delete Edge Operation" << endl;
			cout << "Enter ID of Source Vertex(State): ";
			cin >> id1;
			cout << "Enter ID of Destination Vertex(State): ";
			cin >> id2;
			g.deleteEdgeByID(id1, id2);

			break;
		case 7:
			cout << "Check if 2 Vertices are neighbours " << endl;
			break;
		case 8:
			cout << "Print all neighbours of a Vertex" << endl;
			break;
		case 9:
			cout << "Print Graph" << endl;
			g.printGraph();

			break;
		case 10:
			system("cls");
			break;
		default:
			cout << "Enter a valid option number" << endl;
		}
	} while (option != 0);

	return 0;
}