#pragma once
#include<iostream>
#include"player.h"
#include"card.h"
#include<fstream>
#include<cstdio>
#include<iomanip>
#include<cstring>

int& Player::lenghtOfName()
{
    int counter=0;
    for(int i=0 ; this->name[i] != '\0' ; ++i)
    {
        counter++;
    }
    int* ptr = & counter;
    return *ptr ;
}

void Player::destroy()
{
    delete[] this->name;
}
void Player::copy( Player& other)
{
    this->name = new char [other.lenghtOfName() + 1];
    for(int i =0 ; i < other.lenghtOfName()  ; i++)
    {
        this->name[i] = other.name[i];
    }
    this->age = other.age;
    this->wins = other.wins;
    this->points = other.points;
    this->winsOfGames.numerator = other.winsOfGames.numerator ;
    this->winsOfGames.denominator = other.winsOfGames.denominator ;
}
Player::Player()
{
    this->name = nullptr;
    this->age = 0;
    this->wins = 0;
    this->points = 0;
    this->winsOfGames.numerator = 0 ;
    this->winsOfGames.denominator = 0 ;

}
Player::Player(Player& other)
{
    this->copy(other);
}
Player& Player::operator=(Player& other)
{
    if(this != &other)
    {
        this->destroy();
        this->copy(other);
    }
    return *this;
}

Player::~Player()
{
    this->destroy();
}

size_t& Player::getPoints()
{
    return this->points;
}
void Player::calculatePoints(Card& myCard)
{
    switch (myCard.getValue())
    {
        //  J / Q / K
        case 11:
        case 12:
        case 13: this->points += 10;
            break;
        case 14: // A
                 if(this->points <= 10 )
                 {
                     this->points += 11;
                 }
                 else
                 {
                     this->points += 1;
                 }
                 break;
                 
        default: this->points += myCard.getValue();
            break;
    }
}

void Player::increaseWins()
{
    this->wins += 1;

    this->winsOfGames.numerator += 1;
    this->winsOfGames.denominator += 1;
    //for testing you need to change the path 
    std::fstream in;
    in.open("/home/kristina/Music/BlackJack/players.txt" , std::fstream::in );
    std::fstream out;
    out.open("/home/kristina/Music/BlackJack/newPlayes.txt" , std::fstream::out);
    bool exist = false;
    char row[20];
    while(!in.eof())
    {
        in.getline(row , 19 , '\n');
        if(strcmp(row , this->name) == 0)
        {
            exist = true;

            out<<row;
            out<<'\n';
            out<<(this->wins);
            out<<'\n';
            out<<std::setprecision(1)<<( this->wins / (double)this->winsOfGames.denominator);
            out<<'\n';
            for(int i =0 ; i<2 ; ++i)
            {
               in.getline(row , 19 , '\n');
            }
               
        }
        else
        {
            out<<row;
            out<<'\n';
        }
        
    }
    if(!exist)
    {
        out<<this->name;
        out<<'\n';
        out<<(this->wins);
        out<<'\n';
        out<<std::setprecision(1)<<( this->wins / (double)this->winsOfGames.denominator);
        out<<'\n';
    }
    
    //for testing you need to change the path
    std::remove("/home/kristina/Music/BlackJack/players.txt");
    in.close();
    out.close();
    int result = std::rename("/home/kristina/Music/BlackJack/newPlayes.txt", "/home/kristina/Music/BlackJack/players.txt") ;
    if(result == 0)
    {
        std::cout<<"all files are successfully saved"<<std::endl;
    }
    else
    {
        std::cout<<"something went wrong"<<std::endl;
    }
   
    
}
void Player::increaseGames()
{
    this->winsOfGames.denominator += 1;
    //for testing you need to change the path
    std::fstream in;
    in.open("/home/kristina/Music/BlackJack/players.txt" , std::fstream::in );
    std::fstream out;
    out.open("/home/kristina/Music/BlackJack/newPlayes.txt" , std::fstream::out);
    bool exist = false;
    char row[20];
    while(!in.eof())
    {
        in.getline(row , 19 , '\n');
        if(strcmp(row , this->name) == 0)
        {
            exist = true;
            
            out<<row;
            out<<'\n';
            out<<(this->wins);
            out<<'\n';
            out<<std::setprecision(1)<<( this->wins / (double)this->winsOfGames.denominator);
            out<<'\n';
            for(int i =0 ; i<2 ; ++i)
            {
               in.getline(row , 19 , '\n');
            }
               
        }
        else
        {
            out<<row;
            out<<'\n';
        }
        
    }
    if(!exist)
    {
        out<<this->name;
        out<<'\n';
        out<<(this->wins);
        out<<'\n';
        out<<std::setprecision(1)<<( this->wins / (double)this->winsOfGames.denominator);
        out<<'\n';
    }
    
    
    //for testing you need to change the path
    std::remove("/home/kristina/Music/BlackJack/players.txt");
    in.close();
    out.close();
    int result = std::rename("/home/kristina/Music/BlackJack/newPlayes.txt", "/home/kristina/Music/BlackJack/players.txt") ;
    if(result == 0)
    {
        std::cout<<"all files are successfully saved"<<std::endl;
    }
    else
    {
        std::cout<<"something went wrong"<<std::endl;
    }
  
}
bool correctName(char* enteredName)
{
    size_t spaces = 0;
    
    if(enteredName[0] < 'A' || enteredName[0] > 'Z')
    {
        return false;
    }
    size_t upperCase = 1;
    for(int i=1 ; enteredName[i] != '\0' ; i++)
    {
        if( enteredName[i] == ' ')
        {
            spaces++;
            if(enteredName[i+1] < 'A' || enteredName[i+1] > 'Z')
            {
                return false;
            }  
        }
        else if( enteredName[i] >= 'A' && enteredName[i] <= 'Z' )
        {
            upperCase++;
        }
    }
    if( spaces != 1 || upperCase > 2 )
    {
        return false;
    }
    return true;
}

std::istream& operator>>(std::istream& in, Player& item)
{
    char str[35];
    
    do
    {
        do
        {
            std::cin.getline(str , 34);
        } while ( !correctName(str));

        std::cout<<"age: ";
        in>>item.age;

    } while (item.age < 18);//the person we enter have to be at least 18 years old

    item.name = new char [35];
    int i=0;
    for( ; str[i] != '\0' ; i++)
    {
        item.name[i] = str[i];
    }
    item.name[i] = '\0';

    std::ifstream input ("players.txt");
    char row[20];
    double koeficient;
    while(!input.eof())
    {
        input.getline(row , 20 , '\n');
        if(strcmp(row , item.name) == 0)
        {
            std::cout<<"You chose to play with: "<<item.name<<std::endl;
            input>>item.wins;
            input>>koeficient;
            item.winsOfGames.numerator =  item.wins ;
            item.winsOfGames.denominator =  item.wins / koeficient ;

        }
    }
    
    input.close();
    return in;
}

