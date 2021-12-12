//testing lexicographic

#include <iostream>
#include <string>
#include <algorithm>
#include <cstddef>

using namespace std;

void permutations(string str[]);
bool next_permutation(string str[], int n);

int main()
{
	string str[3] = {"AL", "TN", "WV"};

	permutations(str);
}

void permutations(string str[])
{

	int x = 3;
	while(1)
	{
		for(int i = 0; i < 3; i++)
		{
			cout << str[i] << " ";
		}

		cout << "\n\n\n\n";

		if(!next_permutation(str, x))
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
		j--;

	swap(str[i-1], str[j]);

	reverse(str->begin() + i, str->end());

	return true;
}