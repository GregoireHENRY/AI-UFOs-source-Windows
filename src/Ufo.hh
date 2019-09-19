#ifndef UFO_HH
#define UFO_HH

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tools.hh"
#include "sfmltools.hh"
#include "Graphics.hh"


class Flag;


class Ufo
{
public:
    bool collided, owning;
    int team, id;
    float size=350, mag, flag_rot_speed=0.1f, motorsize=40;
    sf::Vector2f pos, vel, acc, aim, field, flag_rot, motorposleft,
                 motorposright, spawn;
    sf::CircleShape shape, motorleft, motorright;
    sf::Color color;
    sf::Text *name, *score;
    Graphics gfx;
    Flag *flag;
    Flag *enemy_flag;

    Ufo();
    Ufo(int team, int id);
    void setup();
    std::vector<float> getData();
    void setData(float dt, float _mag, float aimx, float aimy);
    void draw(sf::RenderWindow &window);
    void collwall();
    void collufos(Ufo* othufo);
    void collflag();
    void detectScore();
};


#endif
