//
//  Constantes.h
//  purpurudigger
//
//  Created by Ananas-Mac on 18/02/2014.
//  Copyright (c) 2014 Ananas-Mac. All rights reserved.
//

#ifndef purpurudigger_Constantes_h
#define purpurudigger_Constantes_h

const unsigned long COLONNE = 19;
const unsigned long LIGNE = 19;
const unsigned long MINVAL = 1;
const unsigned long MAXVAL = 6;
const unsigned long MINOBJ = 8;
const unsigned long MAXOBJ = 10;
const unsigned long MINVALB = 10;
const unsigned long MAXVALB = 100;

const std::string FILEBESTSCORE = "bestScores.txt";

enum Language {
    français,
    english,
    deutsch,
    español,
    italiano
};

enum Message {
    choice,
    
    move, nwest, north, neast, west, east, swest, south, seast, stop,
    score, level, global, current, goal, step, life, position,
    winlevel, looselevel, loosegame, name,
    
    by
};

#endif
