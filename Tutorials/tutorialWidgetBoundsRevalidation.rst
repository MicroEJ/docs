How compute Optimal Size works
===============================

A Container has multiple children widgets, to compute the size of each of the children on a container

Every time a widget is laid out, the method ComputeOptimalSize is called, it calculates the of this widget

Every call to computeOptimalsize stores the Size needed to show the Widget correctly Including outlines(Example: Margin,Padding)

As a Container is also a Widget,it also contains a computeOptimalsize, calculating its size using its childrenm

on every call to LayOut, the optimal Size is recalculated

every container has it's own way to calculate the optimal size
Flow Container
--------------

.. code-block:: Java

    protected void computeContentOptimalSize(Size size) {
            int widthHint = size.getWidth();
            int heightHint = size.getHeight();

            Widget[] children = getChildren();
            for (Widget child : children) {
                assert (child != null);

                // compute child optimal size
                computeChildOptimalSize(child, widthHint, heightHint);
            }

            // get total size
            boolean isHorizontal = (this.orientation == LayoutOrientation.HORIZONTAL);
            int mainSizeHint = (isHorizontal ? widthHint : heightHint);
            int[] totalSize = new int[2];
            computeTotalSize(children, isHorizontal, mainSizeHint, totalSize);

            // set container optimal size
            if (isHorizontal) {
                size.setSize(totalSize[0], totalSize[1]);
            } else {
                size.setSize(totalSize[1], totalSize[0]);
            }
        }