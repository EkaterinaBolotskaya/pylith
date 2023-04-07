// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University at Buffalo
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2022 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

/**
 * @file mmstets/elasticity/TestLinearElasticity.hh
 *
 * @brief C++ abstract base class for testing Elasticity for various rheologies.
 */

#if !defined(pylith_mmstests_testLinearelasticity_hh)
#define pylith_mmstests_testLinearelasticity_hh

#include "pylith/testing/MMSTest.hh" // ISA MMSTEST

#include "pylith/materials/Elasticity.hh" // USES Elasticity
#include "pylith/materials/IsotropicLinearElasticity.hh" // USES IsotropicLinearElasticity
#include "pylith/bc/DirichletUserFn.hh" // USES DirichletUserFn

#include "spatialdata/spatialdb/UserFunctionDB.hh" // USES UserFunctionDB
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/units/Nondimensional.hh" // USES Nondimensional

#include "pylith/problems/Physics.hh" // USES FormulationEnum
#include "pylith/topology/Field.hh" // HASA FieldBase::Discretization

namespace pylith {
    namespace mmstests {
        class TestLinearElasticity;

        class TestLinearElasticity_Data; // test data
    } // mmstets
} // pylith

/// C++ abstract base class for testing Elasticity with various rheologies.
class pylith::mmstests::TestLinearElasticity : public pylith::testing::MMSTest {
    // PUBLIC METHODS //////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /// Setup testing data.
    virtual
    void setUp(void);

    /// Deallocate testing data.
    virtual
    void tearDown(void);

    // PROTECTED METHODS ///////////////////////////////////////////////////////////////////////////////////////////////
protected:

    /// Initialize objects for test.
    void _initialize(void);

    // PROTECTED MEMBERS ///////////////////////////////////////////////////////////////////////////////////////////////
protected:

    TestLinearElasticity_Data* _data; ///< Test parameters.

}; // class TestLinearElasticity

// =====================================================================================================================
class pylith::mmstests::TestLinearElasticity_Data {
    // PUBLIC METHODS //////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /// Constructor
    TestLinearElasticity_Data(void);

    /// Destructor
    ~TestLinearElasticity_Data(void);

    // PUBLIC MEMBERS //////////////////////////////////////////////////////////////////////////////////////////////////
public:

    int spaceDim; ///< Spatial dimension of domain.
    const char* meshFilename; ///< Name of file with ASCII mesh.
    const char* meshOptions; ///< Command line options for mesh.
    const char* boundaryLabel; ///< Group defining domain boundary.
    bool useAsciiMesh; ///< Use MeshIOAscii to read mesh, otherwise use PETSc.

    PylithReal t; ///< Time for MMS solution.
    PylithReal dt; ///< Time step in simulation.
    spatialdata::geocoords::CSCart cs; ///< Coordinate system.
    spatialdata::units::Nondimensional normalizer; ///< Scales for nondimensionalization.
    pylith::problems::Physics::FormulationEnum formulation; ///< Time stepping formulation

    pylith::materials::Elasticity material; ///< Materials.
    pylith::materials::IsotropicLinearElasticity rheology; ///< Bulk rheology for materials.
    spatialdata::spatialdb::GravityField* gravityField; ///< Gravity field.
    std::vector<pylith::bc::BoundaryCondition*> bcs; ///< Dirichlet boundary condition.

    // Solution field.
    int numSolnSubfields; ///< Number of solution fields.
    pylith::topology::Field::Discretization const* solnDiscretizations; ///< Discretizations for solution fields.

    // Material auxiliary fields.
    int numAuxSubfields; ///< Number of auxiliary subfields for materials.
    const char** auxSubfields; ///< Names of auxiliary subfields for materials.
    pylith::topology::Field::Discretization const* auxDiscretizations; ///< Discretizations for auxiliary subfields.
    spatialdata::spatialdb::UserFunctionDB auxDB; ///< Spatial database for auxiliary field.

}; // TestLinearElasticity_Data

#endif // pylith_mmstests_testlinearelasticity_hh

// End of file
