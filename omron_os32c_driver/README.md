![align=right,width=240](doc/os32c.jpg)

## Overview

This package provides a driver for the OMRON OS32C EtherNet/IP based
safety laser. You can learn more about this device on the
manufacturer's website:

<https://www.ia.omron.com/products/family/2717/>

The primary resource used in developing this driver was the
[OS32C with EtherNet/IP & Measurement Data Addendum](http://downloads.omron.ca/IAB/Products/Safety/Programmable%20safety%20system/Standalone%20safety%20controllers/OS32C/Z336/OS32C-DM_UsersManual_en_201404_Z336-E1-05.pdf).

## Nodes

### omron_os32c_driver

Standalone driver node that publishes the laserscan with diagnostics
information.

#### Published Topics

- `scan`
  ([sensor_msgs/msg/LaserScan](https://docs.ros.org/en/rolling/p/sensor_msgs/msg/LaserScan.html)):
  Scans output from the device at specified frequency.

#### Parameters

- `~host` (`string`, default: `192.168.1.1`): IP address to find device
  at.
- `~local_ip` (`string`, default: `0.0.0.0`): IP adress where the device
  sends its data to. Enables using multiple scanners at the same time
  when specifying different local_ip parameters.
- `~frame_id` (`string`, default: `laser`): The header frame_id of the
  published laser scan message
- `~start_angle` (`double`, default: `OS32C::ANGLE_MAX`): Start angle
- `~end_angle` (`double`, default: `OS32C::ANGLE_MIN`): End angle
- `~frequency` (`double`, default: `12.856`): Poll frequency
- `~expected_frequency` (`double`, default: `frequency`): Expected
  frequency
- `~frequency_tolerance` (`double`, default: `0.1`): Tolerance on
  frequency for diagnosed publisher
- `~timestamp_min_acceptable` (`double`, default: `-1`): Min acceptable
  timestamp for diagnosed publisher
- `~timestamp_max_acceptable` (`double`, default: `-1`): Max acceptable
  timestamp for diagnosed publisher
- `~reconnect_timeout` (`double`, default: `2.0`): How long before we
  try a reconnecting to the device
- `~publish_intensities` (`bool`, default: `false`): Whether the
  intensities are filled in the output scan msg
