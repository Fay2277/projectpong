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

sf::Vector2f ballVelocity;
bool player1Serving = true;
const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;

void init()
{
    for (sf::RectangleShape& p : paddles)
    {
        p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
    }

    ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius / 2.f, ballRadius / 2.f);
    paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
    paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f);

    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
}

void load()
{
	ballVelocity = { (player1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };
}

void reset()
{
    ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);
    paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
    paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f);
    load();
}

void update(float dt)
{
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

    float direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[0]))
    {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[1]))
    {
        direction++;
	}

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
        reset();
    }
    else if (bx < 0)
    {
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

    

	paddles[0].move(sf::Vector2f(0.f, direction * paddleSpeed * dt));
}

void render(sf::RenderWindow& window)
{
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

void clean()
{
    // Clean up resources if needed
}

int main()
{

  sf::RenderWindow window(sf::VideoMode({gameWidth, gameHeight}), "PONG");
  init();
  while(window.isOpen())
  {
      static sf::Clock clock;
      const float dt = clock.restart().asSeconds();

      window.clear();
      update(dt);
	  render(window);

      sf::sleep(sf::seconds(time_step));

	  window.display();
  }

  clean();
  return 0;
}
