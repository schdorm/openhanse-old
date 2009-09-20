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

#include <QtCore/QtDebug>

#include "gesamtbild.h"
#include "handelsfenster.h"
#include "waren.h"


#include "datamanager.h"
#include "dataclass.h"
#include "gameparameter.h"

#include "stadtklasse.h"
#include "shipdata.h"

#include <math.h>

#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QButtonGroup>
#include <QtGui/QTabWidget>


// #define WARENANZAHL 20
// const int const_warenanzahl = 30;

// const int const_grundpreis[const_warenanzahl] = {50, 95, 84, 67, 10000, 350, 950, 168, 270, 400, 107, 60, 130, 210, 30, 50, 300, 190, 3800, 5100, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};


handelsfenster::handelsfenster(/*DataClass *dc*/)		//defines and declares all trading-variables
{
// GAMEDATA = dc;
QVBoxLayout *gesamtlayout = new QVBoxLayout(this);

QWidget *buttonwidget = new QWidget(this);
QHBoxLayout *buttonlayout = new QHBoxLayout;

htypgroup = new QButtonGroup(this);		//Gruppe der Radio-Buttons

htypgroup->setExclusive(true);

htyp[0] = new QRadioButton(tr("ship trade"),buttonwidget);
htyp[1] = new QRadioButton(tr("kontor trade"),buttonwidget);
htyp[2] = new QRadioButton(tr("storage transfer"),buttonwidget);
// htyp[0]->setChecked(true);
for(int i = 0; i < 3; i++)
{
	htypgroup->addButton(htyp[i], i);
	buttonlayout->addWidget(htyp[i]);
}

/*htypgroup->addButton(htyp[1]);
htypgroup->addButton(htyp[2]);*/

// buttonlayout->addWidget(htyp[0]);
// buttonlayout->addWidget(htyp[1]);
// buttonlayout->addWidget(htyp[2]);

QSpacerItem *hsp = new QSpacerItem(20,25);
// hsp->setParent(this);
buttonlayout->addSpacerItem(hsp);

m_TradeProceedsTextLabel = new QLabel(buttonwidget);
m_TradeProceedsTextLabel->setText(tr("trade balance"));	// Handelsbilanz
buttonlayout->addWidget(m_TradeProceedsTextLabel);

m_TradeProceedsLabel = new QLabel(this);
m_TradeProceedsLabel->setText(tr("(volume)"));		//(Umsatz)
buttonlayout->addWidget(m_TradeProceedsLabel);

handelsbutton = new QPushButton(tr("Trade"),buttonwidget);	// Handeln
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

// QLabel *goodname[const_warenanzahl];


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

header[0]->setText(tr("Product"));				// Ware
header[1]->setText(tr("Offered\nAmount"));	// angebotene Warenmenge
header[2]->setText(tr("Buy"));
header[3]->setText(tr("Price"));
header[4]->setText(tr("Sell"));
header[5]->setText(tr("Proceeds"));		//Erloes
header[6]->setText(tr("Store"));		// Vorrat

for(int i = 0; i< 7; i++)
{
header2[i]->setText(header[i]->text());

}
// header2[1]->setText(tr("angebotene\nWarenmenge"));
// header2[2]->setText(tr("Kauf"));
// header2[3]->setText(tr("Preis"));
// header2[4]->setText(tr("Verkauf"));
// header2[5]->setText(tr("Erloes"));
// header2[6]->setText(tr("Vorrat"));
///

for(int i=0; i < (const_warenanzahl/2); i++)
{
QLabel *goodname = new QLabel(wtab[0]);
goodname->setAlignment(Qt::AlignCenter);
goodname->setText(GAMEPARAMETER->GoodLabelHash().value(i));


QLabel *goodamount = new QLabel(wtab[0]);
goodamount->setAlignment(Qt::AlignCenter);
Storage0LabelList << goodamount;

// warenmenge[i] = new QLabel(wtab[0]);
// warenmenge[i]->setAlignment(Qt::AlignCenter);

QLabel *price = new QLabel(wtab[0]);
price->setText(tr("(price)"));
price->setAlignment(Qt::AlignCenter);
PriceLabelList << price;

QLabel *stored = new QLabel(wtab[0]);
stored->setAlignment(Qt::AlignCenter);
Storage1LabelList << stored;

QLabel *proceeds = new QLabel(wtab[0]);
proceeds->setText(tr("(proceeds)"));
proceeds->setAlignment(Qt::AlignCenter);
ProceedsLabelList << proceeds;

QSpinBox *buyamount = new QSpinBox(wtab[0]);
BuySpinboxList << buyamount;
buyamount->setRange(0,999);

QSpinBox *sellamount = new QSpinBox(wtab[0]);
SellSpinboxList << sellamount;
sellamount->setRange(0,999);


connect(buyamount, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
connect(sellamount, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

layout->addWidget(goodname, i+1, 0);
layout->addWidget(goodamount,i+1, 2);
layout->addWidget(buyamount, i+1, 4);
layout->addWidget(price, i+1, 6);
layout->addWidget(sellamount, i+1, 8);
layout->addWidget(proceeds, i+1, 10);
layout->addWidget(stored, i+1, 12);
layout->setColumnStretch(0, 2);


goodname = new QLabel(wtab[1]);
goodname->setAlignment(Qt::AlignCenter);
goodname->setText(GAMEPARAMETER->GoodLabelHash().value(i + const_warenanzahl/2));

goodamount = new QLabel(wtab[1]);
goodamount->setAlignment(Qt::AlignCenter);
Storage0LabelList << goodamount;

price = new QLabel(wtab[1]);
price->setAlignment(Qt::AlignCenter);
price->setText(tr("(price)"));
PriceLabelList << price;


stored = new QLabel(wtab[1]);
stored->setAlignment(Qt::AlignCenter);
Storage1LabelList << stored;

proceeds = new QLabel(wtab[1]);
proceeds->setText(tr("(proceeds)"));
proceeds->setAlignment(Qt::AlignCenter);
ProceedsLabelList << proceeds;


buyamount = new QSpinBox(wtab[1]);
buyamount->setRange(0,999);
BuySpinboxList << buyamount;

sellamount = new QSpinBox(wtab[1]);
sellamount->setRange(0,999);
SellSpinboxList << sellamount;

layout2->addWidget(goodname, i+1, 0);
layout2->addWidget(goodamount, i+1, 2);
layout2->addWidget(buyamount, i+1, 4);
layout2->addWidget(price, i+1, 6);
layout2->addWidget(sellamount, i+1, 8);
layout2->addWidget(proceeds, i+1, 10);
layout2->addWidget(stored, i+1, 12);
layout2->setColumnStretch(0,2);

connect(buyamount, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
connect(sellamount, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));

// for(int i =0; i < const_warenanzahl; i++)
// {
// // tradingwindow->vorrat[i]->setText(QString("%1").arg(lager.ware[i]));
// // tradingwindow->warenmenge[i]->setText(QString("%1").arg(lager2.ware[i]));
// tradingwindow->preis[i]->setText(QString("(price)"));
// tradingwindow->ProceedsLabelList[i]->setText(QString("(proceeds)"));
// tradingwindow->BuySpinboxList[i]->setRange(0,999);
// tradingwindow->SellSpinboxList[i]->setRange(0,999);
// 
// }
}
// for(int i=0; i< const_warenanzahl; i ++)
// {
// ware[i]->setText(GAMEPARAMETER->GoodLabelHash().value(i));
// }
/*
ware[]->setText(tr("Baumstaemme"));
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
ware[25]->setText(tr("Schmuck"));*/
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
// m_TradeProceedsLabel->setText(tr("(Umsatz)"));
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
connect(handelsbutton, SIGNAL(clicked()), this, SLOT(handelsaktion()));
connect(handelsbutton, SIGNAL(clicked()), this, SLOT(updateWidget()));
connect(htypgroup,SIGNAL(buttonClicked(int)), this, SLOT(buttonHandler(int)));

connect(exit, SIGNAL(clicked()), this, SLOT(close()));
connect(exit, SIGNAL(clicked()), this, SLOT(deleteLater()));
}

///******************************************************************************************************

void gesamtbild::handel()
{
gameview->slotpause();

qWarning() << "handel";


QFrame *rahmen = new QFrame(this);

rahmen->setFrameShape(QFrame::StyledPanel);
rahmen->setFrameShadow(QFrame::Sunken);
// rahmen->setPalette(QPalette(Qt::white));
// rahmen->setPalette(QPalette::Base);
 rahmen->setBackgroundRole(QPalette::Window);
// rahmen->setBackgroundRole(QPalette::Base);
 rahmen->setAutoFillBackground(true);
rahmen->setLineWidth(5);

tradingwindow = new handelsfenster();

tradingwindow->setParent(rahmen);
rahmen->setMinimumSize(753, 600);
//  rahmen->setGeometry(gameview->x(),gameview->y(),tradingwindow->width(),tradingwindow->height());
rahmen->move(gameview->x() + (gameview->width() - rahmen->width())/2, gameview->y() + (gameview->height() - rahmen->height())/2);



// tradingwindow->updateWidget();
qWarning() << "Nach HU";


connect(tradingwindow->exit,SIGNAL(clicked()),rahmen,SLOT(close()));
connect(tradingwindow->exit,SIGNAL(clicked()),rahmen,SLOT(deleteLater()));
connect(tradingwindow->exit,SIGNAL(clicked()),gameview,SLOT(show()));
connect(tradingwindow->exit,SIGNAL(clicked()),gameview,SLOT(slotpause()));

// connect(tradingwindow->handelsbutton, SIGNAL(clicked()), this, SLOT(tradingFinished()));


// connect(tradingwindow,SIGNAL(hmoeglich(bool)), tradingwindow->handelsbutton,SLOT(setEnabled(bool)));

// connect(tradingwindow->htypgroup,SIGNAL(buttonClicked(int)), tradingwindow, SLOT(buttonHandler(int)));
// tradingwindow->show();
rahmen->show();
/*
if(gameview->activeship.attribute.stadt != gameview->mapprops.stadtname)
{
tradingwindow->htyp[0]->setEnabled(false);
tradingwindow->htyp[1]->animateClick();
tradingwindow->htyp[2]->setEnabled(false);
}
bool found = false;
for (QList<kontorklasse>::iterator it = kontorliste.begin();
it != kontorliste.end();
++it)
	{
		if(it->stadt == gameview->mapprops.stadtname)
		{
			found = true;
			break;
		}
	}
if(!found)
{
tradingwindow->htyp[1]->setEnabled(false);
tradingwindow->htyp[2]->setEnabled(false);
}*/

tradingwindow->setGameData(/*GAMEDATA*/);
}

void handelsfenster::setGameData(/*DataClass *param_data*/)
{

qWarning() << "void handelsfenster::setGameData(/*DataClass *param_data*/)";


// GAMEDATA = param_data;
for(int i = 0; i < 3; i++)
{
	htyp[i]->setEnabled(false);
}

if(GAMEDATA->activeKontor()->getCityID() == GAMEDATA->activeCity()->id() && GAMEDATA->currentMap()->cityname() == GAMEDATA->activeCity()->cityname())
{
htyp [1]->setEnabled(true);
htyp[1]->animateClick();
}
if(GAMEDATA->activeShip()->currentPosition().mapcoords == GAMEDATA->currentMap()->coordinates() && GAMEDATA->currentMap()->cityname() == GAMEDATA->activeCity()->cityname())
{
htyp [0]->setEnabled(true);
htyp[0]->animateClick();

}

if(htyp[1]->isEnabled() && htyp[0]->isEnabled() )
{
htyp [2]->setEnabled(true);
}

qWarning() << "End of: void handelsfenster::setGameData(/*DataClass *param_data*/)";

}

void handelsfenster::buttonHandler(int id)
{
switch(id)
{
	case 0:
	{
		setStorage(GAMEDATA->activeShip()->cargo(), 1);
		setStorage(GAMEDATA->activeCity()->storage(), 0);
		break;
	}
	case 1:
	{
		setStorage(GAMEDATA->activeKontor()->storage(), 1);
		setStorage(GAMEDATA->activeCity()->storage(), 0);
		break;
	}
	case 2:
	{
		setStorage(GAMEDATA->activeShip()->cargo(), 1);
		setStorage(GAMEDATA->activeKontor()->storage(), 0);
		break;
	}
}
updateWidget();

}

void handelsfenster::setStorage(const Goods &param_stor, int i)
{
	if(i == 0 || i == 1)
	{
		storage[i] = param_stor;
	}
}

void handelsfenster::updateWidget()
{

// qWarning() << "Handelsupdate";


// if(tradingwindow->htyp[1]->isChecked() && tradingwindow->typ != 1)
// {
// bool found = false;
// for (QList<kontorklasse>::iterator it = kontorliste.begin();
// it != kontorliste.end();
// ++it)
// 	{
// 		if(it->stadt == gameview->mapprops.stadtname)
// 		{
// 			qWarning() << gameview->mapprops.stadtname ;
// 			kontor = *it;
// 			lager = kontor.Lager;
// 			found = true;
// 			break;
// 		}
// 	}
// 	if(found)		// Wenn der Kontor nicht gefunden wurde, dann bleibt bisherige 
// 	{
// 		for (QList<stadtklasse>::iterator it = stadtliste.begin(); it != stadtliste.end(); ++it)
// 		{
// 			if(it->stadtname == gameview->mapprops.stadtname)
// 			{
// 				qWarning() << it->stadtname << gameview->mapprops.stadtname ;
// 				stadt = *it;
// 				lager2 = stadt.stadtwaren;
// 				break;
// 				tradingwindow->typ = 1;
// 			}
// 		}
// 	}
// 	else
// 	{
// 	tradingwindow->htyp[1]->setChecked(false);
// 	tradingwindow->htyp[tradingwindow->typ]->setChecked(true);
// 	}
// }


	int sellamount_int[const_warenanzahl];
	int buyamount_int[const_warenanzahl];

	int price_int[const_warenanzahl];
//allgemeine Formel: Preis = Grundpreis * Menge + (10 * Grundpreis * Menge) / ( Stadtwaren - Menge + 3)

	int proceeds_int[const_warenanzahl]; 
//allgemeine Formel: Preis = Grundpreis * Menge + (10 * Grundpreis * Menge) / ( Stadtwaren + Menge + 3)

	int singleproceeds_int[const_warenanzahl];
	int singleprice_int[const_warenanzahl];
	int totalproceeds_int = 0;
	int totalprice_int = 0;

	int mengenbilanz = 0;

	if(htyp[0]->isChecked() || htyp[1]->isChecked())
	{
qWarning() << "0 oder 1 gecheckt";
		for (int i = 0; i < const_warenanzahl; i++)
		{
			if(BuySpinboxList[i]->value() > storage[0].good(i))
			{
				BuySpinboxList[i]->setValue(storage[0].good(i));
			}
			
			if(SellSpinboxList[i]->value() > storage[1].good(i))
			{
				SellSpinboxList[i]->setValue(storage[1].good(i));
			}

			buyamount_int[i] = BuySpinboxList[i]->value();
			sellamount_int[i] = SellSpinboxList[i]->value();
			mengenbilanz = mengenbilanz - sellamount_int[i] + buyamount_int[i];

/*

PREISFORMELN:

Nachfrage = Stueckzahl an zu kaufenden Einheiten pro Ware


GESAMTPREIS = HaendlerNachfrage * Grundpreis +
aufrunden(10 * Grundpreis * HaendlerNachfrage / (StadtAngebot - HaendlerNachfrage + 3))


Erloes = Haendlerangebot * grundpreis +
abrunden( 10 * Grundpreis * HaendlerAngebot / (StadtAngebot + HaendlerAngebot + 3))

*/
			singleprice_int[i] = GAMEPARAMETER->BasicPrice(i) + int(ceil((10 * GAMEPARAMETER->BasicPrice(i)) / (storage[1].good(i) + 2 )));

			price_int[i] = buyamount_int[i] * GAMEPARAMETER->BasicPrice(i)  + int(ceil((10 * buyamount_int[i] * GAMEPARAMETER->BasicPrice(i)) / (storage[1].good(i) - buyamount_int[i] + 3 )));

			proceeds_int[i] = sellamount_int[i] * GAMEPARAMETER->BasicPrice(i)  + int(floor((10 * sellamount_int[i] * GAMEPARAMETER->BasicPrice(i)) / (storage[1].good(i) + sellamount_int[i] + 3 )));

			singleproceeds_int[i] = GAMEPARAMETER->BasicPrice(i)  + int(floor((10 * GAMEPARAMETER->BasicPrice(i)) / (storage[1].good(i) + 4 )));

			totalprice_int += price_int[i];
			totalproceeds_int += proceeds_int[i];

// 	qWarning() << sellamount_int[i] << ProceedsLabelList[i] << singleproceeds_int[i];

			if(proceeds_int[i] > 0 )
			{
// 	tradingwindow->ProceedsLabelList[i]->setText(QString("%1 (%2)").arg(ProceedsLabelList[i], int(ProceedsLabelList[i]/sellamount_int[i])));
				ProceedsLabelList[i]->setText( QString("%1").arg(proceeds_int[i]).append(QString("(%1)").arg(int(proceeds_int[i]/sellamount_int[i]))));
			}
			else
			{
				ProceedsLabelList[i]->setText(QString("%1").arg(singleproceeds_int[i]));
			}

			if(price_int[i] > 0)
			{
// 		qWarning() << buyamount_int[i];
				PriceLabelList[i]->setText(QString("%1").arg( price_int[i] ).append( QString("(%1)").arg( int(price_int[i]/buyamount_int[i]))));
			}
			else
			{
				PriceLabelList[i]->setText(QString("%1").arg(singleprice_int[i]));
			}
			Storage0LabelList[i]->setText(QString("%1").arg(storage[0].good(i)));
			Storage1LabelList[i]->setText(QString("%1").arg(storage[1].good(i)));
		}

		int bilanz = totalproceeds_int - totalprice_int;

// qWarning() << "Nach Schleife" << totalproceeds_int << totalprice_int << bilanz << mengenbilanz;


		m_TradeProceedsLabel->setText(QString("%1").arg(bilanz));

		qWarning() << storage[0].taler() << storage[0].taler() + bilanz;

		handelsbutton->setEnabled(false);
		show();

		bool hb_e_geld = true;		// Handelsbutton enabled << Money
		bool hb_e_lager = true;		// Handelsbutton enabled << Capacity
		if(qint32(storage[0].taler() + bilanz) < 0)
		{
			hb_e_geld = false;	
// 	tradingwindow->handelsbutton->setEnabled(hb_enabled);
// 	tradingwindow->sethandelsbutton(false);
		}

// if((lager.taler + bilanz) > 0 && !tradingwindow->handelsbutton->isEnabled())
// 	{	tradingwindow->handelsbutton->setEnabled(true);	}

		if(storage[0].capacity() < storage[0].filling() + mengenbilanz )
		{
// 	tradingwindow->handelsbutton->setEnabled(false);
			hb_e_lager = false;
		}

		if((!hb_e_lager || !hb_e_geld ) && handelsbutton->isEnabled())
		{
			handelsbutton->setEnabled(false);
		}
		if((hb_e_lager && hb_e_geld ) && !handelsbutton->isEnabled())
		{
			handelsbutton->setEnabled(true);
		}
// if(lager.kapazitaet > lager.fuellung + mengenbilanz && tradingwindow->handelsbutton->isEnabled() == false && hb_enabled)
// 	{	tradingwindow->handelsbutton->setEnabled(true);	}
	storage[0].exchangeVolume() += mengenbilanz;
	}

	else if(htyp[2]->isEnabled())
	{
		for(int i = 0; i < const_warenanzahl; i++)
		{
			PriceLabelList[i]->setText(QString());
			ProceedsLabelList[i]->setText(QString());
			
			Storage0LabelList[i]->setText(QString("%1").arg(storage[0].good(i)));
			Storage1LabelList[i]->setText(QString("%1").arg(storage[1].good(i)));
			
			if(BuySpinboxList[i]->value() > storage[0].good(i))
			{
				BuySpinboxList[i]->setValue(storage[0].good(i));
			}
			
			if(SellSpinboxList[i]->value() > storage[1].good(i))
			{
				SellSpinboxList[i]->setValue(storage[1].good(i));
			}
			handelsbutton->setEnabled(true);

		}
	}
	
// 	qWarning() << "Ende Handelsupdate";
}

void handelsfenster::handelsaktion()
{

	int warek[const_warenanzahl];
	int warev[const_warenanzahl];
// 	qWarning() << "Lager.taler" << lager.taler;
	storage[0].setTaler(storage[0].taler() + m_TradeProceedsLabel->text().toInt());
// 	qWarning() << "Lager.taler" << lager.taler;

	for(int i=0; i<const_warenanzahl; i++)
	{
		warek[i] = BuySpinboxList[i]->text().toInt();
		warev[i] = SellSpinboxList[i]->text().toInt();
		storage[1].addGood(i, warek[i] - warev[i]);
	
		storage[0].addGood(i, warev[i] - warek[i]);
		// gameview->activeship.Ladung.ware[i] = lager.ware[i] ;
	}
	

	if(htyp[0]->isChecked())
	{
		GAMEDATA->activeCity()->setStorage(storage[0]);
		GAMEDATA->activeShip()->setCargo(storage[1]);
	}
	else if(htyp[1]->isChecked())
	{
		GAMEDATA->activeCity()->setStorage(storage[0]);
		GAMEDATA->activeKontor()->setStorage(storage[1]);
	}
	else if(htyp[2]->isChecked())
	{
		GAMEDATA->activeKontor()->setStorage(storage[0]);
		GAMEDATA->activeShip()->setCargo(storage[1]);
	}
/// 	gameview->activeship.Ladung = lager;
// 	qWarning() << "gameview->ASL.taler" << gameview->activeship.Ladung.taler;
// 	for(int i = 0; i<const_warenanzahl; i++)
// {
// // qWarning() << i;
// menupanel->ware[i]->setText(QString("%1").arg(gameview->activeship.Ladung.ware[i]));
// }
// 	{
// 	QString flstring = QString("%1").arg(gameview->activeship.Ladung.fuellung);
// 	flstring.append(QString("/%1 belegt").arg(gameview->activeship.Ladung.kapazitaet));
// 	menupanel->fuellung->setText(flstring);
/// 	}
// gameview->activeship.Ladung.gesamtladung += lager.mengenbilanz;

// 	qWarning() << gameview->activeship.Ladung.fuellung << gameview->activeship.Ladung.kapazitaet;

// gameview->activeship.Ladung.taler += tradingwindow->m_TradeProceedsLabel->text().toInt();

// 	taler->setText(QString("Geladenes Geld: %1 Taler").arg(gameview->activeship.Ladung.taler));
// 	menupanel->taler->setText(QString("%1").arg(gameview->activeship.Ladung.taler).prepend(tr("Geladenes Geld: ")).append(tr("Taler")));

// 	fuellung->setText(QString("Belegt: %1 von %2").arg(gameview->activeship.Ladung.fuellung, gameview->activeship.Ladung.kapazitaet));
						qWarning() << "Handel ...";
/// 	rahmen->deleteLater();

/// 	stadt.stadtwaren = lager2;
// 	for (QList<stadtklasse>::iterator it = stadtliste.begin(); it != stadtliste.end(); ++it)
// 	{
// // 		qWarning() << it->stadtname << gameview->mapprops.stadtname ;
// 		if(it->stadtname == gameview->mapprops.stadtname)
// 		{
// // 			qWarning() << it->stadtname;
// 			*it = stadt;
// 			break;
// 		}
// 	}

}
handelsfenster::~handelsfenster()
{
#ifdef _DEBUG_DESTRUCTORS
qWarning() << "Destructing Trading Window";
#endif
delete htypgroup;
delete handelsbutton;
delete exit;
delete m_TradeProceedsTextLabel;
delete m_TradeProceedsLabel;

#ifdef _DEBUG_DESTRUCTORS
qWarning() << "End of Destructing Trading Window";
#endif
}

void gesamtbild::tradingFinished()
{
	tradingwindow->hide();
	gameview->show();
	gameview->slotpause();
}