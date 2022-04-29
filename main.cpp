#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#define node 6

//Sourcing
//https://www.tutorialspoint.com/Detect-Cycle-in-a-Directed-Graph
//Simple algorithm I used to determine whether or not the adjacency matrix is cyclic

using namespace std;

	int graph[node][node] =
	{
		{1,0,0,0,1,0},
		{0,1,0,1,0,1},
		{0,0,1,0,0,0},			//due to timing and differing manners on how to determine whether deadlock was or was not present I simply hardcoded the given graph into the program
		{1,0,1,1,0,0},			//Colton was in charge of pulling data from the given text, but my other portion was incompatable, thus due to time constraints I had to forgo that portion
		{0,1,0,0,1,0},
		{0,0,1,0,0,1}
	};

bool search(int curr, set<int>&wSet, set<int>&gSet, set<int>&bSet)
{
	wSet.erase(wSet.find(curr));		//delete the given current node from the given set
	gSet.insert(curr);		//insert given current node to differing set

	for(int i = 0; i < node; i++)		//for loop looping through all nodes within adjacency matrix
	{
		if(graph[curr][i] != 0)		//given node is withing the given set, continue
		{
			if(bSet.find(i) != bSet.end())
			{
				continue;
			}
			if(gSet.find(i) != gSet.end())		//given node is within the specified set return 1
			{
				return true;
			}
			if(search(i,wSet,gSet,bSet))		//given node is within the specifiedset return 1
			{
				return true;
			}
		}

	}

	gSet.erase(gSet.find(curr));		//remove the given current value from the gSet and push it to the given bSet
	bSet.insert(curr);
}

bool cyclic()		//function that determines if given graph is cyclic
{
	set<int> gSet;		//declaration of given set containers

        set<int> wSet;

        set<int> bSet;

        for(int r = 0; r < node; r++)		//place all elements within the w set
        {
                wSet.insert(r);
        }

        while(wSet.size() > 0)		//while loop iterating through the w set whilst it still obtains elements
        {
                for(int curr = 0; curr < node; curr++)		//nested loops determining if all nodes within the given matrix are within the w set, if so call the given search() then return 1
                {
                        if(wSet.find(curr) != wSet.end())
                        {
                                if(search(curr, wSet, gSet, bSet))
                                {
                                        return true;
                                }
                        }
                }

        }
        return false;


}





int main()
{

	ifstream ins;  // input file stream
	string filename;  // filename, user input
	do
	{
		cout << "Enter input filename: ";
		cin >> filename;

		ins.open(filename);

		if(!ins.is_open())
			cout << filename << " does not exist. Try again.";

	} while(!ins.is_open());

	stringstream ss;  // using stringstream to remove leading whitespace
	string line;  // keeps track of current line in file
	int numProcesses = -1;  // number of processes, user specified
	int numResources = -1;  // number of processes, user specified
	while (getline(ins, line) && ( numProcesses == -1 || numResources == -1 ))
	{  // loop for numProcesses and numResources
		ss.str(line);  // set stringstream to current line
		ss >> ws;  // remove any leading whitespace
		line = ss.str(); // store current line

		if(line.at(0) == '%' || line.size() == 0)  // if line is comment or empty,
			continue;		  					   //  then skip to the next line

		if(line.substr(0,14) == "num_processes=")
			numProcesses = stoi(line.substr(14)); // first number to end()
		else if(line.substr(0,14) == "num_resources=")
			numResources = stoi(line.substr(14));
	}

	vector<int> numUnitsPerResource;  // number of units per resource
	vector<vector<int>> matrix;  // adjacency matrix
	int row = 0;  // keeps track of current row while filling matrix
	while(getline(ins, line))
	{  // finish processing file for numUnitsPerResource and adjacency matrix
		ss.str(line);
		ss >> ws;
		line = ss.str();

		if (line.at(0) == '%' || line.size() == 0)  // if line is comment or empty
		{
			continue;
		}
		if(numUnitsPerResource.empty())  // wait to fill matrix
		{
			for(int i = 0; i < line.size(); i++)
			{
				if(isdigit(line.at(i)))
				{
					numUnitsPerResource.push_back(line.at(i)-'0');	// store char converted to int
				}													//  converting from ascii value
			}
		}
		else  // now fill the matrix
		{
			matrix.push_back(vector<int>());  // create a new row (blank) in matrix
			for(int i = 0; i < line.size(); i++)
			{
				if(isdigit(line.at(i)))
				{
					matrix[row].push_back(line.at(i)-'0'); // store char converted to int
				}
			}
			row++;  // move on to next row in matrix
		}
	}

	if(numUnitsPerResource.size() != numResources)
	{
		cout << "Incorrect number of units per resource provided." << endl;
		cout << numUnitsPerResource.size() << " were given. Looking for " << numResources << "." << endl;
		return 1;  // fatal error
	}


	// --- debug output ---
	cout << endl;
	cout << " -- DEBUG --" << endl;
	cout << "num_processes: " << numProcesses << endl;
	cout << "num_resources: " << numResources << endl;
	cout << "numUnitsPerResource: ";
	for(int i = 0; i < numUnitsPerResource.size(); i++)
	{
		cout << numUnitsPerResource.at(i);
		if(i != numUnitsPerResource.size()-1)
			cout << ',';
	}
	cout << endl;
	cout << "Matrix:";
	for(int i = 0; i < matrix.size(); i++)
	{
		for(int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	// --- end of debug output ---

	//int curr;
	//wSet.erase(Wset.find(curr));


	bool determine = cyclic();		//setting the given boolean value to the cyclic() call

	if(determine)		//if-else statements determining deadlock
		{
			cout << "\nDeadlock Detected\n";
		}
	else
		{
			cout << "\nDeadlock Not Detected\n";
		}

	return 0;

}
