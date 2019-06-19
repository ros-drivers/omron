^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package omron_os32c_driver
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Forthcoming
-----------
* feat: ~reconnect_timeout parameter
  Driver will automatically reconnect if no connection can be established
  or if a scan has not be received for the specified number of seconds.
* Added reflection measurement and frequency param
* Use TCP/IP polling instead of UDP
* Contributors: Rein Appeldoorn, Tom de Winter

0.1.3 (2019-04-18)
------------------
* Merge pull request `#23 <https://github.com/ros-drivers/omron/issues/23>`_ from ros-drivers/ci/kinetic_melodic
  Industrial CI Kinetic + Melodic
* fix: test narrow conversion from char to uint8_t
* Merge pull request `#21 <https://github.com/ros-drivers/omron/issues/21>`_ from ros-drivers/rosconsole_bridge
  Enabled rosconsole_bridge for odva_ethernetip
* Contributors: Rein Appeldoorn

0.1.2 (2018-05-18)
------------------
* Changed maintainer to Rein Appeldoorn
* feat(omron_node): ~local_ip parameter for udp binding (`#15 <https://github.com/ros-drivers/omron/issues/15>`_)
* omron_node: Diagnostics for frequency (`#14 <https://github.com/ros-drivers/omron/issues/14>`_)
* Swap start and end angles. The laser rotates in the negative direction.
* Merge pull request `#10 <https://github.com/ros-drivers/omron/issues/10>`_ from gavanderhoorn/build_infra
* Minor manifest and build script updates.
* Contributors: Mike Purvis, Rein Appeldoorn, gavanderhoorn

0.1.1 (2015-11-17)
------------------
* Fixed library name.
* Contributors: Tony Baltovski

0.1.0 (2015-11-17)
------------------
* Initial release.
* Contributors: Kareem Shehata, Mike Purvis, Tony Baltovski
