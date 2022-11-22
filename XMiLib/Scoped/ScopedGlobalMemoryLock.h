/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of a scoped lock for Windows global memory.


#ifndef XMILIB_SCOPED_GLOBAL_MEMORY_LOCK_H
#define XMILIB_SCOPED_GLOBAL_MEMORY_LOCK_H


namespace xmilib {


//****************************************************************************************************************************************************
/// \brief A class to manage Windows global memory locks using the scope of a variable instance
//****************************************************************************************************************************************************
class ScopedGlobalMemoryLock {
public: // member functions
    explicit ScopedGlobalMemoryLock(HGLOBAL handle); ///< Default constructor.
    ScopedGlobalMemoryLock(ScopedGlobalMemoryLock const &) = delete; ///< Disabled copy-constructor.
    ScopedGlobalMemoryLock(ScopedGlobalMemoryLock &&) = delete; ///< Disabled assignment copy-constructor.
    ~ScopedGlobalMemoryLock(); ///< Destructor.
    ScopedGlobalMemoryLock &operator=(ScopedGlobalMemoryLock const &) = delete; ///< Disabled assignment operator.
    ScopedGlobalMemoryLock &operator=(ScopedGlobalMemoryLock &&) = delete; ///< Disabled move assignment operator.
    bool locked() const; ///< Returns true if and only if the memory object was successfully locked.
    void *pointer() const; ///< Returns A pointer to the locked memory.

private: // data members
    HGLOBAL handle_; ///< The handle to the memory object.
    void *pointer_ { nullptr }; ///< The pointer to the locked memory object.
};


} // namespace xmilib


#endif // XMILIB_SCOPED_GLOBAL_MEMORY_LOCK_H

