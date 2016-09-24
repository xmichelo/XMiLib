/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of thread-safe integer pseudo random number generator



#ifndef XMILIB__RANDOM__NUMBER__GENERATOR__H
#define XMILIB__RANDOM__NUMBER__GENERATOR__H


#include <random>
#include <numeric>


namespace xmilib {


//**********************************************************************************************************************
/// \brief A thread safe integer pseudo random number generator
//**********************************************************************************************************************
class RandomNumberGenerator
{
public: // member functions
   RandomNumberGenerator(qint32 min = 0, qint32 max = std::numeric_limits<int>::max()); ///< Default constructor
   RandomNumberGenerator(quint32 seed, qint32 man = 0, qint32 max = std::numeric_limits<int>::max()); ///< Constructor using a user-provided seed
	~RandomNumberGenerator(); ///< Default destructor
   qint32 get(); ///< Retrieve a pseudo-random integer in the range defined at construction time 
	
private: // member functions
	RandomNumberGenerator(RandomNumberGenerator const&); ///< Disabled copy constructor
	RandomNumberGenerator& operator=(RandomNumberGenerator const&); ///< Disabled assignment operator

private: // data members
   QMutex mutex_; ///< The mutex used to ensure thread safety
   std::mt19937 generator_; ///< The Mersenne Twister pseudo random number generator
   std::uniform_int_distribution<int> distrib_; ///< The uniform distribution used to ensure that the return numbers are within the specified r
};


} // namespace xmilib


#endif // #ifndef XMILIB__RANDOM__NUMBER__GENERATOR__H