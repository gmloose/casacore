//# DataType.h: data types (primarily) in the table system
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

#include <aips/Utilities/DataType.h>

#include <iostream.h>

ostream &operator<<(ostream &os, DataType type)
{
    switch (type) {
    case TpBool: os << "Bool"; break;
    case TpChar: os << "Char"; break;
    case TpUChar: os << "uChar"; break;
    case TpShort: os << "Short"; break;
    case TpUShort: os << "uShort"; break;
    case TpInt: os << "Int"; break;
    case TpUInt: os << "uInt"; break;
    case TpFloat: os << "float"; break;
    case TpDouble: os << "double"; break;
    case TpComplex: os << "Complex"; break;
    case TpDComplex: os << "DComplex"; break;
    case TpString: os << "String"; break;
    case TpTable: os << "Table"; break;
    case TpArrayBool: os << "Array<Bool>"; break;
    case TpArrayChar: os << "Array<Char>"; break;
    case TpArrayUChar: os << "Array<uChar>"; break;
    case TpArrayShort: os << "Array<Short>"; break;
    case TpArrayUShort: os << "Array<uShort>"; break;
    case TpArrayInt: os << "Array<Int>"; break;
    case TpArrayUInt: os << "Array<uInt>"; break;
    case TpArrayFloat: os << "Array<float>"; break;
    case TpArrayDouble: os << "Array<double>"; break;
    case TpArrayComplex: os << "Array<Complex>"; break;
    case TpArrayDComplex: os << "Array<DComplex>"; break;
    case TpArrayString: os << "Array<String>"; break;
    case TpRecord: os << "Record"; break;
    case TpOther: os << "Other"; break;
    default:
	os << "unknown (cannot happen)'";
    }
    return os;
}

Bool isScalar(DataType type)
{
    return ToBool(type <= TpString);
}

Bool isArray(DataType type)
{
    return ToBool(type >= TpArrayBool && type <= TpArrayString);
}
