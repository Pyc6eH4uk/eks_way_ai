#include <iostream>
#include <vector>
#include <limits>
#include "source/simplex_task_t.h"
#include "source/linear_cut_task_t.h"
#include "source/linear_cut_debuger_t.h"

int main() {
    std::vector<linear_cut_task_t::package_t> packages;
    std::vector<linear_cut_task_t::package_t> patterns;

    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
    int m, n, piece, length, count, low_length, high_length;
    std::cin >> m;
    std::cin >> n;
    std::cin >> piece;

    for (int i = 0; i < m; i++) {
        std::cin >> length;
        std::cin >> low_length;
        std::cin >> high_length;
        patterns.push_back({length, low_length, high_length});
    }

    for (int i = 0; i < n; i++) {
        std::cin >> length;
        std::cin >> count;
        packages.push_back({length, 0, count});
    }

    auto task = new linear_cut_task_t(packages, patterns);
    //auto task = linear_cut_task_t::make_standart_simplex_task(packages, patterns);

    auto simplex_method = new simplex_method_t(task);
    auto debuger = new linear_cut_debuger_t();
    simplex_method->solve(debuger);

    return 0;
}