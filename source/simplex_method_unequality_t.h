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

    simplex_method_equality_t to_canonical();
};


#endif //RUSLAN_DEBIL_REFACTOR_SIMPLEX_METHOD_UNEQUALITY_T_H
