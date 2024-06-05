#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1200, 600), "fallout");
    Image background_image;
    background_image.loadFromFile("images/nebo.jpg");
    Texture t_nebo;
    t_nebo.loadFromImage(background_image);
    Sprite nebo(t_nebo);

    while (window.isOpen())
    {
        window.clear();
        window.draw(nebo);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.display();
    }

    return 0;
}
