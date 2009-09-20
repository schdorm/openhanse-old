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
#ifndef _handelsfenster_h
#define _handelsfenster_h

#include <QtGui/QWidget>
// #include <QtGui/QAction>
// #include <QtGui/QApplication>
// #include <QtGui/QButtonGroup>
// #include <QtGui/QFrame>
// #include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QSpacerItem>

#include "waren.h"
// #include "dataclass.h"

// const int const_warenanzahl = 30;

class handelsfenster : public QWidget
{
Q_OBJECT

// signals:
// void hmoeglich(bool);

public:
handelsfenster();
~handelsfenster();
void setGameData(/*DataClass **/);

void setStorage(const Goods &, int);

// DataClass *gamedata;


QPushButton *handelsbutton;
QPushButton *exit;

// void sethandelsbutton(bool enabled)
// {
// handelsbutton->setEnabled(enabled);
// // emit hmoeglich(enabled);
// }

private slots:
void buttonHandler(int);
void handelsaktion();
void updateWidget();

private:
Goods storage[2];			// Storage1 -> city/city/kontor; storage0 -> ship / Kontor/ship;
// Warenstruct storage2;


QButtonGroup *htypgroup;
QRadioButton *htyp[3];		//Handelstyp: Schiff mit Stadt, Kontor mit Stadt, Transfer Kontor->Schiff

QList<QLabel *> Storage0LabelList;

QList<QLabel *> Storage1LabelList;

QList<QLabel *> PriceLabelList;

QList< QLabel *> ProceedsLabelList;


QList<QSpinBox *> BuySpinboxList;

QList<QSpinBox *> SellSpinboxList;


// QLabel *warenmenge[const_warenanzahl];		//Angebot || city-> goods
// QLabel *preis[const_warenanzahl];		// price
// QLabel *vorrat[const_warenanzahl];		// eigene Waren (Lager 0) || goods <- storage 0
// QLabel *erloes[const_warenanzahl];		//

QLabel  *m_TradeProceedsTextLabel, *m_TradeProceedsLabel;
/* *gesamtpreis, *gesamterloes,*/

quint8 typ;			//Letzter Handelstyp fuer Aktualisierung: -> Resourcensparend

// QSpinBox *kaufmenge[const_warenanzahl];
// QSpinBox *verkaufsmenge[const_warenanzahl];

};


#endif
