/*
	LCD_nokia8310.cpp - Library for Nokia 8310 LCD.
	Created by Alextrim/Alextrimux(Aleksei) , July 27 2015.
*/
 
#include <Arduino.h>
#include <stdint.h>
#include "LCD_nokia8310.h"

#define DEBUG 1
#if DEBUG
#define DBGPRINTF(txt) Serial.print(txt)
#else
#define DBGPRINTF(txt) 
#endif

//5 x 8
static const uint8_t charMap_5_8[] = {
	0x00,0x00,0x00,0x00,0x00,        // 20 SP
	0x00,0x00,0x5f,0x00,0x00,        // 21 !
	0x00,0x07,0x00,0x07,0x00,        // 22 "
	0x14,0x7f,0x14,0x7f,0x14,        // 23 #
	0x24,0x2a,0x7f,0x2a,0x12,        // 24 0x
	0x23,0x13,0x08,0x64,0x62,        // 25 %
	0x36,0x49,0x55,0x22,0x50,        // 26 &
	0x00,0x05,0x03,0x00,0x00,        // 27 '
	0x00,0x1c,0x22,0x41,0x00,        // 28 (
	0x00,0x41,0x22,0x1c,0x00,        // 29 )
	0x14,0x08,0x3e,0x08,0x14,        // 2a *
	0x08,0x08,0x3e,0x08,0x08,        // 2b +
	0x00,0x50,0x30,0x00,0x00,        // 2c ,
	0x08,0x08,0x08,0x08,0x08,        // 2d -
	0x00,0x60,0x60,0x00,0x00,        // 2e .
	0x20,0x10,0x08,0x04,0x02,        // 2f /
	0x3e,0x51,0x49,0x45,0x3e,        // 30 0
	0x00,0x42,0x7f,0x40,0x00,        // 31 1
	0x42,0x61,0x51,0x49,0x46,        // 32 2
	0x21,0x41,0x45,0x4b,0x31,        // 33 3
	0x18,0x14,0x12,0x7f,0x10,        // 34 4
	0x27,0x45,0x45,0x45,0x39,        // 35 5
	0x3c,0x4a,0x49,0x49,0x30,        // 36 6
	0x01,0x71,0x09,0x05,0x03,        // 37 7
	0x36,0x49,0x49,0x49,0x36,        // 38 8
	0x06,0x49,0x49,0x29,0x1e,        // 39 9
	0x00,0x36,0x36,0x00,0x00,        // 3a :
	0x00,0x56,0x36,0x00,0x00,        // 3b ;
	0x08,0x14,0x22,0x41,0x00,        // 3c <
	0x14,0x14,0x14,0x14,0x14,        // 3d =
	0x00,0x41,0x22,0x14,0x08,        // 3e >
	0x02,0x01,0x51,0x09,0x06,        // 3f ?
	0x32,0x49,0x79,0x41,0x3e,        // 40 @
	0x7e,0x11,0x11,0x11,0x7e,        // 41 A
	0x7f,0x49,0x49,0x49,0x36,        // 42 B
	0x3e,0x41,0x41,0x41,0x22,        // 43 C
	0x7f,0x41,0x41,0x22,0x1c,        // 44 D
	0x7f,0x49,0x49,0x49,0x41,        // 45 E
	0x7f,0x09,0x09,0x09,0x01,        // 46 F
	0x3e,0x41,0x49,0x49,0x7a,        // 47 G
	0x7f,0x08,0x08,0x08,0x7f,        // 48 H
	0x00,0x41,0x7f,0x41,0x00,        // 49 I
	0x20,0x40,0x41,0x3f,0x01,        // 4a J
	0x7f,0x08,0x14,0x22,0x41,        // 4b K
	0x7f,0x40,0x40,0x40,0x40,        // 4c L
	0x7f,0x02,0x0c,0x02,0x7f,        // 4d M
	0x7f,0x04,0x08,0x10,0x7f,        // 4e N
	0x3e,0x41,0x41,0x41,0x3e,        // 4f O
	0x7f,0x09,0x09,0x09,0x06,        // 50 P
	0x3e,0x41,0x51,0x21,0x5e,        // 51 Q
	0x7f,0x09,0x19,0x29,0x46,        // 52 R
	0x46,0x49,0x49,0x49,0x31,        // 53 S
	0x01,0x01,0x7f,0x01,0x01,        // 54 T
	0x3f,0x40,0x40,0x40,0x3f,        // 55 U
	0x1f,0x20,0x40,0x20,0x1f,        // 56 V
	0x3f,0x40,0x38,0x40,0x3f,        // 57 W
	0x63,0x14,0x08,0x14,0x63,        // 58 X
	0x07,0x08,0x70,0x08,0x07,        // 59 Y
	0x61,0x51,0x49,0x45,0x43,        // 5a Z
	0x00,0x7f,0x41,0x41,0x00,        // 5b [
	0x02,0x04,0x08,0x10,0x20,        // 5c '\'
	0x00,0x41,0x41,0x7f,0x00,        // 5d ]
	0x04,0x02,0x01,0x02,0x04,        // 5e ^
	0x40,0x40,0x40,0x40,0x40,        // 5f _
	0x00,0x01,0x02,0x04,0x00,        // 60 '
	0x20,0x54,0x54,0x54,0x78,        // 61 a
	0x7f,0x48,0x44,0x44,0x38,        // 62 b
	0x38,0x44,0x44,0x44,0x20,        // 63 c
	0x38,0x44,0x44,0x48,0x7f,        // 64 d
	0x38,0x54,0x54,0x54,0x18,        // 65 e
	0x08,0x7e,0x09,0x01,0x02,        // 66 f
	0x0c,0x52,0x52,0x52,0x3e,        // 67 g
	0x7f,0x08,0x04,0x04,0x78,        // 68 h
	0x00,0x44,0x7d,0x40,0x00,        // 69 i
	0x20,0x40,0x44,0x3d,0x00,        // 6a j
	0x7f,0x10,0x28,0x44,0x00,        // 6b k
	0x00,0x41,0x7f,0x40,0x00,        // 6c l
	0x7c,0x04,0x18,0x04,0x78,        // 6d m
	0x7c,0x08,0x04,0x04,0x78,        // 6e n
	0x38,0x44,0x44,0x44,0x38,        // 6f o
	0x7c,0x14,0x14,0x14,0x08,        // 70 p
	0x08,0x14,0x14,0x18,0x7c,        // 71 q
	0x7c,0x08,0x04,0x04,0x08,        // 72 r
	0x48,0x54,0x54,0x54,0x20,        // 73 s
	0x04,0x3f,0x44,0x40,0x20,        // 74 t
	0x3c,0x40,0x40,0x20,0x7c,        // 75 u
	0x1c,0x20,0x40,0x20,0x1c,        // 76 v
	0x3c,0x40,0x30,0x40,0x3c,        // 77 w
	0x44,0x28,0x10,0x28,0x44,        // 78 x
	0x0c,0x50,0x50,0x50,0x3c,        // 79 y
	0x44,0x64,0x54,0x4c,0x44,        // 7a z
	0x00,0x08,0x36,0x41,0x00,        // 7b {
	0x00,0x00,0x7f,0x00,0x00,        // 7c ¦
	0x00,0x41,0x36,0x08,0x00,        // 7d }
	0x10,0x08,0x08,0x10,0x08,        // 7e ~
	0x78,0x46,0x41,0x46,0x78         // 7f
};
#define NUMCHARS (sizeof(charMap_5_8) / 5)
 
NokiaLCD::NokiaLCD(uint8_t XRES_pin, uint8_t XCS_pin, uint8_t SDA_pin, uint8_t SCLK_pin){
	pinMode(XRES_pin, OUTPUT);
	pinMode(XCS_pin , OUTPUT);
	pinMode(SDA_pin , OUTPUT);
	pinMode(SCLK_pin, OUTPUT);
	this->XRES = XRES_pin;
	this->XCS = XCS_pin;
	this->SDA = SDA_pin;
	this->SCLK = SCLK_pin;
}

void NokiaLCD::HardReset(){
	digitalWrite(XRES,LOW);
	delay(10);
	digitalWrite(XRES,HIGH);
	this->Reset();
}

void NokiaLCD::Init(){
	this->HardReset();
	this->SetVPR(144); //or 127 perhaps
	this->SetAllOn(0);
	this->SetPower(B111);
	this->SetMirrorY(0);
	this->SetFrameCalibrationMode(0);
	this->SetReverse(0); //normal mode

	this->Lcd_Clear(); // clear LCD
	//this->SetReverse(1); //reverse mode
	this->SetStartRow(0);

	
	this->SetCursor(0, 0);
	this->SetPrintMode(LCD_REL_TL);
}

void NokiaLCD::Deinit(){
	this->SetEnableDisplay(0);
	this->SetAllOn(1);
	this->SetPower(B000);
	this->SetVPR(0);
}

void NokiaLCD::SendBit(uint8_t bit){
	digitalWrite(SCLK, LOW); // tick
	//delayMicroseconds(1);
	digitalWrite(SDA, bit); //HIGH or LOW
	digitalWrite(SCLK, HIGH); // tock
	//delayMicroseconds(1);
}

void NokiaLCD::Cmd(uint8_t data, uint8_t mode)
{
	digitalWrite(XCS, LOW);
	
	uint8_t i=7;	
	this->SendBit(mode);

	do {
		this->SendBit(data & (1 << i)); //1 if bit is set, 0 otherwise
	} while(i-- != 0);
	digitalWrite(XCS, HIGH);
}

void NokiaLCD::Update(){
	this->SetAddr(0, 0);
	for(uint16_t i = 0; i < LCD_CACHE_SIZE; i++){
		Cmd( LcdCache[i], LCD_DATA );
	}
}

void NokiaLCD::Lcd_Clear(void){
	this->SetAddr(0, 0);
	this->SetEnableDisplay(0);
	this->Erase();
	this->Update();
	this->SetEnableDisplay(1);
}

void NokiaLCD::Erase(void){
	memset(&LcdCache, 0x00, LCD_CACHE_SIZE);
	this->SetCursor(0, 0);
}

void NokiaLCD::Set(uint8_t x, uint8_t y, uint8_t v){
	//Each bank is 8 rows
	//(y / LCD_ROWS_PER_BANK) -> bank Number

	//Determine which bank holds col y, and add x
	// x is which column
	uint16_t p = ((y / LCD_ROWS_PER_BANK) * LCD_BANK_SIZE) + x;
	//Offset in the column
	uint8_t u = y % LCD_ROWS_PER_BANK;
	if(v){
		LcdCache[p] |= (1 << u); //set, black
	} else {
		LcdCache[p] &= ~(1 << u); //clear, white
	}
}

/*
 * Print chars in 5x8 font
 */

void NokiaLCD::SetPrintMode(uint8_t pMode){
	this->printMode = pMode;
}

void NokiaLCD::SetCursor(uint8_t cx, uint8_t cy){
	this->cx = cx;
	this->cy = cy;
}

void NokiaLCD::AddX(uint8_t ax){
	if((uint16_t)this->cx + ax > LCD_X_RES){
		//return to start
		this->cx = 0;
		this->cy = 0;
	} else {
		this->cx += ax;
	}
}
void NokiaLCD::AddY(uint8_t ay){
	if((uint16_t)this->cy + ay > LCD_Y_RES){
		this->cx += 6;
		this->cy = 0;
	} else {
		this->cy += ay;
	}
}

int NokiaLCD::PrintAt(char *text, uint8_t row, uint8_t col){
	return this->Print(text, row * 8, col * 6);
}


int NokiaLCD::Print(char const *text, uint8_t cx, uint8_t cy){
	this->SetCursor(cx, cy);
	return this->Print(text);
}

int NokiaLCD::Print(char const *text){
	size_t len = strlen(text);
	/* For each char */
	for(unsigned int i=0; i<len; i++){
		int ch = text[i];
		if(ch - 0x20 > (int)NUMCHARS){
			return -1;
		}

		switch(ch){
			/* Override 5 pixels space with 2 pixels only */
			case ' ':
				this->cy += 2;
				continue;
				break;
			case '\n':
				this->cx += 8;
				this->cy = 0;
				continue;
				break;
		}

		/*
		* To print in horizontal/landscape mode
		* (1) Get character start
		* (2) Get char line (j)
		* (3) Process line in reverse (MSB first)
		* (4) Map row to column and column to row (x to y, y to x)
		*/
		
		//each char is 5 lines (5 bytes from data)
		for(uint8_t j=0; j<5; j++){
			uint8_t v = charMap_5_8[(5 * (ch - 0x20)) + j]; //char line
			//Serial.print(">> "); Serial.println(v);

			//print line
			uint8_t k=7;
			do {
				//charmap in reverse order...MSB first...
				uint8_t b;
				if(this->printMode == LCD_REL_TL){
					b = ((v >> 7) & 1);
					v <<= 1;
				} else {
					b = (v & 1);
					v >>= 1;
				}
				this->Set(this->cy + j, this->cx + k, b); //Invert char: x->y and y->x (due to inverted charmap)
			} while(k-- != 0);
		}
		this->cy += 6; //Included 1 space between chars
	}
	return 0;
}

/******** LCD COMMANDs ********/

void NokiaLCD::NOP(){
	Cmd( B11100011, LCD_CMD );
}
void NokiaLCD::Reset(){
	Cmd( B11100010, LCD_CMD );
}
void NokiaLCD::WriteData(uint8_t data){
	Cmd( data, LCD_DATA );
}
void NokiaLCD::ReadStatus(uint8_t statusReg){
	Cmd( B11011000 | (statusReg & 1), LCD_CMD );
}
//on, off
void NokiaLCD::SetEnableDisplay(uint8_t value){
	Cmd( B10101110 | (value & 1), LCD_CMD );
}
//normal, reverse
void NokiaLCD::SetReverse(uint8_t mode){
	Cmd( B10100110 | (mode & 1), LCD_CMD );
}
//on, off
void NokiaLCD::SetAllOn(uint8_t value){
	Cmd( B10100100 | (value & 1), LCD_CMD );
}
//on,off
void NokiaLCD::SetMirrorY(uint8_t value){
	Cmd( B11000000 | ((value << 3) & 1), LCD_CMD );
}
void NokiaLCD::SetYAddr(uint8_t yaddr){
	this->curBank = yaddr;
	Cmd( B10110000 | (yaddr & 7), LCD_CMD );
}
void NokiaLCD::SetXAddr(uint8_t xaddr){
	this->curRow = xaddr;
	Cmd( B00010000 | ((xaddr >> 4) & 7), LCD_CMD ); //b 6,5,4
	Cmd( B00000000 | (xaddr & 0xF), LCD_CMD ); //b 3,2,1,0
}
void NokiaLCD::SetAddr(uint8_t bankNo, uint8_t byteOffset){
	this->SetYAddr(bankNo);
	this->SetXAddr(byteOffset);
}

void NokiaLCD::SetStartRow(uint8_t row){
	this->curStartRow = row;
	Cmd( B01000000 | (row & 0x3F), LCD_CMD );
}
void NokiaLCD::SetPower(uint8_t value){
	Cmd( B00101000 | (value & 7), LCD_CMD );
}

//Contrast
void NokiaLCD::SetVPR(uint8_t value){
	Cmd( B00100000 | ((value >> 5) & 7), LCD_CMD ); //b 7,6,5
	Cmd( B10000000 | (value & 0x1F), LCD_CMD ); //b 4,3,2,1,0
}

void NokiaLCD::SetFrameCalibrationMode(uint8_t value){
	Cmd( B10101100 | (value & 1), LCD_CMD );
}
void NokiaLCD::SetTemperatureCoef(uint8_t value){
	Cmd( B00111000 | (value & 3), LCD_CMD );
}


/////////// END IMPLEMENTATION

NokiaLCD lcd(3,4,5,6); //84 x 48

#define SNAKESTARTLEN 5

#define SNAKE_RIGHT B00
#define SNAKE_LEFT B01
#define SNAKE_UP B10
#define SNAKE_DOWN B11


uint8_t snakeHeadX = 0, snakeHeadY = 0;
uint8_t snakeDir = SNAKE_RIGHT;
uint16_t snakeLen = SNAKESTARTLEN;

struct SnakeSeg {
	uint8_t x;
	uint8_t y;
};

struct SnakeSeg snakeSegs[255]; //segments circular buffer
uint8_t snakeStartIdx = 0;
uint8_t snakeEndIdx = 0;
uint8_t gameRunning = 1;

const char snakeLooseMsg[] = "\n\n\n        HAI PERSO!";

uint8_t eaten = 0;
uint8_t food_x, food_y;
void makeFood(){
	food_x = random(0, LCD_X_RES - 1);
	food_y = random(0, LCD_Y_RES - 1);
}

void snakeInit(){
	snakeDir = SNAKE_RIGHT;
	snakeLen = SNAKESTARTLEN;
	memset(&snakeSegs, 0x00, sizeof(snakeSegs));
	makeFood();
}

void setup(){
	Serial.begin(9600);
	Serial.println("Starting up...");
	lcd.Init();

	/*
	lcd.Erase();
	char x[] = "A";
	for(int i=0; i<NUMCHARS/3; i++){
		lcd.PrintAt(x, 0, i);
		x[0]++;
	}
	lcd.Update();
	*/

	snakeInit();
}

void snakeDraw(){
	//Overflow will get us there
	for(uint8_t i=snakeStartIdx; i!=snakeEndIdx; i++){
		if(
			snakeHeadX == snakeSegs[i].x &&
			snakeHeadY == snakeSegs[i].y
		){
			lcd.Print((char *)&snakeLooseMsg);
			Serial.println((char *)&snakeLooseMsg);
			gameRunning = 0;
		} else {
			lcd.Set(snakeSegs[i].x, snakeSegs[i].y, 1);
		}
	}

	if(snakeHeadX == food_x && snakeHeadY == food_y){
		snakeLen++;
		makeFood();
	}
	lcd.Set(food_x, food_y, 1);
	lcd.Update();
}

void loop(){
	int16_t input = Serial.read();
	while(Serial.read() != -1);

	switch(input){
		//right
		case 54:
			if(snakeDir != SNAKE_LEFT)
				snakeDir = SNAKE_RIGHT;
			break;
		//left
		case 52:
			if(snakeDir != SNAKE_RIGHT)
				snakeDir = SNAKE_LEFT;
			break;
		//down
		case 50:
			if(snakeDir != SNAKE_UP)
				snakeDir = SNAKE_DOWN;
			break;
		//up
		case 56:
			if(snakeDir != SNAKE_DOWN)
				snakeDir = SNAKE_UP;
			break;
	}

	if(!gameRunning){
		if(input != 0x20) //wait for Space to restart
			return;
		else {
			lcd.Erase();
			snakeInit();
			gameRunning = 1;
		}
	}

	switch(snakeDir){
		case SNAKE_UP:
			snakeHeadY--;
			if(snakeHeadY >= (LCD_Y_RES - 1))
				snakeHeadY = LCD_Y_RES - 1;
			break;
		case SNAKE_DOWN:
			snakeHeadY++;
			if(snakeHeadY >= (LCD_Y_RES - 1))
				snakeHeadY = 0;
			break;
		case SNAKE_LEFT:
			snakeHeadX--;
			if(snakeHeadX >= (LCD_X_RES - 1))
				snakeHeadX = LCD_X_RES - 1;
			break;
		case SNAKE_RIGHT:
			snakeHeadX++;
			if(snakeHeadX >= (LCD_X_RES - 1))
				snakeHeadX = 0;
			break;
	}

	//draw Snake
	snakeDraw();
	Serial.print(snakeHeadX);Serial.print(" ");Serial.println(snakeHeadY);
	delay(50);

	snakeSegs[snakeEndIdx++] = {
		.x = snakeHeadX,
		.y = snakeHeadY
	};
	if(snakeEndIdx > (snakeLen - 1)){
		snakeStartIdx = (snakeEndIdx - snakeLen - 1);
	}


	lcd.Erase();
}
