.. _section_define_extra_style_field:

How to Define an Extra Style Field
==================================

Extra style fields allow to customize a widget by configuring graphical elements of the widget from the stylesheet.
Extra fields are only relevant to a specific widget type and its subtypes. A widget type can support up to ``7`` extra fields.
The value of an extra field may be represented as an ``int``, a ``float`` or any object, and it can not be inherited from parent widgets.

Defining an extra field ID
--------------------------

The recommended practice is to add a public constant for the ID of the new extra field in the widget subtype.
This ID should be an integer with a value between ``0`` and ``6``.

Every extra field ID has to be unique within the widget type. However, two unrelated widget types may define an extra field with the same ID.

For example, the following snippet defines an extra field for a secondary color:

.. code-block:: Java

	public static final int SECONDARY_COLOR_FIELD = 0;

Setting an extra field in the stylesheet
----------------------------------------

The value of an extra field may be set in the stylesheet in a similar fashion to built-in style fields, using one of the ``setExtraXXX()`` methods of `EditableStyle`_.

For example, the following snippet sets the value of an extra field for all the instances of a widget subtype:

.. code-block:: Java

	EditableStyle style = stylesheet.getSelectorStyle(new TypeSelector(MyWidget.class));
	style.setExtraInt(MyWidget.SECONDARY_COLOR_FIELD, Colors.RED);

.. _EditableStyle: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/EditableStyle.html

Getting an extra field during rendering
---------------------------------------

The value of an extra field may be retrieved from the style of a widget in a similar fashion to built-in style fields, using one of the ``getExtraXXX()`` methods of `Style`_.
When calling one of these methods, a default value has to be given in case the extra field is not set for this widget.

For example, the following snippet gets the value of an extra field of the widget:

.. code-block:: Java

	Style style = getStyle();
	int secondaryColor = style.getExtraInt(SECONDARY_COLOR_FIELD, Colors.BLACK);

.. _Style: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/style/Style.html

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
