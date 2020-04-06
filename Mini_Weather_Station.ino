// SOURCES:
// https://create.arduino.cc/projecthub/dnbakshi07/mini-weather-station-using-arduino-nano-b211fe?fbclid=IwAR2AyprrQPpumjUkTDI2wFdadUCjiJbLzPdgpT8ni-vu8mcJgtulg2zDT6Q
// https://circuitdigest.com/microcontroller-projects/rain-detector-using-arduino
// https://earthscience.stackexchange.com/questions/16366/weather-forecast-based-on-pressure-temperature-and-humidity-only-for-implement


// LIBRARIES
#include <SPI.h>               //include Serial Peripheral Interface library
#include <Wire.h>              //include Two Wire Interface library
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library
#include <Adafruit_BMP280.h>   // include Adafruit BMP280 sensor library
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>   // include Adafruit BMP280 sensor library
#include <Time.h>
#include <TimeLib.h>
#define TFT_RST   8            // TFT RST pin is connected to arduino pin D8
#define TFT_CS    10           // TFT CS  pin is connected to arduino pin D9
#define TFT_DC    9            // TFT DC  pin is connected to arduino pin D10
#define rainfall A3           // rain detector pin is connected to arduino pin A3

int rainValue;                    // store read values from raindrops module
int set = 10;                 // threshold value for rain detector


// initialize ST7735 SERIES TFT library
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// define device I2C address: 0x76 (0x76 is the library default address)
#define BME280_I2C_ADDRESS  0x76

// initialize Adafruit BME280 sensor library
// Sensor can measure temperature, humidty, pressure, and altitude
Adafruit_BME280  bme280;

// Functions

// Prints the forecast based on the zambretti weather forecasting instrument
void forecast (int zambretti)
{
  switch (zambretti) {
    case 1:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Settled Fine");                      // print the forecast
      break;
    case 2:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fine Weather");                      // print the forecast
      break;
    case 3:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fine, Becoming Less");               // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Settled");                           // print the forecast
      break;
    case 4:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fairly Fine,");                      // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Showery Later");                     // print the forecast
      break;
    case 5:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Showery, Becoming");                 // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("More Unsettled");                    // print the forecast
      break;
    case 6:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Unsettled, Rain Later");             // print the forecast
      break;
    case 7:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Rain at Times, ");                   // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Worse Later");                             // print the forecast
      break;
    case 8:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Rain at Times,");                    // print the forecast
      tft.setCursor(10, 143);                         // move cursor to position of given coordinates
      tft.print("Becoming More");                     // print the forecast
      tft.setCursor(10, 151);                         // move cursor to position of given coordinates
      tft.print("Unsettled");                         // print the forecast
      break;
    case 9:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Very Unsettled,");                   // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Rain");                              // print the forecast
      break;
    case 10:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Settled Fine");                      // print the forecast
      break;
    case 11:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fine Weather");                      // print the forecast
      break;
    case 12:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fine, ");                            // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Possible Showers");                  // print the forecast
      break;
    case 13:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fair Fine, ");                       // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Showers Likely");                    // print the forecast
      break;
    case 14:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Showery,");                          // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Bright Intervals");                  // print the forecast
      break;
    case 15:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Changeable,");                       // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Some Rain");                         // print the forecast
      break;
    case 16:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Unsettled, ");                       // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Rain at Times");                     // print the forecast
      break;
    case 17:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Rain at ");                          // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Frequent Intervals");                // print the forecast
      break;
    case 18:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Very Unsettled,");                   // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Rain");                              // print the forecast
      break;
    case 19:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Stormy, ");                          // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Much Rain");                         // print the forecast
      break;
    case 20:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Settled Fine");                      // print the forecast
      break;
    case 21:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fine Weather");                      // print the forecast
      break;
    case 22:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Becoming Fine");                     // print the forecast
      break;
    case 23:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fairly Fine,");                      // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Improving");                         // print the forecast
      break;
    case 24:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Fairly Fine,");                      // print the forecast
      tft.setCursor(10, 143);                         // move cursor to position of given coordinates
      tft.print("Possibly Showers,");                 // print the forecast
      tft.setCursor(10, 151);                         // move cursor to position of given coordinates
      tft.print("Early");                             // print the forecast
      break;
    case 25:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Showerly Early");                             // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Improving");                             // print the forecast
      break;
    case 26:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Changeable ");                       // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Mending");                             // print the forecast
      break;
    case 27:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Rather Unsettled ");                 // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Clearing Later");                    // print the forecast
      break;
    case 28:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Unsettled, ");                       // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Probably Improving");                // print the forecast
      break;
    case 29:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Unsettled, Short");                  // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Fine Intervals");                    // print the forecast
      break;
    case 30:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Very Unsettled,");                   // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Finer at Times");                    // print the forecast
      break;
    case 31:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Stormy,");                           // print the forecast
      tft.setCursor(10, 145);                         // move cursor to position of given coordinates
      tft.print("Possibly Improving");                // print the forecast
      break;
    case 32:
      tft.setCursor(10, 135);                         // move cursor to position of given coordinates
      tft.print("Stormy Much Rain");                  // print the forecast
      break;
  }
}


// Calculates the sea level
int station2sealevel (int p, int height, int t) {
  return (double) p * pow(1 - 0.0065 * (double)height / (t + 0.0065 * (double)height + 273.15), -5.275);
}


// Calculates the zambretti values
// It interprets the reading of a barometer into one forecast from a large selection
// of permutations after making allowances for variable factors.
// These include wind direction, a rising, falling or steady barometer, and the season. (Source: Wikipedia)
int calculate_zambretti (int curr_pressure, int prev_pressure, int month) {
  if (curr_pressure < prev_pressure) {

    //FALLING air pressure
    if (month >= 4 and month <= 9)
      // Summer
    {
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 18;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 24;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
    else {
      // Winter
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 15;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 22;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
  }
  else if (curr_pressure > prev_pressure) {
    //RAISING air pressure
    if (month >= 4 and month <= 9) {
      // Summer
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 3;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 9;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 12;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }

    else
      // Winter
    {
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 6;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 10;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 13;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }
  }
  else {
    if (curr_pressure >= 1030)
      return 1;
    else if (curr_pressure >= 1020 and curr_pressure < 1030)
      return 2;
    else if (curr_pressure >= 1010 and curr_pressure < 1020)
      return 11;
    else if (curr_pressure >= 1000 and curr_pressure < 1010)
      return 14;
    else if (curr_pressure >= 990 and curr_pressure < 1000)
      return 19;
    else if (curr_pressure >= 980 and curr_pressure < 990)
      return 23;
    else if (curr_pressure >= 970 and curr_pressure < 980)
      return 24;
    else if (curr_pressure < 970)
      return 26;
  }
}



void setup(void)
{
  Serial.begin(9600);
  pinMode(rainfall, INPUT);

  tft.initR(INITR_BLACKTAB);                           // initialize ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);                        // sets the background to black

  tft.drawFastHLine(0, 17 ,  tft.width(), ST77XX_CYAN);// draws a horizontal line at position (0, 15)

  tft.setTextColor(ST7735_CYAN, ST7735_BLACK);         // sets the text color to white and background to black
  tft.setTextSize(1);                                  // sets text size to 1
  tft.setCursor(5, 6);                                 // move cursor to position (25, 5) pixel
  tft.print("MINI WEATHER STATION");                   // display message to LCD screen at position


  // initializes the BME280 sensor
  // if there is a connection error or if the device address is wrong,
  // print connection error message
  if (bme280.begin(BME280_I2C_ADDRESS) == 0 )
  {
    tft.setTextColor(ST7735_RED, ST7735_CYAN);        // set text color to red and background to black
    tft.setTextSize(2);                               // setting text size to 2
    tft.setCursor(5, 76);                             // move cursor to position coordinates
    tft.print("Connection");                          // display message to LCD screen at position
    tft.setCursor(35, 100);                           // move cursor to position coordinates
    tft.print("Error");                               // display message to LCD screen at position
    while (1);                                        // stay here if connection is not made
  }


  tft.drawFastHLine(0, 50,  tft.width(), ST7735_CYAN);  // draws a horizontal seperation line at coordinates
  tft.drawFastHLine(0, 85,  tft.width(), ST7735_CYAN);  // draws a horizontal seperation line at coordinates
  tft.drawFastHLine(0, 120,  tft.width(), ST7735_CYAN); // draws a horizontal seperation line at coordinates

  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);           // set text color and background color
  tft.setCursor(30, 21);                                // move cursor to position of given coordinates
  tft.print("TEMPERATURE ");                            // display message to LCD screen at position

  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);          // set text color and background color
  tft.setCursor(15, 55);                                // move cursor to position of given coordinates
  tft.print("HUMIDITY ");                               // display message to LCD screen at position

  tft.setTextColor(ST77XX_BLUE, ST7735_BLACK);          // set text color and background color
  tft.setCursor(85, 55);                                // move cursor to position of given coordinates
  tft.print("RAIN ");                                   // display message to LCD screen at position

  tft.setTextColor(ST77XX_GREEN, ST7735_BLACK);         // set text color and background color
  tft.setCursor(40, 90);                                // move cursor to position of given coordinates
  tft.print("PRESSURE ");                               // display message to LCD screen at position

  tft.setTextColor(ST77XX_GREEN, ST7735_BLACK);         // set text color and background color
  tft.setCursor(40, 125);                               // move cursor to position of given coordinates
  tft.print("FORECAST ");                               // display message to LCD screen at position

  tft.setTextSize(2);                                   // set text size to 2
}



// Main Loop
void loop()
{

  char _buffer[8];

  // reads the temperature, humidity and pressure from the BME280 sensor
  float temperature = bme280.readTemperature();      // reads the temperature in °C
  float humidity = bme280.readHumidity();          // reads the humidity in rH%
  float pressure = bme280.readPressure();         // reads the pressure in hPa
  float altitude = 560; //(int)bme.readAltitude(SEALEVELPRESSURE_HPA);


  // 1: prints the approximate temperature (in °C)
  if (temperature < 0)                             // if temperature < 0
    sprintf( _buffer, "-%02u.%02u", (int)abs(temperature), (int)(abs(temperature) * 100) % 100 );
  else                                      // if temperature >= 0
    sprintf( _buffer, " %02u.%02u", (int)temperature, (int)(temperature * 100) % 100 );           // setting the value approximation

  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);  // set text color and background color
  tft.setCursor(11, 32);                          // move cursor to position of given coordinates
  tft.print(_buffer);                             // print temperature from BME280 sensor
  tft.drawCircle(89, 32, 2, ST7735_YELLOW);       // print the degree symbol ( ° )
  tft.setCursor(95, 32);                          // move cursor to position of given coordinates
  tft.print("C");                                 // print the Celcius symbol


  // 2: prints the approximate humidity (in %)
  sprintf( _buffer, "%02u ", (int)(humidity));     // setting the value approximation
  tft.setTextColor(ST7735_MAGENTA, ST7735_BLACK);  // set text color and background color
  tft.setCursor(20, 67);                           // move cursor to position of given coordinates
  tft.print(_buffer);                              // print humidity from BME280 sensor
  tft.setCursor(45, 67);                           // move cursor to position of given coordinates
  tft.print("%");                                  // print the percentage symbol


  // 3: print if it is raining (in yes or no)
  rainValue = analogRead(rainfall);                     // store analog values from raindrops module
  rainValue = map(rainValue, 0, 1023, 225, 0);          // map the analog values

  // if value succeeds the threshold, display yes
  if (rainValue >= set) {
    tft.setTextColor(ST7735_ORANGE, ST7735_BLACK);    // set text color and background color
    tft.setCursor(79, 67);                            // move cursor to position of given coordinates
    tft.print("YES");                                 // print YES if raining
  }
  // if not, display no
  else {
    tft.setTextColor(ST7735_ORANGE, ST7735_BLACK);    // set text color and background color
    tft.setCursor(74, 67);                            // move cursor to position of given coordinates
    tft.print(" NO ");                                // print NO if not raining
  }

  // 4: prints the pressure (in hPa)
  sprintf( _buffer, "%04u.%02u", (int)(pressure / 100), (int)((uint32_t)pressure % 100) ); // setting the value approximation

  tft.setTextColor(ST7735_ORANGE, ST7735_BLACK);    // set text color and background color
  tft.setCursor(3, 102);                            // move cursor to position of given coordinates
  tft.print(_buffer);                               // print atmospheric pressure from BME280 sensor
  tft.setCursor(91, 102);                           // move cursor to position of given coordinates
  tft.print("hPa");                                 // print unit of atmospheric pressure as hecto pascal


  // 5: prints the forecast (in words)
  tft.setTextColor(ST7735_ORANGE, ST7735_BLACK);  // set text color to orange and black background

  int seapressure = station2sealevel(pressure, altitude, temperature);
  int pressureArray[10] = {0};
  byte counter = 0;
  byte delta_time = 0;

  int t_hour = 0;
  int t_minute = 0;

  time_t t = now();
  int t_hour2 = hour();
  int t_minute2 = minute();
  int Z = 0;

  if (t_hour2 != t_hour or t_minute2 != t_minute) {
    delta_time++;
    if (delta_time > 10) {
      delta_time = 0;

      if (counter == 10)
      {
        for (int i = 0; i < 9; i++) {
          pressureArray[i] = pressureArray[i + 1];
        }
        pressureArray[counter - 1] = seapressure;
      }
      else {
        pressureArray[counter] = seapressure;
        counter++;
      }
    }

    Z = calculate_zambretti((pressureArray[9] + pressureArray[8] + pressureArray[7]) / 3, (pressureArray[0] + pressureArray[1] + pressureArray[2]) / 3, month());

    tft.setTextColor(ST7735_ORANGE, ST7735_BLACK);    // set text color and background color
    tft.setTextSize(1);                               // setting text size to 2
    forecast(Z);
    tft.setTextSize(2);                               // setting text size to 2

    t_hour = t_hour2;
    t_minute = t_minute2;

    delay(1000);                                    // wait 1 second before taking the next sensor reading
  }
}
