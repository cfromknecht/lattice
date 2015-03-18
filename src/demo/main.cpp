#include <lattice/StreamingDelegator.h>
#include <lattice/Helper.hpp>

#include <stdexcept>
#include <iostream>
#include <string>

#include <sys/time.h>

class StreamingDelegatorDemo {
private:
  size_t _lambda = 256;
  size_t _k = 8;
  lattice::StreamingDelegator _streamingDelegator;

  StreamingDelegatorDemo() = delete;

public:
  StreamingDelegatorDemo( const std::string& filename ) :
      _streamingDelegator( _lambda, _k, lattice::FSM{filename} ) {}
  StreamingDelegatorDemo( const lattice::FSM& fsm ) :
    _streamingDelegator( _lambda, _k, fsm ) {}
  ~StreamingDelegatorDemo() {}

  void run() {
    std::string ipAddress{"127.0.0.1"};
    std::string testString{"Hello World, do I contain the letter a?"};
    
    std::cout << "[Demo]: Opening stream ..." << std::endl;
    auto streamTag = _streamingDelegator.openStream( ipAddress );

    struct timeval start, end;
    std::cout << "[Demo]: Encoding test string ..." << std::endl;
    gettimeofday( &start, 0 );
    _streamingDelegator.encode( streamTag, testString, true );
    gettimeofday( &end, 0 );
    double encodeTime = 1000000.0 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    std::cout << "[Demo]: Encoded string in " << encodeTime << " microseconds, "
              << (encodeTime/(8*double(testString.length()))) << " microseconds/bit"
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
  std::string filename{"fsm/fsm-a.in"};
  try {
    StreamingDelegatorDemo demo{filename};
    demo.run();
  } catch (std::exception& e ) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
