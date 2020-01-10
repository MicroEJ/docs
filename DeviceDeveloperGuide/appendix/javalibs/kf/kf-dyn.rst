.. _kf-dyn:

Loading Features Dynamically
============================

Features may be statically embedded with the Kernel or dynamically built
against a Kernel. To build a Feature binary file, select
``Build Dynamic Feature``\ EMBJPF\ ``Execution`` tab. The generated file
can be dynamically loaded by the Kernel runtime using
``ej.kf.Kernel.load(InputStream)``.
