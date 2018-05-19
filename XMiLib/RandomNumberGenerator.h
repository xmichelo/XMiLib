/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of thread-safe integer pseudo random number generator
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  



#ifndef XMILIB_RANDOM_NUMBER_GENERATOR_H
#define XMILIB_RANDOM_NUMBER_GENERATOR_H


#include <random>


namespace xmilib {


//**********************************************************************************************************************
/// \brief A thread safe integer pseudo random number generator
//**********************************************************************************************************************
class RandomNumberGenerator
{
public: // member functions
   explicit RandomNumberGenerator(qint32 min = 0, qint32 max = std::numeric_limits<int>::max()); ///< Default constructor
   explicit RandomNumberGenerator(quint32 seed, qint32 min = 0, qint32 max = std::numeric_limits<int>::max()); ///< Constructor using a user-provided seed
	RandomNumberGenerator(RandomNumberGenerator const&) = delete; ///< Disabled copy constructor
	RandomNumberGenerator(RandomNumberGenerator&&) = delete; ///< Disabled move copy constructor
	~RandomNumberGenerator() = default; ///< Default destructor
	RandomNumberGenerator& operator=(RandomNumberGenerator const&) = delete; ///< Disabled assignment operator
	RandomNumberGenerator& operator=(RandomNumberGenerator&&) = delete; ///< Disabled move assignment operator
   qint32 get(); ///< Retrieve a pseudo-random integer in the range defined at construction time 
	
private: // data members
   QMutex mutex_; ///< The mutex used to ensure thread safety
   std::mt19937 generator_; ///< The Mersenne Twister pseudo random number generator
   std::uniform_int_distribution<int> distrib_; ///< The uniform distribution used to ensure that the return numbers are within the specified r
};


} // namespace xmilib


#endif // #ifndef XMILIB_RANDOM_NUMBER_GENERATOR_H