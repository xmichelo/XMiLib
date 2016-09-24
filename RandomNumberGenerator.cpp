/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of thread-safe integer pseudo random number generator


#include "stdafx.h"
#include "RandomNumberGenerator.h"
#include "Exception.h"


namespace xmilib {


//**********************************************************************************************************************
/// This variant of the constructor does not require a seed to be provided as it uses std::random_device to get
/// a random seed. std::random_device() being notably slow it's only used to provide a seed to the pseudo random
/// number generator
///
/// \note Microsoft's implementation of random_device guarantees that values produced by std::random_device 
/// are non-deterministic and cryptographically secure, but the C++11 standard does not impose these conditions.
/// Be careful when porting to other compilers/platforms
///
/// \param[in] min The minimum value the generator will return
/// \param[in] max The maximum value the generator will return
//**********************************************************************************************************************
RandomNumberGenerator::RandomNumberGenerator(qint32 min, qint32 max)
   : generator_(std::random_device()())
   , distrib_() // we defer the initialization of the distribution with the right values in order to be able to raise our own exception
   , mutex_()
{
   if (min > max)
      throw xmilib::Exception(QString("%1(): invalid min and max value. min must be <= max.").arg(__FUNCTION__));
   distrib_ = std::uniform_int_distribution<int>(min, max);
}


//**********************************************************************************************************************
/// \param[in] seed The seed to use for the pseudo random number generation
/// \param[in] min The minimum value the generator will return
/// \param[in] max The maximum value the generator will return
//**********************************************************************************************************************
RandomNumberGenerator::RandomNumberGenerator(quint32 seed, qint32 min, qint32 max)
   : generator_(seed)
   , distrib_() // we defer the initialization of the distribution with the right values in order to be able to raise our own exception
   , mutex_()
{
   if (min > max)
      throw xmilib::Exception(QString("%1(): invalid min and max value. min must be <= max.").arg(__FUNCTION__));
   distrib_ = std::uniform_int_distribution<int>(min, max);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
RandomNumberGenerator::~RandomNumberGenerator()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
qint32 RandomNumberGenerator::get()
{
   QMutexLocker locker(&mutex_);
   return distrib_(generator_);
}


} // namespace xmilib
