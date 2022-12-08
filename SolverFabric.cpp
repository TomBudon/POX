#include "SolverFabric.h"

std::unique_ptr<UniqueAPI> SolverFabric::create(GenericExample::SolverType solverType) {

    switch (solverType) {

    case GenericExample::SolverType::Hypre:
    {
        std::unique_ptr<HypreAPI> api = std::make_unique<HypreAPI>();
        return api;
    }
        
    case GenericExample::SolverType::PETSc:
    {
        std::unique_ptr<PETScAPI> api = std::make_unique<PETScAPI>();
        return api;
    }  

    default:
        return nullptr;
    }    
}