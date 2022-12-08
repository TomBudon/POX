#include "gtest/gtest.h"

// #include "HypreExample.h"
// #include "PETScExample.h"

#include "GenericExample.h"

// This macro creates a test case MylibTestPrintTest, of type UnitTest
TEST(UnitTest, MylibTestPrintTest){ 
    GenericExample pets = {};
    auto norm = pets.run(GenericExample::SolverType::PETSc);
    EXPECT_NEAR(norm.norm, norm.norm_local, 0.000000000001); 
}

TEST(UnitTest, MylibTestAddTest){ 
    GenericExample hypre = {};
    auto norm = hypre.run(GenericExample::SolverType::Hypre);
    EXPECT_NEAR(norm.norm, norm.norm_local, 0.000000000001); 
}

