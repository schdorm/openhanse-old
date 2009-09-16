/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel                              *
 *   schdorm@googlemail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _waren_h
#define _waren_h


const int const_warenanzahl = 30;
const int const_waffen = 15;

const int const_grundpreis[const_warenanzahl] = {50, 95, 84, 67, 10000, 350, 950, 168, 270, 400, 107, 60, 130, 210, 30, 50, 300, 190, 3800, 5100, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

struct Warenstruct{
int taler;
int ware[const_warenanzahl];
int waffe[const_waffen];
int kapazitaet;
int fuellung;

int mengenbilanz;				//Fuer Handel
};

enum Ware
{
W_Baumstamme,
W_Holzbretter,
W_Holzkohle,
W_Pech,
W_Steine,
W_Eisenerz,
W_Schmiedeeisen,
W_Werkzeuge,
W_Leder,
W_Wolle,
W_Stoffe,
W_Hanf,
_platzhalter12_,
_platzhalter13_,
_platzhalter14_,

W_Bier,
W_Getreide,
W_Brot,
W_Salz,
W_Fleisch,
W_Fisch,
W_Kase,
W_Wein,
W_Gewurze,
W_Gold,
W_Schmuck,
_platzhalter26_gold_,
_platzhalter27_gold_,
_platzhalter28_gold_,
_platzhalter29_gold_
};

enum weapons{
wp_entermesser,
wp_kanone,
wp_balliste,
wp_blide,

wp_schwert,
wp_dolch,
wp_streitaxt,
wp_lanze,

wp_bogen,
wp_armbrust,
wp_muskete,

wp_l_armor,
wp_h_armor,

};




#endif
