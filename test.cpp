#include<iostream>
#include <iomanip>  
#include<cstring>
#include"card.h"
#include"card.cpp"
#include"deck.h"
#include"deck.cpp"
#include"player.h"
#include"player.cpp"
#include <cstdio>      
#include <stdlib.h>  
#include <time.h>
#include<fstream>



int main()
{
    
    
    std::cout<<std::setw(45)<<"------------------------------"<<std::endl;
    std::cout<<std::setw(34)<<"BLACKJACK"<<std::endl;
    std::cout<<std::setw(45)<<"------------------------------"<<std::endl;

    //print all players
    std::ifstream input ("players.txt");
    char row[20];
    while(!input.eof())
    {
        input.getline(row , 20 , '\n');
        std::cout<<row;
        std::cout<<std::endl;
    }
    input.close();



    Deck deck;
    std::cout<<" Choоse the size of the deck:"<<std::endl;
    int lenghtOfDeck;
    std::cin>>lenghtOfDeck;
    if(lenghtOfDeck == 52)
    {
        deck.createDefaultDeck();
        deck.setSerie();

    }
    else
    {
        deck.createCustomDeck(lenghtOfDeck);
        deck.setSerie();
    }
    Player player ;
    std::cout<<"enter player:"<<std::endl;
    std::cin>>player;


    char choice[15];
    char hit[4];
    strcpy( hit , "Hit");
    char stand[6];
    strcpy( stand , "Stand");
    char probability[12];
    strcpy( probability , "Probability");
    
    Card currentCard;
    int currentIndex=0;
    std::cin.ignore();
    //while player's points<21 && choice != Stand
    do
    {
        std::cout<<"Hit/Stand/Probability"<<std::endl;
        std::cin.getline(choice , 14);
        if(strcmp(choice , hit )== 0)
        {
            currentCard = deck.getDeckCard(currentIndex);
            player.calculatePoints(currentCard);
            std::cout<<currentCard<<" (Points: "<<player.getPoints()<<")"<<std::endl;
            currentIndex++;

        }
        else if( strcmp( choice , stand ) == 0)
        {
            break;
        }
        else if( strcmp( choice , probability ) == 0 )
        {
            int searchedValue = 21 - player.getPoints();
            int counter=0;
            for( int i = currentIndex ; i < lenghtOfDeck ; i++)
            {
                if( (deck.getDeckCard(i)).getValue() == searchedValue )
                {
                    counter++;
                }
            }
            int restOfTheCards = lenghtOfDeck - (currentIndex + 1);
            double result = counter / (double)restOfTheCards ;
            std::cout<< result <<std::endl;
        }
        else
        {
            std::cout<<"incorrect choice"<<std::endl;
        }
    }
    while ( player.getPoints()<=21);
    
    if(player.getPoints() > 21)
    {
        std::cout<<"Sorry Bro"<<std::endl;
        player.increaseGames();
        return 0;
    }

    
    currentIndex = 0;
    deck.ShuffleDeck();
    std::cout<<"The dealer’s draw:";
    Player computer;
    while( computer.getPoints() <= 17)
    {
        currentCard = deck.getDeckCard(currentIndex);
        std::cout<<currentCard<<" ";
        computer.calculatePoints(currentCard);
        currentIndex++;
    }
    std::cout<<"(Points:"<<computer.getPoints()<<")"<<std::endl;

    if(computer.getPoints() >21)
    {
        std::cout<<"You win"<<std::endl;
        player.increaseWins();
        return 0;
    }
    std::cout<<std::endl;
    if( player.getPoints() < 21 && computer.getPoints()<21 && player.getPoints()<computer.getPoints())
    {
        std::cout<<"Sorry Bro"<<std::endl;
        player.increaseGames();
        return 0;
    }
    else if(player.getPoints() < 21 && computer.getPoints()<21 && player.getPoints()>computer.getPoints())
    {
        std::cout<<"You win"<<std::endl;
        player.increaseWins();
        return 0;
    }
    else // if player's points == computer's points
    {
        std::cout<<"You win"<<std::endl;
        player.increaseWins();
        return 0;
    }
    
    

    return 0;
}