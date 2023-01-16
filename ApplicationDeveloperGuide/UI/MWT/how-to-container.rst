How to Create a Container
=========================

To create a custom container, a new class should be created, extending the `Container`_ class.
This new class may define a constructor and setter methods in order to provide a way for the user to configure the container, such as its orientation.
Container subclasses have to implement two methods and may override optional methods, as explained in the following sections.

.. _Container: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html

Implementing the mandatory methods
----------------------------------

This section explains how to implement the two mandatory methods of a container subclass.

Computing the optimal size of the container
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `computeContentOptimalSize()`_ method is called by the MWT framework in order to know the optimal size of the container.
The optimal size of the container should be big enough so that each child can be laid out with a size at least as big as its own optimal size.

The container is responsible for computing the optimal size of every child. To do so, the `computeChildOptimalSize()`_ method should be called for every child.
After this method is called, the optimal size of the child can be retrieved by calling `getWidth()`_ and `getHeight()`_ on the child widget.

The ``Size`` parameter of the `computeContentOptimalSize()`_ method initially contains the size available for the container.
An available width or height equal to `Widget.NO_CONSTRAINT`_ means that the optimal size should be computed without considering any restriction on the respective axis.
Before the method returns, the size object should be set to the optimal size of the container.

For example, the following snippet computes the optimal size of a simple wrapper:

.. code-block:: Java

	@Override
	protected void computeContentOptimalSize(Size size) {
		Widget child = getChild(0);
		computeChildOptimalSize(child, size.getWidth(), size.getHeight());
		size.setSize(child.getWidth(), child.getHeight());
	}

.. _computeContentOptimalSize(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#computeContentOptimalSize-ej.mwt.util.Size-
.. _computeChildOptimalSize(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#computeChildOptimalSize-ej.mwt.Widget-int-int-
.. _getWidth(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#getWidth--
.. _getHeight(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#getHeight--
.. _Widget.NO_CONSTRAINT: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Widget.html#NO_CONSTRAINT

Laying out the children of the container
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `layOutChildren()`_ method is called by the MWT framework in order to lay out every child of the container, i.e. to set the position and size of the children.
If a child is laid out outside the bounds of the container (partially or fully), only the part of the widget which is within the container bounds will be visible.

The container is responsible for laying out each child. To do so, the `layOutChild()`_ method should be called for every child.
Before this method is called, the optimal size of the child can be retrieved by calling `getWidth()`_ and `getHeight()`_ on the child widget.

When laying out a child, its bounds have to be passed as parameter. The position will be interpreted as relative to the position of the container content. This means that the position should not include the outlines of the container.
This means that the ``(0, 0)`` coordinates represent the top-left pixel of the container content and the ``(contentWidth-1, contentHeight-1)`` coordinates represent the bottom-right pixel of the container content.

For example, the following snippet lays out the children of a simple wrapper:

.. code-block:: Java

	@Override
	protected void layOutChildren(int contentWidth, int contentHeight) {
		Widget child = getChild(0);
		layOutChild(child, 0, 0, contentWidth, contentHeight);
	}

.. _layOutChildren(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#layOutChildren-int-int-
.. _layOutChild(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#layOutChild-ej.mwt.Widget-int-int-int-int-

Managing the visibility of the children of the container
--------------------------------------------------------

By default, when a container is shown, each of its children is shown too.
This behavior can be changed by overriding the `setShownChildren()`_ method of `Container`_.
When implementing this method, the `setShownChild()`_ method should be called for each child which should be shown when the container is shown.

At any time while the container is visible, children may be shown or hidden by calling `setShownChild()`_ or `setHiddenChild()`_.

When a container is hidden, each of its children is hidden too (unless it is already hidden). It is not necessary to override `setHiddenChildren()`_, except for optimization.

.. _setShownChildren(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#setShownChildren--
.. _setShownChild(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#setShownChild-ej.mwt.Widget-
.. _setHiddenChild(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#setHiddenChild-ej.mwt.Widget-
.. _setHiddenChildren(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#setHiddenChildren--

Providing APIs to change the children list of the container
-----------------------------------------------------------

The `Container`_ class introduces ``protected`` APIs in order to manipulate the list of children of the container.
These methods may be overridden in the container subclass and set as ``public`` in order to make these APIs available for the user.

Each of the following methods may be overridden individually:

- `addChild() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#addChild-ej.mwt.Widget->`_
- `removeChild() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#removeChild-ej.mwt.Widget->`_
- `removeAllChildren() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#removeAllChildren-->`_
- `insertChild() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#insertChild-ej.mwt.Widget-int->`_
- `replaceChild() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#replaceChild-int-ej.mwt.Widget->`_
- `changeChildIndex() <https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Container.html#changeChildIndex-ej.mwt.Widget-int->`_

For example, the following snippet allows the user to call the ``addChild()`` method on the container:

.. code-block:: Java

	@Override
	public void addChild(Widget child) {
		super.addChild(child);
	}

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
