#ifndef _POLY_RING_BASE_
#define _POLY_RING_BASE_

#include <cstdlib>

namespace lattice {

  class PolyRingBase {
    private:
      size_t _degree;
      size_t _k;
      size_t _modulus;

      PolyRingBase() = delete;
      
      // arithmetic operator stubs
      virtual void assign( const PolyRingBase& other ) = 0;
      virtual void addAssign( const PolyRingBase& other ) = 0;
      virtual void subtractAssign( const PolyRingBase& other ) = 0;
      virtual void multiplyAssign( const PolyRingBase& other ) = 0;

    protected:
      inline void assignParameters( const PolyRingBase& other );

    public:
      PolyRingBase( size_t nn, size_t kk ) : _degree{nn}, _k{kk}, 
        _modulus{size_t(1) << kk} {}
      PolyRingBase( const PolyRingBase& other) : _degree{other._degree}, 
        _k{other._k}, _modulus{other._modulus} {}
      virtual ~PolyRingBase() {}

      // equality operators
      virtual bool operator==( const PolyRingBase& other ) = 0;
      virtual bool operator!=( const PolyRingBase& other ) = 0;

      // member functions
      inline const size_t& degree() const { return _degree; }
      inline const size_t& k() const { return _k; }
      inline const size_t& modulus() const { return _modulus; }

      virtual void blankInit() = 0;
      virtual void randomInit() = 0;
      virtual void ternaryInit() = 0;
  };


  inline void PolyRingBase::assignParameters( const PolyRingBase& other ) {
    this->_degree = other._degree;
    this->_k = other._k;
    this->_modulus = other._modulus;
  }

}

#endif

