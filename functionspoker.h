#ifndef FUNCTIONSPOKER_H_INCLUDED
#define FUNCTIONSPOKER_H_INCLUDED

class poker {
    int value, playerX = 640 - 75, dealerX = 640 - 187;
    bool gameOver = false, used[100] = { false }, hand[100] = { false };
    SDL_Rect image, dealerPos = {500, 260};
    TTF_Font* font1 = TTF_OpenFont ("calibri.ttf", 16);
    TTF_Font* font2 = TTF_OpenFont ("AxeHandel.ttf", 42);
  public:
    void reset ();
    void communityDraw (SDL_Surface*, SDL_Surface*, SDL_Surface*);
    void playerDeal (SDL_Surface*, SDL_Surface*);
    void outcome (SDL_Surface*, SDL_Surface*, SDL_Surface*);
};

void poker::reset ()
{
    playerX = 640 - 75;
    dealerX = 640 - 187;
    gameOver = false;

    for (int t = 1; t < 100; t++)
    {
        used[t] = false;
        hand[t] = false;
    }
}

void poker::communityDraw (SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* text)
{
	int random;

    dealerPos = {dealerX, 260};

    if (!gameOver)
    {
        random = rand() % 52 + 1;

        if (used[random])
            for (int k = 1 ; k <= 40 ; k++) //cycles through cards until an unused one is found
            {
                random = rand() % 52 + 1;

                if (!used[random])
                    break;
            }

        if (!used[random])
        {
            draw (random, value, image); //random value out, card value and image location returned
            used[random] = true;
            hand[random] = true;

            SDL_BlitSurface (deck, &image, screen, &dealerPos); //outputs 1st and 2nd player card

            dealerX += 75; //for second player card
        }

        if (dealerX > 827)
        {
            gameOver = true;
            outcome (screen, deck, text);
        }
    }
}


void poker::playerDeal (SDL_Surface* screen, SDL_Surface* deck)
{
	int random;
	SDL_Rect playerPos1;

	while (playerX < 715) //stops after 2 cards
    {
        playerPos1 = {playerX, 575}; //defines position of the 1st and 2nd player card

        random = rand() % 52 + 1;

        if (used[random])
            for (int k = 1 ; k <= 30 ; k++) //cycles through cards until an unused one is found
            {
                random = rand() % 52 + 1;

                if (!used[random])
                    break;
            }

        else
        {
            draw (random, value, image); //random value out, card value and image location returned
            used[random] = true;
            hand[random] = true;

            SDL_BlitSurface (deck, &image, screen, &playerPos1); //outputs 1st and 2nd player card

            playerX += 75; //for second player card
        }
    }
}

void poker::outcome (SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* text)
{
    SDL_FreeSurface (text);
    SDL_Rect outcomePos = {0, 25};
    text = TTF_RenderText_Blended (font2, "You lose!", {255, 255, 255});
    std::stringstream stream;

    for (int i = 1; i < 53; i++)
    {
        if (hand[i] && hand[(i + 13)] && hand[(i + 26)] && hand[(i + 39)])
        {
            text = TTF_RenderText_Blended (font2, "4 of a kind", {255, 255, 255});
            break;
        }

        if (hand[i] && hand[(i + 13)] && hand[(i + 26)])
        {
            text = TTF_RenderText_Blended (font2, "3 of a kind", {255, 255, 255});
            break;
        }

        if ((hand[i] && hand[(i + 13)]) || (hand[i] && hand[(i + 26)]) || (hand[i] && hand[(i + 39)]))
        {
            text = TTF_RenderText_Blended (font2, "2 of a kind", {255, 255, 255});
            break;
        }
    }
    outcomePos.x = screen->clip_rect.w/2 - text->clip_rect.w/2;
	SDL_BlitSurface (text, NULL, screen, &outcomePos); //outputs outcome text
}

#endif // FUNCTIONSPOKER_H_INCLUDED
