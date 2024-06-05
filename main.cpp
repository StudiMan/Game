#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;

class Rocket {
public:
    std::pair<unsigned, unsigned> size{ 12,23 };
    std::pair<unsigned, unsigned> place;
    Clock clock;

    Rocket() :place((rand() * 1100) / RAND_MAX, (rand() * 500) / RAND_MAX) {}

    bool Booom()
    {
        if (this->size.first >= 100 && this->size.second >= 100)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void fall()
    {
        size.first *= 1.2;
        size.second *= 1.2;
    }
};

int main()
{
    srand(time(0));
    RenderWindow window(sf::VideoMode(1200, 600), "fallout");
    Image background_image;
    background_image.loadFromFile("images/nebo.jpg");
    Texture t_nebo;
    t_nebo.loadFromImage(background_image);
    Sprite nebo(t_nebo);

    Rocket r;

    while (window.isOpen())
    {
        window.clear();
        window.draw(nebo);

        Texture t_rocket;
        t_rocket.loadFromFile("images/missile00.png");
        Sprite rocket(t_rocket);
        rocket.setTextureRect(IntRect(10, 3, 12, 23));
        rocket.setScale(r.size.first / 12.0, r.size.second / 23.0);
        rocket.setPosition(r.place.first, r.place.second);
        window.draw(rocket);

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
