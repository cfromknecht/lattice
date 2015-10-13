#ifndef _POLY_RING_BASE_
#define _POLY_RING_BASE_

#include <cstdlib>
#include <string>

namespace lattice {

  template< class T >
    class PolyRingBase {
    public:
      PolyRingBase() {}
      PolyRingBase( const PolyRingBase<T>& other ) {}
      virtual ~PolyRingBase() {}

      /*
       * Lattice parameters
       */
      virtual size_t degree() const = 0;
      virtual size_t k() const = 0;
      virtual size_t modulus() const = 0;

      /*
       * Polynomial initializations
       */
      virtual void uniformInit() = 0;
      virtual void ternaryInit() = 0;

      /*
       * Assignment
       */
      virtual T& operator=( const T& rhs ) = 0;
      virtual T& operator+=( const T& rhs ) = 0;
      virtual T& operator-=( const T& rhs ) = 0;
      virtual T& operator*=( const T& rhs ) = 0;

      /*
       * Arithmetic
       */
      virtual T operator+( const T& rhs ) = 0;
      virtual T operator-( const T& rhs ) = 0;
      virtual T operator*( const T& rhs ) = 0;

      /*
       * Equality
       */
      virtual bool operator==( const T& rhs ) const = 0;
      virtual bool operator!=( const T& rhs ) const = 0;

      /*
       * Polynomial Accessors and Modifiers
       */
      virtual size_t get( size_t i ) const = 0;
      virtual void set( size_t i, size_t coeff ) = 0;

      /*
       * Required to Guassian Elimination
       */
      virtual T* halveEntries() const = 0;

      /*
       * Representation
       */
      virtual std::string toString() const = 0;
    };

}

#endif

