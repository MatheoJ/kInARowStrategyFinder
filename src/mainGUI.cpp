#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileGenerator.h"

using namespace sf;


const int WIN_WIDTH = 600;
const int NB_SQUARE_ROW = 5;
const int SIZE_SQUARE =WIN_WIDTH/NB_SQUARE_ROW;

const int NB_SQUAR_COLUMN = 4;
const int WIN_HEIGHT = SIZE_SQUARE*NB_SQUAR_COLUMN;


void InputHandler(Event& event, RenderWindow& window,vector<Tile>& tVect,int& numPage,int& numPageMax,vector<sf::RectangleShape> & shapeTile );
void drawTile(RenderWindow& window,Tile tile, int x, int y, int sizeForTile,vector<sf::RectangleShape> & shapeTile );
void drawLine(RenderWindow& window, int sizeSquare, vector<sf::RectangleShape> & shapeLine );
void loadFont();


sf::Color colBack(254, 250, 224);
sf::Color colTile(250, 237, 205);
sf::Color colLine(233, 237, 201);
sf::Color colText(204, 213, 174);
sf::Color colEdge(212, 163, 115);

sf::Font font;


int main()
{
    RenderWindow window(VideoMode(WIN_WIDTH , WIN_HEIGHT+30), "Tile viewer");

    TileGenerator tg;
    vector<char> vect;
    tg.generateBoundWord(6, vect);
    tg.generateTile();
    vector<Tile> tVect = tg.getTileVect();

    vector<sf::RectangleShape> shapeTile;
    vector<sf::RectangleShape> shapeLine;

    drawLine(window, SIZE_SQUARE,shapeLine);
    for (int i=0; i<NB_SQUAR_COLUMN;i++){
        for(int j =0; j<NB_SQUARE_ROW; j++){
            drawTile(window, tVect[i*NB_SQUARE_ROW+j],j*SIZE_SQUARE,i*SIZE_SQUARE,SIZE_SQUARE,shapeTile);
        }
    }

    int numPage = 0;
    int numPageMax = tVect.size()/(NB_SQUARE_ROW*NB_SQUAR_COLUMN);

    
    sf::Text text; 
    loadFont();   
    text.setFont(font);
    text.setCharacterSize(24);
    //text.setStyle(sf::Text::Bold);
    text.setFillColor(colText);
    text.setPosition(0,WIN_HEIGHT);


   


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            //input gestion or event 
            InputHandler(event, window, tVect, numPage, numPageMax,shapeTile);
        }

        window.clear(colBack);

        for(sf::RectangleShape s: shapeLine ){
            window.draw(s);
        }
        
        for(sf::RectangleShape s: shapeTile ){
            window.draw(s);
        }

        text.setString("Page "+std::to_string(numPage)+"/"+std::to_string(numPageMax));
        window.draw(text);
        
        window.display();
    }

    return 0;
}


void InputHandler(Event& event, RenderWindow& window,vector<Tile>& tVect,int& numPage,int& numPageMax,vector<sf::RectangleShape> & shapeTile){

    static int lastTileClicked =-1;

    if (event.type == Event::Closed)
                window.close();
                
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        int x=localPosition.x/SIZE_SQUARE;
        int y=localPosition.y/SIZE_SQUARE;   
        int numTilePerPage= NB_SQUARE_ROW*NB_SQUAR_COLUMN;    
        int num = y*NB_SQUARE_ROW+x+numTilePerPage*numPage;
        if (num != lastTileClicked && num<<tVect.size()){
            std::cout<<tVect[num];
            std::cout<<"x = "<<x<< " y= "<<y<<endl;
            lastTileClicked = num;
        }       
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(numPage!=0){
            numPage--;
            shapeTile.clear();
            int numTilePerPage= NB_SQUARE_ROW*NB_SQUAR_COLUMN;
            for (int i=0; i<NB_SQUAR_COLUMN;i++){
                for(int j =0; j<NB_SQUARE_ROW; j++){
                    drawTile(window, tVect[i*NB_SQUARE_ROW+j+numTilePerPage*numPage],j*SIZE_SQUARE,i*SIZE_SQUARE,SIZE_SQUARE,shapeTile);
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(numPage!=numPageMax){
            shapeTile.clear();
            numPage++;
            int numTilePerPage= NB_SQUARE_ROW*NB_SQUAR_COLUMN;
            for (int i=0; i<NB_SQUAR_COLUMN;i++){
                for(int j =0; j<NB_SQUARE_ROW; j++){
                    int index =i*NB_SQUARE_ROW+j+numTilePerPage*numPage; 
                    if(index<tVect.size()){
                        drawTile(window, tVect[index],j*SIZE_SQUARE,i*SIZE_SQUARE,SIZE_SQUARE,shapeTile);
                    }                    
                }
            }
        }
    }
}

void drawLine(RenderWindow& window, int sizeSquare, vector<sf::RectangleShape> & shapeLine){
    
    for ( int i =1 ; i<WIN_WIDTH/sizeSquare; i++){
        sf::RectangleShape line(sf::Vector2f(WIN_HEIGHT, 3));
        line.setPosition(i*sizeSquare,0);
        line.rotate(90);
        line.setFillColor(colLine);
        shapeLine.push_back(line);
    }

    for ( int i =1 ; i<WIN_HEIGHT/sizeSquare; i++){
        sf::RectangleShape line(sf::Vector2f(WIN_WIDTH, 3));
        line.setPosition(0,i*sizeSquare);
        line.setFillColor(colLine);
        shapeLine.push_back(line);
    }
}

void drawTile(RenderWindow& window,Tile tile, int x, int y, int sizeForTile, vector<sf::RectangleShape> & shapeTile ){
    int sizeUnit = (sizeForTile-20)/tile.getSize();
    int tileS = tile.getSize();
    Unit** shape = tile.getBasicShape(); 

    //Leave a margin;
    x+=10;
    y+=10;
    for(int i =0; i<tileS; i++){
        for (int  j =0; j<tileS; j++){
            if(shape[i][j].getTileNumber()!=-1){
                sf::RectangleShape u(sf::Vector2f(sizeUnit-1, sizeUnit-1));
                u.setPosition(j*sizeUnit+x,i*sizeUnit+y);
                u.setFillColor(colTile);
                u.setOutlineColor(colEdge);
                u.setOutlineThickness(1);
                shapeTile.push_back(u);
            }
        }
    }
}


//Load font
void loadFont(){
    if(!font.loadFromFile("res/poppins.ttf")){
        std::cout<<"error load font";
    }
}