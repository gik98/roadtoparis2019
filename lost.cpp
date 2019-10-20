#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

unordered_map<string, int> langmap;
vector<vector<int>> adj_list;
vector<vector<int>> adj_map;

int main(void) {
	int langs, trans;
	cin >> langs >> trans;
	langs++;

	adj_list.resize(langs);
	adj_map.assign(langs, vector<int>(langs));

	langmap["English"] = 0;
	for (int i = 1; i<langs; i++) {
		string l;
		cin >> l;
		langmap[l] = i;
	}

	for (int i = 0; i<trans; i++) {
		string s, t;
		int c, si, ti;
		cin >> s >> t >> c;
		si = langmap[s];
		ti = langmap[t];

		adj_list[si].push_back(ti);
		adj_list[ti].push_back(si);
		adj_map[si][ti] = adj_map[ti][si] = c;
	}

	// Run BFS
	
	vector<int> distance(langs, 1000000000);
	vector<int> parent(langs, -1);
	
	distance[0] = 0;
	queue<int> q;
	q.push(0);

	while (!q.empty()) {
		int x = q.front();
		q.pop();

		for (int y: adj_list[x]) {
			if (distance[y] > distance[x] + 1 || ((distance[x] + 1 == distance[y]) && (adj_map[y][parent[y]] > adj_map[x][y]))) {
				parent[y] = x;
				distance[y] = distance[x] + 1;
				q.push(y);
			}
		}
	}

	for (int i = 1; i<langs; i++) {
		if (parent[i] == -1) {
			cout << "Impossible" << endl;
			return 0;
		}
	}

	int total = 0;
	for (int i = 1; i<langs; i++) {
		total += adj_map[i][parent[i]];
	}

	cout << total << endl;
}
