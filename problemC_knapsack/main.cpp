#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int n, T;

    cin >> n >> T;

    vector<int> t(n);

    vector<ll> v(n);

    for (int i = 0; i < n; i++) {

        cin >> t[i] >> v[i];

    }

    // TODO: compute maximum value achievable within time T
    
    vector<ll> table(T + 1, 0);
    for (int i = 0; i < n; i++) {
        int currentT = t[i];
        ll currentValue = v[i];
        for (int j = T; j >= currentT; j--) {
            table[j] = max(table[j], table[j - currentT] + currentValue);
        }
    }

    ll best = table[T];

    cout << best << "\n";

    return 0;

}
