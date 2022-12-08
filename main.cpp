#include <iostream>
#include <stdlib.h>
#include <concepts>

#include "HypreAPI.h"
#include "PETScAPI.h"

#include "GenericExample.h"


int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    GenericExample generic_example = {};

    generic_example.info<HypreAPI>();
    std::cout << std::endl;
    generic_example.run(GenericExample::SolverType::Hypre);
    
    std::cout << std::endl << std::endl;

    generic_example.info<PETScAPI>();
    std::cout << std::endl;
    generic_example.run(GenericExample::SolverType::PETSc);


    MPI_Finalize();
}
