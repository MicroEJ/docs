How compute Optimal Size works
===============================

A Container has multiple children widgets, to compute the size of each of the children on a container

Every time a widget is laid out, the method ComputeOptimalSize is called, it calculates the Size of this widget

Every call to computeOptimalsize stores the Size needed to show the Widget correctly Including outlines(Example: Margin,Padding) and Sets the Size atrribute

As a Container is also a Widget,it also contains a computeOptimalsize, calculating its size using its children

on every call to LayOut, the optimal Size is recalculated

every container has it's own way to calculate the optimal size as seen below

Flow Container
--------------
- Each time Compute optimal size is called on a Container(And a widget), Compute content optimal size is also called, in the case of Flow, it computes the size of each children and adds to the total sum


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


Canvas Container
------------------
- Since Canvas can position widgets freely we calculate the optimal size based on the position of the farthest child in the X and Y position, its width and compare if the width of the canvas


.. code-block:: java

    int widthHint = size.getWidth();
    int heightHint = size.getHeight();
    PackedMap<Widget, Rectangle> widgetBounds = this.widgetBounds;

    int width = 0;
    int height = 0;
    for (Widget child : getChildren()) {
        assert (child != null);

        // get child desired bounds
        Rectangle bounds = widgetBounds.get(child);
        int childX = bounds.getX();
        int childY = bounds.getY();
        int childWidth = bounds.getWidth();
        int childHeight = bounds.getHeight();

        // compute child optimal size
        int childWidthHint = getChildSize(childWidth, widthHint);
        int childHeightHint = getChildSize(childHeight, heightHint);
        computeChildOptimalSize(child, childWidthHint, childHeightHint);

        // update container optimal size
        childWidth = getChildSize(childWidth, child.getWidth());
        childHeight = getChildSize(childHeight, child.getHeight());
        width = Math.max(width, childX + childWidth);
        height = Math.max(height, childY + childHeight);
    }

    // set container optimal size
    size.setSize(width, height);