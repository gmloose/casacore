//# MSFreqOffsetColumns.cc:  provides easy access to MeasurementSet columns
//# Copyright (C) 1999,2000
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

#include <casacore/ms/MeasurementSets/MSFreqOffColumns.h>
#include <casacore/ms/MeasurementSets/MSFreqOffset.h>

namespace casacore { //# NAMESPACE CASACORE - BEGIN

MSFreqOffsetColumns::MSFreqOffsetColumns():
  isNull_p(True)
{
}

MSFreqOffsetColumns::MSFreqOffsetColumns(const MSFreqOffset& msFreqOffset):
  isNull_p(True)
{
  attach(msFreqOffset);
}

MSFreqOffsetColumns::~MSFreqOffsetColumns() {}

void MSFreqOffsetColumns::attach(const MSFreqOffset& msFreqOffset) 
{
  isNull_p = msFreqOffset.isNull();
  if (!isNull()) {
    antenna1_p.attach(msFreqOffset, MSFreqOffset::
		      columnName(MSFreqOffset::ANTENNA1));
    antenna2_p.attach(msFreqOffset, MSFreqOffset::
		      columnName(MSFreqOffset::ANTENNA2));
    feedId_p.attach(msFreqOffset, MSFreqOffset::
		    columnName(MSFreqOffset::FEED_ID));
    interval_p.attach(msFreqOffset, MSFreqOffset::
		      columnName(MSFreqOffset::INTERVAL));
    offset_p.attach(msFreqOffset, MSFreqOffset::
		    columnName(MSFreqOffset::OFFSET));
    spectralWindowId_p.attach(msFreqOffset, MSFreqOffset::
			      columnName(MSFreqOffset::SPECTRAL_WINDOW_ID));
    time_p.attach(msFreqOffset, MSFreqOffset::
		  columnName(MSFreqOffset::TIME));
    timeMeas_p.attach(msFreqOffset, MSFreqOffset::
		      columnName(MSFreqOffset::TIME));
    intervalQuant_p.attach(msFreqOffset, MSFreqOffset::
			   columnName(MSFreqOffset::INTERVAL));
    offsetQuant_p.attach(msFreqOffset, MSFreqOffset::
			 columnName(MSFreqOffset::OFFSET));
    timeQuant_p.attach(msFreqOffset, MSFreqOffset::
		       columnName(MSFreqOffset::TIME));
  }
}

void MSFreqOffsetColumns::
setEpochRef(MEpoch::Types ref, Bool tableMustBeEmpty) {
  timeMeas_p.setDescRefCode(ref, tableMustBeEmpty);
}

} //# NAMESPACE CASACORE - END

