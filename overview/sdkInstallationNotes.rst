Advanced Installation Notes
---------------------------

-----------------
Windows Specifics
-----------------

If you are using Windows Defender as your default antivirus software,
MicroEJ Studio or SDK may be slow down as it manipulates lots of JAR
files (which are ZIP files) that are regularly analyzed.

To improve MicroEJ Studio or SDK experience, please find below a list of
folders that should be excluded from Windows Defender monitoring:

-  ``%USERPROFILE%\.eclipse``
-  ``%USERPROFILE%\.ivy2``
-  ``%USERPROFILE%\.microej``
-  ``%USERPROFILE%\.p2``
-  ``%USERPROFILE%\AppData\Local\Temp\microej``
-  ``C:\Program Files\MicroEJ``
-  your workspace(s) folder(s)

The exclusion page is available in the ``Settings`` application
(:guilabel:`Windows Security` > :guilabel:`Virus & threat protection` > :guilabel:`Manage settings` > :guilabel:`Exclusions` > :guilabel:`Add or remove exclusions`).

---------------
Linux Specifics
---------------

Starting MicroEJ Studio or SDK on a linux distribution may produce
troubles such as missing content pages. This is related to incomplete
Eclipse SWT configuration (see `Eclipse GTK wiki
page <https://wiki.eclipse.org/SWT/Devel/Gtk/GtkVersion>`__).

One solution is to configure Eclipse as follows:

-  Add the next lines to ``MicroEK-[SDK|Studio].ini``, before
   ``-vmargs`` argument:

   ::

      --launcher.GTK_Version 2

-  Ensure GTK is correctly installed (``libwebkitgtk`` packet)
-  Configure the following environment variables

   ::

       MOZILLA_FIVE_HOME=/usr/lib/mozilla
       LD_LIBRARY_PATH=${MOZILLA_FIVE_HOME}:${LD_LIBRARY_PATH}

-  Restart MicroEJ Studio/SDK
-  Check there is not more SWT/MOZILLA related errors
   (:guilabel:`Window` > :guilabel:`Show View` > :guilabel:`Other...` > :guilabel:`General` > :guilabel:`Error Log`)



..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
