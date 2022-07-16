#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

//Stating an enumeration for direction
enum eDir{STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall {
    private:
        int x,y;
        int origX, origY;
        eDir direction;

    public:
        //Constructor for the class
        cBall(int posX, int posY) {
            origX = posX;
            origY = posY;
            x = posX; y = posY;
            direction = STOP;
        }
        //Reset function
        void Reset() {
            x = origX; y = origY;
            direction = STOP;
        }
        //Function to change direction
        void changeDir(eDir d) {
            direction = d;
        }
        //Function to generate a random direction
        void randomDir() {
            //This way we could set the direction from 1-6
            srand(time(0)*x*y);
            direction = (eDir)((rand()%6) + 1);
        }
        //Functions to get current x, y and direction
        inline int getX() {return x;}
        inline int getY() {return y;}
        inline eDir getDir() {return direction;}

        //Function to move the ball
        void moveBall() {
            switch(direction) {
                case STOP:
                    break;
                case LEFT:
                    x--;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UPRIGHT:
                    x++; y++;
                    break;
                case UPLEFT:
                    x--; y++;
                    break;
                case DOWNLEFT:
                    x--; y--;
                    break;
                case DOWNRIGHT:
                    x++; y--;
                    break;
            }
        }

        //Friend function
        friend ostream & operator << (ostream & o, cBall c) {
            o << "Ball [" << c.x << "." << c.y << "][" << c.direction << "]" << endl;
            return o;
        }
};

//Creating the paddle class, similar to the ball class
class cPaddle {
    private:
        int x,y;
        int origX, origY;

    public:
        cPaddle() {
            x = y = 0;
        }

        cPaddle(int posX, int posY) : cPaddle() {
            origX = posX;
            origY = posY;
            x = posX;
            y = posY;
        }

        inline void Reset() {x = origX; y = origY;}
        inline int getX(){return x;}
        inline int getY() {return y;}
        inline void movePaddleUP() {y++;}
        inline void movePaddleDOWN() {y--;}

        //Friend function
        friend ostream & operator << (ostream & o, cPaddle p) {
            o << "Paddle [" << p.x << "." << p.y << "]" << endl;
            return o;
        }
};

//Creating a game manager class to control everything about the other classes
//The game manager class also has the draw function, which deals with the UI
class cGameMngr {
    private:
        //The game manager would manage the width and height of the window
        int width, height;
        //It would also keep track of the scores of both players
        int score1, score2;
        //Here we set the controls for the game, ie the characters that would count as inputs
        char up1,down1,up2, down2;
        //And also a boolean variable to quit the game
        bool quit;
        //We set some pointers for the objects we use
        cBall * ball;
        cPaddle *player1;
        cPaddle *player2;

    public:
        //Setting the default constructor, the basic values that we'll need
        cGameMngr(int w, int h) {
            //Getting another RNG seed
            srand(time(NULL));
            quit = false;
            //Setting controls and default scores
            up1 = 'w'; down1 = 's';
            up2 = 'i'; down2 = 'k';
            score1 = score2 = 0;
            width = w;
            height = h;

            //Creating a ball and placing it in middle
            ball = new cBall(w/2, h/2);
            //Creating paddles, the Y position is mentioned considering the paddle height.
            player1 = new cPaddle(2, h/2 - 3);
            player2 = new cPaddle(w - 3, h/2 - 3);
        }

        //Setting the default constructor which frees up the memory of our pointers
        ~cGameMngr() {
            delete ball, player1, player2;
        }

        //Making the function to manage (increase) the score
        void scoreUP(cPaddle * player) {
            if(player == player1) {
                score1++;
            } else if(player == player2) {
                score2++;
            }
        }

        //The Draw function. We're currently using the simple console window, no fancy graphics.
        void Draw() {
            //clearing screen. 'cls' for windows, 'clear' for linux
            system("cls");
            //This is the top wall
            for(int i = 0; i < width + 1; i++) {
                cout << "\xB1";
            }
            cout << endl;
            //Draw other things
            for(int i = 0; i < height; i++) {
                
                for(int j = 0; j < width + 1; j++) {
                    
                    //Getting positions of all our elements
                    int ballx = ball->getX();
                    int bally = ball->getY();
                    int player1x = player1->getX();
                    int player2x = player2->getX();
                    int player1y = player1->getY();
                    int player2y = player2->getY();

                    //Drawing a character for the left wall
                    if(j == 0) {
                        cout << "\xB1";
                    }

                    //Drawing the ball
                    if(ballx == j && bally == i) {
                        cout << "\xE9";
                    }

                    //Drawing player 1 paddle (We do it on multiple lines for paddle height)
                    if(player1x == j && player1y==i) {
                        cout << "\xDB";
                    } else if(player1x == j && player1y==i-1) {
                        cout << "\xDB";
                    } else if(player1x == j && player1y==i+1) {
                        cout << "\xDB";
                    } else if(player1x == j && player1y==i-2) {
                        cout << "\xDB";
                    } else if(player1x == j && player1y==i+2) {
                        cout << "\xDB";
                    }

                    //Drawing player 2 paddle (We do it on multiple lines for paddle height)
                    else if(player2x == j && player2y == i) {
                        cout << "\xDB";
                    } else if(player2x == j && player2y==i-1) {
                        cout << "\xDB";
                    } else if(player2x == j && player2y==i+1) {
                        cout << "\xDB";
                    } else if(player2x == j && player2y==i-2) {
                        cout << "\xDB";
                    } else if(player2x == j && player2y==i+2) {
                        cout << "\xDB";
                    }

                    //Drawing the right wall, then going on a new line
                    if(j == width - 1) {
                        cout << "\xB1" << endl;
                    }
                    //Drawing a blank if there's nothing
                    else {
                        cout << " ";
                    }
                }
            }
            //This is the bottom wall
            for(int i = 0; i < width + 2; i++) {
                cout << "\xB1";
            }
        }

        //The input function to deal with user input
        void Input() {
            //Moves the ball, ie update the next frame co-ordinates
            ball->moveBall();

            //Getting positions of all our elements
            int ballx = ball->getX();
            int bally = ball->getY();
            int player1x = player1->getX();
            int player2x = player2->getX();
            int player1y = player1->getY();
            int player2y = player2->getY();

            //Non-blocking getchar function, to take the user input, triggers if keyboard is hit (kbhit)
            if(_kbhit) {
                char current = _getch();

                //updating co-ordinates according to input
                if(current == up1) {
                    if(player1y - 2 > 0) {
                        player1 -> movePaddleUP();
                    }
                } else if (current == up2) {
                    if(player2y - 2 > 0) {
                        player2 -> movePaddleUP();
                    }
                }
                if(current == down1) {
                    if(player1y + 2 > 0) {
                        player1 -> movePaddleDOWN();
                    }
                } else if (current == down2) {
                    if(player2y + 2 > 0) {
                        player2 -> movePaddleDOWN();
                    }
                } else if(current == 'q') {
                    quit = true;
                }

                //Getting a random direction if the ball is stopped
                if(ball->getDir() == STOP){
                    ball->randomDir();
                }
            }

        }

        //The logic function taking care of scores and collision
        void Logic() {
            
            //Getting positions of all our elements
            int ballx = ball->getX();
            int bally = ball->getY();
            int player1x = player1->getX();
            int player2x = player2->getX();
            int player1y = player1->getY();
            int player2y = player2->getY();

            //Left paddle bounce
            if(ballx == player1x + 1) {
                for(int i = -2; i <=2; i++){
                    if(bally == player1y + i){
                        //Changing direction by where it hits on the paddle
                        if(i < 0){
                            ball->changeDir((eDir)5);
                        } else if(i > 0) {
                            ball->changeDir((eDir)6);
                        } else {
                            ball -> changeDir((eDir)4);
                        }
                    }
                }
            }

            //Right paddle bounce
            if(ballx == player2x - 1) {
                for(int i = -2; i <=2; i++){
                    if(bally == player2y + i){
                        //Changing direction by where it hits on the paddle
                        if(i < 0){
                            ball->changeDir((eDir)2);
                        } else if(i > 0) {
                            ball->changeDir((eDir)3);
                        } else {
                            ball -> changeDir((eDir)1);
                        }
                    }
                }
            }

            //Vertical wall hit reflections
            if(bally == height - 1 || bally == 0) {
                switch (ball->getDir()){
                    case DOWNLEFT:
                        ball->changeDir(UPLEFT);
                        break;
                    case DOWNRIGHT:
                        ball->changeDir(UPRIGHT);
                        break;
                    case UPRIGHT:
                        ball->changeDir(DOWNRIGHT);
                        break;
                    case UPLEFT:
                        ball->changeDir(DOWNLEFT);
                        break;
                }
            }

            //Horizontal wall hits, ie scoring
            if(ballx == width-1) {
                scoreUP(player1);
            } else if (ballx == 0) {
                scoreUP(player2);
            }
        }
        
        //This is the game execution function
        void Run() {
            while(!quit) {
                Draw();
                Input();
                Logic();
            }
        }
};


int main() {
    //Initializing the game manager
    cGameMngr c(50,20);
    c.Run();
    return 0;
}