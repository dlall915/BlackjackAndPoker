#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h> //SDL text output
#include <cstdlib>
#include <string> //deck struct, file output
#include <ctime> //random
#include <sstream> //string stream for total and score output

#include "deck.h"
#include "functionsclass.h"

int showmenu (SDL_Surface* screen, TTF_Font* font2, TTF_Font* font3) //outputs menu
{
        Uint32 time;
        int x, y, i, j; //mouse coordinates
        const int NUMMENU = 5;
        const char* labels[NUMMENU] = {"Play", "Instructions", "Exit", "ak", "Blackjack"};
        SDL_Surface* menus[NUMMENU];
        bool selected[(NUMMENU - 2)] = {0, 0, 0};
        SDL_Color color[2] = {{255, 255, 255}, {0, 0, 0}};
        TTF_Font* font = TTF_OpenFont ("AxeHandel.ttf", 30); //text font, size
        SDL_Rect pos[NUMMENU];

        SDL_FillRect (screen, &screen->clip_rect, SDL_MapRGB (screen->format, 0x00, 0x71, 0x00)); //fills output screen with specified color (green)

        menus[0] = TTF_RenderText_Solid (font, labels[0], color[1]);
        menus[1] = TTF_RenderText_Solid (font, labels[1], color[1]);
        menus[2] = TTF_RenderText_Solid (font, labels[2], color[1]);
        menus[3] = TTF_RenderText_Blended (font2, labels[3], color[1]);
        menus[4] = TTF_RenderText_Blended (font3, labels[4], color[1]);

        pos[0].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2; //position at middle of screen - half of the width of "Play"
        pos[0].y = 225;

        pos[1].x = screen->clip_rect.w/2 - menus[1]->clip_rect.w/2;
        pos[1].y = 295;

        pos[2].x = screen->clip_rect.w/2 - menus[2]->clip_rect.w/2;
        pos[2].y = 365;

        pos[3].x = screen->clip_rect.w/2 - menus[3]->clip_rect.w/2;
        pos[3].y = 25;

        pos[4].x = screen->clip_rect.w/2 - menus[4]->clip_rect.w/2;
        pos[4].y = 125;

        SDL_Event event;

        while (1)
        {
            time = SDL_GetTicks();
            while (SDL_PollEvent (&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        for (j = 0; j < NUMMENU; j++)
                            SDL_FreeSurface (menus[j]);
                        return 1;

                    case SDL_MOUSEMOTION:
                        x = event.motion.x;
                        y = event.motion.y;
                        for (i = 0; i < (NUMMENU - 2); i++)
                            {
                                if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                                    y >= pos[i].y && y <= pos[i].y + pos[i].h)
                                {
                                    if (!selected[i])
                                    {
                                        selected[i] = 1;
                                        SDL_FreeSurface (menus[i]);
                                        menus[i] = TTF_RenderText_Solid (font, labels[i], color[0]);
                                    }
                                }
                                else
                                {
                                    if (selected[i])
                                    {
                                        selected[i] = 0;
                                        SDL_FreeSurface (menus[i]);
                                        menus[i] = TTF_RenderText_Solid (font, labels[i], color[1]);
                                    }
                                }
                            }
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        x = event.button.x;
                        y = event.button.y;
                        for (i = 0; i < (NUMMENU - 2); i++)
                        {
                            if(x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                               y >= pos[i].y && y <= pos[i].y + pos[i].h &&
                               event.button.button == SDL_BUTTON_LEFT)
                            {
                                for (j = 0; j < NUMMENU; j++)
                                    SDL_FreeSurface (menus[j]);
                                return i;
                            }
                        }
                        break;

                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            for (j = 0; j < NUMMENU; j++)
                                SDL_FreeSurface (menus[j]);
                            return 0;
                        }
                }
            }

            for (i = 0; i < NUMMENU; i++)
                SDL_BlitSurface (menus[i], NULL, screen, &pos[i]);

            SDL_Flip(screen);
            if (1000/30 > (SDL_GetTicks() - time))
                SDL_Delay (1000/30 - (SDL_GetTicks() - time));
        }
}

void staticScreen (SDL_Surface*, SDL_Surface*, TTF_Font*, TTF_Font*, TTF_Font*); //outputs instructions, deck top, etc.

int main (int argc, char** argv)
{
    SDL_Init (SDL_INIT_EVERYTHING); //Initializes everything
    TTF_Init(); //Initializes TTF
    SDL_Surface *screen, *deck, *text;
    screen = SDL_SetVideoMode (800, 600, 32, SDL_SWSURFACE); //800x600 resolution, 32 bit, flag
    const int FPS = 30;
    Uint32 start; //unsigned integer 32 bits long
    //unsigned allows double the range of positive #s at the cost of negative #s

    srand((unsigned)time(0));

    bool running = true;

    deck = SDL_DisplayFormat (SDL_LoadBMP ("deck.bmp")); //loads bmp containing every card (http://www.jfitz.com/cards/)

    TTF_Font* font1 = TTF_OpenFont ("calibri.ttf", 16); //text font, size
    TTF_Font* font2 = TTF_OpenFont ("cards.ttf", 80);
    TTF_Font* font3 = TTF_OpenFont ("CaviarDreams.ttf", 40);

    SDL_Rect deckTopPos = {200, 150}, playerPos1 = {365, 490};

    blackjack game;

    int i = showmenu (screen, font2, font3);
    if (i == 2)
        running = false;

    if (i == 0)
    {
        ////////////////////////////////////////////////////////////////////////
        SDL_FreeSurface (screen);
        SDL_FillRect (screen, &screen->clip_rect, SDL_MapRGB (screen->format, 0x00, 0x71, 0x00)); //fills output screen with specified color (green)
        game.dealerDeal (screen, deck, text);
        staticScreen (screen, text, font1, font2, font3); //outputs instructions, deck top, etc.
        game.playerDeal (screen, deck, text);
    }

    while (running)
    {
        start = SDL_GetTicks(); //time in milliseconds
        SDL_Event event;
        int x, y;

        while (SDL_PollEvent (&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;

                if (event.button.button == SDL_BUTTON_MIDDLE) //new game on middle mouse click
                {
                    /////////////////////////////////////////////////////
                    SDL_FreeSurface (screen);
                    SDL_FillRect (screen, &screen->clip_rect, SDL_MapRGB (screen->format, 0x00, 0x71, 0x00)); //fills output screen with specified color (green)

                    game.reset();
                    game.dealerDeal (screen, deck, text);
                    staticScreen (screen, text, font1, font2, font3); //outputs instructions, deck top, etc.
                    game.playerDeal (screen, deck, text);
                }

                //draw card on deck left click
                if (x > deckTopPos.x && x < deckTopPos.x + 83 &&
                    y > deckTopPos.y && y < deckTopPos.y + 96 &&
                    event.button.button == SDL_BUTTON_LEFT)

                        game.playerDraw (screen, deck, text);

                //stand on player card left click
                if (x > playerPos1.x && x < playerPos1.x + 101 &&
                    y > playerPos1.y && y < playerPos1.y + 96 &&
                    event.button.button == SDL_BUTTON_LEFT)

                        game.outcome (screen, deck, text);

                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) //checks for key press
                {
                    case SDLK_n: //checks for N key down (new game)
                        /////////////////////////////////////////////////////
                        SDL_FreeSurface (screen);
                        SDL_FillRect (screen, &screen->clip_rect, SDL_MapRGB (screen->format, 0x00, 0x71, 0x00)); //fills output screen with specified color (green)

                        game.reset();
                        game.dealerDeal (screen, deck, text);
                        staticScreen (screen, text, font1, font2, font3); //outputs instructions, deck top, etc.
                        game.playerDeal (screen, deck, text);

                        break;

                    case SDLK_s: //checks for S key down (stand)
                        game.outcome (screen, deck, text);
                        break;

                    case SDLK_h: //checks for H key down (hit)
                        game.playerDraw (screen, deck, text);
                        break;

                    case SDLK_q: //checks for Q key down (quit)
                        running = false;
                        break;
                }
                break;
            }
        }

        //SDL_BlitSurface (textScore, NULL, screen, &score); //outputs score

        SDL_Flip (screen);
        if (1000/FPS > SDL_GetTicks() - start) //new frame every 33 milliseconds
            SDL_Delay (1000/FPS - (SDL_GetTicks() - start));
    }

    SDL_FreeSurface (deck); //remember to free every surface except the screen
    SDL_FreeSurface (text);

    TTF_Quit(); //Deinitialzes
    SDL_Quit();
    return 0;
}

void staticScreen (SDL_Surface* screen, SDL_Surface* text, TTF_Font* font1, TTF_Font* font2, TTF_Font* font3) //outputs instructions, deck top, etc.
{
    //deck top
    SDL_Surface *deckTop;
    deckTop = SDL_DisplayFormat (SDL_LoadBMP ("deckTop.bmp")); //loads bmp containing every card (http://www.jfitz.com/cards/)
    SDL_Rect deckTopPos = {200, 150}; //deck top position
    SDL_BlitSurface (deckTop, NULL, screen, &deckTopPos); //outputs the top of the deck
                   //image, whole image, destination, location
    SDL_FreeSurface (deckTop);


    //dealer's hole
    SDL_Surface *dealerHole;
    dealerHole = SDL_DisplayFormat (SDL_LoadBMP ("deckTopBig.bmp")); //loads bmp containing dealer's face down card
    SDL_Rect dealerHolePos = {530, 150}; //dealer's hole position
    SDL_BlitSurface (dealerHole, NULL, screen, &dealerHolePos); //outputs dealer's hole card
    SDL_FreeSurface (dealerHole);

    //instructions
    text = TTF_RenderText_Blended (font1, "H: Hit | S: Stand | N: New Game | Q: Quit", {255, 255, 255}); //instructions
    SDL_Rect textPos = {5, 581}; //instructions position
    SDL_BlitSurface (text, NULL, screen, &textPos); //outputs instructions
    SDL_FreeSurface (text);

    //Blackjack image
    text = TTF_RenderText_Blended (font2, "ak", {0, 0, 0}); //ace and jack of spades
    textPos = {49, 465}; //ace and jack of spades position
    SDL_BlitSurface (text, NULL, screen, &textPos); //outputs ace and jack
    SDL_FreeSurface (text);

    //Blackjack text
    text = TTF_RenderText_Blended (font3, "Blackjack", {0, 0, 0});
    textPos = {53, 410}; //position of "Blackjack"
    SDL_BlitSurface (text, NULL, screen, &textPos); //outputs "Blackjack"
    SDL_FreeSurface (text);
}
