#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <machine.h>
#include <display.h>

SDL_Window* win;
SDL_Renderer* renderer;
SDL_Texture* texture;

void initDisplay(machine* m)
{
    m->display.LCDC = &(m->mem[LCDC_ADDR]);
    m->display.tdata_0 = &(m->mem[TDATA_0_ADDR]);
    m->display.tdata_1 = &(m->mem[TDATA_1_ADDR]);
    m->display.tdata_2 = &(m->mem[TDATA_2_ADDR]);
    m->display.OAM = &(m->mem[OAM_ADDR]);
    m->display.tmap_0 = &(m->mem[TMAP_0_ADDR]);
    m->display.tmap_1 = &(m->mem[TMAP_1_ADDR]);

    SDL_CreateWindowAndRenderer(1000, 1000, 0, &win, &renderer);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 256, 256);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
}

// val = 2bit color
// x_pos/y_pos 0-255
void drawPixel(uint8_t val, uint8_t x_pos, uint8_t y_pos)
{
    switch(val){
        case 0x0: SDL_SetRenderDrawColor(renderer, 0x9a, 0xc8, 0xeb, 0); break;
        case 0x1: SDL_SetRenderDrawColor(renderer, 0xf4, 0xcf, 0xdf, 0); break;
        case 0x2: SDL_SetRenderDrawColor(renderer, 0xf7, 0xf6, 0xcf, 0); break;
        case 0x3: SDL_SetRenderDrawColor(renderer, 0x57, 0x84, 0xba, 0); break;
        default: SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0);
    }
    SDL_RenderDrawPoint(renderer, x_pos, y_pos);
}

// 8x8 2-bit pixels
// x_pos/y_pos are coordinates on tilemap (ie 0-32)
void drawTile(uint8_t tile_addr, uint8_t *tileset, uint8_t x_pos, uint8_t y_pos)
{
    uint8_t* tile = &tileset[tile_addr*16];
    // iterate over rows
    for(size_t i=0; i<8; i++){
        uint8_t row_a = tile[i*2];
        uint8_t row_b = tile[i*2+1];

        // iterate over bits
        for(size_t j=0; j<8; j++){
            uint8_t bit1 = (row_a >> (7 - j)) & 0x1;
            uint8_t bit2 = (row_b >> (7 - j)) & 0x1;
            uint8_t val = bit1 << 1 | bit2;
            drawPixel(val, j+x_pos*8, i+y_pos*8);
        }
    }
}

void drawTileMap(uint8_t *tilemap, uint8_t *tileset)
{

    for(size_t x=0; x<32; x++){
        for(size_t y=0; y<32; y++){
            drawTile(tilemap[x+y*32], tileset, x, y);
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}
