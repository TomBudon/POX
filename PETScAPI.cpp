#include "PETScAPI.h"

std::unique_ptr<Alien::ILinearAlgebra> PETScAPI::createAlgebra() {
    std::unique_ptr<Alien::SimpleCSRLinearAlgebra> algebra = std::make_unique<Alien::SimpleCSRLinearAlgebra>();
    return algebra;
}

std::unique_ptr<Alien::ILinearSolver> PETScAPI::createSolver() {
    Alien::PETSc::Options options;
    options.numIterationsMax(100);
    options.stopCriteriaValue(1e-10);
    options.preconditioner(Alien::PETSc::OptionTypes::Jacobi);
    options.solver(Alien::PETSc::OptionTypes::BiCGstab /*CG*/);
    std::unique_ptr<Alien::PETSc::LinearSolver> solver = std::make_unique<Alien::PETSc::LinearSolver>(options);
    return solver;
}

void PETScAPI::info() {
    std::cout << "PETSc Info : \n\n numIterationsMax : 100\n stopCriteriaValue : 1e-10\n preconditioner : Alien::PETSc::OptionTypes::Jacobi\n solver : Alien::PETSc::OptionTypes::BiCGstab\n" << std::endl;
}
