.. _section.ivy.dependency.manager:

MicroEJ Module Manager
======================

Modern electronic device design involves many parts and teams to
collaborate to finally obtain a product to be sold on its market.
MicroEJ encourages modular design which involves various stake holders:
hardware engineers, UX designers, graphic designers, drivers/BSP
engineers, software engineers, etc.

Modular design is a design technique that emphasizes separating the
functionality of an application into independent, interchangeable
modules. Each module contains everything necessary to execute only one
aspect of the desired functionality. In order to have team members
collaborate internally within their team and with other teams, MicroEJ
provides a powerful modular design concept, with smart module
dependencies, controlled by the MicroEJ Module Manager (MMM). MMM frees
engineers from the difficult task of computing module dependencies.
Engineers specify the bare minimum description of the module
requirements.

MMM is based on of the following tools:

-  Apache Ivy (:http:`http://ant.apache.org/ivy`) for dependencies
   resolution and module publication;

-  Apache EasyAnt
   (:http:`https://ant.apache.org/easyant/history/trunk/reference.html`) for
   module build from source code.

MMM provides a non ambiguous semantic for dependencies
resolution. Please consult the MMM specification available on
:http:`https://developer.microej.com/packages/documentation/TLT-0831-SPE-MicroEJModuleManager-2.0-C.pdf`.

An Ivy configuration file (``module.ivy``) must be provided at the root
of each MicroEJ project to solve classpath dependencies. Multiple Ivy
configuration file templates are available depending on the kind of
MicroEJ Application created.

.. code:: xml

   <ivy-module version="2.0" xmlns:ea="http://www.easyant.org" xmlns:m="http://ant.apache.org/ivy/extra" 
                             xmlns:ej="https://developer.microej.com" ej:version="2.0.0"> 
       <info organisation="[organisation]" module="[name]" status="integration" revision="[version]">
           <ea:build organisation="com.is2t.easyant.buildtypes" module="[buildtype_name]" revision="[buildtype_version]">
               <ea:property name="[buildoption_name]" value="[buildoption_value]"/>
           </ea:build>
       </info>
       
       <configurations defaultconfmapping="default->default;provided->provided">
           <conf name="default" visibility="public"/>
           <conf name="provided" visibility="public"/>
           <conf name="documentation" visibility="public"/>
           <conf name="source" visibility="public"/>
           <conf name="dist" visibility="public"/>
           <conf name="test" visibility="private"/>
       </configurations>
       
       <publications>
       </publications>
       
       <dependencies>
         <dependency org="[dep_organisation]" name="[dep_name]" rev="[dep_version]"/>
       </dependencies>
   </ivy-module>        

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
