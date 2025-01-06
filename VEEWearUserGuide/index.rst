.. _vee-wear:

VEE Wear User Guide
===================

VEE Wear is a comprehensive wearable software solution.
It aggregates multiple libraries, applications and tools dedicated to the development of wearable software.

|

**VEE Wear Framework**

The :ref:`VEE Wear Framework <vee_wear_framework>` provides a turnkey, customizable wearable firmware.

This framework contains the following components:

- a Multi-Sandboxed wearable Kernel
- common wearable apps (Settings, :ref:`Facer <facer_engine>`, Health, Stopwatch, etc.)
- a wearable API to develop custom wearable apps

|

.. _facer_engine:

**Low Power Facer Engine**

VEE Wear supports the `Facer <https://www.facer.io/>`_ Engine, expanding Facer's extensive watch face catalog of 500,000 faces across all smartwatches, including low-power RTOS watches, enriching the user experience for all users. 
For further information about the MicroEJ and Facer partnership, please contact your `MicroEJ sales representative <https://www.microej.com/contact/#form_1>`_.

|

**Android Compatibility Kit**

The :ref:`Android Compatibility Kit <android_compatibility_kit>` comprises two technologies:

1.	Support for Android development tools, including Android Studio and Gradle, is provided by MICROEJ SDK 6.
2.	Support for MicroEJ applications on the Android OS (Android Runtime).

The support provided by Android development tools and Android runtime is especially beneficial when running the same application on both an Android processor and an MCU. 
This scenario occurs, for example, when implementing Android off-loading with a big-little architecture.

Moreover, the Android runtime enables the execution of the same application on an Android smartphone. 
For instance, in scenarios such as building a watch face or app picker within a companion smartphone app, the MicroEJ application code can be directly utilized to display the app or watch face. 
This eliminates the necessity to develop a similar version specifically for Android.

|

**iOS Compatibility Kit**

The :ref:`iOS Compatibility Kit <ios_compatibility_kit>` feature provides support for MicroEJ applications on iOS (iOS Runtime). 
This runtime enables the execution of the same application on an iOS smartphone. 
For example, when creating a watch face or app picker within a companion smartphone app, the MicroEJ application code can be directly used to display the app or watch face. 
This eliminates the necessity to develop a separate version for iOS.

|

**MicroEJ's offloading framework**

VEE Wear incorporates an :ref:`offloading framework <offloading>` designed to optimize power consumption in a big-little architecture, where an application processor runs Android, and a companion MCU operates MICROEJ VEE. 
By alternating the execution of applications between low-consumption MCUs and powerful MPUs, this setup guarantees maximum power efficiency, thereby conserving battery life. 
The offloading framework encompasses an inter-processor communication framework and efficient low-power profile management.



.. toctree::
   :hidden:
   :maxdepth: 0

   framework
   android/index
   ick
   offloading
   veescript

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
