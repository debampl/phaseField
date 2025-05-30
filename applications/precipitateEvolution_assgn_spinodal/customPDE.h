#include "matrixFreePDE.h"

using namespace dealii;

#include <random>

template <int dim, int degree>
class customPDE : public MatrixFreePDE<dim, degree>
{
public:
  customPDE(userInputParameters<dim> _userInputs)
    : MatrixFreePDE<dim, degree>(_userInputs)
    , userInputs(_userInputs) 
	{
	// Defining seed
    	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    	// Initializing distribution
    	dist = distribution(0.0, 1.0);
    	// Initializing random variable
    	rng = engine(seed);
	};
  // Function to set the initial conditions (in ICs_and_BCs.h)
  void
  setInitialCondition([[maybe_unused]] const Point<dim>  &p,
                      [[maybe_unused]] const unsigned int index,
                      [[maybe_unused]] double            &scalar_IC,
                      [[maybe_unused]] Vector<double>    &vector_IC) override;

  // Function to set the non-uniform Dirichlet boundary conditions (in
  // ICs_and_BCs.h)
  void
  setNonUniformDirichletBCs([[maybe_unused]] const Point<dim>  &p,
                            [[maybe_unused]] const unsigned int index,
                            [[maybe_unused]] const unsigned int direction,
                            [[maybe_unused]] const double       time,
                            [[maybe_unused]] double            &scalar_BC,
                            [[maybe_unused]] Vector<double>    &vector_BC) override;
 
  typedef std::mt19937_64                        engine;
  typedef std::uniform_real_distribution<double> distribution;

private:
#include "typeDefs.h"

  const userInputParameters<dim> userInputs;

  // Function to set the RHS of the governing equations for explicit time
  // dependent equations (in equations.h)
  void
  explicitEquationRHS(
    [[maybe_unused]] variableContainer<dim, degree, VectorizedArray<double>>
                                                              &variable_list,
    [[maybe_unused]] const Point<dim, VectorizedArray<double>> q_point_loc,
    [[maybe_unused]] const VectorizedArray<double> element_volume) const override;

  // Function to set the RHS of the governing equations for all other equations
  // (in equations.h)
  void
  nonExplicitEquationRHS(
    [[maybe_unused]] variableContainer<dim, degree, VectorizedArray<double>>
                                                              &variable_list,
    [[maybe_unused]] const Point<dim, VectorizedArray<double>> q_point_loc,
    [[maybe_unused]] const VectorizedArray<double> element_volume) const override;

  // Function to set the LHS of the governing equations (in equations.h)
  void
  equationLHS(
    [[maybe_unused]] variableContainer<dim, degree, VectorizedArray<double>>
                                                              &variable_list,
    [[maybe_unused]] const Point<dim, VectorizedArray<double>> q_point_loc,
    [[maybe_unused]] const VectorizedArray<double> element_volume) const override;

// Function to set postprocessing expressions (in postprocess.h)
#ifdef POSTPROCESS_FILE_EXISTS
  void
  postProcessedFields(
    [[maybe_unused]] const variableContainer<dim, degree, VectorizedArray<double>>
      &variable_list,
    [[maybe_unused]] variableContainer<dim, degree, VectorizedArray<double>>
                                                              &pp_variable_list,
    [[maybe_unused]] const Point<dim, VectorizedArray<double>> q_point_loc,
    [[maybe_unused]] const VectorizedArray<double> element_volume) const override;
#endif

// Function to set the nucleation probability (in nucleation.h)
#ifdef NUCLEATION_FILE_EXISTS
  double
  getNucleationProbability([[maybe_unused]] variableValueContainer variable_value,
                           [[maybe_unused]] double                 dV) const override;
#endif

  // ================================================================
  // Methods specific to this subclass
  // ================================================================

  // ================================================================
  // Model constants specific to this subclass
  // ================================================================

  double         McV  = userInputs.get_model_constant_double("McV");
  double         Mn1V = userInputs.get_model_constant_double("Mn1V");
  double         Mn2V = userInputs.get_model_constant_double("Mn2V");
  double         Mn3V = userInputs.get_model_constant_double("Mn3V");
  double	 c0   = userInputs.get_model_constant_double("c0");
  double         icamplitude   = userInputs.get_model_constant_double("icamplitude");

  Tensor<2, dim> Kn1  = userInputs.get_model_constant_rank_2_tensor("Kn1");
  Tensor<2, dim> Kn2  = userInputs.get_model_constant_rank_2_tensor("Kn2");
  Tensor<2, dim> Kn3  = userInputs.get_model_constant_rank_2_tensor("Kn3");
  bool           n_dependent_stiffness =
    userInputs.get_model_constant_bool("n_dependent_stiffness");
  Tensor<2, dim> sfts_linear1 =
    userInputs.get_model_constant_rank_2_tensor("sfts_linear1");
  Tensor<2, dim> sfts_const1 = userInputs.get_model_constant_rank_2_tensor("sfts_const1");
  Tensor<2, dim> sfts_linear2 =
    userInputs.get_model_constant_rank_2_tensor("sfts_linear2");
  Tensor<2, dim> sfts_const2 = userInputs.get_model_constant_rank_2_tensor("sfts_const2");
  Tensor<2, dim> sfts_linear3 =
    userInputs.get_model_constant_rank_2_tensor("sfts_linear3");
  Tensor<2, dim> sfts_const3 = userInputs.get_model_constant_rank_2_tensor("sfts_const3");
  //double         A4          = userInputs.get_model_constant_double("A4");
  //double         A3          = userInputs.get_model_constant_double("A3");
  //double         A2          = userInputs.get_model_constant_double("A2");
  //double         A1          = userInputs.get_model_constant_double("A1");
  double         A0          = userInputs.get_model_constant_double("A0");
  //double         B2          = userInputs.get_model_constant_double("B2");
  //double         B1          = userInputs.get_model_constant_double("B1");
  //double         B0          = userInputs.get_model_constant_double("B0");

  const static unsigned int  CIJ_tensor_size = 2 * dim - 1 + dim / 3;
  Tensor<2, CIJ_tensor_size> CIJ_Mg =
    userInputs.get_model_constant_elasticity_tensor("CIJ_Mg");
  Tensor<2, CIJ_tensor_size> CIJ_Beta =
    userInputs.get_model_constant_elasticity_tensor("CIJ_Beta");

  // Declaring random number generator (Type std::mt19937_64)
  engine rng;
  // Declaring distribution (Type std::uniform_real_distribution<double>)
  distribution dist;
  // ================================================================
};
