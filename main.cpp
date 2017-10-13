#include <iostream>
#include <random>
#include "Functions.h"

using namespace std;

int main() {
    int house{100};
    int player{100};
    int currentPot{0};
    vector<char> cards{'A', '2', '3',
                       '4', '5', '6',
                       '7', '8', '9',
                       'T', 'J', 'Q', 'K'};
    vector<char> cardsHouse{'A', '2', '3',
                            '4', '5', '6',
                            '7', '8', '9',
                            'T', 'J', 'Q', 'K'};
    bool playGame{true};
    while (playGame)
    {
        cout << "Welcome to Blackjack!\n";
        cout << "You start with $100, and playing costs $10 per round. Continue? Y/N:";
        char startGame{0};
        cin >> startGame;
        cin.ignore(32767,'\n');
        while (playGame)
        {
            if (startGame == 'n' || startGame == 'N') {
                playGame = false;
            }
            else if (startGame != 'y' && startGame != 'Y')
            {
                cout << "Not valid input.\n";
                cin >> startGame;
                cin.ignore(32767,'\n');
            }
            else {
                // Number of rounds relates to how many cards you can have in hand
                shuffleDeck(cards, cardsHouse);
                int playerPoints{0};
                int housePoints{0};
                int roundCnt{0};
                int houseCnt{0};
                playerHand(cards, roundCnt, playerPoints);
                player -= 10;
                currentPot += 10;
                bool roundDone{false};
                if (playerPoints == 21) {
                    winCheck(playerPoints, housePoints, player, house, currentPot);
                    player += 10;  // Not sure what the rules are for when player draws 21 before betting
                    currentPot = 10;
                    roundDone = true;
                    shuffleDeck(cards, cardsHouse);
                    playerHand(cards, roundCnt, playerPoints);
                }
                bettingFunction(house, player, currentPot);
                char opt{0};
                while (!roundDone) {
                    while (playerPoints < 21) {
                        cout << "Hit or Stand?(h/s) ";
                        cin >> opt;
                        cin.ignore(32767,'\n');
                        if (opt == 'h' || opt == 'H') {
                            ++roundCnt;
                            playerHand(cards, roundCnt, playerPoints);
                            winCheck(playerPoints, housePoints, player, house, currentPot);
                            continue;
                        } else if (opt == 's' || opt == 'S') {
                            cout << "House is drawing: \n";
                            while (housePoints < 17) {
                                houseLogic(cardsHouse, housePoints, houseCnt);
                                winCheck(playerPoints, housePoints, player, house, currentPot);
                                ++houseCnt;
                            }
                            break;
                        }
                        else {
                            cout << "Not valid input.\n";
                            continue;
                        }
                    }
                    roundDone = true;
                }
                while (playGame)
                {
                    cout << "Do you want to play again? Y/N: ";
                    cin >> startGame;
                    cin.ignore(32767,'\n');
                    if (startGame == 'n' || startGame == 'N') {
                        playGame = false;
                    }
                    else if (startGame != 'y' && startGame != 'Y')
                    {
                        cout << "Not valid input.\n";
                        continue;
                    } else
                        break;
                }

            }

        }
    }
    return 0;
}