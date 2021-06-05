#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define SCR_WIDTH 80
#define SCR_HEIGHT 22

const char* luminance = ".,-~:;=!*#$@";

int flatten(int x, int y){
    int res;
    res = x + SCR_WIDTH * y;
    return res;
}

void clr_scr(void){
    printf("\033[2J");
}

int main() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z_buff[SCR_HEIGHT*SCR_WIDTH];
    char output[SCR_HEIGHT*SCR_WIDTH];
    clr_scr();
    while(true) {
        memset(output,32,1760);
        memset(z_buff,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = flatten(x, y);
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(SCR_HEIGHT > y && y > 0 && x > 0 && SCR_WIDTH > x && D > z_buff[o]) {
                    z_buff[o] = D;
                    output[o] = luminance[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < SCR_WIDTH*SCR_HEIGHT; k++) {
            putchar(k % SCR_WIDTH ? output[k] : '\n');
            A += 0.00004;
            B += 0.00002;
        }
        usleep(30000);
    }
    return 0;
}
