//
// Created by pyc6eh4uk on 09.03.18.
//

#include "simplex_method_unequality_t.h"

simplex_method_equality_t simplex_method_unequality_t::to_canonical() {
    std::vector<real_t> result = coefficients;
    if (type == simplex_method_unequality_t::type_t::LESS) {
        result.push_back(1);
    }
    if (type == simplex_method_unequality_t::type_t::GREATER) {
        result.push_back(-1);
    }
    return simplex_method_equality_t {result, right_side_value};
}
