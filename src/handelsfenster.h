/***************************************************************************
 *   Copyright (C) 2009 by Christian Doerffel   *
 *   christian.doerffel@googlemail.com   *
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

// const int const_warenanzahl = 30;

class handelsfenster : public QWidget
{
Q_OBJECT

signals:
void hmoeglich(bool);

public:
handelsfenster();

QButtonGroup *htypgroup;
QRadioButton *htyp[3];		//Handelstyp: Schiff mit Stadt, Kontor mit Stadt, Transfer Kontor->Schiff

QLabel *warenmenge[const_warenanzahl];
QLabel *preis[const_warenanzahl];
QLabel *vorrat[const_warenanzahl];
QLabel *erloes[const_warenanzahl];

QLabel /* *gesamtpreis, *gesamterloes,*/ *handelsbilanz, *umsatz;

quint8 typ;			//Letzter Handelstyp fuer Aktualisierung: -> Resourcensparend

QSpinBox *kaufmenge[const_warenanzahl];
QSpinBox *verkaufsmenge[const_warenanzahl];
QPushButton *handelsbutton;
QPushButton *exit;

void sethandelsbutton(bool enabled)
{
handelsbutton->setEnabled(enabled);
emit hmoeglich(enabled);
}


};


#endif
