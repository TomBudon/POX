#include "HypreAPI.h"


std::unique_ptr<Alien::ILinearAlgebra> HypreAPI::createAlgebra() {
    std::unique_ptr<Alien::Hypre::LinearAlgebra> algebra = std::make_unique<Alien::Hypre::LinearAlgebra>();
    return algebra;
}

std::unique_ptr<Alien::ILinearSolver> HypreAPI::createSolver() {
    std::unique_ptr<Alien::Hypre::LinearSolver> solver = std::make_unique<Alien::Hypre::LinearSolver>();
    return solver;
}

void HypreAPI::info() {
    std::cout << "Hypre Info : \n\n Base options" << std::endl;
}