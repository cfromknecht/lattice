#include <lattice/RingMatrix.hpp>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <sys/time.h>

const size_t DEG = 256;
const size_t K = 8;

const size_t ITERATIONS = 100;
const size_t SPREAD = 100;

double microsecondsBetween( struct timeval tv1, struct timeval tv2 ) {
  return tv2.tv_usec - tv1.tv_usec + 1000000.0*(tv2.tv_sec - tv1.tv_sec);
}

template< size_t n, size_t m, size_t deg, size_t k >
void encodeString( lattice::RingMatrix<n,m,deg,k>& rings, const std::string& msg ) {
  auto msgLength = msg.length();
  if ( msgLength * 8 > deg )
    throw std::logic_error{"Cannot encode more than 8*DEG bytes."};

  for ( size_t i = 0; i < n; ++i ) {
    for ( size_t j = 0; j < m; ++j ) {
      for ( size_t byteIndex = 0; byteIndex < msgLength; ++byteIndex ) {
        auto c = msg[byteIndex];
        for ( size_t bitIndex = 0; bitIndex < 8; ++bitIndex ) {
          bool bit = (c >> bitIndex) & 1;
          size_t encodedBit = bit ? 
                              lattice::RingMatrix<n,m,deg,k>::MODULUS/2 : 
                              0;
          rings.setCoeff( i, j, 8*byteIndex + bitIndex, encodedBit );
        }
      }
    }
  }
}

template< size_t n, size_t m, size_t deg, size_t k >
std::string decodeString( lattice::RingMatrix<n,m,deg,k>& rings ) {
  std::stringstream ss;

  size_t quarter = lattice::RingMatrix<n,m,deg,k>::MODULUS/4;
  for ( size_t i = 0; i < n; ++i ) {
    for ( size_t j = 0; j < m; ++j ) {
      for ( size_t byteIndex = 0; byteIndex < deg/8; ++byteIndex ) {
        char c = 0;
        for ( size_t bitIndex = 0; bitIndex < 8; ++bitIndex ) {
          auto coeff = rings.getCoeff( i, j, 8*byteIndex + bitIndex );
          bool decodedBit = (coeff < quarter || coeff > 3*quarter) ? 0 : 1;
          c |= (decodedBit << bitIndex);
        }
        ss << c;
      }
    }
  }

  return ss.str();
}

int main() {
  srand( time( NULL ) );

  double encrypt_time = 0;
  double decrypt_time = 0;
  struct timeval t1, t2;

  auto A = lattice::RingMatrix<1,K,DEG,K>{};
  auto s = lattice::RingMatrix<1,1,DEG,K>{};
  auto e = lattice::RingMatrix<K,1,DEG,K>{};
  auto m = lattice::RingMatrix<K,1,DEG,K>{};


  A.uniformInit();

  for ( size_t i = 0; i < ITERATIONS; ++i ) {
    gettimeofday( &t1, 0 );
    s.uniformInit();
    e.ternaryInit();
    encodeString( m, "Hello World, I am 32 characters!" );
    auto y = A.T()*s + e + m; // error correcting encryption
    gettimeofday( &t2, 0 );
    encrypt_time += microsecondsBetween( t1, t2 );

    gettimeofday( &t1, 0 );
    auto emPrime = y - A.T()*s;
    auto mPrime = decodeString( emPrime );
    gettimeofday( &t2, 0 );
    decrypt_time += microsecondsBetween( t1, t2 );

    if ( i == ITERATIONS - 1 )
      std::cout << "mPrime: " << mPrime << std::endl;
  }

  std::cout << "total time: " << encrypt_time + decrypt_time << std::endl;
  std::cout << "encrypt time: " << (encrypt_time/double(ITERATIONS)) << std::endl;
  std::cout << "decrypt time: " << (decrypt_time/double(ITERATIONS)) << std::endl;

  return 0;
}

