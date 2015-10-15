#ifndef _POLY_RING_FLINT_
#define _POLY_RING_FLINT_

#include <lattice/BernoulliSampler.hpp>
#include <lattice/PolyRingBase.hpp>
#include <lattice/RingMatrix.hpp>

#include <flint/fmpz_mod_poly.h>

#include <functional>
#include <memory>
#include <string>
#include <sstream>

namespace lattice {

  using ring_t = fmpz_mod_poly_struct;
  using ring_handler = std::unique_ptr< ring_t, void(*)(ring_t*) >;

  class PolyRingFLINT : public PolyRingBase<PolyRingFLINT> {
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

    std::string toString() const;

  private:
    size_t _degree;
    size_t _k;
    size_t _modulus;

    ring_handler _poly;
    ring_handler _F;

    ring_handler initPoly();
    ring_handler initF();
    ring_handler copyPoly() const;
    static void deleteRingT( ring_t* r );
  };

}

#endif
