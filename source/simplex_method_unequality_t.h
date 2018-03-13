//
// Created by pyc6eh4uk on 09.03.18.
//

#ifndef RUSLAN_DEBIL_REFACTOR_SIMPLEX_METHOD_UNEQUALITY_T_H
#define RUSLAN_DEBIL_REFACTOR_SIMPLEX_METHOD_UNEQUALITY_T_H


#include <vector>
#include "simplex_definitions.h"
#include "simplex_method_equality_t.h"

struct simplex_method_unequality_t {
    enum class type_t {
        LESS, EQUAL, GREATER
    };

    row_t coefficients;
    real_t right_side_value;
    type_t type;

    simplex_method_unequality_t(const row_t &coefficients, real_t right_side_value, type_t type) {
        this->coefficients = coefficients;
        this->right_side_value = right_side_value;
        this->type = type;
    }

    static std::vector<simplex_method_equality_t> to_canonical(const std::vector<simplex_method_unequality_t> &unequalities) {
        std::vector<simplex_method_equality_t> result;
        for (int i = 0; i < unequalities.size(); i++) {
            auto unequality = unequalities[i];
            row_t row = unequality.coefficients;
            for (int j = 0; j < unequalities.size(); j++) {
                if (j == i) {
                    if (unequality.type == simplex_method_unequality_t::type_t::LESS) {
                        row.push_back(1);
                    }
                    if (unequality.type == simplex_method_unequality_t::type_t::GREATER) {
                        row.push_back(-1);
                    }
                    if (unequality.type == simplex_method_unequality_t::type_t::EQUAL) {
                        row.push_back(0);
                    }
                } else {
                    row.push_back(0);
                }
            }
            result.emplace_back(row, unequality.right_side_value);
        }
        return result;
    }
};


#endif //RUSLAN_DEBIL_REFACTOR_SIMPLEX_METHOD_UNEQUALITY_T_H
