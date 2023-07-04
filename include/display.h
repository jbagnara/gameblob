#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define LCDC_ADDR       0xff40
#define TDATA_0_ADDR    0x8000
#define TDATA_1_ADDR    0x8800
#define TDATA_2_ADDR    0x9000
#define OAM_ADDR        0xfe00
#define TMAP_0_ADDR     0x9800
#define TMAP_1_ADDR     0x9c00


// using non gbc functionality
typedef struct LCDC_flags {
    uint8_t BG_win_en:      1;  // when cleared bg and win become blank
    uint8_t obj_en:         1;  // toggles whether objects are displayed
    uint8_t obj_size:       1;  // size of ALL objects (1 tile or 2 stacked)
    uint8_t bg_tilemap:     1;  // 0=0x9800 1=0x9c00   
    uint8_t bg_win_tdata:   1;  // addr mode for tile data
    uint8_t win_en:         1;  // whether window layer displayed or not
    uint8_t win_tilemap:    1;  // 0=0x9800 1=0x9c00
    uint8_t LCD_en:         1;  // whether lcd display is on or not
} LCDC_flags;

typedef struct obj_flags {
    uint8_t p_num_gbc:      3; // UNUSED
    uint8_t t_bank_gbc:     1; // UNUSED
    uint8_t p_num:          1;
    uint8_t x_flip:         1;
    uint8_t y_flip:         1;
    uint8_t over_obj:       1; // BG + WIN over OBJ
} obj_flags;

typedef struct obj_attr {
    uint8_t Y_pos;
    uint8_t X_pos;
    uint8_t Tile_idx;
    obj_flags f;
} obj_attr;

typedef uint8_t tile_t[16];

typedef struct display_t {
    LCDC_flags* LCDC;

    // vram
    tile_t* tdata_0;  // 0x8000-0x87ff tiles 0-127
    tile_t* tdata_1;  // 0x8800-0x8fff tiles 128-255
    tile_t* tdata_2;  // 0x9000-0x97ff
    uint8_t* tmap_0;   // 0x9800-0x9bff
    uint8_t* tmap_1;   // 0x9c00-0x9fff
    obj_attr* OAM;     // 0xfe00-0xfe9f 

    
} display_t;

void drawTileMap(uint8_t *tilemap, uint8_t *tileset);

#endif
