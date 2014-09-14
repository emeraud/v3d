#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SDL/SDL.h>

#include "Hello.h"
 
void pause();

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("SDL Init", NULL);

    pause();
 
    SDL_Quit();
 
    return EXIT_SUCCESS;


    for (int i=0; i<argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    Hello hello;
    hello.tellMe();

    return 1;
}

void pause()
{
    bool keepOn = true;
    SDL_Event event;
 
    while (keepOn)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                keepOn = false;
        }
    }
}
