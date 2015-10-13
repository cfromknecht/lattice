#include <lattice/EncodedFSM.h>

#include <lattice/EncodedBlock.h>
#include <lattice/EncodedFSMSecretKey.h>
#include <lattice/FSM.h>
#include <lattice/GTrapdoor.h>
#include <lattice/Helper.hpp>
#include <lattice/PolyRingMatrix.h>
#include <lattice/StreamState.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace lattice {

  EncodedFSM::EncodedFSM( size_t lambda, size_t k, const FSM& fsm ) :
      _secretKeyPtr( make_unique<EncodedFSMSecretKey>( lambda, k ) ),
      _currentTag( 0 ) {
    this->preProcess( fsm );

    std::cout << "encoded fsm size:\n" << this->toString().size() << std::endl;
  }

  void EncodedFSM::preProcess( const FSM& fsm ) {
    std::cout << "[EncodedFSM]: Preproccessing FSM ..." << std::endl;

    size_t k = _secretKeyPtr->k();
    size_t lambda = _secretKeyPtr->lambda();

    auto states = fsm.states();

    std::map<size_t, PolyRingMatrixPtr> stateSecretKeys;
    // secret start key is already generated
    stateSecretKeys[0] = make_unique<PolyRingMatrix>( *_secretKeyPtr->start() );
    // create new random key for every state except start state
    std::cout << "[EncodedFSM]: Creating encoded state keys ..." << std::endl;
    for ( size_t stateID = 1; stateID < fsm.numStates(); ++stateID ) {
      // key should be Z^n -> 1 polynomial in ring setting
      auto stateKey = PolyRingMatrix{1, 1, lambda, k};
      stateKey.uniformInit();
      stateSecretKeys[stateID] = make_unique<PolyRingMatrix>( stateKey );
    }

    /**
     * Encode transitions using public matrices and  secret start and terminal
     * states.
     */
    auto G = GTrapdoor{k, lambda};
    auto transitions = fsm.transitions();
    std::cout << "[EncodedFSM]: Creating encoded transitions ..." << std::endl;
    for ( size_t stateID = 0; stateID < fsm.numStates(); ++stateID ) {
      auto transition = transitions[stateID];

      // retrieve state keys
      auto currentStateKey = make_unique<PolyRingMatrix>( *stateSecretKeys[stateID] );
      auto stateKeyFor0 = make_unique<PolyRingMatrix>( *stateSecretKeys[transition.nextStateFor0()]);
      auto stateKeyFor1 = make_unique<PolyRingMatrix>( *stateSecretKeys[transition.nextStateFor1()] );

      // sample error
      auto e0 = _secretKeyPtr->buildTernaryTempMatrix( k, 1 );
      auto e1 = _secretKeyPtr->buildTernaryTempMatrix( k, 1 );

      // encode transitions
      auto t0 = *_secretKeyPtr->A0() * *currentStateKey + e0 + G * *stateKeyFor0;
      auto t1 = *_secretKeyPtr->A1() * *currentStateKey + e1 + G * *stateKeyFor1;
      
      _transitions.push_back( make_unique<PolyRingMatrix>( t0 ) );
      _transitions.push_back( make_unique<PolyRingMatrix>( t1 ) );

      // generate error for terminal transition
      auto et = _secretKeyPtr->buildTernaryTempMatrix( k, 1 );

      // encode terminal transition
      if ( states[stateID].acceptState() ) {
        auto tt = *_secretKeyPtr->At() * *currentStateKey + et + G * 
            *_secretKeyPtr->accept();
        _acceptTransitions.push_back( make_unique<PolyRingMatrix>( tt ) );
      } else {
        auto tt = *_secretKeyPtr->At() * *currentStateKey + et + G *
            *_secretKeyPtr->reject();
        _rejectTransitions.push_back( make_unique<PolyRingMatrix>( tt ) );
      }
    }
    std::cout << "[EncodedFSM]: DONE preprocessing" << std::endl;
  }

  size_t EncodedFSM::openStream() {
    _streamStates[_currentTag] = make_unique<StreamState>( true );
    return _currentTag++;
  }

  EncodedBlockPtr EncodedFSM::encode( size_t tag, bool x, bool isLastBit ) {
    auto k = _secretKeyPtr->k();
    auto lambda = _secretKeyPtr->lambda();

    auto newState = make_unique<StreamState>( false );
    EncodedBlockPtr encodedBlock = make_unique<EncodedBlock>();

    PolyRingMatrixPtr prevToken;
    if ( _streamStates[tag]->isInitialUse() ) {
        prevToken = _secretKeyPtr->buildUniformMatrix( 1, 1 );
        // initToken should only be non nil for first bit in stream
        auto initToken = *prevToken + *_secretKeyPtr->start();
        encodedBlock->setInitToken( new PolyRingMatrix{initToken} );
    } else {
      prevToken = make_unique<PolyRingMatrix>( _streamStates[tag]->prevToken() );
    }

    auto currToken = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );
    auto error = _secretKeyPtr->buildTernaryTempMatrix( k, 1 );
    auto G = GTrapdoor{k, lambda};
    // retrieve transition matrix
    auto Ax = x ? _secretKeyPtr->A1() : _secretKeyPtr->A0();
    // encode transition
    auto encodedBit = *Ax * *prevToken + error + G * currToken;

    encodedBlock->setEncodedBit( new PolyRingMatrix{encodedBit} );
    newState->setPrevToken( currToken );


    if ( isLastBit ) {
      std::cout << "encoded bit size: " << encodedBlock->getEncodedBit()->toString().size() << std::endl;
      auto terminalToken = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );
      auto terminalError = _secretKeyPtr->buildTernaryTempMatrix( k, 1 );

      auto encodedTerminalToken = *_secretKeyPtr->At() * currToken + terminalError + 
          G * terminalToken;

      auto B = _secretKeyPtr->buildUniformTempMatrix( k, 1 );
      auto r0 = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );
      auto r1 = _secretKeyPtr->buildUniformTempMatrix( 1, 1 );

      // generate errors
      auto e0 = _secretKeyPtr->buildTernaryTempMatrix( k, 1 );
      auto e1 = _secretKeyPtr->buildTernaryTempMatrix( k, 1 );

      auto encodedRejectToken = B * (*_secretKeyPtr->reject() + terminalToken) + e0 + G * r0;
      auto encodedAcceptToken = B * (*_secretKeyPtr->accept() + terminalToken) + e1 + G * r1;

      encodedBlock->setEncodedTerminalToken( new PolyRingMatrix{encodedTerminalToken} );
      encodedBlock->setEncodedRejectToken( new PolyRingMatrix{encodedRejectToken} );
      encodedBlock->setEncodedAcceptToken( new PolyRingMatrix{encodedAcceptToken} );
      encodedBlock->setB( new PolyRingMatrix{B} );

      newState->setR0( r0 );
      newState->setR1( r1 );
    }

    if ( !_streamStates[tag] )
      std::cout << "[EncodedFSM]: Stream state does not exist" << std::endl;

    // update previous state
    _streamStates[tag] = std::move( newState );

    return encodedBlock;
  }

  void EncodedFSM::evaluate( size_t tag ) {
    auto lambda = _secretKeyPtr->lambda();
    auto k = _secretKeyPtr->k();

    // trapdoor for G
    auto TG = lattice::PolyRingMatrix{k, k, lambda, k};
    for ( size_t i = 0; i < k; ++i ) {
      TG.setCoeff( i, i, 0, 2 );
      if ( i < k-1 )
        TG.setCoeff( i, i + 1, 0, -1 );
    }

    auto add = _streamStates[tag]->prevToken() + _streamStates[tag]->prevToken();
    auto A = _secretKeyPtr->A0();
    auto randomToken = PolyRingMatrix{1, 1, lambda, k};
    auto randomShit = PolyRingMatrix{k, 1, lambda, k};
    randomToken.uniformInit();
    randomShit.uniformInit();

    auto Ay = *A * randomToken;
    auto TGe = TG * (randomShit - Ay);
    auto m = randomShit - Ay - TGe;
  }

  StreamStatePtr EncodedFSM::streamStateForTag( size_t tag ) {
//    std::cout << "[EncodedFSM]: retrieving stream state for tag " << tag 
//              << std::endl;
//    std::cout << "[EncodedFSM]: Stream state count for tag " << _currentTag 
//              << ": " << _streamStates.count( _currentTag ) << std::endl;
    return make_unique<StreamState>( *_streamStates[tag] );
  }

  std::string EncodedFSM::toString() const {
    std::stringstream ss;

    ss << this->toStringPublicKey();
    ss << this->toStringSecretKey();
    ss << this->toStringTransitions();

    return ss.str();
  }

  std::string EncodedFSM::toStringPublicKey() const {
    std::stringstream ss;

    ss << _secretKeyPtr->At()->toString();
    ss << _secretKeyPtr->A0()->toString();
    ss << _secretKeyPtr->A1()->toString();

    return ss.str();
  }

  std::string EncodedFSM::toStringSecretKey() const {
    std::stringstream ss;

    ss << _secretKeyPtr->start()->toString();
    ss << _secretKeyPtr->accept()->toString();
    ss << _secretKeyPtr->reject()->toString();

    return ss.str();
  }

  std::string EncodedFSM::toStringTransitions() const {
    std::stringstream ss;

    for ( size_t i = 0; i < _transitions.size(); ++i )
      ss << _transitions[i]->toString();
    for ( size_t i = 0; i < _acceptTransitions.size(); ++i )
      ss << _transitions[i]->toString();
    for ( size_t i = 0; i < _rejectTransitions.size(); ++i )
      ss << _transitions[i]->toString();

    return ss.str();
  }

} // namespace lattice

