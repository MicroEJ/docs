.. _ack_installation_:

Installation
============

This chapter will guide you through the installation process of the SDK using Android Studio as the integrated development environment (IDE).
Before proceeding with the installation, please make sure your workstation meets the system requirements.

System Requirements
-------------------

* **Hardware**
   * x86_64 CPU architecture, ARM-based chips, 2nd generation Intel Core or newer, or AMD processor with support for AMD Virtualization (AMD-V) and SSSE3
   * 8 GB RAM or more
   * 8 GB of available disk space minimum (IDE + Android SDK + Android Emulator)
   * 1280 x 800 minimum screen resolution

* **Operating Systems**
   * 64-bit Microsoft® Windows® 8/10
   * Any 64-bit Linux distribution that supports Gnome, KDE, or Unity DE; GNU C Library (glibc) 2.31 or later.
   * MacOS® 10.14 (Mojave) or higher

* **Java Runtime Environment**
    * JDK 11 - Eclipse Temurin or Oracle Distributions


Download Android Studio
-----------------------

Download and install Android Studio Dolphin 2021.3.1 released on September 15, 2022, from the `Android Developer Archive <https://developer.android.com/studio/archive>`_.

For more information about Android Studio (installation, release notes or system requirements), please refer to the `Android Developer site <https://developer.android.com/studio>`_.


JDK Version
-----------

The latest versions of Android Studio bundle a copy of the OpenJDK. To check that version 11 of the JDK is used:

1. In Android Studio, ``File`` > ``Settings`` (on macOS, ``Android Studio`` > ``Preferences``).
2. In the settings pane, navigate to ``Build, Execution, Deployment`` > ``Build Tools`` > ``Gradle``.
3. Under Gradle JDK, check that the version of the JDK being used is 11.

If you don't have a JDK 11 installed, 
you can download and install one from `Adoptium <https://adoptium.net/temurin/releases/>`_ or `Oracle <https://www.oracle.com/fr/java/technologies/downloads/>`_.


..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.