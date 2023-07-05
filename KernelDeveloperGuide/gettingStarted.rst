Getting Started
===============

Online Getting Started
----------------------

The Multi-Sandbox Executable Getting Started is available on MicroEJ
GitHub repository, at
`<https://github.com/MicroEJ/Example-MinimalMultiAppFirmware>`_.

The file ``README.md`` provides a step by step guide to produce a
minimal firmware on an evaluation board on which new applications can be
dynamically deployed through a serial or a TCP/IP connection.

.. |x| image:: ../images/check.png
   :width: 10pt
   :height: 10pt

.. role:: fwgre
.. role:: fwblu
.. role:: fwred
.. role:: fwpur
.. role:: fwbla

MicroEJ Demo VEE Flavors
------------------------
This set of APIs is proposed as examples of industrial or commercial typical products APIs.

What is a MicroEJ Demo Runtime Environment?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Runtime Environment defines a set of MicroEJ APIs exposed to a MicroEJ Sandboxed Application. Here are the default runtimes provided for evaluation by MicroEJ. Any runtime can be customized with MicroEJ SDK for a specific product.

+----------------------------------+-------------+-------------+--------------+-----------------+-----+-----+-----------+
| MicroEJ Demo Runtime Environment | EDC/B-ON/KF | MICROUI/MWT | LEDS/BUTTONS | NET/CONNECT/SSL | BLE | HAL | ECOM/COMM |
+==================================+=============+=============+==============+=================+=====+=====+===========+
| MicroEJ-Developer                | |x|         | |x|         | |x|          | |x|             |     | |x| | |x|       |
+----------------------------------+-------------+-------------+--------------+-----------------+-----+-----+-----------+
| MicroEJ-UI                       | |x|         | |x|         | |x|          |                 |     | |x| | |x|       |
+----------------------------------+-------------+-------------+--------------+-----------------+-----+-----+-----------+
| MicroEJ-Headless                 | |x|         |             | |x|          | |x|             |     | |x| | |x|       |
+----------------------------------+-------------+-------------+--------------+-----------------+-----+-----+-----------+
| MicroEJ-BLE                      | |x|         | |x|         | |x|          | |x|             | |x| | |x| | |x|       |
+----------------------------------+-------------+-------------+--------------+-----------------+-----+-----+-----------+								

You can find below what are the different APIs included in the Runtime Environment:

+----------------------------+--------------------------------------------------------------------------------------------------+
| API                        | Purpose                                                                                          |
+============================+==================================================================================================+
| EDC                        | Core APIs for the execution.                                                                     |
+----------------------------+--------------------------------------------------------------------------------------------------+
| B-ON                       | Memory Usage control and Sequences start-up.                                                     |
+----------------------------+--------------------------------------------------------------------------------------------------+
| KF                         | Required by the implementation of Shared Interfaces, an inter-application communication process. |
+----------------------------+--------------------------------------------------------------------------------------------------+
| COMP or COMPONENTS         | Lightweight Services Framework.                                                                  |
+----------------------------+--------------------------------------------------------------------------------------------------+
| MICROUI/MWT                | Main UI library for MicroEJ and the Widgets framework based on MicroUI.                          |
+----------------------------+--------------------------------------------------------------------------------------------------+
| LEDS or MICROUI-LEDS       | UI library specific to LEDs.                                                                     |
+----------------------------+--------------------------------------------------------------------------------------------------+
| BUTTONS or MICROUI-BUTTONS | UI library specfic to buttons.                                                                   |
+----------------------------+--------------------------------------------------------------------------------------------------+
| NET                        | Socket (TCP/UDP) library.                                                                        |
+----------------------------+--------------------------------------------------------------------------------------------------+
| CONNECT or CONNECTIVITY    | Network connectivity detection library.                                                          |
+----------------------------+--------------------------------------------------------------------------------------------------+
| SSL                        | Secure Socket Layer.                                                                             |
+----------------------------+--------------------------------------------------------------------------------------------------+
| BLE                        | Bluetooth Low Energy support.                                                                    |
+----------------------------+--------------------------------------------------------------------------------------------------+
| HAL                        | GPIO Access (digital and analog)                                                                 |
+----------------------------+--------------------------------------------------------------------------------------------------+
| ECOM                       | Device access framework.                                                                         |
+----------------------------+--------------------------------------------------------------------------------------------------+
| COMM or ECOM-COMM          | Serial ports support for the ECOM.                                                               |
+----------------------------+--------------------------------------------------------------------------------------------------+

What is a MicroEJ Demo Flavor?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A MicroEJ Demo Flavor is a composition of a set of runtime services, pre-installed Applications, and a given MicroEJ Runtime Environment. Any flavor can be customized with MicroEJ SDK for a specific product.

+---------------------+-----------------------------+----------------------------------------------------------------+---------------------------------+
| MicroEJ Demo Flavor | MicroEJ Runtime Environment | Services Pre-installed Apps                                    | UI Pre-installed Apps           |
+---------------------+-----------------------------+------------+----------------------+----------------------+-----+-------+---------+---------------+
|                                                   | Management | App-Metadata-Storage | CommandServer-Socket | NTP | About | AppList | Forge Connect |
+=====================+=============================+============+======================+======================+=====+=======+=========+===============+
| :fwgre:`Green`      | MicroEJ-Developer           | |x|        | |x|                  | |x|                  | |x| |       |         |               |
+---------------------+-----------------------------+------------+----------------------+----------------------+-----+-------+---------+---------------+
| :fwblu:`Blue`       | MicroEJ-Developer           | |x|        | |x|                  | |x|                  | |x| | |x|   | |x|     | |x|           |
+---------------------+-----------------------------+------------+----------------------+----------------------+-----+-------+---------+---------------+
| :fwred:`Red`        | MicroEJ-UI                  | |x|        | |x|                  |                      |     | |x|   | |x|     |               |
+---------------------+-----------------------------+------------+----------------------+----------------------+-----+-------+---------+---------------+
| :fwpur:`Purple`     | MicroEJ-Headless            | |x|        | |x|                  | |x|                  | |x| |       |         |               |
+---------------------+-----------------------------+------------+----------------------+----------------------+-----+-------+---------+---------------+
| :fwbla:`Black`      | MicroEJ-BLE                 | |x|        | |x|                  | |x|                  | |x| |       |         | |x|           |
+---------------------+-----------------------------+------------+----------------------+----------------------+-----+-------+---------+---------------+

You can find below what are the different pre-installed Applications included in the Flavor:

+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| Application                  | Purpose                                                                                                                                  |
+==============================+==========================================================================================================================================+
| Management                   | Contains the implementation of Application lifecycle and services.                                                                       |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| App-Metadata-Storage         | Stores some Applications Metadata (icons, descriptions) so that it can be locally used by a MicroEJ Companion.                           |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| CommandServer-Socket         | Allows the deployment of MicroEJ Applications through a local network connection.                                                        |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| NTP                          | Synchronizes the time of the device.                                                                                                     |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| About                        | Displays version information about the VEE.                                                                                              |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| AppList                      | An application browser, can be used to start, stop or uninstall the applications, or display their descriptions and version information. |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| Forge Connect                | Displays a desktop that allows the management of MicroEJ Applications using a connection to MICROEJ FORGE.                               |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+
| Settings                     | Displays the VEE parameters and settings.                                                                                                |
+------------------------------+------------------------------------------------------------------------------------------------------------------------------------------+

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
