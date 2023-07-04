#include <machine.h>
#include <display.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    machine_t m;
    initDisplay(&m);

    uint8_t tiledata[] = {0x3C, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x5E, 0x7E, 0x0A, 0x7C, 0x56, 0x38, 0x7C};
    memcpy(&m.display.tdata_0[1], &tiledata, sizeof(tiledata));

    for(int i=0; i<32; i++){
        for(int j=0; j<32; j++){
            m.display.tmap_0[32*i+j] = j%2 ^ i%2;
        }
    }
    drawTileMap(m.display.tmap_0, m.display.tdata_0);
    sleep(5);
}
