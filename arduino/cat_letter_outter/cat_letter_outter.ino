#include  <arduinoFFT.h>
 
#define SAMPLES 128             //SAMPLES-pt FFT. Must  be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2048  //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
 
#define SOUND_SENSOR_PIN A0

arduinoFFT  FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
  
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double  vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
 
void  setup() 
{
    Serial.begin(115200); //Baud rate for the Serial Monitor
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds  
}
 
void loop() 
{  
    /*Sample SAMPLES times*/
    for(int  i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the  number of microseconds since the Arduino board began running the current script.  
     
        vReal[i] = analogRead(SOUND_SENSOR_PIN); //Reads the value from analog pin  0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes  imaginary term 0 always

        /*remaining wait time between samples if  necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    /*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal,  vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    /*Find peak frequency and print peak*/
    double peak = FFT.MajorPeak(vReal,  SAMPLES, SAMPLING_FREQUENCY);
    Serial.println(peak);     //Print out the most  dominant frequency.
 
    /*Script stops here. Hardware reset required.*/
    //while (1); //do one time
}
