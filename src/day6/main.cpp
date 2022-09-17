#include<string>
#include<vector>
#include<iostream>
#include"ReadFile.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

void tokenize(string &str, string &delims, vector<string> &ll)
{
	string tok("");
	for(int i = 0; i < str.length(); i++)
	{
		string chr(1,str[i]);
		if(delims.find(chr) != string::npos)
		{
			if(tok.length() > 0)
			{
				if(tok != "turn" && tok != "through")
					ll.push_back(tok);
				tok = "";
			}
		}
		else
			tok += chr;
	}
	if(tok.length() > 0)
		ll.push_back(tok);
}

void readInput(vector<string> &ll)
{
	mhr::ReadFile inf("input.txt");
	string ln;
	while(inf.readLine(ln))
	{
		if(ln.length() > 0)
			ll.push_back(ln);
	}
	inf.close();
}

int grid[1000][1000];

void initGrid()
{
	for(int y = 0; y < 1000; y++)
	{
		for(int x = 0; x < 1000; x++)
		{
			grid[y][x] = 0;
		}
	}
}

int countOn()
{
	int cnt = 0;
	for(int y = 0; y < 1000; y++)
	{
		for(int x = 0; x < 1000; x++)
		{
			if(grid[y][x] > 0) cnt++;
		}
	}
	return cnt;
}

int getBrightness()
{
	int cnt = 0;
	for(int y = 0; y < 1000; y++)
	{
		for(int x = 0; x < 1000; x++)
		{
			cnt += grid[y][x];
		}
	}
	return cnt;
}

void process1(vector<string> ss)
{
	string cmd = ss[0];
	int x1 = std::stoi(ss[1]);
	int y1 = std::stoi(ss[2]);
	int x2 = std::stoi(ss[3]);
	int y2 = std::stoi(ss[4]);
	for(int x = x1; x <= x2; x++)
	{
		for(int y = y1; y <= y2; y++)
		{
			if(cmd == "on") grid[y][x] = 1;
			else if(cmd == "off") grid[y][x] = 0;
			else if(cmd == "toggle") grid[y][x] = !grid[y][x];
		}
	}
}

void process2(vector<string> ss)
{
	string cmd = ss[0];
	int x1 = std::stoi(ss[1]);
	int y1 = std::stoi(ss[2]);
	int x2 = std::stoi(ss[3]);
	int y2 = std::stoi(ss[4]);
	for(int x = x1; x <= x2; x++)
	{
		for(int y = y1; y <= y2; y++)
		{
			if(cmd == "on") grid[y][x]++;
			else if(cmd == "off" && grid[y][x] > 0) grid[y][x]--;
			else if(cmd == "toggle") grid[y][x] += 2;
		}
	}
}

void print()
{
	for(int y = 0; y < 1000; y++)
	{
		for(int x = 0; x < 1000; x++)
		{
			cout << grid[y][x];
		}
		cout << endl;
	}
}

int main()
{
	vector<string> ll;
	readInput(ll);
	initGrid();

	string delims = " ,";
	for(string ss : ll)
	{
		vector<string> tkns;
		tokenize(ss, delims, tkns);
		process1(tkns);
	}

	//print();
	int cnt = countOn();
	cout << "PART1 answer    = " << cnt << endl;
	cout << "PART1 should be = 377891" << endl;

	/////

	initGrid();

	for(string ss : ll)
	{
		vector<string> tkns;
		tokenize(ss, delims, tkns);
		process2(tkns);
	}

	cnt = getBrightness();
	cout << "PART2 answer    = " << cnt << endl;
	cout << "PART2 should be = 14110788" << endl;

	return 0;
}
