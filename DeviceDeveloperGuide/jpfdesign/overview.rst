Process Overview
================

This section summarizes the steps required to build a PLATFORM and
obtain a binary file to deploy on a board.

`figure_title <#jpfdesignFig1>`__ shows the overall process. The first
three steps are performed within the PLATFORM_BUILDER. The remaining
steps are performed within the C IDE.

.. figure:: jpfdesign/images/process-overview5.svg
   :alt: Overall Process
   :width: 80.0%

   Overall Process

1. Step 1 consists in creating a new PLATFORM configuration project.
   This project describes the PLATFORM (XPF, metadata, etc.).

2. Step 2 allows you to select which modules available in XPF will be
   installed in the PLATFORM.

3. Step 3 builds the PLATFORM according to the choices made in steps 1
   and 2.

4. Step 4 compiles a MicroEJ application against the PLATFORM in order
   to obtain an application file to link in the BSP.

5. Step 5 consists in compiling the BSP and linking it with the MicroEJ
   application that was built previously, in step 4.

6. Step 6 is the final step: Deploy the binary application onto a board.
