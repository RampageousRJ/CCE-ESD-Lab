#define RS_CTRL 0x08000000 // P0.27 [register select bit (0 --- command register; 1 --- data register]
#define EN_CTRL 0x10000000 // P0.28	[enable bit]
#define DT_CTRL 0x07800000 // P0.23 - P0.26	[data bits]
#define mask_lcd 0xff807fff // P0.15 - P0.22 [keyboard (rows)]
#define mask_keys 0xe07fffff // P0.23 - P0.28 [reg_sel || enable || data]

void lcd_init(void); //intitalize
void clr_disp(void); //clear display
void lcd_com(unsigned int); //send command
void wr_cn(unsigned int); //divide 8 bit commands to two 4 bit and write to pins
void lcd_data(unsigned int); //send data
void wr_dn(unsigned int); //divide 8 bit data to two 4 bit and write to pins
void delay_lcd(unsigned int); //call some delay
void clear_ports(void); //clear all pins
void lcd_puts(unsigned char *); // write the message

void lcd_init(void) {
	LPC_PINCON->PINSEL1 &= 0xfc003fff; //P0.23 - P0.26
	
	//all outputs
	LPC_GPIO0->FIODIR |= EN_CTRL;
	LPC_GPIO0->FIODIR |= RS_CTRL;
	LPC_GPIO0->FIODIR |= DT_CTRL;
	
	clear_ports();
	delay_lcd(3200);
	
	lcd_com(0x30); //8bit
	delay_lcd(3000);
	
	lcd_com(0x30); //8bit mode
	delay_lcd(30000);
	
	lcd_com(0x30); //8bit mode
	delay_lcd(30000);
	
	lcd_com(0x20); //4bit mode
	delay_lcd(30000);
	
	lcd_com(0x28); //4bit, 2 lines
	delay_lcd(30000);
	
	lcd_com(0x0c); //display on; cursor off
	delay_lcd(800);
	
	lcd_com(0x06); //entry mode --- increment
	delay_lcd(800);
	
	lcd_com(0x01); //clear display and return to home
	delay_lcd(10000);
	
	lcd_com(0x80); //row 0, col 0
	delay_lcd(800);
	
	return;
}

void lcd_com(unsigned int cmd) {
	unsigned int cmd_nibble;
	
	cmd_nibble = (cmd & 0xf0) << 19;
	wr_cn(cmd_nibble);
	
	cmd_nibble = (cmd & 0x0f) << 23;
	wr_cn(cmd_nibble);
	
	delay_lcd(1000);
	
	return;
}

void wr_cn(unsigned int cnibble) {
	clear_ports();
	LPC_GPIO0->FIOPIN = cnibble; // assign value to pin
	LPC_GPIO0->FIOCLR = RS_CTRL; // command mode
	LPC_GPIO0->FIOSET = EN_CTRL; // enable
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL; //disable
	return;
}

void lcd_data(unsigned int data) {
	unsigned int data_nibble;
	
	data_nibble = (data & 0xf0) << 19;
	wr_dn(data_nibble);
	
	data_nibble = (data & 0x0f) << 23;
	wr_dn(data_nibble);
	
	delay_lcd(1000);
	
	return;
}

void wr_dn(unsigned int dnibble) {
	clear_ports();
	LPC_GPIO0->FIOPIN = dnibble; // assign value to pin
	LPC_GPIO0->FIOSET = RS_CTRL; // data mode
	LPC_GPIO0->FIOSET = EN_CTRL; // enable
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL; //disable
	return;
}

void delay_lcd(unsigned int delay) {
	unsigned int i;
	for(i=0; i<delay; i++);
	return;
}

void clr_disp(void) {
	lcd_com(0x01); // clear display
	delay_lcd(10000);
	return;
}

void clear_ports(void) {
	LPC_GPIO0->FIOCLR = (DT_CTRL | RS_CTRL | EN_CTRL); //clear all
	return;
}

void lcd_puts(unsigned char *msg) {
	unsigned int i = 0;
	while(msg[i] != '\0') {
		lcd_data(msg[i]);
		i++;
		if(i == 16) {
			lcd_com(0xc0); // row 1, col 0
		}
	}
	return;
}
