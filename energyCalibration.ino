/*
Copyright (c) 2021 Jakub Mandula

Example of using one PZEM module with Software Serial interface.
================================================================

If only RX and TX pins are passed to the constructor, software
serial interface will be used for communication with the module.

*/

#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(Serial3, 0x02);

//  Блок Energy Monitor  ------------------------------------------------------
#include <EmonLib.h>          //  трансформаторы тока pins A1,A2,A3,A4,A5,A6,A0

#define PIN_EMON1 A1
#define PIN_EMON2 A2
#define PIN_EMON3 A3
#define PIN_EMON4 A4
#define PIN_EMON5 A5
#define PIN_EMON6 A6
#define PIN_EMON7 A0

float current_koef1 = 1;
float current_koef2 = 1;
float current_koef3 = 1;
float current_koef4 = 1;
float current_koef5 = 1;
float current_koef6 = 1;
float current_koef7 = 1;    // Калибровка при float current_koef7 = 1;

EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;
EnergyMonitor emon4;
EnergyMonitor emon5;
EnergyMonitor emon6;
EnergyMonitor emon7;

//  Блок SETUP  ------------------------------------------------------

void setup() {
    /* Debugging serial */
    Serial.begin(115200);

  pinMode( PIN_EMON1, INPUT );
  pinMode( PIN_EMON2, INPUT );
  pinMode( PIN_EMON3, INPUT );
  pinMode( PIN_EMON4, INPUT );
  pinMode( PIN_EMON5, INPUT );
  pinMode( PIN_EMON6, INPUT );
  pinMode( PIN_EMON7, INPUT );

  emon1.current(1, current_koef1);
  emon2.current(2, current_koef2);
  emon3.current(3, current_koef3);
  emon4.current(4, current_koef4);
  emon5.current(5, current_koef5);
  emon6.current(6, current_koef6);
  emon7.current(7, current_koef7);


  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);

  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(29, HIGH);
  digitalWrite(30, HIGH);
  digitalWrite(31, HIGH);
}
//  Блок LOOP  ------------------------------------------------------

void loop() {
    Serial.println("  PZEM_RX_PIN 12 ");
    Serial.println("  PZEM_TX_PIN 13");
    Serial.println("Трансформаторы тока pins A1,A2,A3,A4,A5,A6,A0");
    Serial.println("");

    Serial.print("Custom Address:");
    Serial.println(pzem.getAddress(), HEX);

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);
    }

    Serial.println();

    Serial.println("  Калиброка через 22 сек  (метки времени убрать)");
    delay(10222);
    Serial.println("  Старт автокалибровки");

float current_1 = emon1.calcIrms(1480);
float current_2 = emon2.calcIrms(1480);
float current_3 = emon3.calcIrms(1480);
float current_4 = emon4.calcIrms(1480);
float current_5 = emon5.calcIrms(1480);
float current_6 = emon6.calcIrms(1480);
float current_7 = emon7.calcIrms(1480);

current_koef1 = current / current_1;
current_koef2 = current / current_2;
current_koef3 = current / current_3;
current_koef4 = current / current_4;
current_koef5 = current / current_5;
current_koef6 = current / current_6;
current_koef7 = current / current_7;

Serial.println("   Результаты калиброки: ");
Serial.println("");

Serial.print("float current_koef1 = "); Serial.print(current_koef1);
Serial.println(";");
Serial.print("float current_koef2 = "); Serial.print(current_koef2);
Serial.println(";");
Serial.print("float current_koef3 = "); Serial.print(current_koef3);
Serial.println(";");
Serial.print("float current_koef4 = "); Serial.print(current_koef4);
Serial.println(";");
Serial.print("float current_koef5 = "); Serial.print(current_koef5);
Serial.println(";");
Serial.print("float current_koef6 = "); Serial.print(current_koef6);
Serial.println(";");
Serial.print("float current_koef7 = "); Serial.print(current_koef7);
Serial.println(";");

Serial.println("");
Serial.println(" Результаты калиброки надо скопировать и заменить");
Serial.println(" в файле boiler_down_init.h в Блоке Energy Monitor");
Serial.println("");
Serial.println("   П а у з а      на   2 минуты");
delay(15111);
Serial.println("     Пауза закончилась");

}
//  END  ------------------------------------------------------
