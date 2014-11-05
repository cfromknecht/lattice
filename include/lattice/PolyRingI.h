#ifndef _POLY_RING_I_
#define _POLY_RING_I_

namespace lattice {

  template< class T >                                                               
    class PolyRingI {                                                               
    public:
      PolyRingI() {}                                                                
      virtual ~PolyRingI() {}                                                       
      virtual inline void uniformInit() = 0;                                               
      virtual inline void ternaryInit() = 0;                                               
      virtual inline void assign( const T& rhs ) = 0;                                      
      virtual inline void addAssign( const T& rhs ) = 0;                                   
      virtual inline void subtractAssign( const T& rhs ) = 0;                              
      virtual inline void multiplyAssign( const T& rhs ) = 0;                              
      virtual inline bool operator==( const T& rhs ) = 0;                                  
      virtual inline bool operator!=( const T& rhs ) = 0;                           
    };

}

#endif

