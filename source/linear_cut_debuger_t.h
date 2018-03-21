//
// Created by pyc6eh4uk on 21.03.18.
//

#ifndef EKS_WAY_AI_LINEAR_CUT_DEBUGER_T_H
#define EKS_WAY_AI_LINEAR_CUT_DEBUGER_T_H


#include "abstract_debuger_t.h"
#include "simplex_method_t.h"

class linear_cut_debuger_t : public abstract_debuger_t {
public:
    void debug(int iteration, simplex_method_t *simplex_method) override;
};


#endif //EKS_WAY_AI_LINEAR_CUT_DEBUGER_T_H
