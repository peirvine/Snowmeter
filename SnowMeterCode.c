/***************************
SnowMeter Source Code
Copyright 2015 Peter Irvine, Madeline Arpin, and Sean Rogers
***************************/
#include "SparkFun_Photon_Weather_Shield_Library/SparkFun_Photon_Weather_Shield_Library.h"

float humidity = 0;
int tempf = 0;
float pascals = 0;
float baroTemp = 0;

String racewax;
String trainingwax;
double tempF;
String snowtype;


long lastPrint = 0;

String racing, training;
bool snow = false;
long int starttime, nowtime;

//Create Instance of HTU21D or SI7021 temp and humidity sensor and MPL3115A2 barometric sensor
Weather sensor;

//---------------------------------------------------------------
void setup()
{
    Particle.function("SnowAge", NewSnow);
    starttime = Time.now();
    
    Serial.begin(9600);   // open serial over USB at 9600 baud

    // Make sure your Serial Terminal app is closed before powering your device
    // Now open your Serial Terminal, and hit any key to continue!
   // Serial.println("Press any key to begin");
    //This line pauses the Serial port until a key is pressed
    //while(!Serial.available()) Spark.process();

    //Initialize the I2C sensors and ping them
    sensor.begin();

    /*You can only receive accurate barometric readings or accurate altitude
    readings at a given time, not both at the same time. The following two lines
    tell the sensor what mode to use. You could easily write a function that
    takes a reading in one made and then switches to the other mode to grab that
    reading, resulting in data that contains both accurate altitude and barometric
    readings. For this example, we will only be using the barometer mode. Be sure
    to only uncomment one line at a time. */
    sensor.setModeBarometer();//Set to Barometer Mode
    //baro.setModeAltimeter();//Set to altimeter Mode

    //These are additional MPL3115A2 functions that MUST be called for the sensor to work.
    sensor.setOversampleRate(7); // Set Oversample rate
    //Call with a rate from 0 to 7. See page 33 for table of ratios.
    //Sets the over sample rate. Datasheet calls for 128 but you can set it
    //from 1 to 128 samples. The higher the oversample rate the greater
    //the time between data samples.


    sensor.enableEventFlags(); //Necessary register calls to enble temp, baro and alt
    
    Particle.variable("racewax", &racewax, STRING);
    Particle.variable("trainingwax", &training, STRING);
    Particle.variable("temp", &tempF, DOUBLE);
    Particle.variable("snowtype", &snowtype, STRING);
}
//---------------------------------------------------------------
void loop()
{
    nowtime = Time.now();
    if((nowtime - starttime) > 120){ //for demoing use 120 for real lyfe use 172,800
        starttime = nowtime;
        snow = false;
        snowtype = "Old Snow";
    }
      //Get readings from all sensors
      getWeather();

      // This math looks at the current time vs the last time a publish happened
      if(millis() - lastPrint > 5000) //Publishes every 5000 milliseconds, or 5 seconds
      {
        // Record when you published
        lastPrint = millis();

        // Use the printInfo() function to print data out to Serial
        printInfo();
      }
    tempF = tempf;
}
//---------------------------------------------------------------
void getWeather()
{
  // Measure Relative Humidity from the HTU21D or Si7021
  humidity = sensor.getRH();

  // Measure Temperature from the HTU21D or Si7021
  tempf = sensor.getTempF();
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement with getTemp() instead with readTemp()

  //Measure the Barometer temperature in F from the MPL3115A2
  baroTemp = sensor.readBaroTempF();

  //Measure Pressure from the MPL3115A2
  pascals = sensor.readPressure();

  //If in altitude mode, you can get a reading in feet with this line:
  //float altf = sensor.readAltitudeFt();
}
//---------------------------------------------------------------
void printInfo()
{

//old snow
if(snow == false){
    Serial.println("Old Snow");
    snowtype = "Old Snow";
    if (humidity >= 60){
        //High humidity, will use HF or LF wax - make sure to differentiate. Also list training wax.
        Serial.print("Racing: ");
        if (tempf >= 32){
            Serial.print("LF: Not Recomended; HF: Use Yellow (HF10)");
            racewax = "LF: Not Recomended <br /> HF: Use Yellow (HF10)";
        }else if(tempf >= 25 && tempf < 32){
            Serial.print("LF: Not Recomended; HF: Use Red (HF8)");
            racewax = "LF: Not Recomended<br /> HF: Use Red (HF8)";
        }else if(tempf >= 18 && tempf < 25){
            Serial.print("LF: Not Recomended; HF: Use Purple (HF7)");
            racewax = "LF: Not Recomended<br /> HF: Use Purple (HF7)";
        }else if(tempf >= 7 && tempf < 18){
            if(tempf > 10){
                Serial.print("LF: Use Blue (LF6); HF: Use Blue (HF6)");
                racewax = "LF: Use Blue (LF6)<br /> HF: Use Blue (HF6)";
            }else{
                Serial.print("LF: Use Green (LF 4 or LF3); HF: Use Blue (HF6)");
                racewax = "LF: Use Green (LF 4 or LF3)<br /> HF: Use Blue (HF6)";
            }
        }else if(tempf < 7){
            Serial.print("LF: Use Green (LF4 or LF3); HF: Use Green (HF4 or HF3)");
            racewax = "LF: Use Green (LF4 or LF3)<br /> HF: Use Green (HF4 or HF3)";
        }
       
        Serial.print("Training: ");
        if (tempf >= 36){
            Serial.print("Use Yellow (CH10)");
            training = "Use Yellow (CH10)";
        }else if(tempf >= 29 && tempf < 36){
            Serial.print("Use Red (CH8)");
            training = "Use Red (CH8)";
        }else if(tempf >= 18 && tempf < 29){
            Serial.print("Use Purple (CH7)");
            training = "Use Purple (CH7)";
        }else if(tempf >= 10 && tempf < 18){
            Serial.print("Use Blue (CH6)");
            training = "Use Blue (CH6)";
        }else if(tempf < 10){
            Serial.print("Use Green (CH4 or CH3)");
            training = "Use Green (CH4 or CH3)";
        }
        Serial.println();
    }else{
        Serial.print("Racing: ");
        if (tempf >= 36){
            Serial.print("LF: Not Recomended; HF: Use Yellow (HF10)");
            racewax = "LF: Not Recomended <br /> HF: Use Yellow (HF10)";
        }else if(tempf >= 29 && tempf < 36){
            Serial.print("LF: Not Recomended; HF: Use Red (HF8)");
            racewax = "LF: Not Recomended<br /> HF: Use Red (HF8)";
        }else if(tempf >= 18 && tempf < 29){
            if (tempf > 21){
                Serial.print("LF: Not Recomended; HF: Use Purple (HF7)");
                racewax = "LF: Not Recomended<br /> HF: Use Purple (HF7)";
            }else{
                Serial.print("LF: Use Purple (LF7); HF: Use Purple (HF7)");
                racewax = "LF: Use Purple (LF7)<br /> HF: Use Purple (HF7)";
            }
        }else if(tempf >= 10 && tempf < 18){
            Serial.print("LF: Use Blue (LF6); HF: Use Blue (HF6)");
            racewax = "LF: Use Blue (LF6)<br /> HF: Use Blue (HF6)";
        }else if(tempf < 10){
            Serial.print("LF: Use Green (LF4 or LF3); HF: Not Recommended");
            racewax = "LF: Use Green (LF4 or LF3)<br /> HF: Not Recommended";
        }
       
        Serial.print("Training: ");
        if (tempf >= 36){
            Serial.print("Use Yellow (CH10)");
            training = "Use Yellow (CH10)";
        }else if(tempf >= 29 && tempf < 36){
            Serial.print("Use Red (CH8)");
            training = "Use Red (CH8)";
        }else if(tempf >= 18 && tempf < 29){
            Serial.print("Use Purple (CH7)");
            training = "Use Purple (CH7)";
        }else if(tempf >= 10 && tempf < 18){
            Serial.print("Use Blue (CH6)");
            training = "Use Blue (CH6)";
        }else if(tempf < 10){
            Serial.print("Use Green (CH4 or CH3)");
            training = "Use Green (CH4 or CH3)";
        }
        Serial.println();
    }
}
    
 else{   
    //New Snow
     Serial.println("New Snow");
    if (humidity >= 60){
        //High humidity, will use HF or LF wax - make sure to differentiate. Also list training wax.
        Serial.print("Racing: ");
        if (tempf >= 36){
            Serial.print("LF: Not Recomended; HF: Use Yellow (HF10)");
            racewax = "LF: Not Recomended<br /> HF: Use Yellow (HF10)";
        }else if(tempf >= 29 && tempf < 36){
            Serial.print("LF: Not Recomended; HF: Use Red (HF8)");
            racewax = "LF: Not Recomended<br /> HF: Use Red (HF8)";
        }else if(tempf >= 21 && tempf < 29){
            Serial.print("LF: Not Reccomended; HF: Use Purple (HF7)");
            racewax = "LF: Not Reccomended<br /> HF: Use Purple (HF7)";
        }else if(tempf >= 10 && tempf < 21){
            if(tempf > 18){
                Serial.print("LF: Not Recommended; HF: Use Blue (HF6)");
                racewax = "LF: Not Recommended<br /> HF: Use Blue (HF6)";
            }else{
                Serial.print("LF: Use Blue (LF6); HF: Use Blue (HF6)");
                racewax = "LF: Use Blue (LF6)<br /> HF: Use Blue (HF6)";
            }
        }else if(tempf < 10){
            Serial.print("LF: Use Green (LF4 or LF3); HF: Use Green (HF4 or HF3)");
            racewax = "LF: Use Green (LF4 or LF3)<br /> HF: Use Green (HF4 or HF3)";
        }
       
        Serial.print("Training: ");
        if (tempf >= 39){
            Serial.print("Use Yellow (CH10)");
            training = "Use Yellow (CH10)";
        }else if(tempf >= 32 && tempf < 39){
            Serial.print("Use Red (CH8)");
            training = "Use Red (CH8)";
        }else if(tempf >= 25 && tempf < 32){
            Serial.print("Use Purple (CH7)");
            training = "Use Purple (CH7)";
        }else if(tempf >= 14 && tempf < 25){
            Serial.print("Use Blue (CH6)");
            training = "Use Blue (CH6)";
        }else if(tempf < 14){
            Serial.print("Use Green (CH4 or CH3)");
            training = "Use Green (CH4 or CH3)";
        }
        Serial.println();
    }else{
        Serial.print("Racing: ");
        if (tempf >= 39){
            Serial.print("LF: Not Recomended; HF: Use Yellow (HF10)");
            racewax = "LF: Not Recomended<br /> HF: Use Yellow (HF10)";
        }else if(tempf >= 29 && tempf < 39){
            Serial.print("LF: Not Recomended; HF: Use Red (HF8)");
            racewax = "LF: Not Recomended<br /> HF: Use Red (HF8)";
        }else if(tempf >= 21 && tempf < 29){
            if (tempf > 25){
                Serial.print("LF: Not Recomended; HF: Use Purple (HF7)");
                racewax = "LF: Not Recomended<br /> HF: Use Purple (HF7)";
            }else{
                Serial.print("LF: Use Purple (LF7); HF: Use Purple (HF7)");
                racewax = "LF: Use Purple (LF7)<br /> HF: Use Purple (HF7)";
            }
        }else if(tempf >= 14 && tempf < 21){
            Serial.print("LF: Use Blue (LF6); HF: Use Blue (HF6)");
            racewax = "LF: Use Blue (LF6)<br /> HF: Use Blue (HF6)";
        }else if(tempf < 14){
            Serial.print("LF: Use Green (LF4 or LF3); HF: Not Recommended");
            racewax = "LF: Use Green (LF4 or LF3)<br /> HF: Not Recommended";
        }
       
        Serial.print("Training: ");
        if (tempf >= 39){
            Serial.print("Use Yellow (CH10)");
            training = "Use Yellow (CH10)";
        }else if(tempf >= 32 && tempf < 39){
            Serial.print("Use Red (CH8)");
            training = "Use Red (CH8)";
        }else if(tempf >= 25 && tempf < 32){
            Serial.print("Use Purple (CH7)");
            training = "Use Purple (CH7)";
        }else if(tempf >= 14 && tempf < 25){
            Serial.print("Use Blue (CH6)");
            training = "Use Blue (CH6)";
        }else if(tempf < 14){
            Serial.print("Use Green (CH4 or CH3)");
            training = "Use Green (CH4 or CH3)";
        }
        Serial.println();
    }
 }
}

int NewSnow(String command){
    snow = true;
    snowtype = "New Snow";
    nowtime = Time.now();
    return 0;
}