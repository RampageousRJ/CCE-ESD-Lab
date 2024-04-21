#include <LPC17xx.h>
#include <stdio.h>

#define RS_CTRL (1<<27)
#define EN_CTRL (1<<28)
#define DT_CTRL (0xF<<23)

unsigned long int temp1 = 0, temp2 = 0;

void lcd_init(void);
void lcd_com(void);
void clear_ports(void);
void delay_lcd(unsigned int);
void lcd_puts(unsigned char*);
void lcd_data(void);
void wr_cn(void);
void wr_dn(void);

void lcd_init(void) {
    LPC_GPIO0->FIODIR |= DT_CTRL | RS_CTRL | EN_CTRL;
    clear_ports();
    delay_lcd(3200);
    temp1 = 0x30; // Function set command
    lcd_com();
    delay_lcd(800);
    temp1 = 0x30; // Function set command
    lcd_com();
    delay_lcd(200);
    temp1 = 0x30; // Function set command
    lcd_com();
    delay_lcd(200);
    temp1 = 0x20; // DL=0, N=1, F=0 (4-bit interface)
    lcd_com();
    delay_lcd(200);

    // Initialize display
    temp1 = 0x28; // 4-bit, 2 lines, 5x8 font
    lcd_com();
    delay_lcd(200);
    temp1 = 0x0c; // Display ON, Cursor OFF, Blink OFF
    lcd_com();
    delay_lcd(200);
    temp1 = 0x06; // Entry mode: Increment cursor, no display shift
    lcd_com();
    delay_lcd(200);
    temp1 = 0x01; // Clear display
    lcd_com();
    delay_lcd(2000);
    return;
}

void clear_ports(void) {
    LPC_GPIO0->FIOCLR = DT_CTRL | RS_CTRL | EN_CTRL;
}

void delay_lcd(unsigned int r1) {
    unsigned int r;
    for(r=0; r<r1; r++);
    return;
}

void lcd_com(void) {
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_cn();
    delay_lcd(30000);
    temp2 = temp1 & 0x0f;
    temp2 = temp2 << 23;
    wr_cn();
    delay_lcd(30000);
    return;
}

void wr_cn() {
    LPC_GPIO0->FIOPIN = temp2;
    LPC_GPIO0->FIOCLR = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
}

void lcd_puts(unsigned char* buf) {
    unsigned int i=0;
    while(buf[i]!='\0') {
        temp1=buf[i];
        lcd_data();
        delay_lcd(800);
        i++;
        if(i==16) {
            temp1=0xc0;
            lcd_com();
            delay_lcd(800);
        }
    }
    return;
}

void lcd_data(void) {
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_dn();
    delay_lcd(30000);
    temp2 = temp1 & 0x0f;
    temp2 = temp2 << 23;
    wr_dn();
    delay_lcd(30000);
    return;
}

void wr_dn() {
    LPC_GPIO0->FIOPIN = temp2;
    LPC_GPIO0->FIOSET = RS_CTRL;
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    return;
}


    // Your scan logic goes here

   void scan(void) {
    unsigned char keys[4][4] = {
        {'1', '2', '3', '4'},
        {'5', '6', '7', '8'},
        {'9', '0', '+', '-'},
        {' ', ' ', ' ', ' '}
    };
    unsigned char row, col;
    char key_pressed = ' ';

    // Scan rows
    for (row = 0; row < 4; row++) {
        LPC_GPIO2->FIOPIN = (1 << (row + 10)) & 0x3c00;

        // Scan columns
        for (col = 0; col < 4; col++) {
            if (!(LPC_GPIO2->FIOPIN & (1 << (col + 14)))) {
                key_pressed = keys[row][col];
                break;
            }
        }
        if (col < 4) {
            break;
        }
    }

    if (key_pressed != ' ') {
        // Display the pressed key on LCD
        temp1 = key_pressed;
        lcd_data();
    }
}



int calculate(int a, int b, char op) {
    if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        // Handle invalid operator
        return 0;
    }
}

int main(void) {
    // Initialize GPIO ports
    LPC_GPIO2->FIODIR = 0x3c00;
    LPC_GPIO1->FIODIR = 0xf87fffff;
    // Initialize LCD
    lcd_init();
    // Your main code logic goes here
    while (1) {
        // Scan for input and display result
        scan();
    }
    return 0;
}
