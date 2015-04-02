#include <vector>

using namespace std;

typedef long long ll;


struct RollingHash {
    ll base;
    ll mod;
    vector<ll> hash;
    vector<ll> pow;
 
    RollingHash() : base(1009), mod(1000000007) {}
 
    void init(const string &s) {
        int n = s.size();
 
        hash.assign(n+1,0);
        pow.assign(n+1,1);
 
        for(int i=0;i<n;i++) {
            hash[i+1] = (hash[i]+s[i]) * base % mod;
            pow[i+1] = pow[i] * base % mod;
        }
    }
 
    ll get(int l, int r) {
        ll t = ((hash[r] - hash[l] * pow[r-l]) % mod + mod) % mod;
        return t;
    }
};
