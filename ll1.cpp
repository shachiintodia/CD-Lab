#include<iostream>
#include<bits/stdc++.h>
using namespace std;
string first(map<char,vector<string> > m, char ch){
	if(ch=='^' || !(ch>='A' && ch<='Z'))
		return ch+"";
	string ans="";
	for(int i=0;i<m[ch].size();i++){
		string s = m[ch][i];
		bool checknext=true;
		for(int j=0;j<s.length() && checknext;j++){
			
			checknext = false;
			if(s[j]=='^' || !(s[j]>='A' && s[j]<='Z')){
				if(ans.find(s[j])==string::npos)
					ans.push_back(s[j]);	
			}
			else{
				string temp = first(m,s[j]);
				for(int k=0;k<temp.length();k++){
					if(temp[k]=='^')
						checknext=true;
					else if(ans.find(temp[k])==string::npos)
						ans.push_back(temp[k]);
				}
				if(checknext && j==s.length()-1)
				ans.push_back('^');
			}
		}
	}
	return ans;
}
string firstofstring(map<char,vector<string> > m, string s){
	string ans="";
	bool checknext = true;
	for(int j=0;j<s.length() && checknext;j++){
			
		checknext = false;
		if(s[j]=='^' || !(s[j]>='A' && s[j]<='Z')){
			if(ans.find(s[j])==string::npos)
				ans.push_back(s[j]);	
		}
		else{
			string temp = first(m,s[j]);
			for(int k=0;k<temp.length();k++){
				if(temp[k]=='^')
					checknext=true;
				else if(ans.find(temp[k])==string::npos)
					ans.push_back(temp[k]);
			}
			if(checknext && j==s.length()-1)
				ans.push_back('^');
		}
	}
	if(ans=="")
		return "^";
	return ans;
}
string follow(map<char, vector<string> > prod, char start, char ch){
	string ans="";
	if(start==ch)
		ans.push_back('$');
	for(map<char, vector<string> >::iterator i=prod.begin(); i!=prod.end(); i++){
		
		for(int j=0;j<i->second.size();j++){
			
			if(i->second[j].find(ch)==string::npos)
				continue;
			string temp="";
			bool parent = false;
			for(int a=0;a<i->second[j].length();a++){
				parent=false;
				if(i->second[j][a]==ch){
					
					if(a==i->second[j].length()-1){
					parent=true;

					}else{
						//cout<<"substr "<<i->second[j].substr(a,i->second[j].length()-a-1)<<endl;
						temp = firstofstring(prod,i->second[j].substr(a+1,i->second[j].length()-a-1));
						//cout<<"temp "<<temp;
						for(int k=0;k<temp.length();k++){
							if(temp[k]=='^'){
								parent=true;
								continue;
							}
							if(ans.find(temp[k])==string::npos)
								ans.push_back(temp[k]);
						}
					}
					if(parent){
						//to tackle the case when parent is same as 'ch'
						if(ch==i->first)
							continue;					
						temp=follow(prod,start,i->first);	
						for(int k=0;k<temp.length();k++){
							if(ans.find(temp[k])==string::npos)
								ans.push_back(temp[k]);
						}
					}
				}
			}	
		}
	}
	return ans;
}
int main(){
	map <char, vector<string> > prod;
	int n;
	int t;
	cout<<"Enter number of terminals : ";
	cin>>t;
	map<char,int> terminals;
	for(int i=0;i<t;i++){
		char ch;
		cin>>ch;
		
		terminals[ch] = i;
	}
	terminals['$'] = t;
	cout<<"Enter number of productions : ";
	cin>>n;
	cout<<"Enter productions : "<<endl;
	char start;
	for(int i=0;i<n;i++){
		char ch;
		string s;
		cin>>ch;
		if(i==0)
		start=ch;
		cout<<" -> ";
		cin>>s;
		prod[ch].push_back(s);
	}
	
	cout<<"Given grammar is :"<<endl<<endl;
	for(map<char, vector<string> >::iterator i=prod.begin(); i!=prod.end(); i++){
		cout<<i->first<<" -> ";
		for(int j=0;j<i->second.size();j++){
			cout<<i->second[j];
			if(j!= i->second.size()-1)
			cout<<" | ";
		}
		cout<<endl;
	}
	vector< vector< string > > table(prod.size(), vector<string>(t+1, "") );
	for(map<char, vector<string> >::iterator i=prod.begin(); i!=prod.end(); i++){
		
		for(int j=0;j<i->second.size();j++){
			string s = firstofstring(prod, i->second[j]);
			bool hasnull=false;
			for(int k=0;k<s.length();k++){
				if(s[k]=='^'){
					hasnull=true;
					continue;
				}
				string gg="";
				gg= gg+i->first;
				gg= gg + " -> ";
				gg= gg +i->second[j];
				table[i->first - 'A'][terminals[s[k]]] = gg;
				
			}
			if(hasnull){
				string temp = follow (prod,start,i->first);
				for(int k=0;k<temp.length();k++){
					string ss= "";
					ss+=i->first;
					ss += " -> ^";
					table[i->first - 'A'][terminals[temp[k]]] =  ss ;
				}
			}
		}
	}
	cout<<endl<<endl;
	cout<<"Non terminals \\ Terminals | ";
	vector<char> vv(t+1);
	for(map<char,int>::iterator i= terminals.begin(); i!=terminals.end();i++)
		vv[i->second]=i->first;
	
	for(int i=0;i<vv.size();i++)	
	cout<<"     "<<vv[i]<<"     | ";
	cout<<endl;
	int ii=0;
	for(map<char, vector<string> >::iterator i=prod.begin(); i!=prod.end(),ii<table.size(); i++,ii++){
		
		cout<<"             "<<i->first<<"             |";
		for(int j=0;j<table[ii].size();j++){
			cout<<" "<<table[ii][j]<<" |";
		}
		cout<<endl;
	}	
}

