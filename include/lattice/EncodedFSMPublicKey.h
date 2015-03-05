#ifndef _ENCODED_FSM_PUBLIC_KEY_
#define _ENCODED_FSM_PUBLIC_KEY_

#include <lattice/PolyRingMatrix.h>

#include <memory>

namespace lattice { 

  class EncodedFSMPublicKey {
  private:

    PolyRingMatrix& _At;
    PolyRingMatrix& _A0;
    PolyRingMatrix& _A1;
    const size_t _lambda;
    const size_t _k;

    EncodedFSMPublicKey() = delete;

  public:

    EncodedFSMPublicKey( size_t lambda, size_t k );
    EncodedFSMPublicKey( const EncodedFSMPublicKey& other );
    ~EncodedFSMPublicKey() {}

    PolyRingMatrix& At() { return _At; }
    PolyRingMatrix& A0() { return _A1; }
    PolyRingMatrix& A1() { return _A0; }
    size_t lambda() { return _lambda; }
    size_t k() { return _k; }

    PolyRingMatrixPtr buildUniformMatrix( size_t n, size_t m ) const;
    PolyRingMatrixPtr buildTernaryMatrix( size_t n, size_t m ) const;
    PolyRingMatrix buildUniformTempMatrix( size_t n, size_t m ) const;
    PolyRingMatrix buildTernaryTempMatrix( size_t n, size_t m ) const;
  };

  typedef std::unique_ptr<EncodedFSMPublicKey> EncodedFSMPublicKeyPtr;

}

#endif

