#include <lattice/StreamingDelegator.h>

#include <lattice/DishonestEvaluatorException.h>
#include <lattice/EncodedFSM.h>
#include <lattice/Helper.hpp>

#include <exception>
#include <map>
#include <sstream>
#include <string>

namespace lattice {

  StreamingDelegator::StreamingDelegator( size_t lambda, size_t k, 
      const FSM& fsm ) : 
      _encodedFSM( make_unique<EncodedFSM>( lambda, k, fsm ) ) {}

  size_t StreamingDelegator::openStream( const std::string& ipAddress ) {
    // create stream and record ip address
    auto newTag = _encodedFSM->openStream();
    _ipAddresses[newTag] = ipAddress;

    return newTag;
  }

  void StreamingDelegator::encode( size_t tag, bool x, bool isLastBit ) {
    auto encodedBlock = _encodedFSM->encode( tag, x, isLastBit );
    auto ipAddress = _ipAddresses[tag];
    // TODO send block to ipAddress
  }

  void StreamingDelegator::encode( size_t tag, const std::string& input, bool
      isLastString ) {
    auto inputLength = input.size();
    std::cout << "[StreamingDelegator]: encrypting string of length " 
              << inputLength << std::endl;
    for ( size_t i = 0; i < inputLength; ++i ) {
      for ( size_t j = 7; j < 8; --j ) {
        std::cout << "." << std::flush;
        bool nextSymbol = (input[i] >> j) & 1;
        if ( !isLastString ) {
          this->encode( tag, nextSymbol, false );
        } else {
          auto isLastBit = (i == inputLength-1) && (j == 0);
          if ( isLastBit ) std::cout << std::endl;
          this->encode( tag, nextSymbol, isLastBit );
        }
      }
    }
  }

  bool StreamingDelegator::verify( size_t tag ) {
    auto ipAddress = _ipAddresses[tag];

    // TODO retrieve computation
//    std::cout << "[StreamingDelegator]: creating fake proof ..." << std::endl;
    auto proof = make_unique<PolyRingMatrix>( 1, 1, 256, 8 );
//    std::cout << "[StreamingDelegator]: getting previous state ..." << std::endl;
    auto prevState = _encodedFSM->streamStateForTag( tag );

    // if proof equals r0 or r1, evaluation was honest.  Otherwise we should not
    // trust the evaluator
    if ( prevState->r0 == proof ) {
      return false;
    } else if ( prevState->r1 == proof ) {
      return true;
    } else {
      throw DishonestEvaluatorException{tag};
    }
  }

} // namespace lattice

