#include<string>
#include<vector>
#include<iostream>
#include"ReadFile.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

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

bool hasThreeVowels(const string &ss)
{
	int cnt = 0;
	for(char c : ss)
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') cnt++;
	if(cnt > 2) return true;
	return false;
}

bool hasRepeatLetter(const string &ss)
{
	static string dbls[] = {
		"aa","bb","cc","dd","ee","ff","gg","hh","ii","jj","kk","ll","mm",
		"nn","oo","pp","qq","rr","ss","tt","uu","vv","ww","xx","yy","zz" };
	for(string dbl : dbls)
		if(ss.find(dbl) != std::string::npos) return true;
	return false;
}

bool hasBadStrings(const string &ss)
{
	static string bads[] = { "ab","cd","pq","xy" };
	for(string bad : bads)
		if(ss.find(bad) != std::string::npos) return true;
	return false;
}

string to_string(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	std::string ss(buf);
	return ss;
}

bool hasRepeatPair(const string &ss)
{
	static string ltrs = "abcdefghijklmnopqrstuvwxyz";
	for(char c1 : ltrs)
	{
		for(char c2 : ltrs)
		{
			string ls = to_string(c1) + to_string(c2);
			size_t i1 = ss.find(ls);
			size_t i2 = ss.rfind(ls);
			size_t i3 = i1 + 1;
			if(i1 != std::string::npos && (i1 != i2) && (i2 != i3))
				return true;
		}
	}
	return false;
}

bool hasGapRepeat(const string &ss)
{
	static string ltrs = "abcdefghijklmnopqrstuvwxyz";
	for(char c1 : ltrs)
	{
		for(char c2 : ltrs)
		{
			string f = to_string(c1) + to_string(c2) + to_string(c1);
			if(ss.find(f) != std::string::npos)
				return true;
		}
	}
	return false;
}

int main()
{
	vector<string> ll;
	readInput(ll);

	int cnt = 0;
	for(string ss : ll)
		if(hasThreeVowels(ss) && hasRepeatLetter(ss) && !hasBadStrings(ss))
			cnt++;

	cout << "PART1 answer    = " << cnt << endl;
	cout << "PART1 should be = 255 " << endl;

	/////

	cnt = 0;
	for(string ss : ll)
		if(hasRepeatPair(ss) && hasGapRepeat(ss))
			cnt++;

	cout << "PART2 answer    = " << cnt << endl;
	cout << "PART2 should be = 55" << endl;

	return 0;
}
