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

// const int tageslaenge = 1000;

// const int taglaenge = 

// #define AKTUALISIERUNGSINTERVALL 40
// #define WENDEGESCHWINDIGKEIT 10
// #define BESCHLEUNIGUNG 50
// #define WINDVERAENDERUNG 30
//Beschleunigung -> Traegheit: bei groesseren Werten reagiert das Schiff langsamer
// #define PRODUKTION 1000

// #define _RELEASE_
#define _NO_CONTROL_LABEL_

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

hauptfenster::hauptfenster(DataClass *dc)
{
	gamedata = dc;
// 	gamedata->active_ship = new ShipClass();
// 	gamedata->active_ship->init();

	qWarning() << "Schiffstyp" << gamedata->active_ship->type;

	anbord=true;
	pause = false;
// 	uhra=false;
// 	tageslaenge = 2000;
// 	tag = 0;
// 	stunde = 0;
// 	minute = 0;
	gamedata->gametime.init();
// 	spielzeit.setYear(1350);
// 	spielzeit.setMonth(4);
// 	spielzeit.setDay(1);
// 	spielzeit.setHour(12);
// 	spielzeit.setMinute(0);
// 	spielzeit.setDayLength(2000);

	gamedata->wind.init();
// 	int randint = rand()%7;
// 	windrichtung = randint;
// 	windgeschwindigkeit = rand() %30 +5;
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
// 	gamedata->active_ship->schiffbreite = testschiff->boundingRect().width();
// 	gamedata->active_ship->schifflange = testschiff->boundingRect().height();
	gamedata->active_ship->schiffsname = tr("Seeadler");

#ifndef _NO_CONTROL_LABEL_

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

	knoten -> setText (QString("V:%1").arg(gamedata->active_ship->attribute.geschwindigkeit));
	sollknoten -> setText(QString("SollV: %1").arg(gamedata->active_ship->attribute.sollgeschwindigkeit));

	segel->setText(QString("SegelFlaeche: %1").arg(gamedata->active_ship->attribute.prozentgesetzteSegel));
	sollsegel->setText(QString("SollSegelFl: %1").arg(gamedata->active_ship->attribute.sollprozentgesetzteSegel));
	segeldir -> setText(QString("SegelDir: %1").arg(gamedata->active_ship->attribute.segelausrichtung));

	solldir -> setText(QString("SollDir %1").arg(gamedata->active_ship->attribute.sollausrichtung));
	dir -> setText(QString("Dir %1").arg(gamedata->active_ship->attribute.ausrichtung));
	steuerdir -> setText(QString("SteuerDir: %1").arg(gamedata->active_ship->attribute.steuerruderausrichtung));
	sollsteuerdir -> setText(QString("SollSteuerDir: %1").arg(gamedata->active_ship->attribute.sollsteuerruderausrichtung));

//  	winddir -> setText(QString("WindDir: %1").arg(windrichtung));
// 	windv -> setText(QString("WindV: %1").arg(windgeschwindigkeit));
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

void hauptfenster::setDataClass(DataClass *param_dc)
{
gamedata = param_dc;
}

void hauptfenster::starttimer()
{
konsolenwidget->debug(QString("void hauptfenster::starttimer()"));
bewegung= new QTimer(this);

bewegung->start(AKTUALISIERUNGSINTERVALL);
connect(bewegung,SIGNAL(timeout()),this,SLOT(aktualisieren()));
}

void hauptfenster::mousePressEvent(QMouseEvent *event) /// MAUS-Steuerungssachen
{
konsolenwidget->debug(QString("void hauptfenster::mousePressEvent(QMouseEvent *event) "));

const float scale = transform().m11();
QPointF clickpoint = QPointF((event->x() + horizontalScrollBar()->value())/scale,
(event->y() + verticalScrollBar()->value())/scale);
if(!pause)
{
	if(gamedata->landingstruct.landingstate == LandingProcess::WaitingForDestination)
	{
	QGraphicsItem *it;
	QList <QGraphicsItem *> qgilistAP = szene->items(clickpoint);
	foreach(it, qgilistAP)
	{
		if(it->data(0).toInt() >= 100 && it->data(0).toInt() < 500 )
		{
		gamedata->landingstruct.landing_line = QLineF(QPointF(gamedata->landingstruct.landingShip_gi->x() + gamedata->landingstruct.landingShip_gi->boundingRect().width()/2, gamedata->landingstruct.landingShip_gi->y() + gamedata->landingstruct.landingShip_gi->boundingRect().height()/2), clickpoint);
		gamedata->landingstruct.landingstate = LandingProcess::ActiveLanding;
		gamedata->landingstruct.vx = gamedata->landingstruct.landing_line.dx() / gamedata->landingstruct.landing_line.length();
		gamedata->landingstruct.vy = gamedata->landingstruct.landing_line.dy() / gamedata->landingstruct.landing_line.length();
		gamedata->landingstruct.l_orientation = (gamedata->landingstruct.landing_line.angle() - 90) ;
		if (gamedata->landingstruct.l_orientation < 0)
		{
		gamedata->landingstruct.l_orientation += 360;
		}
		gamedata->landingstruct.l_orientation = gamedata->landingstruct.l_orientation *  M_PI / 180;
		konsolenwidget->debug(QString("landing_line_orientation: %1 ").arg(gamedata->landingstruct.l_orientation));
		konsolenwidget->debug(QString("landing_line_angle: %1 ").arg(gamedata->landingstruct.landing_line.angle()));
		konsolenwidget->debug(QString("landing orientation: %1 ").arg(gamedata->landingstruct.orientation));
		qWarning() << gamedata->landingstruct.vx << gamedata->landingstruct.landing_line.dx() << gamedata->landingstruct.vy << gamedata->landingstruct.landing_line.dy() << gamedata->landingstruct.landing_line.length();
		gamedata->landingstruct.correctOrientation = false;
		return;
		}
	}
	
	
	}
	if(!anbord && gamedata->landingstruct.landingstate == LandingProcess::AtLand)
	{
		QGraphicsItem *ort = scene()->itemAt(clickpoint);
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

			if(ort->data(0).toInt() == ObjectType::Market)
			{
#ifndef _RELEASE_
			qWarning() << "Man begibt sich auf den Markt ...";
#endif
			emit handel();
			}

			if(ort->data(0).toInt() == ObjectType::Townhall)
			{
			}

			if(ort->data(0).toInt() == ObjectType::Church)
			{
			}

			if(ort->data(0).toInt() == ObjectType::Port)
			{
			}

			if(ort->data(0).toInt() == ObjectType::Kontor)
			{
			}

			if(ort->data(0).toInt() == ObjectType::Bank)
			{
			}

			if(ort->data(0).toInt() == ObjectType::Tavern)
			{
				emit enterBuilding(ObjectType::Tavern);
			}

/*			if(ort->toolTip() == "Uhr" || ort->toolTip() == "grosser Zeiger" || ort->toolTip() == "kleiner Zeiger")
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
			}*/

// #ifndef _RELEASE_
// 			 qWarning() << testschiff->pos() << event->posF() << (testschiff->x() - event->x()) << " \t" << testschiff->y() - event->y() << "\nVBar-Value:" <<verticalScrollBar()->value();
// #endif
		}
	}
	else if(anbord)
	{
// 	gamedata->active_ship->mouse_control = true;
	int x = (event->x() + horizontalScrollBar()->value())/scale;
	int y = (event->y() + verticalScrollBar()->value())/scale;

// 	int mposx = int(testschiff->x() + cos(gamedata->active_ship->ret_Dir()) * gamedata->active_ship->schiffbreite/2 + sin(gamedata->active_ship->ret_Dir())* gamedata->active_ship->schifflange / 2);

// 	int mposy = int(testschiff->y() + cos(gamedata->active_ship->ret_Dir()) * gamedata->active_ship->schifflange/2 + sin(gamedata->active_ship->ret_Dir()) * gamedata->active_ship->schiffbreite /2);
	PositioningStruct ship_pos = gamedata->active_ship->ret_currentPosition();
  int mposx = ship_pos.m_position.x();
  int mposy = ship_pos.m_position.y();

#ifndef _RELEASE_
	qWarning() << "Maussteuerung" << x << y << mposx << mposy;
	QGraphicsLineItem *blah = new QGraphicsLineItem(QLineF(mposx, mposy, x, y));
	szene->addItem(blah);
#endif

	if(x > mposx &&  y < mposy)			// Klick im "I. Quadrant" (Schiff -> KO [O(0|0)] )
							//(Koordinatensystem: gespiegelte Y-Achse ...)
	{
		int diffx = (x - mposx);
// 		int diffy = int(testschiff->y() - (event->y() + verticalScrollBar()->value()));
		int diffy = (mposy - y);
		float klickabstand = sqrt( diffx*diffx + diffy*diffy);
		float winkel = asin(diffy/klickabstand);

		gamedata->active_ship->set_ToDir(3*M_PI/2 + winkel);

#ifndef _RELEASE_
		qWarning() << "I" << winkel << "Ausrichtung" << gamedata->active_ship->ret_ToDir() <<"Abstand:" <<klickabstand;
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
		gamedata->active_ship->set_ToDir(winkel);

#ifndef _RELEASE_
		qWarning() << "II" << winkel << "Ausrichtung" << gamedata->active_ship->ret_ToDir() <<"Abstand:" <<klickabstand;
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
		gamedata->active_ship->set_ToDir(M_PI/2 + winkel);

#ifndef _RELEASE_
		qWarning() << "III" << winkel << "Ausrichtung" << gamedata->active_ship->ret_ToDir() <<"Abstand:" <<klickabstand;
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
		gamedata->active_ship->set_ToDir(M_PI + winkel);
#ifndef _RELEASE_
		qWarning() << "IV" << winkel << "Ausrichtung" << gamedata->active_ship->ret_ToDir() <<"Abstand:" <<klickabstand;
#endif
	}
// 	tastatur=false;
	gamedata->active_ship->mouse_control = true;
	}
}
}

void hauptfenster::keyEventWeiterleitung(QKeyEvent *event)
{
keyPressEvent(event);
}


void hauptfenster::keyPressEvent(QKeyEvent *event)
{
konsolenwidget->debug(QString("void hauptfenster::keyPressEvent(QKeyEvent *event) ").append(event->text()));
switch (event->key())
{
	case Qt::Key_W:
	{
		if(anbord)
		{
// 		if(gamedata->active_ship->attribute.sollprozentgesetzteSegel < 1)
// 		{
// 			gamedata->active_ship->attribute.sollprozentgesetzteSegel = gamedata->active_ship->attribute.sollprozentgesetzteSegel + 0.2;
			gamedata->active_ship->set_ToSettedSails(gamedata->active_ship->ret_ToSettedSails() + 0.2);
// 			gamedata->active_ship->mouse_control = false;
#ifndef _RELEASE_
			qWarning() << "Segel gesetzt:" << gamedata->active_ship->ret_ToSettedSails();
#endif

// 		}
		}
		break;
	}
	case Qt::Key_S: 
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(anbord)
				{
					gamedata->active_ship->set_ToSettedSails(gamedata->active_ship->ret_ToSettedSails() - 0.2);
// 					gamedata->active_ship->mouse_control = false;
				}
				else
				{
				}
				break;
			}
			case Qt::ControlModifier:
			{
				emit savesig();
				break;
			}
			case Qt::ShiftModifier:
			{
				
				
				break;
			}
		
		}
		break;
	}
	
	case Qt::Key_A:
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(anbord)
				{
					gamedata->active_ship->set_ToRudderDir(gamedata->active_ship->ret_ToRudderDir() + 0.0002);
// 					tastatur = true;
// 					gamedata->active_ship->mouse_control = false;
					
				}
				else
				{
					
				}
				break;
			}
			case Qt::ShiftModifier:
			{
				if(anbord)
				{
				gamedata->active_ship->set_SailDir(gamedata->active_ship->ret_SailDir() + 0.02);

				}
				else
				{
					
				}
				break;
			}
		}
		break;
	}
	
	case Qt::Key_D:
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(anbord)
				{
					gamedata->active_ship->set_ToRudderDir(gamedata->active_ship->ret_ToRudderDir() - 0.0002);
// 					gamedata->active_ship->mouse_control = false;
				}
				else
				{
					
				}
				break;
			}
			case Qt::ShiftModifier:
			{
				if(anbord)
				{
					
				}
				else
				{
					
				}
				break;
			}
		}
		break;
	}
	
	case Qt::Key_P:
	{
#ifndef _RELEASE_
		qWarning() << "Pause" << pause;
#endif
		slotpause();
		break;
	}
// 		static int zoomlvl;
	case Qt::Key_Minus:		/*&& zoomlvl <2)*/
	{
		scale(0.8,0.8);
		zoomlvl++;
		break;
	}
	case Qt::Key_Plus:		/*&& zoomlvl >0)*/
	{
		scale(1.25,1.25);
		zoomlvl--;
		break;
	}
	
	case Qt::Key_AsciiCircum:
	{
		qWarning() << "Open Console!";

		konsolenwidget->show();
		break;
	}
	case Qt::Key_Escape:
	{
		emit menusig();
		qWarning() << "Menusig";
		break;
	}
	
	case Qt::Key_M:
	{
		switch (event->modifiers())
		{
			case Qt::NoModifier:
			{
				if(anbord)
				{
				}
				else
				{
					
				}
				break;
			}
			case Qt::ShiftModifier:
			{
				if(anbord)
				{
					
				}
				else
				{
					
				}
				break;
			}
			case Qt::ControlModifier:
			{
#ifndef _RELEASE_
				gamedata->active_ship->cargo.taler += 1000;
#endif
				break;
			}
		}

		break;
	}
#ifndef _RELEASE_
	case Qt::Key_C:
	{
		centerOn(gamedata->active_ship->graphicsitem);
		break;
	}
	case Qt::Key_L:
	{
		gamedata->wind.setV(gamedata->wind.retV() + 1);
		break;
	}
	case Qt::Key_K:
	{
		gamedata->wind.setV(gamedata->wind.retV() - 1);
		break;
	}
	case Qt::Key_Left:
	{
// 		if(anbord)
// 		{
// 		gamedata->active_ship->attribute.ausrichtung += 0.2;
// 		if(gamedata->active_ship->attribute.ausrichtung > 2 * M_PI)
// 		{
// 			gamedata->active_ship->attribute.ausrichtung = 0.1;
// 		}
// 		}
		break;
	}
	case Qt::Key_Right:
	{
// 		if(anbord)
// 		{
// 		gamedata->active_ship->attribute.ausrichtung -= 0.2;
// 		if(gamedata->active_ship->attribute.ausrichtung < 0 )
// 		{
// 			gamedata->active_ship->attribute.ausrichtung = 2 * M_PI - 0.1;
// 		}
// 		}
		break;
	}
	case Qt::Key_Up:
	{
		if(anbord)
// 		gamedata->active_ship->attribute.geschwindigkeit ++;
		break;
	}

	case Qt::Key_Down:
	{
		if(anbord)
// 		gamedata->active_ship->attribute.geschwindigkeit--;
		break;
	}

#endif
}

if(event->text() =="Q" || (event->key() == Qt::Key_Q && event->modifiers() == Qt::ControlModifier))
{
	close();
	deleteLater();
}

}



void hauptfenster::slotpause()
{
konsolenwidget->debug(QString("void hauptfenster::slotpause()"));

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
konsolenwidget->debug(QString("void hauptfenster::endePause()"));
		if(!bewegung->isActive())
		{
			bewegung->start(AKTUALISIERUNGSINTERVALL);
			pause=false;
		}
}

void hauptfenster::startPause()
{
konsolenwidget->debug(QString("void hauptfenster::startPause()"));
		if(bewegung->isActive())
		{
			bewegung->stop();
			pause=true;
		}
}


void hauptfenster::segelsetzen(int i)
{
konsolenwidget->debug(QString("void hauptfenster::segelsetzen(int i) ").append(i));
// float n = i;
// gamedata->active_ship->attribute.sollprozentgesetzteSegel = n/5;
gamedata->active_ship->set_ToSettedSails(i/5);
#ifndef _RELEASE_
qWarning() << "sollgesetzteSegel:" << gamedata->active_ship->ret_ToSettedSails();
#endif
}



void hauptfenster::aktualisieren()
{

durchlauf++;
// if(durchlauf % (tageslaenge/1440))

// if(false)
// if(durchlauf%2 == 0 && uhra)u(fi                          
#ifdef _DEBUG_REFRESH_
qWarning() << "Aktualisieren";
#endif

// static int durchlauf;	//Zaehlvariable fuer Ruder bzw. Geschwindigkeit -> Schiff ist traege und wird nur langsam schneller / lenkt langsam ----> jetzt Klassenvariable

if(gamedata->gametime.refreshTime())			//returns true, when a new day starts ...
{
	qWarning() << "New Day ...";
	emit sig_newDay(durchlauf);
// 	qWarning() << "Aktualisierungssignal gesendet";
	if(durchlauf > 2000000000)	// 4 000 000 000
	{
		durchlauf=0;
	}
}

/////////////WIND + WOLKEN/////////////////////////////





if(durchlauf % WINDVERAENDERUNG == 0)
{
	qWarning() << "Windsetzen ...";
	gamedata->wind.refresh();

#ifndef _NO_CONTROL_LABEL_
	double windrichtung = gamedata->wind.retDir();
	int windgeschwindigkeit = gamedata->wind.retV();
	winddir -> setText(QString("WindDir: %1").arg(windrichtung));
	windv -> setText(QString("WindV: %1").arg(windgeschwindigkeit));
#endif
}
// qWarning() << "Vor Wolkenzeugs";

// qWarning()<< "KGL: WL: Eintraege" << wolkenliste.size();
if(gamedata->wind.retV() > 0)
{
double windrichtung = gamedata->wind.retDir();
int windgeschwindigkeit = gamedata->wind.retV();
	if(durchlauf%10==0 )					//Bewegung mit Verschiebung
	{
		foreach(QGraphicsItem *wolkenit, wolkenliste)
		{
			int rx = (rand() % 3)-1;
			float xverschiebung=rx;
			xverschiebung = xverschiebung /10;

			int ry = (rand() % 3)-1;
			float yverschiebung = ry;
			yverschiebung = yverschiebung/10;

			wolkenit->moveBy(-(windgeschwindigkeit * sin(windrichtung))/10 + xverschiebung, -(windgeschwindigkeit * cos(windrichtung))/10 + yverschiebung);

			if(wolkenit->x() <10 )
			{
// wolke->setPos(3800 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(gamedata->currentMap.size.width() - 10, (rand()%(gamedata->currentMap.size.height() - 200)) + 50);
			}
			if(wolkenit->x() > gamedata->currentMap.size.width() - 10 )
			{
// wolke->setPos(205 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(10, (rand()%(gamedata->currentMap.size.height() - 200)) + 50);
			}
			if(wolkenit->y() <10 )
			{
				wolkenit->setPos((rand() % (gamedata->currentMap.size.width() - 200)) + 50, gamedata->currentMap.size.height() - 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 2800 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
			if(wolkenit->y() > gamedata->currentMap.size.height() - 10 )
			{
				wolkenit->setPos((rand() % (gamedata->currentMap.size.width() - 200)) + 50, 10);
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
				wolkenit->setPos(gamedata->currentMap.size.width() - 10, (rand()%(gamedata->currentMap.size.height() - 200)) + 50);
			}
			if(wolkenit->x() > gamedata->currentMap.size.width() - 10 )
			{
// wolke->setPos(205 - (windgeschwindigkeit * sin(windrichtung))/10, wolke->y() - (windgeschwindigkeit * cos(windrichtung))/10);
				wolkenit->setPos(10, (rand()%(gamedata->currentMap.size.height() - 200)) + 50);
			}
			if(wolkenit->y() <10 )
			{
				wolkenit->setPos((rand() % (gamedata->currentMap.size.width() - 200)) + 50, gamedata->currentMap.size.height() - 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 2800 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
			if(wolkenit->y() > gamedata->currentMap.size.height() - 10 )
			{
				wolkenit->setPos((rand() % (gamedata->currentMap.size.width() - 200)) + 50, 10);
// wolke->setPos( wolke->x() - (windgeschwindigkeit * sin(windrichtung))/10, 205 - (windgeschwindigkeit * cos(windrichtung))/10);
			}
		}
	}

}

//  qWarning() << "Ende Wolkenzeugs";

// #define _DEBUG_REFRESH_
///////SCHIFF////////////////////////////////////////
//falls v>0 / geplant: v>0
// qWarning() << "IfAnbord";
if(gamedata->landingstruct.landingstate == LandingProcess::ActiveLanding)
{
#ifdef _DEBUG_REFRESH_
qWarning() << "Landing";
#endif
activeLanding();
}


else if(anbord)
{

// qWarning() << "Beginn Schiffszeug";
// if(gamedata->active_ship->attribute.geschwindigkeit > 0 || gamedata->active_ship->attribute.sollprozentgesetzteSegel > 0 || gamedata->active_ship->attribute.prozentgesetzteSegel > 0 || windgeschwindigkeit > 0)
{
// qWarning() << "Vor Bewegungsbeschreibung";
// 	bewegungsbeschreibung();
// qWarning() << "Nach Bewegungsbeschreibung";
#ifdef _DEBUG_REFRESH_
 	qWarning() << "Calc Movement";
#endif
	gamedata->active_ship->calcMovement(gamedata->wind.retV(), gamedata->wind.retDir());
#ifdef _DEBUG_REFRESH_
	qWarning() << "End: Calc Movement, move Graphics";
#endif
// 	gamedata->active_ship->moveGraphics();

//////////////////////Landkollossion
/////////////////Schiffbar?
// qWarning() << "Schiffbar?";

// if(0==1)
if(gamedata->active_ship->moveGraphics())
 {
#ifdef _DEBUG_REFRESH_
	qWarning() << "End moveGraphics()";
#endif
	float bremsfaktor = 0;

// QList <QGraphicsItem*> collliste = testschiff->collidingItems();	//Kollisionsliste

// if(/*!collliste.isEmpty() &&*/ durchlauf % 5 ==0)
// {
// bool found = false;
// qWarning() << "Not Empty" << collliste.size() << landobjektliste.size();
	QGraphicsPixmapItem *landgi;
	int iz = 0;
	for(QList <QGraphicsPixmapItem*>::iterator it = landobjektliste.begin(); it < landobjektliste.end(); ++it)
	{
		iz ++;
		landgi = *it;
		if(schiffskollision(landgi))
		{
			static int ibrprufg[3];			//Ueberpruefungszahl: Neubelegung der Bilder erforderlich?
// int eolx = (testschiff->x() +  (cos(gamedata->active_ship->attribute.ausrichtung) * schifflange)/2 + (sin(gamedata->active_ship->attribute.ausrichtung) * schiffhohe)/2 - landgi->x()),
// eoly = testschiff->y() + (cos(gamedata->active_ship->attribute.ausrichtung) * schiffhohe)/2 + (sin(gamedata->active_ship->attribute.ausrichtung) * schifflange)/2 - landgi->y();
			int eolx = gamedata->active_ship->ret_MPos_X() - landgi->x(),
			eoly = gamedata->active_ship->ret_MPos_Y() - landgi->y();

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
// 	gamedata->active_ship->attribute.geschwindigkeit = gamedata->active_ship->attribute.geschwindigkeit * (1 - bremsfaktor);
	gamedata->active_ship->brake(bremsfaktor);
	}
// }
	/////Kartenrand - Mapwechsel
	int ship_xpos = gamedata->active_ship->ret_MPos_X();
	int ship_ypos = gamedata->active_ship->ret_MPos_Y();
	if(ship_xpos > gamedata->currentMap.size.width() - 120 )
		{
 		qWarning()<< "Mapwechsel zu Ost" << gamedata->currentMap.mapeast;
 		if(! gamedata->currentMap.mapeast.isEmpty())
 		{
// 			float ty = ypos;
// 			delete testschiff;
// 			karteladen(mapprops.mapeast);
// 			gamedata->active_ship->attribute.map = mapprops.mapname;
// //  			qWarning() << "Karte geladen (mapeast)";
// //  			activeship->graphicsitem->setPos(125, ypos);
// // 			qWarning() << "Pos gesetzt";
// 			centerOn(testschiff);
			return;
 		}
 		else	{
// 			  testschiff->setPos(mapprops.breite - 120,testschiff->y());
			}
		}
	else if(ship_xpos < 120 )
		{
		qWarning() << "Mapwechsel zu West" << gamedata->currentMap.mapwest;
		if(!gamedata->currentMap.mapwest.isEmpty())
		{
// 			float ty = testschiff->y();
//  			qWarning() << ty;
// 			delete testschiff;
// 			scene()-> clear();
// 			scene()-> deleteLater();
// 			karteladen(mapprops.mapwest);
// 			gamedata->active_ship->attribute.map = mapprops.mapname;
// // 			delete testschiff;
// //  			qWarning() << "Karte geladen (mapwest)";
// // 			testschiff = szene->addPixmap(QPixmap(gamedata->active_ship->attribute.filename));
// // 			testschiff = szene->add#
// // 			qWarning() << "Schiff geladen";
// 			testschiff->setPos(mapprops.breite-125,ty);
// // 			qWarning() << "Pos gesetzt";
// 			centerOn(testschiff);
// // 			setScene(szene);
// // 			qWarning() << "Szene gesetzt";
			return;
		}
		else{}
// 			testschiff->setPos(120,testschiff->y());
		}

	if(ship_ypos < 120)
		{
 		qWarning()<< "Mapwechsel zu Nord:" << gamedata->currentMap.mapnorth;
		if(! gamedata->currentMap.mapnorth.isEmpty())
		{
// 			float tx = testschiff->x();
// 			delete testschiff;

// 			karteladen(mapprops.mapnorth);
// 			gamedata->active_ship->attribute.map = mapprops.mapname;
// //  			qWarning() << "Karte geladen (mapnorth)";
// 			testschiff->setPos(tx,mapprops.hoehe-125);
// // 			qWarning() << "Pos gesetzt";
// 			centerOn(testschiff);
// 			return;
		}
		else{}
// 			testschiff->setPos(testschiff->x(), 120);
		}

	else if(ship_ypos > gamedata->currentMap.size.height() - 100)
		{
		qWarning()<< "Mapwechsel zu Sued" << gamedata->currentMap.mapnorth ;
		if(!gamedata->currentMap.mapsouth.isEmpty())
		{
		/*
			float tx = testschiff->x();
			delete testschiff;
			karteladen(mapprops.mapsouth);
			gamedata->active_ship->attribute.map = mapprops.mapname;
// 			qWarning() << "Karte geladen (mapsouth)";
			testschiff->setPos(tx, 125);
// 			qWarning() << "Pos gesetzt";
			centerOn(testschiff);
			return;*/
		}
		else{}
// 			testschiff->setPos(testschiff->x(), mapprops.hoehe - 100);
		}
// }
}
if(durchlauf%50==0
#ifndef _NO_CONTROL_LABEL_
 && fokussieren->isChecked()
#endif
)
{
// centerOn(testschiff->x(),testschiff->y());
}
}
// }

#ifndef _NO_CONTROL_LABEL_

if(durchlauf%10==0)
{
	knoten -> setText (QString("V:%1").arg(gamedata->active_ship->attribute.geschwindigkeit));
	sollknoten -> setText(QString("SollV: %1").arg(gamedata->active_ship->attribute.sollgeschwindigkeit));
	solldir -> setText(QString("SollDir %1").arg(gamedata->active_ship->attribute.sollausrichtung));
	dir -> setText(QString("Dir %1").arg(gamedata->active_ship->attribute.ausrichtung));
	steuerdir -> setText(QString("SteuerDir: %1").arg(gamedata->active_ship->attribute.steuerruderausrichtung));
	sollsteuerdir -> setText(QString("SollSteuerDir: %1").arg(gamedata->active_ship->attribute.sollsteuerruderausrichtung));
// 	segeldir -> setText(QString("SegelDir: %1").arg(gamedata->active_ship->attribute.segelausrichtung));
	segel->setText(QString("SegelFlaeche: %1").arg(gamedata->active_ship->attribute.prozentgesetzteSegel));
	sollsegel->setText(QString("SollSegelFl: %1").arg(gamedata->active_ship->attribute.sollprozentgesetzteSegel));
	segeldir -> setText(QString("SegelDir: %1").arg(gamedata->active_ship->attribute.segelausrichtung));
}
#endif

}}
///				ENDE Aktualisierung



//// HIER BEGINNT DIE BEWEGUNGSBESCHREIBUNG .........................................................


bool hauptfenster::schiffskollision(QGraphicsItem *land)
{
// int x = testschiff->x();
	if(gamedata->active_ship->ret_MPos_X() > land->x() && gamedata->active_ship->ret_MPos_Y() > land->y() && gamedata->active_ship->ret_MPos_X() < land->x() + land->boundingRect().width() && gamedata->active_ship->ret_MPos_Y() < land->y() + land->boundingRect().height() )
	{
		qWarning() << "Kollision";
	      return true;
	}
	else return false;
}

bool hauptfenster::kollision(QGraphicsItem *param_item, QGraphicsItem *param_ground)
{
	int param_item_posx = param_item->x() + param_item->boundingRect().width();
	int param_item_posy = param_item->y() + param_item->boundingRect().height();
	if(param_item_posx  > param_ground->x() && param_item_posy > param_ground->y() && param_item_posx < param_ground->x() + param_ground->boundingRect().width() && param_item_posy < param_ground->y() + param_ground->boundingRect().height() )
	{
		qWarning() << "Kollision";
	      return true;
	}
	else return false;

}

bool hauptfenster::isLand(QGraphicsItem *checkqgi)
{
	if(checkqgi->data(0).toInt() >= 100 && checkqgi->data(0).toInt() < 1000)
	{
		qWarning() << "Land";
	      return true;
	}
	else return false;
}

void hauptfenster::rotateItem(QGraphicsItem *item, double angle)
{
	const int w = item->boundingRect().width()/2;
	const int h = item->boundingRect().height()/2;

	item->resetTransform();
	QTransform t;

	t.translate( w, h );
	t.rotateRadians(- angle);
	t.translate( -w, -h );
	item->setTransform( t );
}



void hauptfenster::schuss()
{
konsolenwidget->debug(QString("void hauptfenster::schuss()"));

}
