#ifndef _POLY_RING_BASE_
#define _POLY_RING_BASE_

#include <cstdlib>
#include <memory>

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

      virtual void uniformInit() = 0;                                        
      virtual void ternaryInit() = 0;                                        
    };

}

#endif

