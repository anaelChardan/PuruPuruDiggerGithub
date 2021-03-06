/**
 * \file GameViewSFML.cpp
 * \brief Notre classe GameViewSFML
 * \author CHARDAN Anaël
 * \author DAMEY Jérémy
 * \date 09/03/2014
 */

#include "GameViewSFML.h"

#include "Observers/InterfaceObserver.h"
#include "Graphics/EnglishGraphic.h"
#include "Graphics/FrenchGraphic.h"
#include "Graphics/SpanishGraphic.h"
#include "Graphics/DeutschGraphic.h"
#include "Graphics/ItalianoGraphic.h"
#include "Manager/SoundManager.h"

using namespace sf;


//Constructeur
GameView::GameView() {
     //Le style de la fenêtres
    my_window = new RenderWindow( VideoMode(WINDOWWITDH, WINDOWHEIGHT, BPP), "PuruPuruDigger", Style::Close);

     //On bloque le rafraichissement à 60 par seconde
    my_window->SetFramerateLimit(60);

    // buttons
    my_playButton = new ButtonGraphic();
    my_settingButton = new ButtonGraphic();
    my_bestButton = new ButtonGraphic();
    my_quitButton = new ButtonGraphic();

    my_soundIcon = new GraphicSound();
    my_musicIcon = new GraphicMusic();

    my_ananasSprite = new AnanasSprite();
    my_teacherSprite = new TeacherSprite();

    my_background = new BackgroundGraphic();

    my_languageToSprite = new std::map<Language, LanguageGraphic*>();

    my_languageToSprite->operator[](english) = new EnglishGraphic();
    my_languageToSprite->operator[](francais) = new FrenchGraphic();
    my_languageToSprite->operator[](italiano) = new ItalianoGraphic();
    my_languageToSprite->operator[](espanol) = new SpanishGraphic();
    my_languageToSprite->operator[](deutsch) = new DeutschGraphic();


    // dispatch d'event en tout genre
    my_context = new PuruContext();
    SoundManager::getInstance()->setContext( my_context );
    my_eventDispatcher = new EventDispatcher( my_context );
}

//Destructeur
GameView::~GameView() {
    delete my_window;
    delete my_context;
    delete my_playButton;
    delete my_settingButton;
    delete my_bestButton;
    delete my_quitButton;
    delete my_soundIcon;
    delete my_ananasSprite;
    delete my_teacherSprite;
    delete my_background;
    delete my_eventDispatcher;


    for ( std::map<Language, LanguageGraphic*>::const_iterator it = my_languageToSprite->begin() ; it!=my_languageToSprite->end(); ++it) {
        delete (*my_languageToSprite)[ it->first ];
    }

}

//Injection de dépendance model
void GameView::setModel(GameModel *model) {
    my_model = model;
}


void GameView::goToPresentation() {
    my_context->setChoosingOption( false );
    my_context->setViewingBestScore( false );
    my_context->setInPresentation( true );
}

void GameView::goToSettings() {
    my_context->setInPresentation( false );
    my_context->setChoosingOption( true );
}

void GameView::goToPlay() {
    my_context->setInPresentation( false );
    my_context->setPlaying( true );

    if ( my_context->isEnableMusic() ) {
        SoundManager::getInstance()->playMusic();
    }
    my_model->reset();

}

void GameView::goToScore() {
    my_context->setInPresentation( false );
    my_context->setViewingBestScore( true);

}

void GameView::goToEnterScore() {
    my_context->setPlaying( false );
    my_context->setEnterABestScore( true );
    my_context->setAnimation( false );
}



void GameView::initPresentation() {
    my_eventDispatcher->addObserver( my_playButton );
    my_eventDispatcher->addObserver( my_bestButton );
    my_eventDispatcher->addObserver( my_settingButton );
    my_eventDispatcher->addObserver( my_quitButton );

    for ( std::map<Language, LanguageGraphic*>::const_iterator it = my_languageToSprite->begin() ; it!=my_languageToSprite->end(); ++it) {
        my_eventDispatcher->removeObserver( (*my_languageToSprite)[ it->first ] );
    }

    my_eventDispatcher->removeObserver(my_ananasSprite);
    my_eventDispatcher->removeObserver(my_teacherSprite);
}

void GameView::initSettings() {
    for ( std::map<Language, LanguageGraphic*>::const_iterator it = my_languageToSprite->begin() ; it!=my_languageToSprite->end(); ++it) {
        my_eventDispatcher->addObserver( (*my_languageToSprite)[ it->first ] );
    }
    my_eventDispatcher->addObserver(my_ananasSprite);
    my_eventDispatcher->addObserver(my_teacherSprite);

    my_eventDispatcher->removeObserver( my_playButton );
    my_eventDispatcher->removeObserver( my_bestButton );
    my_eventDispatcher->removeObserver( my_settingButton );

}

void GameView::initBestScore() {
    my_eventDispatcher->addObserver( my_quitButton );
    my_eventDispatcher->removeObserver( my_playButton );
    my_eventDispatcher->removeObserver( my_bestButton );
    my_eventDispatcher->removeObserver( my_settingButton );
}

void GameView::initEnterScore() {
    my_eventDispatcher->removeObserver( my_quitButton );
}

void GameView::initPlay() {
    my_eventDispatcher->removeObserver( my_playButton );
    my_eventDispatcher->removeObserver( my_bestButton );
    my_eventDispatcher->removeObserver( my_settingButton );
};


void GameView::initView() {
    if ( my_context->isInPresentation() ) {
        initPresentation();
    } else if ( my_context->isChoosingOption() ) {
        initSettings();
    } else if ( my_context->isViewingBestScore() ) {
        initBestScore();
    } else if ( my_context->isPlaying() ) {
        initPlay();
    } else if ( my_context->isEnterABestScore() ) {
        initEnterScore();
    }
}


//Boucle d'événement
void GameView::treatGame( ) {

    InterfaceObserver* interfaceObserver = new InterfaceObserver( my_window, my_model, my_playButton, my_settingButton, my_bestButton, my_quitButton, my_musicIcon, my_soundIcon, my_languageToSprite, my_ananasSprite, my_teacherSprite, my_background );

    my_eventDispatcher->addObserver( interfaceObserver );
    my_eventDispatcher->addObserver( my_soundIcon );
    my_eventDispatcher->addObserver( my_musicIcon );
    my_eventDispatcher->addObserver( my_background );

    // On abonne quand meme pour le change theme
    // cela sera desabommer dans le init
    for ( std::map<Language, LanguageGraphic*>::const_iterator it = my_languageToSprite->begin() ; it!=my_languageToSprite->end(); ++it) {
        my_eventDispatcher->addObserver( (*my_languageToSprite)[ it->first ] );
    }
    my_eventDispatcher->addObserver(my_ananasSprite);
    my_eventDispatcher->addObserver(my_teacherSprite);
    my_eventDispatcher->addObserver( my_playButton );
    my_eventDispatcher->addObserver( my_bestButton );
    my_eventDispatcher->addObserver( my_settingButton );
    my_eventDispatcher->addObserver( my_quitButton );

    // theme par defaut
    my_eventDispatcher->changeTheme("ananas");

    initPresentation();

    while ( my_window->IsOpened( ) ) {
        Event event;
        while ( my_window->GetEvent( event ) ) {
            if ( event.Type == Event::Closed ) {
                my_window->Close();
            } else {
                initView();

                switch (event.Type) {
                    case Event::MouseButtonPressed:
                        if ( my_context->isInPresentation() ) {
                            if ( my_playButton->isInZone(event.MouseButton.X, event.MouseButton.Y) ) {
                                goToPlay();
                            } else if ( my_quitButton->isInZone(event.MouseButton.X, event.MouseButton.Y) ) {
                                my_window->Close();
                            } else if ( my_settingButton->isInZone(event.MouseButton.X, event.MouseButton.Y) ) {
                                goToSettings();
                            } else if ( my_bestButton->isInZone(event.MouseButton.X, event.MouseButton.Y) ) {
                                goToScore();
                            }
                        } else if ( my_context->isChoosingOption() ) {
                            for ( std::map<Language, LanguageGraphic*>::const_iterator it = my_languageToSprite->begin() ; it!=my_languageToSprite->end(); ++it) {
                                if (  (*my_languageToSprite)[ it->first ]->isInZone ( event.MouseButton.X, event.MouseButton.Y ) ) {
                                    my_context->setLanguage( it->first );
                                    break;
                                }
                            }

                            if ( my_ananasSprite->isInZone( event.MouseButton.X, event.MouseButton.Y ) ) {
                                my_eventDispatcher->changeTheme("ananas");

                            } else if ( my_teacherSprite->isInZone( event.MouseButton.X, event.MouseButton.Y) ) {
                                my_eventDispatcher->changeTheme("teacher");

                            } else if ( my_quitButton->isInZone(event.MouseButton.X, event.MouseButton.Y) ) {
                                goToPresentation();
                            }
                        } else if ( my_context->isViewingBestScore() ) {
                            if ( my_quitButton->isInZone(event.MouseButton.X, event.MouseButton.Y ) ) {
                                goToPresentation();
                            }
                        } else if ( my_context->isPlaying() ) {
                            int valueY = convertYPixel( event.MouseButton.Y );
                            int valueX = convertXPixel( event.MouseButton.X );

                            if ( ( valueY != -1 ) && ( valueX != -1 ) && ( !my_context->isInAnimation() )  ) {
                                SoundManager::getInstance()->clickCell();
                                my_model->orderMovement( valueY, valueX );
                                my_context->setAnimation( true );
                            }
                            if ( my_quitButton->isInZone(event.MouseButton.X, event.MouseButton.Y) ) {
                                goToEnterScore();
                            }
                        }
                        break;
                    default:
                        break;

                }
                my_eventDispatcher->notify( event );
            }
        }

        my_eventDispatcher->preDisplay();
        my_window->Display();
        my_eventDispatcher->postDisplay();
    }
    delete interfaceObserver;
}
