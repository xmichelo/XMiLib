/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of threaded operation class


#include "stdafx.h"
#include "ThreadedOperation.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] description The description of the operation
/// \param[in] parent The parent object of the instance
//**********************************************************************************************************************
ThreadedOperation::ThreadedOperation(QString const& description, QObject* parent)
   : QObject(parent)
   , description_(description)
{

}


//**********************************************************************************************************************
/// \return The description of the operation
//**********************************************************************************************************************
QString ThreadedOperation::getDescription() const
{
   return description_;
}


} // namespace xmilib