/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of a scoped lock for Windows global memory.


#include "stdafx.h"
#include "ScopedGlobalMemoryLock.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] handle The handle to the global memory object.
//**********************************************************************************************************************
ScopedGlobalMemoryLock::ScopedGlobalMemoryLock(HGLOBAL handle)
   : handle_(handle)
   , pointer_(GlobalLock(handle))
{
   
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
ScopedGlobalMemoryLock::~ScopedGlobalMemoryLock()
{
   if (pointer_)
      GlobalUnlock(handle_);
}


//**********************************************************************************************************************
/// \return A pointer to the locked memory. If locked_ is false, the return value is null.
//**********************************************************************************************************************
void* ScopedGlobalMemoryLock::pointer() const
{
   return pointer_;
}


} // namespace xmilib
