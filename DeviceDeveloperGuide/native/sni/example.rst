Example
=======

.. code:: java

   package example;

   import java.io.IOException;

   /**
    * Abstract class providing a native method to access sensor value.
    * This method will be executed out of virtual machine.
    */
   public abstract class Sensor {

       public static final int ERROR = -1;

       public int getValue() throws IOException {
           int sensorID = getSensorID();
           int value = getSensorValue(sensorID);
           if (value == ERROR) {
               throw new IOException("Unsupported sensor");
           }
           return value;
       }

       protected abstract int getSensorID();

       public static native int getSensorValue(int sensorID);
   }

   class Potentiometer extends Sensor {
       
       protected int getSensorID() {
           return Constants.POTENTIOMETER_ID; // POTENTIOMETER_ID is a static final
       }
   }

.. code:: c

   // File providing an implementation of native method using a C function
               #include <sni.h>
               #include <potentiometer.h>
               
               #define SENSOR_ERROR (-1)
               #define POTENTIOMETER_ID (3)
               
               jint Java_example_Sensor_getSensorValue(jint sensor_id){
               
                   if (sensor_id == POTENTIOMETER_ID)
                   {
                       return get_potentiometer_value();
                   }
                   return SENSOR_ERROR;
               }
