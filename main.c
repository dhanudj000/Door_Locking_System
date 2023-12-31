#include "main.h"

#pragma config WDTE = OFF //Watchdog timer disabled 

static void init_config(void) {
    //Write your initialization code here 
    init_matrix_keypad();
    init_clcd();
    init_i2c(9600);
    init_timer0();
    TRISB3 =0;
    GIE=1;
    PEIE=1;
}

unsigned char control_flag = SET_PASS ;
long int duty = 20 , period = 400;

void main(void) {
    init_config();
    //Calling initializing function
    
    unsigned char  key , reset = RESET_SCREEN;
    clcd_print("SET THE PASSWORD",LINE1(0));
    while (1) {
        key = read_matrix_keypad(STATE);
        switch(control_flag)
        {
            case SET_PASS:
                set_pass(key , &reset);
                break;
            case LOGIN_SCREEN:
                login_screen(key , &reset);
                break;
            case OPEN_DOOR:
                unlock_door(key , &reset);
                break;
        }
    }
}
unsigned char sys_pass[5];
void set_pass(unsigned char key , unsigned char *reset)
{
    static int i=0;
    if(*reset == RESET_SCREEN)
    {
        key = ALL_RELEASED;
        *reset = RESET_NOTHING;
    }
    if(key != ALL_RELEASED)
    {
        sys_pass[i++] = key;
        clcd_putch('*',LINE2(5+i));
    }
    if(i==4)
    {
        sys_pass[4] = '\0';
        eeprom_at24C04_str_write(0x00 , sys_pass);
        *reset = RESET_SCREEN;
        control_flag = LOGIN_SCREEN;
    }
}

void fetch_pass_from_eeprom(unsigned char *pass)
{
    for(unsigned char i =0 ; i<4 ;i++)
    {
        pass[i] = eeprom_at24C04_read(i); 
    }
}

void block_user()
{
    for(int i=5;i>=0;i--)
    {
        clcd_print("YOU ARE BLOCKED",LINE1(0));
        clcd_putch((i/10)+'0' , LINE2(0));
        clcd_putch((i%10)+'0' , LINE2(1));
        clcd_print(" SEC LEFT",LINE2(2));
        __delay_ms(1000);
    }
}

unsigned char user_pass[4] , fetch_pass[4];
void login_screen(unsigned char key , unsigned char *reset)
{
    static unsigned char i=0 , attempts = 5;
    if(*reset == RESET_SCREEN)
    {
        clear_screen();
        clcd_print("ENTER THE PASS:",LINE1(0));
        key = ALL_RELEASED;
        *reset = RESET_NOTHING;
        i = 0;
    }
    if(key != ALL_RELEASED)
    {
        user_pass[i++] = key;
        clcd_putch('*' , LINE2(5+i));
    }
    if(i == 4)
    {
        fetch_pass_from_eeprom(fetch_pass);
        if(strncmp(user_pass , fetch_pass , 4) == 0)
        {
            clear_screen();
            clcd_print(":) DOOR OPEN",LINE1(0));
            clcd_print("press * to lock the door",LINE2(0));
            *reset = RESET_SCREEN;
            control_flag = OPEN_DOOR;
        }
        else
        {
            if(--attempts == 0)
            {
                clear_screen();
                block_user();
                attempts =5;
                *reset = RESET_SCREEN;
            }
            else
            {
                *reset = RESET_SCREEN;
                clear_screen();
                clcd_putch(attempts+'0'  , LINE1(0));
                clcd_print(" ATTEMPTS LEFT",LINE1(1));
                __delay_ms(2000);
            }
        }
    }
}

void unlock_door(unsigned char key , unsigned char * reset)
{
    if(*reset == RESET_SCREEN)
    {
        duty = 40;
        key = ALL_RELEASED;
        *reset = RESET_NOTHING;
    }
    if(key == '*')
    {
        duty = 20;
        *reset = RESET_SCREEN;
        control_flag = LOGIN_SCREEN;
    }
}