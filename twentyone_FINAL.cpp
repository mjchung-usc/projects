/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Michele Chung
 * USC email: mjchung@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]); //passing on an array of integers into void shuffle. int cards is a parameter, whatever is inside () is a parameter
void printCard(int id); //passing on one integer
int cardValue(int id); //passing one one variable that's an integer and when done, returns int
void printHand(int hand[], int numCards); //passing 2 parameters separated by comma. int hand[] is a array of integers. int numCards is just one number. returning nothing. VOID MEANS YOU RETURN NOTHING, BUT YOU ARE MODIFYING THE VALUES STORED IN THE ARRAY. INT NUMCARDS IS NOT COMING OUT, BUT YOU NEED IT INSIDE OF PRINTHAND TO MODIFY THE ARRAY. 
void printQuestion(int hand[], int numCards);
int getBestScore(int hand[], int numCards); //returns an int
void compare(int phand[],int numInPlayer, int dhand[],int numInDealer);
    
const int NUM_CARDS = 52; //CONST does not allow a change. like if you don't want someone to change the value. 

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'}; //the ' ' means that it is just a single character
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"}; //the star means that the array has 13 elements of pointer that points to string. string is defined by " ". the reason that we have the * is because 10 is 2 characters, not 1 character, otherwise we could just use char type[13]. 
    //type[0] holds the address. that address points to/ holds to the other array [2][\0] (each is a character). * automatically puts the "10" into a string, which is then called by the address in char type[13]

const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11}; //goal is to code the int value with the char type. so giving char 2 a value of 2, giving char 3 a value of 3 

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/

    /*goals: 
        1. make the cards aka assign cards[i] array to cards
        2. randomly shuffle 
    */ 
      
    for (int i=0; i<NUM_CARDS;i++) //just puts the numbers in order from 0-51 so that the arrays have some value 
    {
        cards[i]=i;
      //  cout << cards[i]<<endl;
    }
    
    for (int i=NUM_CARDS-1; i>0; i--) // this is to shuffle the numbers in order from above 
    {
       
        int j=rand()%(i+1); //don't need to use srand b/c srand already affects the numbers in rand. so you just need to call rand. SRAND is a randomizing function while rand gives a random number 
        int temp=cards[i];
        cards[i]= cards[j]; //j is a random number. so cards[j] stores a card value
        cards[j]=temp;
        
    }
  //  cout << "shuffled cards: " <<endl;
    for (int i=0; i<NUM_CARDS; i++)
    {
   //    cout << cards[i]<<endl; 
    }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
   
    int i= id%13; //to get the valid type, if you mod the number by 13, then you can get the char[value]. ex: if id is 33, id%13= 7. type[7]=9.  
    int j = id/13;  // same with this. 33/13= 2. suits[2] = 'S' 
    cout <<type[i]<<"-"<<suit[j]<< " " ; 
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
    int i = id%13;
 //   cout<< value[i]<<endl; //returns the value of 2 to A being 11 
    return value[i];
}



/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
    for (int i=0; i<numCards; i++)
    {
        printCard(hand[i]);
        
    }
    


}

void printQuestion(int hand[], int numCards)
{
  /******** You complete ****************/
    for (int i=0; i<numCards; i++)
    {
        if (i==0)
            cout << "? " ;
        
        else
            printCard(hand[i]);
        
    }
    


}



/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/

    int numOfAce=0;
    int totalValue=0;
    
    for (int i =0; i<numCards; i++)
    {
        if (cardValue(hand[i])==11)
        {
            numOfAce++;
           // cout << " Num of Ace is " <<numOfAce<<endl;
               
        }
       
       // cout << "CardValue is "<<cardValue(hand[i])<<endl;
        //cout << " total value is " << totalValue<<endl;
        
        totalValue=totalValue+ cardValue(hand[i]);
     //   cout <<" New Total Value is " <<totalValue<<endl; 
        
    }
   // cout << " num of ace is : " <<numOfAce<<endl; 
    
    totalValue=(totalValue-((numOfAce)*11));
   
        while (numOfAce>0)
    {
        if ((totalValue+11)>21)
        {
            totalValue=totalValue+1;
            numOfAce=numOfAce-1; 
            
           /* if ((totalValue+1)>21)
               cout <<"hi"<<endl;
         
            else
                numOfAce=numOfAce-1; 
           */
        }
        else
        {
            totalValue=totalValue+11;
            numOfAce=numOfAce-1; 
        }
    }

    return totalValue;
}

void compare(int phand[],int numInPlayer, int dhand[],int numInDealer) //x is player's best score. y is dealer's best score. 
{
    int x= getBestScore(phand, numInPlayer);
    int y= getBestScore(dhand, numInDealer);
    
 if (x>21)
 {
    // cout << "Player: " ;
    // printHand(phand, numInPlayer);
  //   cout << endl; //phand is address of first element of phand. phand[0}
     cout << "Player busts" <<endl;
     cout << "Lose " << x <<" " << y <<endl; 
 }
 
 else if (y>21)
 {
     cout << "Dealer: " ;
     printHand(dhand, numInDealer);
     cout << endl; 
     cout << "Dealer busts" <<endl;
     cout << "Win " << x <<" " << y <<endl; 
 }
     
 else if (x>y)
 {
     cout << "Dealer: ";
     printHand(dhand, numInDealer); 
     cout << endl; //phand is address of first element of phand. phand[0}
     cout << "Win " << x <<" " << y <<endl; 
 }
 else if(y>x)
 {
     cout << "Dealer: ";
     printHand(dhand, numInDealer);
     cout << endl; //phand is address of first element of phand. phand[0}
     cout << "Lose " << x << " " << y <<endl; 
 }
 
  else if (x==y)
  {
      cout << "Dealer: ";
      printHand(dhand, numInDealer);
      cout << endl;
      cout << "Tie " << x << " " << y <<endl; 
  }
    
}




/**
 * Main program logic for the game of 21
 */


int main(int argc, char* argv[]) //as you run the program after you compile, it asks for a number which turns to string. so write ./twentyone 34. ./twentyone is put as a string into argv[0] and 34 is put as a character into the array as argv[1]
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){ //this can only be one when after you compile when you write twentyone
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  
  int seed = atoi(argv[1]); //takes the string (the seed number that user puts in) from above and puts it as an int seed 
  srand(seed);  //only need to run srand once. use srand number for the next subset of all rand numbers. srand does not return any value. just tells compiler that you are going to use seed for running a random number. so if you just write rand(), then it just thinks that seed is 1. rand doesn't take any input- just generates random number. 

  int cards[52]; //52 spots so cards[0] to cards[51]. cards array will store integers
  int dhand[9]; //int number of dealer's cards
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
    char playAgain; 
    char hitOrStay;
    
    shuffle(cards);
  
   /* for (int j=0; j< NUM_CARDS; j++)
        cout << cards[j] << endl;
         */
    
    
    playAgain='y';
    while (playAgain=='y')
    {
        int numInPlayer=0;
        int numInDealer=0;
        int total_cards_played=0;

        
        //give card to player then dealer (?)  then player to dealer. alternate 
        int i =0; 
        int d= 0;
        phand[i++]=cards[total_cards_played++];
            numInPlayer++;
        dhand[d++]=cards[total_cards_played++];
            numInDealer++;
        phand[i++]=cards[total_cards_played++];
            numInPlayer++;
        dhand[d++]=cards[total_cards_played++];
            numInDealer++;

        //cout<<"total_cards_played is: " << total_cards_played<<endl;

        
        cout << "Dealer: ";
        printQuestion(dhand, numInDealer);
       
        cout <<endl; 
        //print what the dealer has in his hand  
        
        cout << "Player: ";
        printHand(phand, numInPlayer);//print what player has in his hand 
        cout <<endl; 
        
        if (getBestScore(phand, numInPlayer)==21)
        {
           
            hitOrStay='s';
        }
        else
        {
            cout << "Type 'h' to hit and 's' to stay: " <<endl;
            cin >>hitOrStay;
        }
        
    
        while (hitOrStay=='h')
        {
                
                phand[i++]=cards[total_cards_played++];
              //  cout<<"total_cards_played is: " << total_cards_played<<endl;
                numInPlayer++;
                
                cout << "Player: ";
                printHand(phand, numInPlayer);//print what player has in his hand 
                 cout <<endl; 
                 
                 if ((getBestScore(phand, numInPlayer))<21)
                     {
                        cout <<"Type 'h' to hit and 's' to stay: " <<endl;
                        cin >> hitOrStay; 
                     }
            
                else if ((getBestScore(phand, numInPlayer))==21)
                    {
                        hitOrStay='s';
                    }
                else //like if it equals 21 or is over 21 
                     {
                        compare(phand, numInPlayer, dhand, numInDealer);

                        hitOrStay='n';
                     }

        
        }
        
       
        if (hitOrStay=='s')
        {
            if ((getBestScore(dhand, numInDealer)<17))
            {
               while ((getBestScore(dhand, numInDealer)<17))
            {
               dhand[d++]=cards[total_cards_played++];
               numInDealer++;
              // cout << "Dealer: ";
            //   printHand(dhand, numInDealer);
          //     cout <<endl; 
            }
                
            }
            compare(phand, numInPlayer, dhand, numInDealer);
        }
            

  cout <<"Play again? [y/n]"<<endl; 
  cin >>playAgain;
  shuffle(cards);
  total_cards_played=0;
        
    
  
                
 }//end of while loop 
    
       
    
   return 0;    
}
  