//# MVDouble.cc: to disticguish between internal and external Measure values
//# Copyright (C) 1996
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

//# Includes
#include <aips/Measures/Quantum.h>
#ifdef __GNUG__
typedef Quantum<Double> gpp_mvdouble_bug1;
#endif
#include <aips/Measures/MVDouble.h>
#include <aips/Exceptions/Error.h>
#include <aips/Mathematics/Math.h>

// MVDouble class

//# Constructors
MVDouble::MVDouble(Double d) : 
val(d){}

MVDouble::MVDouble(const MVDouble &other) :
val(other.val) {}

MVDouble::MVDouble(const Quantity &other) {
    val = other.get().getValue();
}

MVDouble::MVDouble(const Quantum<Vector<Double> > &other) {
    Vector<Double> tmp;
    tmp = other.get().getValue();
    uInt i = tmp.nelements();
    if (i == 0) {
	val = 0.0;
    } else if (i == 1) {
	val = tmp(0);
    } else {
	throw (AipsError("Illegal vector length in MVDouble constructor"));
    };
}

MVDouble::MVDouble(const Vector<Double> &other) {
    uInt i = other.nelements();
    if (i == 0) {
	val = 0.0;
    } else if (i == 1) {
	val = other(0);
    } else {
	throw (AipsError("Illegal vector length in MVDouble constructor"));
    };
}

MVDouble::MVDouble(const Vector<Quantity> &other) {
    uInt i = other.nelements();
    if (i == 0) {
	val = 0.0;
    } else if (i == 1) {
	val = (other(0)).get().getValue();
    } else {
	throw (AipsError("Illegal vector length in MVDouble constructor"));
    };
}

MVDouble &MVDouble::operator=(const MVDouble &other) {
    if (this != &other) {
	val = other.val;
    }
    return *this;
}

// Destructor
MVDouble::~MVDouble() {}

// Operators
MVDouble::operator Double() const {
    return val;
}

MVDouble &MVDouble::operator+=(const MVDouble &other) {
    val += other.val;
    return *this;
}

MVDouble &MVDouble::operator-=(const MVDouble &other) {
    val -= other.val;
    return *this;
}

Bool MVDouble::operator==(const MVDouble &other) const {
    return ToBool(val == other.val);
}

Bool MVDouble::operator!=(const MVDouble &other) const {
    return ToBool(val != other.val);
}

Bool MVDouble::near(const MVDouble &other, Double tol) const {
    return ::near(val, other.val, tol);
}

Bool MVDouble::nearAbs(const MVDouble &other, Double tol) const {
    return ::nearAbs(val, other.val, tol);
}

// Member functions
void MVDouble::print(ostream &os) const {
    os << val;
}

MeasValue *MVDouble::clone() const {
    return (new MVDouble(*this));
}
