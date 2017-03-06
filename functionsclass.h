#ifndef FUNCTIONSCLASS_H_INCLUDED
#define FUNCTIONSCLASS_H_INCLUDED

class blackjack {
    int totalP = 0, totalD = 0, playerX = 425, value;
    bool acePlayer = false, aceDealer = false, gameOver = false, used[53] = { false };
    SDL_Rect image, dealerPos = {500, 150}, totalPosP = {725, 572, 75, 19}, totalPosD = {725, 233, 75, 19};
    TTF_Font* font1 = TTF_OpenFont ("calibri.ttf", 16);
    TTF_Font* font2 = TTF_OpenFont ("AxeHandel.ttf", 42);
  public:
    void reset ();
    void dealerDeal (SDL_Surface*, SDL_Surface*, SDL_Surface*);
    void playerDeal (SDL_Surface*, SDL_Surface*, SDL_Surface*);
    void playerDraw (SDL_Surface*, SDL_Surface*, SDL_Surface*);
    void outcome (SDL_Surface*, SDL_Surface*, SDL_Surface*);
};

//resets values for new game
void blackjack::reset ()
{
    totalP = 0;
    totalD = 0;
    playerX = 425;
    acePlayer = false;
    aceDealer = false;
    gameOver = false;
    used[53] = { false };
}

//draws first dealer card, no random test since this is the 1st card on the table
void blackjack::dealerDeal (SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* text)
{
	int random;
    std::stringstream stream;

    random = rand() % 52 + 1;

    draw (random, value, image); //random value out, card value and image location returned
    used[random] = true;

    if ((value == 1) && (totalD <= 10)) //Ace
        {
            totalD = totalD + value + 10; //Ace value of 11
            aceDealer = true;
        }

    else
        totalD += value;

    if (aceDealer == true && totalD >= 22 && totalD <=30) //changes Ace to value of 1 if next card(s) busts
    {
        aceDealer = false; //avoids subtracting 10 after every bust when an ace is drawn
        totalD -= 10;
    }

    SDL_BlitSurface (deck, &image, screen, &dealerPos); //outputs 1st random card for dealer before any key press

    stream << "Total: " << totalD;
    text = TTF_RenderText_Blended (font1, stream.str().c_str(), {255, 255, 255}); //total
    SDL_BlitSurface (text, NULL, screen, &totalPosD); //outputs total
    SDL_FreeSurface (text);
}

//draws 1st and 2nd cards for the player
void blackjack::playerDeal (SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* text)
{
	int random, x = 365;
	SDL_Rect playerPos1;
    std::stringstream stream;

	while (x <= 395) //stops after 2 cards
    {
        playerPos1 = {x, 490}; //defines position of the 1st and 2nd player card

        random = rand() % 52 + 1;

        if (used[random])
        {
            for (int k = 1 ; k <= 30 ; k++) //cycles through cards until an unused one is found
            {
                random = rand() % 52 + 1;

                if (!used[random])
                    break;
            }
        }

        else
        {
            draw (random, value, image); //random value out, card value and image location returned
            used[random] = true;

            if ((value == 1) && (totalP <= 10)) //Ace
            {
                totalP = totalP + value + 10; //Ace value of 11
                acePlayer = true;
            }

            else
                totalP += value;

            if (acePlayer == true && totalP >= 22 && totalP <=30) //changes Ace to value of 1 if next card(s) bust
            {
                acePlayer = false;
                totalP -= 10;
            }


            SDL_BlitSurface (deck, &image, screen, &playerPos1); //outputs 1st and 2nd player card

            x += 30; //for second player card
        }
    }

    stream << "Total: " << totalP;
    text = TTF_RenderText_Blended (font1, stream.str().c_str(), {255, 255, 255}); //total
    SDL_BlitSurface (text, NULL, screen, &totalPosP); //outputs total
    SDL_FreeSurface (text);

    if (totalP >= 21)
        outcome (screen, deck, text);
}

//runs if player decides to hit
void blackjack::playerDraw (SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* text)
{
    std::stringstream stream;

    if (!gameOver) //to avoid drawing after outcome
    {
        int random;
        SDL_Rect playerPos3 = {playerX, 490}; //using a passed x value to avoid x resetting on every draw

        random = rand() % 52 + 1;

        if (used[random])
            for (int k = 1 ; k <= 30 ; k++) //cycles through cards until an unused one is found
            {
                random = rand() % 52 + 1;

                if (!used[random])
                break;
            }

        draw (random, value, image); //random value out, card value and image location returned
        used[random] = true;

        if ((value == 1) && (totalP <= 10)) //Ace
        {
            totalP = totalP + value + 10; //Ace value of 11
            acePlayer = true;
        }

        else
            totalP += value;

        if (acePlayer == true && totalP >= 22 && totalP <= 30) //changes Ace to value of 1 if next card(s) bust
        {
            acePlayer = false;
            totalP -= 10;
        }

        if (totalP >= 21)
            outcome (screen, deck, text);

        SDL_BlitSurface (deck, &image, screen, &playerPos3); //outputs 3rd+ card for the player

        playerX += 30; //for 4th+ card

        stream << "Total: " << totalP;
        SDL_FillRect (screen, &totalPosP, 0x007100);
        text = TTF_RenderText_Blended (font1, stream.str().c_str(), {255, 255, 255}); //total
        SDL_BlitSurface (text, NULL, screen, &totalPosP); //outputs total
        SDL_FreeSurface (text);
    }
}

//runs if player stands or if player total is 21 or greater
void blackjack::outcome (SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* text)
{
    SDL_Rect outcomePos = {0, 25};

    std::stringstream stream;

    int random, y = 530;
    gameOver = true;

    if (totalP < 22)
    {

    while (totalD < 17) //dealer has to hit until total is 17 or more
    {
        SDL_Rect dealerPos2 = {y, 150}; //defines position of the 2nd+ card for the dealer

        random = rand() % 52 + 1;

        if (!used[random])
            {
                draw (random, value, image); //random value out, card value and image location returned
                used[random] = true;

                if ((value == 1) && (totalD <= 10)) //Ace
                {
                    totalD = totalD + value + 10; //Ace value of 11
                    aceDealer = true;
                }

                else
                    totalD += value;

                if (aceDealer == true && totalD >= 22 && totalD <=30) //changes Ace to value of 1 if next card(s) busts
                {
                    aceDealer = false;
                    totalD -= 10;
                }

                SDL_BlitSurface (deck, &image, screen, &dealerPos2); //outputs 2nd+ card for the dealer

                y += 30;
            }
    }

    stream << "Total: " << totalD;
    SDL_FillRect (screen, &totalPosD, 0x007100);
    text = TTF_RenderText_Blended (font1, stream.str().c_str(), {255, 255, 255}); //total
    SDL_BlitSurface (text, NULL, screen, &totalPosD); //outputs total
    SDL_FreeSurface (text);
    }

    else if (totalP > 21)
    {
        SDL_FreeSurface (text);
        text = TTF_RenderText_Blended (font2, "Bust! You lose!", {255, 255, 255});
    }

        SDL_FreeSurface (text);

        if (totalP > 21 && totalD <= 21)
            text = TTF_RenderText_Blended (font2, "Bust! You lose!", {255, 255, 255});

        if (totalP == 21 && totalD != 21)
            text = TTF_RenderText_Blended (font2, "Blackjack! You win!", {255, 255, 255});

        if ((totalD <= 21 && totalD > totalP) || (totalP > 21 && totalD > 21))
            text = TTF_RenderText_Blended (font2, "You lose!", {255, 255, 255});

        if (totalP < 21 && totalD > 21)
            text = TTF_RenderText_Blended (font2, "Dealer bust! You win!", {255, 255, 255});

        if (totalP <= 21 && totalP == totalD)
            text = TTF_RenderText_Blended (font2, "Tie!", {255, 255, 255});

        if (totalP > totalD && totalP < 21)
            text = TTF_RenderText_Blended (font2, "You win!", {255, 255, 255});

    outcomePos.x = screen->clip_rect.w/2 - text->clip_rect.w/2;
	SDL_BlitSurface (text, NULL, screen, &outcomePos); //outputs outcome text
	SDL_FreeSurface (text);
}
#endif // FUNCTIONSCLASS_H_INCLUDED
