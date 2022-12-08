#ifndef H_API_H
#define H_API_H

#include "UniqueAPI.h"

class HypreAPI : public UniqueAPI {

public:
    ~HypreAPI() = default;

    std::unique_ptr<Alien::ILinearAlgebra> createAlgebra() override;
    std::unique_ptr<Alien::ILinearSolver> createSolver() override;

    static void info();
};

#endif