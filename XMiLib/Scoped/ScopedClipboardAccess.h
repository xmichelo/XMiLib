/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of scoped clipboard access.


#ifndef XMILIB_CLIPBOARD_TEST_SCOPED_CLIPBOARD_ACCESS_H
#define XMILIB_CLIPBOARD_TEST_SCOPED_CLIPBOARD_ACCESS_H


namespace xmilib {


//****************************************************************************************************************************************************
/// \brief A class for scoped clipboard access. The constructor opens the clipboard, and the destructor closes it
//****************************************************************************************************************************************************
class ScopedClipboardAccess {
public: // member functions
    explicit ScopedClipboardAccess(HWND handle); ///< Default constructor.
    ScopedClipboardAccess(ScopedClipboardAccess const &) = delete; ///< Disabled copy-constructor.
    ScopedClipboardAccess(ScopedClipboardAccess &&) = delete; ///< Disabled assignment copy-constructor.
    ~ScopedClipboardAccess(); ///< Destructor.
    ScopedClipboardAccess &operator=(ScopedClipboardAccess const &) = delete; ///< Disabled assignment operator.
    ScopedClipboardAccess &operator=(ScopedClipboardAccess &&) = delete; ///< Disabled move assignment operator.
    bool isOpen() const; ///< Is the clipboard open?

private: // data members
    bool isOpen_ { false }; ///< Is the clipboard open?
};


} // namespace xmilib


#endif // XMILIB_CLIPBOARD_TEST_SCOPED_CLIPBOARD_ACCESS_H
