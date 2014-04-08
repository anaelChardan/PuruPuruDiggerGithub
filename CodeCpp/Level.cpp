/**
 * \file Level.cpp
 * \brief Les méthodes liées à notre classe level
 * \author CHARDAN Anaël
 * \author DAMEY Jérémy
 * \date 09/03/2014
 */


#include "Level.h"
#include "Bomb.h"
#include "GoldCell.h"
#include "EmptyCell.h"
#include <vector>
#include <algorithm>

using namespace std;
/*===========================
 Le constructeur
 =============================*/

Level::Level(Score* score) {
    //On fait pointé my_score sur l'adresse du score qu'on lui à donné
    my_score = score;

    //On met nos mouvements courants à 0
    my_currentMove = 0;

    //Comme c'est le premier niveau, l'objectif est 10
    my_goal = 10;

    //Comme c'est le premier niveau, le bonus généré par le level est 500
    my_bonus = 500;
    
    //On donne l'instant présent à notre départ
    time(&my_depart);
    timeGoal = 60;

    //On alloue le digger
    my_digger = new Digger();

    //On bloque la taille de notre vecteur
    my_grid.resize( LIGNE );

    for(  int i = 0; i < LIGNE; i++ ) {
        my_grid[i].resize( COLONNE );
    }
    
    my_win = false;
    my_lose = false;

    //On fait pointé notre Digger dessus cette case;
    my_grid[0][0] = my_digger;

    //On appelle la fonction n'initialisation
    initGrid();
}

/*===========================
 Le destructeur
 =============================*/

Level::~Level() {
    for (  int i = 0; i < LIGNE; i++ ) {
        for (  int j = 0; j < COLONNE; j++ ) {
            delete my_grid[i][j];
        }
    }
}

/*===========================
 Les méthodes privés
 =============================*/

void
Level::move(  int DeltaX,  int DeltaY ) {
    int nbStep = -1;
    int pointInGame = -1;

    if ( isCellClickable( ( my_digger->getX() + DeltaX ), ( my_digger->getY() + DeltaY ) ) ) {
        ///On veut savoir de combien de coup on veut se déplacer
        nbStep = my_grid[ (my_digger->getX() + DeltaX) ][ (my_digger->getY() + DeltaY ) ]->getValue();
        
        ///On veut connaître les points en jeu
        pointInGame = my_grid[ (my_digger->getX() + DeltaX) ][ (my_digger->getY() + DeltaY ) ]->getPoints();
    }
    
    ///On met notre compteur à 0
    int cpt = 0;
    
    ///Tant que l'on à pas fait le bon nombre de coup et que la case d'a côté est bien une gold ou une value
    while ( cpt < nbStep && ( isCellClickable( ( my_digger->getX() + DeltaX ), ( my_digger->getY() + DeltaY ) ) ) ) {
        
        ///Si l'on rencontre un trésor pendant un déplacement
        if ( dynamic_cast<GoldCell*>(my_grid[ ( my_digger->getX() + DeltaX ) ][ ( my_digger->getY() + DeltaY ) ]) !=NULL ) {
            ///On prend les points du bonus
            my_score->addPoints( my_grid[ ( my_digger->getX() + DeltaX ) ][ ( my_digger->getY() + DeltaY ) ]->getPoints() );
        }
        
        ///On delete la case suivante
        delete my_grid[ ( my_digger->getX() + DeltaX ) ][ ( my_digger->getY() + DeltaY ) ];
        
        ///On y place notre digger
        my_grid[ ( my_digger->getX() + DeltaX ) ][ ( my_digger->getY() + DeltaY ) ] = my_digger;
        
        ///On remplace notre ancienne case du digger par une case Vide avec un autoSet
        my_grid[ my_digger->getX() ][ my_digger->getY() ] = new EmptyCell( my_digger->getX(), my_digger->getY() );
        
        ///On set les case de notre digger
        my_digger->setX( my_digger->getX() + DeltaX );
        my_digger->setY( my_digger->getY() + DeltaY );
        
        ///On passe au coup suivant
        cpt++;
    }
    
    //Si le déplacement s'est mal passé ( donc cpt a bougé et est différent de 0 )
    //Les autres renvoient -1
    if ( cpt != 0 &&  cpt < nbStep ) {
        lostLevel();
    } else if ( nbStep != -1 && cpt!=0 ){
        my_currentMove += nbStep;
        my_score->addPoints(pointInGame);
        //Si on a atteint l'objectif
        if ( my_currentMove >= my_goal ) {
            winLevel();
        }
    }
    
}

void
Level::shuffle() {

    vector<CellBase*> tmp;
     int taille = LIGNE * COLONNE;
    tmp.resize( taille );
     int z = 0;

    //2D to 1D
    while ( z < ( taille ) ) {
        for (  int i = 0 ; i < LIGNE ; i++ ){
            for ( int j = 0; j < COLONNE ; j++ ){
                tmp[z] = my_grid[i][j];
                z++;
            }
        }
    }

    random_shuffle( tmp.begin(), tmp.end() );

    //1D to 2D
    z=0;
    while ( z < taille ) {
        //Parcours en hauteur
        for (  int i = 0 ; i < LIGNE ; i++ ) {
            //Parcours en inteur
            for (  int j = 0; j < COLONNE ; j++ ) {
                my_grid[i][j] = tmp[z];
                //On peut maintenant set chaque case avec les bon x et les bon y dont le digger
                my_grid[i][j]->setX(i);
                my_grid[i][j]->setY(j);
                z++;
            }
        }
    }
}

void
Level::initGrid() {
    //Calcul du nombre de bombe
    
    int nbrB = MINOBJ + ( rand() % ( MAXOBJ - MINOBJ ) );
    
    //Remplissage du tableau avec des bombe
    for (  int i = 1 ; i <= nbrB; i++ ) {
        my_grid[0][i] = new Bomb();
    }
    
    //On place les trésors en fonction du nombre de bomb
    for (  int i = nbrB +1 ; i < COLONNE ; i++ ) {
        my_grid[0][i] = new GoldCell();
    }
    
    //On rempli tout le reste avec des numéros
    for (  int i = 1; i < LIGNE; i++ ) {
        for (  int j = 0; j < COLONNE; j++ ) {
            my_grid[i][j] = new ValueCell();
        }
    }
    
    //On mélange tout cela
    shuffle();
}

//Gagner un level
void
Level::winLevel() {
    my_win = true;
    //On additionne le bonus au score courant
    my_score->addPoints( my_bonus );
    //On dit que l'on fait un nouveau niveau
    my_score->addSuccess();
    //On augmente le bonus du level
    my_bonus += 500;
    //On augmente la difficulté
    my_goal +=10;
    //On remet nos mouvements à 0
    my_currentMove = 0;
    //On reset le level
    reset();
}

void
Level::reset() {

    CellBase* temp = new Digger();
    
    while ( temp->getLife() != my_digger->getLife() ) {
        temp->lostLife();
    }
    
    
    //On delete tout !!
    for (  int i = 0; i < LIGNE; i++ ) {
        for (  int j = 0; j < COLONNE; j++ ) {
            delete my_grid[i][j];
        }
    }
    
    my_digger = new Digger();
    
    while ( temp->getLife() != my_digger->getLife() ) {
        my_digger->lostLife();
    }
    
    my_grid[0][0] = my_digger;
    delete temp;
    resetTime();
    initGrid();
    
}

/*===========================
 Les méthodes publics
 =============================*/
void
Level::resetWin() {
    my_win = false;
}

void Level::resetLose() {
    my_lose = false;
}

void
Level::lostLevel() {
    my_lose = true;
    //On fait perdre une vie au digger
    my_digger->lostLife();
    //On reset le score actuel
    my_score->resetScore();
    //On remet nos mouvements à 0
    my_currentMove = 0;
    //On reset le level
    reset();
}

int
Level::getGoal() const {
    return my_goal;
}

int
Level::getCurrentMove() const {
    return my_currentMove;
}

bool
Level::timeIsUp() const {
    time_t dateActuelle;
    time(&dateActuelle);
    if ( difftime( dateActuelle, my_depart ) > timeGoal )
        return true;
    else
        return false;
}

float
Level::leftTime() const {
    time_t dateActuelle;
    time(&dateActuelle);
    return ( timeGoal - difftime(dateActuelle, my_depart) );
}

void
Level::resetTime() {
    time(&my_depart);
}

CellBase* const
Level::getDigger() const {
    return my_digger;
}


bool
Level::isCellClickable( int click_x, int click_y ) const {
    
    /// Il faut vérifier si l'on ne sort pas du tableau
    if ( click_x >= 0 || click_x < LIGNE || click_y >= 0 || click_y < COLONNE ) {
        ///Il faut d'abord vérifier que la case est juste à côté de notre digger
        if ( ( ( click_x <= my_digger->getX() - 1 ) || ( click_x <= my_digger->getX() + 1 ) ) && ( ( click_y <= my_digger->getY() - 1 ) || ( click_y <= my_digger->getY() + 1 ) ) ) {
            ///On vérifie son type
            if ( dynamic_cast<ValueCell*>(my_grid[click_x][click_y]) != NULL || dynamic_cast<GoldCell*>(my_grid[click_x][click_y]) != NULL ) {
                return true;
            }
        }
    }
    return false;
}

const Grid&
Level::getGrid() const {
    return my_grid;
}


bool
Level::isDead() const {
    if ( my_digger->getLife() < 0 )
        return true;
    else
        return false;
}

bool
Level::win() const {
    return my_win;
}

bool
Level::lose() const {
    return my_lose;
}

/*===========================
 Les sucres
 =============================*/

void
Level::moveWest() {
    move( 0, -1 );
}

void
Level::moveEast() {
    move( 0, 1 );
}

void
Level::moveNorth() {
    move( -1, 0 );
}

void
Level::moveSouth() {
    move( 1, 0 );
}

void
Level::moveNorthEast() {
    move( -1, 1 );
}

void
Level::moveNorthWest() {
    move( -1, -1 );
}

void
Level::moveSouthWest() {
    move( 1, -1 );
}

void
Level::moveSouthEast() {
    move( 1, 1 );
}


