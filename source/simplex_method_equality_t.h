//
// Created by pyc6eh4uk on 09.03.18.
//

#ifndef RUSLAN_DEBIL_REFACTOR_SIMPLEX_METHOD_EQUALITY_T_H
#define RUSLAN_DEBIL_REFACTOR_SIMPLEX_METHOD_EQUALITY_T_H


#include <vector>
#include "simplex_definitions.h"

struct simplex_method_equality_t {
    row_t coefficients;
    real_t right_side_value;
};


#endif //RUSLAN_DEBIL_REFACTOR_SIMPLEX_METHOD_EQUALITY_T_H
