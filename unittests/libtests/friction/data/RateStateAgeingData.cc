// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include "RateStateAgeingData.hh"

const int pylith::friction::RateStateAgeingData::_numLocs = 2;

const int pylith::friction::RateStateAgeingData::_numProperties = 5;

const int pylith::friction::RateStateAgeingData::_numStateVars = 1;

const int pylith::friction::RateStateAgeingData::_numDBProperties = 5;

const int pylith::friction::RateStateAgeingData::_numDBStateVars = 1;

const int pylith::friction::RateStateAgeingData::_numPropsVertex = 5;

const int pylith::friction::RateStateAgeingData::_numVarsVertex = 1;

const double pylith::friction::RateStateAgeingData::_lengthScale =   1.00000000e+03;

const double pylith::friction::RateStateAgeingData::_timeScale =   1.00000000e+00;

const double pylith::friction::RateStateAgeingData::_pressureScale =   2.25000000e+10;

const double pylith::friction::RateStateAgeingData::_densityScale =   1.00000000e+03;

const double pylith::friction::RateStateAgeingData::_dt = 0.01;

const int pylith::friction::RateStateAgeingData::_numPropertyValues[] = {
  1,
  1,
  1,
  1,
  1,
};

const int pylith::friction::RateStateAgeingData::_numStateVarValues[] = {
  1,
};

const char* pylith::friction::RateStateAgeingData::_dbPropertyValues[] = {
  "reference-friction-coefficient",
  "reference-slip-rate",
  "characteristic-slip-distance",
  "constitutive-parameter-a",
  "constitutive-parameter-b",
};

const char* pylith::friction::RateStateAgeingData::_dbStateVarValues[] = {
  "state-variable",
};

const double pylith::friction::RateStateAgeingData::_dbProperties[] = {
  0.6,
  0.000001,
  0.0370,
  0.0125,
  0.0172,
  0.5,
  0.000002,
  0.0470,
  0.0225,
  0.0272,
};

const double pylith::friction::RateStateAgeingData::_dbStateVars[] = {
  92.7,
  93.7,
};

const double pylith::friction::RateStateAgeingData::_properties[] = {
  0.6,
  0.000001,
  0.0370,
  0.0125,
  0.0172,
  0.5,
  0.000002,
  0.0470,
  0.0225,
  0.0272,
};

const double pylith::friction::RateStateAgeingData::_stateVars[] = {
  92.7,
  93.7,
};

const double pylith::friction::RateStateAgeingData::_propertiesNondim[] = {
  0.6,
  0.000000001,
  0.0000370,
  0.0125,
  0.0172,
  0.5,
  0.000000002,
  0.0000470,
  0.0225,
  0.0272,
};

const double pylith::friction::RateStateAgeingData::_stateVarsNondim[] = {
  92.7,
  93.7,
};

const double pylith::friction::RateStateAgeingData::_friction[] = {
  1.285949009547604,
  1.164378652801948,
};

const double pylith::friction::RateStateAgeingData::_slip[] = {
  0.12,
  0.22,
};

const double pylith::friction::RateStateAgeingData::_slipRate[] = {
  0.0011,
  0.0021,
};

const double pylith::friction::RateStateAgeingData::_normalTraction[] = {
  -2.2,
  -2.3,
};

const double pylith::friction::RateStateAgeingData::_stateVarsUpdated[] = {
  92.682443150471812,
  93.668141160483529,
};

pylith::friction::RateStateAgeingData::RateStateAgeingData(void)
{ // constructor
  numLocs = _numLocs;
  numProperties = _numProperties;
  numStateVars = _numStateVars;
  numDBProperties = _numDBProperties;
  numDBStateVars = _numDBStateVars;
  numPropsVertex = _numPropsVertex;
  numVarsVertex = _numVarsVertex;
  lengthScale = _lengthScale;
  timeScale = _timeScale;
  pressureScale = _pressureScale;
  densityScale = _densityScale;
  numPropertyValues = const_cast<int*>(_numPropertyValues);
  numStateVarValues = const_cast<int*>(_numStateVarValues);
  dbPropertyValues = const_cast<char**>(_dbPropertyValues);
  dbStateVarValues = const_cast<char**>(_dbStateVarValues);
  dbProperties = const_cast<double*>(_dbProperties);
  dbStateVars = const_cast<double*>(_dbStateVars);
  dt = _dt;
  properties = const_cast<double*>(_properties);
  stateVars = const_cast<double*>(_stateVars);
  propertiesNondim = const_cast<double*>(_propertiesNondim);
  stateVarsNondim = const_cast<double*>(_stateVarsNondim);
  friction = const_cast<double*>(_friction);
  slip = const_cast<double*>(_slip);
  slipRate = const_cast<double*>(_slipRate);
  normalTraction = const_cast<double*>(_normalTraction);
  stateVarsUpdated = const_cast<double*>(_stateVarsUpdated);
} // constructor

pylith::friction::RateStateAgeingData::~RateStateAgeingData(void)
{}


// End of file