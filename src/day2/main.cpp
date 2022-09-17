#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::sort;

string to_string(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	std::string ss(buf);
	return ss;
}

void tokenize(string &str, string &delims, vector<int> &ll)
{
	std::string tok("");
	for(int i = 0; i < (int)str.length(); i++)
	{
		std::string chr = to_string(str[i]);
		if(delims.find(chr) != std::string::npos)
		{
			if(tok.length() > 0)
			{
				ll.push_back(std::stoi(tok));
				tok = "";
			}
		}
		else
			tok += chr;
	}
	if(tok.length() > 0)
		ll.push_back(std::stoi(tok));
}

/////////////////////////////////////////////////

class Present
{
public:
	Present(string &ss)
	{
		string delims = "x";
		vector<int> ll;
		tokenize(ss, delims, ll);
		if(ll.size() == 3)
		{
			l = ll[0];
			w = ll[1];
			h = ll[2];
		}
	}

	void print() { cout << w << " * " << h << " * " << l << endl; }

	int getWrap()
	{
		int i1 = l * w;
		int i2 = w * h;
		int i3 = h * l;
		return 2*i1 + 2*i2 + 2*i3 + std::min(i1, std::min(i2, i3));
	}

	int getRibbon()
	{
		vector<int> aa;
		aa.push_back(l);
		aa.push_back(w);
		aa.push_back(h);
		sort(aa.begin(), aa.end());
		return aa[0]*2 + aa[1]*2 + l*w*h;
	}

private:
	int l, w, h;
};

/////////////////////////////////////////////////

vector<Present *> ll;

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ln;
	while(inf.readLine(ln))
	{
		if(ln.length() > 0)
		{
			Present *p = new Present(ln);
			ll.push_back(p);
		}
	}
	inf.close();
}

int main()
{
	readInput();

	int total = 0;
	for(Present *p : ll)
		total += p->getWrap();
	cout << "PART1 answer = " << total << endl;

	total = 0;
	for(Present *p : ll)
		total += p->getRibbon();
	cout << "PART2 answer = " << total << endl;

	for(Present *p : ll)
		delete p;
	ll.clear();

	return 0;
}

//PART1 answer = 1598415
//PART2 answer = 3812909
