
#include <lattice/DiscreteGaussianSampler.h>

#include <iostream>
#include <map>
#include <stdexcept>

#include <sys/time.h>

size_t K = 7;
size_t LAMBDA = size_t(1) << K;

size_t ITERATIONS = 1000;

class GuassianSampleDemo {
private:
  size_t _lambda;
  size_t _k;
  lattice::DiscreteGaussianSampler _sampler;

public:
  GuassianSampleDemo() : 
      _lambda( LAMBDA ), 
      _k( K ), 
      _sampler( LAMBDA, 63, K ) {}
  GuassianSampleDemo( const GuassianSampleDemo& other ) : 
      _lambda( other.lambda() ), 
      _k( other.k() ), 
      _sampler( other.sampler() ) {}
  ~GuassianSampleDemo() {}

  size_t lambda() const { return _lambda; }
  size_t k() const { return _k; }
  lattice::DiscreteGaussianSampler sampler() const { return _sampler; }


  void run() {
    std::cout << "[Demo]: Sampling ..." << std::endl;

    std::map<size_t, size_t> buckets;
    for ( size_t i = 0; i < LAMBDA; ++i )
      buckets[i] = 0;

    struct timeval start, end;
    gettimeofday( &start, 0 );

    for ( size_t i = 0; i < ITERATIONS; ++i ) {
      auto sample = _sampler.sample();
      buckets[sample] += 1;
    }

    gettimeofday( &end, 0 );

    double sampleTime = 1000000.0 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    std::cout << "[Demo]: Sampled " << ITERATIONS << " samples in " << sampleTime << " microseconds, "
              << (sampleTime/ITERATIONS) << " microseconds/sample" << std::endl;

    std::cout << "entropy consumed: " <<
    (_sampler.bitsConsumed()/_sampler.count()) << " bits/sample" << std::endl;

    std::cout << "buckets:" << std::endl;
    for ( size_t i = 0; i < LAMBDA; ++i )
      std::cout << i << ":" << buckets[i] << " " << std::endl;

    buckets.clear();
    for ( size_t i = 0; i < ITERATIONS; ++i ) {
      auto sample = _sampler.sampleWithSupport( 100 );
      buckets[sample] += 1;
    }

    std::cout << "buckets with support at 20:" << std::endl;
    for ( size_t i = 0; i < LAMBDA; ++i )
      std::cout << i << ":" << buckets[i] << " " << std::endl;
  }
};

int main() {
  try {
    GuassianSampleDemo demo;
    demo.run();
  } catch ( std::exception& e ) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
