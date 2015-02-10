#ifndef _POLY_RING_FLINT_
#define _POLY_RING_FLINT_

#include <lattice/BernoulliSampler.h>
#include <lattice/PolyRingBase.hpp>

#include <flint/fmpz_mod_poly.h>
#include <functional>
#include <memory>

namespace lattice {

  typedef fmpz_mod_poly_t ring_t;

  class PolyRingFLINT : public PolyRingBase<PolyRingFLINT> {
  private:
    size_t _degree;
    size_t _k;
    size_t _modulus;
    ring_t* _poly;
    ring_t* _F;

  public:
    PolyRingFLINT( size_t nn, size_t kk );
    PolyRingFLINT( const PolyRingFLINT& other );
    ~PolyRingFLINT();

    // PolyRingBase Interface
    PolyRingFLINT& operator=( const PolyRingFLINT& rhs );
    PolyRingFLINT& operator+=( const PolyRingFLINT& rhs );
    PolyRingFLINT& operator-=( const PolyRingFLINT& rhs );
    PolyRingFLINT& operator*=( const PolyRingFLINT& rhs );
    PolyRingFLINT operator+( const PolyRingFLINT& rhs );
    PolyRingFLINT operator-( const PolyRingFLINT& rhs );
    PolyRingFLINT operator*( const PolyRingFLINT& rhs );
    bool operator==( const PolyRingFLINT& rhs ) const;
    bool operator!=( const PolyRingFLINT& rhs ) const;

    size_t get( size_t i ) const;
    void set( size_t i, size_t coeff );

    size_t degree() const { return _degree; }
    size_t k() const { return _k; }
    size_t modulus() const { return _modulus; }

    void uniformInit();
    void ternaryInit();

    PolyRingFLINT* halveEntries() const;

    ring_t* poly() const { return _poly; }

  private:
    void initPoly();
    void copyPoly( ring_t* r );
    void clearPoly();
    void initF();
    void clearF();
  };

}

#endif
