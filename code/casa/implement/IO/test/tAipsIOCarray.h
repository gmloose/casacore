//# tAipsIOCarray.h: This program tests the AipsIOCarray functions
//# Copyright (C) 1996
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This program is free software; you can redistribute it and/or modify it
//# under the terms of the GNU General Public License as published by the Free
//# Software Foundation; either version 2 of the License, or (at your option)
//# any later version.
//#
//# This program is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//# more details.
//#
//# You should have received a copy of the GNU General Public License along
//# with this program; if not, write to the Free Software Foundation, Inc.,
//# 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

#if !defined(AIPS_TAIPSIOCARRAY_H)
#define AIPS_TAIPSIOCARRAY_H

//# Includes
#include <aips/IO/AipsIOCarray.h>


// This file defines an example class used in tAipsIOCarray.cc


//# Make a class AipsIOCarrayEx1 to construct an array of non-standard objects.
class AipsIOCarrayEx1 
{
public:
    AipsIOCarrayEx1() : a_p(0), b_p(0) {;}
    AipsIOCarrayEx1 (Int a, double b) : a_p(a), b_p(b) {;}
    friend AipsIO& operator<< (AipsIO& ios, const AipsIOCarrayEx1& a)
	{ return ios << a.a_p << a.b_p; }
    friend AipsIO& operator>> (AipsIO& ios, AipsIOCarrayEx1& a)
	{ return ios >> a.a_p >> a.b_p; }
    Int a() const {return a_p;}
    double b() const {return b_p;}
private:
    Int a_p;
    double b_p;
};


#endif
