#include <iostream>
#include <map>

typedef std::map<std::string, char> str_map;

int main() {
    int k, l;
    str_map map;

    std::cin >> k >> l;

    char ch, nope;
    std::string s;

    for (int i = 0; i < k; ++i) {
        std::cin >> ch;
        std::cin >> nope;
        std::cin >> s;
        map[s] = ch;
    }

    std::cin >> s;

    std::string prefix;
    std::string result;
    str_map::iterator found;

    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        prefix.push_back(*it);

        if ((found = map.find(prefix)) != map.end()) {
            result.push_back(found->second);
            prefix.clear();
        }
    }

    std::cout << result << std::endl;

    return 0;
}