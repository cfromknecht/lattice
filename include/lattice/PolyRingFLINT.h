#ifndef _POLY_RING_FLINT_
#define _POLY_RING_FLINT_

#include <lattice/PolyRingI.h>

#include <flint/fmpz_mod_poly.h>

namespace lattice {

  typedef fmpz_mod_poly_t ring_t;

  class PolyRingFLINT: public PolyRingI<PolyRingFLINT> {
  private:
    const size_t _degree;
    const size_t _k;
    const size_t _modulus;
    ring_t& _poly;
    ring_t& _F;

  public:
    PolyRingFLINT( size_t nn, size_t kk );
    PolyRingFLINT( const PolyRingFLINT& other );
    ~PolyRingFLINT();
    inline bool operator==( const PolyRingFLINT& rhs );
    inline bool operator!=( const PolyRingFLINT& rhs );
    inline void uniformInit();
    inline void ternaryInit();
    inline void assign( const PolyRingFLINT& );
    inline void addAssign( const PolyRingFLINT& );
    inline void subtractAssign( const PolyRingFLINT& );
    inline void multiplyAssign( const PolyRingFLINT& );

    inline const ring_t& poly() const { return _poly; }

  private:
    ring_t& blankPoly() const;
    ring_t& copyPoly( const ring_t& other) const;
    ring_t& makeF() const;
  };
                                                                                 
  PolyRingFLINT::PolyRingFLINT( size_t nn, size_t kk ) : _degree{nn}, _k{kk},    
      _modulus{size_t(1) << kk}, _poly{blankPoly()}, _F{makeF()} {}              
                                                                                 
  PolyRingFLINT::PolyRingFLINT( const PolyRingFLINT& other ) :                   
    _degree{other._degree}, _k{other._k}, _modulus{other._modulus},              
    _poly{copyPoly(other._poly)}, _F{makeF()} {}                                 
                                                                                 
  PolyRingFLINT::~PolyRingFLINT() {                                              
    fmpz_mod_poly_clear( _poly );                                                
    fmpz_mod_poly_clear( _F );                                                   
  }                                                                              
                                                                                 
  inline void PolyRingFLINT::assign( const PolyRingFLINT& rhs ) {                       
    fmpz_mod_poly_set( _poly, rhs._poly );                                       
  }                                                                              
                                                                                 
  inline void PolyRingFLINT::addAssign( const PolyRingFLINT& rhs ) {                    
    fmpz_mod_poly_add( _poly, _poly, rhs._poly );                                
  }                                                                              
                                                                                 
  inline void PolyRingFLINT::subtractAssign( const PolyRingFLINT& rhs ) {               
    fmpz_mod_poly_sub( _poly, _poly, rhs._poly );                                
  }                                                                                 

  inline void PolyRingFLINT::multiplyAssign( const PolyRingFLINT& rhs ) {                  
    fmpz_mod_poly_mulmod( _poly, _poly, rhs._poly, _F );                            
  }                                                                                 
                                                                                    
  inline bool PolyRingFLINT::operator==( const PolyRingFLINT& rhs ) {                      
    return (0 == fmpz_mod_poly_equal( _poly, rhs._poly ));                          
  }                                                                                 

  inline bool PolyRingFLINT::operator!=( const PolyRingFLINT& rhs ) { 
    return !(*this == rhs); 
  }
                                                                                    
  inline void PolyRingFLINT::uniformInit() {                                               
    for ( size_t i = 0; i < _degree; ++i )                                          
      fmpz_mod_poly_set_coeff_ui( _poly, i, rand() );                               
  }                                                                                 
                                                                                    
  inline void PolyRingFLINT::ternaryInit() {                                               
    for ( size_t i = 0; i < _degree; ++i )                                          
      fmpz_mod_poly_set_coeff_ui( _poly, i, rand() );                               
  }                                                                                 
                                                                                    
  ring_t& PolyRingFLINT::blankPoly() const {                                        
    fmpz_t q_z;                                                                     
    fmpz_set_ui( q_z, _modulus );                                                   
                                                                                    
    ring_t* blank = new ring_t[1];                                                  
    fmpz_mod_poly_init2( blank[0], q_z, _degree );                                  
                                                                                    
    fmpz_clear( q_z );                                                              
                                                                                    
    return blank[0];                                                                
  }                                                                                 
                                                                                    
  ring_t& PolyRingFLINT::copyPoly( const ring_t& other ) const {                    
    ring_t& polyF = blankPoly();                                                    
    fmpz_mod_poly_set( polyF, other );                                              
                                                                                    
    return polyF;                                                                   
  }                                                                                 
                                                                                    
  ring_t& PolyRingFLINT::makeF() const {                                            
    ring_t& polyF = blankPoly();                                                    
    fmpz_mod_poly_set_coeff_ui( polyF, 0, 1 );                                      
    fmpz_mod_poly_set_coeff_ui( polyF, _degree, 1 );                                
                                                                                    
    return polyF;                                                                   
  }    

}

#endif
