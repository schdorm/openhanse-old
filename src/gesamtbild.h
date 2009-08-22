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

#ifndef _gesamtbild_h
#define _gesamtbild_h

#include <QtCore/QList>

#include <QtGui/QWidget>
#include <QtGui/QFrame>

#include "waren.h"
#include "zeit.h"

#include "stadtklasse.h"
#include "kontorklasse.h"

#include "hauptfenster.h"
#include "handelsfenster.h"
#include "tabpanel.h"
#include "konsole.h"

#include "dataclass.h"

#include <QtGui/QKeyEvent>

#include <QtGui/QTabWidget>
#include <QtGui/QListWidget>

#include <QtGui/QComboBox>

class gesamtbild : public QWidget
{
Q_OBJECT
public:
//  QString binfilepath;
gesamtbild();
// void init(QString);
void spielfensteraufbau();

public slots:
// void mmenuslot();
void hauptmenu();
void spielmenu();

void execCommand(QString);

void aktivieren();

void startNewGame();

void handel();
void tradingFinished();
// void handelsupdate();
// void handelsaktion();
void produktion(int);

void landmenu();
void seemenu();

void zeitanzeige();

void speichern();
void speicherndialog();
void speichername(QString);
void speichern(QListWidgetItem*);

void laden(QListWidgetItem*);
void lademenu();

private:
bool spielbool;
bool aktiv;
int schwierigkeitsgrad;
DataClass *gamedata;

hauptfenster *hf;
handelsfenster *hwin;
SeaTabPanel *menupanel;
konsole *konsolenwidget;

QFrame *rahmen;
// QLabel *ware[const_warenanzahl];
// QLabel *fuellung;
// QLabel *taler;
// QTabWidget *menutabs;
// QWidget *tab[3];
QComboBox *schwierigkeitauswahl;
QPushButton *okbutton;
QString filename;			// fuer Savegame 

/*struct gebaudeklasse{			//Zusaetzliche, Nicht-Map-Standard-Gebaude, kommen in Liste
int id;
QString name;
QString datei;
int xpos;
int ypos;
quint8 menschen;
}; */

// struct kontorklasse{
// QString stadt;
// int id;
// Warenstruct waren;
// 
// };

// struct Warenstruct{
// int taler;
// quint16 ware[20];
// quint16 kapazitaet;
// quint16 fuellung;
// quint16 mengenbilanz;
// }lager[2];


/*struct schiffsklasse
{

};*/


// QList <stadtklasse> stadtliste;
// QList <schiffsklasse> schiffsliste;
// QList <gebaudeklasse> gebaudeliste;
// QList <kontorklasse> kontorliste;

protected:
	void keyPressEvent(QKeyEvent *event);
};

// #include <QDebug>
// QString binFileName(QString filename_param)
// {
// 
// 	static QString binfilename;
// 	if(!filename_param.isEmpty())
// 	{
// 		binfilename = filename_param;
// 		qWarning() << "FN set to: " << filename_param;
// 		return 0;
// 	}
// 	else
// 		return binfilename;
// }
#endif
