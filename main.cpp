#include <SFML/Graphics.hpp>

const sf::Keyboard::Key controls[4] =
{
    sf::Keyboard::A,
    sf::Keyboard::Z,
    sf::Keyboard::Up,
    sf::Keyboard::Down
};

const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; // 60 fps




int main()
{
  sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}
