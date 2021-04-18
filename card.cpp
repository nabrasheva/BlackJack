#pragma once
#include<iostream>
#include"card.h"
#include<cstring>

Card& Card::createCard(int& value_ , int& paint_  )
{
    this->value = value_;

    switch (paint_)
    {
        case 0 : this->cardPaint = Clubs;
            break;
        case 1 : this->cardPaint = Diamonds;
            break;
        case 2 : this->cardPaint = Hearts;
            break;
        case 3 : this->cardPaint = Spades;
            break;
    }
    
    return *this;
}
void Card::setSerieOfCard( int index , bool default_)
{
   
   for(int i=0 ; i<15 ; i++)
   {
       this->serialNUmber[i] = '0';
   }
    if(default_)
    {
        strcpy(this->serialNUmber , "Default   ");
        int i = 10;
        while(index)
        {
             this->serialNUmber[i] = (index%10) + '0';
             index/=10;
             i++;
        }

    }
    else
    {
        strcpy(this->serialNUmber , "Custom    ");
        int i = 10;
        while(index)
        {
             this->serialNUmber[i] = (index%10) + '0';
             index/=10;
             i++;
        }
    }
    
//    for(int i=0 ; i<15 ; i++)
//    {
//        std::cout<<this->serialNUmber[i] ;
//    }
   
}
void Card::swapCards(Card& second)
{
    Card helper;
    helper.cardPaint = this->cardPaint;
    helper.value = this->value;
    for(int i =0  ; i<15 ; ++i)
    {
        helper.serialNUmber[i] = this->serialNUmber[i];
    }

    this->cardPaint = second.cardPaint;
    this->value = second.value;
    for(int i =0  ; i<15  ; ++i)
    {
        this->serialNUmber[i] = second.serialNUmber[i];
    }

    second.cardPaint = helper.cardPaint;
    second.value = helper.value;
    for(int i =0  ; i<15  ; ++i)
    {
        second.serialNUmber[i] = helper.serialNUmber[i];
    }

}
Paint& Card::getPaint()
{
    return this->cardPaint;
}
int& Card::getValue()
{
    return this->value;
}
void Card::getSerialNum()
{
    
    for(int i =0 ;this->serialNUmber[i] !='\0' ; ++i)
    {
        std::cout<<this->serialNUmber[i];
    }

}
std::ostream& operator<<(std::ostream& out, Card& item)
{
    
    switch (item.value)
    {
        case 11 : out<<" J";
            break;
        case 12 : out<<" Q";
            break;
        case 13 : out<<" K";
            break;
        case 14 : out<<" A";
            break;
        default: out<<" "<<item.value;
            break;
    }

    switch (item.cardPaint)
    {
        case 0 : out<<" Clubs ";
            break;
        case 1 : out<<" Diamonds ";
            break;
        case 2 : out<<" Hearts ";
            break;
        case 3 : out<<" Spades ";
            break;
    }
  
    
   
    return out;
}
Card& Card::operator=(Card& other)
{
    this->cardPaint = other.cardPaint;
    this->value = other.value;
    for(int i= 0 ; other.serialNUmber[i] !='\0' ; ++i)
    {
        this->serialNUmber[i] = other.serialNUmber[i];
    }
}
