#include <iostream>
#include <vector>
#include <chrono>

typedef std::vector<int> vec;

vec merge(const vec &left, const vec &right) {
    vec result;
    vec::const_iterator l = left.begin(), r = right.begin();

    while (l != left.end() && r != right.end()) {
        if (*l < *r) {
            result.push_back(*l++);
        } else {
            result.push_back(*r++);
        }
    }

    while (l != left.end()) {
        result.push_back(*l++);
    }

    while (r != right.end()) {
        result.push_back(*r++);
    }

    return result;
}

vec merge_sort(vec &v) {
    if (v.size() <= 1) {
        return v;
    }

    vec::iterator middle = v.begin() + v.size() / 2;
    vec left(v.begin(), middle);
    vec right(middle, v.end());

    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

vec parallel_sort(vec &v) {
    if (v.size() <= 1) {
        return v;
    }

    vec::iterator middle = v.begin() + v.size() / 2;
    vec left(v.begin(), middle);
    vec right(middle, v.end());

#pragma omp parallel sections
    {
#pragma omp section
        {
            left = parallel_sort(left);
        }
#pragma omp section
        {
            right = parallel_sort(right);
        }
    }

    return merge(left, right);
}

int main() {
    vec input;
    int s = 0;

    while (!std::cin.eof()) {
        if (std::cin >> s) {
            input.push_back(s);
        }
    }

    std::chrono::high_resolution_clock::time_point t1, t2;
    t1 = std::chrono::high_resolution_clock::now();
    vec m = merge_sort(input);
    t2 = std::chrono::high_resolution_clock::now();
    std::cerr << "single:\t" << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    vec p = parallel_sort(input);
    t2 = std::chrono::high_resolution_clock::now();
    std::cerr << "multi:\t" << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    for (int i = 0; i < input.size(); ++i) {
        if (m[i] != p[i]) {
            return -1;
        }
    }

    for (vec::const_iterator it = p.begin(); it != p.end(); ++it) {
        if (it != p.begin()) {
            std::cout << " ";
        }

        std::cout << *it;
    }

    return 0;
}
