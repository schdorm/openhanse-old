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


#include "gameparameter.h"
#include "waren.h"

GameParameter::GameParameter()
{
// GoodLabelHash.insert();
m_GoodLabelHash.insert(Goods::Trunks, tr("trunks"));		//Baumstaemme
m_GoodLabelHash.insert(Goods::Shelves,tr("shelves"));		//Holzbretter
m_GoodLabelHash.insert(Goods::Charcoal, tr("charcoal"));	//Holzkohle
m_GoodLabelHash.insert(Goods::Pitch, tr("pitch"));		//Pech
m_GoodLabelHash.insert(Goods::Bricks, tr("bricks"));		//Steine/Ziegel
m_GoodLabelHash.insert(Goods::IronOre, tr("iron ore"));		//Eisenerz
m_GoodLabelHash.insert(Goods::MalleableIron, tr("malleable iron"));	//Schmiedeeisen
m_GoodLabelHash.insert(Goods::Tools, tr("tools"));		//Werkzeuge
m_GoodLabelHash.insert(Goods::Leather, tr("leather"));		//Leder
m_GoodLabelHash.insert(Goods::Wool, tr("wool"));		//Wolle
m_GoodLabelHash.insert(Goods::Cloth, tr("cloth"));		//Stoff
m_GoodLabelHash.insert(Goods::Hemp, tr("hemp"));		//Hanf

m_GoodLabelHash.insert(Goods::Beer, tr("beer"));	//Bier
m_GoodLabelHash.insert(Goods::Cereal, tr("cereal"));	//Getreide
m_GoodLabelHash.insert(Goods::Bread, tr("bread"));	//Brot
m_GoodLabelHash.insert(Goods::Salt, tr("salt"));	//Salz
m_GoodLabelHash.insert(Goods::Meat, tr("meat"));	//Fleisch
m_GoodLabelHash.insert(Goods::Fish, tr("fish"));	//Fisch
m_GoodLabelHash.insert(Goods::Cheese, tr("cheese"));	//Kaese
m_GoodLabelHash.insert(Goods::Wine, tr("wine"));	//Wein
m_GoodLabelHash.insert(Goods::Spicery, tr("spicery"));	//Gewuerze
m_GoodLabelHash.insert(Goods::Gold, tr("gold"));	//Gold
m_GoodLabelHash.insert(Goods::Jewellery, tr("jewellery"));//Schmuck

//const int const_grundpreis[const_warenanzahl] = {50, 95, 84, 67, 10000, 350, 950, 168, 270, 400, 107, 60, 130, 210, 30, 50, 300, 190, 3800, 5100, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

m_GoodBasicPriceHash[Goods::Trunks] = 50;
m_GoodBasicPriceHash[Goods::Shelves] = 95;
m_GoodBasicPriceHash[Goods::Charcoal] = 84;
m_GoodBasicPriceHash[Goods::Pitch] = 67;
m_GoodBasicPriceHash[Goods::Bricks] = 10000;
m_GoodBasicPriceHash[Goods::IronOre] = 350;
m_GoodBasicPriceHash[Goods::MalleableIron] = 950;
m_GoodBasicPriceHash[Goods::Tools] = 168;
m_GoodBasicPriceHash[Goods::Leather] = 270;
m_GoodBasicPriceHash[Goods::Wool] = 400;
m_GoodBasicPriceHash[Goods::Cloth] = 107;
m_GoodBasicPriceHash[Goods::Hemp] = 60;

m_GoodBasicPriceHash[Goods::Beer] = 50;
m_GoodBasicPriceHash[Goods::Cereal] = 1;
m_GoodBasicPriceHash[Goods::Bread] = 1;
m_GoodBasicPriceHash[Goods::Salt] = 1;
m_GoodBasicPriceHash[Goods::Meat] = 300;
m_GoodBasicPriceHash[Goods::Fish] = 190;
m_GoodBasicPriceHash[Goods::Cheese] = 90;
m_GoodBasicPriceHash[Goods::Wine] = 420;
m_GoodBasicPriceHash[Goods::Spicery] = 1000;
m_GoodBasicPriceHash[Goods::Gold] = 2000;
m_GoodBasicPriceHash[Goods::Jewellery] = 4000;
// m_GoodBasicPriceHash[Goods::] = ;
// m_GoodBasicPriceHash[Goods::] = ;

}