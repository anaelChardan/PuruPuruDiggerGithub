/**
 * \file CellTextGraphic.cpp
 * \brief Notre classe CellTextGraphic
 * \author CHARDAN Anaël
 * \author DAMEY Jérémy
 * \date 09/03/2014
 */

#include "CellTextGraphic.h"

sf::Font CellTextGraphic::my_font;

void CellTextGraphic::changeTheme( std::string theme ) {
    std::string myfont;
#ifdef __linux__
    if ( theme == "teacher" ) {
         myfont = "Ressources/Font/" + theme + "_arial.ttf";
    } else {
        myfont = "Ressources/Font/" + theme + "_value.ttf";
    }
#else
    if ( theme == "teacher" ) {
         myfont = theme + "_arial.ttf";
    } else {
        myfont = theme + "_value.ttf";
    }
#endif

    if ( !my_font.LoadFromFile( myfont.c_str() ) ) {
        std::cerr << " Error when loading value font " << std::endl;
    } else {
        my_string.SetFont(my_font);
        if ( theme == "ananas" ) {
             my_string.SetSize(23);
             my_string.SetColor(sf::Color(255,255,255));
        } else {
            my_string.SetSize(20);
            my_string.SetColor(sf::Color(0,0,0));
            my_string.SetStyle( sf::String::Bold );
        }
        CellBaseGraphic::changeTheme( theme );
    }
}

void CellTextGraphic::setSpriteAndDraw(int x, int y, sf::RenderWindow* _window, std::string _string) {
    GraphicElement::setSpriteAndDraw( x, y, _window);
    my_string.SetText(_string);
    my_string.SetPosition( my_sprite.GetPosition().x + ( my_sprite.GetSize().x / 2 ) - ( my_string.GetRect().GetWidth() / 2 ), my_sprite.GetPosition().y + ( my_sprite.GetSize().y / 2 ) - ( my_string.GetRect().GetHeight() / 2 ) );
    _window->Draw(my_string);

}

void
CellTextGraphic::setImageToSprite() {
    CellBaseGraphic::setImageToSprite();
}
