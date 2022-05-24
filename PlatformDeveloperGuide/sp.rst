.. _sp:

==================
Shielded Plug (SP)
==================


Principle
=========

The Shielded Plug (SP) library provides data segregation with a clear
publish-subscribe API. The data-sharing between modules uses the concept
of shared memory blocks, with introspection. The database is made of
blocks: chunks of RAM.

.. figure:: images/sp1.*
   :alt: A Shielded Plug Between Two Application (Java/C) Modules.
   :align: center
   :scale: 75%

   A Shielded Plug Between Two Application (Java/C) Modules.

.. list-table::
   :widths: 10 30

   * - **Documentation**
     - **Link**
   * - Java APIs
     - https://repository.microej.com/javadoc/microej_5.x/apis/ej/sp/package-summary.html
   * - Specification
     - http://e-s-r.net/download/specification/ESR-SPE-0014-SP-2.0-A.pdf
   * - Module
     - https://repository.microej.com/modules/ej/api/sp/


Functional Description
======================

The usage of the Shielded Plug (SP) starts with the definition of a
database. The implementation uses an
XML file description to describe the database; the syntax follows the
one proposed by the `[SP] specification <http://e-s-r.net/download/specification/ESR-SPE-0014-SP-2.0-A.pdf>`_.

Once this database is defined, it can be accessed within the MicroEJ
Application or the C application. The ``SP`` Foundation Library is
accessible from the :ref:`[SP] API Module <sp-api-mmm>`. This library contains
the classes and methods to read and write data in the database. The C header file ``sp.h`` available in the MicroEJ
Platform ``source/include`` folder contains the C functions for
accessing the database.

To embed the database in your binary file, the XML file description
must be processed by the :ref:`SP compiler <sp_compiler>`. This compiler generates a binary
file (``.o``) that will be linked to the overall application by the linker.
It also generates two descriptions of the block ID constants, one in
Java and one in C. These constants can be used by either the Java or the
C application modules.

.. _sp_compiler:

Shielded Plug Compiler
======================

A :ref:`MicroEJ tool <MicroEJToolsSection>` is available to launch the compiler. The tool
name is :guilabel:`Shielded Plug Compiler`. It outputs:

-  A description of the requested resources of the database as a binary
   file (``.o``) that will be linked to the overall application by the
   linker. It is an ELF format description that reserves both the
   necessary RAM and the necessary Flash memory for the Shielded Plug database.

-  Two descriptions, one in Java and one in C, of the block ID constants
   to be used by either Java or C application modules.

.. figure:: images/sp_flow.png
   :alt: Shielded Plug Compiler Process Overview
   :align: center
   :scale: 75%

   Shielded Plug Compiler Process Overview


Example
=======

Below is an example of using a database. The code that publishes the
data is written in C, and the code that receives the data is written in
Java. The data is transferred using two memory blocks. ``TEMP`` is a scalar
value, ``THERMOSTAT`` is a boolean.

Database Description
--------------------

The database is described as follows:

.. code:: xml

   <shieldedPlug>
       <database name="Forecast" id="0" immutable="true" version="1.0.0">
           <block id="1" name="TEMP" length="4" maxTasks="1"/>
           <block id="2" name="THERMOSTAT" length="4" maxTasks="1"/>
       </database>
   </shieldedPlug>

Java Code
---------

From the database description we can create an interface.

.. code:: java

   public interface Forecast {
      public static final int ID = 0;
      public static final int TEMP = 1;
      public static final int THERMOSTAT = 2;
   }

Below is the task that reads the published temperature and controls the
thermostat.

.. code:: java

   public void run(){
      ShieldedPlug database = ShieldedPlug.getDatabase(Forecast.ID);
      while (isRunning) {
         //reading the temperature every 30 seconds
         //and update thermostat status
         try {
            int temp = database.readInt(Forecast.TEMP);
            print(temp);
            //update the thermostat status
            database.writeInt(Forecast.THERMOSTAT,temp>tempLimit ? 0 : 1);
         }
         catch(EmptyBlockException e){
            print("Temperature not available");
         }
         sleep(30000);
      }
   }

C Code
------

Here is a C header that declares the constants defined in the XML
description of the database.

.. code:: c

   #define Forecast_ID 0
   #define Forecast_TEMP 1
   #define Forecast_THERMOSTAT 2

Below, the code shows the publication of the temperature and thermostat
controller task.

.. code:: c

   void temperaturePublication() {
      ShieldedPlug database = SP_getDatabase(Forecast_ID);
      int32_t temp = temperature();
      SP_write(database, Forecast_TEMP, &temp);
   }

   void thermostatTask(){
      int32_t thermostatOrder;
      ShieldedPlug database = SP_getDatabase(Forecast_ID);
      while(1){
         SP_waitFor(database, Forecast_THERMOSTAT);
         SP_read(database, Forecast_THERMOSTAT, &thermostatOrder);
         if(thermostatOrder == 0) {
            thermostatOFF();
         }
         else {
            thermostatON();
         }
      }
   }


Dependencies
============

-  ``LLSP_impl.h`` implementation (see :ref:`LLSP-API-SECTION`).


Installation
============

The ``[SP]`` library and its relative tools are an optional feature of the
platform. In the platform configuration file, check
:guilabel:`Java to C Interface` > :guilabel:`Shielded Plug` to install the library and
its relative tools.


.. _sp-api-mmm:

Use
===

The `Shielded Plug API Module <https://repository.microej.com/modules/ej/api/sp/>`_
must be added to the :ref:`module.ivy <mmm_module_description>` of the 
Application project.

::

   <dependency org="ej.api" name="sp" rev="2.0.2"/>

This library provides a set of options. Refer to the chapter
:ref:`application_options` which lists all available options.

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
