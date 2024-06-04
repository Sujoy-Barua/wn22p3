// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Pack.h"
#include "Card.h"
#include "Player.h"

using namespace std;

class Game {
private:
    vector<Player*> players;
    Pack packofCards;
    string shuffleType;
    int winPoints;

    Card card;
    int prevTrickWinner;
    vector<int> trickWinCount{0,0,0,0};
    vector<bool> whoOrdered{false,false,false,false};
    string order_up_suit;
    

    
    void shuffle(string shuffleType) {
        if (shuffleType == "shuffle") {
            packofCards.shuffle();
        }
        if (shuffleType == "noshuffle") {
            packofCards.reset();
        }
    }

    void deal(int dealer) {
        int receiver;
        if (dealer < 3) {
            receiver = dealer + 1;
        }
        else {
            receiver = 0;
        }
        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 3; j++) {
                Card pCard = packofCards.deal_one();
                players[receiver]->add_card(pCard);
                
            }
            if (receiver < 3) {
                receiver++;
            }
            else {
                receiver = 0;
            }
            
            for (size_t j = 0; j < 2; j++) {
                Card pCard = packofCards.deal_one();
                players[receiver]->add_card(pCard);
                
                
            }
            if (receiver < 3) {
                receiver++;
            }
            else {
                receiver = 0;
            }
        }

        for (size_t i = 0; i < 2; i++) {
            for (size_t j = 0; j < 2; j++) {
                Card pCard = packofCards.deal_one();
                players[receiver]->add_card(pCard);
                
                
            }
            if (receiver < 3) {
                receiver++;
            }
            else {
                receiver = 0;
            }
            for (size_t j = 0; j < 3; j++) {
                Card pCard = packofCards.deal_one();
                players[receiver]->add_card(pCard);
                
                
            }
            if (receiver < 3) {
                receiver++;
            }
            else {
                receiver = 0;
            }
        }
    }

    // takes in the current player's index, if the player
    // is dealeror not, and the round number and returns the player's 
    // wish to make the upcard trump or not, changes the order up suit
    // if player wishes to make trump

    bool make_trump(Card &upcard, int curPlayer, bool is_dealer, 
                    int round) {
        return players[curPlayer]->make_trump(upcard, is_dealer,
                  round, order_up_suit);
    }

    void play_trick(int trickPlayer, string &order_up_suit) {
        int leadplayerindex = trickPlayer;
        vector<Card> table;
        Card pCard; // played card
        //switch to the player to the dealer's left (eldest hand)
        Card ledCard = players[leadplayerindex]->lead_card(order_up_suit);
        table.push_back(ledCard);
        cout << ledCard << " led by " << *players[leadplayerindex] << endl;
        if (trickPlayer < 3) {
        trickPlayer++;
        }
        else {
        trickPlayer = 0;
        }

        for (size_t i = 0; i < 3; i++) {
            pCard = players[trickPlayer]->play_card(ledCard, order_up_suit);
            cout << pCard << " played by " << *players[trickPlayer] << endl;
            if (trickPlayer < 3) {
                table.push_back(pCard);
                trickPlayer++;
            }
            else {
                table.push_back(pCard);
                trickPlayer = 0;
            }
        }

        int curMaxIndex = 0;
        for (size_t i = 1; i < table.size(); i++) {
            if (Card_less(table[curMaxIndex], table[i], ledCard, order_up_suit)) {
                curMaxIndex = i;
            }
        }
        int rawindex = leadplayerindex + curMaxIndex;
        if (rawindex > 3) {
            prevTrickWinner = (rawindex % 4);
        }
        else {
            prevTrickWinner = rawindex;
        }
        cout << *players[prevTrickWinner] << " takes the trick" << endl;
        trickWinCount[prevTrickWinner] += 1;
    }

    void increase_curPlayer(int &dealerWho, int &curPlayer) {
        if (dealerWho < 3) {
            curPlayer = dealerWho + 1;
        }
        else {
            curPlayer = 0;
        }
    }

    void increase_curPlayer(int &curPlayer) {
        if (curPlayer < 3) {
            curPlayer++;
        }
        else {
            curPlayer = 0;
        }
    }

    void increase_dealer(int &dealerWho) {
        if (dealerWho < 3) {
            dealerWho++;
        } else {
            dealerWho = 0;
        }
    }


    void add_discard_manager(int &round, int &dealerWho, Card &upCard) {
        if (round == 1) {
            players[dealerWho]->add_and_discard(upCard);
        }
    }

    void play_next_4_tricks() {
        for (size_t i = 0; i < 4; i++) {
            //next 4 tricks led by the winner of previous trick
            play_trick(prevTrickWinner, order_up_suit);
            cout << endl;
        }
    }
    void play_hand(int dealerWho) {
        int round = 1;
        int curPlayer;
        bool is_dealer;
        packofCards.reset();
        shuffle(shuffleType);
        deal(dealerWho);
        Card upCard = packofCards.deal_one();
        cout << upCard << " turned up" << endl;

        for (size_t j = 0; j < 2; j++) {
            increase_curPlayer(dealerWho, curPlayer);
            for (size_t i = 0; i < 4; i++) {
                if (curPlayer == dealerWho) {
                    is_dealer = true;
                }
                else {
                    is_dealer = false;
                }
                if (make_trump(upCard, curPlayer, is_dealer, round)) {
                    order_up_suit = order_up_suit;
                    cout << *players[curPlayer] << " orders up " << order_up_suit << endl;
                    whoOrdered[curPlayer] = true;
                    add_discard_manager(round, dealerWho, upCard);
                    cout << endl;
                    //now trick taking begins. First trick by the eldest hand
                    //play_trick takes in the eldestPlayer's index
                    increase_dealer(dealerWho);
                    play_trick((dealerWho), order_up_suit);
                    cout << endl;
                    play_next_4_tricks();
                    j = 3; 
                    //so that the loop for second round doesn't run
                    break;
                    //breaking out from the inner for loop
                } 
                else {
                    cout << *players[curPlayer] << " passes" << endl;
                    increase_curPlayer(curPlayer);
                }
            }
            round++;
        }
    }

    void GPointManager(int &G1, int &G2, bool &G1O, bool &G2O) {
        G1 = trickWinCount[0] + trickWinCount[2];
        G1O = (whoOrdered[0] || whoOrdered[2]);

        G2 = trickWinCount[1] + trickWinCount[3];
        G2O = (whoOrdered[1] || whoOrdered[3]);
    }

    void handWinManager(bool &GO, int &G, vector<int> &Grp, int gInd) {
        if (gInd == 0) {
            cout << *players[0] << " and " << *players[2]
                 << " win the hand" << endl;
        }
        else if (gInd == 1) {
            cout << *players[1] << " and " << *players[3]
                 << " win the hand" << endl;
        }

        if (GO) {
            if (G > 2 && G < 5) {
                Grp[gInd] += 1;
            }
            else if (G == 5) {
                Grp[gInd] += 2;
                cout << "march!" << endl;
            }
        }
        else {
            Grp[gInd] += 2;
            cout << "euchred!" << endl;
        }
    }
    

public:
    Game(vector<Player*> players_in, Pack packofcards_in, 
            string shuffleType_in, int winPoints_in)
    : players(players_in), packofCards(packofcards_in), 
        shuffleType(shuffleType_in), winPoints(winPoints_in) {}

    void print_score(vector<int> grp_points, int grp) {
        int player1;
        int player2;
        if (grp == 0) {
            player1 = 0;
            player2 = 2;
        }
        else {
            player1 = 1;
            player2 = 3;
        }
        cout << *players[player1] << " and " 
             << *players[player2] << " have " 
             << grp_points[grp] << " points" << endl;
    }
    void play() {
        
        int G1_tPoints = 0;
        bool G1_ordered = false;
        // player 0 and 2 are G1, tpoints mean trick points
        int G2_tPoints = 0;
        bool G2_ordered = false;
        //player 1 and 3
        vector<int> grp_points{0,0};
        //points received by each group

        bool G1won = false;
        bool G2won = false;
        int Hand = 0;
        int dealer = 0;

        while (G1won == false && G2won == false) {
            //hand 0 begins
            cout << "Hand " << Hand << endl;
            cout << *players[dealer] << " deals" << endl;
            play_hand(dealer);

            GPointManager(G1_tPoints, G2_tPoints, G1_ordered, G2_ordered);
            
            
            if (G1_tPoints > G2_tPoints) {
                handWinManager(G1_ordered, G1_tPoints, grp_points, 0);
            }
            else if (G2_tPoints > G1_tPoints) {
                handWinManager(G2_ordered, G2_tPoints, grp_points, 1);
            }
            print_score(grp_points, 0);
            print_score(grp_points, 1);
            cout << endl;

            if (grp_points[0] >= winPoints) {
                G1won = true;
            }
            else if (grp_points[1] >= winPoints) {
                G2won = true;
            }

            // incrementing to next hand and 
            // resetting everything for next Hand
            // dont reset grp_points since it will
            // be used in the next hands as well
            Hand++;

            increase_dealer(dealer);

            //G1_tPoints = 0;
            //G2_tPoints = 0;
            //G1_ordered = false;
            //G2_ordered = false;

            for (size_t i = 0; i < 4; i++) {
                whoOrdered[i] = false;
                trickWinCount[i] = 0;
            }
        }
        if (G1won == true) {
            cout << *players[0] << " and " << *players[2] << " win!" << endl;
        }
        else if (G2won == true) {
            cout << *players[1] << " and " << *players[3] << " win!" << endl;
        }

        for (size_t i = 0; i < players.size(); ++i) {
            delete players[i];
        }
    }
};


int main(int argc, char* argv[]) {
    if (argc != 12) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return -1;
    }

    //storing all user input in relevant variables
    string inputPack = argv[1];
    string shuffleType = argv[2];
    int winPoints = atoi(argv[3]); 
    string P1 = argv[4];
    string P1Strat = argv[5];
    string P2 = argv[6];
    string P2Strat = argv[7];
    string P3 = argv[8];
    string P3Strat = argv[9];
    string P4 = argv[10];
    string P4Strat = argv[11];

    for (size_t i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    
    //opening stream to read in file
    ifstream fin;
    fin.open(inputPack);
    // or use fin.open(argv[1]);
    if (!(fin.is_open())) {
        cout << "Error opening " << inputPack << endl;
        // or use cout << "Error opening " << argv[1] << endl;
    }

    Pack packofCards(fin);
    vector<Player*> players;

    for (size_t i = 4; i < 12; i+=2) {
        players.push_back(Player_factory(argv[i], argv[i+1]));
    }
        
    Game game(players, packofCards, shuffleType, winPoints);
    game.play();
}