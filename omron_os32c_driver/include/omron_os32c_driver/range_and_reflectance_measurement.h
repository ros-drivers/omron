/**
Software License Agreement (BSD)

\file      range_and_reflectance_measurement.h
\authors   Kareem Shehata <kareem@shehata.ca>
\copyright Copyright (c) 2015, Clearpath Robotics, Inc., All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that
the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the
   following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
   following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Clearpath Robotics nor the names of its contributors may be used to endorse or promote
   products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WAR-
RANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, IN-
DIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef OMRON_OS32C_DRIVER_RANGE_AND_REFLECTANCE_MEASUREMENT_H
#define OMRON_OS32C_DRIVER_RANGE_AND_REFLECTANCE_MEASUREMENT_H

#include <string>
#include <vector>

#include "odva_ethernetip/eip_types.h"
#include "odva_ethernetip/serialization/reader.h"
#include "odva_ethernetip/serialization/writer.h"
#include "odva_ethernetip/serialization/serializable.h"
#include "omron_os32c_driver/measurement_report_header.h"

using std::vector;
using eip::serialization::Serializable;
using eip::serialization::Reader;
using eip::serialization::Writer;

namespace omron_os32c_driver {

/**
 * Data structure and operators for OS32C specific Measurement Report data
 * as defined in the OS32C-DM Ethernet/IP Addendum that includes both
 * range and reflectance data in the same message.
 */
class RangeAndReflectanceMeasurement : public Serializable
{
public:
  MeasurementReportHeader header;
  vector<EIP_UINT> range_data;
  vector<EIP_UINT> reflectance_data;

  /**
   * Size of this message including all measurement data.
   */
  virtual size_t getLength() const
  {
    return header.getLength() + range_data.size() * sizeof(EIP_UINT) + reflectance_data.size() * sizeof(EIP_UINT);
  }

  /**
   * Serialize data into the given buffer
   * @param writer Writer to use for serialization
   * @return the writer again
   * @throw std::length_error if the buffer is too small for the header data
   */
  virtual Writer& serialize(Writer& writer) const
  {
    header.serialize(writer);
    writer.writeBytes(&range_data[0], range_data.size() * sizeof(EIP_UINT));
    writer.writeBytes(&reflectance_data[0], reflectance_data.size() * sizeof(EIP_UINT));
    return writer;
  }

  /**
   * Extra length information is not relevant in this context. Same as deserialize(reader)
   */
  virtual Reader& deserialize(Reader& reader, size_t length)
  {
    deserialize(reader);
    return reader;
  }

  /**
   * Deserialize data from the given reader without length information
   * @param reader Reader to use for deserialization
   * @return the reader again
   * @throw std::length_error if the buffer is overrun while deserializing
   */
  virtual Reader& deserialize(Reader& reader)
  {
    header.deserialize(reader);
    range_data.resize(header.num_beams);
    reflectance_data.resize(header.num_beams);
    reader.readBytes(&range_data[0], range_data.size() * sizeof(EIP_UINT));
    reader.readBytes(&reflectance_data[0], reflectance_data.size() * sizeof(EIP_UINT));
    return reader;
  }
};

}  // namespace omron_os32c_driver

#endif  // OS32C_RANGE_AND_REFLECTANCE_MEASUREMENT_H
