#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//draws first dealer card, no random test since this is the 1st card on the table
void dealerDeal (int& total, bool B[], bool& aceDealer, SDL_Surface* screen, SDL_Surface* deck)
{
	int random, value;
	SDL_Rect image, dealerPos = {500, 150}; //defines position of card 1st dealer card

    std::ofstream totalOut ("total.txt", std::ios::app); //for testing outcomes **Delete?**
    time_t  ptr;                                    //
    time ( &ptr );                                  //for outputting date and time to file
    totalOut << "Time: " << ctime (&ptr) << "\n";   //

    random = rand() % 52 + 1;

    draw (random, value, image); //random value out, card value and image location returned
    B[random] = true;

    if ((value == 1) && (total <= 10)) //Ace
        {
            total = total + value + 10; //Ace value of 11
            aceDealer = true;
        }

    else
        total += value;

    if (aceDealer == true && total >= 22 && total <=30) //changes Ace to value of 1 if next card(s) busts
    {
        aceDealer = false; //avoids subtracting 10 after every bust when an ace is drawn
        total -= 10;
    }

    totalOut << "dealer " << total << "\n"; //for testing outcomes **Delete?**

    SDL_BlitSurface (deck, &image, screen, &dealerPos); //outputs 1st random card for dealer before any key press

    totalOut.close(); //for testing outcomes **Delete?**
}

//draws 1st and 2nd cards for the player
void playerDeal (int& total, bool B[], bool& acePlayer, SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* textTotal)
{
	int random, x = 365, value;
	SDL_Rect image, playerPos1;

    std::stringstream stream;
    SDL_Color textColor = {255, 255, 255}; //text color (white)
    TTF_Font* font = TTF_OpenFont ("calibri.ttf", 16); //text font, size
    SDL_Rect tot = {725, 560}; //total position

    std::ofstream totalOut ("total.txt", std::ios::app); //for testing outcomes **Delete?**

	while (x <= 395) //stops after 2 cards
    {
        playerPos1 = {x, 490}; //defines position of the 1st and 2nd player card

        random = rand() % 52 + 1;

        if (B[random])
        {
            for (int k = 1 ; k <= 30 ; k++) //cycles through cards until an unused one is found
            {
                random = rand() % 52 + 1;

                if (!B[random])
                    break;
            }
        }

        else
        {
            draw (random, value, image); //random value out, card value and image location returned
            B[random] = true;

            if ((value == 1) && (total <= 10)) //Ace
            {
                total = total + value + 10; //Ace value of 11
                acePlayer = true;
            }

            else
                total += value;

            if (acePlayer == true && total >= 22 && total <=30) //changes Ace to value of 1 if next card(s) bust
            {
                acePlayer = false;
                total -= 10;
            }

            totalOut << "player " << total << "\n"; //for testing outcomes **Delete?**

            SDL_BlitSurface (deck, &image, screen, &playerPos1); //outputs 1st and 2nd player card

            x += 30; //for second player card
        }
    }

    SDL_FreeSurface (textTotal);
    stream << "Total: " << total;
    textTotal = TTF_RenderText_Blended (font, stream.str().c_str(), textColor); //total
    SDL_BlitSurface (textTotal, NULL, screen, &tot); //outputs total

    totalOut.close(); //for testing outcomes **Delete?**
}

//runs if player decides to hit
void playerDraw (int& total, bool B[], bool& acePlayer, int& playerX, SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* textTotal)
{
    std::stringstream stream;
    SDL_Color textColor = {255, 255, 255}; //text color (white)
    TTF_Font* font = TTF_OpenFont ("calibri.ttf", 16); //text font, size
    SDL_Rect tot = {725, 560, 75, 19}; //total position

    if (total < 21) //to avoid drawing after outcome
    {
        int random, value;
        SDL_Rect image, playerPos3 = {playerX, 490}; //using a passed x value to avoid x resetting on every draw

        std::ofstream totalOut ("total.txt", std::ios::app); //for testing outcomes **Delete?**

        random = rand() % 52 + 1;

        if (B[random])
        {
            for (int k = 1 ; k <= 30 ; k++) //cycles through cards until an unused one is found
            {
                random = rand() % 52 + 1;
                totalOut << "random " << random << "\n"; //for testing random **Delete?**

                if (!B[random])
                    break;
            }
        }

        else
        {
            draw (random, value, image); //random value out, card value and image location returned
            B[random] = true;

            if ((value == 1) && (total <= 10)) //Ace
            {
                total = total + value + 10; //Ace value of 11
                acePlayer = true;
            }

            else
                total += value;

            if (acePlayer == true && total >= 22 && total <= 30) //changes Ace to value of 1 if next card(s) bust
            {
                acePlayer = false;
                total -= 10;
            }

            totalOut << "player " << total << "\n"; //for testing outcomes **Delete?**

            SDL_BlitSurface (deck, &image, screen, &playerPos3); //outputs 3rd+ card for the player

            playerX += 30; //for 4th+ card
        }

    SDL_FreeSurface (textTotal);
    SDL_FillRect (screen, &tot, 0x007100);
    stream << "Total: " << total;
    textTotal = TTF_RenderText_Blended (font, stream.str().c_str(), textColor); //total
    SDL_BlitSurface (textTotal, NULL, screen, &tot); //outputs total
    totalOut.close(); //for testing outcomes **Delete?**
    }
}

//runs if player stands or if player total is 21 or greater
void outcome (int player, int total, bool B[], SDL_Surface* screen, SDL_Surface* deck, SDL_Surface* text, bool& aceDealer)
{
    int value;

    SDL_Rect image, outcomePos = {5, 5};

    SDL_Color colorText = {255, 255, 255}; //text color (white)
    TTF_Font* font = TTF_OpenFont ("CaviarDreams.ttf", 42); //text font, size

    std::ofstream totalOut ("total.txt", std::ios::app); //for testing outcomes **Delete?**

    int random, y = 530;

    while (total < 17) //dealer has to hit until total is 17 or more
    {
        SDL_Rect dealerPos2 = {y, 150}; //defines position of the 2nd+ card for the dealer

        random = rand() % 52 + 1;

        if (!B[random])
            {
                draw (random, value, image); //random value out, card value and image location returned
                B[random] = true;

                if ((value == 1) && (total <= 10)) //Ace
                {
                    total = total + value + 10; //Ace value of 11
                    aceDealer = true;
                }

                else
                    total += value;

                if (aceDealer == true && total >= 22 && total <=30) //changes Ace to value of 1 if next card(s) busts
                {
                    aceDealer = false;
                    total -= 10;
                }

                totalOut << "dealer " << total << "\n"; //for testing outcomes **Delete?**

                SDL_BlitSurface (deck, &image, screen, &dealerPos2); //outputs 2nd+ card for the dealer

                y += 30;
            }
    }

        //possible outcomes
        if (player > 21 && total <= 21)
        {
        text = TTF_RenderText_Blended (font, "Bust! You lose!", colorText);
        totalOut << "player > 21, Bust! You lose!" << "\n\n"; //for testing outcomes **Delete?**
        }

        if (player == 21 && total != 21)
        {
        text = TTF_RenderText_Blended (font, "Blackjack! You win!", colorText);
        totalOut << "player = 21, Blackjack! You win!" << "\n\n"; //for testing outcomes **Delete?**
        }

        if (total <= 21 && total > player)
        {
        text = TTF_RenderText_Blended (font, "You lose!", colorText);
        totalOut << "dealer < 21, dealer > player, You lose!" << "\n\n"; //for testing outcomes **Delete?**
        }

        if (player < 21 && total > 21)
        {
        text = TTF_RenderText_Blended (font, "Dealer bust! You win!", colorText);
        totalOut << "player < 21, dealer > 21, Dealer bust! You win!" << "\n\n"; //for testing outcomes **Delete?**
        }

        if ((player <= 21 && player == total) || (player > 21 && total > 21))
        {
        text = TTF_RenderText_Blended (font, "Tie!", colorText);
        totalOut << "player = dealer, player < 21, Tie!" << "\n\n"; //for testing outcomes **Delete?**
        }

        if (player > total && player < 21)
        {
        text = TTF_RenderText_Blended (font, "You win!", colorText);
        totalOut << "player > dealer, player < 21, You win!" << "\n\n"; //for testing outcomes **Delete?**
        }

	SDL_BlitSurface (text, NULL, screen, &outcomePos); //outputs outcome text

	TTF_CloseFont (font);
	totalOut.close(); //for testing outcomes **Delete?**
}
#endif
