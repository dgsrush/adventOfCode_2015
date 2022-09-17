#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

vector<char> ll;

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ln;
	inf.readLine(ln);
	inf.close();

	for(int i = 0; i < ln.size(); i++)
		ll.push_back(ln[i]);
}

int main()
{
	readInput();
	int cnt = 1;
	bool part2done = false;
	int floor = 0;
	for(char c : ll)
	{
		if(c == '(') floor++;
		else floor--;

		if(!part2done)
		{
			if(floor == -1)
			{
				cout << "PART2 answer = " << cnt << endl;
				part2done = true;
			}
			cnt++;
		}
	}
	cout << "PART1 answer = " << floor << endl;
	return 0;
}

//PART1 answer = 74
//PART2 answer = 1795
