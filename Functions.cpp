
#include <iostream>
#include <random>
#include <algorithm>
#include "Functions.h"

using namespace std;

/**
 * void shuffleDeck(vector<char> &cards, vector<char> &cardsHouse)
 * Shuffles the deck each turn. Uses a different function than srand/rand, apparently this one is better?
 * @param cards - player cards
 * @param cardsHouse - house cards
 */
void shuffleDeck(vector<char> &cards, vector<char> &cardsHouse)
{
    mt19937 mt((unsigned int) time(nullptr)); // similar to srand()
    shuffle(begin(cardsHouse), end(cardsHouse), mt);
    shuffle(begin(cards), end(cards), mt);
}
/**
 * int iInput()
 * Just a basic function to make sure the game doesn't crash if an invalid type is used.
 * @return - Function requires an integer before it allows the player to continue.
 */
int iInput ()
{
    while (true)
    {
        int bet{0};
        cin >> bet;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767,'\n');
            cout << "Please enter a valid number.\n";
        }
        else
        {
            cin.ignore(32767,'\n');
            return bet;
        }
    }
}
/**
* void cashStatus(int house, int player)
 * Basic function to tell the player how much money can be bet.
 * @param int house - how much the house has
 * @param int player - how much the player has
*/
void cashStatus(int house, int player)
{
    cout << "House: $" << house << '\n';
    cout << "You:   $" << player << '\n';
}
/**
 * void bettingFunction(int &house, int &player, int &gambled)
 * Function asks for an integer to add to the pot and adds an equal amount from the house.
 * @param house - Used to display and change how much money the house has
 * @param player - Used to display and change how much money the player has
 * @param gambled - takes currentPot from main() and changes it depending on how much the player bets.
 */
void bettingFunction(int &house, int &player, int &gambled)
{
    cout << "House: $" << house << '\n';
    cout << "You:   $" << player << " (-$10 to start the round)" << '\n';
    while (player > 0 && house > 0)
    {
        cout << "Would you like to bet any extra?\n";
        cout << "Enter 0 for no bet: ";
        int bet = iInput();
        if (player >= bet && house >= 0 && bet > 5)
        {
            player -= bet;
            house -= bet;
            gambled += (bet * 2);
            cout << "You bet $" << bet << ". You now have $" << player << " left.\n";
            cout << "Money in pot: " << gambled << '\n';
            break;
        }
        else if (player < bet)
        {
            cout << "You don't have that much money!";
            cout << "Current amount of money: " << "$" << player << '\n';
            continue;
        }
        else if (house < bet)
        {
            cout << "The House can't afford that bet.";
            cout << "House: " << "$" << house << '\n';
            continue;
        }
        else if (bet == 0)
        {
            break;
        }
        else if (bet < 0)
        {
            cout << "Sorry, you can't bet less than nothing!\n";
            continue;
        }
    }
}
/**
 * void playerHand(vector<char> &cards, int roundCnt, int &playerPoints)
 * Used to output the player's hand, calculate the value of each card and add it to the total point value (playerPoints).
 * @param cards - player's cards
 * @param roundCnt - Tells the program what turn it is. Useful for telling it how many cards to give the player.
 * Incremented by 2 at the start because player starts with two cards.
 * @param playerPoints - Total value of cards in hand. Incremented by an additional card's value at the end of the function.
 */
void playerHand(vector<char> &cards, int roundCnt, int &playerPoints)
{
    roundCnt += 2;
    playerPoints = 0;
    cout << "You have these cards in your hand:\n";
    for (int i{0}; i < roundCnt; i++)
    {
        cout << " ~~~~~~~ \n";
        cout << " |" << cards[i] << "     | \n";
        cout << " |      | \n";
        cout << " |      | \n";
        cout << " |     " << cards[i] << "| \n";
        cout << "  ~~~~~~~ \n";
        playerPoints += cardValues(cards[i], playerPoints);
    }
    cout << playerPoints << " points.\n";
}
/**
 * void houseLogic (vector<char> &cardsHouse, int &housePoints, int &houseCnt)
 * Shows the house's hand after player "stands". Adds the current card in line to house's total point value.
 * @param cardsHouse - House's deck. Used for display and plugged into cardValues() to decide the value of cards.
 * @param housePoints - Adds the card's value to total points.
 * @param houseCnt - Used to figure out which cards are currently in play.
 */
void houseLogic (vector<char> &cardsHouse, int &housePoints, int &houseCnt)
{
    if (housePoints < 17)
    {
        cout << " ~~~~~~~ \n";
        cout << " |" << cardsHouse[houseCnt] << "     | \n";
        cout << " |      | \n";
        cout << " |      | \n";
        cout << " |     " << cardsHouse[houseCnt] << "| \n";
        cout << "  ~~~~~~~ \n";
        housePoints += cardValues(cardsHouse[houseCnt], housePoints);
    }
    else
        return;
}
/**
 * int cardValues(char newCards, int currentPoints)
 * This function checks for the value of Ace and assigns usable int values to the chars from vector<char> cards.
 * @param newCards - Gets the character of the current card from vector<char> cards in main().
 * @param currentPoints - Used to calculate whether an Ace is worth 1 or 11 points. Otherwise not used.
 * @return Returns the value of the card for use in main().
 */
int cardValues(char newCards, int currentPoints)
{
    int cards[11]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int cardValue{0};
    if (newCards == 'A')
    {
        if (currentPoints <= 10)
        {
            cardValue = cards[10];
        }
        else
        {
            cardValue = cards[0];
        }
    }
    else if (newCards >= 50 && newCards <= 57)
    {
        cardValue = cards[newCards-49];
    }
    else if (newCards == 'T' || newCards == 'J' || newCards == 'Q' || newCards == 'K') // Ten, Jack, Queen, King
    {
        cardValue = cards[9];
    }
    return cardValue;
}
/**
 * void winCheck(int pPoints, int hPoints, int &player, int &house, int &pot)
 * Checks if the win condition has been met by player or house.
 * @param pPoints - Sum of player's cards  - Used to check win condition
 * @param hPoints - Sum of house's cards - Used to check win condition
 * @param player - How much money the player has left. If win - gains the value in pot
 * @param house - How much money the house has left. If win - gains the value in pot
 * @param pot - How much money is in the pot.
 */
void winCheck(int pPoints, int hPoints, int &player, int &house, int &pot)
{
    if (pPoints >= 21)
    {
        if (pPoints == 21)
        {
            cout << "Congratulations! You scored a perfect 21!\n";
            player += pot;
            pot = 0;
            cashStatus(house, player);
        }
        else if (pPoints > 21)
        {
            cout << "You lost. Better luck next time!\n";
            house += pot;
            pot = 0;
            cashStatus(house, player);
        }
    }
    else if (hPoints >= 21)
    {
        if (hPoints == 21)
        {
            cout << "  " << hPoints << " points.\nYou lost. Better luck next time!\n";
            house += pot;
            pot = 0;
            cashStatus(house, player);
        }
        else if (hPoints > 21)
        {
            cout << "  " << hPoints << " points.\nHouse busted! You win.\n";
            player += pot;
            pot = 0;
            cashStatus(house, player);
        }
    }
    else if (hPoints >= 17 && pPoints < 21)
    {
        if (hPoints < pPoints)
        {
            cout << "  " << hPoints << " points.\nYou won!\n";
            player += pot;
            pot = 0;
            cashStatus(house, player);
        }
        else if (hPoints > pPoints)
        {
            cout << "  " << hPoints << " points.\nYou lost. Better luck next time!\n";
            house += pot;
            pot = 0;
        }
        else if (hPoints == pPoints)
        {
            cout << "  " << hPoints << " points.\nTied! Pot remains in play.\n";
            cashStatus(house, player);
        }
    }

}
