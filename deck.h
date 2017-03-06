#ifndef DECK_H
#define DECK_H

struct card {
    int value; //1-10
    std::string suite; //Clubs, Spades, Hearts, Diamonds
    std::string facevalue; //Ace, 2-10, Jack, Queen, King
    SDL_Rect image; //Position in deck.bmp
};

void draw (int x, int& value, SDL_Rect& image)
{
    card deck[53];

    deck[0].value = 0;
    deck[0].suite = "";
    deck[0].facevalue = "Joker";

    deck[1].value = 1;
    deck[1].suite = "Clubs";
    deck[1].facevalue = "Ace";
    deck[1].image = {1,1,71,97}; //x,y,width,height

    deck[2].value = 2;
    deck[2].suite = "Clubs";
    deck[2].facevalue = "2";
    deck[2].image = {74,1,71,97};

    deck[3].value = 3;
    deck[3].suite = "Clubs";
    deck[3].facevalue = "3";
    deck[3].image = {147,1,71,97};

    deck[4].value = 4;
    deck[4].suite = "Clubs";
    deck[4].facevalue = "4";
    deck[4].image = {220,1,71,97};

    deck[5].value = 5;
    deck[5].suite = "Clubs";
    deck[5].facevalue = "5";
    deck[5].image = {293,1,71,97};

    deck[6].value = 6;
    deck[6].suite = "Clubs";
    deck[6].facevalue = "6";
    deck[6].image = {366,1,71,97};

    deck[7].value = 7;
    deck[7].suite = "Clubs";
    deck[7].facevalue = "7";
    deck[7].image = {439,1,71,97};

    deck[8].value = 8;
    deck[8].suite = "Clubs";
    deck[8].facevalue = "8";
    deck[8].image = {512,1,71,97};

    deck[9].value = 9;
    deck[9].suite = "Clubs";
    deck[9].facevalue = "9";
    deck[9].image = {585,1,71,97};

    deck[10].value = 10;
    deck[10].suite = "Clubs";
    deck[10].facevalue = "10";
    deck[10].image = {658,1,71,97};

    deck[11].value = 10;
    deck[11].suite = "Clubs";
    deck[11].facevalue = "Jack";
    deck[11].image = {731,1,71,97};

    deck[12].value = 10;
    deck[12].suite = "Clubs";
    deck[12].facevalue = "Queen";
    deck[12].image = {804,1,71,97};

    deck[13].value = 10;
    deck[13].suite = "Clubs";
    deck[13].facevalue = "King";
    deck[13].image = {877,1,71,97};

    deck[14].value = 1;
    deck[14].suite = "Spades";
    deck[14].facevalue = "Ace";
    deck[14].image = {1,99,71,97};

    deck[15].value = 2;
    deck[15].suite = "Spades";
    deck[15].facevalue = "2";
    deck[15].image = {74,99,71,97};

    deck[16].value = 3;
    deck[16].suite = "Spades";
    deck[16].facevalue = "3";
    deck[16].image = {147,99,71,97};

    deck[17].value = 4;
    deck[17].suite = "Spades";
    deck[17].facevalue = "4";
    deck[17].image = {220,99,71,97};

    deck[18].value = 5;
    deck[18].suite = "Spades";
    deck[18].facevalue = "5";
    deck[18].image = {293,99,71,97};

    deck[19].value = 6;
    deck[19].suite = "Spades";
    deck[19].facevalue = "6";
    deck[19].image = {366,99,71,97};

    deck[20].value = 7;
    deck[20].suite = "Spades";
    deck[20].facevalue = "7";
    deck[20].image = {439,99,71,97};

    deck[21].value = 8;
    deck[21].suite = "Spades";
    deck[21].facevalue = "8";
    deck[21].image = {512,99,71,97};

    deck[22].value = 9;
    deck[22].suite = "Spades";
    deck[22].facevalue = "9";
    deck[22].image = {585,99,71,97};

    deck[23].value = 10;
    deck[23].suite = "Spades";
    deck[23].facevalue = "10";
    deck[23].image = {658,99,71,97};

    deck[24].value = 10;
    deck[24].suite = "Spades";
    deck[24].facevalue = "Jack";
    deck[24].image = {731,99,71,97};

    deck[25].value = 10;
    deck[25].suite = "Spades";
    deck[25].facevalue = "Queen";
    deck[25].image = {804,99,71,97};

    deck[26].value = 10;
    deck[26].suite = "Spades";
    deck[26].facevalue = "King";
    deck[26].image = {877,99,71,97};

    deck[27].value = 1;
    deck[27].suite = "Hearts";
    deck[27].facevalue = "Ace";
    deck[27].image = {1,197,71,97};

    deck[28].value = 2;
    deck[28].suite = "Hearts";
    deck[28].facevalue = "2";
    deck[28].image = {74,197,71,97};

    deck[29].value = 3;
    deck[29].suite = "Hearts";
    deck[29].facevalue = "3";
    deck[29].image = {147,197,71,97};

    deck[30].value = 4;
    deck[30].suite = "Hearts";
    deck[30].facevalue = "4";
    deck[30].image = {220,197,71,97};

    deck[31].value = 5;
    deck[31].suite = "Hearts";
    deck[31].facevalue = "5";
    deck[31].image = {293,197,71,97};

    deck[32].value = 6;
    deck[32].suite = "Hearts";
    deck[32].facevalue = "6";
    deck[32].image = {366,197,71,97};

    deck[33].value = 7;
    deck[33].suite = "Hearts";
    deck[33].facevalue = "7";
    deck[33].image = {439,197,71,97};

    deck[34].value = 8;
    deck[34].suite = "Hearts";
    deck[34].facevalue = "8";
    deck[34].image = {512,197,71,97};

    deck[35].value = 9;
    deck[35].suite = "Hearts";
    deck[35].facevalue = "9";
    deck[35].image = {585,197,71,97};

    deck[36].value = 10;
    deck[36].suite = "Hearts";
    deck[36].facevalue = "10";
    deck[36].image = {658,197,71,97};

    deck[37].value = 10;
    deck[37].suite = "Hearts";
    deck[37].facevalue = "Jack";
    deck[37].image = {731,197,71,97};

    deck[38].value = 10;
    deck[38].suite = "Hearts";
    deck[38].facevalue = "Queen";
    deck[38].image = {804,197,71,97};

    deck[39].value = 10;
    deck[39].suite = "Hearts";
    deck[39].facevalue = "King";
    deck[39].image = {877,197,71,97};

    deck[40].value = 1;
    deck[40].suite = "Diamonds";
    deck[40].facevalue = "Ace";
    deck[40].image = {1,295,71,97};

    deck[41].value = 2;
    deck[41].suite = "Diamonds";
    deck[41].facevalue = "2";
    deck[41].image = {74,295,71,97};

    deck[42].value = 3;
    deck[42].suite = "Diamonds";
    deck[42].facevalue = "3";
    deck[42].image = {147,295,71,97};

    deck[43].value = 4;
    deck[43].suite = "Diamonds";
    deck[43].facevalue = "4";
    deck[43].image = {220,295,71,97};

    deck[44].value = 5;
    deck[44].suite = "Diamonds";
    deck[44].facevalue = "5";
    deck[44].image = {293,295,71,97};

    deck[45].value = 6;
    deck[45].suite = "Diamonds";
    deck[45].facevalue = "6";
    deck[45].image = {366,295,71,97};

    deck[46].value = 7;
    deck[46].suite = "Diamonds";
    deck[46].facevalue = "7";
    deck[46].image = {439,295,71,97};

    deck[47].value = 8;
    deck[47].suite = "Diamonds";
    deck[47].facevalue = "8";
    deck[47].image = {512,295,71,97};

    deck[48].value = 9;
    deck[48].suite = "Diamonds";
    deck[48].facevalue = "9";
    deck[48].image = {585,295,71,97};

    deck[49].value = 10;
    deck[49].suite = "Diamonds";
    deck[49].facevalue = "10";
    deck[49].image = {658,295,71,97};

    deck[50].value = 10;
    deck[50].suite = "Diamonds";
    deck[50].facevalue = "Jack";
    deck[50].image = {731,295,71,97};

    deck[51].value = 10;
    deck[51].suite = "Diamonds";
    deck[51].facevalue = "Queen";
    deck[51].image = {804,295,71,97};

    deck[52].value = 10;
    deck[52].suite = "Diamonds";
    deck[52].facevalue = "King";
    deck[52].image = {877,295,71,97};

	value = deck[x].value;
	image = deck[x].image;
}
#endif
