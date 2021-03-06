/**
 * \file GraphicAudibleElement.cpp
 * \brief Notre classe GraphicAudibleElement
 * \author CHARDAN Anaël
 * \author DAMEY Jérémy
 * \date 09/03/2014
 */

#include "GraphicAudibleElement.h"
#include "../Constantes.h"

sf::Image GraphicAudibleElement::my_image;


void GraphicAudibleElement::changeTheme( std::string theme ) {
    std::string myimage;
#ifdef __linux__
    myimage = "Ressources/Pictures/icon.png";
#else
    myimage = "icon.png";
#endif
    if ( !my_image.LoadFromFile( myimage.c_str() ) ) {
        std::cerr << " Error when loading icon image " << std::endl;
    } else {
        setImageToSprite();
    }
}

void GraphicAudibleElement::setImageToSprite() {
    my_image.CreateMaskFromColor(sf::Color(0, 55, 97));
    my_sprite.SetImage(my_image);
    my_sprite.Resize( ICONWIDTH, ICONHEIGHT);
}



/** Events Subscriber */

void GraphicAudibleElement::mouseButtonPressed( sf::Event event ) {
    if ( isInZone( event.MouseButton.X, event.MouseButton.Y ) ) {
        reverse();
    }
}
