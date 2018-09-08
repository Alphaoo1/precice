#pragma once

#include "mesh/SharedPointer.hpp"
#include "utils/assertion.hpp"
#include "mesh/Data.hpp"
#include <Eigen/Core>
#include <vector>

namespace precice {
namespace cplscheme {

struct CouplingData
{
  typedef Eigen::MatrixXd DataMatrix;

  /// Data values of current iteration and current timestep
  Eigen::VectorXd* values;

  /// Data values of next timestep (different from values for subcycling)
  Eigen::VectorXd* newValues;

  /// Data values of previous iteration (1st col) and previous timesteps.
  DataMatrix oldValues;

  mesh::PtrMesh mesh;

  ///  True, if the data values are initialized by a participant.
  bool initialize;

  /// dimension of one data value (scalar=1, or vectorial=interface-dimension)
  int dimension;

  /**
   * @brief Default constructor, not to be used!
   *
   * Necessary when compiler creates template code for std::map::operator[].
   */
  CouplingData ()
    {
      assertion ( false );
    }

  CouplingData (
    Eigen::VectorXd*  values,
    mesh::PtrMesh     mesh,
    bool              initialize,
    int               dimension)
    :
    values ( values ),
    newValues(),
    mesh(mesh),
    initialize ( initialize ),
    dimension(dimension)
    {
      assertion ( values != NULL );
      assertion ( mesh.use_count()>0);
    }
};

}} // namespace precice, cplscheme
