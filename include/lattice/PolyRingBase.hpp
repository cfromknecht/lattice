#ifndef _POLY_RING_BASE_
#define _POLY_RING_BASE_

#include <cstdlib>

namespace lattice {

  template< class T >
    class PolyRingBase {
    public:
      PolyRingBase() {}
      PolyRingBase( const PolyRingBase<T>& other ) {}
      virtual ~PolyRingBase() {}

      virtual T& operator=( const T& rhs ) = 0;
      virtual T& operator+=( const T& rhs ) = 0;
      virtual T& operator-=( const T& rhs ) = 0;
      virtual T& operator*=( const T& rhs ) = 0;
      virtual T operator+( const T& rhs ) = 0;
      virtual T operator-( const T& rhs ) = 0;
      virtual T operator*( const T& rhs ) = 0;

      virtual bool operator==( const T& rhs ) const = 0;
      virtual bool operator!=( const T& rhs ) const = 0;

      virtual size_t get( size_t i ) const = 0;
      virtual void set( size_t i, size_t coeff ) = 0;

      virtual size_t degree() const = 0;
      virtual size_t k() const = 0;
      virtual size_t modulus() const = 0;

      virtual void uniformInit() = 0;
      virtual void ternaryInit() = 0;
    };

}

#endif

