#ifndef P_API_H
#define P_API_H

#include "UniqueAPI.h"

class PETScAPI : public UniqueAPI {

public:
    ~PETScAPI() = default;

    std::unique_ptr<Alien::ILinearAlgebra> createAlgebra() override;
    std::unique_ptr<Alien::ILinearSolver> createSolver() override;

    static void info();
};

#endif