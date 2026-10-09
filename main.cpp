#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <cstddef>
#include <random>

class squares {
    private:
    unsigned int windowWidth;
    unsigned int windowHeight;
    sf::RectangleShape Element;
    int quantity_of_point;

    public:
    squares(int Width_Bound, int Height_Bound, sf::RectangleShape Shape, int Points) {
        windowWidth       = Width_Bound;
        windowHeight      = Height_Bound;
        Element           = Shape;
        quantity_of_point = Points;
    }
    
    const std::vector<sf::Vector2f> Calculating_Points(sf::RectangleShape& points) {
        // It returns the quantity of point depending on percentage
        std::vector<sf::Vector2f> point_vectors;
        for (int y = 0; y <= quantity_of_point; y++) {
            for (int x = 0; x <= quantity_of_point; x++) {
                point_vectors.push_back({
                    static_cast<float>(x) / quantity_of_point * static_cast<float>(windowWidth),
                    static_cast<float>(y) / quantity_of_point * static_cast<float>(windowHeight)
                });
            }
        }
        return point_vectors;
    }

    const static sf::Vector2f setSize_Square(float windowWidth, float windowHeight) {
        return {windowWidth * 0.1f, windowHeight * 0.1f};
    }

    void Draw_Square(sf::RenderWindow& window) {
        std::vector Coordinates_Vector = Calculating_Points(Element);
        for (const auto coordinates : Coordinates_Vector) {
            Element.setPosition(coordinates);
            window.draw(Element);
        }
    }
};

enum struct Color {

};

int main() {

    constexpr unsigned int Width  = 600;
    constexpr unsigned int Height = 600;

    sf::RenderWindow window(sf::VideoMode({Width, Height}), "Squares");

    sf::RectangleShape Square;
    sf::Vector2f squareSize = squares::setSize_Square(Width, Height);
    Square.setSize(squareSize);
    
    
    squares Squares(Width, Height, Square, 10);
    Squares.Calculating_Points(Square);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if  (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();

        Squares.Draw_Square(window);

        window.display();
    }
}
