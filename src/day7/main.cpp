#include<string>
#include<vector>
#include<iostream>
#include<unordered_map>
#include"ReadFile.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;

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

bool isANumber(const string &s)
{
	string::const_iterator it = s.begin();
    while(it != s.end() && std::isdigit(*it))
    	++it;
    return !s.empty() && it == s.end();
}

/////

unordered_map<string,unsigned short> vals;

class Row
{
public:
	Row(string ss)
	{
		tokenize(ss, delims, tkns);
		processed = false;
	}

	void print()
	{
		for(string tkn : tkns)
			cout << tkn << endl;
		cout << "***************" << endl;
	}

	void process(bool isPart2, unsigned short value)
	{
		if(processed) return;

		if(tkns.size() == 3)
		{
			if(isANumber(tkns[0])) // 1 -> a
			{
				unsigned short val = std::stoi(tkns[0]);
				if(isPart2 && tkns[2] == "b")
					val = value;
				vals[tkns[2]] = val;
				processed = true;
			}
			else if(vals.count(tkns[0]) == 1) // b -> a
			{
				unsigned short val = vals[tkns[0]];
				vals[tkns[2]] = val;
				processed = true;
			}
		}
		else if(tkns.size() == 4) // NOT a -> b
		{
			if(vals.count(tkns[1]) == 1)
			{
				unsigned short val = vals[tkns[1]];
				vals[tkns[3]] = ~val;
				processed = true;
			}
		}
		else if(tkns.size() == 5)
		{
			if(tkns[1] == "AND")
			{
				if(vals.count(tkns[0]) == 1 && vals.count(tkns[2]) == 1) // a AND b -> c
				{
					unsigned short v1 = vals[tkns[0]];
					unsigned short v2 = vals[tkns[2]];
					vals[tkns[4]] = v1 & v2;
					processed = true;
				}
				else if(isANumber(tkns[0]) && vals.count(tkns[2]) == 1) // # AND b -> c
				{
					unsigned short v1 = std::stoi(tkns[0]);
					unsigned short v2 = vals[tkns[2]];
					vals[tkns[4]] = v1 & v2;
					processed = true;
				}
			}
			else if(tkns[1] == "OR")
			{
				if(vals.count(tkns[0]) == 1 && vals.count(tkns[2]) == 1) // a OR b -> c
				{
					unsigned short v1 = vals[tkns[0]];
					unsigned short v2 = vals[tkns[2]];
					vals[tkns[4]] = v1 | v2;
					processed = true;
				}
			}
			else if(tkns[1] == "LSHIFT")
			{
				if(vals.count(tkns[0]) == 1 && isANumber(tkns[2])) // a LSHIFT # -> c
				{
					unsigned short v1 = vals[tkns[0]];
					unsigned short v2 = std::stoi(tkns[2]);
					vals[tkns[4]] = v1 << v2;
					processed = true;
				}
			}
			else if(tkns[1] == "RSHIFT")
			{
				if(vals.count(tkns[0]) == 1 && isANumber(tkns[2])) // a RSHIFT # -> c
				{
					unsigned short v1 = vals[tkns[0]];
					unsigned short v2 = std::stoi(tkns[2]);
					vals[tkns[4]] = v1 >> v2;
					processed = true;
				}
			}
		}
	}

	bool hasProcessed() { return processed; }

	void reset() { processed = false; }

private:
	string delims = " -";
	vector<string> tkns;
	bool processed;
};

vector<Row *> rows;

bool allProcessed()
{
	int cnt = 0;
	for(Row *r : rows)
		if(r->hasProcessed()) cnt++;
	if(cnt == rows.size()) return true;
	return false;
}

/////

int main()
{
	vector<string> ll;
	readInput(ll);

	string delims = " -";
	for(string ss : ll)
	{
		Row *r = new Row(ss);
		rows.push_back(r);
	}

	while(true)
	{
		for(Row *row : rows)
			row->process(false, 0);
		if(allProcessed()) break;
	}

	unsigned short part1a = vals["a"];
	cout << "PART1 a           = " << part1a << endl;
	cout << "PART1 a should be = 956" << endl;

	/////

	for(Row *row : rows)
		row->reset();
	vals.clear();

	while(true)
	{
		for(Row *row : rows)
			row->process(true, part1a);
		if(allProcessed()) break;
	}

	cout << "PART2 a           = " << vals["a"] << endl;
	cout << "PART2 a should be = 40149" << endl;

	for(Row *row : rows)
		delete row;
	rows.clear();
	vals.clear();

	return 0;
}
