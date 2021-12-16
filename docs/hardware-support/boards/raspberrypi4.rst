.. SPDX-FileCopyrightText: Huawei Inc.
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../definitions.rst

.. _raspberrypi:

Raspberry Pi 4 Model B
######################

.. contents::
   :depth: 3

Overview
********

Raspberry Pi 4 Model B is powered with Broadcom BCM2711, quad-core Cortex-A72
(ARM v8) 64-bit SoC @ 1.5GHz. This product's key features include a
high-performance 64-bit quad-core processor, dual-display support at
resolutions up to 4K via a pair of micro-HDMI ports, hardware video decode at
up to 4Kp60, and the RAM size various from 2GB, 4GB, or 8GB, dual-band
2.4/5.0GHz wireless LAN, Bluetooth 5.0, Gigabit Ethernet, USB 3.0, and PoE
capability (via a separate PoE HAT add-on). The dual-band wireless LAN and
Bluetooth have modular compliance certification, allowing the board to be
designed into end products with significantly reduced compliance testing,
improving both cost and time to market.

Applications
************

* Embedded Design & Development
* Hobby & Education
* IoT (Internet of Things)
* Communications & Networking

Hardware
********

* For Raspberry Pi 4 Model B Schematics, see `RaspberryPi official website
  <https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_4b_4p0_reduced.pdf>`__.

* For Raspberry Pi 4 Model B datasheet, see `RaspberryPi official website
  <https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2711/rpi_DATA_2711_1p0.pdf>`__.

* For Raspberry Pi 4 boot EEPROM, see `RaspberryPi official website
  <https://www.raspberrypi.org/documentation/hardware/raspberrypi/booteeprom.md>`__.

For more details on the Raspberry Pi 4 board, see `Raspberry Pi hardware page
<https://www.raspberrypi.org/documentation/hardware/raspberrypi/>`__.

Working with the board
**********************

Building |main_project_name| image
==================================

To clone the source code, perform the procedure in: :ref:`Setting up a repo
workspace <RepoWorkspace>`.

Linux image
-----------

1. Source the environment with proper template settings, the flavour being
   *linux* and target machine being *raspberrypi4-64*. Pay attention to how
   relative paths are constructed. The value of *TEMPLATECONF* is relative to
   the location of the build directory *./build-linux-raspberrypi4-64*, which
   is going to be created after this step:

.. code-block:: console

   $ TEMPLATECONF=../oniro/flavours/linux . \
      ./oe-core/oe-init-build-env build-oniro-linux-raspberrypi4-64

2. You will find yourself in the newly created build directory. Call *bitbake*
   to build the image. For example, if you are using *oniro-image-base*
   run the following command:

.. code-block:: console

   $ MACHINE=raspberrypi4-64 bitbake oniro-image-base

3. After the build completes, the bootloader, kernel, and rootfs image files
   can be found in
   ``build-oniro-linux-raspberrypi4-64/tmp/deploy/images/$MACHINE/``.
   The key file which is needed to flash into the SD card is
   ``oniro-image-base-raspberrypi4-64.wic.bz2``.

Flashing |main_project_name| Linux image
****************************************

SD Card
=======

The Raspberry Pi 4 board support multiple boot options. The below section
describes booting the board with an SD card option.

1. After the image is built, you are ready to burn the generated image onto the
   SD card. We recommend using `bmaptool <https://github.com/intel/bmap-tools>`
   and the instructions below will use it. For example, if you are building
   oniro-image-base run the following command replacing (or defining)
   ``$DEVNODE`` accordingly:

.. code-block:: console

   $ cd tmp/deploy/images/raspberrypi4-64
   $ bmaptool copy oniro-image-base-raspberrypi4-64.wic.bz2 $DEVNODE

2. Put the card to the board and turn it on.

Testing the Board
*****************

HDMI
====

Two micro HDMI ports (HDMI-0 and HDMI-1) are enabled by default. Simply
plugging your HDMI-equipped monitor into the RPi4 using a standard HDMI
cable will automatically lead to the Pi using the best resolution
the monitor supports.

For more details, see `HDMI ports and configuration
<https://www.raspberrypi.org/documentation/configuration/hdmi-config.md>`__.

Bluetooth & BLE
===============
By default, BT and BLE are supported.

For any fault in the hardware device, see :ref:`How to handle faulty hardware device <FallbackSupport>`.

Ethernet & WiFi
===============

Drivers for both Ethernet and WiFi is available by default and hence no
specific configuration is needed to enable drivers for these interfaces.

Setting a static of dynamic IP for the interface is implementation and
deployment specific and any network configuration tool can be used to
configure IPv4 or IPv6 address to RPi.

To set up Wi-Fi connection, use ``nmcli`` by executing the following command:

.. code-block:: console

   # nmcli dev wifi connect "network-ssid" password "network-password"

For any fault in the hardware device, see :ref:`How to handle faulty hardware device <FallbackSupport>`.

Audio
=====

To enable the audio over 3.5mm jack, add the following line in your build's
``local.conf``:

.. code-block:: console

   RPI_EXTRA_CONFIG = "dtparam=audio=on"

To enable the ``aplay`` support for audio playback, append the following lines:

.. code-block:: console

   IMAGE_INSTALL_append = " gstreamer1.0  gstreamer1.0-meta-base
   gstreamer1.0-plugins-base gstreamer1.0-plugins-good"
   IMAGE_INSTALL_append = " alsa-lib alsa-utils alsa-tools"

To test the audio out on the *3.5mm audio jack*, we need to download the wav
file and play with ``aplay``.

.. code-block:: console

   # wget https://file-examples-com.github.io/uploads/2017/11/file_example_WAV_1MG.wav
   # aplay file_example_WAV_1MG.wav

Connect the headset on *3.5mm audio jack* and you should be able to hear the
audio.

I2C
===

I2C is disabled by default. To enable I2C, edit the ``local.conf`` build's
configuration adding:

.. code-block:: console

   ENABLE_I2C = "1"

The device tree does not create the I2C devices. For a quick test, install the
module.

.. code-block:: console

   root@raspberrypi4-64:~# modprobe i2c_dev
   [  611.019250] i2c /dev entries driver

   root@raspberrypi4-64:~# ls -ls /dev/i2c-1
       0 crw-------    1 root     root       89,   1 Mar 29 10:41 /dev/i2c-1

.. note::
   Need to be updated with more options.

GPIO
====

GPIO testing can be done using the sysfs Interface.

The following example shows how to test the GPIO-24 (which corresponds to
physical pin number 18 on the GPIO connector of the Raspberry Pi):

By default, sysfs driver is loaded, you will see the GPIO hardware exposed in
the file system under ``/sys/class/gpio``. It might look something like this:

.. code-block:: console

   root@raspberrypi4-64:/sys/class/gpio# ls /sys/class/gpio/
   export       gpiochip0    gpiochip504  unexport

We'll look at how to use this interface next. Note that the device names
starting with ``gpiochip`` are the GPIO controllers and we won't directly use
them.

To use a GPIO pin from the sysfs interface, perform the following steps:

1) Export the pin.

.. code-block:: console

   # echo 24 >/sys/class/gpio/export

2) Set the pin direction (input or output).

.. code-block:: console

   # echo out >/sys/class/gpio/gpio24/direction

3) If an output pin, set the level to low or high.

To validate the GPIO24 pin value, connect the LED light with the positive line
on pin #18 (GPIO24) and the negative line on pin #20 (Ground).

.. code-block:: console

   # echo 0 >/sys/class/gpio/gpio24/value  # to set it low - LED Turn OFF
   # echo 1 >/sys/class/gpio/gpio24/value  # to set it high - LED Turn ON

4) If an input pin, read the pin's level (low or high).

.. code-block:: console

   # cat /sys/class/gpio/gpio24/value  # 0 is low & 1 is high.

5) When done, unexport the pin.

.. code-block:: console

   # echo 24 >/sys/class/gpio/unexport
