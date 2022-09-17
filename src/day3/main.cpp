#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::sort;

vector<char> ll;
typedef std::unordered_map<std::string, int> HouseMap;

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ln;
	inf.readLine(ln);
	for(int i = 0; i < ln.size(); i++)
		ll.push_back(ln[i]);
	inf.close();
}

string loc2str(int x, int y) { return std::to_string(x) + ":" + std::to_string(y); }

int main()
{
	readInput();

	int x = 0, y = 0;
	HouseMap hm;
	hm[loc2str(x,y)] = 1;

	for(int i = 0; i < ll.size(); i++)
	{
		if(ll[i] == '^') y--;
		else if(ll[i] == 'v') y++;
		else if(ll[i] == '<') x--;
		else if(ll[i] == '>') x++;
		hm[loc2str(x,y)]++;
	}

	int cnt = 0;
	for(auto it = hm.cbegin(); it != hm.cend(); it++)
    	if(it->second > 0) cnt++;

    cout << "PART1 answer           = " << cnt << endl;
	cout << "PART1 answer should be = 2572" << endl;
	hm.clear();

	////

	x = 0;
	y = 0;
	hm[loc2str(x,y)] = 1;

	int xr = 0, yr = 0;
	HouseMap hmr;
	hmr[loc2str(xr,yr)] = 1;

	bool santa = true;
	for(int i = 0; i < ll.size(); i++)
	{
		if(santa)
		{
			if(ll[i] == '^') y--;
			else if(ll[i] == 'v') y++;
			else if(ll[i] == '<') x--;
			else if(ll[i] == '>') x++;
			hm[loc2str(x,y)]++;
		}
		else
		{
			if(ll[i] == '^') yr--;
			else if(ll[i] == 'v') yr++;
			else if(ll[i] == '<') xr--;
			else if(ll[i] == '>') xr++;
			hmr[loc2str(xr,yr)]++;
		}
		santa = !santa;
	}

	cnt = 0;
	for(auto it = hm.cbegin(); it != hm.cend(); it++)
		if(it->second > 0) cnt++;
	for(auto it = hmr.cbegin(); it != hmr.cend(); it++)
	{
		if(hm.count(it->first) == 1) continue;
		if(it->second > 0) cnt++;
	}
	cout << "PART2 answer           = " << cnt << endl;
	cout << "PART2 answer should be = 2631" << endl;

	return 0;
}
