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

#include <portinfo>

#include "TestElasticityImplicitLgDeformGrav2DLinear.hh" // Implementation of class methods

#include "data/ElasticityImplicitLgDeformGravData2DLinear.hh"

#include "pylith/topology/Mesh.hh" // USES Quadrature<Mesh>
#include "pylith/feassemble/Quadrature.hh" // USES Quadrature
#include "pylith/feassemble/GeometryTri2D.hh" // USES GeometryTri2D
#include "pylith/materials/ElasticPlaneStrain.hh" // USES ElasticPlaneStrain
#include "spatialdata/spatialdb/GravityField.hh" // USES GravityField

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( pylith::feassemble::TestElasticityImplicitLgDeformGrav2DLinear );

// ----------------------------------------------------------------------
// Setup testing data.
void
pylith::feassemble::TestElasticityImplicitLgDeformGrav2DLinear::setUp(void)
{ // setUp
  TestElasticityImplicitLgDeform::setUp();

  _data = new ElasticityImplicitLgDeformGravData2DLinear();
  _gravityField = new spatialdata::spatialdb::GravityField();
  CPPUNIT_ASSERT(0 != _quadrature);
  CPPUNIT_ASSERT(0 != _gravityField);
  GeometryTri2D geometry;
  _quadrature->refGeometry(&geometry);

  const double g = 1.0e8;
  const double gravityDir[] = { 0.0, -1.0, 0.0 };
  _gravityField->gravAcceleration(g);
  _gravityField->gravityDir(gravityDir[0], gravityDir[1], gravityDir[2]);

  _material = new materials::ElasticPlaneStrain;
  CPPUNIT_ASSERT(0 != _material);
  
  CPPUNIT_ASSERT(0 != _data);
  CPPUNIT_ASSERT_EQUAL(std::string("ElasticPlaneStrain"),
		       std::string(_data->matType));
} // setUp


// End of file 