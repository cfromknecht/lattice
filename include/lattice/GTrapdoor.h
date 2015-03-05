#ifndef _LATTICE_G_TRAPDOOR_H_
#define _LATTICE_G_TRAPDOOR_H_

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

namespace lattice {

  class GTrapdoor: public PolyRingMatrix {
    private:
      GTrapdoor() = delete;

    public:
      GTrapdoor( size_t n, size_t m, size_t degree );
      GTrapdoor( const GTrapdoor& other );
      ~GTrapdoor() {}
  };

} // namespace lattice

#endif

