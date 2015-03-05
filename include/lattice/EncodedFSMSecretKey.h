#ifndef _ENCODED_FSM_SECRET_KEY_
#define _ENCODED_FSM_SECRET_KEY_

#include <lattice/PolyRingMatrix.h>
#include <lattice/EncodedFSMPublicKey.h>

#include <memory>

namespace lattice {

  class EncodedFSMSecretKey : public EncodedFSMPublicKey {
  private:

    PolyRingMatrix& _start;
    PolyRingMatrix& _accept;
    PolyRingMatrix& _reject;
    
    EncodedFSMSecretKey() = delete;

  public:

    EncodedFSMSecretKey( size_t lambda, size_t k );
    EncodedFSMSecretKey( const EncodedFSMSecretKey& other );
    ~EncodedFSMSecretKey() {}

    PolyRingMatrix& start() { return _start; }
    PolyRingMatrix& accept() { return _accept; }
    PolyRingMatrix& reject() { return _reject; }
    EncodedFSMPublicKey* publicKey() { return new EncodedFSMPublicKey{*this}; }

  };

  typedef std::unique_ptr<EncodedFSMSecretKey> EncodedFSMSecretKeyPtr;

} // namespace lattice

#endif

