#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "TileGenerator.h"
#include "TileAnalyzer.h"

using namespace sf;


const int WIN_WIDTH = 600;
const int NB_SQUARE_ROW = 5;
const int SIZE_SQUARE =WIN_WIDTH/NB_SQUARE_ROW;

const int NB_SQUAR_COLUMN = 4;
const int WIN_HEIGHT = SIZE_SQUARE*NB_SQUAR_COLUMN;

const int WIN_OPTION_SIZE=220;
const int SIZE_SQUARE_OPTION = 200;



bool InputHandler(Event& event, RenderWindow& window,RenderWindow& window2,vector<Tile>& tVect,int& numPage,int& numPageMax,vector<sf::RectangleShape> & shapeTile,vector<sf::RectangleShape>& shapePlaning,bool& isTileSelected,sf::RectangleShape& selctedTile  );
void drawTile(RenderWindow& window,Tile tile, int x, int y, int sizeForTile,vector<sf::RectangleShape> & shapeTile );
void drawLine(RenderWindow& window, int sizeSquare, vector<sf::RectangleShape> & shapeLine );
void drawTilingShape(Tile tile, int sizeForTile, vector<sf::RectangleShape> & shapePlaning);
void loadFont();


sf::Color colBack(254, 250, 224);
sf::Color colTile(250, 237, 205);
sf::Color colLine(233, 237, 201);
sf::Color colSelect(233, 237, 201,150);
sf::Color colText(204, 213, 174);
sf::Color colEdge(212, 163, 115);

sf::Font font;


int main(int argc, char** argv)
{
    RenderWindow window(VideoMode(WIN_WIDTH , WIN_HEIGHT+30), "Tile viewer");
    RenderWindow window2(VideoMode(WIN_OPTION_SIZE , WIN_OPTION_SIZE), "More option");

    TileGenerator tg;
    TileAnalyzer ta(7);
    vector<char> vect;
    vector<Tile> tVect;
    int minHPer,maxHPer;
    
     int numPage = 0;
    

    vector<sf::RectangleShape> shapeTile;
    vector<sf::RectangleShape> shapePlaning;
    vector<sf::RectangleShape> shapeLine;

    bool isTileSelected = false;
    sf::RectangleShape selectedTile(sf::Vector2f(SIZE_SQUARE, SIZE_SQUARE));
    selectedTile.setFillColor(colSelect);

    if(argc>1){
        
        if(strcmp(argv[1], "-a") == 0){
            minHPer=5;
            maxHPer= 7;
            if(argc==3){
                minHPer=atoi(argv[2]);
                maxHPer= minHPer;
            }
            tg.generateBoundWord(minHPer,maxHPer, vect);
            tg.generateTile();
            tg.generateTilingShape(7);
            ta.analyzeTileVect(tg.getTileVect());
            for(TileAlignment& tal: ta.getVectTileAlignment()){
                tVect.push_back(*(tal.getTile()));
            }
        }
        else if(strcmp(argv[1], "-p") == 0 && argc==4){            
            minHPer=atoi(argv[2]);
            maxHPer= minHPer;

            int  id = atoi(argv[3]);               
            
            tg.generateBoundWord(minHPer,maxHPer, vect);
            tg.generateTile();
            tg.generateTilingShape(7);
            ta.analyzeTileVect(tg.getTileVect());
            for(TileAlignment& tal: ta.getVectTileAlignment()){
                tVect.push_back(*(tal.getTile()));
            }
            int i=0;
            for(; i< tVect.size(); i++){
                if(tVect[i].getId()==id){
                    break;
                }
            }

            int numTilePerPage= NB_SQUARE_ROW*NB_SQUAR_COLUMN;
            numPage = i/numTilePerPage;
            for (int i=0; i<NB_SQUAR_COLUMN;i++){
                for(int j =0; j<NB_SQUARE_ROW; j++){
                    drawTile(window, tVect[i*NB_SQUARE_ROW+j+numTilePerPage*numPage],j*SIZE_SQUARE,i*SIZE_SQUARE,SIZE_SQUARE,shapeTile);
                }
            }

            std::cout<<tVect[i];

            int y = (i-numPage*numTilePerPage)/NB_SQUARE_ROW;
            int x = (i-numPage*numTilePerPage)%NB_SQUARE_ROW;

            
            drawTilingShape(tVect[i], SIZE_SQUARE_OPTION, shapePlaning);
            selectedTile.setPosition(x*SIZE_SQUARE,y*SIZE_SQUARE);
            isTileSelected = true;



        }
        else{
            minHPer=atoi(argv[1]);
            maxHPer= minHPer;
            tg.generateBoundWord(minHPer,maxHPer, vect);
            tg.generateTile();
            tVect = tg.getTileVect();
        }
        
    }
    else{
        tg.generateBoundWord(5,7, vect);
        tg.generateTile();
        tVect = tg.getTileVect();
    }

    int numPageMax = tVect.size()/(NB_SQUARE_ROW*NB_SQUAR_COLUMN);
    int numTilePerPage= NB_SQUARE_ROW*NB_SQUAR_COLUMN;

    drawLine(window, SIZE_SQUARE,shapeLine);
    for (int i=0; i<NB_SQUAR_COLUMN;i++){
        for(int j =0; j<NB_SQUARE_ROW; j++){
            drawTile(window, tVect[i*NB_SQUARE_ROW+j+numTilePerPage*numPage],j*SIZE_SQUARE,i*SIZE_SQUARE,SIZE_SQUARE,shapeTile);
        }
    }

   

    
    sf::Text text; 
    loadFont();   
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(colText);
    text.setPosition(0,WIN_HEIGHT);


  


    while (window.isOpen())
    {
        Event event;
        while (window.waitEvent(event))
        {
            
            if (event.type == Event::Closed){
                break;
            }

            //input gestion or event 
            if(!InputHandler(event, window, window2, tVect, numPage, numPageMax,shapeTile,shapePlaning,isTileSelected,selectedTile))
                break;
            window.clear(colBack);
            window2.clear(colBack);

            for(sf::RectangleShape s: shapeLine ){
                window.draw(s);
            }
            
            for(sf::RectangleShape s: shapeTile ){
                window.draw(s);
            }

            for(sf::RectangleShape s: shapePlaning ){            
                window2.draw(s);
            }

            if(isTileSelected){
                window.draw(selectedTile);
            }
            //window2.draw(shape);


            text.setString("Page "+std::to_string(numPage)+"/"+std::to_string(numPageMax));
            window.draw(text);
            
            window2.display();
            window.display();
        
        }
        window.close();
        
        
    }

    return 0;
}


bool InputHandler(Event& event, RenderWindow& window, RenderWindow& window2,vector<Tile>& tVect,int& numPage,int& numPageMax,vector<sf::RectangleShape> & shapeTile, vector<sf::RectangleShape>& shapePlaning,bool& isTileSelected,sf::RectangleShape& selectedTile ){

    static int lastTileClicked =-1;

    if (event.type == Event::Closed){
        window.close();
        return false;
    }
                
                
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        int x=localPosition.x/SIZE_SQUARE;
        int y=localPosition.y/SIZE_SQUARE;   
        int numTilePerPage= NB_SQUARE_ROW*NB_SQUAR_COLUMN;    
        int num = y*NB_SQUARE_ROW+x+numTilePerPage*numPage;
        if (num != lastTileClicked && num<(int)tVect.size()){
            shapePlaning.clear();
            std::cout<<tVect[num];
            lastTileClicked = num;
            
            drawTilingShape(tVect[num], SIZE_SQUARE_OPTION, shapePlaning);
            selectedTile.setPosition(x*SIZE_SQUARE,y*SIZE_SQUARE);
            isTileSelected = true;
            
            
        }       
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
            isTileSelected = false;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(numPage!=numPageMax){
            shapeTile.clear();
            numPage++;
            int numTilePerPage= NB_SQUARE_ROW*NB_SQUAR_COLUMN;
            for (int i=0; i<NB_SQUAR_COLUMN;i++){
                for(int j =0; j<NB_SQUARE_ROW; j++){
                    int index =i*NB_SQUARE_ROW+j+numTilePerPage*numPage; 
                    if(index<(int)tVect.size()){
                        drawTile(window, tVect[index],j*SIZE_SQUARE,i*SIZE_SQUARE,SIZE_SQUARE,shapeTile);
                    }                    
                }
            }
            isTileSelected = false;
        }
    }

    return true;
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

void drawTilingShape(Tile tile, int sizeForTile, vector<sf::RectangleShape> & shapePlaning){
    
    int numTile;
     

    map<int, sf::Color> colorOfTile;
    colorOfTile[0]=sf::Color::Green;
    sf::Color color;

    tile.buildPlanningShape(7);

    Unit** shape = tile.getPlaningShape();
    int size = tile.getPlaningShapeSize();
    int sizeUnit = sizeForTile/size;


    for(int i =0; i<size; i++){
        for (int  j =0; j<size; j++){
            numTile = shape[i][j].getTileNumber();
            if(numTile!=-1){
               if (colorOfTile.count(numTile)){
                    color = colorOfTile[numTile];
                }
                else{
                    colorOfTile[numTile]=sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
                    color = colorOfTile[numTile];
                } 
                sf::RectangleShape u(sf::Vector2f(sizeUnit-1, sizeUnit-1));
                u.setPosition(j*sizeUnit+10,i*sizeUnit+10);
                u.setFillColor(color);                
                if(numTile==0){
                    u.setOutlineColor(sf::Color::Black);
                    u.setOutlineThickness(3);
                }
                else{
                    u.setOutlineColor(colEdge);
                    u.setOutlineThickness(1);
                }                
                shapePlaning.push_back(u);
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