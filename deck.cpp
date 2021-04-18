#pragma once
#include<iostream>
#include<cstring>
#include"card.h"
#include"deck.h"
#include <stdio.h>     //remove  rename file
#include <stdlib.h>  //srand rand
#include <time.h> //time

void Deck::destroy()
{
    delete[] this->deck;
}
Deck::Deck()
{
    this->deck = nullptr;
    this->sizeOfDeck = 0;

}
Deck::~Deck()
{
   this->destroy();
}
Deck::Deck(const Deck& other)
{
    this->sizeOfDeck = other.sizeOfDeck;
    this->deck = new Card[this->sizeOfDeck];
    for(int i = 0 ; i < this->sizeOfDeck ; ++i)
    {
        this->deck[i] = other.deck[i];
    }
    for(int i=0 ; other.serie[i] != '\0' ; ++i)
    {
        this->serie[i] = other.serie[i];
    }
}
void Deck::setSerie()
{
    //if deck size = 52 
    bool default_;

    if(this->sizeOfDeck == 52)
    {
        default_ = true;
        strcpy(this->serie , "Default   ");
        for(int i =0 ; i<52 ; ++i)
        {
            this->deck[i].setSerieOfCard( i , default_);
        }
    }
    else //if deck size != 52
    {
        default_ = false;
        strcpy(this->serie , "Custom    ");
        for(int i =0 ; i< this->sizeOfDeck ; ++i)
        {
            this->deck[i].setSerieOfCard(i , default_);
        }
    }
    
}
void Deck::swap(size_t first , size_t second)
{
    if( ( first >= 0 && first < this->sizeOfDeck )  && ( second >= 0 && second < this->sizeOfDeck ))
    {
        this->deck[first].swapCards(this->deck[second]);
    }
}
Card& Deck::draw()
{
    if(this->deck != nullptr && this->sizeOfDeck > 1)
    {
        for(int i=0 ; i < this->sizeOfDeck-1 ; i++)
        {
            this->deck[i].swapCards(this->deck[i+1]);
        }
        return this->deck[sizeOfDeck-1];
    }
}
int& Deck::suit_count(int paint_)
{
    if( paint_ >=0 && paint_<=3)
    {
        int* ptr = nullptr;
        int count = 0 ;
        for(int i=0 ; i < this->sizeOfDeck ; ++i)
        {
            if( this->deck[i].getPaint() == paint_)
            {
                count++;
            }
        }
        ptr = &count;
        return *ptr;
    }
}
int& Deck::rank_count(int searchedValue , int index)
{
    int counter=0;
    for(int i= index ; i<this->sizeOfDeck ; i++)
    {
        if(this->deck[i].getValue() == searchedValue)
        {
            counter++;
        }
    }
    int* ptr = &counter;
    return *ptr;
}
void Deck::ShuffleDeck()
{
    srand(time(0));
    int index;
    for(int i=0 ; i < 51 ; ++i)
    {
        index = i + (rand() % (52 -i));
        this->deck[i].swapCards(this->deck[index]);
    }
}
void Deck::createDefaultDeck()
{
    //create ordered deck of 52 cards
    this->sizeOfDeck = 52;
    this->deck = new  Card[52];
    int indexOfCard=0;
    //for card value
    for(int j = 2 ; j <= 14 ; ++j )
    {   //for card paint      
        for(int k=0 ; k<4 ; ++k)
            {
               deck[indexOfCard].createCard( j , k );
               indexOfCard++;
            }
    }
    this->ShuffleDeck();    
}
void Deck::createCustomDeck(int size_)
{
    if(size_ < 52)
    {
       this->createDefaultDeck(); 
       this->sizeOfDeck = size_;
    }
    else
    {  // if size_ > 52  
        this->sizeOfDeck = size_;
        this->deck = new Card [this->sizeOfDeck];

        Deck currentDeck;
        currentDeck.createDefaultDeck();

        int index = 0 ;
        while( size_ > 52)
        {
            for(int i =0 ; i < 52 ; i++)
            {
                this->deck[index] = currentDeck.deck[i];
                index++;
            } 
            currentDeck.ShuffleDeck();
            size_= size_ - 52;
        }

        int i=0;
        currentDeck.ShuffleDeck();
        while( size_)
        {
            this->deck[index] = currentDeck.deck[i];
            index++;
            size_-=1;
            i++;
        }

    }

}

Card& Deck::getDeckCard(int i)
{
    return this->deck[i];
}