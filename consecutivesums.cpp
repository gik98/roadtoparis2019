#include<iostream>
using namespace std;

void solve(int n) {
    for(int i = 2; i*i <= 2*n; i++) {
        if((2*n) % i == 0 && ((((2*n) / i)+ 1) - i) % 2 == 0) {
            int k = ((((2*n) / i) + 1) - i) / 2;
            cout << n << " = ";
            for(int j = 0; j < i-1; j++) {
                cout << k + j << " + ";
            }
            cout << k + i - 1 << endl;
            return;
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int main() {
    int T, N;
    cin >> T;
    for(int t = 0; t < T; t++) {
        cin >> N;
        solve(N);
    }
    return 0;
}