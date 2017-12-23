#include <psp2/kernel/processmgr.h>
#include <psp2/message_dialog.h>
#include <psp2/ime_dialog.h>

#include <string>
#include <inttypes.h>
#include <stdint.h>

#include "utils.hpp"
#include "graphics.hpp"
#include "colors.hpp"
#include "filesystem.hpp"
#include "io.hpp"

#include "game.hpp"
#include <psp2/gxm.h>

#include "preloaded.hpp"


int main(int argc, char *argv[])
{
    int framecount = 0;
    std::string idleFile = "ux0:/test/idle.rgba";
    std::string rightRunFile = "ux0:/test/rightrun.rgba";
    
    graphics::enableTouchControl(); //Vita2d and Selfmade
    graphics::setUp(); //Turn off system control of screen off and timeout; // TODO
    
    graphics::initializeFramebuffers(); //Selfmade
    
    
    filesystem::preloadTiles();
    
    game::player = game::Player();

    
    
    
    
    
    
    bool exit = false;
    while(!exit)
    {
        graphics::colorScreen(colors::BLACK16); //Flush screen BLACK.
        utils::printsf(700, 0, colors::WHITE32, "Frame: %d", framecount); //Print out frame number.
        io::getio();    //Vita2d and Selfmade //Read Input
        game::checkInput(io::pad); //Interpret Input
        
        game::drawPlayer();

        
        uint32_t pixelsSaved[100][100];
        for(unsigned int x = 20; x <  80; x++)
        {
            for(unsigned int y = 250; y < 320; y++)
            {
                
                if( (int)(framecount/5)%3 == 0)
                {
                    if(y%10 < 5)
                        pixelsSaved[x][y] = graphics::getPixel(x+1+((int)(framecount/5)%3),y);
                    else
                        pixelsSaved[x][y] = graphics::getPixel(x-1-((int)(framecount/5)%3),y);
                }
                else
                {
                    if(y%10 < 5)
                        pixelsSaved[x][y] = graphics::getPixel(x-((int)(framecount/5)%3),y);
                    else
                        pixelsSaved[x][y] = graphics::getPixel(x+((int)(framecount/5)%3),y);
                }
                pixelsSaved[x][y] ^=  0x00FF0000;
            }
        }
        for(unsigned int x = 20; x <  80; x++)
        {
            for(unsigned int y = 250; y < 320; y++)
            {
                graphics::draw_pixel(x,y, pixelsSaved[x][y]);
            }
        }
     
        
        graphics::draw_tile(0, 400,300);
        
        
        
        utils::printsf(10, 20, colors::WHITE32, "pos x: %d, y: %d", game::player.position.x, game::player.position.y); //Print out frame number.
        utils::printsf(10, 50, colors::WHITE32, "lx x: %d,", io::pad.lx); //Print out left-axis value.
        
    

        graphics::swapFramebuffers(); //Selfmade
        sceDisplayWaitVblankStart();
        framecount+=1;
    }
    
   
    graphics::freeFramebuffers(); //Vita2d and Selfmade
    sceKernelExitProcess(0);
    return 0;
}


