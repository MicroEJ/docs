Example
=======

Below is an example of using a database SP. The code that publishes the
data is written in C, and the code that receives the data is written in
Java. The data is transferred using two memory blocks. One is a scalar
value, the other is a more complex object representing a two-dimensional
vector.

Database Description
--------------------

The database is described as follows:

.. code:: xml

   <shieldedPlug>
       <database name="Forecast" id="0" immutable="true" version="1.0.0">
           <block id="1" name="TEMP" length="4" maxTasks="1"/>
           <block id="2" name="THERMOSTAT" length="4" maxTasks="1"/>
       </database>
   </shieldedPlug>

Java Code
---------

From the database description we can create an interface.

.. code:: java

   public interface Forecast {
               public static final int ID = 0;
               public static final int TEMP = 1;
               public static final int THERMOSTAT = 2;
   }

Below is the task that reads the published temperature and controls the
thermostat.

.. code:: java

   public void run(){
               ShieldedPlug database = ShieldedPlug.getDatabase(Forecast.ID);
               while (isRunning){
                   //reading the temperature every 30 seconds
                   //and update thermostat status
                   try {
                       int temp = database.readInt(Forecast.TEMP);
                       print(temp);
                       //update the thermostat status
                       database.writeInt(Forecast.THERMOSTAT,temp>tempLimit ? 0 : 1);
                   }
                   catch(EmptyBlockException e){
                       print("Temperature not available");
                   }
                   sleep(30000);
               }
   }

C Code
------

Here is a C header that declares the constants defined in the XML
description of the database.

.. code:: c

   #define Forecast_ID 0
   #define Forecast_TEMP 1
   #define Forecast_THERMOSTAT 2

Below, the code shows the publication of the temperature and thermostat
controller task.

.. code:: c

   void temperaturePublication(){
               ShieldedPlug database = SP_getDatabase(Forecast_ID);
               int32_t temp = temperature();
               SP_write(database, Forecast_TEMP, &temp);
           }

           void thermostatTask(){
               int32_t thermostatOrder;
               ShieldedPlug database = SP_getDatabase(Forecast_ID);
               while(1){
                   SP_waitFor(database, Forecast_THERMOSTAT);
                   SP_read(database, Forecast_THERMOSTAT, &thermostatOrder);
                   if(thermostatOrder == 0) {
                       thermostatOFF();
                   }
                   else {
                       thermostatON();
                   }
               }
   }
