// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

/** @file libsrc/materials/DruckerPragerEP3D.hh
 *
 * @brief 3-D, isotropic, Drucker-Prager elastic/perfectly plastic material. 
 */

#if !defined(pylith_materials_druckerpragerep3d_hh)
#define pylith_materials_druckerpragerep3d_hh

// Include directives ---------------------------------------------------
#include "ElasticMaterial.hh" // ISA ElasticMaterial

// Powerlaw3D -----------------------------------------------------------
/** @brief 3-D, isotropic, Drucker-Prager elastic/perfectly plastic material. 
 *
 * The physical properties are specified using density, shear-wave
 * speed, friction angle, cohesion, dilatation angle, and
 * compressional-wave speed.  The physical properties are stored
 * internally using density, lambda, mu, which are directly related to
 * the elasticity constants used in the finite-element
 * integration. The plasticity information is retained as alpha_yield,
 * beta, and alpha_flow.
 */

class pylith::materials::DruckerPragerEP3D : public ElasticMaterial
{ // class DruckerPragerEP3D
  friend class TestDruckerPragerEP3D; // unit testing

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Default constructor
  DruckerPragerEP3D(void);

  /// Destructor
  ~DruckerPragerEP3D(void);

  /** Set current time step.
   *
   * @param dt Current time step.
   */
  void timeStep(const double dt);

  /** Set whether elastic or inelastic constitutive relations are used.
   *
   * @param flag True to use elastic, false to use inelastic.
   */
  void useElasticBehavior(const bool flag);


  // PROTECTED METHODS //////////////////////////////////////////////////
protected :

  /** Compute properties from values in spatial database.
   *
   * Order of values in arrays matches order used in dbValues() and
   * parameterNames().
   *
   * @param propValues Array of property values.
   * @param dbValues Array of database values.
   */
  void _dbToProperties(double* const propValues,
		       const double_array& dbValues) const;

  /** Nondimensionalize properties.
   *
   * @param values Array of property values.
   * @param nvalues Number of values.
   */
  void _nondimProperties(double* const values,
			 const int nvalues) const;

  /** Dimensionalize properties.
   *
   * @param values Array of property values.
   * @param nvalues Number of values.
   */
  void _dimProperties(double* const values,
		      const int nvalues) const;

  /** Compute initial state variables from values in spatial database.
   *
   * @param stateValues Array of state variable values.
   * @param dbValues Array of database values.
   */
  void _dbToStateVars(double* const stateValues,
		      const double_array& dbValues) const;

  /** Nondimensionalize state variables..
   *
   * @param values Array of state variables.
   * @param nvalues Number of values.
   */
  void _nondimStateVars(double* const values,
			const int nvalues) const;

  /** Dimensionalize state variables.
   *
   * @param values Array of state variables.
   * @param nvalues Number of values.
   */
  void _dimStateVars(double* const values,
		     const int nvalues) const;

  /** Compute density from properties.
   *
   * @param density Array for density.
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param stateVars State variables at location.
   * @param numStateVars Number of state variables.
   */
  void _calcDensity(double* const density,
		    const double* properties,
		    const int numProperties,
		    const double* stateVars,
		    const int numStateVars);

  /** Compute stress tensor from properties and state variables. If
   * the state variables are from the previous time step, then the
   * computeStateVars flag should be set to true so that the state
   * variables are updated (but not stored) when computing the stresses.
   *
   * @param stress Array for stress tensor.
   * @param stressSize Size of stress tensor.
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param stateVars State variables at location.
   * @param numStateVars Number of state variables.
   * @param totalStrain Total strain at location.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   * @param computeStateVars Flag indicating to compute updated state variables.
   */
  void _calcStress(double* const stress,
		   const int stressSize,
		   const double* properties,
		   const int numProperties,
		   const double* stateVars,
		   const int numStateVars,
		   const double* totalStrain,
		   const int strainSize,
		   const double* initialStress,
		   const int initialStressSize,
		   const double* initialStrain,
		   const int initialStrainSize,
		   const bool computeStateVars);

  /** Compute derivatives of elasticity matrix from properties.
   *
   * @param elasticConsts Array for elastic constants.
   * @param numElasticConsts Number of elastic constants.
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param stateVars State variables at location.
   * @param numStateVars Number of state variables.
   * @param totalStrain Total strain at location.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   */
  void _calcElasticConsts(double* const elasticConsts,
			  const int numElasticConsts,
			  const double* properties,
			  const int numProperties,
			  const double* stateVars,
			  const int numStateVars,
			  const double* totalStrain,
			  const int strainSize,
		          const double* initialStress,
		          const int initialStressSize,
		          const double* initialStrain,
		          const int initialStrainSize);

  /** Get stable time step for implicit time integration.
   *
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param stateVars State variables at location.
   * @param numStateVars Number of state variables.
   *
   * @returns Time step
   */
  double _stableTimeStepImplicit(const double* properties,
				 const int numProperties,
				 const double* stateVars,
				 const int numStateVars) const;

  /** Update state variables (for next time step).
   *
   * @param stateVars State variables at location.
   * @param numStateVars Number of state variables.
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param totalStrain Total strain at location.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   */
  void _updateStateVars(double* const stateVars,
			const int numStateVars,
			const double* properties,
			const int numProperties,
			const double* totalStrain,
			const int strainSize,
			const double* initialStress,
			const int initialStressSize,
			const double* initialStrain,
			const int initialStrainSize);

  // PRIVATE TYPEDEFS ///////////////////////////////////////////////////
private :

  /// Member prototype for _calcStress()
  typedef void (pylith::materials::DruckerPragerEP3D::*calcStress_fn_type)
    (double* const,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const bool);

  /// Member prototype for _calcElasticConsts()
  typedef void (pylith::materials::DruckerPragerEP3D::*calcElasticConsts_fn_type)
    (double* const,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int);

  /// Member prototype for _updateStateVars()
  typedef void (pylith::materials::DruckerPragerEP3D::*updateStateVars_fn_type)
    (double* const,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int,
     const double*,
     const int);

  // PRIVATE METHODS ////////////////////////////////////////////////////
private :

  /** Compute stress tensor from properties as an elastic material.
   *
   * @param stress Array for stress tensor.
   * @param stressSize Size of stress tensor.
   * @param properties Properties at locations.
   * @param numProperties Number of properties.
   * @param stateVars State variables at locations.
   * @param numStateVars Number of state variables.
   * @param totalStrain Total strain at locations.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   * @param computeStateVars Flag indicating to compute updated state vars.
   */
  void _calcStressElastic(double* const stress,
			  const int stressSize,
			  const double* properties,
			  const int numProperties,
			  const double* stateVars,
			  const int numStateVars,
			  const double* totalStrain,
			  const int strainSize,
			  const double* initialStress,
			  const int initialStressSize,
			  const double* initialStrain,
			  const int initialStrainSize,
			  const bool computeStateVars);

  /** Compute stress tensor from properties as an elastoplastic material.
   *
   * @param stress Array for stress tensor.
   * @param stressSize Size of stress tensor.
   * @param properties Properties at locations.
   * @param numProperties Number of properties.
   * @param stateVars State variables at locations.
   * @param numStateVars Number of state variables.
   * @param totalStrain Total strain at locations.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   * @param computeStateVars Flag indicating to compute updated state vars.
   */
  void _calcStressElastoplastic(double* const stress,
				const int stressSize,
				const double* properties,
				const int numProperties,
				const double* stateVars,
				const int numStateVars,
				const double* totalStrain,
				const int strainSize,
				const double* initialStress,
				const int initialStressSize,
				const double* initialStrain,
				const int initialStrainSize,
				const bool computeStateVars);

  /** Compute derivatives of elasticity matrix from properties as an
   * elastic material.
   *
   * @param elasticConsts Array for elastic constants.
   * @param numElasticConsts Number of elastic constants.
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param stateVars State variables at locations.
   * @param numStateVars Number of state variables.
   * @param totalStrain Total strain at location.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   */
  void _calcElasticConstsElastic(double* const elasticConsts,
				 const int numElasticConsts,
				 const double* properties,
				 const int numProperties,
				 const double* stateVars,
				 const int numStateVars,
				 const double* totalStrain,
				 const int strainSize,
				 const double* initialStress,
				 const int initialStressSize,
				 const double* initialStrain,
				 const int initialStrainSize);

  /** Compute derivatives of elasticity matrix from properties as an
   * elastoplastic material.
   *
   * @param elasticConsts Array for elastic constants.
   * @param numElasticConsts Number of elastic constants.
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param stateVars State variables at locations.
   * @param numStateVars Number of state variables.
   * @param totalStrain Total strain at location.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   */
  void _calcElasticConstsElastoplastic(double* const elasticConsts,
				       const int numElasticConsts,
				       const double* properties,
				       const int numProperties,
				       const double* stateVars,
				       const int numStateVars,
				       const double* totalStrain,
				       const int strainSize,
				       const double* initialStress,
				       const int initialStressSize,
				       const double* initialStrain,
				       const int initialStrainSize);
  
  /** Update state variables after solve as an elastic material.
   *
   * @param stateVars State variables at locations.
   * @param numStateVars Number of state variables.
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param totalStrain Total strain at location.
   * @param strainSize Size of strain tensor.
   * @param initialStress Initial stress values.
   * @param initialStressSize Size of initial stress array.
   * @param initialStrain Initial strain values.
   * @param initialStrainSize Size of initial strain array.
   */
  void _updateStateVarsElastic(double* const stateVars,
			       const int numStateVars,
			       const double* properties,
			       const int numProperties,
			       const double* totalStrain,
			       const int strainSize,
			       const double* initialStress,
			       const int initialStressSize,
			       const double* initialStrain,
			       const int initialStrainSize);

  /** Update state variables after solve as an elastoplastic material.
   *
   * @param properties Properties at location.
   * @param numProperties Number of properties.
   * @param totalStrain Total strain at location.
   * @param strainSize Size of strain tensor.
   * @param initialState Initial state values.
   * @param initialStateSize Size of initial state array.
   */
  void _updateStateVarsElastoplastic(double* const stateVars,
				     const int numStateVars,
				     const double* properties,
				     const int numProperties,
				     const double* totalStrain,
				     const int strainSize,
				     const double* initialStress,
				     const int initialStressSize,
				     const double* initialStrain,
				     const int initialStrainSize);

  /** Compute scalar product, assuming vector form of a tensor.
   *
   * @param tensor1 First tensor.
   * @param tensor2 Second tensor.
   */
  double _scalarProduct(const double* tensor1,
			const double* tensor2) const;


  // PRIVATE MEMBERS ////////////////////////////////////////////////////
private :

  /// Method to use for _calcElasticConsts().
  calcElasticConsts_fn_type _calcElasticConstsFn;

  /// Method to use for _calcStress().
  calcStress_fn_type _calcStressFn;

  /// Method to use for _updateStateVars().
  updateStateVars_fn_type _updateStateVarsFn;

  static const int p_density;
  static const int p_mu;
  static const int p_lambda;
  static const int p_alphaYield;
  static const int p_beta;
  static const int p_alphaFlow;
  static const int db_density;
  static const int db_vs;
  static const int db_vp;
  static const int db_frictionAngle;
  static const int db_cohesion;
  static const int db_dilatationAngle;

  static const int s_plasticStrain;
  static const int db_plasticStrain;

  // NOT IMPLEMENTED ////////////////////////////////////////////////////
private :

  DruckerPragerEP3D(const DruckerPragerEP3D&); ///< Not implemented
  const DruckerPragerEP3D& operator=(const DruckerPragerEP3D&); ///< Not implemented

}; // class DruckerPragerEP3D

#include "DruckerPragerEP3D.icc" // inline methods

#endif // pylith_materials_druckerpragerep3d_hh


// End of file 