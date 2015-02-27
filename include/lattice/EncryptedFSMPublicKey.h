#ifndef _ENCRYPTED_FSM_PUBLIC_KEY_
#define _ENCRYPTED_FSM_PUBLIC_KEY_

namespace lattice { 

  class EncryptedFSMPublicKey {
  private:

    const PolyRingMatrix& _At;
    const PolyRingMatrix& _A0;
    const PolyRingMatrix& _A1;
    const size_t _lambda;
    const size_t _k;

    EncryptedFSMPublicKey() = delete;

  public:

    EncryptedFSMPublicKey( size_t lambda, size_t k );
    EncryptedFSMPublicKey( const EncryptedFSMPublicKey& other );
    ~EncryptedFSMPublicKey() {}

    const PolyRingMatrix& At() { return _At; }
    const PolyRingMatrix& A0() { return _A1; }
    const PolyRingMatrix& A1() { return _A0; }
    size_t lambda() { return _lambda; }
    size_t k() { return _k; }

  };

}

#endif

