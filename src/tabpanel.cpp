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

#include "tabpanel.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QScrollArea>

#include <QDebug>


void TabPanel::create()
{
	qWarning() << "Create";
// 	QVBoxLayout tablayout[3];




	for(int i = 0; i < 3; i++)
	{
		tab[i] = new QWidget(this);
	}

	qWarning() << "Create2";

	int index;
	index = addTab(tab[0], QIcon(":img/icons/kiste_icon_alpha_hell.png") , tr("L"));
// 	index = menutabs->addTab(w1,QIcon(":fass03_weich_heller.png") , tr("Lad."));
	setTabToolTip(index, tr("Warenladung des Schiffes"));

	index = addTab(tab[1], QIcon(":img/icons/steuerrad01.png"), tr("S"));
	setTabToolTip(index, tr("Steuerung des Schiffes"));

	index = addTab(tab[2], "B");
	setTabToolTip(index, tr("Besatzung des Schiffes"));
// 	menutabs->setGeometry(800, 2, 225, 655);
// 	resize(225,655);
	qWarning() << "Create3";

	steuerung = new QWidget(tab[1]);

	QVBoxLayout *steuerungslayout = new QVBoxLayout(steuerung);

// 	steuerung->resize(tab[1].width(),tab[1].height());

// 	ablegen = new QPushButton(tr("Ablegen"),steuerung);
// 	menutabs->addTab(ablegen, tr("Ablegen"));
// 	anlegen->setEnabled(false);
// 	anlegen->move(810,10);
// 	ablegen->move(810,10);
// 	anlegen->show();
// 	ablegen->hide();
// 	qWarning() << "Create4";


	geschwindigkeitsregler = new QSlider(steuerung);
// 	geschwindigkeitsregler->setGeometry(5,40,200,45);
	geschwindigkeitsregler->setRange(0,5);
	geschwindigkeitsregler->setOrientation(Qt::Horizontal);
	geschwindigkeitsregler->setToolTip(tr("Diesen Regler verschieben um Anzahl\n der gesetzten Segel zu aendern."));
	steuerungslayout->addWidget(geschwindigkeitsregler);
// 	qWarning() << "Create5";


	geschwindigkeitsanzeige = new QProgressBar(steuerung);
// 	geschwindigkeitsanzeige->setGeometry(5,100,200,30);
	geschwindigkeitsanzeige->setOrientation(Qt::Horizontal);
// 	geschwindigkeitsanzeige->setRange(0,20);
// 	geschwindigkeitsanzeige->setText(tr("Schiffsgeschwindigkeit"));
	steuerungslayout->addWidget(geschwindigkeitsanzeige);


	anlegen = new QPushButton(tr("Anlegen"),steuerung);
	steuerungslayout->addWidget(anlegen);

	schuss = new QPushButton(tr("Feuer!"),steuerung);
	steuerungslayout->addWidget(schuss);

	steuerung->setLayout(steuerungslayout);
// 	qWarning() << "Vor Ladungszeugs";


// 	qWarning() << "Create6";


	ladung = new QWidget(tab[0]);
// 	QScrollArea ladungsanzeige/* = new QScrollArea(ladung)*/;
// 	ladungsanzeige.setWidget(ladung);
	QGridLayout *ladungslayout = new QGridLayout(ladung);

// 	QScrollArea *ladungsanzeige = new QScrollArea(tab[0]);
// 	ladungsanzeige->setWidget(ladung);
// 	ladung->resize(width()-50,height()-10);
// 	tab[0]->resize(300,300);
// 	QVBoxLayout laly(tab[0]);
// 	laly.addWidget(ladung);

	qWarning() << "Create7";


// 	for(int i = 0; i < const_warenanzahl; i++)
// 	{
// 		ware[i] = new QLabel(ladung/*sanzeige*/);
// // 		ware[i]->setText(QString("%1").arg(hf->activeship.Ladung.ware[i]));
// 		ladungslayout.addWidget(ware[i]);
// 	}
	fuellung = new QLabel(ladung/*sanzeige*/);
	ladungslayout->addWidget(fuellung,0,0,1,2);
	taler = new QLabel(ladung);
	ladungslayout->addWidget(taler,1,0,1,2);


	for(int i = 0; i < const_warenanzahl; i++)
	{
		ware[i] = new QLabel(ladung);
// 		ware[i]->setText(QString("%1").arg(hf->activeship.Ladung.ware[i]));
		ladungslayout->addWidget(ware[i],i/2+2,i%2);
	}


// 	qWarning() << "Nach Ladungszeugs";


// 	taler->setText(QString("%1").arg(hf->activeship.Ladung.taler).prepend(tr("Geladenes Geld: ")));


// 	fuellung->setText(QString("Belegt: %1 von %2").arg(hf->activeship.Ladung.gesamtladung, hf->activeship.ladekapazitaet));
// 	{
// 	QString flstring = QString("%1").arg(hf->activeship.Ladung.fuellung);
// 	flstring.append(QString("/%1 belegt").arg(hf->activeship.Ladung.kapazitaet));
// 	fuellung->setText(flstring);
// 	}

	ladung->setLayout(ladungslayout);

	qWarning() << "Create8";

// 	tab[0]->setLayout(&tab0layout);
// 	QWidget *baumenu = new QWidget(tab[4]);
// QPushButton *geb[5];
// geb[0] = new QPushButton(tr("Kontor"), baumenu);

// 	QSpacerItem *spacer = new QSpacerItem(600,48);

// 	gridlayout->addWidget(hf,0,0,1,1);
// 	gridlayout->addWidget(menutabs,0,1,1,1);
// // 	gridlayout->addItem(spacer,1,0,1,1);
// 
// 	gridlayout->setColumnStretch(0,7);
// 	gridlayout->setColumnStretch(1,2);
}


void TabPanel::landmenu()
{
steuerung->hide();
ladung->hide();
}
