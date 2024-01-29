.. _vee-wear:

VEE Wear User Guide
===================

VEE Wear is a specialized application framework tailor-made for next-gen smartwatches. 
Engineered with a highly optimized memory footprint, VEE Wear ensures efficient performance on low-power MCUs and MPUs while offering robust features comparable to larger operating systems.

VEE Wear includes all graphical features from MicroEJ runtime, including:

* A thread-safe 2D graphics engine
* A widget framework
* Vector drawing support
* And more. Refer to the :ref:`Graphical User Interface <pack_gui>` section for more info

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

|

**Low Power Facer Engine**

VEE Wear supports the `Facer <https://www.facer.io/>`_ Engine, expanding Facer's extensive watch face catalog of 500,000 faces across all smartwatches, including low-power RTOS watches, enriching the user experience for all users. 
For further information about the MicroEJ and Facer partnership, please contact your `MicroEJ sales representative <https://www.microej.com/contact/#form_1>`_.



.. toctree::
   :hidden:
   :maxdepth: 0

   android/index
   ick
   offloading

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
