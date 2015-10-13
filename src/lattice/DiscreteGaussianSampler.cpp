#include <lattice/DiscreteGaussianSampler.h>

#include <bitset>
#include <cstdlib>
#include <iostream>

namespace lattice {

  // initialization
  DiscreteGaussianSampler::DiscreteGaussianSampler( size_t nn, size_t ll, size_t mod ) : 
      _n( nn ), 
      _l( ll ), 
      _modulus( mod ), 
      _count( 0 ),
      _bitsConsumed( 0 ),
      _thresholds( std::vector<double>( ll ) ), 
      _engine( std::mt19937{std::random_device{}()} ) {
    if ( _l > 63 ) 
      throw std::runtime_error( "Cannot use word size of greater than 63 bits" );
    this->initializeLookup();
  }

  DiscreteGaussianSampler::DiscreteGaussianSampler( const DiscreteGaussianSampler& sampler ) : 
      _n( sampler.n() ), 
      _l( sampler.l() ), 
      _modulus( sampler.modulus() ), 
      _count( 0 ),
      _bitsConsumed( 0 ),
      _thresholds( std::vector<double>( sampler.l() ) ),
      _engine( std::mt19937{std::random_device{}()} ) {
    if ( _l > 63 ) 
      throw std::runtime_error( "Cannot use word size of greater than 63 bits" );
    this->initializeLookup();
  }

  DiscreteGaussianSampler::~DiscreteGaussianSampler() {}

  // sampling
  size_t DiscreteGaussianSampler::sampleWithSupport( size_t c ) {
    _count += 1;
    while ( true ) {
      size_t z = this->gaussianPositive();
      bool b = this->bernoulli( .5 );
      if ( z == 0 && !b ) 
        continue;
      return !b ? z : (_modulus - z) % _modulus;
    }
    return (c + this->sample()) % _modulus;
  }

  // helper Methods
  size_t DiscreteGaussianSampler::gaussianPositive() {
    std::uniform_int_distribution<size_t> intDist{0, _n-1};

    while ( true ) {
      size_t x = this->gaussianBinaryPositive();
      size_t y = intDist( _engine );
      _bitsConsumed += 8;
      size_t z = x*_n + y;
      bool b = this->bernoulliExp( -y*(y + 2*x*_n) );
      if ( !b )
        continue;
      return z;
    }
  }

  size_t DiscreteGaussianSampler::gaussianBinaryPositive() {
    bool b = this->bernoulli( .5 );
    if ( !b ) return 0;

    std::vector<bool> randArray;
    size_t i = 0;
    while ( true ) {
      i++;
      randArray.clear();
      for ( size_t j = 0; j < 2*i-1; ++j )
        randArray.push_back( this->bernoulli( .5 ) );
      for ( size_t j = 0; j < 2*i-2; ++j )
        if ( randArray[j] )
          continue;
      if ( !randArray.back() )
        return i;
    }
  }

  bool DiscreteGaussianSampler::bernoulliExp( size_t x ) {
    for ( size_t i = _l - 1; i < _l; --i ) {
      size_t mask = 1LL << i;
      if ( (x & mask) > 0 )
        if ( !this->bernoulli( _thresholds[i] ) )
          return 0;
    }
    return 1;
  }

  bool DiscreteGaussianSampler::bernoulli( double p ) {
    std::bernoulli_distribution X( p );
    _bitsConsumed += 2;
    return X( _engine );
  }

  void DiscreteGaussianSampler::initializeLookup() {
    for ( size_t i = 0; i < _l; ++i )
      _thresholds[i] = this->computeThreshold( i );
  }

  double DiscreteGaussianSampler::computeThreshold( size_t i ) const {
    double x = double(1LL << i);
    x /= 2*std::pow(_n*0.8493218003, 2);
    return std::exp( -x );
  }

}

