#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

using namespace sf;
using namespace std;

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
    background_image.loadFromFile("Images/nebo.jpg");
    Texture t_nebo;
    t_nebo.loadFromImage(background_image);
    Sprite nebo(t_nebo);

    vector<Rocket> rockets(1);

    Clock global_time;

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

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            pair<unsigned, unsigned> mouse_place(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            for (int i = 0; i < rockets.size(); ++i)
            {
                if (rockets[i].place.first <= mouse_place.first && rockets[i].place.second <= mouse_place.second
                    && (rockets[i].place.first + rockets[i].size.first) >= mouse_place.first && (rockets[i].place.second + rockets[i].size.second) >= mouse_place.second)
                {
                    rockets.erase(rockets.begin() + i);
                    break;
                }
            }
        }

        Texture t_rocket;
        t_rocket.loadFromFile("Images/missile00.png");
        Sprite rocket(t_rocket);
        rocket.setTextureRect(IntRect(10, 3, 12, 23));
        for (int i = 0; i < rockets.size(); ++i)
        {
            rocket.setScale(rockets[i].size.first / 12.0, rockets[i].size.second / 23.0);
            rocket.setPosition(rockets[i].place.first, rockets[i].place.second);
            window.draw(rocket);
            if (!rockets[i].Booom() && rockets[i].clock.getElapsedTime() >= milliseconds(300))
            {
                rockets[i].fall();
                rockets[i].clock.restart();
            }
        }
        if (global_time.getElapsedTime() >= milliseconds(1100))
        {
            rockets.push_back(Rocket());
            global_time.restart();
        }
        window.display();
    }

    return 0;
}
