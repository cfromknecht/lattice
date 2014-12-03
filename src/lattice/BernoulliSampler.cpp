#include <lattice/BernoulliSampler.h>

#include <bitset>
#include <cstdlib>
#include <iostream>
#include <random>

namespace lattice {

  // initialization
  BernoulliSampler::BernoulliSampler() :
      _engine{std::mt19937{std::random_device{}()}} {}

  BernoulliSampler::BernoulliSampler( const BernoulliSampler& ) :
      _engine{std::mt19937{std::random_device{}()}} {}

  BernoulliSampler::~BernoulliSampler() {}

  // sampling
  bool BernoulliSampler::sample() {
    std::bernoulli_distribution dist{.5};
    return dist( _engine );
  }

}

