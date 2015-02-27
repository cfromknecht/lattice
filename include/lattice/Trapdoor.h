#ifndef _TRAPDOOR_
#define _TRAPDOOR_

#include <lattice/PolyRingMatrix.h> 
#include <cstdlib>

namespace lattice {

  class Trapdoor : public PolyRingMatrix {
  private:
    PolyRingMatrix* _parityCheck;
    Trapdoor() = delete;
  public:
    Trapdoor( size_t deg, size_t kk );
    Trapdoor( const Trapdoor& other );
    Trapdoor& operator=( const Trapdoor& rhs );
    ~Trapdoor();

    void buildTrapdoorWithParityCheck();
    PolyRingMatrix* parityCheck() const { return _parityCheck; }
  };

}

#endif
