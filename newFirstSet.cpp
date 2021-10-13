#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>

using namespace std;
bool findFirst(string tmp, string current);
void removeDuplicate(string& target);

vector<string> rules;
string noTerminal;
map<string,string> sets;

int main(int argc, char *argv[])
{
	
	string s;
	while(getline(cin, s)) //read in and generate production rule
	{
		if(s == "END_OF_GRAMMAR")
		{
			break;
		}
		sets[s.substr(0, 1)] = "";
		noTerminal.push_back(s[0]);
		string nt;
		nt.push_back(s[0]);
		for(uint ptr = 2 ; ptr < s.size() ; ptr++)
		{
			if(s.substr(ptr, 1) == "|")
			{
				rules.push_back(nt);
				nt.clear();
				nt.push_back(s[0]);
			}
			else if(ptr == s.size() -1 )
			{
				nt.push_back(s[ptr]);
				rules.push_back(nt);
				nt.clear();
			}
			else
			{
				nt.push_back(s[ptr]);
			}
		}
	}
	cout<<endl;
	for(uint counter = 0 ; counter<noTerminal.size(); counter++)
	{
		string tmp = noTerminal.substr(counter,1);
		findFirst(tmp, tmp);
		sort(sets[tmp].begin(), sets[tmp].end());
		removeDuplicate(sets[tmp]);
		//cout<<tmp<<" "<<sets[tmp]<<endl;
	}

	sort(noTerminal.begin(),noTerminal.end());
	for(uint counter = 0 ; counter<noTerminal.size(); counter++)
	{
		string tmp = noTerminal.substr(counter,1);
		cout<<tmp<<" "<<sets[tmp]<<endl;
	}
	
	cout<<"END_OF_FIRST"<<endl;
}

bool findFirst(string tmp, string current) //tmp 代表這次進入的NonT  current代表這一大圈的NonT
{
	//cout<<current<<" "<<sets[current]<<endl;
	bool flag=false;
	for(uint incounter = 0 ; incounter<rules.size() ; incounter++) // 走過每一條rule
	{
		if(tmp == rules[incounter].substr(0,1)) //當走到tmp時
		{
			//cout<<current<<" "<<sets[current]<<endl;	
			for(uint ptr = 1; ptr < rules[incounter].size() ; ptr++) //走過該rule
			{
				if(!(isupper(rules[incounter][ptr])) && rules[incounter].substr(ptr,1) != ";") // 當是T且不是;時
				{
					//cout<<current<<" "<<sets[current]<<endl;
					sets[current].append(rules[incounter].substr(ptr,1)); // 將terminal推進current set裡
					break;
				}
				else if(rules[incounter].substr(ptr,1) == ";" && current != rules[incounter].substr(0,1)) //當是;且不在current裡時
				{
					//cout<<current<<" "<<sets[current]<<endl;
					flag = true;
					break;
				}
				else if(rules[incounter].substr(ptr,1) == ";" && current == rules[incounter].substr(0,1)) //當是;且在current裡時
				{
					sets[current].append(rules[incounter].substr(ptr,1));
					break;
				}
				else //NonT
				{
					bool ep = false;
					//cout<<current<<" "<<sets[current]<<endl;
					ep = findFirst(rules[incounter].substr(ptr,1), current);
					//cout<<current<<" "<<sets[current]<<endl;
					if( ep && ptr!=rules[incounter].size()-1)
					{
						continue;
					}
					else if(ep && ptr==rules[incounter].size()-1) //最後一個
					{
						bool lastEp = false;
						lastEp = findFirst(rules[incounter].substr(ptr,1), current);
						if(lastEp && current == rules[incounter].substr(0,1)) //最後一個有; 且在current裡
						{
							sets[current].append(";");
						}
						else
						{
							flag = true;
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	return flag;
}


void removeDuplicate(string& target)
{
	uint counter = 0;
	while(counter < target.size() -1)
	{ 
		if(target[counter] == target[counter+1])
		{
			target.erase(target.begin()+counter+1);
		}
		else
		{
			counter++;
		}
	}
}











