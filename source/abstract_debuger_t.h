//
// Created by pyc6eh4uk on 21.03.18.
//

#ifndef EKS_WAY_AI_DEFAULT_DEBUGER_T_H
#define EKS_WAY_AI_DEFAULT_DEBUGER_T_H


class simplex_method_t;

class abstract_debuger_t {
public:
    virtual void debug(int iteration, simplex_method_t *simplex_method) = 0;
};


#endif //EKS_WAY_AI_DEFAULT_DEBUGER_T_H
