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
#include "gesamtbild.h"
#include "stadtklasse.h"

#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
// #include <QtCore/QDir>

#include <QtCore/QtDebug>

#include <QtGui/QDialog>
// #include <QtCore/QSignalMapper>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
// #include <QtGui/QProgressBar>
// #include <QtGui/QSlider>
#include <QtGui/QGridLayout>

// #include <QtGui/QScrollArea>
/*
void gesamtbild::initGameData()
{
// gamedata = new DataClass();

}*/


void gesamtbild::startNewGame()
{
	gamedata = new DataClass();
	gamedata->active_city = new CityClass();
	spielbool=true;
//  	QFile file("");		//Map-XML-Lesen
//  	if(file.exists())
	{
// 		qWarning() << "Datei existiert" ;
		for(int i = 0; i<5 ; i++)
		{
			gamedata->active_city->hproduction[i]=-1;
			gamedata->active_city->mproduction[i]=-1;
			gamedata->active_city->lproduction[i]=-1;
		}


		enum stati	{
				null,
				stadttoken,
				city_name,
				city_mproduction,
				city_hproduction,
				city_lproduction,
				} status = null;	// status als dieses enum: zeigt an, was fuer ein Wert als naechstes ausgelesen wird

		int hz = 0;		//Zaehlvariablen fuer die jeweiligen Produktionsarrays
		int mz = 0;
		int nz = 0;

		QFile file(":maps/stadtliste.ohc");
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QXmlStreamReader reader(&file);
		while (!reader.atEnd()) 
		{
		reader.readNext();
		switch(reader.tokenType())
		{
			case QXmlStreamReader::StartElement:
			{
			qWarning() << "Start:\t" <<reader.qualifiedName().toString();
				if(reader.qualifiedName().toString() == "list")
				{
				break;
				}
				if(reader.qualifiedName().toString() == "city")
				{
				status=stadttoken;
				break;
				}
				if(reader.qualifiedName().toString() == "cityname")
				{
				status=city_name;
				break;
				}

				if(reader.qualifiedName().toString() =="hproduction")
				{
				status=city_hproduction;
				break;
				}
				if(reader.qualifiedName().toString() =="mproduction")
				{
				status=city_mproduction;
				break;
				}
				if(reader.qualifiedName().toString() =="lproduction")
				{
				status=city_lproduction;
				break;
				}
				break;
			}

			case QXmlStreamReader::Invalid:
			{
			qWarning() << "Error:" << reader.errorString() <<"\nEnde Error" ;
			break;
			}

			case QXmlStreamReader::Characters:
			{
				qWarning() << "\n\tChars:" <<reader.text().toString() << "\n";
				//Tags ohne Inhalt - nur mit Unterkategorien
				switch(status)
				{
				case stadttoken:
					break;
				case city_name:
				{
				gamedata->active_city->cityname = reader.text().toString();
				qWarning() << "\tStadt: " << gamedata->active_city->cityname;
				break;
				}

				case city_hproduction:
				{
				gamedata->active_city->hproduction[hz] = reader.text().toString().toInt();
				qWarning() << "\tHohe Produktion: " << gamedata->active_city->hproduction[hz] << "(wird viel produziert)";
				hz++;
				break;
				}

				case city_mproduction:
				{
				gamedata->active_city->mproduction[mz] = reader.text().toString().toInt();
				qWarning() << "\tMittlere Produktion: " << gamedata->active_city->mproduction[mz] << "(wird maessig viel produziert)";
				mz++;
				break;
				}

				case city_lproduction:
				{
				gamedata->active_city->lproduction[nz] = reader.text().toString().toInt();
				qWarning() << "\tNiedrige Produktion: " << gamedata->active_city->lproduction[nz] << "(wird wenig produziert)";
				nz++;
				break;
				}

				default:
					break;
				}
				break;
			}
			case QXmlStreamReader::EndElement:
			{
				qWarning() << "Ende :"<< reader.qualifiedName().toString();
				if(reader.qualifiedName().toString() == "stadt" && !gamedata->active_city->cityname.isEmpty())
				{
				gamedata->active_city->init();
				gamedata->addCity(gamedata->active_city);
				qWarning() << gamedata->active_city->cityname << " zur Liste hinzugefuegt";
				gamedata->active_city->reset();
				}
				status=null;
				break;

			}
			default:
				break;

		}
		}
	
		if (reader.hasError()) {
		qWarning() << reader.errorString();
	}
}

	qWarning() << "Stadtliste erzeugt";
// 	if(!load)
// 	{
	schwierigkeitsgrad = schwierigkeitauswahl->currentIndex();
	qWarning() << "Schwierigkeitsgrad" <<schwierigkeitsgrad;
	schwierigkeitauswahl->deleteLater();
// 	}


	qWarning() << "vor Spielfenster aufgebaut";

 	hf = new hauptfenster(gamedata);

	spielfensteraufbau();
	qWarning() << "Spielfenster aufgebaut";
// 	hf->setDataClass(gamedata);
	qWarning() << "Data set";
// 	hfgametime = &(hf->spielzeit);
// 	konsolenwidget->hfgametime = hfgametime;
// 	konsolenwidget->debug("Timepointer set");
	hf->schwierigkeit = schwierigkeitsgrad;
	qWarning() << "Schwierigkeitsgrad:" << schwierigkeitsgrad;
	gamedata->active_ship->filename = "img/schiffe/schiff_gerade_skaliert2.png";

	hf->karteladen("testmap001.ohm");
// 	hf->testschiff->setPos(1500,900);
	gamedata->active_ship->graphicsitem->setPos(1500, 900);
//  	qWarning() << "StartTimer";
	hf->starttimer();
// 	hf->setSceneRect(1,1,4000,4000);
 	qWarning() << "Timer gestartet";
// 	hf->show();
// 	hf->centerOn(hf->testschiff);
	aktiv=true;
}

void gesamtbild::spielfensteraufbau()
{
	qWarning() << "spielfensteraufbau";
	QGridLayout *gridlayout = new QGridLayout(this);		//Fuer Hauptfenster

	hf->setParent(this);
// 	hf->resize(700,700);
	hf->move(0,0);
	hf->setFocus();
	gridlayout->addWidget(hf,0,0,1,1);

// 	{
// 	QImage *img = new QImage(":img/sonstige/mapfarbdef.png");
// 	hf->schiffbar = img->pixel(0,0);
// 	hf->anlegestelle = img->pixel(0,1);
// 	hf->strand_weich = img->pixel(0,2);
// 	hf->strand_hart = img->pixel(0,3);
// 	hf->nschiffbar = img->pixel(0,4);
// 	delete img;
// 	}
// 	QImage testimg = QImage(":img/testimg/gros.gif");


	qWarning() << "SFA1";
	menupanel = new SeaTabPanel();
	menupanel->create();
	qWarning() << "created";
// 	menupanel->setParent(this);
	gridlayout->addWidget(menupanel,0,1,1,1);

	qWarning()<< "hf->setFocus(); (gb->spiel)";


// // 	qWarning() << "Vor Ladungszeugs";

	for(int i = 0; i < const_warenanzahl; i++)
 	{
		menupanel->ware[i]->setText(QString("%1").arg(gamedata->active_ship->cargo.ware[i]));
 	}
// // 	qWarning() << "Nach Ladungszeugs";
// 	taler = new QLabel(Ladung);
// 

// // 	fuellung->setText(QString("Belegt: %1 von %2").arg(gamedata->active_ship->cargo.gesamtladung, gamedata->active_ship->ladekapazitaet));
	{
 	menupanel->taler->setText(QString("%1").arg(gamedata->active_ship->cargo.taler).prepend(tr("Geladenes Geld: ")));
	QString flstring = QString("%1").arg(gamedata->active_ship->cargo.fuellung);
	flstring.append(QString("/%1 belegt").arg(gamedata->active_ship->cargo.kapazitaet));
	menupanel->fuellung->setText(flstring);
	}
	menupanel->show();

	gridlayout->setColumnStretch(0,7);
	gridlayout->setColumnStretch(1,2);

	connect(hf,SIGNAL(destroyed()),this,SLOT(close()));

	connect(hf,SIGNAL(handel()),this,SLOT(handel()));
// 	connect(hf,SIGNAL(handel()),hf,SLOT(hide()));

	connect(hf, SIGNAL(sig_anlegbar(bool)), menupanel->anlegen,SLOT(setEnabled(bool)));

	connect(hf, SIGNAL(sig_newDay(int)), this, SLOT(produktion(int)));

	connect(hf, SIGNAL(SIGgeschwindigkeit(int)), menupanel->geschwindigkeitsanzeige,SLOT(setValue(int)));

	connect(hf, SIGNAL(zeitsig()),this,SLOT(zeitanzeige()));

	connect(hf, SIGNAL(savesig()),this,SLOT(speicherndialog()));

	connect(hf, SIGNAL(menusig()), this, SLOT(spielmenu()));

	connect(menupanel->anlegen, SIGNAL(clicked()), this, SLOT(landmenu()));
	connect(menupanel->schuss, SIGNAL(clicked()), hf, SLOT(schuss()));
// 	connect(menupanel->anlegen, SIGNAL(clicked()), hf, SLOT(landgang()));
// 	connect(anlegen, SIGNAL(clicked()), anlegen, SLOT(hide()));
// 	connect(menupanel->anlegen, SIGNAL(clicked()), menupanel->ablegen, SLOT(show()));

// 	connect(menupanel->ablegen, SIGNAL(clicked()), this, SLOT(seemenu()));
// 	connect(menupanel->ablegen, SIGNAL(clicked()), hf, SLOT(ablegen()));
// 	connect(ablegen, SIGNAL(clicked()), anlegen, SLOT(show()));
// 	connect(ablegen, SIGNAL(clicked()), ablegen, SLOT(hide()));

	connect(menupanel->geschwindigkeitsregler,SIGNAL(valueChanged(int)),hf,SLOT(segelsetzen(int)));
	
	konsolenwidget = new konsole();
	konsolenwidget->resize(width(), height()/2);
	konsolenwidget->setParent(this);
	konsolenwidget->setWindowFlags(Qt::Popup);
	konsolenwidget->hide();
	connect(hf, SIGNAL(sig_konsole()), konsolenwidget, SLOT(show()));
// 	connect(konsolenwidget, SIGNAL(sig_loadMap(QString)), hf, SLOT(karteladen(QString)));
	connect(konsolenwidget, SIGNAL(sig_command(QString)), this, SLOT(execCommand(QString)));
	hf->konsolenwidget = konsolenwidget;
}



void gesamtbild::zeitanzeige(/*int dora, int hin, int may*/)
{
			qWarning() << "Zeit";


			QDialog *zeitw = new QDialog(this);
			QVBoxLayout layout(zeitw);
			QLabel *anzeige = new QLabel(tr("Zeit: Tag %1,").arg(gamedata->gametime.retDay()).append(QString("%1 Uhr").arg(gamedata->gametime.retHour())), zeitw);

// 			anzeige->setText(anzeige->text().append(QString(", %2 Uhr %3").arg( hf->stunde, hf->minute)));hf->stunde
// 			qWarning() << anzeige->text().append(QString(", %2 Uhr %3").arg( hf->stunde, hf->minute));

			QPushButton *ok = new QPushButton("Ok",zeitw);
			ok->move(50, 50);
			layout.addWidget(anzeige);
			layout.addWidget(ok);
// 			zeitw->setGeometry(width()/2,height()/2,200,100);
			zeitw->setLayout(&layout);
			zeitw->setAutoFillBackground(true);
			zeitw->move(hf->width()/2,hf->height()/2);
  			zeitw->raise();
			zeitw->show();

			connect(ok, SIGNAL(clicked()),hf,SLOT(endePause()));
			connect(ok, SIGNAL(clicked()),zeitw,SLOT(close()));
			connect(ok, SIGNAL(clicked()),zeitw,SLOT(deleteLater()));
}


void gesamtbild::spielmenu()
{
hf->startPause();
hf->setEnabled(false);
menupanel->setEnabled(false);
aktiv = false;

qWarning() << "Spielmenu";
// hf->hide();

QWidget *menuw = new QWidget(this);
QVBoxLayout layout;
QGroupBox *gb = new QGroupBox(menuw);
QPushButton *fortfahren = new QPushButton(tr("Fortfahren"),menuw);
QPushButton *speichern = new QPushButton(tr("Speichern"),menuw);
QPushButton *laden = new QPushButton(tr("Laden"),menuw);
QPushButton *verlassen = new QPushButton(tr("Verlassen"),menuw);

layout.addWidget(fortfahren);
layout.addWidget(speichern);
layout.addWidget(laden);
layout.addWidget(verlassen);

connect(fortfahren, SIGNAL(clicked()), menuw, SLOT(close()));
// connect(fortfahren, SIGNAL(clicked()), hf, SLOT(endePause()));
connect(fortfahren, SIGNAL(clicked()), this, SLOT(aktivieren()));

connect(speichern, SIGNAL(clicked()), menuw, SLOT(close()));
connect(speichern, SIGNAL(clicked()), this, SLOT(aktivieren()));
connect(speichern, SIGNAL(clicked()), this, SLOT(speicherndialog()));

connect(verlassen, SIGNAL(clicked()), this, SLOT(close()));

// QSignalMapper *sigm = new QSignalMapper(this);
// sigm->setMapping(fortfahren, true);
// connect(fortfahren, SIGNAL(clicked()), this, SLOT(setEnabled(bool)));
// connect(sigm, SIGNAL(mapped(int)), hf, SLOT(setEnabled(int)));
// connect(sigm, SIGNAL(mapped(int)), menupanel, SLOT(setEnabled(int)));


gb->setLayout(&layout);
menuw->setGeometry(width()/2-200,height()/2-200,200,400);
menuw->show();
menuw->raise();
}


void gesamtbild::aktivieren()
{
aktiv=true;
hf->setEnabled(true);
menupanel->setEnabled(true);
hf->endePause();
}


void gesamtbild::seemenu()
{
// 	tab[3]->hide();
// 	tab[4]->hide();
// 	tab[5]->hide();
// menupanel->clear();
// menupanel->removeTab(0);
// menupanel->removeTab(1);
// menupanel->removeTab(2);

	// int index;
	// 	index = menupanel->addTab(tab[0],QIcon(":img/icons/kiste_icon_alpha_hell.png") , tr("L"));
	// 	menupanel->setTabToolTip(index, tr("Warenladung des Schiffes"));
	// 
	// 	index = menupanel->addTab(tab[1],QIcon(":img/icons/steuerrad01.png"), tr("S"));
	// 	menupanel->setTabToolTip(index, tr("Steuerung des Schiffes"));
	// 
	// 	index = menupanel->addTab(tab[2], "B");
	// 	menupanel->setTabToolTip(index, tr("Besatzung des Schiffes"));

// menupanel->setTabText(0,tr("L"));
// menupanel->setTabIcon(0, QIcon(":img/icons/kiste_icon_alpha_hell.png"));
// menupanel->setTabToolTip(0, tr("Warenladung des Schiffes"));
// 
// 
// menupanel->setTabText(1, tr("S"));
// menupanel->setTabIcon(1, QIcon(":img/icons/steuerrad01.png"));
// menupanel->setTabToolTip(1, tr("Steuerung des Schiffes"));
// 
// menupanel->setTabText(2, tr("B"));
// 	menupanel->setTabToolTip(index, tr("Besatzung des Schiffes"));


}

void gesamtbild::landmenu()
{
// menupanel->landmenu();
execCommand(QString("hide sidemenu"));		//lets the sidebar disappear, isn't needed for a landwalk.

hf->landing();
// 	tab[0]->hide();
// 	tab[1]->hide();
// 	tab[2]->hide();
// menupanel->clear();
// menupanel->removeTab(0);
// menupanel->removeTab(1);
// menupanel->removeTab(2);

// int index;
// 	index = menupanel->addTab(tab[3],QIcon(":img/icons/steuerrad01.png") , tr("Schiffsmenu"));
// 	menupanel->setTabToolTip(index, tr("Schiffsaktionen und -befehle verwalten"));

// 	index = menupanel->addTab(tab[4], tr("Baumenu"));
// 	menupanel->setTabToolTip(index, tr("Gebaude bauen"));

//  	index = menupanel->addTab(tab[5],QIcon(""), tr("blah"));
//  	menupanel->setTabToolTip(index, tr("irgendwas"));
// 

// tab[3]->show();
// tab[4]->show();
// tab[5]->show();
}
