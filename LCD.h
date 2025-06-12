sbit E = P3^6;
sbit RS = P3^7;

void delay(int a) {
    int i;
    for(i = 0; i < a; i++);
}

void lcd_data(char t) {
    RS = 1;
    P2 = t;
    E = 1;
    delay(300);
    E = 0;
}

void lcd_cmd(char c) {
    RS = 0;
    P2 = c;
    E = 1;
    delay(300);
    E = 0;
}

void lcd_init() {
   delay(1500);
	lcd_cmd(0x30);
	delay(50);
	lcd_cmd(0x30);
	delay(10);

	lcd_cmd(0x38);
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	delay(2);
}

void lcd_string(char *str){
	while(*str){
		lcd_data(*str);
		str++;
	}
}