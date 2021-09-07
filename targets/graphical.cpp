#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <memory>

#include "game.hpp"

#define BOARD_GRAPH_SIZE    800 // Must be divisible by BOARD_SIZE
#define RECTANGLE_SIZE      (BOARD_GRAPH_SIZE / BOARD_SIZE)
#define PIECE_SIZE          (RECTANGLE_SIZE * 0.40f)
#define PIECE_OFFSET        ((RECTANGLE_SIZE / 2.0f) - PIECE_SIZE)

struct PieceData
{
    sf::CircleShape shape;
    int x;
    int y;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_GRAPH_SIZE, BOARD_GRAPH_SIZE), "Checkers MiniMax", sf::Style::Close);

    // Board
    sf::RectangleShape blackRectangle(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE));
    blackRectangle.setFillColor(sf::Color(59, 46, 15));
    sf::RectangleShape whiteRectangle(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE));
    whiteRectangle.setFillColor(sf::Color(120, 98, 47));
    
    auto solver = std::make_unique<MiniMaxAB>(9);
    Game game(solver.get(), GameType::CPU_VS_PLAYER);

    std::vector<PieceData> pieces;
    pieces.reserve(game.getBoard().aliveBlacks() + game.getBoard().aliveReds());

    bool updatePieces = true;
    bool movePiece = false;
    std::vector<int> eats;
    PieceData* pieceToMove = nullptr;
    int lastEatX = -1;
    int lastEatY = -1;

    while (window.isOpen())
    {
        // Process events
        sf::Event e;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        while (window.pollEvent(e))
        {
            // Close window: exit
            if(e.type == sf::Event::Closed)
                window.close();
            // Drag pieces
            if(e.type == sf::Event::MouseButtonPressed)
            {
                for(auto& p : pieces)
                {
                    if(p.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        pieceToMove = &p;
                        movePiece = true;
                        break;
                    }
                }
            }
            if(e.type == sf::Event::MouseButtonReleased)
            {
                if(movePiece)
                {
                    int x = mousePos.x / RECTANGLE_SIZE;
                    int y = mousePos.y / RECTANGLE_SIZE;
                    
                    // check if something was eaten
                    int compx = pieceToMove->x;
                    int compy = pieceToMove->y;
                    if(lastEatX >= 0 && lastEatY >= 0)
                    {
                        compx = lastEatX;
                        compy = lastEatY;
                    }
                    int disx = std::abs(x - compx);
                    int disy = std::abs(y - compy);
                    if(disx == 2 && disy == 2)
                    {
                        int eatx = (x + compx) / 2;
                        int eaty = (y + compy) / 2;
                        eats.push_back(Board::locationToIndex(eatx, eaty));
                    }

                    switch(game.tryMove(pieceToMove->x, pieceToMove->y, x, y, eats))
                    {
                        case MoveLegality::LEGAL:
                            updatePieces = true;
                            eats.clear();
                            lastEatX = -1;
                            lastEatY = -1;
                            break;
                        case MoveLegality::PARTIAL:
                            pieceToMove->shape.setPosition(x * RECTANGLE_SIZE + PIECE_OFFSET, y * RECTANGLE_SIZE + PIECE_OFFSET);
                            lastEatX = x;
                            lastEatY = y;
                            break;
                        case MoveLegality::ILLEGAL: // Fallthrough
                        case MoveLegality::NOTHING:
                            eats.clear();
                            pieceToMove->shape.setPosition(pieceToMove->x * RECTANGLE_SIZE + PIECE_OFFSET, pieceToMove->y * RECTANGLE_SIZE + PIECE_OFFSET);
                            lastEatX = -1;
                            lastEatY = -1;
                            break;
                    }

                }
                movePiece = false;
                pieceToMove = nullptr;
            }
        }

        // Move animation
        if(movePiece)
        {
            pieceToMove->shape.setPosition(mousePos.x - PIECE_SIZE, mousePos.y - PIECE_SIZE);
        }
        

        if(updatePieces)
        {
            updatePieces = false;
            pieces.clear();
            game.nextTurn();
            const Board b = game.getBoard();
            std::cout << b;
            for(int x = 0; x < BOARD_SIZE; x++)
            {
                for(int y = 0; y < BOARD_SIZE; y++)
                {
                    uint8_t piece = b.getLocation(x, y);
                    if(piece & IS_PIECE)
                    {
                        PieceData pd = {sf::CircleShape(PIECE_SIZE), x, y};
                        pd.shape.setPosition(x * RECTANGLE_SIZE + PIECE_OFFSET, y * RECTANGLE_SIZE + PIECE_OFFSET);
                        if(piece & IS_BLACK)
                            pd.shape.setFillColor(sf::Color(79, 96, 184));
                        if(piece & IS_RED)
                            pd.shape.setFillColor(sf::Color(158, 49, 49));
                        if(piece & IS_KING)
                        {
                            pd.shape.setOutlineColor(sf::Color(191, 175, 33));
                            pd.shape.setOutlineThickness(3);
                        }
                        pieces.push_back(pd);
                    }
                }
            }
        }
        
        // Draw
        window.clear();
        // Board
        for(int x = 0; x < BOARD_SIZE; x++)
        {
            for(int y = 0; y < BOARD_SIZE; y++)
            {
                sf::RectangleShape& r = ((x + y) % 2) ? whiteRectangle : blackRectangle;
                r.setPosition(x * RECTANGLE_SIZE, y * RECTANGLE_SIZE);
                window.draw(r);
            }
        }
        // Pieces
        for(auto& p : pieces)
        {
            window.draw(p.shape);
        }
        // Update the window
        window.display();
    }
    return 0;
}
