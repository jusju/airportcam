/*!
 * @file  SEN0186.ino
 * @brief DFRobot brings you this new version of the weather station kit that integrates anemometer, wind vane and rain gauge.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  DFRobot
 * @version  V1.0
 * @date  2023-08-03
 */

char                 databuffer[35];
double               temp;

void getBuffer()                                                                    //Get weather status data
{
  int index;
  for (index = 0; index < 35; index++) {
    if (Serial.available() > 0) {
      databuffer[index] = Serial.read();
        //Serial.println(databuffer[index]);

      if (databuffer[0] != 'c') {
        index = -1;
      }
    } else {
      index--;
    }
  }
}

int transCharToInt(char* _buffer, int _start, int _stop)                             //char to int）
{
  int _index;
  int result = 0;
  int num = _stop - _start + 1;
  int _temp[num];
  for (_index = _start; _index <= _stop; _index++) {
    _temp[_index - _start] = _buffer[_index] - '0';
    result = 10 * result + _temp[_index - _start];
  }
  return result;
}

int transCharToInt_T(char* _buffer)
{
  int result = 0;
  if (_buffer[13] == '-') {
    result = 0 - (((_buffer[14] - '0') * 10) + (_buffer[15] - '0'));
  } else {
    result = ((_buffer[13] - '0') * 100) + ((_buffer[14] - '0') * 10) + (_buffer[15] - '0');
  }
  return result;
}

int WindDirection()                                                                  //Wind Direction
{
  return transCharToInt(databuffer, 1, 3);
}

float WindSpeedAverage()                                                             //air Speed (1 minute)
{
  temp = 0.44704 * transCharToInt(databuffer, 5, 7);
  return temp;
}

float WindSpeedMax()                                                                 //Max air speed (5 minutes)
{
  temp = 0.44704 * transCharToInt(databuffer, 9, 11);
  return temp;
}

float Temperature()                                                                  //Temperature ("C")
{
  temp = (transCharToInt_T(databuffer) - 32.00) * 5.00 / 9.00;
  return temp;
}

float RainfallOneHour()                                                              //Rainfall (1 hour)
{
  temp = transCharToInt(databuffer, 17, 19) * 25.40 * 0.01;
  return temp;
}

float RainfallOneDay()                                                               //Rainfall (24 hours)
{
  temp = transCharToInt(databuffer, 21, 23) * 25.40 * 0.01;
  return temp;
}

int Humidity()                                                                       //Humidity
{
  return transCharToInt(databuffer, 25, 26);
}

float BarPressure()                                                                  //Barometric Pressure
{
  temp = transCharToInt(databuffer, 28, 32);
  return temp / 10.00;
}

// Function to manually create and send JSON data
void sendJsonManually()
{
  // Manually build the JSON string
  String jsonString = "{";
  jsonString += "\"windDirection\": " + String(WindDirection()) + ",";
  jsonString += "\"averageWindSpeedMps\": " + String(WindSpeedAverage(), 2) + ",";
  jsonString += "\"maxWindSpeedMps\": " + String(WindSpeedMax(), 2) + ",";
  jsonString += "\"rainfallOneHourMm\": " + String(RainfallOneHour(), 2) + ",";
  jsonString += "\"rainfall24HoursMm\": " + String(RainfallOneDay(), 2) + ",";
  jsonString += "\"temperatureCelsius\": " + String(Temperature(), 2) + ",";
  jsonString += "\"humidityPercent\": " + String(Humidity()) + ",";
  jsonString += "\"barometricPressureHpa\": " + String(BarPressure(), 2) + ",";
  jsonString += "\"timeCheckMillis\": " + String(millis());
  jsonString += "}";

  // Send the JSON string via Serial
  Serial.println(jsonString);
}


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  getBuffer();                                                                      //Begin!
  Serial.print("{");
  Serial.print("WindDirection: ");
  Serial.print(WindDirection());
  Serial.println("  ,");
  Serial.print("AverageWindSpeedOneMinuteMeterPerSecond: ");
  Serial.print(WindSpeedAverage());
  Serial.println("  ,");
  Serial.print("MaxWindSpeedFiveMinutesMeterPerSecond: ");
  Serial.print(WindSpeedMax());
  Serial.println("  ,");
  Serial.print("RainFallOneHourMm: ");
  Serial.print(RainfallOneHour());
  Serial.println("   ,");
  Serial.print("RainFall24HourMm: ");
  Serial.print(RainfallOneDay());
  Serial.println("  ,");
  Serial.print("TemperatureCelsius: ");
  Serial.print(Temperature());
  Serial.println("  ,");
  Serial.print("HumidityPercentage: ");
  Serial.print(Humidity());
  Serial.println("  ,");
  Serial.print("BarometricPressurehPa: ");
  Serial.print(BarPressure());
  Serial.println("  ,");
  Serial.print("TimeCheckMillisS: ");
  Serial.print(millis());
  Serial.println("");
  Serial.println("");
  Serial.print("}");
  Serial.println("");

   // Call the function to send JSON data
  sendJsonManually();
  
  Serial.println("");
}
