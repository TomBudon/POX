#include <stdio.h>
#include <vector>
#include <iostream>
#include "HypreExample.h"
#include "LocalLinearAlgebra.h"

std::vector<int> HypreExample::run()
{

  std::vector<int> res = std::vector<int>(2);

  auto* pm = Arccore::MessagePassing::Mpi::StandaloneMpiMessagePassingMng::create(MPI_COMM_WORLD);
  auto* tm = Arccore::arccoreCreateDefaultTraceMng();

  Alien::setTraceMng(tm);
  Alien::setVerbosityLevel(Alien::Verbosity::Debug);

  auto size = 100;

  tm->info() << "Example Alien :";
  tm->info() << "Use of scalar builder (RefSemantic API) for Laplacian problem";
  tm->info() << " => solving linear system Ax = b";
  tm->info() << " * problem size = " << size;
  tm->info() << " ";
  tm->info() << "Start example...";
  tm->info() << " ";

  Alien::Matrix A(size, size, pm);

  LocalLinearAlgebra::Matrix A_local(size, size, 0);

  // Distributions calculée
  const auto& dist = A.distribution();
  int offset = dist.rowOffset();
  int lsize = dist.localRowSize();
  int gsize = dist.globalRowSize();

  tm->info() << "build matrix with direct matrix builder";
  {
    Alien::DirectMatrixBuilder builder(A, Alien::DirectMatrixOptions::eResetValues);
    builder.reserve(3); // Réservation de 3 coefficients par ligne
    builder.allocate(); // Allocation de l'espace mémoire réservé

    for (int irow = offset; irow < offset + lsize; ++irow) {
      builder(irow, irow) = 2.;
      A_local.add_value(irow, irow, 2.);
      if (irow - 1 >= 0) {
        builder(irow, irow - 1) = -1.;
        A_local.add_value(irow, irow - 1, -1.);
      }
      if (irow + 1 < gsize) {
        builder(irow, irow + 1) = -1.;
        A_local.add_value(irow, irow + 1, -1.);
      }
        
    }
  }

  tm->info() << "* xe = 1";

  Alien::Vector xe = Alien::ones(size, pm);

  tm->info() << "=> Vector Distribution : " << xe.distribution();

  tm->info() << "* b = A * xe";

  Alien::Vector b(size, pm);

  Alien::Hypre::LinearAlgebra algebra;

  algebra.mult(A, xe, b);

  Alien::Vector x(size, pm);

  tm->info() << "* x = A^-1 b";

  //  auto options = Alien::Hypre::Options()
  //          .numIterationsMax(100)
  //          .stopCriteriaValue(1e-10)
  //          .preconditioner(Alien::Hypre::OptionTypes::AMGPC)
  //          .solver(Alien::Hypre::OptionTypes::GMRES);
  //
  //  auto solver = Alien::Hypre::LinearSolver (options);

  auto solver = Alien::Hypre::LinearSolver();

  solver.solve(A, b, x);

  tm->info() << "* r = Ax - b";

  Alien::Vector r(size, pm);

  {
    Alien::Vector tmp(size, pm);
    tm->info() << "t = Ax";
    algebra.mult(A, x, tmp);
    tm->info() << "r = t";
    algebra.copy(tmp, r);
    tm->info() << "r -= b";
    algebra.axpy(-1., b, r);
  }

  auto norm = algebra.norm2(r);

  tm->info() << " => ||r|| = " << norm;

  tm->info() << "* r = || x - xe ||";

  {
    tm->info() << "r = x";
    algebra.copy(x, r);
    tm->info() << "r -= xe";
    algebra.axpy(-1., xe, r);
  }

  tm->info() << " => ||r|| = " << norm;

  tm->info() << " ";
  tm->info() << "... example finished !!!";


// Alien::LocalVectorReader b_reader(b);
// Alien::LocalVectorReader x_reader(x);

// LocalLinearAlgebra::Vector b_local{((double)b_reader.size())};
// LocalLinearAlgebra::Vector x_local{((double)x_reader.size())};

// for (size_t i = 0; i < b_reader.size(); i++)
// {
//   b_local[i] = b_reader[i];
// }

// for (size_t i = 0; i < x_reader.size(); i++)
// {
//   x_local[i] = x_reader[i];
// }

LocalLinearAlgebra::Vector x_local(A_local.n_column);
LocalLinearAlgebra::Vector b_local(A_local.n_row);

for (size_t i = 0; i < x_local.size(); i++)
{
  x_local[i] = 1;
}
LocalLinearAlgebra::mult(A_local, x_local, b_local);



// "t = A_local*x_local";
LocalLinearAlgebra::Vector tmp(size);
LocalLinearAlgebra::mult(A_local, x_local, tmp);
// "r_local = t";
LocalLinearAlgebra::Vector r_local(size);
LocalLinearAlgebra::copy(tmp, r_local);
// "r_local -= b_local";
LocalLinearAlgebra::axpy(-1., b_local, r_local);
// norm_local = ||r_local||
auto norm_local = LocalLinearAlgebra::norm2(r_local);


std::cout << "norm Alien : " << norm << std::endl;
std::cout << "norm pas Alien : " << norm_local << std::endl;

  res[0] = norm;
  res[1] = norm_local;

  return res;
}
