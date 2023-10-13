.. _runnning_on_android:

Android Compatibility Kit
=========================

MicroEJ provides a set of tools and libraries to run applications powered by MicroEJ on Android and Wear OS.
This allows for the same application to be developed, simulated, tested, and executed on MicroEJ VEE and Android alike.

Having the same code ready for both Android and MicroEJ VEE opens up a wide range of use cases, including but not limited to:

* Develop derivative products based on small MCUs or low-cost MPUs with limited resources where Android cannot be used as it is inherently resource-intensive.
* Reduce energy consumption by enabling two processors to coexist to distribute tasks between a very powerful processor powered by Android and a low-power processor powered by MicroEJ.

Below are some examples from the wearables segment that illustrate these use cases:

* Watch faces can be developed once and deployed on both a smartwatch (MicroEJ VEE) and its companion smartphone app (Android), enabling consistent functionality and appearance across both devices. This provides a good user experience for the user while minimizing code duplication and maintenance for the developer.
* Power efficiency is a significant concern with wearables as sophisticated features often come at a high cost in terms of power consumption. An offloading framework can reduce power usage by executing the same application alternately on a low-consumption MCU and a powerful MPU. Operating in standby mode as much as possible on the MCU is one of the strategies to achieve energy efficiency.



.. toctree::
   :maxdepth: 2

   overview
   installation
   projectSetup
   veePort

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
