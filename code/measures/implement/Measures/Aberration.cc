//# Aberration.cc:  Aberration class
//# Copyright (C) 1995, 1996
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
#ifdef __GNUG__
#include <aips/Measures/Quantum.h>
typedef Quantum<Double> gpp_aberration_bug1;
#endif
#include <aips/Measures/Aberration.h>
#include <aips/Mathematics/Constants.h>
#include <aips/Arrays/ArrayMath.h>
#include <aips/Functionals/Polynomial.h>
#include <aips/Measures/MeasData.h>

//# Constants
const Double Aberration::INTV = 0.04;

//# Constructors
Aberration::Aberration() : method(Aberration::STANDARD), lres(0) {
    fill();
}

Aberration::Aberration(const Aberration &other) {
    copy(other);
}

Aberration::Aberration(AberrationTypes type) :
method(type), lres(0) {
    fill();
}

Aberration &Aberration::operator=(const Aberration &other) {
    if (this != &other) {
	copy(other);
    }
    return *this;
}


void Aberration::init() {
    method = Aberration::STANDARD;
    fill();
}

void Aberration::init(AberrationTypes type) {
    method = type;
    fill();
}

void Aberration::copy(const Aberration &other) {
    method = other.method;
    checkEpoch = other.checkEpoch;
    for (Int i=0; i<3; i++) {
	aval[i] = other.aval[i];
	dval[i] = other.dval[i];
    };
    for (Int j=0; j<4; j++) {
	result[j] = other.result[j];
    };
}

//# Destructor
Aberration::~Aberration() {}

//# Operators
// Calculate Aberration 
const MVPosition &Aberration::operator()(Double epoch) {
    calcAber(epoch);
    Double dt = epoch - checkEpoch;
    lres++; lres %= 4;
    for (Int i=0; i<3; i++) {
	result[lres](i) = aval[i] + dt*dval[i];
    };
    return result[lres];
}

//# Member functions

const MVPosition &Aberration::derivative(Double epoch) {
    calcAber(epoch);
    lres++; lres %= 4;
    for (Int i=0; i<3; i++) {
	result[lres](i) = dval[i];
    };
    return result[lres];
}

void Aberration::fill() {
    checkEpoch = 1e30;
}

void Aberration::refresh() {
    checkEpoch = 1e30;
}

void Aberration::calcAber(Double t) {
    Double intv;
    if (!nearAbs(t,checkEpoch,
		 (MeasDetail::get(Aberration::D_Interval,intv) ? 
		  intv : Aberration::INTV))) {
	checkEpoch = t;
	switch (method) {
	    case B1950:
	    t = (t - MeasData::MJDB1900)/MeasData::JDCEN;
	    break;
	    default:
	    t = (t - MeasData::MJD2000)/MeasData::JDCEN;
	    break;
	};
	Int i,j;
	Vector<Double> fa(13), dfa(13);
	for (i=0; i<3; i++) {
	    aval[i] = dval[i] = Double(0);
	};
	Double dtmp, ddtmp;
	switch (method) {
	    case B1950:
	    for (i=0; i<12; i++) {
		fa(i) = MeasData::aber1950Arg(i)(t);
		dfa(i) = (MeasData::aber1950Arg(i).derivative())(t);
	    };
	    for (i=0; i<132; i++) {
		dtmp = ddtmp = 0; 
		for (j=0; j<12; j++) {
		    dtmp += MeasData::mulAber1950Arg(i)(j) * fa(j);
		    ddtmp += MeasData::mulAber1950Arg(i)(j) * dfa(j);
		};
		aval[0] += MeasData::mulAber1950(i,t)(0) * sin(dtmp) +
		    MeasData::mulAber1950(i,t)(1) * cos(dtmp);
		aval[1] += MeasData::mulAber1950(i,t)(2) * sin(dtmp) +
		    MeasData::mulAber1950(i,t)(3) * cos(dtmp);
		aval[2] += MeasData::mulAber1950(i,t)(4) * sin(dtmp) +
		    MeasData::mulAber1950(i,t)(5) * cos(dtmp);
		dval[0] += MeasData::mulAber1950(i,t)(6) * sin(dtmp) +
		    MeasData::mulAber1950(i,t)(7) * cos(dtmp) +
			MeasData::mulAber1950(i,t)(0) * cos(dtmp) * ddtmp -
			    MeasData::mulAber1950(i,t)(1) * sin(dtmp) * ddtmp;
		dval[1] += MeasData::mulAber1950(i,t)(8) * sin(dtmp) +
		    MeasData::mulAber1950(i,t)(9) * cos(dtmp) +
			MeasData::mulAber1950(i,t)(2) * cos(dtmp) * ddtmp -
			    MeasData::mulAber1950(i,t)(3) * sin(dtmp) * ddtmp;
		dval[2] += MeasData::mulAber1950(i,t)(10) * sin(dtmp) +
		    MeasData::mulAber1950(i,t)(11) * cos(dtmp) +
			MeasData::mulAber1950(i,t)(4) * cos(dtmp) * ddtmp -
			    MeasData::mulAber1950(i,t)(5) * sin(dtmp) * ddtmp;
	    };
	    break;

	    default:
	    for (i=0; i<13; i++) {
		fa(i) = MeasData::aberArg(i)(t);
		dfa(i) = (MeasData::aberArg(i).derivative())(t);
	    };
	    for (i=0; i<80; i++) {
		dtmp = ddtmp = 0; 
		for (j=0; j<6; j++) {
		    dtmp += MeasData::mulAberArg(i)(j) * fa(j);
		    ddtmp += MeasData::mulAberArg(i)(j) * dfa(j);
		};
		aval[0] += MeasData::mulAber(i,t)(0) * sin(dtmp) +
		    MeasData::mulAber(i,t)(1) * cos(dtmp);
		aval[1] += MeasData::mulAber(i,t)(2) * sin(dtmp) +
		    MeasData::mulAber(i,t)(3) * cos(dtmp);
		aval[2] += MeasData::mulAber(i,t)(4) * sin(dtmp) +
		    MeasData::mulAber(i,t)(5) * cos(dtmp);
		dval[0] += MeasData::mulAber(i,t)(6) * sin(dtmp) +
		    MeasData::mulAber(i,t)(7) * cos(dtmp) +
			MeasData::mulAber(i,t)(0) * cos(dtmp) * ddtmp -
			    MeasData::mulAber(i,t)(1) * sin(dtmp) * ddtmp;
		dval[1] += MeasData::mulAber(i,t)(8) * sin(dtmp) +
		    MeasData::mulAber(i,t)(9) * cos(dtmp) +
			MeasData::mulAber(i,t)(2) * cos(dtmp) * ddtmp -
			    MeasData::mulAber(i,t)(3) * sin(dtmp) * ddtmp;
		dval[2] += MeasData::mulAber(i,t)(10) * sin(dtmp) +
		    MeasData::mulAber(i,t)(11) * cos(dtmp) +
			MeasData::mulAber(i,t)(4) * cos(dtmp) * ddtmp -
			    MeasData::mulAber(i,t)(5) * sin(dtmp) * ddtmp;
	    };
	    for (i=0; i<17; i++) {
		dtmp = ddtmp = 0;
		for (j=0; j<7; j++) {
		    dtmp += MeasData::mulAberSunArg(i)(j) * fa(j+1);
		    ddtmp += MeasData::mulAberSunArg(i)(j) * dfa(j+1);
		};
		aval[0] += MeasData::mulSunAber(i)(0) * sin(dtmp) +
		    MeasData::mulSunAber(i)(1) * cos(dtmp);
		aval[1] += MeasData::mulSunAber(i)(2) * sin(dtmp) +
		    MeasData::mulSunAber(i)(3) * cos(dtmp);
		aval[2] += MeasData::mulSunAber(i)(4) * sin(dtmp) +
		    MeasData::mulSunAber(i)(5) * cos(dtmp);
		dval[0] += MeasData::mulSunAber(i)(0) * cos(dtmp) * ddtmp -
		    MeasData::mulSunAber(i)(1) * sin(dtmp) * ddtmp;
		dval[1] += MeasData::mulSunAber(i)(2) * cos(dtmp) * ddtmp -
		    MeasData::mulSunAber(i)(3) * sin(dtmp) * ddtmp;
		dval[2] += MeasData::mulSunAber(i)(4) * cos(dtmp) * ddtmp -
		    MeasData::mulSunAber(i)(5) * sin(dtmp) * ddtmp;
	    };
	    for (i=0; i<17; i++) {
		dtmp = ddtmp = 0;
		for (j=0; j<5; j++) {
		    dtmp += MeasData::mulAberEarthArg(i)(j) * fa(j+8);
		    ddtmp += MeasData::mulAberEarthArg(i)(j) * dfa(j+8);
		};
		aval[0] += MeasData::mulEarthAber(i)(0) * sin(dtmp);
		aval[1] += MeasData::mulEarthAber(i)(1) * cos(dtmp);
		aval[2] += MeasData::mulEarthAber(i)(2) * cos(dtmp);
		dval[0] += MeasData::mulEarthAber(i)(0) * cos(dtmp) * ddtmp;
		dval[1] += -MeasData::mulEarthAber(i)(1) * sin(dtmp) * ddtmp;
		dval[2] += -MeasData::mulEarthAber(i)(2) * sin(dtmp) * ddtmp;
	    };
	    break;
	};
	for (i=0; i<3; i++) {
	    aval[i] /= C::c;
	    dval[i] /= (C::c * MeasData::JDCEN);
	};
    };
}
