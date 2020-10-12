#include <Arduino.h>

#include "fpc1020a.h"

HardwareSerial hwSerial(2);
FPC1020 fp(&hwSerial);

extern unsigned char l_ucFPID;
extern unsigned char rBuf[192];

void setup()
{
    Serial.begin(115200);

    delay(500);

    Serial.println("Setup done...");
}

void loop()
{
    if (Serial.available() > 0)
    {
        int mode = Serial.read() - 0x30;

        if (mode == 1)
        {
            Serial.println("Add Fingerprint, please put your finger on the Fingerprint Sensor.");

            unsigned char rtf = fp.Enroll(0);

            if (rtf == TRUE)
            {
                Serial.print("Success, your User ID is: ");
                Serial.println(0, DEC);
            }
            else if (rtf == FALSE)
            {
                Serial.println("Failed, please try again.");
            }
            else if (rtf == ACK_USER_OCCUPIED)
            {
                Serial.println("Failed, this User ID already exsits.");
            }
            else if (rtf == ACK_USER_EXIST)
            {
                Serial.println("Failed, this fingerprint already exsits.");
            }
            delay(2000);
        }

        if (mode == 2)
        {
            Serial.println("Mctch Fingerprint, please put your finger on the Sensor.");

            if (fp.Search())
            {
                Serial.print("Success, your User ID is: ");
                Serial.println(l_ucFPID, DEC);
            }
            else
            {
                Serial.println("Failed, please try again.");
            }
            delay(1000);
        }
    }
}