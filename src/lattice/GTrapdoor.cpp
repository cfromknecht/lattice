#include <lattice/GTrapdoor.h>

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

namespace lattice {

  GTrapdoor::GTrapdoor( size_t k, size_t degree ) : PolyRingMatrix{1, k, degree, 
      1_z << k} {
    if ( k != _polys.size() )
      throw std::logic_error{"[GTrapdoor]: Size of GTrapdoor is not equal to k"};

    for ( size_t i = 0; i < k; ++i ) {
      this->setCoeff( 1, i, 0, 1_z << i );
    }
  }

}

