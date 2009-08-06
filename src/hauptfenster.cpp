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
const int AKTUALISIERUNGSINTERVALL = 25;
const int WENDEGESCHWINDIGKEIT = 10;
const int BESCHLEUNIGUNG = 50;
const int WINDVERAENDERUNG = 30;
// const int tageslaenge = 1000;

// const int taglaenge = 

// #define AKTUALISIERUNGSINTERVALL 40
// #define WENDEGESCHWINDIGKEIT 10
// #define BESCHLEUNIGUNG 50
// #define WINDVERAENDERUNG 30
//Beschleunigung -> Traegheit: bei groesseren Werten reagiert das Schiff langsamer
// #define PRODUKTION 1000

// #define _RELEASE_


#include "hauptfenster.h"
#include "schiff.h"

#include <math.h>
// #include <time.h>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>

#include <QtGui/QImage>
#include <QtGui/QBrush>



#include <QtCore/QTimer>

#include <QtGui/QKeyEvent>

#ifndef _RELEASE_
#include <QtGui/QVBoxLayout>
#include <QtCore/QtDebug>
#endif

#include <QtGui/QScrollBar>
#include <QtGui/QPushButton>
// #include <QtGui/QPlainTextEdit>
// #include <QtGui/QLineEdit>
// #include <QtCore/QFile>

#include "konsole.h"

hauptfenster::hauptfenster()
{



	activeship.init();

	qWarning() << "Schiffstyp" <<activeship.schiffstyp;

	anbord=true;
	pause = false;
// 	uhra=false;
	tageslaenge = 2000;
	tag = 0;
	stunde = 0;
	minute = 0;

	int randint = rand()%7;
	windrichtung = randint;
	windgeschwindigkeit = rand() %30 +5;
// 	qWarning() << "clear";
// 	szene[as = new QGraphicsScene();
// 	aszene=1;
					// 	szene[aszene]= new QGraphicsScene();
	szene = new QGraphicsScene();
// 	qWarning() << "Szene:" <<aszene;


// 	kartegeladen=true;
// 	setScene(szene);
// 	setSceneRect(20,20,mapprops.breite-40, mapprops.hoehe-40);


// 	bewegung = new QTimer;
// 	bewegung->start(AKTUALISIERUNGSINTERVALL);
// 	/*QObject::*/connect(bewegung,SIGNAL(timeout()),this,SLOT(aktualisieren()));
	setFocus();
// 	centerOn(testschiff->x(),testschiff->y());
// 	centerOn(testschiff);
// 	activeship.schiffbreite = testschiff->boundingRect().width();
// 	activeship.schifflange = testschiff->boundingRect().height();
	activeship.schiffsname = tr("Seeadler");

#ifndef _RELEASE_

	QWidget *status = new QWidget();

	knoten = new QLabel();
	sollknoten = new QLabel();
	segel = new QLabel();
	sollsegel = new QLabel();
	solldir = new QLabel();
	dir = new QLabel();
	steuerdir = new QLabel();
	sollsteuerdir = new QLabel();
	winddir = new QLabel();
 	windv = new QLabel();
	segeldir = new QLabel();
	acclabel = new QLabel();

	fokussieren = new QCheckBox();

	fokussieren->setChecked(true);

	QLabel *fok = new QLabel("Auf Schiff fokussieren");

	knoten -> setText (QString("V:%1").arg(activeship.attribute.geschwindigkeit));
	sollknoten -> setText(QString("SollV: %1").arg(activeship.attribute.sollgeschwindigkeit));

	segel->setText(QString("SegelFlaeche: %1").arg(activeship.attribute.prozentgesetzteSegel));
	sollsegel->setText(QString("SollSegelFl: %1").arg(activeship.attribute.sollprozentgesetzteSegel));
	segeldir -> setText(QString("SegelDir: %1").arg(activeship.attribute.segelausrichtung));

	solldir -> setText(QString("SollDir %1").arg(activeship.attribute.sollausrichtung));
	dir -> setText(QString("Dir %1").arg(activeship.attribute.ausrichtung));
	steuerdir -> setText(QString("SteuerDir: %1").arg(activeship.attribute.steuerruderausrichtung));
	sollsteuerdir -> setText(QString("SollSteuerDir: %1").arg(activeship.attribute.sollsteuerruderausrichtung));

 	winddir -> setText(QString("WindDir: %1").arg(windrichtung));
	windv -> setText(QString("WindV: %1").arg(windgeschwindigkeit));
	acclabel->setText(QString("Beschleunigung:"));



	steuerdir->setFixedWidth(200);
	sollsteuerdir->setFixedWidth(200);
	QVBoxLayout layout;
	layout.addWidget(knoten);
	layout.addWidget(sollknoten);

	layout.addWidget(sollsegel);
	layout.addWidget(segel);
	layout.addWidget(segeldir);

	layout.addWidget(solldir);
	layout.addWidget(dir);
	layout.addWidget(steuerdir);
	layout.addWidget(sollsteuerdir);

	layout.addWidget(winddir);
	layout.addWidget(windv);
	layout.addWidget(acclabel);


	layout.addWidget(fokussieren);
	layout.addWidget(fok);

	status->setLayout(&layout);
	status->setParent(this,Qt::Tool);
	status->move(1100,400);
	status->show();
#endif
}

void hauptfenster::starttimer()
{
bewegung= new QTimer(this);

bewegung->start(AKTUALISIERUNGSINTERVALL);
connect(bewegung,SIGNAL(timeout()),this,SLOT(aktualisieren()));
}

void hauptfenster::mousePressEvent(QMouseEvent *event) /// MAUS-Steuerungssachen
{
// 	qWarning() << "geklickt";
	const float scale = transform().m11();
// 	if(anbord==false && pause==false)
	{
// 		qWarning() << "geklickt, keine Pause usw.";

		QGraphicsItem *ort = scene()->itemAt((event->x() + horizontalScrollBar()->value())/scale, (event->y() + verticalScrollBar()->value())/scale);
		if(ort==0)
		{
#ifndef _RELEASE_
			qWarning() << "(Leerer Platz)";
#endif
		}

		else
		{
			if(ort->toolTip() == "Name")
			{
#ifndef _RELEASE_
			qWarning() << "Item Name getroffen";
#endif
			}

			if(ort->data(0).toInt() == object_type_market)
			{
#ifndef _RELEASE_
			qWarning() << "Man begibt sich auf den Markt ...";
#endif
			emit handel();
			}

			if(ort->data(0).toInt() == object_type_townhall)
			{
			}

			if(ort->data(0).toInt() == object_type_church)
			{
			}

			if(ort->data(0).toInt() == object_type_port)
			{
			}

			if(ort->data(0).toInt() == object_type_office)
			{
			}

			if(ort->data(0).toInt() == object_type_bank)
			{
			}

			if(ort->data(0).toInt() == object_type_tavern)
			{
				emit enterBuilding(object_type_tavern);
			}

			if(ort->toolTip() == "Uhr" || ort->toolTip() == "grosser Zeiger" || ort->toolTip() == "kleiner Zeiger")
			{
#ifndef _RELEASE_
			qWarning() << "Zeit" << tag << stunde << minute;
#endif
			emit zeitsig();
			slotpause();
// 
// 			QWidget zeitw(this);
// 			QLabel anzeige(tr("Zeit: %1:%2").arg(stunde, minute),&zeitw);
// 			QPushButton ok("Ok",&zeitw);
// 			ok. move(50,50);
// 			zeitw.setGeometry(50,50,200,100);
// 			zeitw.show();
// 			zeitw.raise();
// 			connect(&ok, SIGNAL(clicked()),this,SLOT(slotpause()));
// 			connect(&ok, SIGNAL(clicked()),&zeitw,SLOT(close()));
			}

#ifndef _RELEASE_
			 qWarning() << testschiff->pos() << event->posF() << (testschiff->x() - event->x()) << " \t" << testschiff->y() - event->y() << "\nVBar-Value:" <<verticalScrollBar()->value();
#endif
		}
	}
	if(anbord==true && pause==false)
	{
	int x = (event->x() + horizontalScrollBar()->value())/scale;
	int y = (event->y() + verticalScrollBar()->value())/scale;

	int mposx = int(testschiff->x() + cos(activeship.attribute.ausrichtung) * activeship.schiffbreite/2 + sin(activeship.attribute.ausrichtung)* activeship.schifflange / 2);

	int mposy = int(testschiff->y() + cos(activeship.attribute.ausrichtung) * activeship.schifflange/2 + sin(activeship.attribute.ausrichtung) * activeship.schiffbreite /2);

#ifndef _RELEASE_
	qWarning() << "Maussteuerung" << x << y << mposx << mposy;
#endif

	if(x > mposx &&  y < mposy)			// Klick im "I. Quadrant" (Schiff -> KO [O(0|0)] )
							//(Koordinatensystem: gespiegelte Y-Achse ...)
	{
		int diffx = (x - mposx);
// 		int diffy = int(testschiff->y() - (event->y() + verticalScrollBar()->value()));
		int diffy = (mposy - y);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffy/klickabstand);

		activeship.attribute.sollausrichtung = 3*M_PI/2 + winkel;

#ifndef _RELEASE_
		qWarning() << "I" << winkel << "Ausrichtung" << activeship.attribute.sollausrichtung <<"Abstand:" <<klickabstand;
#endif
	}

	if(x < mposx && y < mposy)			// Klick im II. Quadrant
	{
		int diffx = (mposx - x);
		int diffy = (mposy - y);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffx/klickabstand);
// #ifndef _RELEASE_
// 		qWarning() << "II" << winkel << klickabstand;
// #endif
		activeship.attribute.sollausrichtung = winkel;

#ifndef _RELEASE_
		qWarning() << "II" << winkel << "Ausrichtung" << activeship.attribute.sollausrichtung <<"Abstand:" <<klickabstand;
#endif
	}

	if(x < mposx && y > mposy)			// Klick im III. Quadrant
	{
		int diffx = (mposx - x);
		int diffy = (y - mposy);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffy/klickabstand);
// #ifndef _RELEASE_
// 		qWarning() << "III" << winkel << klickabstand;
// #endif
		activeship.attribute.sollausrichtung = M_PI/2 + winkel;

#ifndef _RELEASE_
		qWarning() << "III" << winkel << "Ausrichtung" << activeship.attribute.sollausrichtung <<"Abstand:" <<klickabstand;
#endif
	}

	if(x > mposx && y > mposy)			// Klick im IV. Quadrant
	{
		int diffx = (x - mposx);
		int diffy = (y - mposy);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffx/klickabstand);
// #ifndef _RELEASE_
// 		qWarning() << "IV" << winkel << klickabstand;
// #endif
		activeship.attribute.sollausrichtung = M_PI + winkel;
#ifndef _RELEASE_
		qWarning() << "IV" << winkel << "Ausrichtung" << activeship.attribute.sollausrichtung <<"Abstand:" <<klickabstand;
#endif
	}
	tastatur=false;
	}
}

void hauptfenster::keyEventWeiterleitung(QKeyEvent *event)
{
keyPressEvent(event);
}


void hauptfenster::keyPressEvent(QKeyEvent *event)
{
if(event->key() == Qt::Key_W && activeship.attribute.sollprozentgesetzteSegel < 1)
{
activeship.attribute.sollprozentgesetzteSegel = activeship.attribute.sollprozentgesetzteSegel + 0.2;

#ifndef _RELEASE_
qWarning() << "Segel gesetzt:" << activeship.attribute.sollprozentgesetzteSegel;
#endif

}
if(event->key() == Qt::Key_S  ) //&& 
{

if(event->modifiers() == Qt::NoModifier && activeship.attribute.sollprozentgesetzteSegel > 0)
	{
		activeship.attribute.sollprozentgesetzteSegel = activeship.attribute.sollprozentgesetzteSegel - 0.2;

#ifndef _RELEASE_
		qWarning() << "Segel gerefft:" << activeship.attribute.sollprozentgesetzteSegel;
#endif

		if(activeship.attribute.sollprozentgesetzteSegel<0.2)
		{
			activeship.attribute.sollprozentgesetzteSegel=0;
		}
	}

if(event->modifiers() == Qt::ControlModifier)
{
emit savesig();
}
}

if(event->text() == "a" && activeship.attribute.sollsteuerruderausrichtung < 0.004)
{
	activeship.attribute.sollsteuerruderausrichtung = activeship.attribute.sollsteuerruderausrichtung + 0.0002;
	tastatur = true;
// 	activeship.attribute.sollausrichtung = activeship.attribute.ausrichtung;
// 	if(activeship.attribute.steuerruderausrichtung < 0.0025 && activeship.attribute.steuerruderausrichtung > -0.0025)
// 	{
// 		activeship.attribute.steuerruderausrichtung=0;
// 	}
#ifndef _RELEASE_
	qWarning () <<"Steuer bewegt:" <<activeship.attribute.sollsteuerruderausrichtung;
#endif
// 	qWarning () << activeship.attribute.sollsteuerruderausrichtung;
}

if(event->text() == "d" && activeship.attribute.sollsteuerruderausrichtung > -0.004)
{
	activeship.attribute.sollsteuerruderausrichtung = activeship.attribute.sollsteuerruderausrichtung - 0.0002;
// 	activeship.attribute.sollausrichtung = activeship.attribute.ausrichtung;
	tastatur=true;

#ifndef _RELEASE_
	qWarning () <<"Steuer bewegt:" <<activeship.attribute.sollsteuerruderausrichtung;
#endif

}

if(event->text() == "A" && activeship.attribute.segelausrichtung <= 1.5)
{
	activeship.attribute.segelausrichtung = activeship.attribute.segelausrichtung + 0.02;
// 	activeship.attribute.sollausrichtung = activeship.attribute.ausrichtung;
// 	tastatur=true;
// 	qWarning () << activeship.attribute.sollsteuerruderausrichtung;

#ifndef _RELEASE_
	segeldir -> setText(QString("SegelDir: %1").arg(activeship.attribute.segelausrichtung));
#endif

}

if(event->text() == "D" && activeship.attribute.segelausrichtung >= -1.5)
{
	activeship.attribute.segelausrichtung = activeship.attribute.segelausrichtung - 0.02;
// 	activeship.attribute.sollausrichtung = activeship.attribute.ausrichtung;
// 	tastatur=true;
// 	qWarning () << activeship.attribute.sollsteuerruderausrichtung;
#ifndef _RELEASE_

	segeldir -> setText(QString("SegelDir: %1").arg(activeship.attribute.segelausrichtung));
#endif

}



if(activeship.attribute.segelausrichtung <0.01 && activeship.attribute.segelausrichtung > -0.01)
{activeship.attribute.segelausrichtung =0;
}

if(activeship.attribute.sollsteuerruderausrichtung < 0.0001 && activeship.attribute.sollsteuerruderausrichtung > -0.0001)
{
	activeship.attribute.sollsteuerruderausrichtung=0;
}
if(activeship.attribute.sollsteuerruderausrichtung < -0.05)
activeship.attribute.sollsteuerruderausrichtung = -0.2;

if(activeship.attribute.sollsteuerruderausrichtung > 0.05)
activeship.attribute.sollsteuerruderausrichtung = 0.2;

#ifndef _RELEASE_

// qWarning () << activeship.attribute.sollgeschwindigkeit << activeship.attribute.steuerruderausrichtung;
sollsegel->setText(QString("SollSegelFl: %1").arg(activeship.attribute.sollprozentgesetzteSegel));
sollsteuerdir -> setText(QString("SollSteuerDir: %1").arg(activeship.attribute.sollsteuerruderausrichtung));
#endif

	if(event->key() == Qt::Key_P)
	{

#ifndef _RELEASE_
	qWarning() << "Pause" << pause;
#endif
	slotpause();
// 		static bool pause;
// 		if(!pause)
// 		{
// 			bewegung->stop();
// 		}
// 		if(pause)
// 		{
// 			bewegung->start(AKTUALISIERUNGSINTERVALL);
// 		}
// 
// 		if(bewegung->isActive())
// 		{
// 			pause=false;
// 		}
// 		if(!bewegung->isActive())
// 		{
// 			pause=true;
// 		}

	}
#ifndef _RELEASE_
	if(event->key() == Qt::Key_L)
	{
		windgeschwindigkeit++;
	}
	if(event->key() == Qt::Key_K)
	{
		windgeschwindigkeit--;
	}
	if(event->key() == Qt::Key_Left)
	{
		activeship.attribute.ausrichtung += 0.2;
		if(activeship.attribute.ausrichtung > 2 * M_PI)
		{
		activeship.attribute.ausrichtung = 0.1;
		}
	}
	if(event->key() == Qt::Key_Right)
	{
	activeship.attribute.ausrichtung -= 0.2;
		if(activeship.attribute.ausrichtung < 0 )
		{
		activeship.attribute.ausrichtung = 2 * M_PI - 0.1;
		}
	}

	if(event->text() == "M" )
	{
	activeship.Ladung.taler +=1000;
	}
	if(event->text() == "B" ||event->key() == Qt::Key_Up )
	{
	activeship.attribute.geschwindigkeit +=20;
	}

	if(event->text() == "b" || event->key() == Qt::Key_Down)
	{
	activeship.attribute.geschwindigkeit--;
	}


#endif
	if(event->text() =="Q" || (event->key() == Qt::Key_Q && event->modifiers() == Qt::ControlModifier))
	{
	close();
	deleteLater();
	}


	if(event->key() == Qt::Key_Escape)
	{
	emit menusig();
// 	qWarning() << "Menusig";
	}



	static int zoomlvl;
	if(event->key() == Qt::Key_Minus /*&& zoomlvl <2*/)
	{
// 		scale(0.5,0.5);
		scale(0.8,0.8);
		zoomlvl++;
	}
	if(event->key() == Qt::Key_Plus /*&& zoomlvl >0*/)
	{
// 		scale(2,2);
		scale(1.25,1.25);
		zoomlvl--;
	}
	
	if(event->key() == Qt::Key_AsciiCircum)
	{
	qWarning() << "Open Console!";

	emit sig_konsole();
//  	QWidget *consoleframe = new QWidget (nativeParentWidget(),Qt::Popup);
// 	konsole *konsolepanel = new konsole();
// 	konsolepanel->setParent(consoleframe);
// 	consoleframe->resize(nativeParentWidget()->width(), height()-200);
// 	konsolepanel->resize(nativeParentWidget()->width(), height());

// 	QPlainTextEdit *console = new QPlainTextEdit(consoleframe);
// 	console->resize(nativeParentWidget()->width(), height()-200);
// // 	console->setPlainText(QString("Hello World!"));
// 	console->move(0,0);
// 	console->setReadOnly(true);
// 	
// 	QLineEdit *commandline = new QLineEdit(consoleframe);
// // 	commandline
// 	
// 	QVBoxLayout clayout(consoleframe);
// 	clayout.addWidget(console);
// 	clayout.addWidget(commandline);
// 	
// 	consoleframe->show();
// 	connect(commandline, SIGNAL(textEdited(QString)), this, SLOT(setConsoleBuffer(QString)));
// 	
// 	connect(commandline, SIGNAL(returnPressed()), this, SLOT(execConsoleCommand()));
// 	connect(commandline, SIGNAL(returnPressed()), commandline, SLOT(clear()));
	}
}



void hauptfenster::slotpause()
{
		if(!pause)
		{
			bewegung->stop();
		}
		if(pause)
		{
			bewegung->start(AKTUALISIERUNGSINTERVALL);
		}

		if(bewegung->isActive())
		{
			pause=false;
		}
		if(!bewegung->isActive())
		{
			pause=true;
		}
}

void hauptfenster::endePause()
{
		if(!bewegung->isActive())
		{
			bewegung->start(AKTUALISIERUNGSINTERVALL);
			pause=false;
		}
}

void hauptfenster::startPause()
{
		if(bewegung->isActive())
		{
			bewegung->stop();
			pause=true;
		}
}


void hauptfenster::segelsetzen(int i)
{
float n = i;
activeship.attribute.sollprozentgesetzteSegel = n/5;
#ifndef _RELEASE_
qWarning() << "sollgesetzteSegel:" << activeship.attribute.sollprozentgesetzteSegel;
#endif
}



void hauptfenster::aktualisieren()
{

durchlauf++;
// if(durchlauf % (tageslaenge/1440))

// if(false)
// if(durchlauf%2 == 0 && uhra)
{

minute += tageslaenge/1440;
if(minute>=60)
{
minute = 0;
stunde ++;
}
// stunde += tageslaenge/24;

if(stunde >=24)
{
tag++;
stunde=0;
}

// QList <QGraphicsItem*> sliste = szene[aszene]->items();
if(uhr){
QList <QGraphicsItem*> sliste = szene->items();

for(QList <QGraphicsItem*>::iterator it = sliste.begin(); it < sliste.end(); ++it)
{
QGraphicsItem *handler = *it;
if(handler->toolTip() == "grosser Zeiger")
{
// 	static int minute; minute ++;
	handler->resetTransform();
	QTransform t;
	const int w = ((handler->boundingRect().width()/2));
	const int h = int(handler->boundingRect().height()-1.8);

	t.translate( w, h );
	t.rotateRadians(minute * M_PI / 30);
	t.translate( -w, -h );
	handler->setTransform( t );
	*it = handler;
}
if(handler->toolTip() == "kleiner Zeiger")
{
// 	static int minute;

	handler->resetTransform();
	QTransform t;
	const int w = int((handler->boundingRect().width()/2));
	const int h = int(handler->boundingRect().height()-1.8);

	t.translate( w, h );
	t.rotateRadians((minute/60 + stunde)* M_PI /6);
// 	t.rotateRadians(minute * M_PI / 150);
	t.translate( -w, -h );
	handler->setTransform( t );
	*it = handler;
}
}
}}


// qWarning() << "Aktualisieren";
// static int durchlauf;	//Zaehlvariable fuer Ruder bzw. Geschwindigkeit -> Schiff ist traege und wird nur langsam schneller / lenkt langsam ----> jetzt Klassenvariable

/////////////WIND + WOLKEN/////////////////////////////



if(durchlauf > 2000000000)	// 4 000 000 000
{
durchlauf=0;
}

if(durchlauf % tageslaenge == 0)
{
emit Aktualisierung(durchlauf);
// qWarning() << "Aktualisierungssignal gesendet";
}

if(durchlauf % WINDVERAENDERUNG ==0)
{
// qWarning() << "Windzeugs";
windsetzen();
#ifndef _RELEASE_

	winddir -> setText(QString("WindDir: %1").arg(windrichtung));
	windv -> setText(QString("WindV: %1").arg(windgeschwindigkeit));
#endif
}
// qWarning() << "Vor Wolkenzeugs";

// qWarning()<< "KGL: WL: Eintraege" << wolkenliste.size();
if(windgeschwindigkeit > 0)
{
	if(durchlauf%10==0 )					//Bewegung mit Verschiebung
	{
		foreach(QGraphicsItem *wolkenit, wolkenliste)
		{
			qint8 rx = (rand() % 3)-1;
			float xverschiebung=rx;
			xverschiebung = xverschiebung /10;

			qint8 ry = (rand() % 3)-1;
			float yverschiebung = ry;
			yverschiebung = yverschiebung/10;

			wolkenit->moveBy(-(windgeschwindigkeit * sin(windrichtung))/10 + xverschiebung, -(windgeschwindigkeit * cos(windrichtung))/10 + yverschiebung);

			if(wolkenit->x() <10 )
			{
// wolke->setPos(3800 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(mapprops.breite - 10, (rand()%(mapprops.hoehe - 200)) + 50);
			}
			if(wolkenit->x() > mapprops.breite - 10 )
			{
// wolke->setPos(205 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(10, (rand()%(mapprops.hoehe - 200)) + 50);
			}
			if(wolkenit->y() <10 )
			{
				wolkenit->setPos((rand() % (mapprops.breite - 200)) + 50, mapprops.hoehe - 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 2800 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
			if(wolkenit->y() > mapprops.hoehe - 10 )
			{
				wolkenit->setPos((rand() % (mapprops.breite - 200)) + 50, 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 205 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
		}
	}
	else						//Wolkenbewegung ohne Verschiebung
	{
		foreach(QGraphicsItem *wolkenit, wolkenliste)
		{
			wolkenit->moveBy(-(windgeschwindigkeit * sin(windrichtung))/10, -(windgeschwindigkeit * cos(windrichtung))/10);

			if(wolkenit->x() <10 )
			{
// wolke->setPos(3800 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(mapprops.breite - 10, (rand()%(mapprops.hoehe - 200)) + 50);
			}
			if(wolkenit->x() > mapprops.breite - 10 )
			{
// wolke->setPos(205 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(10, (rand()%(mapprops.hoehe - 200)) + 50);
			}
			if(wolkenit->y() <10 )
			{
				wolkenit->setPos((rand() % (mapprops.breite - 200)) + 50, mapprops.hoehe - 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 2800 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
			if(wolkenit->y() > mapprops.hoehe - 10 )
			{
				wolkenit->setPos((rand() % (mapprops.breite - 200)) + 50, 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 205 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
		}
	}



}

// qWarning() << "Ende Wolkenzeugs";


///////SCHIFF////////////////////////////////////////
//falls v>0 / geplant: v>0
// qWarning() << "IfAnbord";
if(anbord)
{
// qWarning() << "Beginn Schiffszeug";
// if(activeship.attribute.geschwindigkeit > 0 || activeship.attribute.sollprozentgesetzteSegel > 0 || activeship.attribute.prozentgesetzteSegel > 0 || windgeschwindigkeit > 0)
{
// qWarning() << "Vor Bewegungsbeschreibung";
bewegungsbeschreibung();
// qWarning() << "Nach Bewegungsbeschreibung";



/////////////////Fahren

// 	testschiff->setPos(testschiff->x() - (activeship.attribute.geschwindigkeit * sin(activeship.attribute.ausrichtung))/10, testschiff->y() - (activeship.attribute.geschwindigkeit * cos(activeship.attribute.ausrichtung))/10);
	bool ortswechsel = false;

	if(activeship.attribute.geschwindigkeit>0)
	{
// 		qWarning() << "Schiffsbewegung";
		testschiff->moveBy(- (activeship.attribute.geschwindigkeit * sin(activeship.attribute.ausrichtung))/10, - (activeship.attribute.geschwindigkeit * cos(activeship.attribute.ausrichtung))/10);
		ortswechsel = true;
		activeship.attribute.xpos = int(testschiff->x());
		activeship.attribute.ypos = int(testschiff->y());
	}

 	const int w = activeship.schiffbreite/2;
 	const int h = activeship.schifflange/2;

	static float richtung;
	if(richtung !=  activeship.attribute.ausrichtung)
	{
  	richtung = activeship.attribute.ausrichtung;
							 	testschiff->resetTransform();
 								QTransform t;
// 	const int w = testschiff->boundingRect().width()/2;
// 	const int h = testschiff->boundingRect().height()/2;

//  	const int w = activeship.schiffbreite/2;
//  	const int h = activeship.schifflange/2;

								t.translate( w, h );
						t.rotateRadians(-activeship.attribute.ausrichtung);
								t.translate( -w, -h );

// const int schiffhohe = testschiff->boundingRect().height();
// const int schifflange = testschiff->boundingRect().width();




								testschiff->setTransform( t );
	ortswechsel = true;

// 	activeship.attribute.xposm = testschiff->x() + (cos(activeship.attribute.ausrichtung) * schifflange)/2 + (sin(activeship.attribute.ausrichtung) * schiffhohe)/2;
// 	activeship.attribute.yposm = testschiff->y() + (cos(activeship.attribute.ausrichtung) * schiffhohe)/2 + (sin(activeship.attribute.ausrichtung) * schifflange)/2;


 	}


//////////////////////Landkollossion
/////////////////Schiffbar?
// qWarning() << "Schiffbar?";


 if(ortswechsel)
 {
 	activeship.attribute.xposm = testschiff->x() + w;
	activeship.attribute.yposm = testschiff->y() + h;

//  	QGraphicsItem *blah = szene->addPixmap(QPixmap(":img/sonstige/rot.png"));
//  	blah -> setPos(activeship.attribute.xposm, activeship.attribute.yposm);
//  	blah->setZValue(2);

// 	activeship.attribute.xposm = testschiff->x() /*+  (cos(activeship.attribute.ausrichtung) * schifflange)/2 - (sin(activeship.attribute.ausrichtung) * schiffhohe)/2*/;
// 	activeship.attribute.yposm = testschiff->y() /*+ (cos(activeship.attribute.ausrichtung) * schiffhohe)/2 - (sin(activeship.attribute.ausrichtung) * schifflange)/2*/;

// 	QGraphicsItem *blah = szene[aszene]->addPixmap(QPixmap(":img/objekte/stein01.png"));
// 	blah -> setPos(activeship.attribute.xposm, activeship.attribute.yposm);
// 	blah->setZValue(2);

	float bremsfaktor = 0;

// QList <QGraphicsItem*> collliste = testschiff->collidingItems();	//Kollisionsliste

// if(/*!collliste.isEmpty() &&*/ durchlauf % 5 ==0)
// {
// bool found = false;
// qWarning() << "Not Empty" << collliste.size() << landobjektliste.size();
	QGraphicsPixmapItem *landgi = testschiff;
	int iz = 0;
	for(QList <QGraphicsPixmapItem*>::iterator it = landobjektliste.begin(); it < landobjektliste.end(); ++it)
	{
		iz ++;
		landgi = *it;
		if(schiffskollision(landgi))
		{
			static int ibrprufg[3];			//Ueberpruefungszahl: Neubelegung der Bilder erforderlich?
// int eolx = (testschiff->x() +  (cos(activeship.attribute.ausrichtung) * schifflange)/2 + (sin(activeship.attribute.ausrichtung) * schiffhohe)/2 - landgi->x()),
// eoly = testschiff->y() + (cos(activeship.attribute.ausrichtung) * schiffhohe)/2 + (sin(activeship.attribute.ausrichtung) * schifflange)/2 - landgi->y();
			int eolx = activeship.attribute.xposm - landgi->x(),
			eoly = activeship.attribute.yposm - landgi->y();

			int arrakt;				// Ueberpruefung: aktives Arrayfeld
			if(ibrprufg[0] != iz)
			{
				if(ibrprufg[1] != iz)
				{
					if(ibrprufg[2] != iz)
					{
						static int arrind;
// 						qWarning() << "Neubelegung" << iz << ibrprufg;
						collimg[arrind] = landgi->pixmap().toImage();
						ibrprufg[arrind] = iz;
						arrakt = arrind;
						arrind++;
						if(arrind > 2)
						{
							arrind = 0;
						}
					}
					else
						arrakt = 2;
				}
				else
					arrakt = 1;
			}
			else
				arrakt = 0;
			if(eolx > 0 && eolx < collimg[arrakt].width() && eoly >= 0 && eoly < collimg[arrakt].height())
			{
			float tempfloat = qAlpha(collimg[arrakt].pixel(eolx, eoly));
			if(tempfloat > bremsfaktor)
			{
				bremsfaktor = tempfloat;
				qWarning() << bremsfaktor;
			}
			}

		}
	}
	if(bremsfaktor > 3)
	{
	bremsfaktor = bremsfaktor/255;
	qWarning() << bremsfaktor;
// 	bremsfaktor = bremsfaktor /** bremsfaktor * bremsfaktor*/ / 10;
// 	bremsfaktor = sqrt(sqrt(sqrt(bremsfaktor)));
//  	qWarning() << bremsfaktor;
	activeship.attribute.geschwindigkeit = activeship.attribute.geschwindigkeit * (1 - bremsfaktor);

	}
// 	QGraphicsItem *hafenit;
// 	foreach(hafenit,hafenobjliste)
// 	{
// 		static bool anlegbar;
// 		if(schiffskollision(hafenit))
// 		{
// 			if(hafenit->data(1) == QVariant("Hafenbecken") && activeship.attribute.geschwindigkeit < 5 && !anlegbar)
// 			{
// 				anlegbar = true;
// 				emit kannanlegen(anlegbar);
// 			}
// 
// 		}
// 		else if(anlegbar )
// 		{
// 				anlegbar = false;
// 				emit kannanlegen(anlegbar);
// 		}
// 		if(activeship.attribute.geschwindigkeit >=5 && anlegbar)
// 		{
// 				anlegbar = false;
// 				emit kannanlegen(anlegbar);
// 		}
// 	}
}
/*
// qWarning() << landgi->pixmap().height();
if(testschiff->collidesWithItem(landgi,Qt::IntersectsItemBoundingRect))
{
// QImage collimg = landgi->pixmap().toImage();
// const int schiffhohe = activeship.schiffbreite;
// const int schifflange = activeship.schifflange;
// int eolx = (testschiff->x() - landgi->x()), eoly = testschiff->y() - landgi->y();
// 
// int eorx = eolx + (cos(activeship.attribute.ausrichtung) * schifflange), eory = eoly - (sin(activeship.attribute.ausrichtung) * schifflange);
// 
// int eulx = eolx + (sin(activeship.attribute.ausrichtung) * schiffhohe), euly = eoly + (cos(activeship.attribute.ausrichtung) * schiffhohe);
// 
// int eurx = eulx + eorx - eolx, eury = euly + eory - eoly;

 found = true;
// it = landobjektliste.end();
break;
}
}
if(found)
{
// qWarning() << "Land";
QImage collimg = landgi->pixmap().toImage();

const int schiffhohe = activeship.schiffbreite;
const int schifflange = activeship.schifflange;
//// Ecke Oben Links X-Wert , Ecke Oben Links Y-Wert
// int eolx = (testschiff->x() +  (cos(activeship.attribute.ausrichtung) * schifflange)/2 + (sin(activeship.attribute.ausrichtung) * schiffhohe)/2 - landgi->x()),
// eoly = testschiff->y() + (cos(activeship.attribute.ausrichtung) * schiffhohe)/2 + (sin(activeship.attribute.ausrichtung) * schifflange)/2 - landgi->y();
// Pos der "Mitte des Schiffes"

// activeship.attribute.xposm = testschiff->x() +  (cos(activeship.attribute.ausrichtung) * schifflange)/2 + (sin(activeship.attribute.ausrichtung) * schiffhohe)/2;
// activeship.attribute.yposm = testschiff->y() + (cos(activeship.attribute.ausrichtung) * schiffhohe)/2 + (sin(activeship.attribute.ausrichtung) * schifflange)/2;


// int eorx = eolx + (cos(activeship.attribute.ausrichtung) * schifflange), eory = eoly - (sin(activeship.attribute.ausrichtung) * schifflange);

// int eulx = eolx + (sin(activeship.attribute.ausrichtung) * schiffhohe), euly = eoly + (cos(activeship.attribute.ausrichtung) * schiffhohe);

// int eurx = eulx + eorx - eolx, eury = euly + eory - eoly;
// QPoint ecke_obenlinks, ecke_obenrechts, ecke_untenlinks, ecke_untenrechts;

// QPoint ecke_obenlinks;
// QColor f_eol = QColor(), f_eor = QColor(), f_eul = QColor(), f_eur = QColor();
float bremsfaktor = 0;
if(eolx > 0 && eolx < collimg.width() && eoly >= 0 && eoly < collimg.height())
{
// ecke_obenlinks = QPoint(qreal(testschiff->x() - landgi->x()),qreal(testschiff->y() - landgi->y()));
// ecke_obenlinks = QPoint (eolx, eoly);
// f_eol = QColor(collimg.pixel(eolx, eoly));
// bremsfaktor = f_eol.alphaF();
bremsfaktor = qAlpha(collimg.pixel(eolx, eoly));
// qWarning() << bremsfaktor << "eol" << f_eol.alphaF() << QPoint(eolx,eoly);
}

//i
f(eorx > 0 && eorx < collimg.width() && eory >= 0 && eory < collimg.height())
{
// ecke_obenlinks = QPoint(qreal(testschiff->x() - landgi->x()),qreal(testschiff->y() - landgi->y()));
// ecke_obenrechts = QPoint (eorx, eory);
// f_eor = QColor(collimg.pixel(eorx, eory));
if(bremsfaktor < qAlpha(collimg.pixel(eorx, eory)))
{
// bremsfaktor = f_eor.alphaF();
bremsfaktor = qAlpha(collimg.pixel(eorx, eory));
}
// qWarning() << bremsfaktor << "eor" << f_eor.alphaF() << f_eor << QPoint(eorx,eory) << qAlpha(collimg.pixel(eorx, eory));

}

if(eulx > 0 && eulx < collimg.width() && euly >= 0 && euly < collimg.height())
{
// ecke_obenlinks = QPoint(qreal(testschiff->x() - landgi->x()),qreal(testschiff->y() - landgi->y()));
// ecke_obenlinks = QPoint (eolx, eoly);
// f_eul = QColor(collimg.pixel(eulx, euly));
if(bremsfaktor < qAlpha(collimg.pixel(eulx, euly)))
{
// bremsfaktor = f_eul.alphaF();
bremsfaktor = qAlpha(collimg.pixel(eulx, euly));
}
// qWarning() << bremsfaktor << "eul" << f_eul.alphaF() << f_eul << QPoint(eulx,euly) << qAlpha(collimg.pixel(eulx, euly));

}

if(eurx > 0 && eurx < collimg.width() && eury >= 0 && eury < collimg.height())
{
// ecke_obenlinks = QPoint(qreal(testschiff->x() - landgi->x()),qreal(testschiff->y() - landgi->y()));
// ecke_untenlinks = QPoint (eolx, eoly);
// f_eur = QColor(collimg.pixel(eurx, eury));
if(bremsfaktor < qAlpha(collimg.pixel(eurx, eury)))
{bremsfaktor = qAlpha(collimg.pixel(eurx, eury));
}
// qWarning() << bremsfaktor << "eur"<<  f_eur.alphaF() << f_eul << QPoint(eurx,eury) << qAlpha(collimg.pixel(eurx, eury));

}*/
/*
bremsfaktor = bremsfaktor/255;
qWarning() << bremsfaktor;
bremsfaktor = sqrt(sqrt(sqrt(bremsfaktor)));
qWarning() << bremsfaktor;

// qWarning() << bremsfaktor << "gebremst; post; hohe" << collimg.height() << "Breite" << collimg.width() << QPoint(eolx,eoly) << landgi->y() << testschiff->y();

activeship.attribute.geschwindigkeit = activeship.attribute.geschwindigkeit * (1 - bremsfaktor);

ecke_obenrechts = QPoint(qreal((testschiff->x() + cos(activeship.attribute.ausrichtung) * schifflange) - landgi->x()), qreal((testschiff->y() - sin(activeship.attribute.ausrichtung) * schifflange) - landgi->y()));

ecke_untenlinks = QPoint(qreal((testschiff->x() + sin(activeship.attribute.ausrichtung) * schiffhohe) - landgi->x()), qreal((testschiff->y() + cos(activeship.attribute.ausrichtung) * schiffhohe) - landgi->y()));

ecke_untenrechts = QPoint(qreal(ecke_untenlinks.x()+ ( ecke_obenrechts.x() - ecke_obenlinks.x())- landgi->x()), qreal((ecke_untenlinks.y() + ( ecke_obenrechts.y() - ecke_obenlinks.y())) - landgi->y()));*/

// QImage collimg = landgi->pixmap().toImage();

//////////Punkte innerhalb des kollidierenden Objekts ...
// QColor f_eor = QColor(collimg.pixel(ecke_obenrechts));
// QColor f_eul = QColor(collimg.pixel(ecke_untenlinks));
// QColor f_eur = QColor(collimg.pixel(ecke_untenrechts));


/*if(maphandlingimg.pixel(ecke_obenlinks) == strand_weich || maphandlingimg.pixel(ecke_obenrechts) == strand_weich || maphandlingimg.pixel(ecke_untenlinks) == strand_weich || maphandlingimg.pixel(ecke_untenrechts) == strand_weich)
{
activeship.attribute.geschwindigkeit -= int((activeship.attribute.geschwindigkeit/3));
#ifndef _RELEASE_
qWarning() << "leichter Sand";
#endif
activeship.attribute.steuergeschwindigkeit = 2;
}

if(maphandlingimg.pixel(ecke_obenlinks) == strand_hart || maphandlingimg.pixel(ecke_obenrechts) == strand_hart || maphandlingimg.pixel(ecke_untenlinks) == strand_hart || maphandlingimg.pixel(ecke_untenrechts) == strand_hart)
{
#ifndef _RELEASE_
qWarning() << "harter Sand";
#endif
activeship.attribute.geschwindigkeit -= int((activeship.attribute.geschwindigkeit/2));
activeship.attribute.steuergeschwindigkeit = 4;
}

if(maphandlingimg.pixel(ecke_obenlinks) == nschiffbar || maphandlingimg.pixel(ecke_obenrechts) == nschiffbar || maphandlingimg.pixel(ecke_untenlinks) == nschiffbar || maphandlingimg.pixel(ecke_untenrechts) == nschiffbar)
{
#ifndef _RELEASE_
qWarning() << "Gestrandet";
#endif
landgang();
}

if((maphandlingimg.pixel(ecke_obenlinks) == anlegestelle || maphandlingimg.pixel(ecke_obenlinks) == schiffbar) && (maphandlingimg.pixel(ecke_obenrechts) == anlegestelle || maphandlingimg.pixel(ecke_obenrechts) == schiffbar) && (maphandlingimg.pixel(ecke_untenlinks) == anlegestelle || maphandlingimg.pixel(ecke_untenlinks) == schiffbar) && (maphandlingimg.pixel(ecke_untenrechts) == anlegestelle || maphandlingimg.pixel(ecke_untenrechts) == schiffbar) && activeship.attribute.steuergeschwindigkeit != 1)
{
activeship.attribute.steuergeschwindigkeit = 1;
}

if(maphandlingimg.pixel(ecke_obenlinks) == anlegestelle && maphandlingimg.pixel(ecke_obenrechts) == anlegestelle && maphandlingimg.pixel(ecke_untenlinks) == anlegestelle && maphandlingimg.pixel(ecke_untenrechts) == anlegestelle && anlegbar == false && activeship.attribute.geschwindigkeit<2)
{
anlegbar = true;
emit kannanlegen(anlegbar);

#ifndef _RELEASE_
qWarning() << "anlegen moeglich";
#endif

}
if((maphandlingimg.pixel(ecke_obenlinks) != anlegestelle || maphandlingimg.pixel(ecke_obenrechts) != anlegestelle || maphandlingimg.pixel(ecke_untenlinks) != anlegestelle || maphandlingimg.pixel(ecke_untenrechts) != anlegestelle ) && anlegbar == true)
{
#ifndef _RELEASE_
qWarning() << "anlegen unmoeglich";
#endif
anlegbar = false;
emit kannanlegen(anlegbar);
}*/


// }}
// }}



// 	if(activeship.attribute.geschwindigkeit==0)
// 	{
// 		activeship.attribute.steuerruderausrichtung=0;
// 	}
// }
	/////Kartenrand - Mapwechsel
	if(testschiff->x() > mapprops.breite - 120 )
		{
 		qWarning()<< "Mapwechsel zu Ost" <<mapprops.mapost;
 		if( !mapprops.mapost.isEmpty())
 		{
			float ty = testschiff->y();
			delete testschiff;
			karteladen(mapprops.mapost);
			activeship.attribute.map = mapprops.mapname;
//  			qWarning() << "Karte geladen (mapost)";
 			testschiff->setPos(125,ty);
// 			qWarning() << "Pos gesetzt";
			centerOn(testschiff);
			return;
 		}
 		else
 		testschiff->setPos(mapprops.breite - 120,testschiff->y());
		}
	if(testschiff->x() <120 )
		{
		qWarning() << "Mapwechsel zu West" << mapprops.mapwest;
		if(!mapprops.mapwest.isEmpty())
		{
			float ty = testschiff->y();
//  			qWarning() << ty;
			delete testschiff;
// 			scene()-> clear();
// 			scene()-> deleteLater();
			karteladen(mapprops.mapwest);
			activeship.attribute.map = mapprops.mapname;
// 			delete testschiff;
//  			qWarning() << "Karte geladen (mapwest)";
// 			testschiff = szene->addPixmap(QPixmap(activeship.attribute.filename));
// 			testschiff = szene->add#
// 			qWarning() << "Schiff geladen";
			testschiff->setPos(mapprops.breite-125,ty);
// 			qWarning() << "Pos gesetzt";
			centerOn(testschiff);
// 			setScene(szene);
// 			qWarning() << "Szene gesetzt";
			return;
		}
		else
		testschiff->setPos(120,testschiff->y());
		}

	if(testschiff->y() < 120)
		{
 		qWarning()<< "Mapwechsel zu Nord:" << mapprops.mapnord;
		if(!mapprops.mapnord.isEmpty())
		{
			float tx = testschiff->x();
			delete testschiff;

			karteladen(mapprops.mapnord);
			activeship.attribute.map = mapprops.mapname;
//  			qWarning() << "Karte geladen (mapnord)";
			testschiff->setPos(tx,mapprops.hoehe-125);
// 			qWarning() << "Pos gesetzt";
			centerOn(testschiff);
			return;
		}
		else
		testschiff->setPos(testschiff->x(), 120);
		}

	if(testschiff->y() > mapprops.hoehe - 100)
		{
		qWarning()<< "Mapwechsel zu Sued" << mapprops.mapnord ;
		if(!mapprops.mapsued.isEmpty())
		{
			float tx = testschiff->x();
			delete testschiff;
			karteladen(mapprops.mapsued);
			activeship.attribute.map = mapprops.mapname;
// 			qWarning() << "Karte geladen (mapsued)";
			testschiff->setPos(tx, 125);
// 			qWarning() << "Pos gesetzt";
			centerOn(testschiff);
			return;
		}
		else
			testschiff->setPos(testschiff->x(), mapprops.hoehe - 100);
		}
// }
}
if(durchlauf%50==0
#ifndef _RELEASE_
 && fokussieren->isChecked()
#endif
)
{
centerOn(testschiff->x(),testschiff->y());
}
}
// }

#ifndef _RELEASE_

if(durchlauf%10==0)
{
	knoten -> setText (QString("V:%1").arg(activeship.attribute.geschwindigkeit));
	sollknoten -> setText(QString("SollV: %1").arg(activeship.attribute.sollgeschwindigkeit));
	solldir -> setText(QString("SollDir %1").arg(activeship.attribute.sollausrichtung));
	dir -> setText(QString("Dir %1").arg(activeship.attribute.ausrichtung));
	steuerdir -> setText(QString("SteuerDir: %1").arg(activeship.attribute.steuerruderausrichtung));
	sollsteuerdir -> setText(QString("SollSteuerDir: %1").arg(activeship.attribute.sollsteuerruderausrichtung));
// 	segeldir -> setText(QString("SegelDir: %1").arg(activeship.attribute.segelausrichtung));
	segel->setText(QString("SegelFlaeche: %1").arg(activeship.attribute.prozentgesetzteSegel));
	sollsegel->setText(QString("SollSegelFl: %1").arg(activeship.attribute.sollprozentgesetzteSegel));
	segeldir -> setText(QString("SegelDir: %1").arg(activeship.attribute.segelausrichtung));
}
#endif

}
///				ENDE Aktualisierung


void hauptfenster::windsetzen()
{

	int aenderung = ((rand()%3)-1);
	float faenderung = (rand()%23);
	if(/*faenderung!=0*/ (aenderung*M_PI)/ (1+faenderung*10) < 0.2 && (aenderung*M_PI)/ (1+faenderung*10) > -0.2)
	{
		windrichtung = windrichtung + (aenderung*M_PI)/(1+faenderung*10);
	}
	if(windrichtung > 2 * M_PI)
	{
		windrichtung =0;
	}

	if(windrichtung < 0)
	{
		windrichtung =2 * M_PI;
	}

	windgeschwindigkeit = windgeschwindigkeit + ((rand()%3)-1);

	if(windgeschwindigkeit > 90)
	{
		windgeschwindigkeit=90;
	}

	if(windgeschwindigkeit < 0)
	{
	windgeschwindigkeit=1;
	}
}

/// HIER BEGINNT DIE BEWEGUNGSBESCHREIBUNG .........................................................

void hauptfenster::bewegungsbeschreibung()
{
// static int sollgeschwindigkeit_durchlauf, sollruderrichtung_durchlauf;	//Zaehlvariable fuer Ruder bzw. Geschwindigkeit -> Schiff ist traege und wird nur langsam schneller / lenkt langsam ----> jetzt Klassenvariable
// qWarning() << "bewegungsbeschreibung" << sollgeschwindigkeit_durchlauf++;
// sollgeschwindigkeit_durchlauf++;	//warten .... (Traegheit)



if(durchlauf%BESCHLEUNIGUNG==0)	//wenn genug gewartet
	{
// 				if(activeship.attribute.sollgeschwindigkeit > activeship.attribute.geschwindigkeit)
// 				{
// 					activeship.attribute.geschwindigkeit = activeship.attribute.geschwindigkeit + 1;
// 				}
// 				else
// 				{
// 					activeship.attribute.geschwindigkeit = activeship.attribute.geschwindigkeit - 1;
// 				}

// float acc = windgeschwindigkeit * (activeship.attribute.prozentgesetzteSegel + 0.05 * (1- activeship.attribute.prozentgesetzteSegel)) * cos((activeship.attribute.segelausrichtung + activeship.attribute.ausrichtung) - windrichtung);

// float schiffacc = schiffs 0.05 * windgeschwindigkeit * cos(activeship.attribute.ausrichtung - windrichtung) - activeship.attribute.geschwindigkeit;
if(activeship.attribute.sollprozentgesetzteSegel < activeship.attribute.prozentgesetzteSegel)
{
activeship.attribute.prozentgesetzteSegel = activeship.attribute.prozentgesetzteSegel - 0.2;
if(activeship.attribute.prozentgesetzteSegel<0.1)
{
activeship.attribute.prozentgesetzteSegel=0;
}
}
if(activeship.attribute.sollprozentgesetzteSegel > activeship.attribute.prozentgesetzteSegel)
{
activeship.attribute.prozentgesetzteSegel = activeship.attribute.prozentgesetzteSegel + 0.2;
}



// if(sollgeschwindigkeit_durchlauf > 1000000)
// {
// sollgeschwindigkeit_durchlauf = 0;
// }
// activeship.attribute.geschwindigkeit = 1;

// windrichtung = M_PI/2;
// windgeschwindigkeit=10;
// float segelacc;
// if(schwierigkeit==1)
// {
// 
// }
// else
// {
// segelacc = (activeship.attribute.prozentgesetzteSegel * windgeschwindigkeit * cos((activeship.attribute.ausrichtung - windrichtung)/2));
// }



// qWarning () << segelacc << segelacc/2 << activeship.attribute.prozentgesetzteSegel * cos((activeship.attribute.ausrichtung + activeship.attribute.segelausrichtung) - windrichtung)  ;
//ceil->aufrunden; floor -> abrunden
if(schwierigkeit==1)
{
float segelacc = /*activeship.attribute.geschwindigkeit -*/ (activeship.attribute.prozentgesetzteSegel * windgeschwindigkeit * cos((activeship.attribute.ausrichtung + activeship.attribute.segelausrichtung) - windrichtung)) - activeship.attribute.geschwindigkeit;
	if(segelacc >0)
	{
		activeship.attribute.geschwindigkeit = activeship.attribute.geschwindigkeit + int(ceil(segelacc/2));
	}
	if(segelacc < 0)
	{
		activeship.attribute.geschwindigkeit = activeship.attribute.geschwindigkeit + int(floor(segelacc/2));
	}

#ifndef _RELEASE_
	acclabel->setText(QString("Beschleunigung: %1").arg(ceil(segelacc/2)));
#endif
}

if(schwierigkeit ==0)
{
	float auftreffwinkel = activeship.attribute.ausrichtung - windrichtung;
// 	if(auftreffwinkel < 0)
// 	auftreffwinkel = -auftreffwinkel;

	quint8 wirkendeWindgeschwindigkeit = quint8(ceil(activeship.attribute.prozentgesetzteSegel * windgeschwindigkeit * (1 + cos(auftreffwinkel))/2 ));
// qWarning() << wirkendeW

#ifndef _RELEASE_
	acclabel->setText(QString("wirkende Wind-v %1").arg(wirkendeWindgeschwindigkeit));
#endif

	if(wirkendeWindgeschwindigkeit > activeship.attribute.geschwindigkeit)
	{
		activeship.attribute.geschwindigkeit += int(ceil((wirkendeWindgeschwindigkeit - activeship.attribute.geschwindigkeit)/4));
// 		activeship.attribute.geschwindigkeit += int(ceil((wirkendeWindgeschwindigkeit+1)/(activeship.attribute.geschwindigkeit+1)));
emit SIGgeschwindigkeit(activeship.attribute.geschwindigkeit);

	}
	if(wirkendeWindgeschwindigkeit < activeship.attribute.geschwindigkeit)
	{
		activeship.attribute.geschwindigkeit += int(floor((wirkendeWindgeschwindigkeit - activeship.attribute.geschwindigkeit)/4));
// 		activeship.attribute.geschwindigkeit-= int(ceil((activeship.attribute.geschwindigkeit+1)/(wirkendeWindgeschwindigkeit+1)));
emit SIGgeschwindigkeit(activeship.attribute.geschwindigkeit);

	}
}

// emit SIGgeschwindigkeit(activeship.attribute.geschwindigkeit);
// if(activeship.attribute.geschwindigkeit < activeship.attribute.geschwindigkeit + floor(segelacc/2))
// {
// activeship.attribute.geschwindigkeit++;
// }
// if(activeship.attribute.geschwindigkeit > activeship.attribute.geschwindigkeit + floor(segelacc/2))
// {
// activeship.attribute.geschwindigkeit--;
// }

// 				activeship.attribute.geschwindigkeit =  activeship.attribute.geschwindigkeit + (( windgeschwindigkeit * (activeship.attribute.prozentgesetzteSegel + 0.05 * (1- activeship.attribute.prozentgesetzteSegel)) * cos((activeship.attribute.segelausrichtung + activeship.attribute.ausrichtung) - windrichtung))/* - activeship.attribute.geschwindigkeit*//* - activeship.attribute.geschwindigkeit * activeship.attribute.geschwindigkeit/4*/ );

//Geschwindigkeit = bisherige Geschwindigkeit + Differenz aus bisheriger Geschwindigkeit und der Kraft-Geschwindigkeit die auf das Schiff wirkt: aktive Segelflaeche + Schiffsflaeche als Angriffsflaeche
//Reibung -> v^2/4

// 		sollgeschwindigkeit_durchlauf=0;
		if( activeship.attribute.geschwindigkeit > 60)
		{
#ifndef _RELEASE_

			qWarning() << "Geblitzt :P zu schnell vorwaerts ^^ ";
#endif

			activeship.attribute.geschwindigkeit = 60;
		}
		if(activeship.attribute.geschwindigkeit < -5)
		{
#ifndef _RELEASE_

		qWarning() << "Geblitzt :P zu schnell rueckwaerts ^^ ";
#endif
		activeship.attribute.geschwindigkeit = -4;
		}
	}
		//Maus-Lenkung !
		if((activeship.attribute.sollausrichtung < activeship.attribute.ausrichtung - 0.01 || activeship.attribute.sollausrichtung > activeship.attribute.ausrichtung + 0.01) && !tastatur)
		{
// 		qWarning() << "Mausgesteuertes Lenken" << sollruderrichtung_durchlauf;
// 			sollruderrichtung_durchlauf++;
// 			if(sollruderrichtung_durchlauf%WENDEGESCHWINDIGKEIT ==0)
// 			{
//  				qWarning() << sollruderrichtung_durchlauf;

				if((activeship.attribute.ausrichtung < activeship.attribute.sollausrichtung && activeship.attribute.ausrichtung + M_PI > activeship.attribute.sollausrichtung) || (activeship.attribute.ausrichtung > activeship.attribute.sollausrichtung && activeship.attribute.ausrichtung - M_PI > activeship.attribute.sollausrichtung))
				{
					activeship.attribute.ausrichtung = activeship.attribute.ausrichtung + 0.0006 * ((activeship.attribute.geschwindigkeit/4) + 2) * activeship.attribute.steuergeschwindigkeit;
// 				qWarning() << "MS-Lenken-if" << activeship.attribute.ausrichtung;

 /*activeship.attribute.steuerruderausrichtung;*/
				}
				else
				{
					activeship.attribute.ausrichtung = activeship.attribute.ausrichtung - 0.0006 * ((activeship.attribute.geschwindigkeit/4) + 2) * activeship.attribute.steuergeschwindigkeit;
// 				qWarning() << "MS-Lenken-else" << activeship.attribute.ausrichtung;
// 				activeship.attribute.ausrichtung = activeship.attribute.ausrichtung - 0.0006 * (sqrt(activeship.attribute.geschwindigkeit * activeship.attribute.geschwindigkeit/4) + 2) * activeship.attribute.steuergeschwindigkeit;

				}
// 				sollruderrichtung_durchlauf=0;
// 			}
		}

		///TASTATURGESTEUERTES LENKEN ....
		if(tastatur && activeship.attribute.sollsteuerruderausrichtung != activeship.attribute.steuerruderausrichtung)
		{
// 			sollruderrichtung_durchlauf++;
			if(durchlauf%WENDEGESCHWINDIGKEIT==0)
			{
/*				if(activeship.attribute.sollsteuerruderausrichtung < activeship.attribute.steuerruderausrichtung)
				{
					activeship.attribute.steuerruderausrichtung = activeship.attribute.steuerruderausrichtung - (activeship.attribute.sollsteuerruderausrichtung/10);
 //activeship.attribute.steuerruderausrichtung;
				}
				else
				{
					activeship.attribute.steuerruderausrichtung = activeship.attribute.steuerruderausrichtung + (activeship.attribute.sollsteuerruderausrichtung/10);
// 					activeship.attribute.steuerruderausrichtung = activeship.attribute.steuerruderausrichtung + 0.0025;
				}*/
				if(activeship.attribute.sollsteuerruderausrichtung != activeship.attribute.steuerruderausrichtung)
				{
				activeship.attribute.steuerruderausrichtung = activeship.attribute.steuerruderausrichtung + ((activeship.attribute.sollsteuerruderausrichtung - activeship.attribute.steuerruderausrichtung)/5);

				if(activeship.attribute.steuerruderausrichtung <0.0001 && activeship.attribute.steuerruderausrichtung > -0.0001 && activeship.attribute.sollsteuerruderausrichtung==0)
				{
				activeship.attribute.steuerruderausrichtung =0;
				}
				}


// 				sollruderrichtung_durchlauf=0;
			}
		activeship.attribute.ausrichtung = activeship.attribute.ausrichtung + activeship.attribute.steuerruderausrichtung;
		}



// if(activeship.attribute.sollsteuerruderausrichtung==activeship.attribute.steuerruderausrichtung && (activeship.attribute.sollausrichtung == activeship.attribute.ausrichtung || activeship.attribute.sollausrichtung==0))
// 		{
// 			sollruderrichtung_durchlauf=0;
// 		}
// 		qWarning() << "Ausrichtung: " << activeship.attribute.ausrichtung;

// 		qWarning() << "Ausrichtung: " << activeship.attribute.ausrichtung;
	if(activeship.attribute.ausrichtung<0)
	{
		activeship.attribute.ausrichtung = 2*M_PI-0.0000001;
	}
	if(activeship.attribute.ausrichtung>2*M_PI)
	{
		activeship.attribute.ausrichtung = 0;
	}
// 		qWarning() << "Ausrichtung: " << activeship.attribute.ausrichtung;
}

bool hauptfenster::schiffskollision(QGraphicsItem *land)
{
// int x = testschiff->x();
if(activeship.attribute.xposm > land->x() && activeship.attribute.yposm > land->y() && activeship.attribute.xposm < land->x() + land->boundingRect().width() && activeship.attribute.yposm < land->y() + land->boundingRect().height() )
{
qWarning() << "Kollision";
return true;
}
else return false;


}

void hauptfenster::schuss()
{
}