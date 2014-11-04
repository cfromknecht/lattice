#ifndef _FLINT_POLY_RING_
#define _FLINT_POLY_RING_

#include <lattice/PolyRingBase.h>

#include <flint/fmpz_mod_poly.h>

namespace lattice {

  typedef fmpz_mod_poly_t ring_t;

  class PolyRingFLINT: public PolyRingBase {
    private:
      ring_t& _poly;
      ring_t& _F;

      PolyRingFLINT() = delete;

      // assignment operators
      void assign( const PolyRingBase& );
      void addAssign( const PolyRingBase& );
      void subtractAssign( const PolyRingBase& );
      void multiplyAssign( const PolyRingBase& );

      ring_t& blankPoly() const;
      ring_t& makeF() const;

    protected:
      inline void assignRingParameters( const PolyRingFLINT& other );

    public:
      PolyRingFLINT( size_t nn, size_t kk ) : PolyRingBase{nn, kk}, 
        _poly{blankPoly()}, _F{makeF()} {}
      PolyRingFLINT( const PolyRingFLINT& other ) : 
        PolyRingBase{other.degree(), other.k()}, _poly{blankPoly()}, _F{makeF()} {}
      ~PolyRingFLINT() {}                                            

      // assignment operators                                                    
      inline PolyRingFLINT& operator=( const PolyRingFLINT& other );
      inline PolyRingFLINT& operator+=( const PolyRingFLINT& other );
      inline PolyRingFLINT& operator-=( const PolyRingFLINT& other );
      inline PolyRingFLINT& operator*=( const PolyRingFLINT& other );

      // binary arithmetic operators                                                    
      PolyRingFLINT operator+( const PolyRingFLINT& rhs ) const;
      PolyRingFLINT operator-( const PolyRingFLINT& rhs ) const;
      PolyRingFLINT operator*( const PolyRingFLINT& rhs ) const;
                                                                                 
      // equality operators                                                      
      bool operator==( const PolyRingBase& ) { return true; }
      bool operator!=( const PolyRingBase& ) { return false; }

      // member functions
      inline const ring_t& poly() const { return _poly; }
      inline const ring_t& F() const { return _F; }
                                                                                 
      // initializers
      void blankInit() {}
      void randomInit() {}
      void ternaryInit() {}
  };

  inline PolyRingFLINT& PolyRingFLINT::operator=( const PolyRingFLINT& other ) { 
    assign( other ); 
    return *this; 
  }

  inline PolyRingFLINT& PolyRingFLINT::operator+=( const PolyRingFLINT& other ) { 
    addAssign( other ); 
    return *this; 
  }

  inline PolyRingFLINT& PolyRingFLINT::operator-=( const PolyRingFLINT& other ) { 
    subtractAssign( other ); 
    return *this; 
  }
  
  inline PolyRingFLINT& PolyRingFLINT::operator*=( const PolyRingFLINT& other ) { 
    multiplyAssign( other ); 
    return *this; 
  }

  inline void PolyRingFLINT::assignRingParameters( const PolyRingFLINT& other ) {
    fmpz_mod_poly_set( _poly, other.poly() );
    fmpz_mod_poly_set( _F, other.F() );
  }

  inline ring_t& PolyRingFLINT::blankPoly() const {
    fmpz_t q_z;
    fmpz_set_ui( q_z, modulus() );
    ring_t* blank = new ring_t[1];
    fmpz_mod_poly_init2( blank[0], q_z, degree() );
    return blank[0];
  }

  inline ring_t& PolyRingFLINT::makeF() const {
    ring_t& polyF = blankPoly();
    fmpz_mod_poly_set_coeff_ui( polyF, 0, 1 );
    fmpz_mod_poly_set_coeff_ui( polyF, degree(), 1 );
    return polyF;
  }

}
#endif
