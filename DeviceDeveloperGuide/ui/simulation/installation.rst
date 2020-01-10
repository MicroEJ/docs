.. _fp_installation:

Installation
============

Front Panel is an additional module for MicroUI library. When the
MicroUI module is installed, install this module in order to be able to
simulate UI drawings on the simulator.

In the platform configuration file, check ``GROUP.UI`` >
``MODULE.FRONTPANEL.PNAME`` to install the Front Panel module. When
checked, the properties file ``MODULE.FRONTPANEL.NAME`` >
``MODULE.FRONTPANEL.NAME
            .properties`` is required during platform creation to
configure the module. This configuration step is used to identify and
configure the front panel.

The properties file must / can contain the following properties:

-  ``project.name`` [mandatory]: Defines the name of the front panel
   project (same workspace as the platform configuration project). If
   the project name does not exist, a new project will be created.

-  ``fpFile.name`` [optional, default value is "" (*empty*)]: Defines
   the front panel file (*.fp) to export (in case "project.name"
   contains several fp files). If empty or unspecified, the first ".fp"
   file found will be exported.

-  ``hardwareImageDecoders.list`` [optional, default value is ""
   (*empty*)]: Defines the available list of additional image decoders
   provided by the hardware. Use comma (',') to specify several decoders
   among this list: bmp, jpg, jpeg, gif, png. If empty or unspecified,
   no image decoder is added.
