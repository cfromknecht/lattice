#include <lattice/EncodedFSM.h>

#include <lattice/EncodedBlock.h>
#include <lattice/EncodedFSMSecretKey.h>
#include <lattice/FSM.h>
#include <lattice/GTrapdoor.h>
#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>
#include <lattice/StreamState.h>

#include <map>
#include <memory>
#include <vector>

namespace lattice {

  EncodedFSM::EncodedFSM( size_t lambda, size_t k, const FSM& fsm) :
      _secretKeyPtr(make_unique<EncodedFSMSecretKey>(lambda, k)) {
    this->preProcess( fsm );
  }

  void EncodedFSM::preProcess( const FSM& fsm ) {
    auto states = fsm.states();

    std::map<size_t, PolyRingMatrix> stateSecretKeys;
    // secret start key is already generated
    stateSecretKeys[0] = _secretKeyPtr->start();
    // create new random key for every state except start state
    for ( size_t stateID = 1; stateID < fsm.numStates(); ++stateID ) {
      // key should Z^n -> 1 polynomial in ring setting
      auto stateKey = PolyRingMatrix{1, 1, _secretKeyPtr->lambda(),
      _secretKeyPtr->k()};
      stateSecretKeys[stateID] = stateKey;
    }

    /**
     * Encode transitions using public matrices and  secret start and terminal
     * states.
     */
    auto G = GTrapdoor{_secretKeyPtr->k(), _secretKeyPtr->lambda()};
    auto transitions = fsm.transitions();
    for ( size_t stateID = 0; stateID < fsm.numStates(); ++stateID ) {
      auto transition = transitions[stateID];

      // retrieve state keys
      auto currentStateKey = stateSecretKeys[stateID];
      auto stateKeyFor0 = stateSecretKeys[transition.nextStateFor0()];
      auto stateKeyFor1 = stateSecretKeys[transition.nextStateFor1()];

      // sample error
      auto e0 = _secretKeyPtr->buildTernaryTempMatrix( 1, 1 );
      auto e1 = _secretKeyPtr->buildTernaryTempMatrix( 1, 1 );

      // encode transitions
      auto t0 = _secretKeyPtr->A0() * currentStateKey + e0 + G * stateKeyFor0;
      auto t1 = _secretKeyPtr->A1() * currentStateKey + e1 + G * stateKeyFor1;
      
      _transitions.push_back( t0 );
      _transitions.push_back( t1 );

      // generate error for terminal transition
      auto et = _secretKeyPtr->buildTernaryTempMatrix( 1, 1 );

      // encode terminal transition
      if ( states[stateID].acceptState() ) {
        auto tt = _secretKeyPtr->At() * currentStateKey + et + G *
        _secretKeyPtr->accept();
        _acceptTransitions.push_back( tt );
      } else {
        auto tt = _secretKeyPtr->At() * currentStateKey + et + G *
        _secretKeyPtr->reject();
        _rejectTransitions.push_back( tt );
      }
    }
  }

  size_t EncodedFSM::openStream() {
    _currentTag += 1 ;
    _streamStates[_currentTag] = StreamState( true );
    return _currentTag;
  }

  EncodedBlockPtr EncodedFSM::encode( size_t tag, bool x, bool isLastBit ) {
    StreamState newState( false );
    EncodedBlockPtr encodedBlock = make_unique<EncodedBlock>();

    PolyRingMatrixPtr prevToken;
    if ( _streamStates[tag].isInitialUse ) {
        prevToken = _secretKeyPtr->buildUniformMatrix( 1, 1 );
        // initToken should only be non nill for first bit in stream
        encodedBlock->initToken = make_unique<PolyRingMatrix>( *prevToken +
        _secretKeyPtr->start() );
    } else if ( !_streamStates[tag].prevToken ) {
      throw std::logic_error( "[EncodedFSM]: Stream has already been used but "
          "previous token does not exist" );
    } else {
      prevToken = std::move( _streamStates[tag].prevToken );
    }

    auto currToken = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );
    auto error = _secretKeyPtr->buildTernaryTempMatrix( 1, 1 );
    auto G = GTrapdoor{_secretKeyPtr->k(), _secretKeyPtr->lambda()};
    // retrieve transition matrix
    auto Ax = x ? _secretKeyPtr->A1() : _secretKeyPtr->A0();
    // encode transition
    auto encodedBit = Ax * *prevToken + error + G * currToken;

    encodedBlock->encodedBit = make_unique<PolyRingMatrix>(encodedBit);
    newState.prevToken = make_unique<PolyRingMatrix>(currToken);

    if ( isLastBit ) {
      auto terminalToken = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );
      auto terminalError = _secretKeyPtr->buildTernaryTempMatrix( 1, 1 );

      auto encodedTerminalToken = _secretKeyPtr->At() * *currToken + terminalError + 
          G * terminalToken;

      auto B = _secretKeyPtr->buildUniformTempMatrix( _secretKeyPtr->k(), 1 );
      auto r0 = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );
      auto r1 = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );

      // generate errors
      auto e0 = _secretKeyPtr->buildTernaryTempMatrix( 1, 1 );
      auto e1 = _secretKeyPtr->buildTernaryTempMatrix( 1, 1 );

      auto encodedRejectToken = B * (_secretKeyPtr->reject() + terminalToken) + e0 + 
          G * r0;
      auto encodedAcceptToken = B * (_secretKeyPtr->accept() + terminalToken) + e1 + 
          G * r1;

      encodedBlock->encodedTerminalToken =
          make_unique<PolyRingMatrix>(encodedTerminalToken);
      encodedBlock->encodedRejectToken =
          make_unique<PolyRingMatrix>(encodedRejectToken);
      encodedBlock->encodedAcceptToken =
          make_unique<PolyRingMatrix>(encodedAcceptToken);
      encodedBlock->B = make_unique<PolyRingMatrix>(B);

      newState.r0 = make_unique<PolyRingMatrix>(r0);
      newState.r1 = make_unique<PolyRingMatrix>(r1);
    }

    // update previous state
    _previousStates[tag] = newState;

    return encodedBlock;
  }

} // namespace lattice

