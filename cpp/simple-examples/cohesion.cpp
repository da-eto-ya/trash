#include <iostream>
#include <vector>
#include <limits>

typedef std::vector<std::vector<size_t> > graph;
typedef std::vector<size_t > colorization;

size_t find_uncolored(const colorization &c) {
    for (size_t i = 0; i < c.size(); ++i) {
        if (c[i] == 0) {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}

void dfs(size_t v, size_t color, graph &g, colorization &c) {
    c[v] = color;

    for (std::vector<size_t>::iterator it = g[v].begin(); it != g[v].end(); ++it) {
        if (c[*it] == 0) {
            dfs(*it, color, g, c);
        }
    }
}

int main() {
    size_t v, e;
    graph g;
    colorization colors;
    std::cin >> v >> e;
    g.resize(v);
    colors.resize(v, 0);

    for (size_t i = 0; i < e; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    size_t beg;
    size_t color_count = 0;

    while ((beg = find_uncolored(colors)) != std::numeric_limits<size_t>::max()) {
        ++color_count;
        dfs(beg, color_count, g, colors);
    }

    std::cout << color_count << std::endl;

    return 0;
}
