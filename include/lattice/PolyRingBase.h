#ifndef _POLY_RING_BASE_
#define _POLY_RING_BASE_

#include <lattice/PolyRingI.h>

#include <cstdlib>

namespace lattice {

  template< class T >
    class PolyRingBase {
    public:
      T& _ringImpl;

      PolyRingBase() = delete;
      PolyRingBase( size_t nn, size_t kk ) : _ringImpl(*new T{nn, kk}) {}
      PolyRingBase( const PolyRingBase& pr ) : _ringImpl(pr._ringImpl) {}
      ~PolyRingBase() {}

      PolyRingBase& operator=( const PolyRingBase& rhs );
      PolyRingBase& operator+=( const PolyRingBase& rhs );
      PolyRingBase& operator-=( const PolyRingBase& rhs );
      PolyRingBase& operator*=( const PolyRingBase& rhs );

      PolyRingBase operator+( const PolyRingBase& rhs );
      PolyRingBase operator-( const PolyRingBase& rhs );
      PolyRingBase operator*( const PolyRingBase& rhs );

      void uniformInit();
      void ternaryInit();
    };

  template< class T >
    PolyRingBase<T>& PolyRingBase<T>::operator=( const PolyRingBase<T>& rhs ) {
      if ( this != &rhs )
        _ringImpl.assign( T{rhs._ringImpl} );
      return *this;
    }

  template< class T >
    PolyRingBase<T>& PolyRingBase<T>::operator+=( const PolyRingBase<T>& rhs ) {
      _ringImpl.addAssign( rhs._ringImpl );
      return *this;
    }

  template< class T >
    PolyRingBase<T>& PolyRingBase<T>::operator-=( const PolyRingBase<T>& rhs ) {
      _ringImpl.subtractAssign( rhs._ringImpl );
      return *this;
    }

  template< class T >
    PolyRingBase<T>& PolyRingBase<T>::operator*=( const PolyRingBase<T>& rhs ) {
      _ringImpl.multiplyAssign( rhs._ringImpl );
      return *this;
    }

  template< class T >
    PolyRingBase<T> PolyRingBase<T>::operator+( const PolyRingBase<T>& rhs ) {
      auto lhs = new PolyRingBase<T>{*this};
      *lhs += rhs;
      return *lhs;
    }

  template< class T >
    PolyRingBase<T> PolyRingBase<T>::operator-( const PolyRingBase<T>& rhs ) {
      auto lhs = new PolyRingBase<T>{*this};
      *lhs -= rhs;
      return *lhs;
    }

  template< class T >
    PolyRingBase<T> PolyRingBase<T>::operator*( const PolyRingBase<T>& rhs ) {
      auto lhs = new PolyRingBase<T>{*this};
      *lhs *= rhs;
      return *lhs;
    }

  template< class T >
    void PolyRingBase<T>::uniformInit() {
      _ringImpl.uniformInit();
    }

  template< class T >
    void PolyRingBase<T>::ternaryInit() {
      _ringImpl.ternaryInit();
    }

}

#endif

