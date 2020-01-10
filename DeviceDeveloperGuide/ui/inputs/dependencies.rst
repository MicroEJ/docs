Dependencies
============

-  MicroUI module (see `??? <#section_microui>`__)

-  Static MicroUI initialization step (see
   `??? <#section_static_init>`__). This step generates a header file
   which contains some unique event generator IDs. These IDs must be
   used in the BSP to make the link between the input devices drivers
   and the MicroUI ``Event Generator``\ s.

-  ``LLINPUT_impl.h`` implementation (see
   `??? <#LLINPUT-API-SECTION>`__).
