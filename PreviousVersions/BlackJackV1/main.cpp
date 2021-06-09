/* 
 * File:   main.cpp
 * Author: Michael Echaluse
 * Created on May 17, 2021
 * Purpose:  Blackjack
 *           
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <fstream>
using namespace std;

//User Libraries
struct Deck {
    string name;
    string suit;
    unsigned short value;
};
#include "Hand.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
void introB();
void Shuffle(Deck *);
Deck *cLoad(int );
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    



    //Declare Variables
    fstream trackF;
    unsigned int money;
    unsigned int bet;
    unsigned short move;
    unsigned short choice;
    unsigned short ptotal;
    unsigned short dtotal;
    unsigned short phSize;
    unsigned short dhSize;
    unsigned short round;
    int size;
    int current;
    bool play;
    Deck *deckG;
    introB();
    //Initialize Variables
    Deck *player = new Deck[11];  
    //I chose 11 as player hand size because that is the highest a person can get dealt without busting.
    Deck *dealer = new Deck[11];
    PHand fplayer;
    DHand mdealer;
    Hand *pl = &fplayer;
    Hand *dl = &mdealer;
    round = 0;
    cout<<"Enter Total Betting Money: ";
    //Money player can used if they choose to repeat the game
    cin>>money;
    fplayer.setMoney(money);
    trackF.open("GameReport.txt", ios::out);
    trackF<<"Initial Betting Amount: "<<money<<endl;
    do {
        round = round + 1;
        trackF<<"Round "<<round<<endl;
        size = 52;
        current = size; //Used to keep track the current size of deck after a card is dealt
        phSize = 2; //Player Hand Size
        dhSize = 2; //Dealer Hand Size
        ptotal = 0; //Player total
        dtotal = 0; //Dealer total
        pl->setHandSize(phSize);
        dl->setHandSize(dhSize);
        bet = 0;
        cout<<"Enter betting amount: ";
        cin>>bet;
        fplayer.setBet(bet);
        while(fplayer.getBet() > fplayer.getMoney()) {
            cout<<"Invalid Bet"<<endl;
            cout<<"Enter A Valid Bet: ";
            cin>>bet;
            fplayer.setBet(bet);
        }
        trackF<<"Bet: "<<bet<<endl;
        cout<<endl;
        cout<<"Loading Deck...."<<endl;
        Sleep(1000);
        deckG = cLoad(size); 
        //Loads a new array of struct of 52-deck of cards
        cout<<"Shuffling Deck...."<<endl;
        Sleep(1000);
        Shuffle(deckG); 
        //Shuffles the deck to randomize card placements
        cout<<"Dealing cards to player."<<endl;
        cout<<endl;
        for(int i = 0; i < pl->getHandSize(); i++) { 
            //For Loop used to deal cards to the player.
            player[i] = deckG[current-(i+1)];
        }
        current = current - pl->getHandSize();
        Sleep(500);
        cout<<"Dealing cards to dealer."<<endl;
        //For Loop used to deal cards to the dealer.
        for(int i = 0; i < dl->getHandSize(); i++) { 
            dealer[i] = deckG[current-(i+1)];
        }
        current = current - dl->getHandSize();
        Sleep(500);
        cout<<endl;
        trackF<<"Your Initial Hand Include: "<<endl;
        for(int i = 0; i < pl->getHandSize(); i++) {
            trackF<<player[i].name<<" of "<<player[i].suit<<endl;
        }
        trackF<<endl;
        trackF<<"The Dealer's Initial Hand Include: "<<endl;
        for(int i = 0; i < dl->getHandSize(); i++) {
            trackF<<dealer[i].name<<" of "<<dealer[i].suit<<endl;
        }
        trackF<<endl;
        do {
            trackF<<endl;
            ptotal = 0;
            dtotal = 0;
            cout<<"Your Hand Includes: "<<endl;
            for(int i = 0; i < pl->getHandSize(); i++) {
                cout<<player[i].name<<" of "<<player[i].suit<<endl;
                ptotal += player[i].value;
            }
            cout<<"Your Total Card Value Is Now: "<<ptotal<<endl;
            cout<<endl;
            cout<<"The Dealer's Hand Includes: "<<endl;
            for(int i = 0; i < dl->getHandSize(); i++) {
                if(i == 0) {
                    //In Blackjack the first card of the dealer is always hidden until the player stands.
                    cout<<"The Dealer's First Card Is Hidden."<<endl; 
                }
                else {
                    cout<<dealer[i].name<<" of "<<dealer[i].suit<<endl;
                }
                dtotal += dealer[i].value;
            }
            cout<<endl;
            cout<<"The Dealer's Total Card Value Excluding The First Card Is: "<<(dtotal-dealer[0].value)<<endl;
            cout<<endl;
            if(ptotal > 21 || dtotal > 21) {
                break;
            }
            cout<<"Do You Want to Hit or Stand(Press 1 for Hit or Press 2 for Stand): ";
            cin>>move;
            while(move != 1 && move != 2) {
                cout<<"Invalid Choice"<<endl;
                cout<<"Hit or Stand: ";
                cin>>move;
            }
            cout<<endl;
            if(move == 1) {
                trackF<<"You Chose To Hit"<<endl;
                player[phSize] = deckG[current-1];
                cout<<"You Were Dealt the "<<player[phSize].name<<" of "<<player[phSize].suit<<endl;
                trackF<<"You Were Dealt the "<<player[phSize].name<<" of "<<player[phSize].suit<<endl;
                ptotal = ptotal + player[phSize].value;
                if(ptotal > 21) {
                    cout<<"Your Hand Went Over 21"<<endl;
                    trackF<<"Your Hand Went Over 21"<<endl;
                }
                phSize = phSize + 1;
                pl->setHandSize(phSize);
                current = current - 1;
                system("pause");
                cout<<endl;
            }
            else if(move == 2) {
                cout<<"You Chose To Stand."<<endl;
                trackF<<"You Chose To Stand"<<endl;
                cout<<endl;
                //Fully reveals the hand of the dealer
                cout<<"The Dealer's Hand Includes: "<<endl; 
                for(int i = 0; i < dl->getHandSize(); i++) {
                    cout<<dealer[i].name<<" of "<<dealer[i].suit<<endl;
                }
                Sleep(1000);
                cout<<endl;
                trackF<<endl;
                //Will continue to deal to the dealer until their total value is above 17
                while(dtotal <= 17) { 
                    dealer[dhSize] = deckG[current-1];
                    cout<<"The Dealer Dealt Themself the "<<dealer[dhSize].name<<" of "<<dealer[dhSize].suit<<endl;
                    trackF<<"The Dealer Dealt Themself the "<<dealer[dhSize].name<<" of "<<dealer[dhSize].suit<<endl;
                    dtotal = dtotal + dealer[dhSize].value;
                    Sleep(500);
                    dhSize = dhSize + 1;
                    dl->setHandSize(dhSize);
                    current = current - 1;
                    cout<<endl;
                    trackF<<endl;
                }
            }
        }while((move == 1 && ptotal <= 21) || (move == 1 && dtotal <= 21));
        Sleep(2000);
        ptotal = 0;
        dtotal = 0;
        cout<<endl;
        trackF<<endl;
        cout<<setw(25)<<setfill(' ')<<"FINAL HANDS"<<endl;
        trackF<<setw(25)<<setfill(' ')<<"FINAL HANDS"<<endl;
        cout<<endl;
        trackF<<endl;
        cout<<setw(25)<<setfill(' ')<<"Your Hand"<<endl;
        trackF<<setw(25)<<setfill(' ')<<"Your Hand"<<endl;
        for(int i = 0; i < pl->getHandSize(); i++) {
            cout<<player[i].name<<" of "<<player[i].suit<<endl;
            trackF<<player[i].name<<" of "<<player[i].suit<<endl;
            ptotal += player[i].value;
        }
        cout<<"With A Total Value of: "<<ptotal<<endl;
        trackF<<"With A Total Value of: "<<ptotal<<endl;
        cout<<endl;
        trackF<<endl;
        Sleep(500);
        cout<<setw(25)<<setfill(' ')<<"Dealer's Hand"<<endl;
        trackF<<setw(25)<<setfill(' ')<<"Dealer's Hand"<<endl;
        for(int i = 0; i < dl->getHandSize(); i++) {
            cout<<dealer[i].name<<" of "<<dealer[i].suit<<endl;
            trackF<<dealer[i].name<<" of "<<dealer[i].suit<<endl;
            dtotal += dealer[i].value;
        }
        cout<<"With A Total Value of: "<<dtotal<<endl;
        trackF<<"With A Total Value of: "<<dtotal<<endl;
        cout<<endl;
        trackF<<endl;
        Sleep(500);
        //Parameters to compare the total value of the player's hand to the dealer's
        if((ptotal > dtotal) && ptotal <= 21) { 
            cout<<"Your Hand Was Better Than The Dealer."<<endl;
            cout<<"You Won: "<<bet*2<<endl;
            money = fplayer.getMoney() + (fplayer.getBet());
            fplayer.setMoney(money);
            trackF<<"Your Hand Was Better Than The Dealer."<<endl;
            trackF<<"You Won: "<<bet*2<<endl;
        }
        else if((dtotal > ptotal) && ptotal <= 21 && dtotal <= 21) {
            cout<<"Your Hand Was Not Better Than The Dealer."<<endl;
            cout<<"You Lost: "<<bet<<endl;
            money = fplayer.getMoney() - fplayer.getBet();
            fplayer.setMoney(money);
            trackF<<"Your Hand Was Not Better Than The Dealer."<<endl;
            trackF<<"You Lost: "<<bet<<endl;
        }
        else if(ptotal > 21) {
            cout<<"Your Cards Went Over 21."<<endl;
            cout<<"You Lost: "<<bet<<endl;
            money = fplayer.getMoney() - fplayer.getBet();
            fplayer.setMoney(money);
            trackF<<"Your Cards Went Over 21."<<endl;
            trackF<<"You Lost: "<<bet<<endl;
        }
        else if(dtotal > 21) {
            cout<<"The Dealer's Hand Went Over 21."<<endl;
            cout<<"You Won: "<<bet*2<<endl;
            money = fplayer.getMoney() + (fplayer.getBet());
            fplayer.setMoney(money);
            trackF<<"The Dealer's Hand Went Over 21."<<endl;
            trackF<<"You Won: "<<bet*2<<endl;
        }
        else if(ptotal == dtotal) {
            cout<<"Your Cards and the Dealer's Cards Value are the Same."<<endl;
            cout<<"You Broke Even."<<endl;
            trackF<<"Your Cards and the Dealer's Cards Value are the Same."<<endl;
            trackF<<"You Broke Even."<<endl;
        }
        cout<<"Your New Total Is Now: "<<fplayer.getMoney()<<endl;
        cout<<endl;
        trackF<<"Your New Total Was Now: "<<fplayer.getMoney()<<endl;
        trackF<<endl;
        if(fplayer.getMoney() == 0) {
            cout<<"You No Longer Have Any Betting Money"<<endl;
            trackF<<"You No Longer Have Any Betting Money"<<endl;
            return 0;
        }
        cout<<"Do You Want To Play Again(Press 1 for Yes or Press 2 for No): ";
        cin>>choice;
        while(choice != 1 && choice != 2) {
            cout<<"Invalid Choice."<<endl;
            cout<<"Yes or No: ";
            cin>>choice;
        }
        //If player chooses 2, the program will end
        if(choice == 2) {
            play = false;
        }
        //If player chooses anything besides 2, do-loop will repeat code
        else {
            play = true;
            trackF<<"You Chose To Play Again."<<endl;
            trackF<<endl;
        }
        //Close file output to be saved
        trackF.close();
    } while(play == true);
    //Map Inputs to Outputs -> Process
    
    //Display Inputs/Outputs
    
    //Exit the Program - Cleanup
    delete [] player;
    delete [] dealer;
    delete [] deckG;
    return 0;
}

void introB() {
    cout<<endl;
    cout<<"Welcome to Blackjack!"<<endl;
    cout<<"Blackjack is a hit-or-stand card game in which the player must beat the dealer's hand or get Blackjack in order to win each game."<<endl;
    cout<<endl;
}

void Shuffle(Deck *cards) {
    unsigned short rNum;
    srand(time(NULL));
    Deck temp;
    //For loop used to shuffle the deck that was created in cLoad() and randomize the placement of the array of structs
    for(int i = 0; i < 52; i++) { 
        rNum = rand()%52;
        temp = cards[i];
        cards[i] = cards[rNum];
        cards[rNum] = temp;
    }
}

//Function to manually load a 52-deck of cards
Deck *cLoad(int deckS) { 
    Deck *cards = new Deck[deckS];

    cards[0].name = "Ace";
    cards[0].suit = "Clubs";
    cards[0].value = 11;

    cards[1].name = "Two";
    cards[1].suit = "Clubs";
    cards[1].value = 2;
    
    cards[2].name = "Three";
    cards[2].suit = "Clubs";
    cards[2].value = 3;
    
    cards[3].name = "Four";
    cards[3].suit = "Clubs";
    cards[3].value = 4;
    
    cards[4].name = "Five";
    cards[4].suit = "Clubs";
    cards[4].value = 5;
    
    cards[5].name = "Six";
    cards[5].suit = "Clubs";
    cards[5].value = 6;
    
    cards[6].name = "Seven";
    cards[6].suit = "Clubs";
    cards[6].value = 7;
    
    cards[7].name = "Eight";
    cards[7].suit = "Clubs";
    cards[7].value = 8;
    
    cards[8].name = "Nine";
    cards[8].suit = "Clubs";
    cards[8].value = 9;
    
    cards[9].name = "Ten";
    cards[9].suit = "Clubs";
    cards[9].value = 10;
    
    cards[10].name = "Jack";
    cards[10].suit = "Clubs";
    cards[10].value = 10;
    
    cards[11].name = "Queen";
    cards[11].suit = "Clubs";
    cards[11].value = 10;
    
    cards[12].name = "King";
    cards[12].suit = "Clubs";
    cards[12].value = 10;

    cards[13].name = "Ace";
    cards[13].suit = "Spades";
    cards[13].value = 11;

    cards[14].name = "Two";
    cards[14].suit = "Spades";
    cards[14].value = 2;

    cards[15].name = "Three";
    cards[15].suit = "Spades";
    cards[15].value = 3;

    cards[16].name = "Four";
    cards[16].suit = "Spades";
    cards[16].value = 4;

    cards[17].name = "Five";
    cards[17].suit = "Spades";
    cards[17].value = 5;

    cards[18].name = "Six";
    cards[18].suit = "Spades";
    cards[18].value = 6;

    cards[19].name = "Seven";
    cards[19].suit = "Spades";
    cards[19].value = 7;

    cards[20].name = "Eight";
    cards[20].suit = "Spades";
    cards[20].value = 8;

    cards[21].name = "Nine";
    cards[21].suit = "Spades";
    cards[21].value = 9;

    cards[22].name = "Ten";
    cards[22].suit = "Spades";
    cards[22].value = 10;

    cards[23].name = "Jack";
    cards[23].suit = "Spades";
    cards[23].value = 10;

    cards[24].name = "Queen";
    cards[24].suit = "Spades";
    cards[24].value = 10;

    cards[25].name = "King";
    cards[25].suit = "Spades";
    cards[25].value = 10;

    cards[26].name = "Ace";
    cards[26].suit = "Hearts";
    cards[26].value = 11;

    cards[27].name = "Two";
    cards[27].suit = "Hearts";
    cards[27].value = 2;

    cards[28].name = "Three";
    cards[28].suit = "Hearts";
    cards[28].value = 3;

    cards[29].name = "Four";
    cards[29].suit = "Hearts";
    cards[29].value = 4;

    cards[30].name = "Five";
    cards[30].suit = "Hearts";
    cards[30].value = 5;

    cards[31].name = "Six";
    cards[31].suit = "Hearts";
    cards[31].value = 6;

    cards[32].name = "Seven";
    cards[32].suit = "Hearts";
    cards[32].value = 7;

    cards[33].name = "Eight";
    cards[33].suit = "Hearts";
    cards[33].value = 8;

    cards[34].name = "Nine";
    cards[34].suit = "Hearts";
    cards[34].value = 9;

    cards[35].name = "Ten";
    cards[35].suit = "Hearts";
    cards[35].value = 10;

    cards[36].name = "Jack";
    cards[36].suit = "Hearts";
    cards[36].value = 10;

    cards[37].name = "Queen";
    cards[37].suit = "Hearts";
    cards[37].value = 10;

    cards[38].name = "King";
    cards[38].suit = "Hearts";
    cards[38].value = 10;

    cards[39].name = "Ace";
    cards[39].suit = "Diamonds";
    cards[39].value = 11;

    cards[40].name = "Two";
    cards[40].suit = "Diamonds";
    cards[40].value = 2;

    cards[41].name = "Three";
    cards[41].suit = "Diamonds";
    cards[41].value = 3;

    cards[42].name = "Four";
    cards[42].suit = "Diamonds";
    cards[42].value = 4;

    cards[43].name = "Five";
    cards[43].suit = "Diamonds";
    cards[43].value = 5;

    cards[44].name = "Six";
    cards[44].suit = "Diamonds";
    cards[44].value = 6;

    cards[45].name = "Seven";
    cards[45].suit = "Diamonds";
    cards[45].value = 7;

    cards[46].name = "Eight";
    cards[46].suit = "Diamonds";
    cards[46].value = 8;

    cards[47].name = "Nine";
    cards[47].suit = "Diamonds";
    cards[47].value = 9;

    cards[48].name = "Ten";
    cards[48].suit = "Diamonds";
    cards[48].value = 10;

    cards[49].name = "Jack";
    cards[49].suit = "Diamonds";
    cards[49].value = 10;

    cards[50].name = "Queen";
    cards[50].suit = "Diamonds";
    cards[50].value = 10;

    cards[51].name = "King";
    cards[51].suit = "Diamonds";
    cards[51].value = 10;

    return cards;
}