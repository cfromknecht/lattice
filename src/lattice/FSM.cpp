#include <lattice/FSM.h>

namespace lattice {

  /**
   * Initializes an empty FSM
   */
  FSM::FSM() : _states{std::map<size_t, FSMState>{}}, 
    _transitions{std::map<size_t, FSMTransition>{}}, _currentState{0}, 
    _numStates{0} {}

  /**
   * Initializes an FSM to be identical to an existing FSM
   * @param FSM other - the FSM to be copied
   */
  FSM::FSM( const FSM& other ) : _states{other.states()}, 
    _transitions{other.transitions()}, _currentState{other.currentState()}, 
    _numStates{other.numStates()} {}

  /**
   * Assigns an existing FSM to be identical to an existing FSM
   * @param FSM rhs - the FSM to be copied
   * @return - the current FSM
   */
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

  /**
   * Destroys and FSM
   */
  FSM::~FSM() {}

  /**
   * Resets the start state of the FSM
   */
  void FSM::reset() {
    _currentState = 0;
  }

  /**
   * Determines whether the FSM has reached an accept state.
   * @return - boolean denoting whether the currentState is a member of the
   * accept states.
   */
  bool FSM::isInAcceptState() {
    if ( _states.count( _currentState ) == 0 ) 
      throw std::runtime_error{"Cannot determine accept state if currentState "
        "does not exist"};
    return _states[_currentState].acceptState();
  }

  /**
   * Examines the current stateID of the FSM
   * @return - the stateID of the currentState
   */
  size_t FSM::readState() {
    if ( _states.count( _currentState ) == 0 ) 
      throw std::runtime_error{"Cannot readState if currentState does not exist"};
    return _currentState;
  }

  /**
   * Advances the state of the FSM given a symbol.
   * @param bool nextSymbol - symbol that determines the subsequent transition
   */
  void FSM::applyTransition( bool nextSymbol ) {
    if ( _transitions.count( _currentState ) == 0 ) 
      throw std::runtime_error{"No transition entry for currentState"};
    _currentState = _transitions[_currentState].nextStateForSymbol( nextSymbol );
  }


  /**
   * Checks that the state to add is unique and saves it to the hash table.
   * @param size_t stateID - the ID of the new state
   * @param bool acceptState - flag denoting whether stateID is an accept state
   */
  void FSM::addState( size_t stateID, bool acceptState ) {
    if ( _states.count( stateID ) > 0 ) 
      throw std::runtime_error{"StateID already exists"};

    auto state = FSMState{stateID, acceptState};
    _states[stateID] = state;
    _numStates++;
  }

  /**
   * Checks that the transition to add is unique and saves it to the hash table.
   * @param size_t fromState - the ID of the originating state
   * @param size_t next0 - the ID of the state to move to for symbol 0
   * @param size_t next1 - the ID of the state to move to for symbol 1
   */
  void FSM::addTransition( size_t fromState, size_t next0, size_t next1 ) {
    if ( _transitions.count( fromState ) > 0 )
      throw std::runtime_error{"Transitions beginning at fromState already exist"};

    _transitions[fromState] = FSMTransition{next0, next1};
  }

  /**
   * Performs the Hopcroft FSM minimization algorithm
   * @return - the number of states removed
   */
  size_t FSM::hopcroftOptimization() {
    return 0;
  }

  /**
   * Constructs a state machine from the input filename
   * @param string filename - relative path to file
   * @return - denotes the validtty of the FSM constructed from the input file
   */
  bool FSM::buildFSMFromFile( const std::string& filename ) {
    std::ifstream ifs{filename, std::ifstream::in};

    // clear current FSM
    _states.clear();
    _transitions.clear();
    _currentState = 0;
    _numStates = 0;

    size_t count, blank, next0, next1;
    bool accept;
    ifs >> count;
    // parse states
    for ( size_t i = 0; i < count; ++i ) {
      ifs >> blank >> accept;
      addState( i, accept );
    }
    // parse transitions
    for ( size_t i = 0; i < count; ++i ) {
      ifs >> blank >> next0 >> next1;
      addTransition( i, next0, next1 );
    }

    return validFSM();
  }

  /**
   * Determines the validity of an FSM.  The number of FSMStates and
   * FSMTransitions should match, and each FSMState's stateID should correspond 
   * to its key.  Additionally, each transition should point to another existing 
   * state.
   */
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

}


