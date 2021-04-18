#pragma once
#include"card.h"



class Deck
{
    private:

    Card* deck;
    int sizeOfDeck;
    //includes '\0'
    char serie[11];
    void destroy();
  
    public:

    //constructors
    Deck();
    ~Deck();
    Deck(const Deck&);
    Deck& operator =( const Deck&) = delete;


    void setSerie();
    void ShuffleDeck();
    void createDefaultDeck();
    void createCustomDeck(int);

    void swap(size_t , size_t);
    Card& draw();
    int& suit_count(int);
    int& rank_count(int , int);


    Card& getDeckCard(int);
    
};