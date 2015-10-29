#include <iostream>
#include <vector>

using namespace std;

size_t v;
size_t e;
vector<vector<size_t> > g;
vector<char> color;

void dfs(size_t u, char c) {
    color[u] = c;

    for (vector<size_t>::iterator it = g[u].begin(); it != g[u].end(); ++it) {
        if (color[*it] == 0) {
            dfs(*it, -c);
        }
    }
}

int main() {
    cin >> v >> e;
    g.resize(v);
    color.resize(v, 0);

    for (size_t i = 0; i < e; ++i) {
        size_t a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);

        if (a != b) {
            g[b].push_back(a);
        }
    }

    for (size_t i = 0; i < v; ++i) {
        if (color[i] == 0) {
            dfs(i, 1);
        }
    }

    bool two_parts = true;

    for (size_t i = 0; i < v && two_parts; ++i) {
        for (vector<size_t>::iterator it = g[i].begin(); it != g[i].end() && two_parts; ++it) {
            two_parts = (color[i] != color[*it]);
        }
    }

    cout << (two_parts ? "YES" : "NO") << endl;

    return 0;
}