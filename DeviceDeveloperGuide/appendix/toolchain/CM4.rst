ARM Cortex-M4
=============

.. table:: ARM Cortex-M4 Compilers

   +---------------------+----------+-------------------------------------+
   | Compiler            | Version  | Flags and Options                   |
   +=====================+==========+=====================================+
   | Keil uVision        | 5.18.0.0 | ``--cpu Cortex-M4.fp --a            |
   |                     |          | pcs=/hardfp --fpmode=ieee_no_fenv`` |
   +---------------------+----------+-------------------------------------+
   | GCC                 | 4.8      | ``-mabi=aapcs -mcpu=                |
   |                     |          | cortex-m4 -mlittle-endian -mfpu=fpv |
   |                     |          | 4-sp-d16 -mfloat-abi=hard -mthumb`` |
   +---------------------+----------+-------------------------------------+
   | IAR Embedded        | 7.4      | ``--cpu Cortex-M4F --fpu VFPv4_sp`` |
   | Workbench for ARM   | 0.3.8938 |                                     |
   +---------------------+----------+-------------------------------------+

Note: Since MicroEJ 4.0, Cortex-M4 architectures are compiled using
``hardfp`` convention call.
