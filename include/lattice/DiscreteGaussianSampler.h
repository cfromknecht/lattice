#ifndef _DISCRETE_GAUSSIAN_SAMPLER_
#define _DISCRETE_GAUSSIAN_SAMPLER_

#include <cstdlib>
#include <cmath>
#include <random>
#include <stdexcept>
#include <vector>

namespace lattice {

  class DiscreteGaussianSampler {
    private:
    const size_t _n;                                // security parameter
    const size_t _l;                                // bits of input value
    const size_t _modulus;
    size_t _count;
    size_t _bitsConsumed;
    std::vector<double> _thresholds;                // lookup table
    std::mt19937 _engine;                           // random number generator

    DiscreteGaussianSampler() = delete;

    public:
    DiscreteGaussianSampler( size_t n, size_t wordSize, size_t modulus );
    DiscreteGaussianSampler( const DiscreteGaussianSampler& sampler );
    ~DiscreteGaussianSampler();
    inline size_t sample() { return this->sampleWithSupport( 0 ); }
    size_t sampleWithSupport( size_t c );
    inline size_t count() const { return _count; }
    inline size_t bitsConsumed() const { return _bitsConsumed; }

    protected:
    inline size_t n() const { return _n; }
    inline size_t l() const { return _l; }
    inline size_t modulus() const { return _modulus; }

    private:
    size_t gaussianPositive();
    size_t gaussianBinaryPositive();
    bool bernoulliExp( size_t x );
    bool bernoulli( double p );

    void initializeLookup();
    double computeThreshold( size_t i ) const;
  };

}

#endif

