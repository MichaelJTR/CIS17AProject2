#ifndef HAND_H
#define HAND_H
#include <iostream>
#include <string>

using namespace std;

class Hand {
    private:
        static int Size;
    protected:
        int HSize;
    public:
        Hand() {
            HSize = 0;
        }
        ~Hand() {
            cout<<endl;
            cout<<"Resetting Hand Sizes To Zero"<<endl;
        }
        Hand(int s, int hs) {
            Size = s;
            HSize = hs;
        }
        void setHandSize(int);
        int getHandSize();
};

class PHand: public Hand {
    protected:
        int money;
        int bet;
    public:
        PHand() {
            money = 0;
            bet = 0;
        }
        void setMoney(int);
        void setBet(int);
        int getMoney();
        int getBet();
};

class DHand: public Hand {
    public:
        DHand() {}
        void Display();
};

#endif