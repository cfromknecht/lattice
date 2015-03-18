#ifndef _ENCODED_FSM_SECRET_KEY_
#define _ENCODED_FSM_SECRET_KEY_

#include <lattice/PolyRingMatrix.h>
#include <lattice/EncodedFSMPublicKey.h>

#include <memory>

namespace lattice {

  class EncodedFSMSecretKey : public EncodedFSMPublicKey {
  private:

    PolyRingMatrixPtr _start;
    PolyRingMatrixPtr _accept;
    PolyRingMatrixPtr _reject;
    
    EncodedFSMSecretKey() = delete;

  public:

    EncodedFSMSecretKey( size_t lambda, size_t k );
    EncodedFSMSecretKey( const EncodedFSMSecretKey& other );
    ~EncodedFSMSecretKey() {}

    PolyRingMatrixPtr start() const { return make_unique<PolyRingMatrix>( *_start ); }
    PolyRingMatrixPtr accept() const { return make_unique<PolyRingMatrix>( *_accept ); }
    PolyRingMatrixPtr reject() const { return make_unique<PolyRingMatrix>( *_reject ); }
    EncodedFSMPublicKeyPtr publicKey() const { return make_unique<EncodedFSMPublicKey>( *this ); }

  };

  typedef std::unique_ptr<EncodedFSMSecretKey> EncodedFSMSecretKeyPtr;

} // namespace lattice

#endif

