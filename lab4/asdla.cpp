#include <iostream>
#include <map>

template <typename K, typename V>
std::map<V, K> invertMap(const std::map<K, V>& input) {
    std::map<V, K> result;

    for (const auto& [key, value] : input) {
        result[value] = key;  // меняем местами
    }

    return result;
}

int main() {
    std::map<int, std::string> original = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    auto inverted = invertMap(original);

    for (const auto& [k, v] : inverted) {
        std::cout << k << " -> " << v << std::endl;
    }
}