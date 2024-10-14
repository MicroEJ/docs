.. _tutorials:

========
Training
========

Welcome to the MicroEJ training courses!

This documentation offers online courses to help you learn the essentials of
Firmware development using MICROEJ SDK.

Whether you're a beginner or more advanced, you will gain a solid 
understanding of Application development using MICROEJ SDK and 
MICROEJ VEE integration on custom devices.
Additionally, you will discover the feature-rich ecosystem provided to developers to ease developments on a daily basis.

Each training will specify its prerequisites. 
For courses involving hands-on activities, you may need to use one of the following development kits:

- `NXP i.MX RT1170 Evaluation Kit <https://www.nxp.com/design/design-center/development-boards-and-designs/i-mx-evaluation-and-development-boards/i-mx-rt1170-evaluation-kit:MIMXRT1170-EVKB>`__.
- `STM32F7508-DK Evaluation Kit <https://www.st.com/en/evaluation-tools/stm32f7508-dk.html>`__.

Alternatively, the hands-on activities can be fully completed using MICROEJ SDK Simulator.

.. _training_for_beginners:

For Beginners
=============

Basics
------
.. toctree::
   :hidden:

   trainingSdkBasics
   trainingDebugTools
   trainingCManagedCodeCommunication
   trainingMock

.. raw:: html

         <div class="training_items">

            <a class="training_link" href="trainingSdkBasics.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_sdk_veeport.jpg" alt="MICROEJ SDK Basics">
               </div>
               <h3 class="training_title">MICROEJ SDK Basics</h3>
               <p class="training_description">This training session introduces you to the MicroEJ ecosystem, 
               guiding you through the process of creating your first application project. 
               You will run your project on both a simulator and an actual device using MICROEJ SDK.
               </p>
               <a class="training_learn_more_link" href="trainingSdkBasics.html">Learn more</a>
            </div>
            </a>

            <a class="training_link" href="trainingDebugTools.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 2</div>
                  <img src="../_static/images/training/training_debug.jpg" alt="Debug Tools">
               </div>
               <h3 class="training_title">Debugging with MICROEJ SDK</h3>
               <p class="training_description">In this training, you will get an overview of the debug tools provided 
               to developers to debug an application. 
               </p>
               <a class="training_learn_more_link" href="trainingDebugTools.html">Learn more</a>
            </div>
            </a>
            
            <a class="training_link" href="trainingCManagedCodeCommunication.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 3</div>
                  <img src="../_static/images/training/training_managed_code_c_communication.jpg" alt="C / Managed Code Communication">
               </div>
               <h3 class="training_title">C / Managed Code Communication</h3>
               <p class="training_description">In this training, you will get an in depth view of the different ways
               to perform C / Managed Code communication using Native Interface Mechanisms.
               </p>
               <a class="training_learn_more_link" href="trainingCManagedCodeCommunication.html">Learn more</a>
            </div>
            </a>

            <a class="training_link" href="trainingMock.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 4</div>
                  <img src="../_static/images/training/training_mock.jpg" alt="MicroEJ Java Specificities">
               </div>   
               <h3 class="training_title">Simulate Hardware Behavior using Mocks</h3>
               <p class="training_description">In this training, you will learn how to use mocks
               in order to enhance application development on Simulator.
               </p>
               <a class="training_learn_more_link" href="trainingMock.html">Learn more</a>
            </div>
            </a>

         </div>

For Application Developers
--------------------------

.. toctree::
   :hidden:
   
   tutorialImproveCodeQuality
   tutorialOptimizeMemoryFootprint
   trainingApplicationTesting

.. raw:: html

         <div class="training_items">

            <a class="training_link" href="tutorialImproveCodeQuality.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_java_code_practices.jpg" alt="Best Java Code Practices">
               </div>
               <h3 class="training_title">Best Java Code Practices</h3>
               <p class="training_description">In this training, you will learn the best practices to
               write Java code considering embedded systems constraints.
               </p>
               <a class="training_learn_more_link" href="tutorialImproveCodeQuality.html">Learn more</a>
            </div>
            </a>
            
            <a class="training_link" href="trainingApplicationTesting.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 2</div>
                  <img src="../_static/images/training/training_junit.jpg" alt="JUnit">
               </div>
               <h3 class="training_title">Application Testing</h3>
               <p class="training_description">In this training, you will learn the basics to
               develop and run unit tests on an application using the JUnit framework.
               </p>
               <a class="training_learn_more_link" href="trainingApplicationTesting.html">Learn more</a>
            </div>
            </a>
            
            <a class="training_link" href="tutorialOptimizeMemoryFootprint.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 3</div>
                  <img src="../_static/images/training/training_optimize_footprint.jpg" alt="Optimize the Memory Footprint of an Application">
               </div>
               <h3 class="training_title">Optimize the Memory Footprint of an Application</h3>
               <p class="training_description">In this training, you will learn common rules aimed 
               at optimizing both ROM and RAM footprint of an Application.
               </p>
               <a class="training_learn_more_link" href="tutorialOptimizeMemoryFootprint.html">Learn more</a>
            </div>
            </a>

            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 4</div>
                  <img src="../_static/images/training/training_microej_java.jpg" alt="MicroEJ Java Specificities">
               </div>
               <h3 class="training_title">MicroEJ Java Specificities</h3>
               <p class="training_description">Coming Soon!
               </p>
               <a>Learn more</a>
            </div>
            
         </div>

For VEE Developers
------------------

.. toctree::
   :hidden:
   
   trainingVEEPortDevFromScratch
   trainingPQT
   trainingDebugHardfault

.. raw:: html

         <div class="training_items">

            <a class="training_link" href="trainingVEEPortDevFromScratch.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_createFirmwareFromScratch.jpg" alt="VEE Port Creation for a Custom Device">
               </div>
               <h3 class="training_title">VEE Port Creation for a Custom Device</h3>
               <p class="training_description">In this training, you will follow the typical steps followed by
               a Firmware developer integrating MICROEJ VEE on 
               a target device.
               </p>
               <a class="training_learn_more_link" href="trainingVEEPortDevFromScratch.html">Learn more</a>
            </div>
            </a>

            <a class="training_link" href="trainingPQT.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 2</div>
                  <img src="../_static/images/training/training_pqt.jpg" alt="PQT">
               </div>
               <h3 class="training_title">Qualify & Test your VEE Port</h3>
               <p class="training_description">In this training, you will learn how to validate the integration
               of MICROEJ VEE on a device using PQT (Port Qualification Tools).
               </p>
               <a class="training_learn_more_link" href="trainingPQT.html">Learn more</a>
            </div>
            </a>

            <a class="training_link" href="trainingDebugHardfault.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 3</div>
                  <img src="../_static/images/training/trainingDebugHardfault.jpg" alt="PQT">
               </div>
               <h3 class="training_title">Debug a HardFault</h3>
               <p class="training_description">In this training, you will get 
               insights on how to debug a hardfault.

               </p>
               <a class="training_learn_more_link" href="trainingDebugHardfault.html">Learn more</a>
            </div>
            </a>

         </div>

Graphical User Interface
========================

.. toctree::
   :hidden:

   trainingGuiRaster
   trainingDebugGUIFreeze


.. raw:: html

         <div class="training_items">

            <a class="training_link" href="trainingGuiRaster.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_gui.jpg" alt="Develop GUI with MicroEJ">
               </div>
               <h3 class="training_title">Develop GUI with MicroEJ</h3>
               <p class="training_description">In this training, you will learn how to develop GUIs using the
               MicroEJ Graphical Framework.
               </p>
               <a class="training_learn_more_link" href="trainingGuiRaster.html">Learn more</a>
            </div>
            </a>

            <a class="training_link" href="trainingDebugGUIFreeze.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 2</div>
                  <img src="../_static/images/training/trainingDebugGUIFreeze.jpg" alt="Debugging a GUI Application Freeze">
               </div>
               <h3 class="training_title">Debug a GUI Application Freeze</h3>
               <p class="training_description">In this training, you will get insights on 
               how to instrument a frozen GUI application.
               </p>
               <a class="training_learn_more_link" href="trainingDebugGUIFreeze.html">Learn more</a>
            </div>
            </a>

         </div>


Multi-Sandbox
=============

.. toctree::
   :hidden:
   
   trainingKernel
   trainingSandboxedApps

.. raw:: html

         <div class="training_items">

            <a class="training_link" href="trainingKernel.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_kernel.jpg" alt="GUI Application Development">
               </div>
               <h3 class="training_title">Kernel Development</h3>
               <p class="training_description">In this training, you will get an introduction to Kernel development
               in a Multi-Sandbox context.
               </p>
               <a class="training_learn_more_link" href="trainingKernel.html">Learn more</a>
            </div>
            </a>
            
            <a class="training_link" href="trainingSandboxedApps.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 2</div>
                  <img src="../_static/images/training/training_sandboxed_apps.jpg" alt="GUI Validation">
               </div>
               <h3 class="training_title">Sandboxed Applications Development</h3>
               <p class="training_description">In this training, you will get an introduction to Application development
               in a Multi-Sandbox context.
               </p>
               <a class="training_learn_more_link" href="trainingSandboxedApps.html">Learn more</a>
            </div>
            </a>

         </div>

Connectivity
============

.. toctree::
   :hidden:

   trainingNetworking

.. raw:: html

         <div class="training_items">

            <a class="training_link" href="trainingNetworking.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_networking.jpg" alt="Networking Basics">
               </div>
               <h3 class="training_title">Networking Basics</h3>
               <p class="training_description">In this training, you will discover 
               network connectivity with MicroEJ, illustrated by samples.
               </p>
               <a class="training_learn_more_link" href="trainingNetworking.html">Learn more</a>
            </div>
            </a>

            <a class="training_link" href="../ApplicationDeveloperGuide/dataSerializationLibraries.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 2</div>
                  <img src="../_static/images/training/code.jpg" alt="Explore Data Serialization Formats">
               </div>
               <h3 class="training_title">Explore Data Serialization Formats</h3>
               <p class="training_description">In this training, you will discover 
               some data serialization formats through basic code samples.
               </p>
               <a class="training_learn_more_link" href="../ApplicationDeveloperGuide/dataSerializationLibraries.html">Learn more</a>
            </div>
            </a>

         </div>

For DevOps
==========

.. toctree::
   :hidden:

   tutorialSetupBuildUsingJenkinsAndArtifactory

.. raw:: html

         <div class="training_items">

            <a class="training_link" href="tutorialSetupBuildUsingJenkinsAndArtifactory.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_ci_jenkins_artifactory.jpg" alt="Setup Build Using Jenkins And Artifactory">
               </div>
               <h3 class="training_title">Setup Build Using Jenkins And Artifactory</h3>
               <p class="training_description">In this training, you will learn how to setup an environment 
               for automating MicroEJ Module build and deployment using
               Jenkins, JFrog Artifactory and a Git platform.
               </p>
               <a class="training_learn_more_link" href="tutorialSetupBuildUsingJenkinsAndArtifactory.html">Learn more</a>
            </div>
            </a>

         </div>

Advanced
========

.. toctree::
   :hidden:

   trainingAsyncWorker

.. raw:: html

         <div class="training_items">

            <a class="training_link" href="trainingAsyncWorker.html">
            <div>
               <div class="training_image_container">
                  <div class="training_image_text">Course 1</div>
                  <img src="../_static/images/training/training_async_worker.jpg" alt="Async Worker">
               </div>
               <h3 class="training_title">Delegate Blocking Operations using Async Worker</h3>
               <p class="training_description">In this training, you will get an introduction to
               the Async Worker component that helps to delegate blocking operations 
               from VEE RTOS context to another RTOS task context.
               </p>
               <a class="training_learn_more_link" href="trainingAsyncWorker.html">Learn more</a>
            </div>
            </a>

         </div>

..
   | Copyright 2021-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

