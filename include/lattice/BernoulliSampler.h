#ifndef _DISCRETE_GAUSSIAN_SAMPLER_
#define _DISCRETE_GAUSSIAN_SAMPLER_

#include <cstdlib>
#include <cmath>
#include <random>
#include <stdexcept>
#include <vector>

namespace lattice {

  class BernoulliSampler {
    private:
    std::mt19937 _engine;                           // random number generator

    public:
    BernoulliSampler();
    BernoulliSampler( const BernoulliSampler& sampler );
    ~BernoulliSampler();
    bool sample();
  };

}

#endif

