#include <vector>
#include <iostream>
#include <algorithm>

int main () {
    std::vector<int> vec;
    for (int i=0;i<10;++i) {
        vec.push_back(i);
    }

    if (std::find(vec.begin(), vec.end(), 1) != vec.end()) {
        std::cout << "find" << std::endl;
    }

    return 0;
}
