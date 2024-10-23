MicroEJ
=======

.. only:: html

   .. image:: images/header_docs.png
      :alt: Docs

Welcome to the MicroEJ developer documentation.

MicroEJ (pronounced “micro-EDGE”) turns any electronic product or ‘things’ into smart things, MicroEJ tools and libraries enable you to easily create efficient and feature complete applications for embedded devices.
MicroEJ leverages a runtime environment called VEE (`Virtual Execution Environment <overview/vee.html>`_) to simplify and secure embedded development. 

Browse the following chapters to familiarize yourself and understand the principles of development with MicroEJ Technology.

- The :ref:`chapter-glossary` chapter describes MicroEJ terminology.
- The :ref:`overview` chapter introduces MicroEJ products and technology.
- The :ref:`sdk_user_guide` chapter presents MICROEJ SDK 5 (Software Development Kit). Use SDK 5 for legacy development.
- The :ref:`sdk_6_user_guide` chapter presents MICROEJ SDK 6 (Software Development Kit). Use SDK 6 for new projects.
- The :ref:`application-developer-guide` presents how to develop a Java or JavaScript application on MICROEJ VEE (Virtual Execution Environment).
- The :ref:`vee-porting-guide` teaches you how to integrate MICROEJ VEE into a C Board Support Package as well as simulation configurations.
- The :ref:`kernel-developer-guide` introduces you to advanced concepts, such as partial updates and dynamic app life cycle workflows.
- The :ref:`vee-wear` addresses the development of smartwatch applications using VEE Wear, specifically designed for low-power MCU and MPU.
- The :ref:`trainings` chapter offers online courses to help you learn the essentials of Firmware development using MICROEJ SDK.

.. toctree::
   :maxdepth: 2
   :hidden:
   
   Glossary <glossary>
   overview/index
   SDKUserGuide/index
   SDK6UserGuide/index
   ApplicationDeveloperGuide/index
   VEEPortingGuide/index
   KernelDeveloperGuide/index
   VEEWearUserGuide/index
   Trainings/index
   support
   about

.. toctree::
   :caption: SDK 5 User Guide
   :maxdepth: 2
   :hidden:

   SDKUserGuide/install
   SDKUserGuide/licenses
   SDKUserGuide/standaloneApplication
   SDKUserGuide/sandboxedApplication
   SDKUserGuide/mmmRepository
   SDKUserGuide/platformSelection
   SDKUserGuide/moduleNatures
   SDKUserGuide/debug
   SDKUserGuide/tools
   SDKUserGuide/ide
   SDKUserGuide/version
   SDKUserGuide/mmm
   SDKUserGuide/testsuite
   SDKUserGuide/howtos/index
   SDKUserGuide/sdkReleaseNotes
   SDKUserGuide/sdkChangeLog
   SDKUserGuide/sdkMigrationNotes

.. toctree::
   :caption: SDK 6 User Guide
   :maxdepth: 2
   :hidden:

   SDK6UserGuide/gettingStarted
   SDK6UserGuide/install
   SDK6UserGuide/licenses
   SDK6UserGuide/limitations
   SDK6UserGuide/createProject
   SDK6UserGuide/importProject
   SDK6UserGuide/selectVeePort
   SDK6UserGuide/runOnSimulator
   SDK6UserGuide/buildExecutable
   SDK6UserGuide/runOnDevice
   SDK6UserGuide/selectKernel
   SDK6UserGuide/buildFeature
   SDK6UserGuide/buildVirtualDevice
   SDK6UserGuide/addDependency
   SDK6UserGuide/testProject
   SDK6UserGuide/publishProject
   SDK6UserGuide/tools
   SDK6UserGuide/manageVersion
   SDK6UserGuide/manageResolutionConflicts
   SDK6UserGuide/migrateMMMProject
   SDK6UserGuide/moduleNatures
   SDK6UserGuide/troubleshooting
   SDK6UserGuide/tutorials/index
   SDK6UserGuide/howtos/index
   SDK6UserGuide/appendix/index
   SDK6UserGuide/sdk6ChangeLog
   SDK6UserGuide/sdk6MigrationNotes

.. toctree::
   :caption: Application Developer Guide
   :maxdepth: 2
   :hidden:

   ApplicationDeveloperGuide/introduction
   ApplicationDeveloperGuide/runtime
   ApplicationDeveloperGuide/soar
   ApplicationDeveloperGuide/buildOutputFiles
   ApplicationDeveloperGuide/virtualDevice
   ApplicationDeveloperGuide/classpath
   ApplicationDeveloperGuide/applicationResources
   ApplicationDeveloperGuide/standaloneApplication
   ApplicationDeveloperGuide/sandboxedApplication
   ApplicationDeveloperGuide/characterEncoding
   ApplicationDeveloperGuide/limitations
   ApplicationDeveloperGuide/github
   ApplicationDeveloperGuide/modulesRepositories
   ApplicationDeveloperGuide/libraries
   ApplicationDeveloperGuide/tools

.. toctree::
   :caption: VEE Porting Guide
   :maxdepth: 2
   :hidden:

   VEEPortingGuide/introduction
   VEEPortingGuide/architecture
   VEEPortingGuide/pack
   VEEPortingGuide/platformCreation
   VEEPortingGuide/veePortQualification
   VEEPortingGuide/coreEngine
   VEEPortingGuide/advanceTrace
   VEEPortingGuide/multiSandbox
   VEEPortingGuide/tinySandbox
   VEEPortingGuide/native
   VEEPortingGuide/externalResourceLoader
   VEEPortingGuide/serialCommunications
   VEEPortingGuide/ui
   VEEPortingGuide/vg
   VEEPortingGuide/net
   VEEPortingGuide/bluetooth
   VEEPortingGuide/audio
   VEEPortingGuide/packEventQueue
   VEEPortingGuide/fs
   VEEPortingGuide/hal
   VEEPortingGuide/device
   VEEPortingGuide/security
   VEEPortingGuide/watchdog-timer
   VEEPortingGuide/systemView
   VEEPortingGuide/simulation
   VEEPortingGuide/appendix/index

.. toctree::
   :caption: Kernel Developer Guide
   :maxdepth: 2
   :hidden:

   KernelDeveloperGuide/overview
   KernelDeveloperGuide/kf
   KernelDeveloperGuide/gettingStarted
   KernelDeveloperGuide/kernelCreation
   KernelDeveloperGuide/kernelAPI
   KernelDeveloperGuide/runtimeEnvironment
   KernelDeveloperGuide/kernelUID
   KernelDeveloperGuide/sandboxedAppLifecycle
   KernelDeveloperGuide/applicationSecurityPolicy
   KernelDeveloperGuide/featuresCommunication
   KernelDeveloperGuide/kfEnabledLibraries
   KernelDeveloperGuide/kfTestsuite
   KernelDeveloperGuide/kernelLink
   KernelDeveloperGuide/applicationLink

.. toctree::
   :caption: VEE Wear User Guide
   :maxdepth: 2
   :hidden:

   VEEWearUserGuide/android/index
   VEEWearUserGuide/ick
   VEEWearUserGuide/offloading
   VEEWearUserGuide/veescript

.. toctree::
   :caption: Training Courses
   :maxdepth: 2
   :hidden:

   Trainings/trainingSdkBasics
   Trainings/trainingDebugTools
   Trainings/trainingCManagedCodeCommunication
   Trainings/trainingMock


..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
