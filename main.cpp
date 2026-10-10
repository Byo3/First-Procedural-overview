#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
namespace HexColors 
{
    constexpr std::array<sf::Color, 10> hexColors = {
      // --- Vivid / Vibrant ---
        sf::Color(0xE7, 0x4C, 0x3C), // 0. Crimson Red      (#E74C3C)
        sf::Color(0xE6, 0x7E, 0x22), // 1. Pumpkin Orange   (#E67E22)
        sf::Color(0xF1, 0xC4, 0x0F), // 2. Sunflower Yellow (#F1C40F)
        sf::Color(0x2E, 0xCC, 0x71), // 3. Emerald Green    (#2ECC71)
        sf::Color(0x34, 0x98, 0xDB), // 4. Peter River Blue (#3498DB)
        sf::Color(0x9B, 0x59, 0xB6), // 5. Amethyst Purple  (#9B59B6)
        // --- Pastels ---
        sf::Color(0xFF, 0x9A, 0x9E), // 6. Soft Rose Pink   (#FF9A9E)
        sf::Color(0xA8, 0xE6, 0xCF), // 7. Mint Green       (#A8E6CF)
        sf::Color(0xDC, 0xD6, 0xCD), // 8. Warm Gray        (#DCD6CD)
        // --- Dark / Deep ---
        sf::Color(0x1A, 0x25, 0x2C), // 9. Midnight Dark   (#1A252C)
    };
};

struct Seeds
{
    const static int seedGeneration() 
    {
        constexpr int seedLimit = 1e9 - 1;
        // Obtains a seed from hardware
            std::random_device rd;
            std::mt19937 gen(rd());
            // Set a range
            std::uniform_int_distribution<int> seed_number(0, seedLimit);
            return seed_number(gen);
    }
    const int ShowSeed() 
    {
        return seedGeneration();
    }
};
struct GridElements
{
    sf::Vector2f Actual_Vector;
    sf::Color Actual_Color;
};

class squares : public Seeds 
{
    private:
    unsigned int windowWidth;
    unsigned int windowHeight;
    sf::RectangleShape Element;
    int quantity_of_point;
    const int generatedSeed = Seeds::ShowSeed();

    public:
    squares(int Width_Bound, int Height_Bound, sf::RectangleShape Shape, int Points) 
    {
        windowWidth       = Width_Bound;
        windowHeight      = Height_Bound;
        Element           = Shape;
        quantity_of_point = Points;
    }
    
    const std::vector<sf::Vector2f> Calculating_Points() 
    {
        // It returns the quantity of point depending on percentage
        std::vector<sf::Vector2f> point_vectors;
        for (int y = 0; y <= quantity_of_point; y++) 
        {
            for (int x = 0; x <= quantity_of_point; x++) 
            {
                point_vectors.push_back({
                    static_cast<float>(x) / quantity_of_point * static_cast<float>(windowWidth),
                    static_cast<float>(y) / quantity_of_point * static_cast<float>(windowHeight)
                });
            }
        }
        return point_vectors;
    }

    const static sf::Vector2f setSize_Square(float windowWidth, float windowHeight) 
    {
        // Separa o quadrados em 10%
        return {windowWidth * 0.1f, windowHeight * 0.1f};
    }

    std::vector<sf::Color> set_colors_to_Squares(int Number) 
    {
        std::vector<sf::Color> Color_List;
        std::string stringSeed = std::to_string(Number);
        for (char& digit : stringSeed) 
        {
            int integer_digit = digit - '0';
            Color_List.push_back(HexColors::hexColors[integer_digit]);
        }
        return Color_List;
    }

    std::vector<GridElements> Unifying_GridElements()
    {
        std::vector<GridElements> List_of_Elements;
        std::vector Coordinates_Vector = Calculating_Points();
        std::vector<sf::Color> Colors = set_colors_to_Squares(generatedSeed);
        for (size_t Index = 0; Index < Coordinates_Vector.size(); Index++) 
        {
                List_of_Elements.push_back({Coordinates_Vector[Index], Colors[Index % Colors.size()]});
        }
        return List_of_Elements;
    }

    void Draw_Square(sf::RenderWindow& window) 
    {
        std::vector<GridElements> unified_elements = Unifying_GridElements();
        
        for (const auto& grid_elements : unified_elements) 
        {
            Element.setPosition(grid_elements.Actual_Vector);
            Element.setFillColor(grid_elements.Actual_Color);
            window.draw(Element);
        }
    }
    int show_seed() const
    {
        return generatedSeed;
    }
};

int main() 
{
    constexpr unsigned int Width  = 600;
    constexpr unsigned int Height = 600;

    sf::RenderWindow window(sf::VideoMode({Width, Height}), "Squares");

    sf::RectangleShape Square_Element;
    sf::Vector2f squareSize = squares::setSize_Square(Width, Height);
    Square_Element.setSize(squareSize);
    
    squares Squares(Width, Height, Square_Element, 10);
    Squares.Calculating_Points();
    std::cout << Squares.show_seed() << std::endl;
    for (const auto& each_color : Squares.set_colors_to_Squares(Squares.show_seed()))
    {
    std::cout << "R: " << static_cast<int>(each_color.r) 
          << " G: " << static_cast<int>(each_color.g) 
          << " B: " << static_cast<int>(each_color.b) << std::endl;    
        
    }

    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent()) 
        {
            if  (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
        }
        window.clear();

        Squares.Draw_Square(window);

        window.display();
    }
}
