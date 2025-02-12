//# Functors.h: Define STL functors for basic math functions.
//# Copyright (C) 2008
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

#ifndef CASA_FUNCTORS_H
#define CASA_FUNCTORS_H

#include <casacore/casa/aips.h>
#include <casacore/casa/BasicMath/Math.h>
#include <casacore/casa/BasicSL/Complex.h>
#include <casacore/casa/BasicSL/String.h>
#include <functional>

namespace casacore { //# NAMESPACE CASACORE - BEGIN


  // Define a function to do a binary transform in place.
  // It is functionally equivalent to std::transform where the first and result
  // iterator are the same, but it is faster for non-trivial iterators.
  template<typename InputIterator1, typename InputIterator2, typename BinaryOperator>
  inline void transformInPlace (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, BinaryOperator op)
  {
    for (; first1!=last1; ++first1, ++first2) {
      *first1 = op(*first1, *first2);
    }
  }

  // Define a function to do a unary transform in place.
  // It is functionally equivalent to std::transform where the first and result
  // iterator are the same, but it is faster for non-trivial iterators.
  template<typename InputIterator1, typename UnaryOperator>
  inline void transformInPlace (InputIterator1 first1, InputIterator1 last1,
                                UnaryOperator op)
  {
    for (; first1!=last1; ++first1) {
      *first1 = op(*first1);
    }
  }

  // Define a function (similar to std::accumulate) to do accumulation of
  // elements for which the corresponding mask value is true.
  // The default accumulation is addition.
  template<typename InputIterator, typename MaskIterator, typename Accum, typename BinaryOperator>
  inline Accum accumulateTrue (InputIterator first, InputIterator last,
                               MaskIterator mask, Accum acc,
                               BinaryOperator op = std::plus<Accum>())
  {
    for (; first!=last; ++first, ++mask) {
      if (*mask) acc = op(acc, *first);
    }
    return acc;
  }

  // Define a function (similar to std::accumulate) to do accumulation of
  // elements for which the corresponding mask value is false.
  // The default accumulation is addition.
  template<typename InputIterator, typename MaskIterator, typename Accum, typename BinaryOperator>
  inline Accum accumulateFalse (InputIterator first, InputIterator last,
                                MaskIterator mask, Accum acc,
                                BinaryOperator op = std::plus<Accum>())
  {
    for (; first!=last; ++first, ++mask) {
      if (!*mask) acc = op(acc, *first);
    }
    return acc;
  }

  // Define a function to compare all elements of two sequences.
  // It returns true if all elements compare true.
  // An example compare operator is <src>std::equal_to</src>.
  // <group>
  template<typename InputIterator1, typename InputIterator2, typename CompareOperator>
  inline bool compareAll (InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, CompareOperator op)
  {
    for (; first1!=last1; ++first1, ++first2) {
      if (!op(*first1, *first2)) return false;
    }
    return true;
  }
  // For use with a constant left value.
  // This avoids use of bind1st or bind2nd which can fail for gcc-4.3.
  // (see ArrayMath.h).
  template<typename InputIterator1, typename T, typename CompareOperator>
  inline bool compareAllLeft (InputIterator1 first1, InputIterator1 last1,
                              T left, CompareOperator op)
  {
    for (; first1!=last1; ++first1) {
      if (!op(left, *first1)) return false;
    }
    return true;
  }
  // For use with a constant right value.
  // This avoids use of bind1st or bind2nd which can fail for gcc-4.3.
  // (see ArrayMath.h).
  template<typename InputIterator1, typename T, typename CompareOperator>
  inline bool compareAllRight (InputIterator1 first1, InputIterator1 last1,
                               T right, CompareOperator op)
  {
    for (; first1!=last1; ++first1) {
      if (!op(*first1, right)) return false;
    }
    return true;
  }
  // </group>

  // Define a function to compare all elements of two sequences.
  // It returns true if any element compares true.
  // An example compare operator is <src>std::equal_to</src>.
  // <group>
  template<typename InputIterator1, typename InputIterator2, typename CompareOperator>
  inline bool compareAny (InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, CompareOperator op)
  {
    for (; first1!=last1; ++first1, ++first2) {
      if (op(*first1, *first2)) return true;
    }
    return false;
  }
  // For use with a constant left value.
  // This avoids use of bind1st or bind2nd which can fail for gcc-4.3.
  // (see ArrayMath.h).
  template<typename InputIterator1, typename T, typename CompareOperator>
  inline bool compareAnyLeft (InputIterator1 first1, InputIterator1 last1,
                              T left, CompareOperator op)
  {
    for (; first1!=last1; ++first1) {
      if (op(left, *first1)) return true;
    }
    return false;
  }
  // For use with a constant right value.
  // This avoids use of bind1st or bind2nd which can fail for gcc-4.3.
  // (see ArrayMath.h).
  template<typename InputIterator1, typename T, typename CompareOperator>
  inline bool compareAnyRight (InputIterator1 first1, InputIterator1 last1,
                               T right, CompareOperator op)
  {
    for (; first1!=last1; ++first1) {
      if (op(*first1, right)) return true;
    }
    return false;
  }
  // </group>



  // Functor to add variables of possibly different types.
  // This is unlike std::plus which requires equal types.
  template <typename L, typename R=L, typename RES=L>
  struct Plus
  {
    RES operator() (const L& x, const R& y) const
      { return RES(x)+y; }
  };

  // Functor to subtract variables of possibly different types.
  // This is unlike std::minus which requires equal types.
  template <typename L, typename R=L, typename RES=L>
  struct Minus
  {
    RES operator() (const L& x, const R& y) const
      { return RES(x)-y; }
  };

  // Functor to multiply variables of possibly different types.
  // This is unlike std::multiplies which requires equal types.
  template <typename L, typename R=L, typename RES=L>
  struct Multiplies
  {
    RES operator() (const L& x, const R& y) const
      { return RES(x)*y; }
  };

  // Functor to divide variables of possibly different types.
  // This is unlike std::divides which requires equal types.
  template <typename L, typename R=L, typename RES=L>
  struct Divides
  {
    RES operator() (const L& x, const R& y) const
      { return RES(x)/y; }
  };

  // Functor to take modulo of (integer) variables of possibly different types
  // in the C way.
  // This is unlike std::modulo which requires equal types.
  template <typename L, typename R=L, typename RES=L>
  struct Modulo
  {
    RES operator() (const L& x, const R& y) const
      { return RES(x)%y; }
  };

  // Functor to take modulo of variables of possibly different types
  // using the floor modulo (% as used in Python).
  template <typename L, typename R=L, typename RES=L>
  struct FloorMod
  {
    RES operator() (const L& x, const R& y) const
    { return floormod (RES(x), RES(y)); }
  };

  // Functor for bitwise and of (integer) values.
  template <typename T>
  struct BitAnd
  {
    T operator() (const T& x, const T& y) const
      { return x&y; }
  };

  // Functor for bitwise or of (integer) values.
  template <typename T>
  struct BitOr
  {
    T operator() (const T& x, const T& y) const
      { return x|y; }
  };

  // Functor for bitwise xor of (integer) values.
  template <typename T>
  struct BitXor
  {
    T operator() (const T& x, const T& y) const
      { return x^y; }
  };

  // Functor for bitwise negate of (integer) values.
  template <typename T>
  struct BitNegate
  {
    T operator() (const T& x) const
      { return ~x; }
  };

  // Functor to test for NaN.
  // It can be used in something like:
  // <srcblock>
  //   std::transform (array.begin(), array.end(),
  //                   result.begin(), IsNaN<T>());
  // </srcblock>
  template<typename T>
  struct IsNaN
  {
    bool operator() (T value) const
      { return isNaN (value); }
  };

  // Functor to test for infinity.
  template<typename T>
  struct IsInf
  {
    bool operator() (T value) const
      { return isInf (value); }
  };

  // Functor to test for finiteness.
  template<typename T>
  struct IsFinite
  {
    bool operator() (T value) const
      { return isFinite (value); }
  };

  // Functor to test if two values are relatively near each other.
  // It can be used in something like:
  // <srcblock>
  //   std::transform (left.begin(), left.cend(), right.begin(),
  //                   result.cbegin(), Near<T>(tolerance));
  // </srcblock>
  template<typename L, typename R=L>
  struct Near
  {
    explicit Near (double tolerance=1e-5)
      : itsTolerance (tolerance)
    {}
    bool operator() (L left, R right) const
      { return near (left, L(right), itsTolerance); }
  private:
    double itsTolerance;
  };

  // Functor to test for if two values are absolutely near each other.
  template<typename L, typename R=L>
  struct NearAbs
  {
    explicit NearAbs (double tolerance=1e-13)
      : itsTolerance (tolerance)
    {}
    bool operator() (L left, R right) const
      { return nearAbs (left, L(right), itsTolerance); }
  private:
    double itsTolerance;
  };


  // Functor to apply sin.
  template<typename T, typename RES=T>
  struct Sin
  {
    RES operator() (T value) const
      { return RES(sin (value)); }
  };

  // Functor to apply sinh.
  template<typename T, typename RES=T>
  struct Sinh
  {
    RES operator() (T value) const
      { return RES(sinh (value)); }
  };

  // Functor to apply asin.
  template<typename T, typename RES=T>
  struct Asin
  {
    RES operator() (T value) const
      { return RES(asin (value)); }
  };

  // Functor to apply cos.
  template<typename T, typename RES=T>
  struct Cos
  {
    RES operator() (T value) const
      { return RES(cos (value)); }
  };

  // Functor to apply cosh.
  template<typename T, typename RES=T>
  struct Cosh
  {
    RES operator() (T value) const
      { return RES(cosh (value)); }
  };

  // Functor to apply acos.
  template<typename T, typename RES=T>
  struct Acos
  {
    RES operator() (T value) const
      { return RES(acos (value)); }
  };

  // Functor to apply tan.
  template<typename T, typename RES=T>
  struct Tan
  {
    RES operator() (T value) const
      { return RES(tan (value)); }
  };

  // Functor to apply tanh.
  template<typename T, typename RES=T>
  struct Tanh
  {
    RES operator() (T value) const
      { return RES(tanh (value)); }
  };

  // Functor to apply atan.
  template<typename T, typename RES=T>
  struct Atan
  {
    RES operator() (T value) const
      { return RES(atan (value)); }
  };

  // Functor to apply atan2.
  template<typename L, typename R=L, typename RES=L>
  struct Atan2
  {
    RES operator() (L left, R right) const
      { return RES(atan2 (left, L(right))); }
  };

  // Functor to apply sqr (power of 2).
  template<typename T, typename RES=T>
  struct Sqr
  {
    RES operator() (T value) const
      { return RES(value*value); }
  };

  // Functor to apply a power of 3.
  template<typename T, typename RES=T>
  struct Pow3
  {
    RES operator() (T value) const
      { return RES(value*value*value); }
  };

  // Functor to apply sqrt.
  template<typename T, typename RES=T>
  struct Sqrt
  {
    RES operator() (T value) const
      { return RES(sqrt (value)); }
  };

  // Functor to apply exp.
  template<typename T, typename RES=T>
  struct Exp
  {
    RES operator() (T value) const
      { return RES(exp (value)); }
  };

  // Functor to apply log.
  template<typename T, typename RES=T>
  struct Log
  {
    RES operator() (T value) const
      { return RES(log (value)); }
  };

  // Functor to apply log10.
  template<typename T, typename RES=T>
  struct Log10
  {
    RES operator() (T value) const
      { return RES(log10 (value)); }
  };

  // Functor to apply abs.
  template<typename T, typename RES=T>
  struct Abs
  {
    RES operator() (T value) const
      { return RES(abs (value)); }
  };

  // Functor to apply floor.
  template<typename T, typename RES=T>
  struct Floor
  {
    RES operator() (T value) const
      { return RES(floor (value)); }
  };

  // Functor to apply ceil.
  template<typename T, typename RES=T>
  struct Ceil
  {
    RES operator() (T value) const
      { return RES(ceil (value)); }
  };

  // Functor to apply round (e.g. -3.7 gets -4).
  template<typename T, typename RES=T>
  struct Round
  {
    RES operator() (T value) const
      { return RES(value<0 ? ceil(value-0.5) : floor(value+0.5)); }
  };

  // Functor to apply sign (result is -1, 0, or 1).
  template<typename T, typename RES=T>
  struct Sign
  {
    RES operator() (T value) const
      { return (value<0 ? -1 : (value>0 ? 1:0)); }
  };

  // Functor to form a complex number from the left and right value.
  template<typename L, typename R, typename RES>
  struct MakeComplex
  {
    RES operator() (L l, R r) const
      { return RES(l, r); }
  };

  // Functor to form a complex number from the real part of the
  // left value and the right value.
  template<typename L, typename R, typename RES>
  struct MakeComplexReal
  {
    RES operator() (L l, R r) const
      { return RES(real(l), r); }
  };

  // Functor to form a complex number from the left value and the
  // imaginary part of the right value.
  template<typename L, typename R, typename RES>
  struct MakeComplexImag
  {
    RES operator() (L l, R r) const
      { return RES(l, imag(r)); }
  };

  // Functor to form a complex number from the real part of the
  // left value and the imaginary part of the right value.
  template<typename L, typename R, typename RES>
  struct MakeComplexRealImag
  {
    RES operator() (L l, R r) const
      { return RES(real(l), imag(r)); }
  };

  // Functor to apply complex function conj.
  template<typename T, typename RES=T>
  struct Conj
  {
    RES operator() (T value) const
      { return RES(conj (value)); }
  };

  // Functor to apply complex function real.
  template<typename T, typename RES>
  struct Real
  {
    RES operator() (T value) const
      { return RES(real (value)); }
  };

  // Functor to apply complex function imag.
  template<typename T, typename RES>
  struct Imag
  {
    RES operator() (T value) const
      { return RES(imag (value)); }
  };

  // Functor to apply complex function arg.
  template<typename T, typename RES>
  struct CArg
  {
    RES operator() (T value) const
      { return RES(arg (value)); }
  };

  // Functor to apply complex function fabs.
  template<typename T, typename RES>
  struct CAbs
  {
    RES operator() (T value) const
      { return RES(fabs (value)); }
  };

  // Functor to apply pow.
  template<typename T, typename E=T, typename RES=T>
  struct Pow
  {
    RES operator() (T left, E exponent) const
      { return RES(pow (left, exponent)); }
  };

  // Functor to apply fmod.
  template<typename L, typename R=L, typename RES=L>
  struct Fmod
  {
    RES operator() (R left, L right) const
      { return RES(fmod (left, L(right))); }
  };

  // Functor to get minimum of two values.
  template<typename L, typename R=L, typename RES=L>
  struct Min
  {
    RES operator() (L left, R right) const
      { return RES(left<right  ?  left : right); }
  };

  // Functor to get maximum of two values.
  template<typename L, typename R=L, typename RES=L>
  struct Max
  {
    RES operator() (L left, R right) const
      { return RES(left<right  ?  right : left); }
  };

  // Functor to add square of right to left.
  template<typename T, typename Accum=T>
  struct SumSqr
  {
    Accum operator() (Accum left, T right) const
      { return left + Accum(right)*Accum(right); }
  };

  // Functor to add squared diff of right and base value to left.
  // It can be used to calculate the variance.
  // Note: it is specialized for complex values to handle real and imag separately.
  template<typename T, typename Accum=T>
  struct SumSqrDiff
  {
    explicit SumSqrDiff(T base) : itsBase(base) {}
    Accum operator() (Accum left, T right) const
      { return left + (right-itsBase)*(right-itsBase); }
  private:
    Accum itsBase;    // store as Accum, so subtraction results in Accum
  };
  // Specialize for complex values.
  // Variance has to be taken for the absolute value of a complex value. thus
  //       sum(abs((a[i] - mean)**2
  // where the sqrt used in abs and the **2 cancel each other, thus can be left out.
  // See also https://en.wikipedia.org/wiki/Complex_random_variable#Variance
  // Note that although the sum is real, a complex value is used to have equal template types.
  template<typename T>
  struct SumSqrDiff<std::complex<T>>
  {
    explicit SumSqrDiff(std::complex<T> base) : itsBase(base) {}
    std::complex<T> operator() (std::complex<T> left, std::complex<T> right) const
    { return left + ((right.real() - itsBase.real()) * (right.real() - itsBase.real()) +
                     (right.imag() - itsBase.imag()) * (right.imag() - itsBase.imag())); }
  private:
    std::complex<T> itsBase;
  };

  // Functor to add absolute diff of right and base value to left.
  // It can be used to calculate the average deviation.
  template<typename T, typename Accum=T>
  struct SumAbsDiff
  {
    explicit SumAbsDiff(T base) : itsBase(base) {}
    Accum operator() (Accum left, T right) const
      { return left + abs((right-itsBase)); }
  private:
    Accum itsBase;    // store as Accum, so subtraction results in Accum
  };

  // Functor to downcase a std::string. The result is a casacore::String.
  struct Downcase
  {
    String operator() (const std::string& value) const
      { return downcase(value); }
  };

  // Functor to upcase a std::string. The result is a casacore::String.
  struct Upcase
  {
    String operator() (const std::string& value) const
      { return upcase(value); }
  };

  // Functor to capitalize a std::string. The result is a casacore::String.
  struct Capitalize
  {
    String operator() (const std::string& value) const
      { return capitalize(value); }
  };

  // Functor to trim a std::string. The result is a casacore::String.
  // Leading and trailing whitespace is removed.
  struct Trim
  {
    String operator() (const std::string& value) const
      { return trim(value); }
  };


} //# NAMESPACE CASACORE - END

#endif
