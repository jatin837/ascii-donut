#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define SCR_WIDTH 80
#define SCR_HEIGHT 22
#define DELAY 3e4

const char* luminance = ".,-~:;=!*#$@";

int flatten(int x, int y){
    int res;
    res = x + SCR_WIDTH * y;
    return res;
}

void clr_scr(void){
    printf("\033[2J");
}
void move_curs_to_home(void){
    printf("\x1b[H");
}

int main() {
    float A = 0, B = 0;
    float i, j;
    float z_buff[SCR_HEIGHT*SCR_WIDTH];
    char output[SCR_HEIGHT*SCR_WIDTH];
    clr_scr();
    while(true) {
        memset(output,32,1760);
        memset(z_buff,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float sini = sin(i); //c
                float cosj = cos(j); //d
                float sinA = sin(A); //e
                float sinj = sin(j); //f
                float cosA = cos(A); //g
                float h = cosj + 2;  
                float D = 1 / (sini * h * sinA + sinj * cosA + 5);
                float cosi = cos(i); //l
                float cosB = cos(B);   //m
                float sinB = sin(B);   //n
                float t = sini * h * cosA - sinj * sinA;
                int x = 40 + 30 * D * (cosi * h * cosB - t * sinB);
                int y= 12 + 15 * D * (cosi * h * sinB + t * cosB);
                int o = flatten(x, y);
                int N = 8 * ((sinj * sinA - sini * cosj * cosA) * cosB - sini * cosj * sinA - sinj * cosA - cosi * cosj * sinB);
                if(y < SCR_HEIGHT && y > 0 && x > 0 &&  x < SCR_WIDTH && D > z_buff[o]) {
                    z_buff[o] = D;
                    output[o] = luminance[N > 0 ? N : 0];
                }
            }
        }
        move_curs_to_home();
        for(int k = 0; k < SCR_WIDTH*SCR_HEIGHT; k++) {
            putchar(k % SCR_WIDTH ? output[k] : '\n');
            A += 0.00004;
            B += 0.00002;
        }
        usleep(DELAY);
    }
    return 0;
}
