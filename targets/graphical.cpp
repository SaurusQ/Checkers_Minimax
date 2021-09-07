#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <memory>

#include "game.hpp"

#define BOARD_GRAPH_SIZE    800 // Must be divisible by BOARD_SIZE
#define RECTANGLE_SIZE      (BOARD_GRAPH_SIZE / BOARD_SIZE)
#define PIECE_SIZE          (RECTANGLE_SIZE * 0.45f)
#define PIECE_OFFSET        ((RECTANGLE_SIZE / 2.0f) - PIECE_SIZE)

struct PieceData
{
    sf::CircleShape shape;
    int x;
    int y;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_GRAPH_SIZE, BOARD_GRAPH_SIZE), "SFML window");

    // Board
    sf::RectangleShape blackRectangle(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE));
    blackRectangle.setFillColor(sf::Color::Black);
    sf::RectangleShape whiteRectangle(sf::Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE));
    whiteRectangle.setFillColor(sf::Color::White);

    // Pieces
    sf::CircleShape blackPiece(PIECE_SIZE);
    blackPiece.setFillColor(sf::Color::Blue);
    sf::CircleShape redPiece(PIECE_SIZE);
    redPiece.setFillColor(sf::Color::Red);
    
    auto solver = std::make_unique<MiniMaxAB>(10);
    Game game(solver.get(), GameType::CPU_VS_PLAYER);

    std::vector<PieceData> blackPieces(game.getBoard().aliveBlacks(), PieceData{blackPiece, 0, 0});
    std::vector<PieceData> redPieces(game.getBoard().aliveReds(), PieceData{redPiece, 0, 0});

    bool updatePieces = true;
    bool movePiece = false;
    PieceData* pieceToMove = nullptr;

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
                for(auto& b : blackPieces)
                {
                    if(b.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        pieceToMove = &b;
                        movePiece = true;
                        break;
                    }
                }
                for(auto& r : redPieces)
                {
                    if(r.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        pieceToMove = &r;
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
                    switch(game.tryMove(pieceToMove->x, pieceToMove->y, x, y))
                    {
                        case MoveLegality::LEGAL:
                            updatePieces = true;
                            break;
                        case MoveLegality::PARTIAL:
                            pieceToMove->shape.setPosition(x * RECTANGLE_SIZE + PIECE_OFFSET, y * RECTANGLE_SIZE + PIECE_OFFSET);
                            break;
                        case MoveLegality::ILLEGAL: // Fallthrough
                        case MoveLegality::NOTHING:
                            pieceToMove->shape.setPosition(pieceToMove->x * RECTANGLE_SIZE + PIECE_OFFSET, pieceToMove->y * RECTANGLE_SIZE + PIECE_OFFSET);
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
            blackPieces.clear();
            redPieces.clear();
            game.nextTurn();
            const Board b = game.getBoard();
            std::cout << b;
            for(int x = 0; x < BOARD_SIZE; x++)
            {
                for(int y = 0; y < BOARD_SIZE; y++)
                {
                    uint8_t piece = b.getLocation(x, y);
                    if(piece & IS_BLACK)
                    {
                        blackPiece.setPosition(x * RECTANGLE_SIZE + PIECE_OFFSET, y * RECTANGLE_SIZE + PIECE_OFFSET);
                        blackPieces.push_back(PieceData{blackPiece, x, y});
                    }
                    else if(piece & IS_RED)
                    {
                        redPiece.setPosition(x * RECTANGLE_SIZE + PIECE_OFFSET, y * RECTANGLE_SIZE + PIECE_OFFSET);
                        redPieces.push_back(PieceData{redPiece, x, y});
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
        for(auto& b : blackPieces)
        {
            window.draw(b.shape);
        }
        for(auto& r : redPieces)
        {
            window.draw(r.shape);
        }
        // Update the window
        window.display();
    }
    return 0;
}
