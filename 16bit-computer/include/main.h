#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 512
#define MAX_SIM_TIME 20 // clock edges to simulate

struct PixelIndex {
    int byte_index = -1; 
    int bit_index = -1; 
}; 