#include <lattice/GTrapdoor.h>

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

namespace lattice {

  GTrapdoor::GTrapdoor( size_t k_, size_t degree_ ) : 
      PolyRingMatrix{k_, 1, degree_, k_} {
    if ( k_ != _polys.size() )
      throw std::logic_error{"[GTrapdoor]: Size of GTrapdoor is not equal to k"};

    // initialize G Trapdoor entries
    for ( size_t i = 0; i < _n; ++i )
      this->setCoeff( i, 0, 0, 1_z << i );
  }

  GTrapdoor::GTrapdoor( const GTrapdoor& other ) : PolyRingMatrix{other} {}

  void GTrapdoor::gTrapdoorInit() {
    for ( size_t i = 0; i < _n; ++i )
      this->setCoeff( i, 0, 0, 1_z << i );
  }

}

