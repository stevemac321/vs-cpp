#include <algorithm>
#include <iostream>

template <const size_t N>
bool has_triplet(int (&arr)[N])
{
    if (N < 3) {
        return false;
    }

    std::sort(std::begin(arr), std::end(arr));

    auto left = std::begin(arr);
    
    while (left != std::end(arr) - 2) {
        auto right = std::end(arr) - 1;
        
        while (left < right - 1) {
            int sum = *left + *right;
            int triplet = -(sum);

            if (std::binary_search(left + 1, right, triplet)) {
                std::cout << *left << " + " << *right << " + " << triplet << " is true\n";
                return true;
            } else {
                --right;
            }
        }
        ++left;
    }
    return false;
}

int main()
{
    int a[] = {4, -2, 8, 99, -3, 6, 0, 8, 44, 6};
    auto ret = has_triplet(a);
    std::cout << std::boolalpha << " returned: " << ret << "\n";
}
