/*
  LCD_nokia8310.h - Library for Nokia 8310 LCD.
  Created by Alextrim/Alextrimux(Aleksei) , July 27 2015.
*/
#ifndef LCD_nokia8310_h
#define LCD_nokia8310_h

#include <Arduino.h>
#include <stdint.h>

#define LCD_RAM_BANKS 6 //84 *BYTES* per bank
#define LCD_ROWS_PER_BANK 8
#define LCD_BANK_SIZE 84 //bytes

#define LCD_X_RES 84 //Resolution X, BITS
#define LCD_Y_RES 48 //Resolution Y, BITS

#define LCD_CACHE_SIZE ((LCD_X_RES * LCD_Y_RES) / 8) //(84 * 48) bits -> 504 bytes
#define LCD_CMD 0
#define LCD_DATA 1

#define LCD_REL_BL 0
#define LCD_REL_BR 1
#define LCD_REL_TL 2
#define LCD_REL_TR 3

 
class NokiaLCD
{
  public:
		NokiaLCD(uint8_t XRES_pin, uint8_t XCS_pin, uint8_t SDA_pin, uint8_t SCLK_pin);
		void Init();
		void Deinit();
		void Cmd(byte data, uint8_t mode);

		void NOP();
		void HardReset();
		void Reset();
		void SendBit(uint8_t bit);
		void WriteData(uint8_t data);
		void ReadStatus(uint8_t statusReg);
		void SetEnableDisplay(uint8_t value);
		void SetReverse(uint8_t mode);
		void SetAllOn(uint8_t value);
		void SetMirrorY(uint8_t value);

		void SetYAddr(uint8_t);
		void SetXAddr(uint8_t);
		void SetAddr(uint8_t, uint8_t);

		void SetStartRow(uint8_t);
		void SetPower(uint8_t);
		void SetVPR(uint8_t);
		void SetFrameCalibrationMode(uint8_t);
		void SetTemperatureCoef(uint8_t);


		void Update();
		void Erase();
		void Set(uint8_t x, uint8_t y, uint8_t val);
		void SetCursor(uint8_t cx, uint8_t cy);
		void SetPrintMode(uint8_t pMode);
		void AddX(uint8_t);
		void AddY(uint8_t);
		int Print(char const *text, uint8_t cx, uint8_t cy);
		int Print(char const *);
		int PrintAt(char *, uint8_t, uint8_t);
  private:
    uint8_t XRES;
	uint8_t XCS;
	uint8_t SDA;
	uint8_t SCLK;
	byte LcdCache[LCD_CACHE_SIZE]; //504
	uint8_t curBank, curRow, curStartRow;
	uint8_t cx;
	uint8_t cy;
	uint8_t printMode;
	void Lcd_Clear();
};
 
#endif
