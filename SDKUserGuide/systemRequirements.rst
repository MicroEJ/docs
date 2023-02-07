.. _system-requirements:

System Requirements
===================

- **Hardware :**
   - Intel x64 (Dual-core i5 minimum) or macOS AArch64 (M1) processor
   - 4GB RAM (minimum)
   - 2GB Disk (minimum)

- **Operating Systems :**
   - Windows 10, Windows 8.1 or Windows 8
   - Linux distributions (tested on Ubuntu 18.04, 20.04 and 22.04) - As of SDK Distribution ``20.10`` (based on Eclipse 2020-06), Ubuntu 16.04 is not supported.
   - macOS x86_64 with Intel chip (tested on version 10.13 High Sierra, 10.14 Mojave)
   - macOS aarch64 with M1 chip (tested on version 12.0.1 Monterey), from SDK Distribution ``22.06``

- **Java Runtime Environment :**

The compatible JRE/JDK version depends on the Distribution, the SDK and the Architecture version.
This table lists the supported combinations:

.. list-table:: 
   :widths: auto
   :header-rows: 1

   * - Distribution
     - SDK
     - Architecture
     - JRE/JDK
   * - 22.06
     - >= 5.6.0
     - >= 7.17.0
     - JDK 11
   * - <= 21.11
     - >= 5.6.0
     - >= 7.17.0
     - JRE or JDK 8 or 11
   * - <= 21.11
     - < 5.6.0
     - \*
     - JRE or JDK 8
   * - <= 21.11
     - \*
     - < 7.17.0
     - JRE or JDK 8

The combinations not listed here are not supported.
For the supported combinations, tests have been done with both the Oracle and the Eclipse Adoptium JDK builds.

.. warning::
   It is important to note that the SDK Distribution ``22.06`` requires a JDK ``11`` (not a JRE) 
   and can be used only with an :ref:`Architecture <architecture_overview>` ``7.17.0`` or more.

.. _get_jdk:

Get JDK
-------

You can download and install a JDK from `Adoptium <https://adoptium.net/temurin/releases/>`__ or `Oracle <https://www.oracle.com/fr/java/technologies/downloads/>`__.

.. warning:: 
   When installing the Eclipse Temurin/AdoptOpenJDK build on Windows, the option ``JavaSoft (Oracle) registry keys`` must be enabled:

   .. figure:: images/adoptopenjdk-install.png
      :align: center
   
   Without this option, the SDK installer cannot find the JDK and the message ``The application requires a Java Runtime Environment 8`` is displayed.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
