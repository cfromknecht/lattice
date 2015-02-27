#ifndef _ENCRYPTED_FSM_SECRET_KEY_
#define _ENCRYPTED_FSM_SECRET_KEY_

namespace lattice {

  class EncryptedFSMSecretKey {
  private:

    const PolyRingMatrix& _start;
    const PolyRingMatrix& _accept;
    const PolyRingMatrix& _reject;
    const EncryptedFSMPublicKey& _publicKey;
    const size_t _lambda;
    const size_t _k;
    
    EncryptedFSMSecretKey() = delete;

  public:

    EncryptedFSMSecretKey( size_t lambda, size_t k );
    EncryptedFSMSecretKey( const EncryptedFSMSecretKey other );
    ~EncryptedFSMSecretKey() {}

    const PolyRingMatrix& start() { return _start; }
    const PolyRingMatrix& accept() { return _accept; }
    const PolyRingMatrix& reject() { return _reject; }
    const EncryptedFSMPublicKey& publicKey() { return _publicKey; }
    size_t lambda() { return _lambda; }
    size_t k() { return _k; }

  };

}

#endif

