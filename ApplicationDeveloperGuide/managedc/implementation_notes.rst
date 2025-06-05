.. _managedc.implementation_notes:

===========================
Wasm Implementation Notes
===========================

.. _managedc.implementation_notes.instructions.supported:

------------------------
Supported Instructions
------------------------

The MicroEJ engine supports the version 1.0 of the `Wasm specification <https://www.w3.org/TR/wasm-core-1/>`_ with the following additionnal instsructions and limitations.

~~~~~~~~~~~~~~~~~~~~~~~~~
Additionnal Instructions
~~~~~~~~~~~~~~~~~~~~~~~~~

+++++++++++++++++++
New Sign-extending
+++++++++++++++++++

* ``i32.extend8_s``: extend a signed 8-bit integer to a 32-bit integer
* ``i32.extend16_s``: extend a signed 16-bit integer to a 32-bit integer
* ``i64.extend8_s``: extend a signed 8-bit integer to a 64-bit integer
* ``i64.extend16_s``: extend a signed 16-bit integer to a 64-bit integer
* ``i64.extend32_s``: extend a signed 32-bit integer to a 64-bit integer

+++++++++++++
Bulk Memory
+++++++++++++

* ``memory.init``: copy a region from a data segment
* ``memory.copy``: copy from one region of linear memory to another
* ``memory.fill``: fill a region of linear memory with a given byte value
* ``data.drop``: discard the data in an data segment

++++++++++++++++++++++++++++++++++++
Atomic Memory Accesses Load/Store
++++++++++++++++++++++++++++++++++++

* ``i32.atomic.load8_u``: atomically load 1 byte and zero-extend i8 to i32
* ``i32.atomic.load16_u``: atomically load 2 bytes and zero-extend i16 to i32
* ``i32.atomic.load``: atomically load 4 bytes as i32
* ``i64.atomic.load8_u``: atomically load 1 byte and zero-extend i8 to i64
* ``i64.atomic.load16_u``: atomically load 2 bytes and zero-extend i16 to i64
* ``i64.atomic.load32_u``: atomically load 4 bytes and zero-extend i32 to i64
* ``i64.atomic.load``: atomically load 8 bytes as i64
* ``i32.atomic.store8``: wrap i32 to i8 and atomically store 1 byte
* ``i32.atomic.store16``: wrap i32 to i16 and atomically store 2 bytes
* ``i32.atomic.store``: (no conversion) atomically store 4 bytes
* ``i64.atomic.store8``: wrap i64 to i8 and atomically store 1 byte
* ``i64.atomic.store16``: wrap i64 to i16 and atomically store 2 bytes
* ``i64.atomic.store32``: wrap i64 to i32 and atomically store 4 bytes
* ``i64.atomic.store``: (no conversion) atomically store 8 bytes

++++++++++++++++++++++++++++++++++++++++++
Atomic Memory Accesses Read-Modify-Write
++++++++++++++++++++++++++++++++++++++++++

* ``i32.atomic.rmw8.add_u``: Performs an atomic addition of an i32 value to an 8-bit unsigned integer in memory and returns the original value zero-extended to i32.
* ``i32.atomic.rmw16.add_u``: Performs an atomic addition of an i32 value to a 16-bit unsigned integer and returns the original value zero-extended to i32.
* ``i32.atomic.rmw.add``: Performs an atomic addition of two i32 values and returns the original 32-bit value.
* ``i64.atomic.rmw8.add_u``: Performs an atomic addition of an i64 value to an 8-bit unsigned integer and returns the original value zero-extended to i64.
* ``i64.atomic.rmw16.add_u``: Performs an atomic addition of an i64 value to a 16-bit unsigned integer and returns the original value zero-extended to i64.
* ``i64.atomic.rmw32.add_u``: Performs an atomic addition of an i64 value to a 32-bit unsigned integer and returns the original value zero-extended to i64.
* ``i64.atomic.rmw.add``: Performs an atomic addition of two i64 values and returns the original 64-bit value.
* ``i32.atomic.rmw8.sub_u``: Performs an atomic subtraction of an i32 value from an 8-bit unsigned integer and returns the original value zero-extended to i32.
* ``i32.atomic.rmw16.sub_u``: Performs an atomic subtraction of an i32 value from a 16-bit unsigned integer and returns the original value zero-extended to i32.
* ``i32.atomic.rmw.sub``: Performs an atomic subtraction of two i32 values and returns the original 32-bit value.
* ``i64.atomic.rmw8.sub_u``: Performs an atomic subtraction of an i64 value from an 8-bit unsigned integer and returns the original value zero-extended to i64.
* ``i64.atomic.rmw16.sub_u``: Performs an atomic subtraction of an i64 value from a 16-bit unsigned integer and returns the original value zero-extended to i64.
* ``i64.atomic.rmw32.sub_u``: Performs an atomic subtraction of an i64 value from a 32-bit unsigned integer and returns the original value zero-extended to i64.
* ``i64.atomic.rmw.sub``: Performs an atomic subtraction of two i64 values and returns the original 64-bit value.
* ``i32.atomic.rmw8.and_u``: Performs an atomic bitwise AND on an 8-bit unsigned integer and an i32 value; returns the original value zero-extended to i32.
* ``i32.atomic.rmw16.and_u``: Performs an atomic bitwise AND on a 16-bit unsigned integer and an i32 value; returns the original value zero-extended to i32.
* ``i32.atomic.rmw.and``: Performs an atomic bitwise AND on two i32 values and returns the original 32-bit value.
* ``i64.atomic.rmw8.and_u``: Performs an atomic bitwise AND on an 8-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw16.and_u``: Performs an atomic bitwise AND on a 16-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw32.and_u``: Performs an atomic bitwise AND on a 32-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw.and``: Performs an atomic bitwise AND on two i64 values and returns the original 64-bit value.
* ``i32.atomic.rmw8.or_u``: Performs an atomic bitwise OR on an 8-bit unsigned integer and an i32 value; returns the original value zero-extended to i32.
* ``i32.atomic.rmw16.or_u``: Performs an atomic bitwise OR on a 16-bit unsigned integer and an i32 value; returns the original value zero-extended to i32.
* ``i32.atomic.rmw.or``: Performs an atomic bitwise OR on two i32 values and returns the original 32-bit value.
* ``i64.atomic.rmw8.or_u``: Performs an atomic bitwise OR on an 8-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw16.or_u``: Performs an atomic bitwise OR on a 16-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw32.or_u``: Performs an atomic bitwise OR on a 32-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw.or``: Performs an atomic bitwise OR on two i64 values and returns the original 64-bit value.
* ``i32.atomic.rmw8.xor_u``: Performs an atomic bitwise XOR on an 8-bit unsigned integer and an i32 value; returns the original value zero-extended to i32.
* ``i32.atomic.rmw16.xor_u``: Performs an atomic bitwise XOR on a 16-bit unsigned integer and an i32 value; returns the original value zero-extended to i32.
* ``i32.atomic.rmw.xor``: Performs an atomic bitwise XOR on two i32 values and returns the original 32-bit value.
* ``i64.atomic.rmw8.xor_u``: Performs an atomic bitwise XOR on an 8-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw16.xor_u``: Performs an atomic bitwise XOR on a 16-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw32.xor_u``: Performs an atomic bitwise XOR on a 32-bit unsigned integer and an i64 value; returns the original value zero-extended to i64.
* ``i64.atomic.rmw.xor``: Performs an atomic bitwise XOR on two i64 values and returns the original 64-bit value.
* ``i32.atomic.rmw8.xchg_u``: Performs an atomic exchange between an 8-bit unsigned memory value and an i32 operand; returns the original value zero-extended to i32.
* ``i32.atomic.rmw8.xchg_u``: Performs an atomic exchange: stores the low 8 bits of an i32 value into memory, and returns the previous 8-bit value zero-extended to i32.
* ``i32.atomic.rmw16.xchg_u``: Performs an atomic exchange: stores the low 16 bits of an i32 value into memory, and returns the previous 16-bit value zero-extended to i32.
* ``i32.atomic.rmw.xchg``: Performs an atomic exchange of a 32-bit i32 value in memory and returns the original value.
* ``i64.atomic.rmw8.xchg_u``: Performs an atomic exchange: stores the low 8 bits of an i64 value into memory , and returns the previous 8-bit value zero-extended to i64.
* ``i64.atomic.rmw16.xchg_u``: Performs an atomic exchange: stores the low 16 bits of an i64 value into memory, and returns the previous 16-bit value zero-extended to i64.
* ``i64.atomic.rmw32.xchg_u``: Performs an atomic exchange: stores the low 32 bits of an i64 value into memory, and returns the previous 32-bit value zero-extended to i64.
* ``i64.atomic.rmw.xchg``: Performs an atomic exchange of a 64-bit i64 value in memory and returns the original value.

++++++++++++++++++++++++++++++++++++++++
Atomic Memory Accesses Compare Exchange
++++++++++++++++++++++++++++++++++++++++

* ``i32.atomic.rmw8.cmpxchg_u``: Compares the low 8 bits of the i32 expected value to the 8-bit memory value; if equal, stores the low 8 bits of the replacement value. Returns the original 8-bit memory value zero-extended to i32.
* ``i32.atomic.rmw16.cmpxchg_u``: Compares the low 16 bits of the i32 expected value to the 16-bit memory value; if equal, stores the low 16 bits of the replacement value. Returns the original 16-bit value zero-extended to i32.
* ``i32.atomic.rmw.cmpxchg``: Compares the full 32-bit i32 expected value to the 32-bit memory value; if equal, stores the 32-bit replacement. Returns the original 32-bit value.
* ``i64.atomic.rmw8.cmpxchg_u``: Compares the low 8 bits of the i64 expected value to the 8-bit memory value; if equal, stores the low 8 bits of the replacement value. Returns the original 8-bit value zero-extended to i64.
* ``i64.atomic.rmw16.cmpxchg_u``: Compares the low 16 bits of the i64 expected value to the 16-bit memory value; if equal, stores the low 16 bits of the replacement value. Returns the original 16-bit value zero-extended to i64.
* ``i64.atomic.rmw32.cmpxchg_u``: Compares the low 32 bits of the i64 expected value to the 32-bit memory value; if equal, stores the low 32 bits of the replacement value. Returns the original 32-bit value zero-extended to i64.
* ``i64.atomic.rmw.cmpxchg``: Compares the full 64-bit i64 expected value to the memory value; if equal, stores the full 64-bit replacement. Returns the original 64-bit value.

++++++++++++++++++++++++++++++++++++++++++++++++++
Atomic Memory Accesses Wait and Notify operators
++++++++++++++++++++++++++++++++++++++++++++++++++

* ``memory.atomic.wait32``: load i32 value, compare to expected (as i32), and wait for notify at same address
* ``memory.atomic.wait64``: load i64 value, compare to expected (as i64), and wait for notify at same address
* ``memory.atomic.notify``: notify count threads waiting on the given address via memory.atomic.wait32 or memory.atomic.wait64

.. _managedc.implementation_notes.instructions.partially_supported:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Partially Supported WebAssembly Instructions 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* ``memory_grow``: instruction always returns the previous size but does not expand the Wasm linear memory. See :ref:`managedc.linear.memory` for more details.
* ``i32.atomic.load*``, ``i32.atomic.store*``, ``i64.atomic.load*`` and ``i64.atomic.store*``: instructions do not check for unaligned memory access.

.. _managedc.implementation_notes.traps:

----------------------------
WebAssembly Trap Conditions
----------------------------

This document lists all WebAssembly instructions that can trigger traps, the conditions under which they occur and the Java exception class that will be thrown.

.. table::
   :widths: 57 15 28

   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | Instruction                                                                                                                                            | Trap Condition                    | Java Exception                                                             |
   +========================================================================================================================================================+===================================+============================================================================+
   | ``unreachable``                                                                                                                                        | Always traps                      | **java.lang.AssertionError**                                               |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | ``memory.copy``                                                                                                                                        | Out-of-bounds access              | **java.lang.IndexOutOfBoundsException**                                    |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | ``memory.fill``                                                                                                                                        | Out-of-bounds access              | **java.lang.ArrayIndexOutOfBoundsException**                               |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | ``memory.init``                                                                                                                                        | Out-of-bounds access              | **java.io.IOException or java.lang.IndexOutOfBoundsException**             |
   +                                                                                                                                                        +-----------------------------------+----------------------------------------------------------------------------+
   |                                                                                                                                                        | Invalid data segment index        | **java.io.IOException**                                                    |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | ``call_indirect``                                                                                                                                      | undefined table element           | **java.lang.IllegalArgumentException or java.lang.NullPointerException**   |
   +                                                                                                                                                        +-----------------------------------+----------------------------------------------------------------------------+
   |                                                                                                                                                        | Function signature mismatch       | **java.lang.IllegalArgumentException**                                     |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | ``i32.div_s``, ``i32.div_u``, ``i64.div_s``, ``i64.div_u``, ``i32.rem_s``, ``i32.rem_u``, ``i64.rem_s``, ``i64.rem_u``                                 | Division by zero                  | **java.lang.ArithmeticException**                                          |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | ``i32.load``, ``i32.load8_s``, ``i32.load8_u``, ``i32.load16_s``, ``i32.load16_u``, ``i64.load``, ``i64.load8_s``, ``i64.load8_u``, ``i64.load16_s``,  | Out-of-bounds access              | **java.lang.ArrayIndexOutOfBoundsException**                               |
   | ``i64.load16_u``, ``i64.load32_s``, ``i64.load32_u``, ``i32.store``, ``i32.store8``, ``i32.store16``, ``i64.store``, ``i64.store8``, ``i64.store16``,  | (address + offset ≥ memory size)  |                                                                            |
   | ``i64.store32``, ``f32.load``, ``f64.load``, ``f32.store``, ``f64.store``                                                                              |                                   |                                                                            |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+
   | ``i32.atomic.rmw.add``, ``i32.atomic.rmw8.add_u``, ``i32.atomic.rmw16.add_u``, ``i64.atomic.rmw.add``, ``i64.atomic.rmw8.add_u``,                      | Out-of-bounds access              | **java.lang.ArrayIndexOutOfBoundsException**                               |
   +                                                                                                                                                        +-----------------------------------+----------------------------------------------------------------------------+
   | ``i64.atomic.rmw16.add_u``, ``i64.atomic.rmw32.add_u``,                                                                                                | misaligned address                | **java.lang.IllegalArgumentException**                                     |
   | ``i32.atomic.rmw8.sub_u``, ``i32.atomic.rmw16.sub_u``, ``i32.atomic.rmw.sub``, ``i64.atomic.rmw8.sub_u``, ``i64.atomic.rmw16.sub_u``,                  |                                   |                                                                            |
   | ``i64.atomic.rmw32.sub_u``, ``i64.atomic.rmw.sub``,                                                                                                    |                                   |                                                                            |
   | ``i32.atomic.rmw8.and_u``, ``i32.atomic.rmw16.and_u``, ``i32.atomic.rmw.and``, ``i64.atomic.rmw8.and_u``, ``i64.atomic.rmw16.and_u``,                  |                                   |                                                                            |
   | ``i64.atomic.rmw32.and_u``, ``i64.atomic.rmw.and``,                                                                                                    |                                   |                                                                            |
   | ``i32.atomic.rmw8.or_u``, ``i32.atomic.rmw16.or_u``, ``i32.atomic.rmw.or``, ``i64.atomic.rmw8.or_u``, ``i64.atomic.rmw16.or_u``,                       |                                   |                                                                            |
   | ``i64.atomic.rmw32.or_u``, ``i64.atomic.rmw.or``,                                                                                                      |                                   |                                                                            |
   | ``i32.atomic.rmw8.xor_u``, ``i32.atomic.rmw16.xor_u``, ``i32.atomic.rmw.xor``, ``i64.atomic.rmw8.xor_u``, ``i64.atomic.rmw16.xor_u``,                  |                                   |                                                                            |
   | ``i64.atomic.rmw32.xor_u``, ``i64.atomic.rmw.xor``,                                                                                                    |                                   |                                                                            |
   | ``i32.atomic.rmw8.xchg_u``, ``i32.atomic.rmw8.xchg_u``, ``i32.atomic.rmw16.xchg_u``, ``i32.atomic.rmw.xchg``, ``i64.atomic.rmw8.xchg_u``,              |                                   |                                                                            |
   | ``i64.atomic.rmw16.xchg_u``, ``i64.atomic.rmw32.xchg_u``, ``i64.atomic.rmw.xchg``,                                                                     |                                   |                                                                            |
   | ``i32.atomic.rmw.cmpxchg``, ``i32.atomic.rmw8.cmpxchg_u``, ``i32.atomic.rmw16.cmpxchg_u``, ``i64.atomic.rmw.cmpxchg``, ``i64.atomic.rmw8.cmpxchg_u``,  |                                   |                                                                            |
   | ``i64.atomic.rmw16.cmpxchg_u``, ``i64.atomic.rmw32.cmpxchg_u``,                                                                                        |                                   |                                                                            |
   | ``memory.atomic.wait32``, ``memory.atomic.wait64``, ``memory.atomic.notify``                                                                           |                                   |                                                                            |
   +--------------------------------------------------------------------------------------------------------------------------------------------------------+-----------------------------------+----------------------------------------------------------------------------+




..
   | Copyright 2023-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
