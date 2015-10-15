#ifndef LATTICE_RING_MATRIX_BASE_HPP_
#define LATTICE_RING_MATRIX_BASE_HPP_

#include <cstdlib>
#include <string>

namespace lattice {

  template< size_t N,   // number of rows
            size_t M,   // number of columns
            size_t DEG, // degree of the ring
            size_t K,   // lg_2( MODULUS )
            template< size_t,
                      size_t,
                      size_t,
                      size_t > class Derived >
  class RingMatrixBase {
    using DerivedMatrix = Derived<N,M,DEG,K>;
    using DerivedRing = Derived<1,1,DEG,K>;

  public:
    static const size_t MODULUS = size_t(1) << K;

    /*
     * Constructors and Destructor
     */

    RingMatrixBase() {}

    RingMatrixBase( const DerivedMatrix& ) {}

    virtual ~RingMatrixBase() {}

    /*
     * Ring Initializations
     */

    virtual void uniformInit() = 0;

    virtual void uniformInit( size_t row, size_t col ) = 0;

    virtual void ternaryInit() = 0;

    virtual void ternaryInit( size_t row, size_t col ) = 0;

    /*
     * Arithmetic Assignment
     */

    virtual DerivedMatrix& operator+=( const DerivedMatrix& rhs ) = 0;

    virtual DerivedMatrix& operator-=( const DerivedMatrix& rhs ) = 0;

    template< size_t OUTER_DIM >
    Derived<N,OUTER_DIM,DEG,K>& 
        operator*=( const Derived<M,OUTER_DIM,DEG,K>& rhs );

    /*
     * Arithmetic Operations
     */

    virtual DerivedMatrix operator+( const DerivedMatrix& rhs ) const = 0;

    virtual DerivedMatrix operator-( const DerivedMatrix& rhs ) const = 0;


    template< size_t OUTER_DIM >
    Derived<N,OUTER_DIM,DEG,K> 
        operator*( const Derived<M,OUTER_DIM,DEG,K>& rhs ) const;

    /*
     * Comparison
     */

    virtual bool operator==( const DerivedMatrix& rhs ) const = 0;

    virtual bool operator!=( const DerivedMatrix& rhs ) const = 0;

    /*
     * Transpose
     */
    
    virtual Derived<M,N,DEG,K> T() const = 0;

    /*
     * Ring Accessors and Modifiers
     */

    /*
    virtual DerivedRing& getRing( size_t row, size_t col ) const = 0;
    */

    virtual void setRing( size_t row, size_t col, const DerivedRing& ring ) = 0;

    virtual size_t getCoeff( size_t row, size_t col, size_t deg ) const = 0;

    virtual void setCoeff( size_t row, size_t col, size_t deg, size_t val ) = 0;

    /*
     * Representation
     */

    virtual std::string toString() const = 0;
  };

} /* namespace lattice */


#endif /* LATTICE_RING_MATRIX_BASE_HPP_ */
