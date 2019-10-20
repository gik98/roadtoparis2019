#include <bits/stdc++.h>
#define MAXV 110
#define FIRST_STUDENT 35
#define INF 1000000000

using namespace std;

// Adjacency list
vector<vector<int>> adj_list(MAXV, vector<int>());
// Residual network and flow capacity adjacency matrix
int adj_m_res[MAXV][MAXV], adj_m_cap[MAXV][MAXV];
// Translation to string to vertex id
unordered_map<string, int> names;
// Reverse translation
unordered_map<int, string> rev;
// p stores the BFS spanning tree from s
vector<int> p;

int f, source = 0, sink = 100;

// Flow
void augment(int v, int minEdge) { // traverse BFS spanning tree from s->t
	if (v == source) {
		f = minEdge;
		return;
	} // record minEdge in a global var f
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, adj_m_res[p[v]][v]));
		adj_m_res[p[v]][v] -= f;
		adj_m_res[v][p[v]] += f;
	}
}

int main() {
	int students, days;
	cin >> students >> days;
	
	int max_days = ceil((2.0 * days) / ((double) students));

	for (int i = 0; i<students; i++) {
		string name;
		int n, id = FIRST_STUDENT + i;

		cin >> name >> n;
		names[name] = id;
		rev[id] = name;

		adj_list[source].push_back(id);
		adj_list[id].push_back(source);
		adj_m_res[source][id] = max_days;
		for (int j = 0; j<n; j++) {
			int k;
			cin >> k;

			adj_list[id].push_back(k);
			adj_list[k].push_back(id);
			adj_m_res[id][k] = adj_m_cap[id][k] = 1;
		}
	}

	for (int d = 1; d<=days; d++) {
		adj_list[d].push_back(sink);
		adj_list[sink].push_back(d);
		adj_m_res[d][sink] = adj_m_cap[d][sink]= 2;
	}

	int mf = 0;
	while (mf < days * 2) {
		for (;;) {
			// Edmonds Karp
			f = 0;
			vector<bool> vis (MAXV, false);
			vis[source] = true;
			queue<int> q;
			q.push(source);
			p.assign(MAXV, -1);
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				if (u == sink) {
					break;
				}
				for (int j = 0; j < (int)adj_list[u].size(); j++) {
					int v = adj_list[u][j];
					if (adj_m_res[u][v] > 0 && !vis[v]) {
						vis[v] = true;
						q.push(v);
						p[v] = u;
					}
				}
			}
			augment(sink, INF);

			if (f == 0) {
				break;
			}
			mf += f;
		}

		if (mf < days * 2) {
			max_days++;
			for (int i = 0; i<students; i++) {
				int id = FIRST_STUDENT + i;
				adj_m_res[source][id] = max_days;
			}
		}
		
	}

	assert(mf <= days * 2);
	cout << max_days << endl;
	for (int d = 1; d<=days; d++) {
		cout << "Day " << d << ": ";
		for (int s = FIRST_STUDENT; s<=FIRST_STUDENT + students; s++) {
			if (adj_m_cap[s][d] > 0 && adj_m_res[s][d] == 0) {
				cout << rev[s] << " ";
			}
		}

		cout << endl;
	}
}
