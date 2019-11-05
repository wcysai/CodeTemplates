#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<int> perm;
typedef long long llong;

perm operator *(const perm& a, const perm& b) {
    assert(a.size() == b.size());
    perm c(a.size());
    for (int i = 0; i < a.size(); i++) {
        c[i] = a[b[i]];
    }
    return c;
}

perm inv(const perm& a) {
    perm c(a.size());
    for (int i = 0; i < a.size(); i++)
        c[a[i]] = i;
    return c;
}

perm identity(int n) {
    perm c(n);
    for (int i = 0; i < n; i++)
        c[i] = i;
    return c;
}

void DFS(const perm& cur, const vector<perm>& generators, vector<perm>& sigma) {
    sigma[cur[0]] = cur;
    for (const perm& g : generators) {
        perm y = g * cur;
        if (sigma[y[0]].empty()) {
            DFS(y, generators, sigma);
        }
    }
}

void reduceGenerators(vector<perm>& generators) {
    if (generators.empty())
        return;
    int n = generators.front().size();
    int pt = 0;
    for (int i = 0; i < n; i++) {
        vector<int> posByFirst(n, -1);
        for (int j = pt; j < generators.size(); j++) {
            perm& g = generators[j];
            assert(g[i] >= i);
            if (g[i] == i)
                continue;
            else if (posByFirst[g[i]] == -1) {
                posByFirst[g[i]] = pt;
                g.swap(generators[pt]);
                pt++;
            } else {
                g = inv(generators[posByFirst[g[i]]]) * g;
            }
        }
    }
    assert(pt <= n * (n - 1) / 2);
    generators.resize(pt);
}

llong calc(vector<perm> generators) {
    if (generators.empty())
        return 1ll;
    int n = generators.front().size();
    if (n == 0)
        return 1ll;

    vector<perm> sigma(n, perm());
    DFS(identity(n), generators, sigma);
    vector<perm> invSigma(n, perm());
    for (int i = 0; i < n; i++)
        invSigma[i] = inv(sigma[i]);

    int nSigma = 0;

    vector<perm> newGenerators;
    for (int i = 0; i < n; i++) {
        if (sigma[i].empty())
            continue;
        nSigma++;
        for (const perm& g : generators) {
            perm x = g * sigma[i];
            assert(!invSigma[x[0]].empty());
            newGenerators.emplace_back(invSigma[x[0]] * x);
        }
    }

    reduceGenerators(newGenerators);
    for (perm& g : newGenerators) {
        assert(g[0] == 0);
        g.erase(g.begin() + 0);
        for (int& x : g)
            --x;
    }

    return nSigma * calc(newGenerators);
}


int main() {
    int k, n;
    scanf("%d %d", &k, &n);
    vector<perm> generators;
    for (int i = 0; i < k; i++) {
        perm x(n);
        for (int j = 0; j < n; j++)
            scanf("%d", &x[j]), --x[j];
        generators.emplace_back(x);
    }
    llong ans = calc(generators);
    printf("%lld\n", ans);
    return 0;
}
