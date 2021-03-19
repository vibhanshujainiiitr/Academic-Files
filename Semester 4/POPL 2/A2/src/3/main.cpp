#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	string filename;
	cin >> filename;
	ll n;
	cin >> n;
	n++;
	vector<string> v;
	for (ll i = 0; i < n; i++) {
		string temp;
		getline(cin,temp);
		v.push_back(temp);
	}
	map<string, vector<ll> > map;
	
	

		
	string myText;
	ifstream MyReadFile("filename.txt");
	ll line_number=1;
	while (getline (MyReadFile, myText)) {
  		 // Output the text from the file
 		  //cout << myText<<endl;
 		  map[myText].push_back(line_number);
 		  line_number++;
 		  
	}
	MyReadFile.close();
	
	for(ll i=0;i<map.size();i++){
		for(ll j=0;j<map[v[i]].size();j++){
			cout<<map[v[i]][j]<<" ";
		}
		cout<<endl;
	}
	
}