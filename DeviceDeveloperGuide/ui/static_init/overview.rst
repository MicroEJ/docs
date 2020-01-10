Principle
=========

MicroUI requires a configuration step (also called extension step) to
customize itself before MicroEJ application startup (see
`??? <#section_architecture>`__). This configuration step uses an XML
file. In order to save both runtime execution time and flash memory, the
file is processed by the Static MicroUI Initializer tool, avoiding the
need to process the XML configuration file at runtime. The tool
generates appropriate initialized objects directly within the MicroUI
library, as well as Java and C constants files for sharing MicroUI event
generator IDs.

This XML file (also called the initialization file) defines:

-  The MicroUI event generators that will exist in the application in
   relation to low level drivers that provide data to these event
   generators (see `??? <#section_input>`__).

-  Whether the application has a display; and if so, it provides its
   logical name.

-  Which fonts will be provided to the application.
