//# tConvertArray.cc: This program tests the convertArray functions
//# Copyright (C) 2009
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

//# Includes
#include "../Array.h"
#include "../ArrayMath.h"
#include "../ArrayLogical.h"

#include <boost/test/unit_test.hpp>

using namespace casacore;

BOOST_AUTO_TEST_SUITE(axis_specifier)

template<typename T, typename F>
void tConvertEQ (const IPosition& shape)
{
  Array<F> arr(shape);
  Array<T> res(shape);
  Array<T> exp(shape);
  indgen (arr, F(0), F(1));
  indgen (exp, T(0), T(1));
  convertArray (res, arr);
  BOOST_CHECK (allEQ(res, exp));
  // Test on non-contiguous array.
  IPosition st(shape.size(), 1);
  IPosition end(shape-2);
  Array<F> arr1 = arr(st,end);
  Array<T> exp1 = exp(st,end);
  Array<T> res1 = res(st,end);
  res1 = 0;
  convertArray (res1, arr1);
  BOOST_CHECK (allEQ(res1, exp1));
  BOOST_CHECK (allEQ(res, exp));
}

template<typename T, typename F>
void tConvertNear (const IPosition& shape)
{
  Array<F> arr(shape);
  Array<T> res(shape);
  Array<T> exp(shape);
  indgen (arr, F(0), F(1));
  indgen (exp, T(0), T(1));
  convertArray (res, arr);
  BOOST_CHECK (allNear(res, exp, 1e-5));
  // Test on non-contiguous array.
  IPosition st(shape.size(), 1);
  IPosition end(shape-2);
  Array<F> arr1 = arr(st,end);
  Array<T> exp1 = exp(st,end);
  Array<T> res1 = res(st,end);
  res1 = 0;
  convertArray (res1, arr1);
  BOOST_CHECK (allNear(res1, exp1, 1e-5));
  BOOST_CHECK (allNear(res, exp, 1e-5));
}

BOOST_AUTO_TEST_CASE( converteq1 )
{
  tConvertEQ<int,short> (IPosition{40,50,6}); // size should fit in Short
}

BOOST_AUTO_TEST_CASE( converteq2 )
{
  tConvertEQ<short,int> (IPosition{40,50,6});
}

BOOST_AUTO_TEST_CASE( convertnear1 )
{
  tConvertNear<float,int> (IPosition{40,50,600});
}

BOOST_AUTO_TEST_CASE( convertnear2 )
{
  tConvertNear<std::complex<float>,float> (IPosition{40,50,600});
}

BOOST_AUTO_TEST_SUITE_END()
