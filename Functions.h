
#ifndef BLACKJACKFINAL_FUNCTIONS_H
#define BLACKJACKFINAL_FUNCTIONS_H

int iInput();
void cashStatus(int house, int player);
int cardValues(char newCards, int currentPoints);
void bettingFunction(int &house, int &player, int &gambled);
void shuffleDeck(std::vector<char> &cards, std::vector<char> &cardsHouse);
void playerHand(std::vector<char> &cards, int roundCnt, int &playerPoints);
void winCheck(int pPoints, int hPoints, int &player, int &house, int &pot);
void houseLogic (std::vector<char> &cardsHouse, int &housePoints, int &houseCnt);

#endif //BLACKJACKFINAL_FUNCTIONS_H
