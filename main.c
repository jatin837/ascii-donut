#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define PI M_PI
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
    printf("\033[H");
}

int main() {
    float A = 0, B = 0;
    long long int frame;
    float i, j;
    float z_buff[SCR_HEIGHT*SCR_WIDTH];
    char output[SCR_HEIGHT*SCR_WIDTH];
    clr_scr();
    while(true) {
        memset(output, '.', SCR_HEIGHT*SCR_WIDTH);
        memset(z_buff, '\0', SCR_HEIGHT*SCR_WIDTH*4);
        for(j=0; j < 2*PI; j += 0.07) {
            for(i=0; i < 2*PI; i += 0.02) {
                float sini = sin(i);
                float cosj = cos(j);
                float sinA = sin(A);
                float sinj = sin(j);
                float cosA = cos(A);
                float h = cosj + 2;  
                float D = 1 / (sini * h * sinA + sinj * cosA + 5);
                float cosi = cos(i);
                float cosB = cos(B);
                float sinB = sin(B);
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
            A += 4e-5;
            B += 2e-5;
        }
        printf("%lld", ++frame);
        usleep(DELAY);
    }
    return 0;
}
