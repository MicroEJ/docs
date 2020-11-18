Licenses
========

.. _concepts-licenses:

Overview
--------

MicroEJ Architectures are distributed in two different versions:

- Evaluation Architectures, associated with a software license key. Can be found on `<https://repository.microej.com/architectures/>`_.
- Production Architectures, associated with an hardware license key stored on a USB dongle. Can be requested to MicroEJ support team support@microej.com

Licenses list is available in MicroEJ preferences dialog page in :guilabel:`Window`
> :guilabel:`Preferences` > :guilabel:`MicroEJ`

.. figure:: images/preferences/licenses.jpg
   :alt: MicroEJ Licenses View
   :align: center
   :width: 995px
   :height: 418px

   MicroEJ Licenses View

Note that :

-  Evaluation licenses will be shown only if architectures requiring an
   evaluation license are detected in your MicroEJ repository.

-  Production licenses will be shown only if architectures requiring a
   production license are detected in your MicroEJ repository.

See section :ref:`gettingstarted-installlicenses` for more
information.


.. _gettingstarted-installlicenses:

Installation
------------

For more information about the licenses protection, please refer to
section :ref:`concepts-licenses`.


.. _gettingstarted-installlicenseseval:

Evaluation Licenses
-------------------

This section should be considered when using evaluation platforms, which
use software license keys.

.. _gettingstarted-installlicenseseval-uid:

Generating Machine UID
~~~~~~~~~~~~~~~~~~~~~~

To activate an evaluation platform, a machine UID needs to be provided
to the key server. This information is available from the :guilabel:`Window` >
:guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Architectures` or :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ`
> :guilabel:`Platforms` preferences page. Click on one of the available architectures or platforms and press the :guilabel:`Get UID` button to get the generated machine identifier.

.. note:: At least one Platform or Architecture must have been imported to access this :guilabel:`Get UID` option. See section :ref:`download.hardware.simulator` for more information.

Copy the UID. It will be needed when requesting a license.

.. figure:: images/preferences/uid.jpg
   :alt: Generated Machine Identifier for Evaluation License
   :align: center
   :width: 532px
   :height: 172px

   Generated Machine Identifier for Evaluation License

.. _gettingstarted-installlicenseseval-key:

Generate Your Activation Key
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Go to `license.microej.com <https://license.microej.com/>`_.
- Click on :guilabel:`Create a new account` link.
- Create your account with a valid email address. You will receive a confirmation email a few minutes after. Click on the confirmation link in the email and login with your new account.
- Click on :guilabel:`Activate a License`.
- Set :guilabel:`Product P/N:` to ``9PEVNLDBU6IJ``.
- Set :guilabel:`UID:` to the UID you generated before.
- Click on :guilabel:`Activate`.
- The license is being activated. You should receive your activation by email in less than 5 minutes. If not, please contact support@microej.com.
- Once received by email, save the attached zip file that contains your activation key.

.. _gettingstarted-installlicenseseval-install:

Installing License Keys
~~~~~~~~~~~~~~~~~~~~~~~

- Go back to MicroEJ SDK.
- Select the :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` menu.
- Press :guilabel:`Add...`.
- Browse the previously downloaded activation key archive file.
- Press OK. A new license is successfully installed.
- Go to Architectures sub-menu and check that all architectures are now activated (green check).
- Your MicroEJ SDK is successfully activated.

If an error message appears, the license key could not be installed. (see
section :ref:`gettingstarted-installlicenseseval-troubleshoot`).
A license key can be removed from key-store by selecting it and by
clicking on :guilabel:`Remove` button.

.. _gettingstarted-installlicenseseval-troubleshoot:

License Keys Troubleshooting
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Consider this section when an error message appears while adding the
license key. Before contacting MicroEJ support, please check the
following conditions:

-  Key is corrupted (wrong copy/paste, missing characters or extra
   characters)

-  Key has not been generated for the installed environment

-  Key has not been generated with the machine UID

-  Machine UID has changed since submitting license request and no
   longer matches license key

-  Key has not been generated for one of the installed platforms (no
   license manager able to load this license)

.. figure:: images/preferences/wrongkey.jpg
   :alt: Invalid License Key Error Message
   :align: center
   :width: 532px
   :height: 210px

   Invalid License Key Error Message


.. _gettingstarted-installlicensesprod:

Production Licenses
-------------------

This section should be considered when using production platforms,
which use hardware license keys. If your USB dongle has been provided to you by your sales representative, it may be a pre-activated dongle, then skip the activation steps.

Generate your Activation Key
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Go to `license.microej.com <https://license.microej.com/>`_.
- Click on :guilabel:`Create a new account` link.
- Create your account with a valid email address. You will receive a confirmation email a few minutes after. Click on the confirmation link in the email and login with your new account.
- Click on :guilabel:`Activate a License`.
- Set :guilabel:`Product P/N:` to **The P/N on the activation certificate**.
- Enter your UID: serial number printed on the USB dongle label (8 alphanumeric char.).
- Click on :guilabel:`Activate` and check confirmation message.
- Click on :guilabel:`Confirm your registration`.
- Enter the **Registration Code provided on the activation certificate**.
- Click on :guilabel:`Submit`.
- Your Activation Key will be sent to you by email as soon as it is available (12 business hours max.).

    - You can also check the :guilabel:`My Products` page to verify your product registration status, the Activation Key availability and to download the Activation Key when available.

Product Activation
~~~~~~~~~~~~~~~~~~

 Once the Activation Key is available, update your USB dongle as follow:

- Download and save the Activation Key ZIP file.
- Unzip the ``Activation Key`` file and enter the directory just created by your ZIP extraction tool.
- Insert the USB dongle into a USB port of a Windows computer.
- Launch the executable program.
- Click on the :guilabel:`Update` button (no password needed)
- USB dongle will be updated when “Successfully updated” dialog box appears.

Check activation on MicroEJ SDK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Go back to MicroEJ SDK.
- Select the :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` menu.
- Go to the :guilabel:`Architectures` sub-menu and check that all production architectures are now activated (green check).
- Your MicroEJ SDK is successfully activated.


.. _dongles-update:

USB Dongles Update
~~~~~~~~~~~~~~~~~~

This section contains instructions that will allow to flash your
hardware dongle with the proper activation key.

You shall ensure that the following prerequisites are met :

-  The USB dongle is plugged and recognized by your operating system
   (see :ref:`dongles-recognition` section)

-  No more than one dongle is plugged to the computer while running the
   update tool

-  The update tool is not launched from a Network drive or from a USB
   key

-  The activation key you downloaded is the one for the dongle UID on
   the sticker attached to the dongle (each activation key is tied to
   the unique hardware ID of the dongle).

You can then proceed to the dongle update by running the activation key
executable. Just press :guilabel:`Update` (no key is required). 

.. figure:: images/dongle/updateTool.png
   :alt: Dongle Update Tool
   :align: center
   :width: 271px
   :height: 310px

   Dongle Update Tool

On success, an ``Update successfully`` message shall appear. On failure, an
``Error key or no proper rockey`` message may appear.

.. figure:: images/dongle/updateSuccessful.png
   :alt: Successful dongle update
   :align: center
   :width: 222px
   :height: 169px

   Successful dongle update

Once you have successfully updated your dongle, from MicroEJ, go to
:guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Platforms`. You shall see that the
license status for the platforms you installed with the ``License tag``
matching the one on the sticker attached to your USB dongle has turned
from a red cross to a green tick.

.. figure:: images/dongle/platformLicenseDetails.png
   :alt: Platform License Status OK
   :align: center
   :width: 926px
   :height: 324px

   Platform License Status OK

.. _dongles-recognition:

USB Dongles Recognition
~~~~~~~~~~~~~~~~~~~~~~~

This section contains instructions that will allow to check that your
hardware dongle is actually recognized by your operating system

.. _troubleshooting-linux:

GNU/Linux Troubleshooting
"""""""""""""""""""""""""

For GNU/Linux Users (Ubuntu at least), by default, the dongle access has
not been granted to the user, you have to modify udev rules. Please
create a ``/etc/udev/rules.d/91-usbdongle.rules`` file with the
following contents:

::

   ACTION!="add", GOTO="usbdongle_end"
       SUBSYSTEM=="usb", GOTO="usbdongle_start"
       SUBSYSTEMS=="usb", GOTO="usbdongle_start"
       GOTO="usbdongle_end"
       
       LABEL="usbdongle_start"
       
       ATTRS{idVendor}=="096e" , ATTRS{idProduct}=="0006" , MODE="0666"
       
       LABEL="usbdongle_end"

Then, restart udev: ``/etc/init.d/udev restart``

You can check that the device is recognized by running the ``lsusb``
command. The output of the command should contain a line similar to the
one below for each dongle :
``Bus 002 Device 003: ID 096e:0006 Feitian Technologies, Inc.``

Windows Troubleshooting
"""""""""""""""""""""""

For Windows users, each dongle shall be recognized with the following
hardware ID :

::

   HID\VID_096E&PID_0006&REV_0109

On Windows 8.1, go to :guilabel:`Device Manager` > :guilabel:`Human Interface Devices` and
check among the ``USB Input Device`` entries that the
``Details`` > ``Hardware Ids`` property match the ID mentioned before.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

VirtualBox Troubleshooting
""""""""""""""""""""""""""

In a VirtualBox virtual machine, USB drives must be enabled to be recognized correctly.
So make sure to enable the USB dongle by clicking on it in the VirtualBox menu ``Devices`` > ``USB``.

In order to make this setting persistent, go to ``Devices`` > ``USB`` > ``USB Settings...`` 
and add the USB dongle in the ``USB Devices Filters`` list.

Production License Key Troubleshooting
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- If you did not received an activation certificate, please contact the support@microej.com.
- Check that you have your Activation Key.
- Check that your dongle is activated.
- In the SDK, in :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ`,

   - Check that the dongle appears on the ``Licenses`` list.

       - If not, check that the dongle is plugged in your computer. If using Linux :ref:`please configure the USB rules <troubleshooting-linux>`.

   - In :guilabel:`Architectures` tab check that some Production Architectures are available.

- Errors may occurs when launching the activation tool from a server mounted FS, copy it to your desktop before.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
