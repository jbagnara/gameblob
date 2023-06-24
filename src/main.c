#include <machine.h>

int main()
{
    machine gameboy;
    while(1){
        exec(gameboy.cpu, gameboy.mem);
    }
}
