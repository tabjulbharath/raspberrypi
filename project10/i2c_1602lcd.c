/********************************************************************************************
*Filename      : i2c1602_lcd.c
*Description   : test iic 1602 lcd
*Author        : Alan
*Website       : www.osoyoo.com
*Update        : 2017/07/03
*
* changes and updates
* Jan-14-2018 : R.Chambers    : rewrote functions to generalize and abstract the interfaces.
********************************************************************************************/
#include <stdio.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

int LCDAddr = 0x27;   // I2c LCD address, use sudo i2cdetect -y 1 after hooking up 1602
int BLEN = 1;         // 1--open backlight. 0--close backlight
int fd;               // I2C device linux file descriptor

void sendNibble (int bl, int rs, int rw, int data)
{
    int buf = (data & 0x0F) << 4;  // data nibble in upper nibble of byte

    // set the command pins data in the lower nibble of byte
    buf |= (bl) ? 0x08 : 0;    // set backlight on/off value
    buf |= 0x04;               // EN = 1, RW = 0, RS = 0
    buf |= (rw) ? 0x02 : 0;    // set RW value
    buf |= (rs) ? 0x01 : 0;    // set RS value
    wiringPiI2CWrite (fd, buf);

    delay (2);

    buf &= 0xFB;               // Make EN = 0 to turn off latch
    wiringPiI2CWrite (fd, buf);
}

//send command to lcd
void send_command(int comm)
{
    // Send upper nibble, bit 7-4 firstly
    sendNibble (BLEN, 0, 0, comm >> 4);

    // Send lower nibble, bit 3-0 secondly
    sendNibble (BLEN, 0, 0, comm);
}

//send data (text character) to lcd
void send_data(int data){
    // Send upper nibble, bit 7-4 firstly
    sendNibble (BLEN, 1, 0, data >> 4);

    // Send lower nibble, bit 3-0 secondly
    sendNibble (BLEN, 1, 0, data);
}

//clear screen
void clear1602(void)
{
    send_command (0x01); //clear display, set cursor to home position
}

//Print the message on the lcd
//initialize the lcd
void init1602 (void)
{
    send_command (0x33); // Must initialize to 8-line mode at first
    delay (5);

    send_command (0x32); // Then initialize to 4-line mode
    delay (5);

    send_command (0x28); // 4 bit mode, 2 Lines and 5x7 pixels character size
    delay (5);

    send_command (0x0C); // Enable display without cursor
    delay (5);

    clear1602 ();
    wiringPiI2CWrite (fd, 0x08);  // turn on backlight of LCD
}

void write (int xCol, int yRow, const char data[])
{
    int len = strlen (data);

    // 16 columns per row
    if (xCol < 0)  xCol = 0;
    if (xCol > 15) xCol = 15;

    // only two rows or lines, row 0 and row 1
    if (yRow < 0)  yRow = 0;
    if (yRow > 1)  yRow = 1;

    // Move cursor to either row 0 or row 1
    // row 0 -> 0x80 + xCol, row 1 -> 0xC0 + xCol
    int addr = 0x80 + 0x40 * yRow + xCol;
    send_command (addr);
    
    int i;
    for (i = 0; i < len; i++){
        send_data (data[i]);
    }
}

void print_info()
{
    printf ("\n");
    printf ("|***************************|\n");
    printf ("|    IIC 1602 LCD test      |\n");
    printf ("| --------------------------|\n");
    printf ("| | LCD |            | Pi   |\n");
    printf ("| --------------------------|\n");
    printf ("| | GND | connect to | GND  |\n");
    printf ("| | VCC | connect to | 5V   |\n");
    printf ("| | SDA | connect to | SDA.1|\n");
    printf ("| | SCL | connect to | SCL.1|\n");
    printf ("| --------------------------|\n");
    printf ("|                     OSOYOO|\n");
    printf ("|***************************|\n");
    printf ("Program is running...\n");
    printf ("Press Ctrl+C to end the program\n");
}

int main(int argc, char *argv[])
{

    //init I2C 
    fd = wiringPiI2CSetup (LCDAddr);
    if (fd < 0) {
        printf ("Error: I2C setup for 1602 LCD failed.\n");
        return 1;
    }

    init1602 ();

    print_info ();

    write (0, 0, "Hi man.Welcome ");
    write (0, 1, "to osoyoo.com");
    delay (3000);
    clear1602 ();

    int iCount = 0;
    while (1){
	char buf[24];

        iCount++;
	sprintf (buf, "Lesson13 cnt %d", iCount);
        write (0, 0, buf);
        write (0, 1, "IIC LCD Test");
        delay (2000);
    }
    return 0;
}
