//
// Created by pyc6eh4uk on 09.03.18.
//

#ifndef RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_TASK_T_H
#define RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_TASK_T_H


#include <vector>
#include "abstract_simplex_task_t.h"
#include "simplex_definitions.h"

struct abstract_simplex_task_t {
    virtual double get_cost(int index) const = 0;
    virtual double get_equality(int index) const = 0;
    virtual row_t get_column(int index, const row_t &costs) const = 0;
    virtual int variable_size() const = 0;
    virtual int original_variable_size() const = 0;
    virtual int basis_size() const = 0;
    virtual void print_cost() const = 0;
    virtual void print_equality() const = 0;
};


#endif //RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_TASK_T_H
