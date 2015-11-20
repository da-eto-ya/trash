#include <algorithm>
#include <iostream>
#include <vector>

class max_queue {
private:
    std::vector<int> storage;

    void sift_down(size_t current) {
        if (current < 0 || current >= storage.size()) {
            return;
        }

        size_t children = 2 * current + 1;

        if (children < storage.size()) {
            children += ((children + 1) < storage.size() && storage[children] < storage[children + 1]) ? 1 : 0;

            if (storage[current] < storage[children]) {
                std::iter_swap(storage.begin() + current, storage.begin() + children);
                sift_down(children);
            }
        }
    }

    void sift_up(size_t current) {
        if (current <= 0 || current >= storage.size()) {
            return;
        }

        size_t parent = (current - 1) / 2;

        if (storage[current] > storage[parent]) {
            std::iter_swap(storage.begin() + current, storage.begin() + parent);
            sift_up(parent);
        }
    }

public:
    void insert(int p) {
        storage.push_back(p);
        sift_up(storage.size() - 1);
    }

    int extract() {
        if (0 == storage.size()) {
            return -1;
        }

        int result = storage[0];
        std::iter_swap(storage.begin(), --storage.end());
        storage.pop_back();
        sift_down(0);

        return result;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::string cmd;
    int element;
    max_queue q;

    for (int i = 0; i < n; ++i) {
        std::cin >> cmd;

        if (cmd == "Insert") {
            std::cin >> element;
            q.insert(element);
        } else {
            std::cout << q.extract() << std::endl;
        }
    }

    std::cout.flush();

    return 0;
}