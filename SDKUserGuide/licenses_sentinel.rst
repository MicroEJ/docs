Sentinel License Management
---------------------------

This section contains instructions that will allow you to setup Sentinel environment and activate your license.

.. note::
	Require a MicroEJ Architecture 8.1.0 or higher (Production only).

.. _sentinel_rte_installation:

Install Runtime Environment (RTE)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

`Sentinel LDK Run-time Environment <https://docs.sentinel.thalesgroup.com/ldk/rte.htm>`__ is required on the end user's computer to enable your protected software to run by communicating with Sentinel protection keys. 

.. note:: 
	Sentinel LDK RTE installation requires administrator privileges but is not necessary to be installed on the developer workstation in case of floating licenses. (see this `documentation <https://docs.sentinel.thalesgroup.com/ldk/LDKdocs/SPNL/LDK_SLnP_Guide/Distributing/Distributing_LDK/RTE_when_required.htm>`__ for more details). 

First, get `Sentinel_RTE_Installation-1.0.0.zip <https://repository.microej.com/packages/sentinel/Sentinel_RTE_Installation-1.0.0.zip>`__ file. It contains installer for Windows, macOS and Linux.

Installation for Windows 
""""""""""""""""""""""""

- Get ``haspdinst_37102.exe`` file
- Type ``haspdinst_37102.exe -i`` in the command line. The installation or upgrade process is performed automatically. A message is displayed informing you that the Sentinel LDK Run-time Environment was successfully installed

.. note::
	To uninstall Sentinel RTE, type ``haspdinst_37102.exe -r`` in the command line. A message is displayed informing you that the Sentinel LDK Run-time Environment was successfully removed.

Installation for Linux 
""""""""""""""""""""""

Get ``aksusbd_37102-9.14.1.tar.gz`` file and extract it. The installation packages are in the directory ``pkg``, as root enter the following command:

- For RedHat, SUSE, or CentOS 64-bit Intel systems: ``rpm -i aksusbd-9.14-1.x86_64.rpm``
- For Ubuntu or Debian 64-bit Intel systems: ``dpkg -i aksusbd_9.14-1_amd64.deb``
- Copy ``aksusbd-9.14.1/haspvlib_37102.so`` and ``aksusbd-9.14.1/haspvlib_x86_64_37102.so`` to ``/var/hasplm`` directory

.. note::
	All install/uninstall commands must be executed with root rights. On Ubuntu, prefix the commands with the ``sudo`` command. On other Linux distributions, use the ``su`` utility to become root in the terminal window.

Installation for macOS
""""""""""""""""""""""

- Get ``Sentinel_Runtime_37102.tar`` file
- In ``SentinelRuntimeInstaller.framework/Versions/A/Resources/`` double-click on ``Sentinel_Runtime.dmg``
- Double-click the Install Sentinel Runtime Environment disk image icon. The installer wizard is launched
- Follow the instructions of the installer wizard until the installation is complete. The first time that you run Admin Control Center and submit configuration changes, ``hasplmd`` creates configuration files in ``/private/etc/hasplm/``

Activate Your Product 
~~~~~~~~~~~~~~~~~~~~~

Setup Your Environment
""""""""""""""""""""""

**Windows**

- Put ``MicroEJ_library\hasp_windows_x64_37102.dll`` file in the system folder (``%SystemRoot%\system32``) if you have administrator rights on your machine. Otherwise drop the ``hasp_windows_x64_37102.dll`` file beside ``java.exe`` executable of the Java Development Kit (JDK) used to launch the MICROEJ SDK

**Linux**

- Get ``MicroEJ_library/libhasp_linux_x86_64_37102.so`` file and copy it in a directory of your choice
- Set ``LD_LIBRARY_PATH`` variable with command ``export LD_LIBRARY_PATH=<your_directory>:$LD_LIBRARY_PATH``. This modification has to be setup at session startup  (e.g: using ``.bashrc`` file) to ensure that OS is properly configured before running the SDK

**Mac**

- Get ``MicroEJ_library/hasp_darwin_37102.dylib`` file and copy it in a directory of your choice
- Set ``DYLD_LIBRARY_PATH`` variable with command ``export DYLD_LIBRARY_PATH=<your_directory>:$DYLD_LIBRARY_PATH``. This modification has to be setup at session startup  (e.g: using ``.bashrc`` file) to ensure that OS is properly configured before running the SDK

.. _sentinel_activate_license:

Activate Your License
"""""""""""""""""""""

- On the workstation, open a web navigator and go to http://localhost:1947 (Sentinel Admin Control Center)
- Go to ``Sentinel key`` and click on ``fingerprint`` for Local key to download the C2V file
- Send this file to MicroEJ, MicroEJ will send you a V2C file
- Go back to Sentinel Admin Control Center
- Click on ``Update/Attach`` and upload the V2C file
- Apply it with `Apply` button

Check Activation with the Command Line Tool
"""""""""""""""""""""""""""""""""""""""""""

To verify access to the Sentinel license on the workstation where the SDK executes, run the debug tool as following:

#. Open a terminal
#. Change directory to a Production VEE Port
#. Execute the command:
   
    .. code:: console

       java -Djava.library.path=resources/os/[OS_NAME] -jar licenseManager/licenseManagerProduct.jar

    with ``OS_NAME`` set to ``Windows64`` for Windows OS, ``Linux64`` for Linux OS, ``Mac`` for macOS x86_64 (Intel chip) or ``MacA64`` for macOS aarch64 (M1 chip).

If your Sentinel license has been properly activated, you should get the following output:
   
.. code:: console

   [DEBUG] ===== MicroEJ Sentinel Debug Tool =====
   [DEBUG] => Detected Sentinel License Key ID: XXXXXXXXXXXXXXXX.
   [DEBUG] => Detected MicroEJ License valid until YYYY-MM-DD.
   [DEBUG] ===== SUCCESS =====

Troubleshooting
~~~~~~~~~~~~~~~

Sentinel API dynamic library not found (code 400)
"""""""""""""""""""""""""""""""""""""""""""""""""

The following error occurred when the library ``hasp_[os]_37102.[ext]`` has not been found. Please refer to :ref:`sentinel_rte_installation`. 
Specifically, if you are on Linux, check the library is readable with the command ``file libhasp_linux_x86_64_37102.so``.

Sentinel key not found (code 7)
"""""""""""""""""""""""""""""""

The following error occurred when there is no Sentinel license available. Go to http://localhost:1947/int/devices.html and check your Sentinel licenses. You should see the successfully installed license key:

.. figure:: images/sentinel_rte_installed_license_view.png
   :alt: Sentinel Installed License(s) View
   :align: center
   :scale: 75%

Otherwise, refer to :ref:`sentinel_activate_license`.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.