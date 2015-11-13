/**
Software License Agreement (proprietary)

\file      identity_item_data_test.cpp
\authors   Kareem Shehata <kshehata@clearpathrobotics.com>
\copyright Copyright (c) 2015, Clearpath Robotics, Inc., All rights reserved.

Redistribution and use in source and binary forms, with or without modification, is not permitted without the
express permission of Clearpath Robotics.
*/

#include <gtest/gtest.h>
#include <boost/asio.hpp>

#include "eip/identity_item_data.h"
#include "eip/serialization/serializable_buffer.h"
#include "eip/serialization/buffer_writer.h"
#include "eip/serialization/buffer_reader.h"

using namespace boost::asio;
using namespace eip;
using namespace eip::serialization;
using namespace boost::asio;

class IdentityItemDataTest : public :: testing :: Test
{

};

TEST_F(IdentityItemDataTest, test_deserialize_serialize)
{
  // This example packet is based on the example given in section 10.1.2.4 of
  // the OS32C-DM Ethernet Protocol document.
  EIP_BYTE d[] = {0x01, 0x00, 0x00, 0x02, 0xAF, 0x12, 0xC0, 0xA8, 0x01, 0x01,
    0, 0, 0, 0, 0, 0, 0, 0, 0xEE, 0xDD, 0x98, 0x76, 0xA5, 0x5A, 0x6B, 0xC7,
    0xE7, 0x81, 0x78, 0x56, 0x34, 0x12, 0x06, 'a', 'b', 'c', 'd', 'e', 'f', 0x7E};

  BufferReader reader(buffer(d));
  IdentityItemData id;
  id.deserialize(reader);
  EXPECT_EQ(0x0001, id.encap_protocol_version);
  EXPECT_EQ(0x0002, id.sockaddr.sin_family);
  EXPECT_EQ(0x12AF, id.sockaddr.sin_port);
  EXPECT_EQ(0x0101A8C0, id.sockaddr.sin_addr.s_addr);
  EXPECT_EQ(0xDDEE, id.vendor_id);
  EXPECT_EQ(0x7698, id.device_type);
  EXPECT_EQ(0x5AA5, id.product_code);
  EXPECT_EQ(0x6B, id.revision[0]);
  EXPECT_EQ(0xC7, id.revision[1]);
  EXPECT_EQ(0x81E7, id.status);
  EXPECT_EQ(0x12345678, id.serial_number);
  EXPECT_STREQ("abcdef", id.product_name.c_str());
  EXPECT_EQ(0x7E, id.state);
  EXPECT_EQ(sizeof(d), id.getLength());

  EIP_BYTE d_out[40];
  BufferWriter writer(buffer(d_out));
  id.serialize(writer);
  for(int byte = 0; byte < sizeof(d); byte++)
  {
    EXPECT_EQ(d[byte], d_out[byte]) << "Byte " << byte << " serialized incorrectly.";
  }
}

