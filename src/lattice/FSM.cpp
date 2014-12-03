#include <lattice/FSM.h>

namespace lattice {

  FSM::FSM() : _states{std::map<size_t, FSMState>{}}, 
    _transitions{std::map<size_t, FSMTransition>{}}, _currentState{0}, 
    _numStates{0} {}

  FSM::FSM( const FSM& other ) : _states{other.states()}, 
    _transitions{other.transitions()}, _currentState{other.currentState()}, 
    _numStates{other.numStates()} {}

  FSM& FSM::operator=( const FSM& rhs ) {
    if ( this != &rhs ) {
      // copy states
      _states = std::map<size_t, FSMState>(rhs.states());
      _transitions = std::map<size_t, FSMTransition>(rhs.transitions());
      _numStates = rhs.numStates();
      _currentState = rhs.currentState();
    }
    return *this;
  }

  FSM::~FSM() {}

  void FSM::reset() {
    _currentState = 0;
  }

  bool FSM::isInAcceptState() {
    if ( _states.count( _currentState ) == 0 ) 
      throw std::runtime_error{"Cannot determine accept state if currentState "
        "does not exist"};
    return _states[_currentState].acceptState();
  }

  size_t FSM::readState() {
    if ( _states.count( _currentState ) == 0 ) 
      throw std::runtime_error{"Cannot readState if currentState does not exist"};
    return _currentState;
  }

  void FSM::applyTransition( bool nextSymbol ) {
    if ( _transitions.count( _currentState ) == 0 ) 
      throw std::runtime_error{"No transition entry for currentState"};
    _currentState = _transitions[_currentState].nextStateForSymbol( nextSymbol );
  }

  void FSM::addState( size_t stateID, bool acceptState ) {
    std::cout << "adding state: " << stateID << std::endl;
    if ( _states.count( stateID ) > 0 ) 
      throw std::runtime_error{"StateID already exists"};

    auto state = FSMState{stateID, acceptState};
    _states[stateID] = state;
    _numStates++;
  }

  bool FSM::validFSM() {
    // should have same number of states and transitions
    if ( _states.size() != _transitions.size() )
      return false;
    // iterate over states
    for ( std::map<size_t, FSMState>::iterator it = _states.begin(); 
        it != _states.end(); ++it ) {
      // states should match and have corresponding transitions
      size_t stateID = it->first;
      FSMState state = it->second;
      if ( state.stateID() != stateID || _transitions.count( stateID ) == 0 )
        return false;
      // transition states should exist in states map
      size_t nextState0 = _transitions[stateID].nextStateForSymbol( 0 );
      size_t nextState1 = _transitions[stateID].nextStateForSymbol( 1 );
      if ( _states.count( nextState0 ) == 0 || _states.count( nextState1 ) == 0 )
        return false;
    }

    return true;
  }

  /**
   * Performs the Hopcroft FSM minimization algorithm
   * @return - the number of states removed
   */
  size_t FSM::hopcroftOptimization() {
    return 0;
  }

  bool FSM::buildFSMFromFile( const std::string& filename ) {
    std::ifstream ifs{filename, std::ifstream::in};

    _states.clear();
    _transitions.clear();
    _currentState = 0;
    _numStates = 0;

    size_t count, blank, next0, next1;
    bool accept;
    ifs >> count;
    for ( size_t i = 0; i < count; ++i ) {
      ifs >> blank >> accept;
      addState( i, accept );
    }
    for ( size_t i = 0; i < count; ++i ) {
      ifs >> blank >> next0 >> next1;
      _transitions[i] = FSMTransition{next0, next1};
    }

    return validFSM();
  }

}


