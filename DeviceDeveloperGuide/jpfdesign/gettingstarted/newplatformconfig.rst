Create a New MicroEJ Platform Configuration
===========================================

The first step is to create a MicroEJ Platform configuration:

-  Select ``File > New > Project…``, open MicroEJ category and select
   MicroEJ Platform Project.

-  Click on Next. The Configure Target Architecture page allows to
   select the MicroEJ architecture that contains a minimal MicroEJ
   Platform and a set of compatible modules targeting a processor
   architecture and a compilation toolchain. This environment can be
   changed later.

   -  Click on Browse... to select one of the installed MicroEJ
      architecture.

   -  Check the Create from a platform reference implementation box to
      use one of the available implementation. Uncheck it if you want to
      provide your own implementation or if no reference implementation
      is available.

-  Click on Next. The Configure platform properties contains the
   identification of the MicroEJ Platform to create. Most fields are
   mandatory, you should therefore set them. Note that their values can
   be modified later on.

-  Click on Finish. A new project is being created containing a
   ``[name].platform`` file. A platform description editor shall then
   open.
