#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


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

	return 0;

}