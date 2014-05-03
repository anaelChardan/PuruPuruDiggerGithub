#include "LanguageGraphic.h"
#include "../Constantes.h"

sf::Image LanguageGraphic::my_image;


void LanguageGraphic::changeTheme( std::string theme ) {
    
    std::string myimage = "languages.png";
    if ( !my_image.LoadFromFile( myimage.c_str() ) ) {
        std::cerr << " Error when loading languages image " << std::endl;
    } else {
        setImageToSprite();
    }
}

void LanguageGraphic::setImageToSprite() {
    my_image.CreateMaskFromColor(sf::Color(0, 55, 97));
    my_sprite.SetImage(my_image);
}

void LanguageGraphic::setHover() {
   my_sprite.SetColor(sf::Color(255,255,255,128));
}

void LanguageGraphic::reset() {
    my_sprite.SetColor(sf::Color(255,255,255,255));
}


/** Events Subscriber */

void LanguageGraphic::mouseMoved( sf::Event event ) {
    if ( isInZone( event.MouseMove.X, event.MouseMove.Y ) ) {
        setHover();
    } else {
        reset();
    }
}