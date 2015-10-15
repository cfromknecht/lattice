#include <lattice/StreamingDelegator.h>
#include <lattice/Helper.hpp>

#include <stdexcept>
#include <iostream>
#include <string>

#include <sys/time.h>

std::string FSM_FILENAME = "fsm/fsm-a.in";
size_t K = 10;

class StreamingDelegatorDemo {
private:
  size_t _k = K;
  size_t _lambda = size_t(1) << K;
  lattice::StreamingDelegator _streamingDelegator;

  StreamingDelegatorDemo() = delete;

public:
  StreamingDelegatorDemo( const std::string& filename ) :
      _streamingDelegator( _lambda, _k, lattice::FSM( filename ) ) {}
  StreamingDelegatorDemo( const lattice::FSM& fsm ) :
    _streamingDelegator( _lambda, _k, fsm ) {}
  ~StreamingDelegatorDemo() {}

  void run() {
    std::string ipAddress{"127.0.0.1"};
    std::string testString{"Hello World, do I contain the letter a?"};

    std::cout << "[Demo]: initializing FSM ... ";
    auto fsm = lattice::FSM( FSM_FILENAME );
    std::cout << "DONE" << std::endl;
    auto numStates = fsm.numStates();

    std::cout << "[Demo]: FSM has " << numStates << " states" << std::endl;

    std::cout << "[Demo]: Size of public key: ";
    std::cout << _streamingDelegator.sizeOfPublicKey() << std::endl;

    std::cout << "[Demo]: Size of secret key: ";
    std::cout << _streamingDelegator.sizeOfSecretKey() << std::endl;

    std::cout << "[Demo]: Size of transitions: ";
    std::cout <<
    (double(_streamingDelegator.sizeOfTransitions())/double(numStates)) << std::endl;
    
    // open stream with evaluator
    std::cout << "[Demo]: Opening stream ..." << std::endl;
    auto streamTag = _streamingDelegator.openStream( ipAddress );

    // encode and send test string
    struct timeval start, end;
    std::cout << "[Demo]: Encoding test string ..." << std::endl;
    gettimeofday( &start, 0 );
    _streamingDelegator.encode( streamTag, testString, true );
    gettimeofday( &end, 0 );
    double encodeTime = 1000000.0 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    std::cout << "[Demo]: Encoded string in " << encodeTime << " microseconds, "
              << (encodeTime/(8*double(testString.length()))) << " microseconds/bit"
              << std::endl;

    std::cout << "[Demo]: evaluating ..." << std::endl;
    gettimeofday( &start, 0 );
    for ( size_t i = 0; i < 100; ++i )
      _streamingDelegator.evaluate( streamTag );
    gettimeofday( &end, 0 );
    double evaluateTime = 1000000.0 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    std::cout << "[Demo]: Evaluated string in " << evaluateTime << " microseconds, "
              << (evaluateTime/100.0) << " microseconds/state"
              << std::endl;

    try {
      std::cout << "[Demo]: Verifying evaluation ..." << std::endl;
      auto result = _streamingDelegator.verify( streamTag );
      std::cout << "[Demo]: input string ";
      std::cout << (result ? "contains a" : "does not contain a") << std::endl;
    } catch (lattice::DishonestEvaluatorException& e ) {
      std::cout << e.what() << std::endl;
    }
  }
};

int main() {
  try {
    StreamingDelegatorDemo demo( FSM_FILENAME );
    demo.run();
  } catch (std::exception& e ) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
