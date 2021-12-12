/*
     Title:     Program2.cpp
     Author:    Bradley Harper
     Date:      4/17/2020
     Purpose:   Traveling Salesman - find the lowest cost
                tour when traveling from US to 8 other countries
                and then back to US.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "GraphMatrix.h"
using namespace std;

const int SIZE = 10;
const string COUNTRY_CODES[SIZE]={"AU", "BR", "CA", "CN", "GL", "IT", "NA", "RU", "US", "US"};

/*
	Use the following structure to store each tour & its cost
	You will create an array of Tour variables in your program
*/
struct Tour
{
	string tour[SIZE];
	int cost;
};

//Function Prototypes
int searchCountryCode(string x);
GraphMatrix* readFileMakeMatrix();
void printStringArray(string* arr, int size);
//My prototypes
void permutations(string str[], int length, GraphMatrix* matrix, Tour* tourOptions);
bool next_permutation(string str[], int n);
void reverser(string str[], int length, int i);

int main()
{	
	Tour *tourOptions = new Tour[40320];
	//read in the flight information from the file and then create the weight matrix
	GraphMatrix * matrix = readFileMakeMatrix();
	string * countries = new string[SIZE-2];
	int number = 0, weightCountry1 = 0, weightCountry2 = 0, lowest = 0, lowestIndex = 0;
	
	cout << "\n\n*************************COUNTRIES*******************\n";
	for(int x=0; x < SIZE-2; x++)
	{
		countries[x] = COUNTRY_CODES[x];
		cout << countries[x] << endl;
		number++;
	}
	
	//generate all possible tours (starting & ending with "US") using lexicographic permute algorithm
	//you will need to call your lexicographic function, sending the modified countries array with the 8 country codes

	permutations(countries, number, matrix, tourOptions);


	cout << "\n\n*************************SOLUTION*******************\n";
	//find the lowest cost tour and print it out (including the cost)
	lowest = tourOptions[1].cost;

	/*cout << "First Lowest is: " << lowest << " with Tour ";
	for(int j = 0; j < 9; j++)
	{
		cout << tourOptions[1].tour[j] << " ";
	}*/

	for(int i = 0; i < 40320; i++)
	{
		//lowest = tourOptions[i].cost;
		weightCountry2 = tourOptions[i+1].cost;

		if(weightCountry2 < lowest)
		{
			lowest = weightCountry2;
			cout << "New Lowest is: " << weightCountry2 << " with Tour ";
			for(int j = 0; j < 10; j++)
			{
				cout << tourOptions[i].tour[j] << " ";
			}
			cout << endl;
			lowestIndex = i;
		}
		else;
	}

	cout << "\n*************************************************************\n";
	cout << "The tour with the lowest cost of $" << lowest << " is ";
	for(int j = 0; j < 10; j++)
	{
		cout << tourOptions[lowestIndex].tour[j] << " ";
	}
	
	
	cout << "\nHappy Traveling!\n";
	
	//don't forget to release anything that was dynamically allocated!
	
	return 0;
}
/*
	Function: searchCountryCode
	Parameters: a string with the country code like "US"
	Returns: an integer representing this country's index in the GraphMatrix
	
	Implement this search function with the binary search algorithm!
*/
int searchCountryCode(string x)
{
	int l = 0;
	int r = 9;

	while(l <= r)
	{
		int m = l + (r-l) / 2;

		int res;

		string y = COUNTRY_CODES[m];

		//cout << "\n\n\nwe here " << y << "     " << COUNTRY_CODES[m] << "\n\n\n";

		if(x == y)
			return m;

		else if(x > y)
			l = m + 1;

		else
			r = m - 1;
	}

	return -1;
}

/*
	Title: readFileMakeMatrix
	Purpose:  this function will read the data in flights.txt and create an
	adjacency matrix with the country codes.  The matrix values will be the
	cost of the flights.
*/
GraphMatrix* readFileMakeMatrix()
{
	ifstream inFile;
	GraphMatrix * matrix = new GraphMatrix(SIZE-1);
	cout << "\nCreated the matrix.";
	string country1, country2;
	int price;
	inFile.open("flights.txt");
	cout << "\nReading from flights.txt\n";
	if(inFile)
	{
		while(inFile >> country1)
		{
			inFile >> country2;
			inFile >> price;
			matrix->addEdge(searchCountryCode(country1), searchCountryCode(country2), price);
			cout << "\nAdded edge from " << country1 << " to " << country2 << " with cost of $" << price;
		}
	}
	else
		cout << "\nSorry, I am unable to open the file.\n";
	inFile.close();
	cout << "\n\nFLIGHT PRICE GRAPH MATRIX\n";
	matrix->printGraph();
	cout << endl;
	return matrix;
}

/*
	Title: printStringArray
	Purpose:  this function will print the array of strings with a space
		between each string
*/
void printStringArray(string* arr, int size)
{
	for(int x=0; x<size; x++)
	{
		cout << arr[x] << " ";
	}
	cout << endl;
}

void permutations(string str[], int length, GraphMatrix* matrix, Tour* tourOptions)
{
	int count = 1;
	int weight = 0, adder1 = 0, adder2 = 0, adder3 = 0;
	string countryA, countryB;

	while(1)
	{
		cout << "Permute " << count << ": ";
		count++;

		tourOptions[count-1].tour[0] = "US";

		for(int i = 0; i < length; i++)
		{
			cout << str[i] << " ";
			tourOptions[count-1].tour[i+1] = str[i];
		}

		tourOptions[count-1].tour[9] = "US";

		adder3 = matrix->getWeight(searchCountryCode("US"), searchCountryCode(str[0]));
		cout << adder3 << " ";
		weight = adder3;

		for(int a = 0; a < length; a++)
		{

			if(a == length-1)
			{
				adder2 = matrix->getWeight(searchCountryCode(str[a]), searchCountryCode("US"));
				cout << adder2 << " ";
				weight = weight + adder2;
				//cout << endl << weight;
			}
			else
			{
				adder1 = matrix->getWeight(searchCountryCode(str[a]), searchCountryCode(str[a+1]));
				cout << adder1 << " ";
				weight = weight + adder1;
				
			}
		}

		cout << "has tour weight: " << weight;
		tourOptions[count-1].cost = weight;
		cout << "\n";
		weight = 0;

		if(!next_permutation(str, length))
			break;
	}
}

bool next_permutation(string str[], int n)
{
	int i = n - 1;

	while(str[i-1] >= str[i])
	{
		if(--i == 0)
			return false;
	}

	int j = n-1;
	while(j > i && str[j] <= str[i-1])
	{
		j--;
	}

	swap(str[i-1], str[j]);

	reverser(str, n, i);

	return true;
}

void reverser(string str[], int length, int i)
{
	string temp = "";
	int j = length-1;

	while(i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}

}


