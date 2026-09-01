#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll merge(vector<long long>& a, vector<long long>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    ll inv = 0;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            inv += (mid - i + 1);
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    while (j <= right) {
        temp[k++] = a[j++];
    }
    for (int p = left; p <= right; p++) {
        a[p] = temp[p];
    }

    return inv;
}

ll mergeSort(vector<long long>& a, vector<long long>& temp, int left, int right) {
    if (left >= right) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    ll inv = 0;

    inv += mergeSort(a, temp, left, mid);
    inv += mergeSort(a, temp, mid + 1, right);
    inv += merge(a, temp, left, mid, right);

    return inv;
}

int main() {

    ios::sync_with_stdio(false);

    cin.tie(nullptr);

    int n;

    cin >> n;

    vector<long long> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    vector<long long> temp(n);

    ll inv = mergeSort(a, temp, 0, n - 1);

    cout << inv << "\n";

    return 0;
    
}
