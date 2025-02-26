.. _ui-internationalization:

Internationalization
====================

Using PO Files
--------------

- PO files are a good way to handle Internationalization.
- Documentation is available `here <https://www.gnu.org/software/gettext/manual/gettext.html#PO-Files>`__.
- In this example, let's create two PO files for two different languages(English and Portuguese) and add them to **resources/nls**.

  ``Labels_en_US.po``:

  .. code:: po

    msgid ""
    msgstr ""
    "Language: en_US\n"
    "Language-Team: English\n"
    "MIME-Version: 1.0\n"
    "Content-Type: text/plain; charset=UTF-8\n"

    msgid "Label1"
    msgstr "My label 1"

    msgid "Label2"
    msgstr "My label 2"

  ``Labels_pt_BR.po``:

  .. code:: po

    msgid ""
    msgstr ""
    "Language: pt_BR\n"
    "Language-Team: Portuguese\n"
    "MIME-Version: 1.0\n"
    "Content-Type: text/plain; charset=UTF-8\n"

    msgid "Label1"
    msgstr "Minha label 1"

    msgid "Label2"
    msgstr "Minha label 2"

- These PO files have to be converted to be usable by the application.
- In order to let the build system know which PO files to process, they must be referenced in MicroEJ Classpath using a ``myapp.nls.list`` file.

Configuring NLS in MicroEJ
--------------------------

- First add those two dependencies to the module.ivy of your projet:

  .. code:: xml

    <dependency org="ej.library.runtime" name="nls" rev="4.0.0"/> 
    <dependency org="com.microej.library.runtime" name="binary-nls" rev="3.0.0"/>

- Then, let's create a ``myapp.nls.list`` file, and put it in the **src/main/resources/list** folder. The file looks like this:

  .. code::

    com.mycompany.myapp.generated.Labels

Usage
-----

- Import the interface set in the ``myapp.nls.list`` file:
  
  .. code::

    import com.mycompany.myapp.generated.Labels;

- Print the available locales:

  .. code:: java
    
    for (String locale : Labels.NLS.getAvailableLocales()) {
        System.out.println(locale);
    }

- Print the current locale:

  .. code:: java
    
    System.out.println(Labels.NLS.getCurrentLocale());

- Change the current locale:

  .. code:: java
    
    Labels.NLS.setCurrentLocale("pt_BR"); 

- Finally, put a message from NLS in a label. The code looks like this:
 
  .. code:: java

    public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();
        Labels.NLS.setCurrentLocale("pt_BR");
        // For english locale uncomment the line below and comment the pt_BR locale setter call.
        // Labels.NLS.setCurrentLocale("en_US");
        Label label = new Label(Labels.NLS.getMessage(Labels.Label1));
        desktop.setWidget(label);
        desktop.requestShow();
    }

- The result looks like this:

  .. image:: images/labelsampleptbr.png
   :align: center

- Setting the locale to "en_US" the result is as follows:

  .. image:: images/labelsampleenus.png
   :align: center

..
   | Copyright 2021-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.


