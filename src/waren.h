/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel   *
 *   schdorm@googlemail.com   *
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
const int const_waffen = 10;

struct Warenstruct{
int taler;
qint16 ware[const_warenanzahl];
qint16 waffe[const_waffen];
qint32 kapazitaet;
qint16 fuellung;

qint16 mengenbilanz;				//Fuer Handel
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

enum waffen{
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
