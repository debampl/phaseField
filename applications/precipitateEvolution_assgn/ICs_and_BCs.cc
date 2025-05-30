// ===========================================================================
// FUNCTION FOR INITIAL CONDITIONS
// ===========================================================================

template <int dim, int degree>
void
customPDE<dim, degree>::setInitialCondition([[maybe_unused]] const Point<dim>  &p,
                                            [[maybe_unused]] const unsigned int index,
                                            [[maybe_unused]] double            &scalar_IC,
                                            [[maybe_unused]] Vector<double>    &vector_IC)
{
  // ---------------------------------------------------------------------
  // ENTER THE INITIAL CONDITIONS HERE
  // ---------------------------------------------------------------------
  // Enter the function describing conditions for the fields at point "p".
  // Use "if" statements to set the initial condition for each variable
  // according to its variable index

  double center[4][3] = {
    {1.0 / 3.0, 1.0 / 3.0, 0.5},
    {2.0 / 3.0, 2.0 / 3.0, 0.5},
    {3.0 / 4.0, 1.0 / 4.0, 0.5},
    {1.0 / 4.0, 3.0 / 4,   0.5}
  };
  double rad[4]         = {userInputs.domain_size[0] / 16.0,
                           userInputs.domain_size[0] / 16.0,
                           userInputs.domain_size[0] / 16.0,
                           userInputs.domain_size[0] / 16.0};
  double orientation[4] = {1, 1, 2, 3};
  double dx = userInputs.domain_size[0] / ((double) userInputs.subdivisions[0]) /
              std::pow(2.0, userInputs.refine_factor);
  double dist;
  scalar_IC = 0;

  if (index == 0)
    {
      scalar_IC = 0.04;
    }

  for (unsigned int i = 0; i < 3; i++)
    {
      dist = 0.0;
      for (unsigned int dir = 0; dir < dim; dir++)
        {
          dist += (p[dir] - center[i][dir] * userInputs.domain_size[dir]) *
                  (p[dir] - center[i][dir] * userInputs.domain_size[dir]);
        }
      dist = std::sqrt(dist);

      if (index == orientation[i])
        {
          scalar_IC += 0.5 * (1.0 - std::tanh((dist - rad[i]) / (dx)));
        }
    }

  if (index == 3)
    {
      for (unsigned int d = 0; d < dim; d++)
        {
          vector_IC(d) = 0.0;
        }
    }

  // --------------------------------------------------------------------------
}

// ===========================================================================
// FUNCTION FOR NON-UNIFORM DIRICHLET BOUNDARY CONDITIONS
// ===========================================================================

template <int dim, int degree>
void
customPDE<dim, degree>::setNonUniformDirichletBCs(
  [[maybe_unused]] const Point<dim>  &p,
  [[maybe_unused]] const unsigned int index,
  [[maybe_unused]] const unsigned int direction,
  [[maybe_unused]] const double       time,
  [[maybe_unused]] double            &scalar_BC,
  [[maybe_unused]] Vector<double>    &vector_BC)
{
  // --------------------------------------------------------------------------
  // ENTER THE NON-UNIFORM DIRICHLET BOUNDARY CONDITIONS HERE
  // --------------------------------------------------------------------------
  // Enter the function describing conditions for the fields at point "p".
  // Use "if" statements to set the boundary condition for each variable
  // according to its variable index. This function can be left blank if there
  // are no non-uniform Dirichlet boundary conditions. For BCs that change in
  // time, you can access the current time through the variable "time". The
  // boundary index can be accessed via the variable "direction", which starts
  // at zero and uses the same order as the BC specification in parameters.in
  // (i.e. left = 0, right = 1, bottom = 2, top = 3, front = 4, back = 5).

  // -------------------------------------------------------------------------
}
