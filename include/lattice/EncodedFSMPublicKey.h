#ifndef _ENCODED_FSM_PUBLIC_KEY_
#define _ENCODED_FSM_PUBLIC_KEY_

#include <lattice/PolyRingMatrix.h>
#include <lattice/Helper.hpp>

#include <memory>

namespace lattice { 

  class EncodedFSMPublicKey {
  private:

    PolyRingMatrixPtr _At;
    PolyRingMatrixPtr _A0;
    PolyRingMatrixPtr _A1;
    const size_t _lambda;
    const size_t _k;

    EncodedFSMPublicKey() = delete;

  public:

    EncodedFSMPublicKey( size_t lambda_, size_t k_ );
    EncodedFSMPublicKey( const EncodedFSMPublicKey& other );
    ~EncodedFSMPublicKey() {}

    PolyRingMatrixPtr At() const { return make_unique<PolyRingMatrix>( *_At ); }
    PolyRingMatrixPtr A0() const { return make_unique<PolyRingMatrix>( *_A1 ); }
    PolyRingMatrixPtr A1() const { return make_unique<PolyRingMatrix>( *_A0 ); }
    size_t lambda() const { return _lambda; }
    size_t k() const { return _k; }

    PolyRingMatrixPtr buildUniformMatrix( size_t n, size_t m ) const;
    PolyRingMatrixPtr buildTernaryMatrix( size_t n, size_t m ) const;
    PolyRingMatrix buildUniformTempMatrix( size_t n, size_t m ) const;
    PolyRingMatrix buildTernaryTempMatrix( size_t n, size_t m ) const;
  };

  typedef std::unique_ptr<EncodedFSMPublicKey> EncodedFSMPublicKeyPtr;

}

#endif

