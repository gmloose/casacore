//# ByteSource.h: Class for read-only access to data in a given format
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

#if !defined(AIPS_BYTESOURCE_H)
#define AIPS_BYTESOURCE_H

#if defined (_AIX)
#pragma implementation ("ByteSource.cc")
#endif

//# Includes
#include <aips/aips.h>
#include <aips/IO/TypeIO.h>
#include <aips/IO/BaseSinkSource.h>


// <summary> 
// Class for read-only access to data in a given format.
// </summary>

// <use visibility=export>

// <reviewed reviewer="Friso Olnon" date="1996/11/06" tests="tByteSink" demos="">
// </reviewed>

// <prerequisite> 
//    <li> <linkto class=BaseSinkSource>BaseSinkSource</linkto> class
//    <li> <linkto class=TypeIO>TypeIO</linkto> class and derived classes
// </prerequisite> 

// <etymology> 
// A source is the place where bytes are read from.
// </etymology>

// <synopsis> 
// ByteSource provides read-only access to a typed byte stream in the
// AIPS++ IO framework. The base class <src>BaseSinkSource</src>
// contains common functions like <src>seek</src>.
// <p>
// The object is constructed using a typed byte stream. This stream
// is an instance of a class derived from class
// <linkto class=TypeIO>TypeIO</linkto>. This makes it possible to
// read the data in any format (e.g. CanonicalIO or RawIO).
// <br> In its turn TypeIO uses an instance of a class derived from class
// <linkto class=ByteIO>ByteIO</linkto>. This makes it possible to
// use any input stream (e.g. file, memory).
// </synopsis>

// <example>
// <srcblock>
//    // Construct the correct input stream.
//    RegularFileIO filio ("file.name");
//    CanonicalIO canio (&filio);
//    ByteSource source (&canio);
//    // Read data.
//    Int vali;
//    Bool flag;
//    source >> vali >> flag;
// </srcblock>
// </example>

// <motivation> 
// This class makes it possible to deny write-access to an IO stream.
// </motivation>


class ByteSource: virtual public BaseSinkSource
{
public: 
    // Default constructor.
    // This creates an invalid object, but is present for convenience.
    ByteSource();

    // Construct from given TypeIO object.
    // The constructor does not copy the object,
    // but only keeps a pointer to it.
    ByteSource (TypeIO* typeIO);

    // Copy constructor, copy semantics
    ByteSource (const ByteSource& source);

    // Assignment (copy semantics).
    ByteSource& operator= (const ByteSource& source);

    // destructor
    ~ByteSource();
  
    // These functions read one value of the given type.
    // If this function does not succeed, an exception will be thrown.
    // <group>
    ByteSource& operator>> (Bool& value);
    ByteSource& operator>> (Char& value);
    ByteSource& operator>> (uChar& value);
    ByteSource& operator>> (Short& value);
    ByteSource& operator>> (uShort& value);
    ByteSource& operator>> (Int& value);
    ByteSource& operator>> (uInt& value);
    ByteSource& operator>> (Long& value);
    ByteSource& operator>> (uLong& value);
    ByteSource& operator>> (Float& value);
    ByteSource& operator>> (Double& value);
    ByteSource& operator>> (Complex& value);
    ByteSource& operator>> (DComplex& value);
    ByteSource& operator>> (String& value);
    // </group>

    // These functions read multiple values of the given type.
    // If this function does not succeed, an exception will be thrown.
    // <group>
    void read (uInt nvalues, Bool* value);
    void read (uInt nvalues, Char* value);
    void read (uInt nvalues, uChar* value);
    void read (uInt nvalues, Short* value);
    void read (uInt nvalues, uShort* value);
    void read (uInt nvalues, Int* value);
    void read (uInt nvalues, uInt* value);
    void read (uInt nvalues, Long* value);
    void read (uInt nvalues, uLong* value);
    void read (uInt nvalues, Float* value);
    void read (uInt nvalues, Double* value);
    void read (uInt nvalues, Complex* value);
    void read (uInt nvalues, DComplex* value);
    void read (uInt nvalues, String* value);
    // </group>

protected:
};


#endif
