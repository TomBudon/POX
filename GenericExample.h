#ifndef GEN_EX_H
#define GEN_EX_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <concepts>

#include "alien_files/MpiMock.h"
#include "alien_files/AlienMock.h"
#include "LocalLinearAlgebra.h"

// type verification : T needs a info() function
template<typename T>
concept Infoable = requires(T t)
{
    { t.info() };
};

class GenericExample {    
public:

    enum SolverType {PETSc , Hypre};

    ~GenericExample() = default;

    template<Infoable T>
    void info() {
        T::info();
   }

    Norm run(GenericExample::SolverType solverType);
};

#endif