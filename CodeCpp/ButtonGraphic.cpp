#include "ButtonGraphic.h"
#include "Constantes.h"

sf::Image ButtonGraphic::my_image;
sf::Font ButtonGraphic::my_font;


void
ButtonGraphic::setTeacherMode() {
#ifdef __linux
    if ( !my_image.LoadFromFile("Pictures/buttonTeach.png" ) || !my_font.LoadFromFile("Font/arial.ttf") )
        std::cerr << " Error when loading button image or button font" << std::endl;

#else
    if ( !my_image.LoadFromFile("buttonTeach.png") || !my_font.LoadFromFile("arial.ttf") ) {
        std::cerr << " Error when loading button image or button font " << std::endl;

    }
#endif
    else {
        my_string.SetFont( my_font );
        my_string.SetSize(30);
        my_string.SetColor(sf::Color(0,0,0));
        setImageToSprite();
    }
}

void
ButtonGraphic::setAnanasMode() {
#ifdef __linux
    if ( !my_image.LoadFromFile("Pictures/buttonAnanas.png" ) || !my_font.LoadFromFile("Font/buttonFont.ttf") )
        std::cerr << " Error when loading button image or button font " << std::endl;
#else
    if ( !my_image.LoadFromFile("buttonAnanas.png") || !my_font.LoadFromFile("buttonFont.ttf") ) {
        std::cerr << " Error when loading button image or button font " << std::endl;
    }
#endif
    else {
        my_string.SetFont( my_font );
        my_string.SetSize(30);
        my_string.SetColor(sf::Color(251,210,98));
        setImageToSprite();
    }
}

void
ButtonGraphic::setImageToSprite() {
    my_image.CreateMaskFromColor(sf::Color(0, 55, 97));
    my_sprite.SetImage(my_image);
    my_sprite.SetSubRect( sf::IntRect( BUTTONNORMSX, BUTTONCASEBEGIN, BUTTONNORMEX, BUTTONCASEHEIGHT ) );
    my_sprite.Resize( BUTTONWIDTH, BUTTONHEIGHT);
}

void
ButtonGraphic::setHover() {
    my_sprite.SetSubRect( sf::IntRect( BUTTONHOVESX, BUTTONCASEBEGIN, BUTTONHOVEEX, BUTTONCASEHEIGHT ) );
}

void
ButtonGraphic::reset() {
    my_sprite.SetSubRect( sf::IntRect( BUTTONNORMSX, BUTTONCASEBEGIN, BUTTONNORMEX, BUTTONCASEHEIGHT ) );
}


void
ButtonGraphic::setSpriteAndDraw(int x, int y, sf::RenderWindow* _window, std::string _string) {
    GraphicElement::setSpriteAndDraw( x, y, _window);
    my_string.SetText(_string);
    my_string.SetPosition( my_sprite.GetPosition().x + ( my_sprite.GetSize().x / 2 ) - ( my_string.GetRect().GetWidth() / 2 ), my_sprite.GetPosition().y + ( my_sprite.GetSize().y / 2 ) - ( my_string.GetRect().GetHeight() / 2 ) );
    _window->Draw(my_string);
    
}

void
ButtonGraphic::draw(sf::RenderWindow *_window) const {
    _window->Draw(my_sprite);
    _window->Draw(my_string);
}