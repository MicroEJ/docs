How-To Create a Container
=========================

To create a custom container, a new class should be created, extending the ``Container`` class.
This new class may define a constructor and setter methods in order to provide a way for the user to configure the container, such as its orientation.
Container subclasses have to implement two methods and may override optional methods, as explained in the following sections.

Implementing the mandatory methods
----------------------------------

This section explains how to implement the two mandatory methods of a container subclass.

Computing the optimal size of the container
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``computeContentOptimalSize()`` method is called by the MWT framework in order to know the optimal size of the container.
The optimal size of the container should be big enough so that each child can be allocated a size at least as big as its own optimal size.
For example, the optimal width of a horizontal list is the sum of the optimal width of every child, and the optimal height is the maximum optimal height of all children.

The container is responsible for computing the optimal size of every child. To do so, the ``computeChildOptimalSize()`` method should be called for every child.
After this method is called, the optimal size of the child can be retrieved by calling ``getWidth()`` and ``getHeight()`` on the child widget.

The ``Size`` parameter of the ``computeContentOptimalSize()`` method initially contains the size available for the container.
An available width or height equal to ``Widget.NO_CONSTRAINT`` means that the optimal size should be computed without considering any restriction on the respective axis.
Before the method returns, the size object should be set to the optimal size of the container.

Laying out the children of the container
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``layOutChildren()`` method is called by the MWT framework in order to lay out every child of the container, i.e. to set the position and size of the children.
If a child is laid out outside the bounds of the container (partially or fully), only the part of the widget which is within the container bounds will be visible.

The container is responsible for laying out each child. To do so, the ``layOutChild()`` method should be called for every child.
Before this method is called, the optimal size of the child can be retrieved by calling ``getWidth()`` and ``getHeight()`` on the child widget.

When laying out a child, its bounds have to be passed as parameter. The position will be interpreted as relative to the position of the container content. This means that the position should not include the outlines of the container.
This means that the ``(0, 0)`` coordinates represent the top-left pixel of the container content and the ``(contentWidth-1, contentHeight-1)`` coordinates represent the bottom-right pixel of the container content.

Managing the visibility of the children of the container
--------------------------------------------------------

By default, when a container is shown, each of its children is shown too.
This behavior can be changed by overriding the ``setShownChildren()`` method of `` Container``.
When implementing this method, the ``setShownChild()`` method should be called for each child which should be shown when the container is shown.

At any time while the container is visible, children may be shown or hidden by calling ``setShownChild()`` or ``setHiddenChild()``.

When a container is hidden, each of its children is hidden too (unless it is already hidden). It is not necessary to override ``setHiddenChildren()``, except for optimization.

Providing APIs to change the children list of the container
-----------------------------------------------------------

The ``Container`` class introduces ``protected`` APIs in order to manipulate the list of children of the container.
These methods may be overridden in the container subclass and set as ``public`` in order to make these APIs available for the user.

Each of the following methods may be overridden individually:

- ``addChild()``
- ``removeChild()``
- ``removeAllChildren()``
- ``insertChild()``
- ``replaceChild()``
- ``changeChildIndex()``

For example, the following snippet allows the user to call the ``addChild()`` method on the container:

.. code-block:: Java

	@Override
	public void addChild(Widget child) {
		super.addChild(child);
	}

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
