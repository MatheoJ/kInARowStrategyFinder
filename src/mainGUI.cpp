#include <SFML/Graphics.hpp>
#include "TileGenerator.h"

using namespace sf;

const int WIN_SIZE = 800;
const int WIN_WIDTH = WIN_SIZE;
const int NB_SQUARE_ROW = 8;
const int SIZE_SQUARE =WIN_WIDTH/NB_SQUARE_ROW;

const int WIN_HEIGHT = SIZE_SQUARE*8;
const int NB_SQUAR_COLUMN = (WIN_HEIGHT)/(WIN_WIDTH/NB_SQUARE_ROW);


void InputHandler(Event event, RenderWindow& window);
void drawTile(RenderWindow& window,Tile tile, int x, int y, int sizeForTile );
void drawLine(RenderWindow& window, int sizeSquare);

int main()
{
    RenderWindow window(VideoMode(WIN_WIDTH , WIN_HEIGHT), "Tile viewer");
    /* CircleShape shape(100.f);
    shape.setFillColor(Color::Green); */

    TileGenerator tg;
    vector<char> vect;
    tg.generateBoundWord(6, vect);
    tg.generateTile();
    vector<Tile> tVcet = tg.getTileVect();
   


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            //input gestion or event 
            InputHandler(event, window);
        }

        window.clear();
        //window.draw(shape);
        drawLine(window, SIZE_SQUARE);
        for (int i=0; i<NB_SQUAR_COLUMN;i++){
            for(int j =0; j<NB_SQUARE_ROW; j++){
                drawTile(window, tVcet[i*NB_SQUARE_ROW+j],j*SIZE_SQUARE,i*SIZE_SQUARE,SIZE_SQUARE);
            }
        }
        window.display();
    }

    return 0;
}


void InputHandler(Event event, RenderWindow& window){
    if (event.type == Event::Closed)
                window.close();


}

void drawLine(RenderWindow& window, int sizeSquare){
    
    
    for ( int i =0 ; i<WIN_WIDTH/sizeSquare; i++){
        sf::RectangleShape line(sf::Vector2f(WIN_WIDTH, 3));
        line.setPosition(i*sizeSquare,0);
        line.rotate(90);
        window.draw(line);
    }

    for ( int i =0 ; i<WIN_HEIGHT/sizeSquare; i++){
        sf::RectangleShape line(sf::Vector2f(WIN_HEIGHT, 3));
        line.setPosition(0,i*sizeSquare);
        window.draw(line);
    }

    

}

void drawTile(RenderWindow& window,Tile tile, int x, int y, int sizeForTile ){
    int sizeUnit = (sizeForTile-20)/tile.getSize();
    int tileS = tile.getSize();
    Unit** shape = tile.getBasicShape(); 

    //Leave a margin;
    x+=10;
    y+=10;
    for(int i =0; i<tileS; i++){
        for (int  j =0; j<tileS; j++){
            if(shape[i][j].getTileNumber()!=-1){
                sf::RectangleShape u(sf::Vector2f(sizeUnit, sizeUnit));
                u.setPosition(j*sizeUnit+x,i*sizeUnit+y);
                u.setOutlineColor(Color::Black);
                u.setOutlineThickness(1);
                window.draw(u);
            }
        }
    }
}