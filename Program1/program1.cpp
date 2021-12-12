/*
	Bradley Harper
	CSC 2400 Program 1
	3/2/2020
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//functions
void swapper(string *first, string *second);
void bubbleSort(string arr[], int n);
void permutations(string str);
bool next_permutation(string &str, int n);



int main()
{
	//variables
	const int SIZE = 100;
	string end = "";
	string myArr[SIZE];
	int i = 0;

	

	do
	{
		cout << "Enter a string or type quit: ";
		cin >> end;

		if(end == "quit" || i == 101)
		{
			break;
		}
		else
		{
			myArr[i] = end;
			i++;
		}

	}while(end != "quit");

	cout << "\nThe size of your array is " << i << " elements.\n\n\n";
	cout << "Sorting the array with the Bubble Sort Algorithm.\n";

	/*	Testing if the array would store values
	for(int j = 0; j < i; j++)
	{
		cout  << myArr[j] << " ";
	}*/

	//sorting algorithm
	bubbleSort(myArr, i);

	cout << "\n";

	int j = 0;

	for(j = 0; j < i;)
	{
		cout << myArr[j] << " ";
		j++;
	}

	cout << "\n\n\n";

	for(int x = 0; x < j; x++)
	{
		tester = myArr[x];

		permutations(tester);
	}
	
}

//sort helper function
void swapper(string *first, string *second)
{
	string temp = *first;
	*first = *second;
	*second = temp;
}
//sort function
void bubbleSort(string arr[], int n)
{
	for(int i = 0; i < n-1; i++)
	{
		for(int j = 0; j < n-i-1; j++)
		{
			if(arr[j] > arr[j+1])
				swapper(&arr[j], &arr[j+1]);
		}
	}
}

/*void lexicographic(arr[], int n)
{

}
*/

void permutations(string str)
{
	sort(str.begin(), str.end());

	while(1)
	{
		cout << str << " ";

		if(!next_permutation(str,str.length()))
			break;
	}
}

bool next_permutation(string &str, int n)
{
	int i = n-1;
	while (str[i-1] >= str[i])
	{
		if(--i == 0)
			return false;
	}

	int j = n-1;
	while(j > i && str[j] <= str[i - 1])
	{
		j--;
	}

	swap(str[i-1], str[j]);

	reverse(str.begin() + i, str.end());

	return true;
}