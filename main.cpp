#include <sstream>
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
const float velocityMultiplier = 1.1f;

sf::CircleShape ball;
sf::RectangleShape paddles[2];
sf::Text text;
sf::Font font;

sf::Vector2f ballVelocity;
bool playerServing = true;
const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;

int score[2] = { 0.0 };

void reset()
{
	ballVelocity = {(playerServing ? initialVelocityX : -initialVelocityX), initialVelocityY};

    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
    paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
    paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f);
    
    std::stringstream sstr;
	sstr << score[0] << " - " << score[1];
	text.setString(sstr.str());

	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * 0.5f), 0);

}

void init()
{
    for (sf::RectangleShape& p : paddles)
    {
        p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
    }

    ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius, ballRadius);

	font.loadFromFile("resources/fonts/Roboto-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(sf::Color(255, 255, 255));

    reset();
}

void update(float dt)
{
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

    float direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[0]) && paddles[0].getPosition().y > paddleSize.y / 2.f)
    {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[1]) && paddles[0].getPosition().y < gameHeight - paddleSize.y / 2.f)
    {
        direction++;
	}
    paddles[0].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));

    if (sf::Keyboard::isKeyPressed(controls[2]) && paddles[1].getPosition().y > paddleSize.y / 2.f)
    {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[3]))
    {
        direction++;
    }
    paddles[1].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));

	ball.move(ballVelocity * dt);

    if (by > gameHeight)
    {
        ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
        ball.move(sf::Vector2f(0.f, -10.f));
    }
    else if (by < 0)
    {
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(sf::Vector2f(0.f, -10.f));
    }
    else if (bx > gameWidth)
    {
        score[0]++;
        reset();
    }
    else if (bx < 0)
    {
		score[1]++;
        reset();
	}
    else if (bx < paddleSize.x + paddleOffsetWall &&
             by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
             by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
    {
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(sf::Vector2f(10.f, 0.f));
	}
    else if (bx < gameWidth - paddleSize.x - paddleOffsetWall &&
             by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
             by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
    {
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(sf::Vector2f(10.f, 0.f));
    }

}

void render(sf::RenderWindow& window)
{
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
	window.draw(text);
}

int main()
{

  sf::RenderWindow window(sf::VideoMode({gameWidth, gameHeight}), "PONG");
  window.setVerticalSyncEnabled(true);
  init();
  while(window.isOpen())
  {
      static sf::Clock clock;
      float dt = clock.restart().asSeconds();

      sf::Event event;
      while(window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
          {
              window.close();
              return 0;
		  }
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
          window.close();
          return 0;
	  }

      window.clear();
      update(dt);
	  render(window);

      sf::sleep(sf::seconds(time_step));

	  window.display();
  }

  return 0;
}
