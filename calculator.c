#include <reg52.h>
#include "LCD.h"

#define Error 13

char scan_key();
char get_key();
int get_num(char);
char get_func(char);
void DispError(int);
void disp_num(int);

sbit rA = P1^0;
sbit rB = P1^1;
sbit rC = P1^2;
sbit rD = P1^3;
sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;
sbit C4 = P1^7;

void main() {
    char key;
    int num1;
    char func;
    int num2;
    
    lcd_init();
    
    while(1) {
        key = get_key();
        lcd_cmd(0x01);  // Clear LCD
        lcd_data(key);
        num1 = get_num(key);
        
        if(num1 != Error) {
            key = get_key();
            lcd_data(key);
            func = get_func(key);
            
            if(func != 'e') {
                key = get_key();
                lcd_data(key);
                num2 = get_num(key);
                
                if(num2 != Error) {
                    key = get_key();
                    lcd_data(key);
                    
                    if(key == '=') {
                        switch(func) {
                            case '+': disp_num(num1 + num2); break;
                            case '-': disp_num(num1 - num2); break;
                            case 'x': disp_num(num1 * num2); break;
                            case '/': if(num2 == 0) DispError(2);  
																			else {
																				int tem = num1 *10;
																				int temp = tem/num2;
																				int rem = temp%10;
																				lcd_data( (temp/10) + 0x30);
																				lcd_data('.');
																				lcd_data( rem + 0x30);
																			} break;
                        }
                    } else if(key == 'C') {
                        lcd_cmd(0x01); 
                    } else {
                        DispError(0);
                    }
                }
            }
        }
    }
}

char scan_key() {
    rA = 0; rB = 1; rC = 1; rD = 1;
    if(C1 == 0) { delay(10000); while(C1 == 0); return '7';}
    if(C2 == 0) { delay(10000); while(C2 == 0); return '8';}
    if(C3 == 0) { delay(10000); while(C3 == 0); return '9';}
    if(C4 == 0) { delay(10000); while(C4 == 0); return '/';}
    
    rA = 1; rB = 0; rC = 1; rD = 1;
    if(C1 == 0) { delay(10000); while(C1 == 0); return '4';}
    if(C2 == 0) { delay(10000); while(C2 == 0); return '5';}
    if(C3 == 0) { delay(10000); while(C3 == 0); return '6';}
    if(C4 == 0) { delay(10000); while(C4 == 0); return 'x';}
    
    rA = 1; rB = 1; rC = 0; rD = 1;
    if(C1 == 0) { delay(10000); while(C1 == 0); return '1';}
    if(C2 == 0) { delay(10000); while(C2 == 0); return '2';}
    if(C3 == 0) { delay(10000); while(C3 == 0); return '3';}
    if(C4 == 0) { delay(10000); while(C4 == 0); return '-';}
    
    rA = 1; rB = 1; rC = 1; rD = 0;
    if(C1 == 0) { delay(10000); while(C1 == 0); return 'C';}
    if(C2 == 0) { delay(10000); while(C2 == 0); return '0';}
    if(C3 == 0) { delay(10000); while(C3 == 0); return '=';}
    if(C4 == 0) { delay(10000); while(C4 == 0); return '+';}
    
    return 'n';
}

char get_key() {
    char key = 'n';
    while(key == 'n')
        key = scan_key();
    return key;
}

int get_num(char ch) {
    switch(ch) {
        case '0': return 0; break;
        case '1': return 1; break;
        case '2': return 2; break;
        case '3': return 3; break;
        case '4': return 4; break;
        case '5': return 5; break;
        case '6': return 6; break;
        case '7': return 7; break;
        case '8': return 8; break;
        case '9': return 9; break;
        case 'C': lcd_cmd(0x01); return Error; break;
        default: DispError(0); return Error; break;
    }
}

char get_func(char chfc) {
    if(chfc == 'C') {
        lcd_cmd(0x01);
        return 'e';
    }
    if(chfc != '+' && chfc != '-' && chfc != 'x' && chfc != '/') {
        DispError(1);
        return 'e';
    }
    return chfc;
}

void DispError(int numb) {
    lcd_cmd(0x01);
    switch(numb) {
				case 0: lcd_string("Invalid Input"); break;
        case 1: lcd_string("Invalid Function"); break;
        case 2: lcd_string("Divide by Zero"); break;
        default: lcd_string("Error"); break;
    }
}

void disp_num(int numb) {
    unsigned char unitdigit;
		unsigned char tenthdigit;
    if(numb<0) {
			numb = -numb;
			lcd_data('-');
		}
		
		tenthdigit = (numb/10);
		
		if(tenthdigit != 0)
			lcd_data(tenthdigit + 0x30);
		
		unitdigit = numb - tenthdigit*10;
		
		lcd_data(unitdigit+0x30);
}