#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int> > tree;
vector<vector<int> > directed_tree;
vector<int> predecessor;
vector<int> h1;
vector<int> h2;
vector<int> h3;
vector<int> root_diameter;
vector<int> longest_upper_path;
vector<int> cut_diameter;
vector<int> sub_root_1;
vector<int> sub_root_2;

void build_tree(int node, int pre) {
  predecessor[node] = pre;
  for(auto x: tree[node]) {
    if(x != pre) {
      directed_tree[node].push_back(x);
      build_tree(x, node);
    }
  }
}

void evaluate_h(int node) {
  for(auto x: directed_tree[node]) {
    evaluate_h(x);
    if(h1[x]+1 > h3[node]) {
      h3[node] = h1[x]+1;
      if(h3[node] > h2[node]) {
        int t = h2[node];
        h2[node] = h3[node];
        h3[node] = t;
        if(h2[node] > h1[node]) {
          t = h1[node];
          h1[node] = h2[node];
          h2[node] = t;
        }
      }
    }
  }
}

void evaluate_root_diameter(int node) {
  for(auto x: directed_tree[node]) {
    evaluate_root_diameter(x);
    root_diameter[node] = max(root_diameter[node], root_diameter[x]);
    if(root_diameter[x] > sub_root_2[node]) {
      sub_root_2[node] = root_diameter[x];
      if(sub_root_2[node] > sub_root_1[node]) {
        int t = sub_root_1[node];
        sub_root_1[node] = sub_root_2[node];
        sub_root_2[node] = t;
      }
    }
  }
  root_diameter[node] = max(root_diameter[node], h1[node]+h2[node]);
}

void evaluate_lup(int node) {
  int r;
  if(h1[node]+1 == h1[predecessor[node]]) {
    r = h2[predecessor[node]];
  }
  else {
    r = h1[predecessor[node]];
  }
  longest_upper_path[node] = 1 + max(longest_upper_path[predecessor[node]], r);
}

void evaluate_cut_diameter(int node) {
  int r1, r2;
  if(h1[node]+1 == h1[predecessor[node]]) {
    r1 = h2[predecessor[node]];
    r2 = h3[predecessor[node]];
  }
  else if(h1[node]+1 == h2[predecessor[node]]) {
    r1 = h1[predecessor[node]];
    r2 = h3[predecessor[node]];
  }
  else {
    r1 = h1[predecessor[node]];
    r2 = h2[predecessor[node]];
  }
  cut_diameter[node] = max(cut_diameter[predecessor[node]], max(r1+longest_upper_path[predecessor[node]], r1+r2));

  int sub;
  if(root_diameter[node] == sub_root_1[predecessor[node]]) {
    sub = sub_root_2[predecessor[node]];
  }
  else {
    sub = sub_root_1[predecessor[node]];
  }
  cut_diameter[node] = max(cut_diameter[node], sub);
}

int main(void) {
  cin >> n;
  tree.assign(n, vector<int>());
  for(int i = 0; i < n-1; i++) {
    int a, b;
    cin >> a >> b;
    tree[a-1].push_back(b-1);
    tree[b-1].push_back(a-1);
  }
  directed_tree.assign(n, vector<int>());
  predecessor.assign(n, -1);
  build_tree(0, -1);

  h1.assign(n, 0);
  h2.assign(n, 0);
  h3.assign(n, 0);
  evaluate_h(0);

  root_diameter.assign(n, 0);
  sub_root_1.assign(n, 0);
  sub_root_2.assign(n, 0);
  evaluate_root_diameter(0);

  longest_upper_path.assign(n, 0);
  queue<int> q;
  for(auto x: directed_tree[0]) {
    q.push(x);
  }
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    evaluate_lup(u);
    for(auto x: directed_tree[u]) {
      q.push(x);
    }
  }

  cut_diameter.assign(n, 0);
  for(auto x: directed_tree[0]) {
    q.push(x);
  }
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    evaluate_cut_diameter(u);
    for(auto x: directed_tree[u]) {
      q.push(x);
    }
  }

  int res = 10000000;
  int target = -1;
  int final_a = -1;
  int final_b = -1;
  for(int i = 1; i < n; i++) {
    int diam_a = root_diameter[i];
    int diam_b = cut_diameter[i];

    int a = diam_a%2==0 ? diam_a/2 : (diam_a/2)+1;
    int b = diam_b%2==0 ? diam_b/2 : (diam_b/2)+1;

    int x = max(a+b+1, max(diam_a, diam_b));
    if(x < res) {
      res = x;
      target = i;
      final_a = a;
      final_b = b;
    }
  }

  int dummy = target;
  q.push(dummy);
  vector<bool> visited(n, false);
  visited[dummy] = true;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(auto x: tree[u]) {
      if(!visited[x] && !(x==predecessor[target])) {
        visited[x] = true;
        dummy = x;
        q.push(x);
      }
    }
  }

  vector<int> pre(n, -1);
  visited.assign(n, false);
  visited[dummy] = true;
  q.push(dummy);
  int tail = dummy;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(auto x: tree[u]) {
      if(!visited[x] && !(x==predecessor[target])) {
        visited[x] = true;
        pre[x] = u;
        tail = x;
        q.push(x);
      }
    }
  }

  int new_1 = tail;
  for(int i = 0; i < final_a; i++) {
    new_1 = pre[new_1];
  }

  dummy = predecessor[target];
  q.push(dummy);
  visited.assign(n, false);
  visited[dummy] = true;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(auto x: tree[u]) {
      if(!visited[x] && !(x==target)) {
        visited[x] = true;
        dummy = x;
        q.push(x);
      }
    }
  }

  pre.assign(n, -1);
  visited.assign(n, false);
  visited[dummy] = true;
  q.push(dummy);
  tail = dummy;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(auto x: tree[u]) {
      if(!visited[x] && !(x==target)) {
        visited[x] = true;
        pre[x] = u;
        tail = x;
        q.push(x);
      }
    }
  }

  int new_2 = tail;
  for(int i = 0; i < final_b; i++) {
    new_2 = pre[new_2];
  }

  cout << res << endl;
  cout << target+1 << " " << predecessor[target]+1 << endl;
  cout << new_1+1 << " " << new_2+1 << endl;

  return 0;
}
