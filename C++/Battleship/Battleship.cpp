#include <iostream>
using namespace std;

//Declare arrays
char gameboard[10][10];
char display[10][10];
char p2gameboard[10][10];
char p2display[10][10];

//Declare variables
char input;
char input2;
int battleshipChoice;
bool placedship1;
bool placedship2;
bool placedship3;
bool placedship4;
bool placedship5;
bool chooseShip;
int direction;
int ship1x[2];
int ship1y[2];
int ship2x[3];
int ship2y[3];
int ship3x[3];
int ship3y[3];
int ship4x[4];
int ship4y[4];
int ship5x[5];
int ship5y[5];
int p2ship1x[2];
int p2ship1y[2];
int p2ship2x[3];
int p2ship2y[3];
int p2ship3x[3];
int p2ship3y[3];
int p2ship4x[4];
int p2ship4y[4];
int p2ship5x[5];
int p2ship5y[5];
int guessX;
int guessY;

//Declare functions
void initializeBoard(char a[10][10]);
void printBoard(char a[10][10]);
void plantShip(char a[10][10], int b[], int c[], int d, char e);
bool checkOverlap(char a[10][10], int b[], int c[], int d);
bool checkWin(char a[10][10]);
bool checkHit(char a[10][10], int b, int c);

//Prints the board

int main() {

  //Print out opening title and directions.
  cout << "\n\n\nWelcome To Battleship!\n\n\n";

  cout << "Directions: 1, 2, 3, 4, and 5 mean that you have a ship in that space, and the number shows which ship is taking up that space. X means that the opponent or you has guessed that coordinate and it has hit a ship. M means that you or the opponent has guessed that coordinate but nothing was hit. If a ship sinks, the player whose ship sank has to call it out. Guess where your opponents ships are and knock them down!" << endl << endl;

  //Initialize the boards using a function to give each part of the array the value ' ' so that it shows as a space when the board is printed. 
  initializeBoard(gameboard);
  initializeBoard(p2gameboard);
  initializeBoard(display);
  initializeBoard(p2display);

  //Repeat 2 times for both players' turns.
  for(int i = 0; i < 2; i++){

    //If it is happening the first time, it is Player 1's turn, otherwise it's Player 2's turn.
    if(i == 0){
      printBoard(gameboard);
      cout << "\n\n\nPlayer 1 goes first. Which battleship would you like to place?\n\n";
    }else{
      printBoard(p2gameboard);
      cout << "\n\n\nPlayer 2's turn. Which battleship would you like to place?\n\n";
    }

    //Reset values for player 2. These values are just used to help the player place the ship, so they will be the same for both players.
    placedship1 = false;
    placedship2 = false;
    placedship3 = false;
    placedship4 = false; 
    placedship5 = false; 

  //Inside this loop is the code to place a ship on the grid. There are 5 ships, so it will repeat 5 times.
  for(int j = 0; j < 5; j++){

    //Reset value of chooseShip.
    chooseShip = false;

    //Print out options.
    cout << "1) Mini Battleship (2 Spaces)\n2) Small Battleship (3 Spaces)\n3) Small Battleship (3 Spaces)\n4) Medium Battleship (4 Spaces)\n5) Large Battleship (5 Spaces)\n\n";
    cin >> battleshipChoice;

    //Error statements that will ask the user to try again if they select a ship that they already placed in case they forgot, or enters an invalid number. This uses bools to see if the chosen ship is already placed, and uses chooseShip to see if the user chose a ship so that it doesn't assign the value of the bool as true without anything happening. 
    while(chooseShip == 0){
    if(placedship1 == 1){
      while(battleshipChoice == 1){
        cout << "You already placed that ship. Please try again: ";
        cin >> battleshipChoice;
      }
    }
    if(placedship2 == 1){
      while(battleshipChoice == 2){
        cout << "You already placed that ship. Please try again: ";
        cin >> battleshipChoice;
      }
    }
    if(placedship3 == 1){
      while(battleshipChoice == 3){
        cout << "You already placed that ship. Please try again: ";
        cin >> battleshipChoice;
      }
    }
    if(placedship4 == 1){
      while(battleshipChoice == 4){
        cout << "You already placed that ship. Please try again: ";
        cin >> battleshipChoice;
      }
    }
    if(placedship5 == 1){
      while(battleshipChoice == 5){
        cout << "You already placed that ship. Please try again: ";
        cin >> battleshipChoice;
      }
    }
    while(battleshipChoice < 1 || battleshipChoice > 5){
        cout << "Invalid Input. Please try again: ";
        cin >> battleshipChoice;
    }
    if(battleshipChoice == 1 && placedship1 == 0){
      chooseShip = true;
    }
    if(battleshipChoice == 2 && placedship2 == 0){
      chooseShip = true;
    }
    if(battleshipChoice == 3 && placedship3 == 0){
      chooseShip = true;
    }
    if(battleshipChoice == 4 && placedship4 == 0){
      chooseShip = true;
    }
    if(battleshipChoice == 5 && placedship5 == 0){
      chooseShip = true;
    }
    }

    cout << endl << endl << endl;

    //Switch case with 5 cases for 5 different ships that the player could have chosen. 
    switch(battleshipChoice){

      //Case 1: User chooses to plant mini battleship (2 Spaces).
      case 1: {

        //Make the bool for placing ship 1 true so the player cannot choose it again when the loop repeats. 
        placedship1 = true; 

        //Instead of the user inputting every single coordinate and the code checking each coordinate, ask the user which way his ship will be placed and ask them for the leftmost or highest coordinate on that ship so it can be automatically planted by the code.
        cout << "How would you like your ship to be placed?\n\n1) Horizontally\n2) Vertically\n\n";
        cin >> direction;

        cout << endl;

        //Error message
        while(direction > 2 || direction < 1){
          cout << "Invalid input. PLease try again: ";
          cin >> direction;
        }

        cout << endl << endl;

        //Switch case for what direction the user chooses to place their ship.
        switch(direction){

          //Case 1: User chooses to plant mini battleship horizontally.
          case 1: {

            //Ask for the left most coordinate of the ship.
            cout << "Input the left coordinate of your ship:\n\nX: ";

            //Use an array for each x and each y value of each ship for each player. This way one array can hold all the x/y values of a ship, making it easy to check overlaps. 
            if(i == 0){
              cin >> ship1x[0];
              cout << "Y: ";
              cin >> ship1y[0];
            }else{
              cin >> p2ship1x[0];
              cout << "Y: ";
              cin >> p2ship1y[0];
            }

            //Once given the direction and value of the left coordinate, the computer can add 1 to the x values and make the ship be placed going right, while keeping the y value the same to make it go horizontally straight.
            if(i == 0){
              ship1x[1] = ship1x[0] + 1;
              ship1y[1] = ship1y[0];
            }else{
              p2ship1x[1] = p2ship1x[0] + 1;
              p2ship1y[1] = p2ship1y[0];
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function). Re-assign values of the rest of the coordinates here, because the user enters a new first coordinate. 
            if(i == 0){
              while(ship1x[0] < 1 || ship1x[0] > 9 || ship1y[0] < 1 || ship1y[0] > 10 || checkOverlap(gameboard, ship1x, ship1y, 2) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship1x[0];
                cout << "Y: ";
                cin >> ship1y[0];

                ship1x[1] = ship1x[0] + 1;
                ship1y[1] = ship1y[0];

                cout << endl << endl;
              }
            }else{
              while(p2ship1x[0] < 1 || p2ship1x[0] > 9 || p2ship1y[0] < 1 || p2ship1y[0] > 10 || checkOverlap(p2gameboard, p2ship1x, p2ship1y, 2) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship1x[0];
                cout << "Y: ";
                cin >> p2ship1y[0];

                p2ship1x[1] = ship1x[0] + 1;
                p2ship1y[1] = p2ship1y[0];

                cout << endl << endl;
              }
            }

            break;

          }

          //Case 2: User chooses to plant mini battleship vertically.
          case 2: {

            //Ask for the top coordinate of the mini batlleship.
            cout << "Input the top coordinate of your ship:\n\nX: ";

            //Put in top coordinate. 
            if(i == 0){
              cin >> ship1x[0];
              cout << "Y: ";
              cin >> ship1y[0];
            }else{
              cin >> p2ship1x[0];
              cout << "Y: ";
              cin >> p2ship1y[0];
            }

            //Assign the rest of the values to the mini battleship. X remains the same and y increases by 1.
            if(i == 0){
              ship1x[1] = ship1x[0];
              ship1y[1] = ship1y[0] + 1;
            }else{
              p2ship1x[1] = p2ship1x[0];
              p2ship1y[1] = p2ship1y[0] + 1;
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship1x[0] < 1 || ship1x[0] > 10 || ship1y[0] < 1 || ship1y[0] > 9 || checkOverlap(p2gameboard, p2ship1x,p2ship1y, 2) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship1x[0];
                cout << "Y: ";
                cin >> ship1y[0];

                ship1x[1] = ship1x[0];
                ship1y[1] = ship1y[0] + 1;

                cout << endl << endl;
              }
            }else{
              while(p2ship1x[0] < 1 || p2ship1x[0] > 10 || p2ship1y[0] < 1 || p2ship1y[0] > 9 || checkOverlap(p2gameboard, p2ship1x, p2ship1y, 2) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship1x[0];
                cout << "Y: ";
                cin >> p2ship1y[0];

                p2ship1x[1] = p2ship1x[0];
                p2ship1y[1] = p2ship1y[0] + 1;

                cout << endl << endl;
              }
            }

            break;

          }

          default:{
            break;
          }

        }

        //Use function plantship to plant the mini battleship on the array, and print out the board. 
        if(i == 0){
          plantShip(gameboard, ship1x, ship1y, 2, '1');
          printBoard(gameboard);
        }else{
          plantShip(p2gameboard, p2ship1x, p2ship1y, 2, '1');
          printBoard(p2gameboard);
        }

        cout << endl << endl << endl;

        break;

      }

      //Case 2: User chooses to plant small battleship.
      case 2: {

        //Bool for placing ship 2 is true. 
        placedship2 = true;

        //Ask what direction the user would like to place their ship. 
        cout << "How would you like your ship to be placed?\n\n1) Horizontally\n2) Vertically\n\n";
        cin >> direction;

        cout << endl;

        //Error message.
        while(direction > 2 || direction < 1){
          cout << "Invalid input. PLease try again: ";
          cin >> direction;
        }

        cout << endl << endl;

        //Switch case for direction of small battleship.
        switch(direction){

          //Case 1: User chooses to place small battleship horizontally.
          case 1: {

            //Ask for leftmost coordinate of small battleship. 
            cout << "Input the left coordinate of your ship:\n\nX: ";

            //Put in leftmost coordinate of small battelship.  
            if(i == 0){
              cin >> ship2x[0];
              cout << "Y: ";
              cin >> ship2y[0];
            }else{
              cin >> p2ship2x[0];
              cout << "Y: ";
              cin >> p2ship2y[0];
            }            

            //Assign proper x and y values to the rest of the coordinates of the small battleship based on direction and first coordinate. 
            if(i == 0){
              ship2x[1] = ship2x[0] + 1;
              ship2y[1] = ship2y[0];
              ship2x[2] = ship2x[0] + 2;
              ship2y[2] = ship2y[0];
              cout << "\nship2x[1]: " << ship2x[1];
              cout << "\nship2y[1]: " << ship2y[1];
              cout << "\nship2x[2]: " << ship2x[2];
              cout << "\nship2y[2]: " << ship2y[2];
            }else{
              p2ship2x[1] = p2ship2x[0] + 1;
              p2ship2y[1] = p2ship2y[0];
              p2ship2x[2] = p2ship2x[0] + 2;
              p2ship2y[2] = p2ship2y[0];
            }

            cout << endl << endl;

            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship2x[0] < 1 || ship2x[0] > 8 || ship2y[0] < 1 || ship2y[0] > 10 || checkOverlap(gameboard, ship2x, ship2y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship2x[0];
                cout << "Y: ";
                cin >> ship2y[0];

                ship2x[1] = ship2x[0] + 1;
                ship2y[1] = ship2y[0];
                ship2x[2] = ship2x[0] + 2;
                ship2y[2] = ship2y[0];

                cout << endl << endl;
              }
            }else{
              while(p2ship2x[0] < 1 || p2ship2x[0] > 8 || p2ship2y[0] < 1 || p2ship2y[0] > 10 || checkOverlap(p2gameboard, p2ship2x, p2ship2y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship2x[0];
                cout << "Y: ";
                cin >> p2ship2y[0];

                p2ship2x[1] = p2ship2x[0] + 1;
                p2ship2y[1] = p2ship2y[0];
                p2ship2x[2] = p2ship2x[0] + 2;
                p2ship2y[2] = p2ship2y[0];

                cout << endl << endl;
              }
            }

            break;

          }

          //Case 2: User chooses to place small battleship vertically. 
          case 2: {

            //Ask for top coordinate of small battleship. 
            cout << "Input the top coordinate of your ship:\n\nX: ";

            //Put in top coordinate of small battleship. 
            if(i == 0){
              cin >> ship2x[0];
              cout << "Y: ";
              cin >> ship2y[0];
            }else{
              cin >> p2ship2x[0];
              cout << "Y: ";
              cin >> p2ship2y[0];
            }

            //Assign proper x and y values to the rest of the coordinates of small battleship based on direction and first coordinate. 
            if(i == 0){
              ship2x[1] = ship2x[0];
              ship2y[1] = ship2y[0] + 1;
              ship2x[2] = ship2x[0];
              ship2y[2] = ship2y[0] + 2;
            }else{
              p2ship2x[1] = p2ship2x[0];
              p2ship2y[1] = p2ship2y[0] + 1;
              p2ship2x[2] = p2ship2x[0];
              p2ship2y[2] = p2ship2y[0] + 2;
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship2x[0] < 1 || ship2x[0] > 10 || ship2y[0] < 1 || ship2y[0] > 8 || checkOverlap(gameboard, ship2x, ship2y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship2x[0];
                cout << "Y: ";
                cin >> ship2y[0];

                ship2x[1] = ship2x[0];
                ship2y[1] = ship2y[0] + 1;
                ship2x[2] = ship2x[0];
                ship2y[2] = ship2y[0] + 2;

                cout << endl << endl;
              }
            }else{
              while(p2ship2x[0] < 1 || p2ship2x[0] > 10 || p2ship2y[0] < 1 || p2ship2y[0] > 8 || checkOverlap(p2gameboard, p2ship2x, p2ship2y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship2x[0];
                cout << "Y: ";
                cin >> p2ship2y[0];

                p2ship2x[1] = p2ship2x[0];
                p2ship2y[1] = p2ship2y[0] + 1;
                p2ship2x[2] = p2ship2x[0];
                p2ship2y[2] = p2ship2y[0] + 2;

                cout << endl << endl;
              }
            }

            break;

          }

          default:{
            break;
          }

        }

        //Use function plantship to put the small battleship on the gameboard and print out the board. 
        if(i == 0){
          plantShip(gameboard, ship2x, ship2y, 3, '2');
          printBoard(gameboard);
        }else{
          plantShip(p2gameboard, p2ship2x, p2ship2y, 3, '2');
          printBoard(p2gameboard);
        }
        
        cout << endl << endl << endl;

        break;

      }

      //Case 3: User chooses to plant second small battleship.
      case 3: {

        //Boolean for placing ship 3 is true.
        placedship3 = true;

        //Ask for direction of small battleship.
        cout << "How would you like your ship to be placed?\n\n1) Horizontally\n2) Vertically\n\n";
        cin >> direction;

        cout << endl;

        //Error message.
        while(direction > 2 || direction < 1){
          cout << "Invalid input. PLease try again: ";
          cin >> direction;
        }

        cout << endl << endl;

        //Switch case for the direction of the second small battleship.   
        switch(direction){

          //Case 1: User chooses to place the small battleship horizontally. 
          case 1: {

            //Ask for leftmost coordinate.
            cout << "Input the left coordinate of your ship:\n\nX: ";

            //Enter first coordinate of small battleship.
            if(i == 0){
              cin >> ship3x[0];
              cout << "Y: ";
              cin >> ship3y[0];
            }else{
              cin >> p2ship3x[0];
              cout << "Y: ";
              cin >> p2ship3y[0];
            }

            //Assign x and y values to the rest of. thecoordinates of the small battleship based on the first coordinate and ddirection. 
            if(i == 0){
              ship3x[1] = ship3x[0] + 1;
              ship3y[1] = ship3y[0];
              ship3x[2] = ship3x[0] + 2;
              ship3y[2] = ship3y[0];
            }else{
              p2ship3x[1] = p2ship3x[0] + 1;
              p2ship3y[1] = p2ship3y[0];
              p2ship3x[2] = p2ship3x[0] + 2;
              p2ship3y[2] = p2ship3y[0];
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship3x[0] < 1 || ship3x[0] > 8 || ship3y[0] < 1 || ship3y[0] > 10 || checkOverlap(gameboard, ship3x, ship3y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship3x[0];
                cout << "Y: ";
                cin >> ship3y[0];

                ship3x[1] = ship3x[0] + 1;
                ship3y[1] = ship3y[0];
                ship3x[2] = ship3x[0] + 2;
                ship3y[2] = ship3y[0];

                cout << endl << endl;
              }
            }else{
              while(p2ship3x[0] < 1 || p2ship3x[0] > 8 || p2ship3y[0] < 1 || p2ship3y[0] > 10 || checkOverlap(p2gameboard, p2ship3x, p2ship3y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship3x[0];
                cout << "Y: ";
                cin >> p2ship3y[0];

                p2ship3x[1] = p2ship3x[0] + 1;
                p2ship3y[1] = p2ship3y[0];
                p2ship3x[2] = p2ship3x[0] + 2;
                p2ship3y[2] = p2ship3y[0];

                cout << endl << endl;
              }
            }

            break;

          }

          //Case 2: User chooses to place small battleship vertically. 
          case 2: {

            //Ask for top coordinate of small battleship.
            cout << "Input the top coordinate of your ship:\n\nX: ";

            //Input first coordinate of small battleship. 
            if(i == 0){
              cin >> ship3x[0];
              cout << "Y: ";
              cin >> ship3y[0];
            }else{
              cin >> p2ship3x[0];
              cout << "Y: ";
              cin >> p2ship3y[0];
            }

            //Assign x and y values of the other coordinates of the small battleship based on first coordinate and direction. 
            if(i == 0){
              ship3x[1] = ship3x[0];
              ship3y[1] = ship3y[0] + 1;
              ship3x[2] = ship3x[0];
              ship3y[2] = ship3y[0] + 2;
            }else{
              p2ship3x[1] = p2ship3x[0];
              p2ship3y[1] = p2ship3y[0] + 1;
              p2ship3x[2] = p2ship3x[0];
              p2ship3y[2] = p2ship3y[0] + 2;
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship3x[0] < 1 || ship3x[0] > 10 || ship3y[0] < 1 || ship3y[0] > 8 || checkOverlap(gameboard, ship3x, ship3y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship3x[0];
                cout << "Y: ";
                cin >> ship3y[0];

                ship3x[1] = ship3x[0];
                ship3y[1] = ship3y[0] + 1;
                ship3x[2] = ship3x[0];
                ship3y[2] = ship3y[0] + 2;

                cout << endl << endl;
              }
            }else{
              while(p2ship3x[0] < 1 || p2ship3x[0] > 10 || p2ship3y[0] < 1 || p2ship3y[0] > 8 || checkOverlap(p2gameboard, p2ship3x, p2ship3y, 3) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship3x[0];
                cout << "Y: ";
                cin >> p2ship3y[0];

                p2ship3x[1] = p2ship3x[0];
                p2ship3y[1] = p2ship3y[0] + 1;
                p2ship3x[2] = p2ship3x[0];
                p2ship3y[2] = p2ship3y[0] + 2;

                cout << endl << endl;
              }
            }

            break;

          }

          default:{
            break;
          }

        }

        //Place second small battleship on board and print out board.
        if(i == 0){
          plantShip(gameboard, ship3x, ship3y, 3, '3');
          printBoard(gameboard);
        }else{
          plantShip(p2gameboard, p2ship3x, p2ship3y, 3, '3');
          printBoard(p2gameboard);
        }

        cout << endl << endl << endl;

        break;

      }

      //Case 4: User chooses to plant medium battleship. 
      case 4: {

        //Boolean for placing ship 4 is true.
        placedship4 = true;

        //Ask for direction of medium battleship.
        cout << "How would you like your ship to be placed?\n\n1) Horizontally\n2) Vertically\n\n";
        cin >> direction;

        cout << endl;

        //Error message.
        while(direction > 2 || direction < 1){
          cout << "Invalid input. PLease try again: ";
          cin >> direction;
        }

        cout << endl << endl;

        //Switch case for direction of medium battleship.
        switch(direction){

          //Case 1: User chooses to plant medium battleship horizontally. 
          case 1: {

            //Ask for leftmost coordinate of medium battleship.
            cout << "Input the left coordinate of your ship:\n\nX: ";

            //Input first coordinate of medium battleship.
            if(i == 0){
              cin >> ship4x[0];
              cout << "Y: ";
              cin >> ship4y[0];
            }else{
              cin >> p2ship4x[0];
              cout << "Y: ";
              cin >> p2ship4y[0];
            }

            //Assign x and y values to the rest coordinate on the medium battleship based on first coordinate and direction. 
            if(i == 0){
              ship4x[1] = ship4x[0] + 1;
              ship4y[1] = ship4y[0];
              ship4x[2] = ship4x[0] + 2;
              ship4y[2] = ship4y[0];
              ship4x[3] = ship4x[0] + 3;
              ship4y[3] = ship4y[0];
            }else{
              p2ship4x[1] = p2ship4x[0] + 1;
              p2ship4y[1] = p2ship4y[0];
              p2ship4x[2] = p2ship4x[0] + 2;
              p2ship4y[2] = p2ship4y[0];
              p2ship4x[3] = p2ship4x[0] + 3;
              p2ship4y[3] = p2ship4y[0];
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship4x[0] < 1 || ship4x[0] > 7 || ship4y[0] < 1 || ship4y[0] > 10 || checkOverlap(gameboard, ship4x, ship4y, 4) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship4x[0];
                cout << "Y: ";
                cin >> ship4y[0];

                ship4x[1] = ship4x[0] + 1;
                ship4y[1] = ship4y[0];
                ship4x[2] = ship4x[0] + 2;
                ship4y[2] = ship4y[0];
                ship4x[3] = ship4x[0] + 3;
                ship4y[3] = ship4y[0];

                cout << endl << endl;
              }
            }else{
              while(p2ship4x[0] < 1 || p2ship4x[0] > 7 || p2ship4y[0] < 1 || p2ship4y[0] > 10 || checkOverlap(p2gameboard, p2ship4x, p2ship4y, 4) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship4x[0];
                cout << "Y: ";
                cin >> p2ship4y[0];

                p2ship4x[1] = p2ship4x[0] + 1;
                p2ship4y[1] = p2ship4y[0];
                p2ship4x[2] = p2ship4x[0] + 2;
                p2ship4y[2] = p2ship4y[0];
                p2ship4x[3] = p2ship4x[0] + 3;
                p2ship4y[3] = p2ship4y[0];

                cout << endl << endl;
              }
            }
            
            break;

          }

          //Case 2: User chooses to place medium battleship vertically. 
          case 2: {

            //Ask for top coordinate of medium battleship.
            cout << "Input the top coordinate of your ship:\n\nX: ";

            //Input first coordinate of medium battleship.
            if(i == 0){
              cin >> ship4x[0];
              cout << "Y: ";
              cin >> ship4y[0];
            }else{
              cin >> p2ship4x[0];
              cout << "Y: ";
              cin >> p2ship4y[0];
            }

            //Assign x and y values to the rest of the coordinate on the medium battleship based on direction and first coordinate. 
            if(i == 0){
              ship4x[1] = ship4x[0];
              ship4y[1] = ship4y[0] + 1;
              ship4x[2] = ship4x[0];
              ship4y[2] = ship4y[0] + 2;
              ship4x[3] = ship4x[0];
              ship4y[3] = ship4y[0] + 3;
            }else{
              p2ship4x[1] = p2ship4x[0];
              p2ship4y[1] = p2ship4y[0] + 1;
              p2ship4x[2] = p2ship4x[0];
              p2ship4y[2] = p2ship4y[0] + 2;
              p2ship4x[3] = p2ship4x[0];
              p2ship4y[3] = p2ship4y[0] + 3;
            }
            
            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship4x[0] < 1 || ship4x[0] > 10 || ship4y[0] < 1 || ship4y[0] > 7 || checkOverlap(gameboard, ship4x, ship4y, 4) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship4x[0];
                cout << "Y: ";
                cin >> ship4y[0];

                ship4x[1] = ship4x[0];
                ship4y[1] = ship4y[0] + 1;
                ship4x[2] = ship4x[0];
                ship4y[2] = ship4y[0] + 2;
                ship4x[3] = ship4x[0];
                ship4y[3] = ship4y[0] + 3;

                cout << endl << endl;
              }
            }else{
              while(p2ship4x[0] < 1 || p2ship4x[0] > 10 || p2ship4y[0] < 1 || p2ship4y[0] > 7 || checkOverlap(p2gameboard, p2ship4x, p2ship4y, 4) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship4x[0];
                cout << "Y: ";
                cin >> p2ship4y[0];

                p2ship4x[1] = p2ship4x[0];
                p2ship4y[1] = p2ship4y[0] + 1;
                p2ship4x[2] = p2ship4x[0];
                p2ship4y[2] = p2ship4y[0] + 2;
                p2ship4x[3] = p2ship4x[0];
                p2ship4y[3] = p2ship4y[0] + 3;

                cout << endl << endl;
              }
            }

            break;

          }

          default:{
            break;
          }

        }

        //Place ship on board and print out board.
        if(i == 0){
          plantShip(gameboard, ship4x, ship4y, 4, '4');
          printBoard(gameboard);
        }else{
          plantShip(p2gameboard, p2ship4x, p2ship4y, 4, '4');
          printBoard(p2gameboard);
        }

        cout << endl << endl << endl;

        break;

      }

      //Case 5: User chooses to place large battleship.
      case 5: {

        //Boolean for placing ship 5 is true. 
        placedship5 = true;

        //Ask for direction of large battleship.
        cout << "How would you like your ship to be placed?\n\n1) Horizontally\n2) Vertically\n\n";
        cin >> direction;

        cout << endl;

        //Error message.
        while(direction > 2 || direction < 1){
          cout << "Invalid input. PLease try again: ";
          cin >> direction;
        }

        cout << endl << endl;

        //Switch case for direction of large battleship.
        switch(direction){

          //Case 1: User chooses to place large battleship horizontally.
          case 1: {

            //Ask for leftmost coordinate of large battleship.
            cout << "Input the left coordinate of your ship:\n\nX: ";

            //Input first coordinate. 
            if(i == 0){
              cin >> ship5x[0];
              cout << "Y: ";
              cin >> ship5y[0];
            }else{
              cin >> p2ship5x[0];
              cout << "Y: ";
              cin >> p2ship5y[0];
            }

            //Assign x and y values to the rest of the coordinates on the large battleship based on the first coordinate and direction. 
            if(i == 0){
              ship5x[1] = ship5x[0] + 1;
              ship5y[1] = ship5y[0];
              ship5x[2] = ship5x[0] + 2;
              ship5y[2] = ship5y[0];
              ship5x[3] = ship5x[0] + 3;
              ship5y[3] = ship5y[0];
              ship5x[4] = ship5x[0] + 4;
              ship5y[4] = ship5y[0];
            }else{
              p2ship5x[1] = p2ship5x[0] + 1;
              p2ship5y[1] = p2ship5y[0];
              p2ship5x[2] = p2ship5x[0] + 2;
              p2ship5y[2] = p2ship5y[0];
              p2ship5x[3] = p2ship5x[0] + 3;
              p2ship5y[3] = p2ship5y[0];
              p2ship5x[4] = p2ship5x[0] + 4;
              p2ship5y[4] = p2ship5y[0];
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship5x[0] < 1 || ship5x[0] > 6 || ship5y[0] < 1 || ship5y[0] > 10 || checkOverlap(gameboard, ship5x, ship5y, 5) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship5x[0];
                cout << "Y: ";
                cin >> ship5y[0];

                ship5x[1] = ship5x[0] + 1;
                ship5y[1] = ship5y[0];
                ship5x[2] = ship5x[0] + 2;
                ship5y[2] = ship5y[0];
                ship5x[3] = ship5x[0] + 3;
                ship5y[3] = ship5y[0];
                ship5x[4] = ship5x[0] + 4;
                ship5y[4] = ship5y[0];

                cout << endl << endl;
              }
            }else{
              while(p2ship5x[0] < 1 || p2ship5x[0] > 6 || p2ship5y[0] < 1 || p2ship5y[0] > 10 || checkOverlap(p2gameboard, p2ship5x, p2ship5y, 5) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> p2ship5x[0];
                cout << "Y: ";
                cin >> p2ship5y[0];

                p2ship5x[1] = p2ship5x[0] + 1;
                p2ship5y[1] = p2ship5y[0];
                p2ship5x[2] = p2ship5x[0] + 2;
                p2ship5y[2] = p2ship5y[0];
                p2ship5x[3] = p2ship5x[0] + 3;
                p2ship5y[3] = p2ship5y[0];
                p2ship5x[4] = p2ship5x[0] + 4;
                p2ship5y[4] = p2ship5y[0];

                cout << endl << endl;
              }
            }

            break;

          }

          //Case 2: User chooses to place large battleship vertically.
          case 2: {

            //Ask for top coordinate of large battleship.
            cout << "Input the top coordinate of your ship:\n\nX: ";

            //Input first coordinate of large battleship.
            if(i == 0){
              cin >> ship5x[0];
              cout << "Y: ";
              cin >> ship5y[0];
            }else{
              cin >> p2ship5x[0];
              cout << "Y: ";
              cin >> p2ship5y[0];
            }

            //Assign x and y values to the rest of the coordinates on the large battleship based on direction and first coordinate. 
            if(i == 0){
              ship5x[1] = ship5x[0];
              ship5y[1] = ship5y[0] + 1;
              ship5x[2] = ship5x[0];
              ship5y[2] = ship5y[0] + 2;
              ship5x[3] = ship5x[0];
              ship5y[3] = ship5y[0] + 3;
              ship5x[4] = ship5x[0];
              ship5y[4] = ship5y[0] + 4;
              ship5x[4] = ship5x[0]; 
            }else{
              p2ship5x[1] = p2ship5x[0];
              p2ship5y[1] = p2ship5y[0] + 1;
              p2ship5x[2] = p2ship5x[0];
              p2ship5y[2] = p2ship5y[0] + 2;
              p2ship5x[3] = p2ship5x[0];
              p2ship5y[3] = p2ship5y[0] + 3;
              p2ship5x[4] = p2ship5x[0];
              p2ship5y[4] = p2ship5y[0] + 4;
              p2ship5x[4] = p2ship5x[0]; 
            }

            cout << endl << endl;
            
            //Error message if the user places their ship off the board, or if it overlaps another ship (can be checked used checkOverlap function).
            if(i == 0){
              while(ship5x[0] < 1 || ship5x[0] > 10 || ship5y[0] < 1 || ship5y[0] > 6 || checkOverlap(gameboard, ship5x, ship5y, 5) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship5x[0];
                cout << "Y: ";
                cin >> ship5y[0];

                ship5x[1] = ship5x[0];
                ship5y[1] = ship5y[0] + 1;
                ship5x[2] = ship5x[0];
                ship5y[2] = ship5y[0] + 2;
                ship5x[3] = ship5x[0];
                ship5y[3] = ship5y[0] + 3;
                ship5x[4] = ship5x[0];
                ship5y[4] = ship5y[0] + 4;
                ship5x[4] = ship5x[0]; 

                cout << endl << endl;
              }
            }else{
              while(p2ship5x[0] < 1 || p2ship5x[0] > 10 || p2ship5y[0] < 1 || p2ship5y[0] > 6 || checkOverlap(p2gameboard, p2ship5x, p2ship5y, 5) == 1){
                cout << "Invalid coordinate. Try Again.\n\nX: ";
                cin >> ship5x[0];
                cout << "Y: ";
                cin >> ship5y[0];

                p2ship5x[1] = p2ship5x[0];
                p2ship5y[1] = p2ship5y[0] + 1;
                p2ship5x[2] = p2ship5x[0];
                p2ship5y[2] = p2ship5y[0] + 2;
                p2ship5x[3] = p2ship5x[0];
                p2ship5y[3] = p2ship5y[0] + 3;
                p2ship5x[4] = p2ship5x[0];
                p2ship5y[4] = p2ship5y[0] + 4;
                p2ship5x[4] = p2ship5x[0]; 

                cout << endl << endl;
              }
            }

            break;

          }

          default:{
            break;
          }

        }

        //Place ship on board and print out board. 
        if(i == 0){
          plantShip(gameboard, ship5x, ship5y, 5, '5');
          printBoard(gameboard);
        }else{
          plantShip(p2gameboard, p2ship5x, p2ship5y, 5, '5');
          printBoard(p2gameboard);
        }
        
        cout << endl << endl << endl;

        break;

      }

      default: {
        break;
      }

    }

  }
  }

  //While loop. In this loop players will take turns attacking each other. Loop will repeat until the function checkwin comes back as true, meaning one of the players has won. 
  while(checkWin(gameboard) == 0 && checkWin(p2gameboard) == 0){

    //Print out display that shows attack on enemy board as well as Player 1's board. 
    printBoard(display);
    printBoard(gameboard);

    //Ask for coordinate to attack other player's board.
    cout << "\n\n\nPlayer 1's turn. Guess a coordinate to attack Player 2:\n\nX: ";

    //Input coordinate.
    cin >> guessX;
    cout << "Y: ";
    cin >> guessY;

    cout << endl << endl;

    //Error message if the player enters a number not on the grid or they already guessed. Display is the grid on top of the player's grid which shows the enemy's board but without their ships. It shows where you guessed and what guesses were hits and what guesses were not. 
    while(guessX < 1 || guessX > 10 || guessY < 1 || guessY > 10 || display[guessX - 1][guessY - 1] == 'X' || display[guessX - 1][guessY - 1] == 'M'){
      cout << "Invalid Coordinate or coordinate already guessed. Please try again.\n\nX: ";
      cin >> guessX;
      cout << "Y: ";
      cin >> guessY;
      
      cout << endl << endl;
    }

    //If the player has a ship on the coordinate guessed, mark the board with an X. Otherwise, mark the coordinate guessed with an M. This can be checked using the function checkhit. 
    if(checkHit(p2gameboard, guessX, guessY) == 1){
      cout << "Good job! You hit a ship.\n\n\n";
      p2gameboard[guessX - 1][guessY - 1] = 'X';
      display[guessX - 1][guessY - 1] = 'X';
    }else{
      cout << "There wasn't a ship there.\n\n\n";
      p2gameboard[guessX - 1][guessY - 1] = 'M';
      display[guessX - 1][guessY - 1] = 'M';
    }

    //If player one didn't win, continue to player 2's turn. 
    if(checkWin(p2gameboard) == 1){
      cout << "Congratulations Player 1! You won!" << endl << endl;
    }else{

      //Print out full board.
      printBoard(p2display);
      printBoard(p2gameboard);

      //Ask for coordinate to attack.
      cout << "\n\n\nPlayer 2's turn. Guess a coordinate to attack Player 1:\n\nX: ";

      //Input coordinate.
      cin >> guessX;
      cout << "Y: ";
      cin >> guessY;

      cout << endl << endl;

      //Error message if the player enters a number not on the grid or they already guessed. Display is the grid on top of the player's grid which shows the enemy's board but without their ships. It shows where you guessed and what guesses were hits and what guesses were not. 
      while(guessX < 1 || guessX > 10 || guessY < 1 || guessY > 10 || p2display[guessX - 1][guessY - 1] == 'X' || p2display[guessX - 1][guessY - 1] == 'M'){
        cout << "Invalid Coordinate or coordinate already guessed. Please try again.\n\nX: ";
        cin >> guessX;
        cout << "Y: ";
        cin >> guessY;
      
        cout << endl << endl;
      }

      //If the player has a ship on the coordinate guessed, mark the board with an X. Otherwise, mark the coordinate guessed with an M. This can be checked using the function checkhit. 
      if(checkHit(gameboard, guessX, guessY) == 1){
        cout << "Good job! You hit a ship. Opponent's turn.\n\n\n";
        gameboard[guessX - 1][guessY - 1] = 'X';
        p2display[guessX - 1][guessY - 1] = 'X';
      }else{
        cout << "There wasn't a ship there. Opponent's turn.\n\n\n";
        gameboard[guessX - 1][guessY - 1] = 'M';
        p2display[guessX - 1][guessY - 1] = 'M';
      }

    }

    //If player 2 wins, print out win statement. Else, do nothing and the loop will repeat.
    if(checkWin(gameboard) == 1){
      cout << "Congratulations Player 2! You won!";
    }

  }

}

//Function initializeBoard uses a nested for loop to give each value in the 2d array that is passed on to the function a space. 
void initializeBoard(char a[10][10]){
  for(int y = 0; y < 10; y++){
    for(int x = 0; x < 10; x++){
      a[x][y] = ' ';
    }
  }
}

//Function printBoard prints out the board that is passed on to the function using a nested for loop, dashes, escape sequences, and lines. 
void printBoard(char a[10][10]){
  cout << "\t\t---------------------------------------------------------------------------------\n";
  for(int y = 0; y < 10; y++){
    for(int z = 0; z < 3; z++){
      if(z == 1){
        cout << "\t" << y + 1 << "\t";
      }else{
        cout << "\t\t";
      }
      for(int x = 0; x < 10; x++){
        if(z == 1){
          cout << "|\t" << a[x][y] << "\t";
        }else{
        cout << "|\t \t";
        }
      }
      cout << "|\n";
    }
    if(y == 9){
      cout << "\t\t---------------------------------------------------------------------------------" << endl;
    }else{
      cout << "\t\t|-------------------------------------------------------------------------------|" << endl;
    }
  }
  cout << " \t\t\t1\t \t2\t \t3\t \t4\t \t5\t \t6\t \t7\t \t8\t \t9\t\t10\t" << endl;
}

//Function plantShip uses a for loop and the x and y arrays of the ship to put the ship on the game board. 
void plantShip(char a[10][10], int b[], int c[], int d, char e){
  for(int i = 0; i < d; i++){
    a[b[i] - 1][c[i] - 1] = e;
  }
}

//Function checkOverlap checks if the ship passed on to the function (using the ships x and y arrays) overlaps any other ships on the gameboard.
bool checkOverlap(char a[10][10], int b[], int c[], int d){

  bool checkover;

  for(int i = 0; i < d; i++){
    if(a[b[i] - 1][c[i] - 1] == '1' || a[b[i] - 1][c[i] - 1] == '2' || a[b[i] - 1][c[i] - 1] == '3' || a[b[i] - 1][c[i] - 1] == '4' || a[b[i] - 1][c[i] - 1] == '5'){
      checkover = true;
      i = d;
    }else{
      checkover = false;
    }
  }

  return checkover;

}

//Function checkwin checks if a player has won by checking the passed on gameboard if it has any characters in the array which represent ships. If it does, it adds one to the counter. If the counter is not 0, that means that the gameboard still has parts of a ship on it, and the player has not won yet. 
bool checkWin(char a[10][10]){

  int counter = 0;

  for(int y = 0; y < 10; y++){

    for(int x = 0; x < 10; x++){

      if(a[x][y] == '1' || a[x][y] == '2' || a[x][y] == '3' || a[x][y] == '4' || a[x][y] == '5'){
        counter += 1;
      }

    }

  }

  if(counter == 0){
    return true;
  }else{
    return false;
  }

}

//Function checkHit uses the gameboard being attacked, and the x and y value guessed to see if the coordinate has hit an enemy ship or not. If the guess is correct and hits a ship, function will return true.
bool checkHit(char a[10][10], int b, int c){

  if(a[b - 1][c - 1] == '1' || a[b - 1][c - 1] == '2' || a[b - 1][c - 1] == '3' || a[b - 1][c - 1] == '4' || a[b - 1][c - 1] == '5'){
    return true;
  }else{
    return false; 
  }

}