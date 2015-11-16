/**
Software License Agreement (BSD)

\file      measurement_report_header.h
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

#ifndef OMRON_OS32C_DRIVER_MEASUREMENT_REPORT_HEADER_H
#define OMRON_OS32C_DRIVER_MEASUREMENT_REPORT_HEADER_H

#include <string>

#include "ovda_ethernetip/eip_types.h"
#include "ovda_ethernetip/serialization/reader.h"
#include "ovda_ethernetip/serialization/writer.h"
#include "ovda_ethernetip/serialization/serializable.h"

using std::string;
using eip::serialization::Serializable;
using eip::serialization::Reader;
using eip::serialization::Writer;

namespace omron_os32c_driver {

/**
 * Data structure and operators for OS32C specific Measurement Report Header
 * as defined in the OS32C-DM Ethernet/IP Addendum
 */
class MeasurementReportHeader : public Serializable
{
public:
  EIP_UDINT scan_count;
  EIP_UDINT scan_rate;
  EIP_UDINT scan_timestamp;
  EIP_UDINT scan_beam_period;
  EIP_UINT machine_state;
  EIP_UINT machine_stop_reasons;
  EIP_UINT active_zone_set;
  EIP_WORD zone_inputs;
  EIP_WORD detection_zone_status;
  EIP_WORD output_status;
  EIP_WORD input_status;
  EIP_UINT display_status;
  EIP_UINT non_safety_config_checksum;
  EIP_UINT safety_config_checksum;
  EIP_UINT range_report_format;
  EIP_UINT refletivity_report_format;
  EIP_UINT num_beams;

  /**
   * From OS32C-DM Ethernet/IP addendum, header is always 56 bytes
   */
  virtual size_t getLength() const
  {
    return 56;
  }

  /**
   * Serialize data into the given buffer
   * @param writer Writer to use for serialization
   * @return the writer again
   * @throw std::length_error if the buffer is too small for the header data
   */
  virtual Writer& serialize(Writer& writer) const
  {
    EIP_UINT reserved = 0;
    writer.write(scan_count);
    writer.write(scan_rate);
    writer.write(scan_timestamp);
    writer.write(scan_beam_period);
    writer.write(machine_state);
    writer.write(machine_stop_reasons);
    writer.write(active_zone_set);
    writer.write(zone_inputs);
    writer.write(detection_zone_status);
    writer.write(output_status);
    writer.write(input_status);
    writer.write(display_status);
    writer.write(non_safety_config_checksum);
    writer.write(safety_config_checksum);
    writer.write(reserved);
    writer.write(reserved);
    writer.write(reserved);
    writer.write(reserved);
    writer.write(reserved);
    writer.write(reserved);
    writer.write(range_report_format);
    writer.write(refletivity_report_format);
    writer.write(reserved);
    writer.write(num_beams);
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
    reader.read(scan_count);
    reader.read(scan_rate);
    reader.read(scan_timestamp);
    reader.read(scan_beam_period);
    reader.read(machine_state);
    reader.read(machine_stop_reasons);
    reader.read(active_zone_set);
    reader.read(zone_inputs);
    reader.read(detection_zone_status);
    reader.read(output_status);
    reader.read(input_status);
    reader.read(display_status);
    reader.read(non_safety_config_checksum);
    reader.read(safety_config_checksum);
    reader.skip(6*sizeof(EIP_UINT));
    reader.read(range_report_format);
    reader.read(refletivity_report_format);
    reader.skip(sizeof(EIP_UINT));
    reader.read(num_beams);
    return reader;
  }
};

} // namespace omron_os32c_driver

#endif  // OMRON_OS32C_DRIVER_MEASUREMENT_REPORT_HEADER_H
