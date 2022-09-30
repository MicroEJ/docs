Animation
=========

Animations can be used to make the GUI more appealing and more lively.

MWT provides a framework to create fluid animations.
The principle is as follow:

- make a step of all the running animations (with a probable new rendering of some widgets),
- wait for the display to be flushed,
- do it again.

The goals are:

- doing animations as fast as possible (considering the complexity of the drawings and the hardware capabilities),
- synchronizing all the running animations and avoiding glitches.

Usage
-----

- An animation can be created by implementing the `Animation`_ interface and its `tick()`_ method.
- The `tick()`_ method is called for each step of the animation.
- Every time the method is called, the widget should be re-rendered.
- The animation can be stopped by returning ``false``.
   
  .. code:: java
   
    Animation labelAnimation = new Animation() { 
    
       int tick = 0;
        
       @Override
       public boolean tick(long currentTimeMillis) { 
          label.setText(Integer.toString(tick++));
          label.requestRender();
          return true; 
       } 
    };
    Animator animator = new Animator();
    animator.startAnimation(labelAnimation); 

- The code above updates the label text everytime it is called:

  .. image:: images/ticking.png
   :align: center 

- The final code looks like this:

  .. code:: java

    public static void main(String[] args) {
       MicroUI.start();
       Desktop desktop = new Desktop();
       final Label label = new Label("hello");

       Flow flow = new Flow(LayoutOrientation.VERTICAL);
       flow.addChild(label);

       Animation labelAnimation = new Animation() {

          int tick = 0;

          @Override
          public boolean tick(long currentTimeMillis) {
             label.setText(Integer.toString(this.tick++));
             label.requestRender();
             return true;
          }
       };
       Animator animator = new Animator();
       animator.startAnimation(labelAnimation);

       desktop.setWidget(flow);
       desktop.requestShow();
    }


.. _Animation: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animation.html
.. _tick(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/animation/Animation.html#tick-long-

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.


