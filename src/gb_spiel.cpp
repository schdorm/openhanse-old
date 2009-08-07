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

void gesamtbild::spiel()
{

	spielbool=true;
//  	QFile file("");		//Map-XML-Lesen
//  	if(file.exists())
	{
// 		qWarning() << "Datei existiert" ;
		for(int i = 0; i<5 ; i++)
		{
			stadt.hproduktion[i]=-1;
			stadt.mproduktion[i]=-1;
			stadt.nproduktion[i]=-1;
		}


		enum stati	{
				null,
				stadttoken,
				stadtname,
				stadt_mproduktion,
				stadt_hproduktion,
				stadt_nproduktion,
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
				if(reader.qualifiedName().toString() =="list")
				{
				break;
				}
				if(reader.qualifiedName().toString() =="stadt")
				{
				status=stadttoken;
				break;
				}
				if(reader.qualifiedName().toString() =="stadtname")
				{
				status=stadtname;
				break;
				}

				if(reader.qualifiedName().toString() =="hproduktion")
				{
				status=stadt_hproduktion;
				break;
				}
				if(reader.qualifiedName().toString() =="mproduktion")
				{
				status=stadt_mproduktion;
				break;
				}
				if(reader.qualifiedName().toString() =="nproduktion")
				{
				status=stadt_nproduktion;
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
// 				qWarning() << "Chars:" <<reader.text().toString();
				//Tags ohne Inhalt - nur mit Unterkategorien
				switch(status)
				{
				case stadttoken:
					break;
				case stadtname:
				{
				stadt.stadtname = reader.text().toString();
				qWarning() << "\tStadt: " << stadt.stadtname;
				break;
				}

				case stadt_hproduktion:
				{
				stadt.hproduktion[hz] = reader.text().toString().toInt();
				qWarning() << "\tHohe Produktion: " << stadt.hproduktion[hz] << "(wird viel produziert)";
				hz++;
				break;
				}

				case stadt_mproduktion:
				{
				stadt.mproduktion[mz] = reader.text().toString().toInt();
				qWarning() << "\tMittlere Produktion: " << stadt.mproduktion[mz] << "(wird maessig viel produziert)";
				mz++;
				break;
				}

				case stadt_nproduktion:
				{
				stadt.nproduktion[nz] = reader.text().toString().toInt();
				qWarning() << "\tNiedrige Produktion: " << stadt.nproduktion[nz] << "(wird wenig produziert)";
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
				if(reader.qualifiedName().toString() == "stadt" && !stadt.stadtname.isEmpty())
				{
				stadt.init();
				stadtliste << stadt;
				qWarning() << stadt.stadtname << " zur Liste hinzugefuegt";
				stadt.reset();
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


// 	qWarning() << "vor Spielfenster aufgebaut";

 	hf= new hauptfenster();
	spielfensteraufbau();
	qWarning() << "Spielfenster aufgebaut";

	hfgametime = &(hf->spielzeit);
	konsolenwidget->debug("timepointer set");
	hf->schwierigkeit = schwierigkeitsgrad;
	qWarning() << "Schwierigkeitsgrad:" << schwierigkeitsgrad;


	hf->karteladen("testmap001.ohm");
	hf->testschiff->setPos(1500,900);
//  	qWarning() << "StartTimer";
 	hf->starttimer();
// 	hf->setSceneRect(1,1,4000,4000);
 	qWarning() << "Timer gestartet";
	hf->show();
	hf->centerOn(hf->testschiff);
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
		menupanel->ware[i]->setText(QString("%1").arg(hf->activeship.Ladung.ware[i]));
 	}
// // 	qWarning() << "Nach Ladungszeugs";
// 	taler = new QLabel(Ladung);
// 

// // 	fuellung->setText(QString("Belegt: %1 von %2").arg(hf->activeship.Ladung.gesamtladung, hf->activeship.ladekapazitaet));
	{
 	menupanel->taler->setText(QString("%1").arg(hf->activeship.Ladung.taler).prepend(tr("Geladenes Geld: ")));
	QString flstring = QString("%1").arg(hf->activeship.Ladung.fuellung);
	flstring.append(QString("/%1 belegt").arg(hf->activeship.Ladung.kapazitaet));
	menupanel->fuellung->setText(flstring);
	}
	menupanel->show();

	gridlayout->setColumnStretch(0,7);
	gridlayout->setColumnStretch(1,2);

	connect(hf,SIGNAL(destroyed()),this,SLOT(close()));

	connect(hf,SIGNAL(handel()),this,SLOT(handel()));
// 	connect(hf,SIGNAL(handel()),hf,SLOT(hide()));

	connect(hf, SIGNAL(sig_anlegbar(bool)), menupanel->anlegen,SLOT(setEnabled(bool)));

	connect(hf, SIGNAL(Aktualisierung(int)),this,SLOT(produktion(int)));

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
			QLabel *anzeige = new QLabel(tr("Zeit: Tag %1,").arg(hfgametime->retDay()).append(QString("%1 Uhr").arg(hfgametime->retHour())), zeitw);

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
