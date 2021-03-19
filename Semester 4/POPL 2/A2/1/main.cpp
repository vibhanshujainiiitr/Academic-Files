#include <bits/stdc++.h>

using namespace std;
#define ll long long
//union function
vector<ll> U(vector<ll> a, vector<ll> b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	ll i = 0, j = 0;
	vector<ll>v;
	while (i < a.size() && j < b.size()) {
		if (a[i] < b[j]) {
			//cout << a[i] << " ";
			v.push_back(a[i]);
			i++;
		}


		else if (b[j] < a[i]) {
			//cout << b[j] << " ";
			v.push_back(b[j]);
			j++;
		}

		else {
			//cout << b[j] << " ";
			v.push_back(b[j]);
			j++;
			i++;
		}
	}
	while (i < a.size()) {
		//cout << a[i] << " ";
		v.push_back(a[i]);
		i++;
	}



	while (j < b.size()) {
		v.push_back(b[j]);
		//cout << b[j] << " ";
		j++;
	}
	return v;
}
// intersection funciton
vector<ll> I(vector<ll> arr1, vector<ll> arr2) {
	sort(arr1.begin(), arr1.end());
	sort(arr2.begin(), arr2.end());
	vector<ll> v;
	ll i = 0, j = 0;
	while (i < arr1.size() && j < arr2.size()) {
		if (arr1[i] < arr2[j])
			i++;
		else if (arr2[j] < arr1[i])
			j++;
		else /* if arr1[i] == arr2[j] */
		{
			//cout << arr2[j] << " ";
			v.push_back(arr2[j]);
			i++;
			j++;
		}
	}
	return v;
}
// sym diff function
vector<ll> symmDiff(vector<ll> arr1, vector<ll> arr2)
{
	sort(arr1.begin(), arr1.end());
	sort(arr2.begin(), arr2.end());
	vector<ll> v;
	// Traverse both arrays simultaneously.
	ll i = 0, j = 0;
	while (i < arr1.size() && j < arr2.size()) {

		// Print smaller element and move
		// ahead in array with smaller element
		if (arr1[i] < arr2[j])
		{
			//cout << arr1[i] << " ";
			v.push_back(arr1[i]);
			i++;
		}
		else if (arr2[j] < arr1[i])
		{
			//cout << arr2[j] << " ";
			v.push_back(arr2[j]);
			j++;
		}

		// If both elements same, move ahead
		// in both arrays.
		else
		{
			i++;
			j++;
		}
	}
	//cout << i << j << "is is \n";
	while (i < arr1.size()) {
		//cout << arr1[i] << " i";
		v.push_back(arr1[i]);
		i++;
	}

	while (j < arr2.size()) {
		//cout << arr2[j] << " j";
		v.push_back(arr2[j]);
		j++;
	}

	return v;
}
//print vector
void pv(vector<ll> v) {
	for (ll i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}
int main()
{




	ll n, m;
	cin >> n >> m;
	vector<ll> adj[m];
	for (ll i = 1; i <= n; i++) {
		string s;
		ll id1, id2;
		cin >> s >> id1 >> id2;
		//cout << id1 << "   ";
		if (s == "A") {
			adj[id1].push_back(id2);
			//pv(adj[id1]);

		}
		if (s == "U") {
			adj[id1] = U(adj[id1], adj[id2]);
			//pv(adj[id1]);
		}
		if (s == "I") {
			adj[id1] = I(adj[id1], adj[id2]);
			//pv(adj[id1]);
		}
		if (s == "S") {
			adj[id1] = symmDiff(adj[id1], adj[id2]);
			//pv(adj[id1]);
		}
	}

	for (ll i = 0; i < m; i++) {
		for (auto x : adj[i]) {
			cout << x << " ";
		}
		cout << endl;
	}



}
