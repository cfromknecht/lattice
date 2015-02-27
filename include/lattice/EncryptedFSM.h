#ifndef _ENCRYPTED_FSM_H_
#define _ENCRYPTED_FSM_H_

#include <vector>

namespace lattice {

  class EncryptedFSM {
  private:

    const std::vector<PolyRingMatrix*> _transitions{};
    const std::vector<PolyRingMatrix*> _acceptTransitions{};
    const std::vector<PolyRingMatrix*> _rejectTransitions{};
    const EncryptedFSMSecretKey& _secretKey;

    EncryptedFSM() = delete;

  public:

    EncryptedFSM( size_t lambda, size_t k, const FSM& fsm );
  };

}

#endif

