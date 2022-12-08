#ifndef U_API_H
#define U_API_H

#include <memory>

#include "alien_files/MpiMock.h"
#include "alien_files/AlienMock.h"
#include "LocalLinearAlgebra.h"

class UniqueAPI {

public:
    ~UniqueAPI() = default;

    virtual std::unique_ptr<Alien::ILinearAlgebra> createAlgebra() = 0;
    virtual std::unique_ptr<Alien::ILinearSolver> createSolver() = 0;
};

#endif