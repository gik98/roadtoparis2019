#include <bits/stdc++.h>

using namespace std;

vector<string> v;

int main(void) {
  v.assign(11, "");
  v[0] = "L";
  for(int i = 2; i <= 10; i++) {
    for(int j = 0; j < (1<<i)-1; j++) {
      if(j%2 == 0) {
        if(j%4 == 0) {
          v[i-1].push_back('L');
        }
        else {
          v[i-1].push_back('R');
        }
      }
      else {
        v[i-1].push_back(v[i-2][(j-1)/2]);
      }
    }
  }

  int T;
  cin >> T;
  for(int index = 0; index < T; index++) {
    int n;
    string s;
    cin >> n >> s;

    bool outcome = false;
    if(n < 10) {
      for(int i = 0; i <= v[n-1].size()-s.size(); i++) {
        if(s.compare(v[n-1].substr(i, s.size())) == 0) {
          outcome = true;
          break;
        }
      }
    }
    else {
      for(int i = 0; i <= v[9].size()-s.size(); i++) {
        if(s.compare(v[9].substr(i, s.size())) == 0) {
          outcome = true;
          break;
        }
      }
    }

    if(outcome) {
      cout << "Case " << index+1 << ": Yes" << endl;
    }
    else {
      cout << "Case " << index+1 << ": No" << endl;
    }
  }

  return 0;
}
