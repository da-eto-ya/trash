#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<size_t> > g;
size_t v, e;
std::vector<size_t> path;

bool check_all_vertices() {
    std::vector<bool> color;
    color.resize(v);

    for (int i = 0; i < path.size(); ++i) {
        color[path[i]] = true;
    }

    for (int i = 0; i < color.size(); ++i) {
        if (!color[i]) {
            return false;
        }
    }

    return true;
}

bool all_vertices_even() {
    for (size_t i = 0; i < v; ++i) {
        int sum = 0;

        for (size_t j = 0; j < v; ++j) {
            sum += g[i][j];
        }

        if (sum % 2 != 0) {
            return false;
        }
    }

    return true;
}

void find_euler_path(size_t i) {
    for (size_t j = 0; j < v; ++j) {
        if (g[i][j] > 0) {
            --g[i][j], --g[j][i];

            find_euler_path(j);
        }
    }

    path.push_back(i);
}

bool check_all_edges() {
    for (size_t i = 0; i < v; ++i) {
        int sum = 0;

        for (size_t j = 0; j < v; ++j) {
            sum += g[i][j];
        }

        if (sum != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    std::cin >> v >> e;
    g.resize(v);

    for (size_t i = 0; i < v; ++i) {
        g[i].resize(v, 0);
    }

    for (size_t i = 0; i < e; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        --a, --b;
        ++g[a][b], ++g[b][a];
    }

    bool result = false;

    if (e > 0 && all_vertices_even()) {
        find_euler_path(0);
        result = check_all_edges() && check_all_vertices();
    }

    if (result) {
        for (size_t i = 0; i < path.size() - 1; ++i) {
            std::cout << path[i] + 1 << " ";
        }

        std::cout << std::endl;
    } else {
        std::cout << "NONE" << std::endl;
    }

    return 0;
}
