MicroEJ SDK production architecture and license usage
=====================================================

MicroEJ provides two types of licenses :

- Evaluation
- Production

Both of them have a different way to be activated.

Activate an evaluation license
------------------------------

#. Get your UID

    - Start MicroEJ SDK.
    - Select a workspace. If you are not familiar with Eclipse workspaces, select the default one and press OK.
    - Select the MicroEJ repository where to import MicroEJ architectures from. If you are not familiar with MicroEJ repositories, select the default one and press OK.
    - Wait until MicroEJ Repository is initialized. This may take some time.
    - Select the :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Architectures` menu.
    - Click on one of the available architectures and press :guilabel:`Get UID`.
    - Copy the UID. It will be needed when requesting a license.
    
#. Generate your Activation Key

    - Go to `license.microej.com <https://license.microej.com/>`_.
    - Click on :guilabel:`Create a new account` link.
    - Create your account with a valid email address. You will receive a confirmation email a few minutes after. Click on the confirmation link in the email and login with your new account.
    - Click on :guilabel:`Activate a License`.
    - Set :guilabel:`Product P/N:` to ``9PEVNLDBU6IJ``.
    - Set :guilabel:`UID:` to the UID you generated before.
    - Click on :guilabel:`Activate`.
    - The license is being activated. You should receive your activation by email in less than 5 minutes. If not, please contact support@microej.com.
    - Once received by email, save the attached zip file that contains your activation key.

#. Activate MicroEJ SDK

    - Go back to MicroEJ SDK.
    - Select the :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` menu.
    - Press :guilabel:`Add...`.
    - Browse the previously downloaded activation key archive file.
    - Press OK. A new license is successfully installed.
    - Go to Architectures sub-menu and check that all architectures are now activated (green check).
    - Your MicroEJ SDK is successfully activated.

Activate a production license (USB dongle)
------------------------------------------

If your USB dongle has been provided to you by your sales representative, it may be a pre-activated dongle, then skip steps 1 and 2.

#. Generate your Activation Key

    - Go to `license.microej.com <https://license.microej.com/>`_.
    - Click on :guilabel:`Create a new account` link.
    - Create your account with a valid email address. You will receive a confirmation email a few minutes after. Click on the confirmation link in the email and login with your new account.
    - Click on :guilabel:`Activate a License`.
    - Set :guilabel:`Product P/N:` to **The P/N on the activation certificate**.
    - Enter your UID: serial number printed on the USB dongle label (8 alphanumeric char.).
    - Click on :guilabel:`Activate` and check confirmation message.
    - Click on :guilabel:`Confirm your registration`.
    - Enter the **Registration Code provided on the activation certificate**.
    - Click on :guilabel:`Submit`.
    - Your Activation Key will be sent to you by email as soon as it is available (12 business hours max.).

        - You can also check the :guilabel:`My Products` page to verify your product registration status, the Activation Key availability and to download the Activation Key when available.

#. Product Activation

    Once the Activation Key is available, update your USB dongle as follow:

    - Download and save the Activation Key ZIP file.
    - Unzip the ``Activation Key`` file and enter the directory just created by your ZIP extraction tool.
    - Insert the USB dongle into a USB port of a Windows computer.
    - Launch the executable program.
    - Click on the :guilabel:`Update` button (no password needed)
    - USB dongle will be updated when “Successfully updated” dialog box appears.

#. Import MicroEJ MEJ32 production architecture

    If you have a pre-activated dongle please contact support@microej.com with a valid account on `license.microej.com <https://license.microej.com/>`_ to get a direct link to the production architectures.

    - Go to `license.microej.com <https://license.microej.com/>`_
    - Go to :guilabel:`My Product`
    - Download and install the production architecture matching your SDK version (a zip file contains the architectures and a readme file the instructions to import them). If your required architecture matching your hardware architecture (ISA) and C compiler is not listed on `license.microej.com <https://license.microej.com/>`_, please contact support@microej.com.

#. Check activation on MicroEJ SDK

    - Go back to MicroEJ SDK.
    - Select the :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` menu.
    - Go to the :guilabel:`Architectures` sub-menu and check that all production architectures are now activated (green check).
    - Your MicroEJ SDK is successfully activated.

Troubleshooting
---------------

#. If you did not received an activation certificate, please contact the support@microej.com.
#. Check that you have your Activation Key.
#. Check that your dongle is activated.
#. In the SDK, in :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ`,

    #. Check that the dongle appears on the ``Licenses`` list.

        - If not, check that the dongle is plugged in your computer. If using Linux `please configure the USB rules <https://forum.microej.com/t/how-can-i-use-a-microej-usb-dongle-on-linux/223/2>`_.

    #. In :guilabel:`Architectures` tab check that some Production Architectures are available.

#. Errors may occurs when launching the activation tool from a server mounted FS, copy it to your desktop before.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
