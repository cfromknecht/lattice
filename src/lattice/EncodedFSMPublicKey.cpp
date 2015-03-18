#include <lattice/EncodedFSMPublicKey.h>

#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice {

  EncodedFSMPublicKey::EncodedFSMPublicKey( size_t lambda_, size_t k_ ) :
      _At( make_unique<PolyRingMatrix>( k_, 1, lambda_, k_) ),
      _A0( make_unique<PolyRingMatrix>( k_, 1, lambda_, k_) ),
      _A1( make_unique<PolyRingMatrix>( k_, 1, lambda_, k_ ) ),
      _lambda( lambda_ ), 
      _k( k_ ) {
    _At->uniformInit();
    _A0->uniformInit();
    _A1->uniformInit();
  }

  EncodedFSMPublicKey::EncodedFSMPublicKey( const EncodedFSMPublicKey& other ) :
      _At(make_unique<PolyRingMatrix>(*other.At())),
      _A0(make_unique<PolyRingMatrix>(*other.A0())),
      _A1(make_unique<PolyRingMatrix>(*other.A1())),
      _lambda(other.lambda()),
      _k(other.k()) {}

  PolyRingMatrixPtr EncodedFSMPublicKey::buildUniformMatrix( size_t n, size_t m ) const {
    auto mat = make_unique<PolyRingMatrix>(n, m, _lambda, _k);
    mat->uniformInit();
    return mat;
  }

  PolyRingMatrixPtr EncodedFSMPublicKey::buildTernaryMatrix( size_t n, size_t m ) const {
    auto mat = make_unique<PolyRingMatrix>(n, m, _lambda, _k);
    mat->ternaryInit();
    return mat;
  }

  PolyRingMatrix EncodedFSMPublicKey::buildUniformTempMatrix( size_t n, size_t m ) const {
    auto mat = PolyRingMatrix{n, m, _lambda, _k};
    mat.uniformInit();
    return mat;
  }

  PolyRingMatrix EncodedFSMPublicKey::buildTernaryTempMatrix( size_t n, size_t m ) const {
    auto mat = PolyRingMatrix{n, m, _lambda, _k};
    mat.ternaryInit();
    return mat;
  }

} // namespace lattice

