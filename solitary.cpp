#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> #
using namespace __gnu_pbds;
using namespace std;

#define send ios::sync_with_stdio(false);
#define help cin.tie(NULL);
#define f first
#define s second
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

#define MAXN 1000005
int n, k;
int arr[MAXN];
unordered_map<int, int, custom_hash> cnt;
unordered_map<int, int, custom_hash> longest;

unordered_map<int, int, custom_hash> current;

int main() {
    send help

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (cnt.find(arr[i]) == cnt.end()) cnt[arr[i]] = 1;
        else cnt[arr[i]]++;
        current[arr[i]] = 0;
    }

    for (int i = 0; i < n; i++) {
        current[arr[i]]++;
        current[arr[i] - k] = max(0, current[arr[i] - k] - 1); // subtract one

        if (longest.find(arr[i]) == longest.end() || longest[arr[i]] < current[arr[i]]) {
            longest[arr[i]] = current[arr[i]];
        }
    }

    // for (const pii& p : longest) {
    //     cout << p.first << " " << p.second << '\n';
    // } 

    // for (const pii& p : cnt) {
    //     cout << p.first << " " << p.second << '\n';
    // }     
    ll ans = 0;

    for (const pii& p : cnt) {
        ll cur = p.second + ((longest.find(p.first - k) != longest.end()) ? longest[p.first - k] : 0);
        ans = max(ans, cur);
    }   

    cout << ans << '\n';

    return 0;
}