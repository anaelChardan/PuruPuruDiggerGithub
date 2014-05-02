#include "GameViewSFML.h"

#include "Observers/InterfaceObserver.h"

using namespace sf;


//Constructeur
GameView::GameView() {
     //Le style de la fenêtres
    my_window = new RenderWindow( VideoMode(WINDOWWITDH, WINDOWHEIGHT, BPP), "PuruPuruDigger", Style::Close);

     //On bloque le rafraichissement à 60 par seconde
    my_window->SetFramerateLimit(60);
    
    my_eventDispatcher = new EventDispatcher();

}

//Destructeur
GameView::~GameView() {
    delete my_window;
}

//Injection de dépendance model
void GameView::setModel(GameModel *model) {
    my_model = model;
}

//Boucle d'événement
void GameView::treatGame( ) {
    
    InterfaceObserver* interfaceObserver = new InterfaceObserver( my_window, my_model );
    my_eventDispatcher->addObserver( interfaceObserver );
    

    while ( my_window->IsOpened( ) ) {
        Event event;
        while ( my_window->GetEvent( event ) ) {
            if ( event.Type == Event::Closed ) {
                my_window->Close();
            } else {
                my_eventDispatcher->dispatch( event );
            }
        }
        
        my_eventDispatcher->preDisplay();
        my_window->Display();
        my_eventDispatcher->postDisplay();
    }
}
