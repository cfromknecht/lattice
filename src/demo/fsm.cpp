#include <lattice/FSM.h>

#include <iostream>

void runFSMOnString( lattice::FSM& fsm, const std::string& input ) {
  size_t inputLength = input.size();
  for ( size_t i = 0; i < inputLength; ++i )
    for ( size_t b = 7; b < 8; --b ) {
      size_t nextSymbol = (input[i] >> b) & 1;
      fsm.applyTransition( nextSymbol );
    }
  std::cout << "input: " << input <<  " accept: " << fsm.isInAcceptState() << std::endl;
  fsm.reset();
}

int main() {
  std::string filename{"fsm/fsm-a.in"};

  auto fsm = lattice::FSM{};
  auto valid = fsm.buildFSMFromFile( filename );
  if ( !valid )
    std::cout << "invalid FSM file" << std::endl;
  else
    std::cout << "valid FSM file" << std::endl;

  // test on sentence
  std::string sentence{"This sentence has the letter b."};
  runFSMOnString( fsm, sentence );
  // test on alphabet
  std::string letter{"a"};
  for ( size_t i = 0; i < 26; ++i ) {
    runFSMOnString( fsm, letter );
    letter[0] = size_t(letter[0]) + 1;
  }

  return 0;
}

