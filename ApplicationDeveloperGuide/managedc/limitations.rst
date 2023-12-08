.. _managedc.limitations:

Limitations
===========

The MicroEJ engine supports the version 1.0 of the `WebAssembly specification <https://www.w3.org/TR/wasm-core-1/>`_ with the following limitations.

Simulation
----------

Managed C code is not supported in simulation.

WebAssembly Module Memory
-------------------------

WebAssembly memory instance used page size of 8KB to fit embedded footprint concerns (not 64KB as specified `here <https://www.w3.org/TR/wasm-core-1/#memory-instances%E2%91%A0>`__ ).

WebAssembly stack memory manipulations are currently unsupported.

Unsupported WebAssembly Functionalities
---------------------------------------

- Only one function per WebAssembly module is supported.
- C functions are only permitted to call themselves (recursive functions are supported).
- WebAssembly globals, memory, tables, and elements are currently unsupported.

Supported WebAssembly Instructions
------------------------------------

Only a limited set of `WebAssembly instructions <https://www.w3.org/TR/wasm-core-1/#a7-index-of-instructions>`_ are supported:

* block
* br
* br_if
* else
* end
* i32.add
* i32.and
* i32.const
* i32.eq
* i32.eqz
* i32.ge_s
* i32.ge_u
* i32.gt_s
* i32.gt_u
* i32.lt_u
* i32.mul
* i32.ne
* i32.sub
* if
* local.get
* local.set
* local.tee
* loop
* return
* call

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
