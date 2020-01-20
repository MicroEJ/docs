Link
====

Several sections are defined by the MicroEJ core engine. Each section
must be linked by the third-party linker.

.. table:: Linker Sections

   +-------------------+-----------------------------+---------+---------+
   | Section name      | Aim                         | L       | Al      |
   |                   |                             | ocation | ignment |
   |                   |                             |         | (in     |
   |                   |                             |         | bytes)  |
   +===================+=============================+=========+=========+
   | ``.bss.fea        | Resident applications       | RW      | 4       |
   | tures.installed`` | statics                     |         |         |
   +-------------------+-----------------------------+---------+---------+
   | ``.bss.soar``     | Application static          | RW      | 8       |
   +-------------------+-----------------------------+---------+---------+
   | ``.bss            | Application threads stack   | RW      | 8       |
   | .vm.stacks.java`` | blocks                      |         |         |
   +-------------------+-----------------------------+---------+---------+
   | ``ICETEA_HEAP``   | MicroEJ core engine         | I       | 8       |
   |                   | internal heap               | nternal |         |
   |                   |                             | RW      |         |
   +-------------------+-----------------------------+---------+---------+
   | ``_java_heap``    | Application heap            | RW      | 4       |
   +-------------------+-----------------------------+---------+---------+
   | ``                | Application immortal heap   | RW      | 4       |
   | _java_immortals`` |                             |         |         |
   +-------------------+-----------------------------+---------+---------+
   | ``.r              | Application resources       | RO      | 16      |
   | odata.resources`` |                             |         |         |
   +-------------------+-----------------------------+---------+---------+
   | ``.rodat          | Resident applications code  | RO      | 4       |
   | a.soar.features`` | and resources               |         |         |
   +-------------------+-----------------------------+---------+---------+
   | ``.shieldedplug`` | Shielded Plug data          | RO      | 4       |
   +-------------------+-----------------------------+---------+---------+
   | ``.text.soar``    | Application and library     | RO      | 16      |
   |                   | code                        |         |         |
   +-------------------+-----------------------------+---------+---------+
