#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

void wrapShape(sf::Shape& shape, float screenWidth, float screenHeight) {

    sf::FloatRect bounds = shape.getGlobalBounds();

    float x = bounds.left;
    float y = bounds.top;
    float width = bounds.width;
    float height = bounds.height;

    float newX = x;
    float newY = y;

    //Horizontal wrapping
    if (x > screenWidth) { //Off right -> to left

        newX = -width;

    }

    else if (x + width < 0) { //Off left -> to right

        newX = screenWidth;

    }

    //Vertical wrapping
    if (y > screenHeight) { //Off bottom -> go top

        newY = -height;

    }

    else if (y + height < 0) { //Off top -> to bottom

        newY = screenHeight;

    }

    shape.setPosition(newX, newY);

}

//Check collision function -- returns a bool value 
//Signifying if the objects collided
bool checkCollision(const sf::Shape& shape1, const sf::Shape& shape2) {

    return shape1.getGlobalBounds().intersects(shape2.getGlobalBounds());

}

void handleCollision(sf::Shape& shape1, sf::Color color1,
    sf::Shape& shape2, sf::Color color2,
    sf::Color collisionColor) {

    if (shape1.getGlobalBounds().intersects(shape2.getGlobalBounds())) {
        shape1.setFillColor(collisionColor);
        shape2.setFillColor(collisionColor);
        cout << "\nCollision Detected!\n";
    }
    else {
        shape1.setFillColor(color1);
        shape2.setFillColor(color2);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Drawing Shapes - SFML");
    window.setFramerateLimit(60);

    // Create a red rectangle
    sf::RectangleShape rectangle1(sf::Vector2f(200.f, 100.f));
    rectangle1.setFillColor(sf::Color::Red);
    rectangle1.setPosition(100.f, 100.f);

    //Create a green rectangle
    sf::RectangleShape rectangle2(sf::Vector2f(200.f, 100.f));
    rectangle2.setFillColor(sf::Color::Green);
    rectangle2.setPosition(300.f, 300.f);

    //Creates a speed amount in datatype FLOAT
    float speed = 5.0f;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

            rectangle2.move(0.f, -speed); //UP
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

            rectangle2.move(0.f, speed); //DOWN
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

            rectangle2.move(speed, 0.f); //RIGHT

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

            rectangle2.move(-speed, 0.f); //LEFT

        }

        //Moves the rectanlge to the right by 1, and down by 5
        rectangle1.move(1.f, speed);

        //Wraps the shapes based on wrapShape() function
        wrapShape(rectangle1, 800.f, 600.f);
        wrapShape(rectangle2, 800.f, 600.f);

        //Changes color of shapes upon collision
        handleCollision(rectangle1, sf::Color::Red, rectangle2, sf::Color::Green, sf::Color::Yellow);


        window.clear(sf::Color::Black); // Clear the screen

        // Draw the shapes
        window.draw(rectangle1);
        window.draw(rectangle2);

        window.display(); // Display what was drawn

    }

    return 0;

}