#include <lattice/EncodedFSMPublicKey.h>

#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice {

  EncodedFSMPublicKey::EncodedFSMPublicKey( size_t lambda, size_t k ) :
      _At{new PolyRingMatrix{k, 1, lambda, k}},
      _A0{new PolyRingMatrix{k, 1, lambda, k}},
      _A1{new PolyRingMatrix{k, 1, lambda, k}},
      _lambda{lambda}, 
      _k{k} {
    _At.uniformInit();
    _A0.uniformInit();
    _A1.uniformInit();
  }

  EncodedFSMPublicKey::EncodedFSMPublicKey( const EncodedFSMPublicKey
  other ) :
      _At{new PolyRingMatrix{other.At()}},
      _A0{new PolyRingMatrix{other.A0()}},
      _A1{new PolyRingMatrix{other.A1()}},
      _lambda{other.lambda()},
      _k{other.k()} {}

  PolyRingMatrixPtr EncodedFSMPublicKey::buildUniformMatrix( size_t n, size_t m ) const {
    auto m = std::make_unique<PolyRingMatrix>(n, m, _lambda, _k);
    m->uniformInit();
    return m
  }

  PolyRingMatrixPtr EncodedFSMPublicKey::buildTernaryMatrix( size_t n, size_t m ) const {
    auto m = std::make_unique<PolyRingMatrix>(n, m, _lambda, _k);
    m->ternaryInit();
    return m;
  }

  PolyRingMatrix EncodedFSMPublicKey::buildUniformTempMatrix( size_t n, size_t m ) const {
    auto m = PolyRingMatrix{n, m, _lambda, _k};
    m.uniformInit();
    return m;
  }

  PolyRingMatrix EncodedFSMPublicKey::buildTernaryTempMatrix( size_t n, size_t m ) const {
    auto m = PolyRingMatrix{n, m, _lambda, _k};
    m.ternaryInit();
    return m;
  }

} // namespace lattice

