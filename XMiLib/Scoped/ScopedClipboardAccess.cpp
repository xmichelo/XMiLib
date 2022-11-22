/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of scoped clipboard access.


#include "stdafx.h"
#include "ScopedClipboardAccess.h"


namespace {
qint32 kRetryCount = 20; ///< The maximum number of retries when trying to access
qint32 kDelayBetweenRetriesMs = 50; ///< The delay betwen two attempts to open the clipboard
}


namespace xmilib {


//****************************************************************************************************************************************************
/// \param[in] handle The handle of the window requesting clipboard access. This can be null if a process with no
/// window is requesting access.
//****************************************************************************************************************************************************
ScopedClipboardAccess::ScopedClipboardAccess(HWND handle) {
    for (qint32 i = 0; i < kRetryCount; ++i) {
        if (OpenClipboard(reinterpret_cast<HWND>(handle))) {
            isOpen_ = true;
            return;
        }
        if (i != kRetryCount - 1)
            QThread::msleep(static_cast<quint32>(kDelayBetweenRetriesMs));
    }
}


//****************************************************************************************************************************************************
//
//****************************************************************************************************************************************************
ScopedClipboardAccess::~ScopedClipboardAccess() {
    if (isOpen_)
        CloseClipboard();
}


//****************************************************************************************************************************************************
/// \return true if and only if the clipboard was successfully opened.
//****************************************************************************************************************************************************
bool ScopedClipboardAccess::isOpen() const {
    return isOpen_;
}


} // namespace xmilib
