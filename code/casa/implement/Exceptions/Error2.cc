//# Error2.cc: Base class for all AIPS++ errors (non-templated classes)
//# Copyright (C) 1993,1994,1995,1996
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
//#
//# $Id$

#include <aips/Exceptions/Error.h>
#include <iostream.h>

rtti_imp_init(AipsError);
rtti_imp_mbrf(AipsError);

AipsError::AipsError(const Char *str) : message(str)
{
    // Nothing
}

AipsError::AipsError(const String &str) : message(str)
{
    // Nothing
}

AipsError::AipsError(ExcpError *excp) : ExcpError(excp)
{
    AipsError *tmp;
    PCAST(tmp,AipsError,excp);
    if (tmp) {
        _equal = True;
        message = tmp->message;
    } else {
        _equal = False;
    }
}

AipsError::~AipsError()
    {}


//# Much the same as the class above. This class adds no other exception
//# fragile member variables.
rtti_imp_init(AllocError);
rtti_imp_mbrf(AllocError);

AllocError::AllocError(ExcpError *excp) : AipsError(excp)
{
    AllocError *tmp;
    PCAST(tmp,AllocError,excp);
    if (tmp) {
        Size = (*tmp).Size;
        _equal = True;
    } else {
        _equal = False;
        Size = 0;
    }
}

AllocError::~AllocError()
    {}


//#  This is a relatively uninteresting class, except for the fact that
//#  it serves as the parent of all IndexErrors.
rtti_imp_init(IndexError);
rtti_imp_mbrf(IndexError);

IndexError::IndexError(ExcpError *excp) : AipsError(excp)
{
    IndexError *tmp;
    PCAST(tmp,IndexError,excp);
    if (tmp)
        _equal = True;
    else
        _equal = False;
}

IndexError::~IndexError()
    {}



//#  This is a relatively uninteresting class, except for the fact that
//#  it serves as the parent of all DuplError.
rtti_imp_init(DuplError);
rtti_imp_mbrf(DuplError);

DuplError::DuplError(ExcpError *excp) : AipsError(excp)
{
    DuplError *tmp;
    PCAST(tmp,DuplError,excp);
    if (tmp)
        _equal = True;
    else
        _equal = False;
}

DuplError::~DuplError()
    {}


// Exception which causes an abort instead of continuing
AbortError::AbortError(const Char *str) : AipsError(str)
{
    cerr << "An unrevoverable error occurred: " << endl;
    cerr << str << endl;
    exit(1);
}

AbortError::AbortError(const String &str) : AipsError(str)
{
    cerr << "An unrecoverable error occurred: " << endl;
    cerr << str << endl;
    exit(1);
}

AbortError::~AbortError()
    {}
