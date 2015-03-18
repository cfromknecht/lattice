#ifndef _LATTICE_G_TRAPDOOR_H_
#define _LATTICE_G_TRAPDOOR_H_

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

namespace lattice {

  class GTrapdoor: public PolyRingMatrix {
    private:
      GTrapdoor() = delete;

    public:
      GTrapdoor( size_t k_, size_t degree_ );
      GTrapdoor( const GTrapdoor& other );
      ~GTrapdoor() {}

      void gTrapdoorInit();
  };

} // namespace lattice

#endif

