#ifndef FAB_H
#define FAB_H

#include <memory>

#include "GenericExample.h"
#include "UniqueAPI.h"
#include "HypreAPI.h"
#include "PETScAPI.h"



class SolverFabric {

public:
    ~SolverFabric() = default;

    static std::unique_ptr<UniqueAPI> create(GenericExample::SolverType solverType);
};

#endif