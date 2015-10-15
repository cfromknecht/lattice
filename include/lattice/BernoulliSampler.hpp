#ifndef _LATTICE_BERNOULLI_SAMPLER_HPP_
#define _LATTICE_BERNOULLI_SAMPLER_HPP_

#include <cstdlib>
#include <fstream>
#include <memory>
#include <stdexcept>

namespace lattice {

  const size_t URANDOM_BUFFER_SIZE = 1024;

  template< size_t SIZE = URANDOM_BUFFER_SIZE >
  class BernoulliSampler {

  public:
    bool sample() {
      auto currentByte = _currentBit/8;
      
      if ( currentByte >= SIZE ) {
        // Attempt to open /dev/urandom
        std::ifstream urandom{"/dev/random"};
        if ( urandom.is_open() ) {
          // Read if open
          urandom.read( _buffer.get(), SIZE );
          urandom.close();
        } else {
          // Throw otherwise
          throw std::runtime_error{"Could not open /dev/urandom"};
        }
        _currentBit = 0;
      }

      auto byte = _buffer[currentByte];
      auto bitOffset = _currentBit % 8;
      bool randomBit = byte >> bitOffset;

      _currentBit++;

      return randomBit;
    }

  private:
    size_t _currentBit = 8*SIZE; // Forces read from /dev/random on first sample

    struct deleteBuffer {
      void operator()( char* buf ) const {
        delete [] buf;
      };
    };

    using buffer_handler = std::unique_ptr<char[], deleteBuffer>;
    buffer_handler _buffer{new char[SIZE]};

  }; /* class BernoulliSampler */

} /* namespace lattice */

#endif /* _LATTICE_BERNOULLI_SAMPLER_HPP_ */

