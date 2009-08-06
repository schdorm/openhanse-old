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

#include <QtCore/QtDebug>

#include "gesamtbild.h"
#include "handelsfenster.h"
#include "waren.h"

#include <math.h>

#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QButtonGroup>
#include <QtGui/QTabWidget>

// #define WARENANZAHL 20
// const int const_warenanzahl = 30;

const int grundpreis[const_warenanzahl] = {50, 95, 84, 67, 10000, 350, 950, 168, 270, 400, 107, 60, 130, 210, 30, 50, 300, 190, 3800, 5100, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};


handelsfenster::handelsfenster()
{
QVBoxLayout *gesamtlayout = new QVBoxLayout(this);

QWidget *buttonwidget = new QWidget(this);
QHBoxLayout *buttonlayout = new QHBoxLayout;

htypgroup = new QButtonGroup(this);		//Gruppe der Radio-Buttons

htyp[0] = new QRadioButton(tr("Schiffshandel"),buttonwidget);
htyp[1] = new QRadioButton(tr("Kontorhandel"),buttonwidget);
htyp[2] = new QRadioButton(tr("Lagertransfer"),buttonwidget);
// htyp[0]->setChecked(true);

htypgroup->addButton(htyp[0]);
htypgroup->addButton(htyp[1]);
htypgroup->addButton(htyp[2]);
htypgroup->setExclusive(true);

buttonlayout->addWidget(htyp[0]);
buttonlayout->addWidget(htyp[1]);
buttonlayout->addWidget(htyp[2]);

QSpacerItem *hsp = new QSpacerItem(20,25);
// hsp->setParent(this);
buttonlayout->addSpacerItem(hsp);

handelsbilanz = new QLabel(buttonwidget);
handelsbilanz->setText(tr("Handelsbilanz"));
buttonlayout->addWidget(handelsbilanz);

umsatz = new QLabel(this);
umsatz->setText(tr("(Umsatz)"));
buttonlayout->addWidget(umsatz);

handelsbutton = new QPushButton(tr("Handeln"),buttonwidget);
buttonlayout->addWidget(handelsbutton);

exit = new QPushButton(buttonwidget);
exit->setIcon(QIcon(":img/icons/rotkreuz_alpha01.png"));
buttonlayout->addWidget(exit);

buttonwidget->setLayout(buttonlayout);
gesamtlayout->addWidget(buttonwidget);


QTabWidget *warentabwidget = new QTabWidget(this);
warentabwidget->setTabPosition(QTabWidget::West);

QWidget *wtab[2];
wtab[0] = new QWidget(warentabwidget);
wtab[1] = new QWidget(warentabwidget);
// wtab[2] = new QWidget(warentabs);
warentabwidget->addTab(wtab[0], tr("Gebrauchswaren und Rohstoffe"));
warentabwidget->addTab(wtab[1], tr("Nahrungsmittel und Luxusgueter"));
// warentabs->addTab(t[2], tr("Waren 3"));


QGridLayout *layout = new QGridLayout(wtab[0]);
QGridLayout *layout2 = new QGridLayout(wtab[1]);
// QGridLayout layout3(this);

QLabel *header[7];
QLabel *header2[7];
// QLabel *header3[7];

QSpacerItem *spacer[7];
QSpacerItem *spacer2[7];

QLabel *ware[const_warenanzahl];


for(int i = 0; i<7; i++)
{
header[i] = new QLabel(wtab[0]);
header[i]->setAlignment(Qt::AlignCenter);
layout->addWidget(header[i], 0, 2*i);
spacer[i] = new QSpacerItem(25, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
layout->addItem(spacer[i], 0 , (2*i + 1) ,1,1);
// layout->addItem(spacer[i], 6, 13, 1, 1);

header2[i] = new QLabel(wtab[1]);
header2[i]->setAlignment(Qt::AlignCenter);
layout2->addWidget(header2[i], 0, 2*i);
spacer2[i] = new QSpacerItem(25, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
layout2->addItem(spacer2[i], 0 , (2*i + 1) ,1,1);
}

header[0]->setText(tr("Ware"));
header[1]->setText(tr("angebotene\nWarenmenge"));
header[2]->setText(tr("Kauf"));
header[3]->setText(tr("Preis"));
header[4]->setText(tr("Verkauf"));
header[5]->setText(tr("Erloes"));
header[6]->setText(tr("Vorrat"));

header2[0]->setText(tr("Ware"));
header2[1]->setText(tr("angebotene\nWarenmenge"));
header2[2]->setText(tr("Kauf"));
header2[3]->setText(tr("Preis"));
header2[4]->setText(tr("Verkauf"));
header2[5]->setText(tr("Erloes"));
header2[6]->setText(tr("Vorrat"));

for(int i=0; i < (const_warenanzahl/2); i++)
{
ware[i] = new QLabel(wtab[0]);
ware[i]->setAlignment(Qt::AlignCenter);

warenmenge[i] = new QLabel(wtab[0]);
warenmenge[i]->setAlignment(Qt::AlignCenter);

preis[i] = new QLabel(wtab[0]);
preis[i]->setAlignment(Qt::AlignCenter);

vorrat[i] = new QLabel(wtab[0]);
vorrat[i]->setAlignment(Qt::AlignCenter);

erloes[i] = new QLabel(wtab[0]);
erloes[i]->setAlignment(Qt::AlignCenter);


kaufmenge[i] = new QSpinBox(wtab[0]);
verkaufsmenge[i] = new QSpinBox(wtab[0]);

layout->addWidget(ware[i],i+1,0);
layout->addWidget(warenmenge[i],i+1,2);
layout->addWidget(kaufmenge[i],i+1,4);
layout->addWidget(preis[i],i+1,6);
layout->addWidget(verkaufsmenge[i],i+1,8);
layout->addWidget(erloes[i],i+1,10);
layout->addWidget(vorrat[i],i+1,12);
layout->setColumnStretch(0,2);

ware[i+15] = new QLabel(wtab[1]);
ware[i+15]->setAlignment(Qt::AlignCenter);

warenmenge[i+15] = new QLabel(wtab[1]);
warenmenge[i+15]->setAlignment(Qt::AlignCenter);

preis[i+15] = new QLabel(wtab[1]);
preis[i+15]->setAlignment(Qt::AlignCenter);

vorrat[i+15] = new QLabel(wtab[1]);
vorrat[i+15]->setAlignment(Qt::AlignCenter);

erloes[i+15] = new QLabel(wtab[1]);
erloes[i+15]->setAlignment(Qt::AlignCenter);


kaufmenge[i+15] = new QSpinBox(wtab[1]);
verkaufsmenge[i+15] = new QSpinBox(wtab[1]);

layout2->addWidget(ware[i+15],i+1,0);
layout2->addWidget(warenmenge[i+15],i+1,2);
layout2->addWidget(kaufmenge[i+15],i+1,4);
layout2->addWidget(preis[i+15],i+1,6);
layout2->addWidget(verkaufsmenge[i+15],i+1,8);
layout2->addWidget(erloes[i+15],i+1,10);
layout2->addWidget(vorrat[i+15],i+1,12);
layout2->setColumnStretch(0,2);

}

ware[0]->setText(tr("Baumstaemme"));
ware[1]->setText(tr("Holzbrett"));
ware[2]->setText(tr("Holzkohle"));
ware[3]->setText(tr("Pech"));
ware[4]->setText(tr("Steine/Ziegel"));
ware[5]->setText(tr("Eisenerz"));
ware[6]->setText(tr("Schmiedeeisen"));
ware[7]->setText(tr("Werkzeuge"));
ware[8]->setText(tr("Leder"));
ware[9]->setText(tr("Wolle"));
ware[10]->setText(tr("Stoff"));
ware[11]->setText(tr("Hanf"));


ware[15]->setText(tr("Bier"));
ware[16]->setText(tr("Getreide"));
ware[17]->setText(tr("Brot"));
ware[18]->setText(tr("Salz"));
ware[19]->setText(tr("Fleisch"));
ware[20]->setText(tr("Fisch"));
ware[21]->setText(tr("Kaese"));
ware[22]->setText(tr("Wein"));
ware[23]->setText(tr("Gewuerze"));
ware[24]->setText(tr("Gold"));
ware[25]->setText(tr("Schmuck"));
// ware[24]->setText(tr("Nicht essbares Luxusgut"));

// QFrame *line1 = new QFrame(this);
// line->setObjectName(QString::fromUtf8("line"));
// line1->setFrameShape(QFrame::VLine);
// line1->setFrameShadow(QFrame::Sunken);
// layout->addWidget(line1, 0, 15, 21, 1);
// 
// spacer[7] = new QSpacerItem(60, 20/*, QSizePolicy::Fixed*//*, QSizePolicy::Minimum*/);
// layout->addItem(spacer[7], 0 , 16 ,1,1);

// handelsbilanz = new QLabel(this);
// handelsbilanz->setText(tr("Handelsbilanz"));
// layout->addWidget(handelsbilanz,6,17,1,1);
// 
// umsatz = new QLabel(this);
// umsatz->setText(tr("(Umsatz)"));
// layout->addWidget(umsatz,7,17,1,1);
// 
// handelsbutton = new QPushButton(tr("Handeln"),this);
// layout->addWidget(handelsbutton,10,17,1,1);
// 
// exit = new QPushButton(this);
// exit->setIcon(QIcon(":img/icons/rotkreuz_alpha01.png"));
// layout->addWidget(exit,20,18,1,1);

// QFrame *line = new QFrame(this);
// // line->setObjectName(QString::fromUtf8("line"));
// line->setFrameShape(QFrame::HLine);
// line->setFrameShadow(QFrame::Sunken);
// layout->addWidget(line, 21, 0, 1, 14);

gesamtlayout->addWidget(warentabwidget);

wtab[0]->setLayout(layout);
wtab[1]->setLayout(layout2);
setLayout(gesamtlayout);
typ = -1;
}

///******************************************************************************************************

void gesamtbild::handel()
{
hf->slotpause();

qWarning() << "handel";

 for (QList<stadtklasse>::iterator it = stadtliste.begin();
 it != stadtliste.end();
 ++it)
 {
 if(it->stadtname == hf->mapprops.stadtname)
 {
//  qWarning() << it->stadtname << hf->mapprops.stadtname ;
 stadt = *it;
 lager2 = stadt.stadtwaren;
break;
 }
 }
lager = hf->activeship.Ladung;


//   lager = hf->activeship.Ladung;

rahmen = new QFrame(this);
rahmen->setGeometry(hf->x(),hf->y(),hf->width(),hf->height());
hf->hide();
// // rahmen->move(5,0);
//  rahmen->setFrameShape(QFrame::Panel);
rahmen->setFrameShadow(QFrame::Sunken);
// rahmen->setPalette(QPalette(Qt::white));
// rahmen->setPalette(QPalette::Base);
rahmen->setBackgroundRole(QPalette::Window);
// rahmen->setBackgroundRole(QPalette::Base);
rahmen->setAutoFillBackground(true);
rahmen->setLineWidth(5);

hwin = new handelsfenster();
// hwin->setPalette(QPalette(Qt::white));
// hwin->setAutoFillBackground(true);
// rahmen->resize(hwin->width(),hwin->height());
hwin->setParent(rahmen);


// lager = hf->activeship.Ladung;


for(int i =0; i < const_warenanzahl; i++)
{
// hwin->vorrat[i]->setText(QString("%1").arg(lager.ware[i]));
// hwin->warenmenge[i]->setText(QString("%1").arg(lager2.ware[i]));
hwin->preis[i]->setText(QString("(Preis)"));
hwin->erloes[i]->setText(QString("(Erloes)"));
hwin->kaufmenge[i]->setRange(0,999);
hwin->verkaufsmenge[i]->setRange(0,999);

connect(hwin->kaufmenge[i],SIGNAL(valueChanged(int)),this,SLOT(handelsupdate()));
connect(hwin->verkaufsmenge[i],SIGNAL(valueChanged(int)),this,SLOT(handelsupdate()));
}

handelsupdate();
qWarning() << "Nach HU";


connect(hwin->exit,SIGNAL(clicked()),rahmen,SLOT(close()));
connect(hwin->exit,SIGNAL(clicked()),rahmen,SLOT(deleteLater()));
connect(hwin->exit,SIGNAL(clicked()),hf,SLOT(show()));
connect(hwin->exit,SIGNAL(clicked()),hf,SLOT(slotpause()));

connect(hwin->handelsbutton,SIGNAL(clicked()),this,SLOT(handelsaktion()));
connect(hwin,SIGNAL(hmoeglich(bool)), hwin->handelsbutton,SLOT(setEnabled(bool)));

connect(hwin->htypgroup,SIGNAL(buttonClicked(int)),this,SLOT(handelsupdate()));
// hwin->show();
rahmen->show();

if(hf->activeship.attribute.stadt != hf->mapprops.stadtname)
{
hwin->htyp[0]->setEnabled(false);
hwin->htyp[1]->animateClick();
hwin->htyp[2]->setEnabled(false);
}
bool found = false;
for (QList<kontorklasse>::iterator it = kontorliste.begin();
it != kontorliste.end();
++it)
	{
		if(it->stadt == hf->mapprops.stadtname)
		{
			found = true;
			break;
		}
	}
if(!found)
{
hwin->htyp[0]->animateClick();
hwin->htyp[1]->setEnabled(false);
hwin->htyp[2]->setEnabled(false);
}


}


void gesamtbild::handelsupdate()
{
// static quint8 typ;
qWarning() << "Handelsupdate";
// hwin->handelsbutton->setEnabled(false);
// hwin->handelsbutton->repaint();

if(hwin->htyp[0]->isChecked() && hwin->typ !=0)
{
for (QList<stadtklasse>::iterator it = stadtliste.begin();
it != stadtliste.end();
++it)
	{
		if(it->stadtname == hf->mapprops.stadtname)
		{
			qWarning() << it->stadtname << hf->mapprops.stadtname ;
			stadt = *it;
			lager2 = stadt.stadtwaren;
			break;
		}
	}

lager = hf->activeship.Ladung;

hwin->typ = 0;
}


if(hwin->htyp[1]->isChecked() && hwin->typ != 1)
{
bool found = false;
for (QList<kontorklasse>::iterator it = kontorliste.begin();
it != kontorliste.end();
++it)
	{
		if(it->stadt == hf->mapprops.stadtname)
		{
			qWarning() << hf->mapprops.stadtname ;
			kontor = *it;
			lager = kontor.Lager;
			found = true;
			break;
		}
	}
	if(found)		// Wenn der Kontor nicht gefunden wurde, dann bleibt bisherige 
	{
		for (QList<stadtklasse>::iterator it = stadtliste.begin(); it != stadtliste.end(); ++it)
		{
			if(it->stadtname == hf->mapprops.stadtname)
			{
				qWarning() << it->stadtname << hf->mapprops.stadtname ;
				stadt = *it;
				lager2 = stadt.stadtwaren;
				break;
				hwin->typ = 1;
			}
		}
	}
	else
	{
	hwin->htyp[1]->setChecked(false);
	hwin->htyp[hwin->typ]->setChecked(true);
	}
}


int mengev[const_warenanzahl];
int mengek[const_warenanzahl];

int preis[const_warenanzahl];		//allgemeine Formel: Preis = Grundpreis * Menge + (10 * Grundpreis * Menge) / ( Stadtwaren - Menge + 3)

int erloes[const_warenanzahl]; 	//allgemeine Formel: Preis = Grundpreis * Menge + (10 * Grundpreis * Menge) / ( Stadtwaren + Menge + 3)

int stueckerloes[const_warenanzahl];
int stueckpreis[const_warenanzahl];
int gesamterloes = 0;
int gesamtpreis = 0;

int mengenbilanz = 0;

if(hwin->htyp[0]->isChecked() || hwin->htyp[1]->isChecked())
{
// qWarning() << "0 oder 1 gecheckt";
for (int i = 0; i<const_warenanzahl; i++)
{
	if(hwin->kaufmenge[i]->value() <= lager2.ware[i])
	{
	hwin->kaufmenge[i]->setValue(hwin->kaufmenge[i]->value());
	}
	else
	{
	hwin->kaufmenge[i]->setValue(lager2.ware[i]);
	}

	if(hwin->verkaufsmenge[i]->value() <= lager.ware[i])
	{
	hwin->verkaufsmenge[i]->setValue(hwin->verkaufsmenge[i]->value());
	}
	else
	{
	hwin->verkaufsmenge[i]->setValue(lager.ware[i]);
	}

	mengek[i] = hwin->kaufmenge[i]->value();
	mengev[i] = hwin->verkaufsmenge[i]->value();
	mengenbilanz = mengenbilanz - mengev[i] + mengek[i];

	stueckpreis[i] = grundpreis[i]  + int(ceil((10 * grundpreis[i]) / (lager2.ware[i] + 2 )));

	preis[i] = mengek[i] * grundpreis[i]  + int(ceil((10 * mengek[i] * grundpreis[i]) / (lager2.ware[i] - mengek[i] + 3 )));

	erloes[i] = mengev[i] * grundpreis[i]  + int(floor((10 * mengev[i] * grundpreis[i]) / (lager2.ware[i] + mengev[i] + 3 )));

	stueckerloes[i] = grundpreis[i]  + int(floor((10 * grundpreis[i]) / (lager2.ware[i] + 4 )));

	gesamtpreis += preis[i];
	gesamterloes += erloes[i];

	{
// 	qWarning() << mengev[i] << erloes[i] << stueckerloes[i];

		if(erloes[i]>0)
		{
// 	hwin->erloes[i]->setText(QString("%1 (%2)").arg(erloes[i], int(erloes[i]/mengev[i])));
		hwin->erloes[i]->setText( QString("%1").arg(erloes[i]).append(QString("(%1)").arg(int(erloes[i]/mengev[i]))));
		}
		else
		{
		hwin->erloes[i]->setText(QString("%1").arg(stueckerloes[i]));
		}
	}
	{
		if(preis[i]>0)
		{
// 		qWarning() << mengek[i];
		hwin->preis[i]->setText( QString("%1").arg(preis[i]).append(QString("(%1)").arg(int(preis[i]/mengek[i]))));
		}
		else
		{
		hwin->preis[i]->setText(QString("%1").arg(stueckpreis[i]));
		}
	}
}

int bilanz = gesamterloes - gesamtpreis;

// qWarning() << "Nach Schleife" << gesamterloes << gesamtpreis << bilanz << mengenbilanz;
for(int i = 0; i < const_warenanzahl; i++)
{
hwin->vorrat[i]->setText(QString("%1").arg(lager.ware[i]));
hwin->warenmenge[i]->setText(QString("%1").arg(lager2.ware[i]));
}

hwin->umsatz->setText(QString("%1").arg(bilanz));

qWarning() << lager.taler << lager.taler + bilanz; hwin->handelsbutton->setEnabled(false); hwin->show();
bool hb_e_geld = true;
bool hb_e_lager = true;
if(qint32(lager.taler + bilanz) < 0)
	{
	hb_e_geld = false;	
// 	hwin->handelsbutton->setEnabled(hb_enabled);
// 	hwin->sethandelsbutton(false);
	}

// if((lager.taler + bilanz) > 0 && !hwin->handelsbutton->isEnabled())
// 	{	hwin->handelsbutton->setEnabled(true);	}

if(lager.kapazitaet < lager.fuellung + mengenbilanz )
	{
// 	hwin->handelsbutton->setEnabled(false);
	hb_e_lager = false;
	}

if((!hb_e_lager || !hb_e_geld ) && hwin->handelsbutton->isEnabled())
{
	hwin->handelsbutton->setEnabled(false);
}
if((hb_e_lager && hb_e_geld ) && !hwin->handelsbutton->isEnabled())
{
	hwin->handelsbutton->setEnabled(true);
}
// if(lager.kapazitaet > lager.fuellung + mengenbilanz && hwin->handelsbutton->isEnabled() == false && hb_enabled)
// 	{	hwin->handelsbutton->setEnabled(true);	}

// qWarning() << "Button-Zeugs";
}
lager.mengenbilanz += mengenbilanz;
}

void gesamtbild::handelsaktion()
{

	int warek[const_warenanzahl];
	int warev[const_warenanzahl];
// 	qWarning() << "Lager.taler" << lager.taler;
	lager.taler += hwin->umsatz->text().toInt();
// 	qWarning() << "Lager.taler" << lager.taler;

	for(int i=0; i<const_warenanzahl; i++)
	{
	warek[i] = hwin->kaufmenge[i]->text().toInt();
	warev[i] = hwin->verkaufsmenge[i]->text().toInt();
	lager2.ware[i] = lager.ware[i] + warev[i] - warek[i];
	
	lager.ware[i] = lager.ware[i] - warev[i] + warek[i];
	// hf->activeship.Ladung.ware[i] = lager.ware[i] ;
	}
	hf->activeship.Ladung = lager;
// 	qWarning() << "hf->ASL.taler" << hf->activeship.Ladung.taler;
	for(int i = 0; i<const_warenanzahl; i++)
{
// qWarning() << i;
menupanel->ware[i]->setText(QString("%1").arg(hf->activeship.Ladung.ware[i]));
}
	{
	QString flstring = QString("%1").arg(hf->activeship.Ladung.fuellung);
	flstring.append(QString("/%1 belegt").arg(hf->activeship.Ladung.kapazitaet));
	menupanel->fuellung->setText(flstring);
	}
// hf->activeship.Ladung.gesamtladung += lager.mengenbilanz;

// 	qWarning() << hf->activeship.Ladung.fuellung << hf->activeship.Ladung.kapazitaet;

// hf->activeship.Ladung.taler += hwin->umsatz->text().toInt();

// 	taler->setText(QString("Geladenes Geld: %1 Taler").arg(hf->activeship.Ladung.taler));
	menupanel->taler->setText(QString("%1").arg(hf->activeship.Ladung.taler).prepend(tr("Geladenes Geld: ")).append(tr("Taler")));

// 	fuellung->setText(QString("Belegt: %1 von %2").arg(hf->activeship.Ladung.fuellung, hf->activeship.Ladung.kapazitaet));
						qWarning() << "Handel ...";
	rahmen->deleteLater();

	stadt.stadtwaren = lager2;
	for (QList<stadtklasse>::iterator it = stadtliste.begin(); it != stadtliste.end(); ++it)
	{
// 		qWarning() << it->stadtname << hf->mapprops.stadtname ;
		if(it->stadtname == hf->mapprops.stadtname)
		{
// 			qWarning() << it->stadtname;
			*it = stadt;
			break;
		}
	}
	hf->show();
	hf->slotpause();
}
