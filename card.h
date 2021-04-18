#pragma once

//includes '\0'


enum Paint
{
    //spatiq
    Clubs ,
    //karo
    Diamonds ,
    //kupa
    Hearts ,
    //pika
    Spades
};

class Card
{
    private:

    Paint cardPaint;
    int value;
    char serialNUmber[16];

    
    public:

    Card& createCard(int& , int& );
    void setSerieOfCard(int  , bool);
    void swapCards(Card&);
    Paint& getPaint();
    int& getValue();
    Card& operator=(Card&);
    friend std::ostream& operator<<(std::ostream& out, Card&);
    //for testing
    void getSerialNum();

};
