//# IterError.cc:
//# Copyright (C) 1993,1994,1995,2000
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA

#include <casacore/casa/Containers/IterError.h>


namespace casacore { //# NAMESPACE CASACORE - BEGIN

// The normal constructor when throwing the exception.
IterError::IterError (const char *msg,Category c) : 
          AipsError(msg ? msg : "Iterator Error.",c) {}

IterError::~IterError () noexcept
{ ; }

// The normal constructor when throwing the exception.
IterBoundaryError::IterBoundaryError (const char *msg,Category c) : 
          IterError(msg ? msg : "Iterator boundaries exceeded.",c) {}

IterBoundaryError::~IterBoundaryError () noexcept
{ ; }


// The normal constructor when throwing the exception.
IterInitError::IterInitError (const char *msg,Category c) : 
          IterError(msg ? msg : "Iterator initialization error.",c) {}

IterInitError::~IterInitError () noexcept
{ ; }

// The normal constructor when throwing the exception.
InvalidIterError::InvalidIterError (const char *msg,Category c) : 
          IterError(msg ? msg : "Use of invalid iterator.",c) {}

InvalidIterError::~InvalidIterError () noexcept
{ ; }

} //# NAMESPACE CASACORE - END

