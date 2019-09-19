// sfmltools.cc
//

#include "sfmltools.hh"
#define LZZ_INLINE inline
float dot (sf::Vector2f v1, sf::Vector2f v2)
{
  return v1.x*v2.x + v1.y*v2.y;
}
float norm (sf::Vector2f v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}
float angvec2 (sf::Vector2f v1, sf::Vector2f v2)
{
  return acos(dot(v1,v2)/(norm(v1)*norm(v2)));
}
sf::Vector2f vdir (sf::Vector2f v)
{
    return v/norm(v);
}
sf::Vector2f rotate (sf::Vector2f v, float ang)
{
  float x=v.x, y=v.y, cs=cos(ang), sn=sin(ang);
  return sf::Vector2f(cs*x - sn*y, sn*x + cs*y);
}
sf::Vector2f sc2vc (float scal)
{
  return sf::Vector2f(scal, scal);
}
sf::RectangleShape create_rect (sf::Vector2f pos, sf::Vector2f size, sf::Color colorin, sf::Color colorout, float thick)
{
    sf::RectangleShape shape;
    shape.setPosition(pos);
    shape.setSize(size);
    shape.setFillColor(colorin);
    shape.setOutlineColor(colorout);
    shape.setOutlineThickness(thick);
    return shape;
}
sf::CircleShape create_circ (sf::Vector2f pos, float size, sf::Color colorin, sf::Color colorout, float thick)
{
  sf::CircleShape shape;
  shape.setPosition(pos-sc2vc(size));
  shape.setRadius(size);
  shape.setFillColor(colorin);
  shape.setOutlineColor(colorout);
  shape.setOutlineThickness(thick);
  return shape;
}
sf::Text create_text (sf::Vector2f pos, std::string text, int size, sf::Font & font, sf::Text::Style style, sf::Color colorin, sf::Color colorout, int thick)
{
    sf::Text shape(text, font);
    shape.setCharacterSize(size);
    shape.setStyle(style);
    shape.setFillColor(colorin);
    shape.setOutlineColor(colorout);
    shape.setOutlineThickness(thick);
    sf::FloatRect bounds=shape.getLocalBounds();
    shape.setPosition(pos.x-bounds.width*0.5f,pos.y-bounds.height);
    return shape;
}
#undef LZZ_INLINE
