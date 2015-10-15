#ifndef LATTICE_RING_MATRIX_HPP_
#define LATTICE_RING_MATRIX_HPP_

#include <lattice/BernoulliSampler.hpp>
#include <lattice/RingMatrixBase.hpp>

#include <flint/fmpz_mod_poly.h>

#include <cstdlib>
#include <memory>
#include <string>
#include <sstream>

namespace lattice {

  template< size_t N, size_t M, size_t DEG, size_t K >
  class RingMatrix;

  template< size_t DEG, size_t K >
  using Ring = RingMatrix<1,1,DEG,K>;

  template< size_t N, size_t M, size_t DEG, size_t K >
  class RingMatrix: public RingMatrixBase<N,M,DEG,K,RingMatrix> {
  public:

    /*
     * Constructors and Destructor
     */
    RingMatrix();

    RingMatrix( const RingMatrix& other );

    ~RingMatrix();

    /*
     * Ring Initializations
     */

    void uniformInit(); 

    void uniformInit( size_t row, size_t col ); 

    void ternaryInit(); 

    void ternaryInit( size_t row, size_t col ); 

    /*
     * Arithmetic Assignment
     */

    RingMatrix& operator+=( const RingMatrix& rhs );

    RingMatrix& operator-=( const RingMatrix& rhs );

    template< size_t OUTER_DIM >
    RingMatrix<N,OUTER_DIM,DEG,K>&
        operator*=( const RingMatrix<M,OUTER_DIM,DEG,K>& rhs );

    /*
     * Arithmetic Operations
     */
    RingMatrix operator+( const RingMatrix& rhs ) const;

    RingMatrix operator-( const RingMatrix& rhs ) const;

    template< size_t OUTER_DIM >
    RingMatrix<N,OUTER_DIM,DEG,K>
        operator*( const RingMatrix<M,OUTER_DIM,DEG,K>& rhs ) const;

    /*
     * Comparison
     */

    bool operator==( const RingMatrix& rhs ) const;

    bool operator!=( const RingMatrix& rhs ) const;

    /*
     * Transpose
     */

    RingMatrix<M,N,DEG,K> T() const;

    /*
     * Ring Accessors and Modifiers
     */

    /*
    Ring<DEG,K>& getRing( size_t row, size_t col ) const;
    */

    void setRing( size_t row, size_t col, const Ring<DEG,K>& ring );

    size_t getCoeff( size_t row, size_t col, size_t deg ) const;

    void setCoeff( size_t row, size_t col, size_t deg, size_t val );

    /*
     * Representation
     */

    std::string toString() const;

    using ring_t = fmpz_mod_poly_struct;
    using ring_vector_t = ring_t[];


    /*
     * Delete Function for `ring_t`
     */
    struct deleteRingT {
      void operator()( ring_t* r ) const {
        fmpz_mod_poly_clear( r );
        delete r;
      }
    };


    /*
     * Delete Function for `ring_vector_t`
     */
    struct deleteRingVectorT {
      void operator()( ring_t* rings ) const {
#pragma omp parallel for
        for ( size_t i = 0; i < N*M; ++i )
          fmpz_mod_poly_clear( rings + i );
        delete [] rings;
      }
    };

    using ring_handler = std::unique_ptr< ring_t, deleteRingT >;
    using ring_vector_handler = std::unique_ptr< ring_vector_t, 
                                                 deleteRingVectorT >;

    ring_vector_handler _rings;
    ring_handler        _F;
    
    /*
     * Initialization Helper Methods
     */
    ring_vector_handler initRings() const {
      auto rings = ring_vector_handler(new ring_t[N*M]);

      fmpz_t q_z;
      fmpz_init_set_ui( q_z, RingMatrix::MODULUS );

#pragma omp parallel for
      for ( size_t i = 0; i < N*M; ++i )
        fmpz_mod_poly_init2( rings.get() + i, q_z, DEG );

      fmpz_clear( q_z );

      return rings;
    }

    ring_vector_handler copyRings() const {
      auto newRings = initRings();

#pragma omp parallel for
      for ( size_t i = 0; i < N*M; ++i )
        fmpz_mod_poly_set( newRings.get() + i, _rings.get() + i );

      return newRings;
    }

    ring_handler initF() const {
      auto r = ring_handler(new ring_t);

      fmpz_t q_z;
      fmpz_init_set_ui( q_z, RingMatrix::MODULUS );

      fmpz_mod_poly_init2( r.get(), q_z, DEG );
      fmpz_mod_poly_set_coeff_ui( r.get(), 0, 1 );
      fmpz_mod_poly_set_coeff_ui( r.get(), DEG, 1 );

      fmpz_clear( q_z );

      return r;
    }

  }; /* RingMatrix */

  /*
   * Constructors and Destructor
   */

  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<N,M,DEG,K>::RingMatrix() :
      RingMatrixBase<N,M,DEG,K,RingMatrix>{},
      _rings(initRings()),
      _F(initF()) {}

  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<N, M, DEG, K>::RingMatrix( const RingMatrix& other ) :
      RingMatrixBase<N,M,DEG,K,RingMatrix>{other},
      _rings(other.copyRings()),
      _F(initF()) {}

  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<N,M,DEG,K>::~RingMatrix() {}

  /*
   * Ring Initializations
   */

  template< size_t N, size_t M, size_t DEG, size_t K >
  void 
  RingMatrix<N,M,DEG,K>::uniformInit() {
#pragma omp parallel for
    for ( size_t i = 0; i < N; ++i )
      for ( size_t j = 0; j < M; ++j )
        uniformInit( i, j );
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  void 
  RingMatrix<N,M,DEG,K>::uniformInit( size_t row, size_t col ) {
    for ( size_t d = 0; d < DEG; ++d )
      fmpz_mod_poly_set_coeff_ui( _rings.get() + row*M + col, d, rand() );
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  void 
  RingMatrix<N,M,DEG,K>::ternaryInit() {
#pragma omp parallel for
    for ( size_t i = 0; i < N; ++i )
      for ( size_t j = 0; j < M; ++j )
        ternaryInit( i, j );
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  void 
  RingMatrix<N,M,DEG,K>::ternaryInit( size_t row, size_t col ) {
    BernoulliSampler<DEG/4> bernoulliDist{};

    auto targetRing = row*M + col;
    for ( size_t d = 0; d < DEG; ++d ) {
      if ( bernoulliDist.sample() ) { // 0 with probability 1/2
        bernoulliDist.sample();
        fmpz_mod_poly_set_coeff_ui( _rings.get() + targetRing, d, 0 );
      } else {
        if ( bernoulliDist.sample() ) // 1 with probability 1/4
          fmpz_mod_poly_set_coeff_ui( _rings.get() + targetRing, d, 1 );
        else
          fmpz_mod_poly_set_coeff_ui( _rings.get() + targetRing, 
                                      d,
                                      Ring<DEG,K>::MODULUS - 1 );
      }
    }
  }

  /*
   * Arithmetic Assignment
   */

  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<N,M,DEG,K>& 
  RingMatrix<N,M,DEG,K>::operator+=( const RingMatrix& rhs ) {
#pragma omp parallel for
    for ( size_t i = 0; i < N*M; ++i )
      fmpz_mod_poly_add( _rings.get() + i, 
                         _rings.get() + i, 
                         rhs._rings.get() + i );
    return *this;
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<N,M,DEG,K>& 
  RingMatrix<N,M,DEG,K>::operator-=( const RingMatrix& rhs ) {
#pragma omp parallel for
    for ( size_t i = 0; i < N*M; ++i )
      fmpz_mod_poly_sub( _rings.get() + i, 
                         _rings.get() + i, 
                         rhs._rings.get() + i );
    return *this;
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  template< size_t OUTER_DIM >
  RingMatrix<N,OUTER_DIM,DEG,K>& 
  RingMatrix<N,M,DEG,K>::operator*=( const RingMatrix<M,OUTER_DIM,DEG,K>& rhs ) {
    *this = *this * rhs;

    return *this;
  }

  /*
   * Arithmetic Operations
   */
  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<N,M,DEG,K> 
  RingMatrix<N,M,DEG,K>::operator+( const RingMatrix& rhs ) const {
    RingMatrix matrix{*this};
    matrix += rhs;

    return matrix;
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<N,M,DEG,K> 
  RingMatrix<N,M,DEG,K>::operator-( const RingMatrix& rhs ) const {
    RingMatrix matrix{*this};
    matrix -= rhs;

    return matrix;
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  template< size_t OUTER_DIM >
  RingMatrix<N,OUTER_DIM,DEG,K> 
  RingMatrix<N,M,DEG,K>::operator*( const RingMatrix<M,OUTER_DIM,DEG,K>& rhs ) const {
    RingMatrix matrix{};
#pragma omp parallel for
    for ( size_t r = 0;  r < N; ++r ) {
      for ( size_t s = 0; s < OUTER_DIM; ++s ) {
        auto tempRing = initF();
        for ( size_t t = 0; t < M; ++t ) {
          fmpz_mod_poly_mulmod( tempRing.get(),
                                _rings.get() + r*M + t,
                                rhs._rings.get() + t*OUTER_DIM + s, 
                                _F.get() );
          fmpz_mod_poly_add( matrix._rings.get() + r*OUTER_DIM + s,
                             matrix._rings.get() + r*OUTER_DIM + s,
                             tempRing.get() );
        }
      }
    }

    return matrix;
  }

  /*
   * Comparison
   */

  template< size_t N, size_t M, size_t DEG, size_t K >
  bool 
  RingMatrix<N,M,DEG,K>::operator==( const RingMatrix& rhs ) const {
    // Same object
    if ( this == &rhs ) return true; 
    // Check rings
    for ( size_t i = 0; i < N*M; ++i )
      if ( !fmpz_mod_poly_equal( _rings.get() + i, rhs._rings.get() + i ) )
        return false;
    // Must be
    return true;
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  bool 
  RingMatrix<N,M,DEG,K>::operator!=( const RingMatrix& rhs ) const {
    return !(*this == rhs);
  }

  /*
   * Transpose
   */

  template< size_t N, size_t M, size_t DEG, size_t K >
  RingMatrix<M,N,DEG,K>
  RingMatrix<N,M,DEG,K>::T() const {
    RingMatrix<M,N,DEG,K> transpose{};
    for ( size_t i = 0; i < N; ++i )
      for ( size_t j = 0; j < M; ++j )
        fmpz_mod_poly_set( transpose._rings.get() + j*N + i,
                           _rings.get() + i*M + j );

    return transpose;
  }

  /*
   * Ring Accessors and Modifiers
   */

  /*
  template< size_t N, size_t M, size_t DEG, size_t K >
  Ring<DEG,K>*
  RingMatrix<N,M,DEG,K>::getRing( size_t row, size_t col ) const {
    auto rPtr = new Ring<DEG,K>{};
    fmpz_mod_poly_set( *rPtr._rings.get()[0], _rings.get() + row*M + col );

    return rPtr;
  }
  */

  template< size_t N, size_t M, size_t DEG, size_t K >
  void 
  RingMatrix<N,M,DEG,K>::setRing( size_t row, size_t col, const Ring<DEG,K>& ring ) {
    fmpz_mod_poly_set( _rings.get() + row*M + col, ring._rings.get() );
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  size_t 
  RingMatrix<N,M,DEG,K>::getCoeff( size_t row, size_t col, size_t deg ) const {
    fmpz_t coeff_z;
    fmpz_init( coeff_z );

    fmpz_mod_poly_get_coeff_fmpz( coeff_z, _rings.get() + row*M + col, deg );
    auto coeff = fmpz_get_ui( coeff_z );

    fmpz_clear( coeff_z );

    return coeff;
  }

  template< size_t N, size_t M, size_t DEG, size_t K >
  void 
  RingMatrix<N,M,DEG,K>::setCoeff( size_t row, size_t col, size_t deg, size_t val ) {
    fmpz_mod_poly_set_coeff_ui( _rings.get() + row*M + col, deg, val );
  }

  /*
   * Representation
   */

  template< size_t N, size_t M, size_t DEG, size_t K >
  std::string 
  RingMatrix<N,M,DEG,K>::toString() const {
    std::stringstream ss;
    // Write parameters
    ss << N << " " << M << " " << DEG << " " << K << std::endl;
    // Write each ring
    for ( size_t i = 0; i < N; ++i ) {
      for ( size_t j = 0; j < M; ++j ) {
        ss << "  |";
        for ( size_t d = 0; d < DEG; ++d ) {
          ss << " " << getCoeff( i, j, d );
        }
        ss << std::endl;
      }
    }

    return ss.str();
  }

} /* namespace lattice */

#endif /* LATTICE_RING_MATRIX_HPP_ */

