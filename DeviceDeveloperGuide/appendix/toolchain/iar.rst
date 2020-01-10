IAR Linker Specific Options
===========================

This section lists options that must be passed to IAR linker for
correctly linking the MicroEJ object file (``microejapp.o``) generated
by the SOAR.

``--no_range_reservations``
---------------------------

MicroEJ SOAR generates ELF absolute symbols to define some link-time
options (0 based values). By default, IAR linker allocates a 1 byte
section on the fly, which may cause silent sections placement side
effects or a section overlap error when multiple symbols are generated
with the same absolute value:

``Error[Lp023]: absolute placement (in [0x00000000-0x000000db]) overlaps with
                absolute symbol […]``

The option ``--no_range_reservations`` tells IAR linker to manage an
absolute symbol as described by the ELF specification.

``--diag_suppress=Lp029``
-------------------------

MicroEJ SOAR generates internal veneers that may be interpreted as
illegal code by IAR linker, causing the following error:

``Error[Lp029]: instruction validation failure in section
                "C:\xxx\microejapp.o[.text.__icetea__virtual___1xxx#1126]": nested IT blocks. Code
                in wrong mode?``

The option ``--diag_suppress=Lp029`` tells IAR linker to ignore
instructions validation errors.
