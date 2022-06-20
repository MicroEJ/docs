.. _system-requirements:

System Requirements
===================

- **Intel x64 PC with minimum :**
   - Dual-core Core i5 processor
   - 4GB RAM
   - 2GB Disk

- **Operating Systems :**
   - Windows 10, Windows 8.1 or Windows 8
   - Linux distributions (tested on Ubuntu 18.04, 20.04 and 22.04) - As of SDK Distribution ``20.10`` (based on Eclipse 2020-06), Ubuntu 16.04 is not supported.
   - macOS with Intel chip (tested on version 10.13 High Sierra, 10.14 Mojave)
   - macOS with Apple M1 chip (tested on version 12.0.1 Monterey)

- **Java :**
   - JDK 11 (Oracle JDK or other OpenJDK build: tested on AdoptOpenJDK/Eclipse Adoptium)

.. warning::
   Starting from the SDK Distribution 22.06, a JDK is required to install and launch it, so please ensure that you do not use a JRE.

.. warning:: 
   When installing the AdoptOpenJDK build on Windows, the option ``JavaSoft (Oracle) registry keys`` must be enabled:

   .. figure:: images/adoptopenjdk-install.png
      :align: center
   
   Without this option, the SDK installer cannot find the JDK and the message ``The application requires a Java Runtime Environment 11`` is displayed.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
