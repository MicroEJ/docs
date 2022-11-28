.. _sdk_6_install:

Installation
============

This chapter will guide you through the installation process of the SDK on your workstation.
Please first check the System Requirements before proceding.

System Requirements
-------------------

- **Hardware**
   - Intel x64 (Dual-core i5 minimum) or macOS AArch64 (M1) processor
   - 4GB RAM (minimum)
   - 2GB Disk (minimum)

- **Operating Systems**
   - Windows 11 or Windows 10
   - Linux distributions (tested on Ubuntu 20.04 and 22.04)
   - macOS x86_64 with Intel chip
   - macOS aarch64 with M1 chip

- **Java Runtime Environment**
    - JDK 11 - Eclipse Temurin or Oracle Distributions

Install Gradle
--------------

The first step is to install Gradle by following `the official documentation <https://gradle.org/install/>`__.
The minimum required version is ``7.3``.
Once done, you can verify your installation by opening a terminal and run the command ``gradle -v``.
It should display the Gradle version, for example:

.. code:: console

   $ gradle -v
   
   ------------------------------------------------------------
   Gradle 7.5.1
   ------------------------------------------------------------

Configure repositories
----------------------

In order to use the SDK Gradle plugins and modules in your project, 
the :ref:`Central <central_repository>` and :ref:`Developer <developer_repository>` repositories must be configured.
There are several ways to declare repositories.
For starting you can declare them globally to make them available in all your projects:

- create the folder ``<user.home>/.gradle/init.d`` if they do not exist.
- download and copy :download:`this file <resources/microej.init.gradle.kts>` in the previously created folder.

At this stage, you can already build a project from the command line, 
for example by executing the command ``gradle build`` at the root of the project.
But let's continue the installation process to have a complete development environment.

Install the IDE
---------------

Using an IDE is highly recommended to develop MicroEJ projects, as it makes the development more confortable and increases the productivity. 
The two following IDEs are supported: 

- `Eclipse IDE for Java Developers <https://www.eclipse.org/downloads/packages/release/2022-09/r/eclipse-ide-java-developers>`__ - Minimum supported version is ``2022-03``.
- `IntelliJ IDEA <https://www.jetbrains.com/idea/>`__ - Minimum supported version is ``2022.2``.

Please follow their respective documentation to install one of them.

These 2 IDEs come with the Gradle plugin installed by default, so you don't have anything else to do then, 
you are ready to start developing MicroEJ projects!

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
