#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

struct Pencil{
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

public:
    Pencil(sf::RenderWindow& window) : window(window){
        if(font.loadFromFile("Ubuntu.ttf")){
            std::cout << "Font loaded" << std::endl;
        }else{
            std::cout << "Font don't loaded" << std::endl;
        }
        text.setFont(font);
    }

    void write(std::string str, int x, int y, int size, sf::Color color){
        text.setString(str);
        text.setPosition(x, y);
        text.setCharacterSize(size);
        text.setFillColor(color);
        window.draw(text);
    }
};

class Bubble{
    int x;
    int y;
    char letter;
    int speed;
    bool alive {true};

public:
    static const int radius {10}; // constante de classe
    
    void update(){
        y += speed;
    }

    Bubble(int x, int y, char letter, int speed) : x(x), y(y), letter(letter), speed(speed) {}

    void draw(sf::RenderWindow& window){
        sf::CircleShape bubble {Bubble::radius};
        bubble.setPosition(x, y);
        bubble.setFillColor(sf::Color::White);
        window.draw(bubble);

        static Pencil pencil(window);
        pencil.write(std::string(1, letter), x + 0.2 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::Red);
    }

    bool is_alive(){
        return alive;
    }

    void kill(){
        alive = false;
    }

    char get_letter(){
        return letter;
    }

    int get_speed(){
        return speed;
    }

    int get_x(){
        return x;
    }

    int get_y(){
        return y;
    }
};

class Board{
    sf::RenderWindow& window;
    std::vector<Bubble> bubbles;
    int hits {0};
    int misses {0};
    Pencil pencil;
    int speed_level {3};
    int new_bubble_timeout {30};
    int new_bubble_timer {0};

public:
    Board(sf::RenderWindow& window) : window(window) , pencil(window){
        bubbles.push_back(Bubble(200, 100, 'B', 1));
        bubbles.push_back(Bubble(300, 100, 'A', 2));
        bubbles.push_back(Bubble(400, 100, 'T', 3));
    }

    void set_speed_level(int speed_level){
        this->speed_level = speed_level;
    }

    void set_new_bubble_timeout(int new_bubble_timeout){
        this->new_bubble_timeout = new_bubble_timeout;
    }

    int get_hits(){
        return hits;
    }

    int get_misses(){
        return misses;
    }

    void set_hits(int hits){
        this->hits = hits;
    }

    void set_misses(int misses){
        this->misses = misses;
    }

    void clear_bubbles(){
        bubbles.clear();
    }

    void update(){

        if(check_new_bubble()){
            add_new_bubble();
        }

        for(Bubble& bubble : bubbles){
            bubble.update();
        }

        mark_outside_bubbles();
        remove_dead_bubbles();
    }

    void remove_dead_bubbles(){
        std::vector<Bubble> alive_bubbles;
        
        for(Bubble& bubble : bubbles){
            if(bubble.is_alive()){
                alive_bubbles.push_back(bubble);
            }
        }

        bubbles = alive_bubbles;
    }

    void mark_outside_bubbles(){
        for(Bubble& bubble : bubbles){
            if(bubble.get_y() + 2 * Bubble::radius > (int) window.getSize().y){
                if(bubble.is_alive()){
                    bubble.kill();
                    misses++;
                }
            }
        }
    }

    void mark_by_hit(char letter){
        for(Bubble& bubble : bubbles){
            if(bubble.get_letter() == letter){
                if(bubble.is_alive()){
                    bubble.kill();
                    hits++;
                    break;
                }
            }
        }
    }

    bool check_new_bubble(){
        new_bubble_timer--;
        if(new_bubble_timer <= 0){
            new_bubble_timer = new_bubble_timeout;
            return true;
        }
        return false;
    }

    void add_new_bubble(){
        int x = rand() % ((int) window.getSize().x - 2 * Bubble::radius);
        int y = -2 * Bubble::radius;
        int speed = rand() % speed_level + 1;
        char letter = 'A' + rand() % 26;

        bubbles.push_back(Bubble(x, y, letter, speed));
    }

    void draw(){
        pencil.write("Hits: " + std::to_string(hits) + " Misses: " + std::to_string(misses), 10, 10, 20, sf::Color::White);
        pencil.write("Size: " + std::to_string(bubbles.size()), 10, 30, 20, sf::Color::White);

        for(Bubble& bubble : bubbles){
            bubble.draw(window);
        }
    }
};

class Game {
    sf::RenderWindow window;
    Board board;
    std::function<void()> on_update; //função corrente

public:
    Game() : window(sf::VideoMode(800, 600), "Game"), board(window){
        window.setFramerateLimit(30);
        this->on_update = [&](){ // lambda
            this->menu();
        };
    }

    void process_events(){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }else if(event.type == sf::Event::TextEntered){
                char code = static_cast<char>(event.text.unicode); // converte para char
                code = toupper(code); // converte para maiusculo para independencia de capslock
                board.mark_by_hit(code);
            }
        }
    }


    void menu(){ //TODO
        static Pencil pencil(window);
        window.clear(sf::Color::Blue);
        pencil.write("Welcome to the digitation game", 0, 100, 30, sf::Color::White);
        pencil.write("Choose your difficulty", 0, 150, 30, sf::Color::White);
        pencil.write("1 - Easy", 0, 200, 30, sf::Color::White);
        pencil.write("2 - Medium", 0, 250, 30, sf::Color::White);
        pencil.write("3 - Dark Souls", 0, 300, 30, sf::Color::White);	
        window.display();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            this->on_update = [&](){
                this->gameplay();
            };
        
            board.set_speed_level(3);
            board.set_new_bubble_timeout(30);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            this->on_update = [&](){
                this->gameplay();
            };

            board.set_speed_level(10);
            board.set_new_bubble_timeout(20);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            this->on_update = [&](){
                this->gameplay();
            };

            board.set_speed_level(20);
            board.set_new_bubble_timeout(10);
        }    
    }

    void gameplay(){
        board.update();
        
        window.clear(sf::Color::Black);
        board.draw();
        window.display();

        if(board.get_misses() > 10){
            this->on_update = [&](){
                this->gameover();
            };
        }
    }

    void gameover(){
        static Pencil pencil(window);
        window.clear(sf::Color::Red);
        pencil.write("Game Over", 250, 250, 50, sf::Color::White);
        pencil.write("You scored " + std::to_string(board.get_hits()) + " points", 250, 300, 30, sf::Color::White);
        pencil.write("Press R to restart", 250, 350, 30, sf::Color::White);
        pencil.write("Press Q to quit", 250, 400, 30, sf::Color::White);
        window.display();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){ // TODO
            this->on_update = [&](){
                this->menu();
            };
            board.set_hits(0);
            board.set_misses(0);
            window.clear();
            board.clear_bubbles();
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            window.close();
        }
    }

    void main_loop(){
        while(window.isOpen()){
            process_events();
            on_update();
        }
    }
};


int main(){
    Game game;
    game.main_loop();
    return 0;
}