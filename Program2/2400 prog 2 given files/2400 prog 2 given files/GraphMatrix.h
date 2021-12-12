#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include <iostream>
using namespace std;

class GraphMatrix
{
	private:
		int ** vertexMatrix;
		int numVertices;
		int numEdges;
		
	public:
		GraphMatrix(int numV)
		{
			numVertices = numV;
			numEdges = 0;
			vertexMatrix = new int*[numV];
			
			for(int i=0; i<numVertices; i++)
			{
				vertexMatrix[i] = new int[numVertices];
			}
			
			for(int i=0; i<numVertices; i++)
			{
				for(int j=0; j<numVertices; j++)
					vertexMatrix[i][j] = 0; //set all elements to zero until we know that there is an edge
			}
		}
		~GraphMatrix()
		{
			for(int i=0; i<numVertices; i++)
			{
				delete[] vertexMatrix[i];
			}
			delete[] vertexMatrix;	
		}
		
		/*
			Function addEdge()
			Input:  two vertices, which are integers where v1 has a directed edge toward v2-1
			Output: none
			Purpose:  to create an edge between v1 to v2
		*/
		void addEdge(int v1, int v2, int value)
		{
			if(vertexMatrix[v1][v2] == 0) //no edge created yet
				numEdges++;
			vertexMatrix[v1][v2] = value;
			vertexMatrix[v2][v1] = value;
		}
		
		void delEdge(int v1, int v2)
		{
			if(vertexMatrix[v1][v2] != 0)
				numEdges--;
			vertexMatrix[v1][v2] = 0;
		}
		void printGraph()
		{
			cout << endl;
			for(int i=0; i<numVertices; i++)
			{
				for(int j=0; j<numVertices; j++)
				{
					if(vertexMatrix[i][j] != INT_MAX)
						cout << vertexMatrix[i][j];
					else
						cout << "I";
					cout << "\t";
				}
				cout << endl;
			}
		}
		int getWeight(int v1, int v2)
		{
			return vertexMatrix[v1][v2];
		}
};

#endif