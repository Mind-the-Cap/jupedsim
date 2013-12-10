/**
 * @file    SafestPathRouter.cpp
 * Created on: 29.11.2013
 * Copyright (C) <2009-2013>
 *
 * @section LICENSE
 * This file is part of JuPedSim.
 *
 * JuPedSim is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JuPedSim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JuPedSim. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * This class computes the safest path for pedestrians based on information
 * received from FDS
 *
 */


#include "SafestPathRouter.h"

#include "../pedestrian/Pedestrian.h"

using namespace std;

SafestPathRouter::SafestPathRouter() {

}

SafestPathRouter::~SafestPathRouter() {

}

void SafestPathRouter::Init(Building* building) {
	//Load the FDS file info

	//handle over to the global router engine
	GlobalRouter::Init(building);
}


int SafestPathRouter::FindExit(Pedestrian* p) {
	if(ComputeSafestPath(p)==-1) {
		//Log->Write(" sdfds");
	}
	//handle over to the global router engine
	return GlobalRouter::FindExit(p);
}


int SafestPathRouter::ComputeSafestPath(Pedestrian* p) {

//	int sectionNR = p->GetSubRoomID();
//
//	if (p->GetSubRoomID()==1) {
//		p->SetFinalDestination(0);
//		int TotalNumberofPedInsetion=_building->GetRoom(p->GetRoomID())->GetSubRoom(p->GetSubRoomID())->GetAllPedestrians().size();
//	}

	if(p->GetGlobalTime()>23) {
		if(p->GetFinalDestination()==1)
			if (p->GetID()==1){
				p->SetFinalDestination(0);
				cout<<"changing destination of "<< p->GetID()<<"from "<<p->GetFinalDestination()<< " to 1 at time ";
				p->ClearMentalMap(); // reset the destination
				cout<<p->GetGlobalTime()<<endl;
				getc(stdin);
			}
	}
	return -1;
}

void SafestPathRouter::Initialize(){
	ReadMatrixFromFDS();
}


void SafestPathRouter::ReadMatrixFromFDS(){

	const double dMatrixPreEvac[1][11]={0.000528,0.000302,0.000542,0.000599,0.000448,0.003289,0.003289,0.001078,0.000898,0.000204,0.000355};
	const double dFinalLength[1][11]={0.638,0.569,0.362,0.414,0.586,0.328,0.328,1.000,0.276,0.759,0.741};
	const double dFinalMatrixOFP[300][11]={{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,29.68,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,30.00,28.56,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,29.73,25.02,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,26.26,24.32,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,24.22,23.33,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,24.57,23.11,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,26.15,24.23,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,25.47,23.83,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,23.54,22.88,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,22.12,21.99,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,22.33,22.44,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,21.95,23.44,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,21.08,24.01,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,20.76,23.40,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,20.83,22.28,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,21.34,20.46,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,21.17,19.02,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,20.83,18.44,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,20.54,19.17,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,20.38,19.51,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,19.39,18.15,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.31,17.07,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.61,17.96,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,17.42,17.77,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.87,15.96,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,17.47,16.49,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.96,17.28,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.09,16.50,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.28,15.63,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.15,13.79,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.46,13.39,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.64,14.34,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,16.31,13.91,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,14.95,13.78,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,12.44,13.60,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,11.32,12.01,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,12.90,12.19,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,13.69,13.48,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,13.87,13.86,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,30.00,12.75,12.96,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,29.70,13.00,12.46,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,28.35,13.21,12.35,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,27.42,11.26,11.55,30.00,30.00,30.00,30.00,30.00,30.00},
			{30.00,30.00,27.55,10.85,10.99,30.00,30.00,30.00,29.75,30.00,30.00},
			{30.00,30.00,28.15,11.93,11.39,30.00,30.00,30.00,29.15,30.00,30.00},
			{30.00,30.00,28.98,11.46,11.17,30.00,30.00,30.00,28.43,30.00,30.00},
			{30.00,30.00,29.02,10.17,10.25,30.00,30.00,30.00,27.85,30.00,30.00},
			{30.00,30.00,28.51,10.60,10.56,30.00,30.00,30.00,27.08,30.00,30.00},
			{30.00,30.00,27.25,10.53,11.02,30.00,30.00,30.00,25.61,30.00,30.00},
			{30.00,30.00,26.09,10.67,10.94,30.00,30.00,30.00,24.14,30.00,30.00},
			{30.00,30.00,24.89,10.84,10.78,30.00,30.00,30.00,22.77,30.00,30.00},
			{30.00,30.00,23.10,10.73,9.93,30.00,30.00,30.00,21.83,30.00,30.00},
			{30.00,30.00,22.07,10.25,9.43,30.00,30.00,30.00,21.65,30.00,30.00},
			{30.00,30.00,21.71,9.93,10.19,30.00,30.00,30.00,21.51,30.00,30.00},
			{30.00,30.00,22.21,9.48,10.63,30.00,30.00,30.00,21.20,30.00,30.00},
			{30.00,30.00,22.68,9.70,9.77,30.00,30.00,30.00,20.91,30.00,30.00},
			{30.00,30.00,22.78,10.41,9.44,30.00,30.00,30.00,20.65,30.00,30.00},
			{30.00,30.00,21.89,10.48,9.66,30.00,30.00,30.00,20.43,30.00,30.00},
			{30.00,30.00,20.60,10.43,9.52,30.00,30.00,30.00,20.27,30.00,30.00},
			{30.00,30.00,19.34,10.23,9.43,30.00,30.00,30.00,20.04,30.00,30.00},
			{30.00,30.00,17.99,8.98,8.07,30.00,30.00,30.00,19.44,30.00,30.00},
			{30.00,30.00,17.36,9.05,7.94,30.00,30.00,30.00,18.76,30.00,30.00},
			{30.00,30.00,17.11,9.91,8.47,30.00,30.00,30.00,18.06,30.00,30.00},
			{30.00,30.00,17.42,8.50,8.34,30.00,30.00,30.00,17.49,30.00,30.00},
			{30.00,30.00,17.82,7.92,8.26,30.00,30.00,30.00,17.34,30.00,30.00},
			{30.00,30.00,18.11,8.31,8.40,30.00,30.00,30.00,17.20,30.00,30.00},
			{30.00,30.00,18.19,8.24,8.42,30.00,30.00,30.00,16.95,30.00,30.00},
			{30.00,30.00,18.01,8.32,8.09,30.00,30.00,30.00,16.78,30.00,30.00},
			{30.00,30.00,17.66,8.13,7.75,30.00,30.00,30.00,16.66,30.00,30.00},
			{30.00,30.00,16.95,8.11,8.12,30.00,30.00,30.00,16.42,30.00,30.00},
			{30.00,30.00,16.45,8.07,8.19,30.00,30.00,30.00,16.13,30.00,30.00},
			{30.00,30.00,16.22,7.82,7.65,30.00,30.00,30.00,15.77,30.00,30.00},
			{30.00,30.00,16.26,7.81,7.83,30.00,30.00,30.00,15.41,30.00,30.00},
			{30.00,30.00,16.37,7.84,8.12,30.00,30.00,30.00,15.31,30.00,30.00},
			{30.00,30.00,16.43,7.95,7.99,30.00,30.00,30.00,15.23,30.00,30.00},
			{30.00,30.00,16.36,7.73,7.83,30.00,30.00,30.00,14.91,30.00,30.00},
			{30.00,30.00,16.01,7.63,8.03,30.00,30.00,30.00,14.43,30.00,30.00},
			{30.00,30.00,15.22,7.63,7.72,30.00,30.00,30.00,13.92,30.00,30.00},
			{30.00,30.00,13.88,7.28,7.45,30.00,30.00,30.00,13.49,30.00,30.00},
			{30.00,30.00,13.31,7.01,7.62,30.00,30.00,30.00,13.31,30.00,30.00},
			{30.00,30.00,13.39,7.03,7.21,30.00,30.00,30.00,13.25,30.00,30.00},
			{30.00,30.00,13.75,7.20,7.01,30.00,30.00,30.00,13.34,30.00,30.00},
			{30.00,30.00,13.69,7.16,7.66,30.00,30.00,30.00,13.38,30.00,30.00},
			{30.00,30.00,13.28,6.88,7.90,30.00,30.00,30.00,13.34,30.00,30.00},
			{30.00,30.00,12.48,6.01,7.36,30.00,30.00,30.00,13.20,30.00,30.00},
			{30.00,30.00,12.00,6.43,6.64,30.00,30.00,30.00,13.05,30.00,30.00},
			{30.00,30.00,11.89,6.96,6.04,30.00,30.00,30.00,12.89,30.00,30.00},
			{30.00,30.00,12.12,6.73,6.14,30.00,30.00,30.00,12.61,30.00,30.00},
			{30.00,30.00,12.29,6.68,6.14,30.00,30.00,30.00,12.35,30.00,30.00},
			{30.00,30.00,12.44,6.90,6.52,30.00,30.00,30.00,12.11,30.00,30.00},
			{30.00,30.00,12.59,6.81,6.72,30.00,30.00,30.00,12.02,30.00,30.00},
			{30.00,30.00,12.60,6.73,6.67,30.00,30.00,30.00,12.03,30.00,30.00},
			{30.00,30.00,12.44,6.54,6.42,30.00,30.00,30.00,11.98,30.00,30.00},
			{30.00,30.00,11.99,6.21,5.80,30.00,30.00,30.00,11.81,30.00,30.00},
			{30.00,30.00,11.57,6.05,5.57,30.00,30.00,30.00,11.65,30.00,30.00},
			{30.00,30.00,11.18,6.23,5.92,30.00,30.00,30.00,11.47,30.00,30.00},
			{30.00,30.00,10.81,6.43,6.30,30.00,30.00,30.00,11.21,30.00,30.00},
			{30.00,30.00,10.63,6.34,6.29,30.00,30.00,30.00,11.05,30.00,30.00},
			{30.00,30.00,10.42,6.21,6.11,30.00,30.00,30.00,10.89,30.00,30.00},
			{30.00,30.00,10.16,6.22,5.76,30.00,30.00,30.00,10.80,30.00,30.00},
			{30.00,30.00,9.99,6.71,6.15,30.00,30.00,30.00,10.81,30.00,30.00},
			{30.00,30.00,10.12,6.97,6.29,30.00,30.00,30.00,10.79,30.00,30.00},
			{30.00,30.00,10.36,6.67,6.21,30.00,30.00,30.00,10.42,30.00,30.00},
			{30.00,30.00,10.41,6.10,5.95,30.00,30.00,30.00,9.70,30.00,29.79},
			{30.00,30.00,10.32,5.63,5.38,30.00,30.00,30.00,9.27,30.00,29.05},
			{30.00,30.00,10.16,6.06,5.66,30.00,30.00,30.00,9.48,30.00,28.22},
			{30.00,30.00,10.10,5.89,5.55,30.00,30.00,30.00,9.73,30.00,27.66},
			{30.00,30.00,10.10,5.90,5.52,30.00,30.00,30.00,9.95,30.00,27.16},
			{30.00,30.00,10.03,5.76,5.27,30.00,30.00,30.00,10.06,30.00,26.61},
			{30.00,30.00,9.85,5.44,4.89,30.00,30.00,30.00,9.97,30.00,26.21},
			{30.00,30.00,9.69,5.47,5.25,30.00,30.00,30.00,9.69,30.00,25.89},
			{30.00,30.00,9.65,5.48,5.06,30.00,30.00,30.00,9.07,30.00,25.47},
			{30.00,30.00,9.72,5.76,5.11,30.00,30.00,30.00,8.85,30.00,25.19},
			{30.00,30.00,9.75,5.87,5.37,30.00,30.00,30.00,8.86,30.00,24.95},
			{30.00,29.53,9.63,5.59,5.13,30.00,30.00,30.00,8.95,30.00,24.60},
			{30.00,28.37,9.46,4.98,4.81,30.00,30.00,30.00,8.98,30.00,24.30},
			{30.00,27.33,9.34,5.40,5.35,30.00,30.00,30.00,8.93,30.00,23.98},
			{30.00,26.34,9.32,5.79,5.38,30.00,30.00,30.00,8.80,30.00,23.58},
			{30.00,25.78,9.35,5.66,5.43,30.00,30.00,30.00,8.67,30.00,23.27},
			{30.00,25.34,9.28,5.84,5.54,30.00,30.00,30.00,8.54,30.00,23.00},
			{30.00,24.80,8.96,6.17,5.64,30.00,30.00,30.00,8.31,30.00,22.65},
			{30.00,24.27,8.67,6.20,5.74,30.00,30.00,30.00,8.11,30.00,22.29},
			{30.00,23.69,8.62,6.13,5.75,30.00,30.00,30.00,7.95,30.00,21.87},
			{30.00,22.78,8.80,6.05,5.58,30.00,30.00,30.00,7.85,30.00,21.04},
			{30.00,22.23,8.78,6.15,5.62,30.00,30.00,30.00,7.80,30.00,20.40},
			{30.00,21.83,8.53,6.31,5.91,30.00,30.00,30.00,7.70,30.00,19.86},
			{30.00,21.50,8.18,6.35,6.20,30.00,30.00,30.00,7.58,30.00,19.35},
			{30.00,21.33,8.18,6.34,6.32,30.00,30.00,30.00,7.54,30.00,19.04},
			{30.00,21.17,8.31,6.44,6.40,30.00,30.00,30.00,7.54,30.00,18.72},
			{30.00,20.96,8.35,6.55,6.40,30.00,30.00,30.00,7.54,30.00,18.28},
			{30.00,20.79,8.25,6.48,6.36,30.00,30.00,30.00,7.54,29.46,18.02},
			{30.00,20.60,8.08,6.37,6.35,30.00,30.00,30.00,7.53,28.26,17.88},
			{30.00,20.26,7.91,6.49,6.42,30.00,30.00,30.00,7.55,26.55,17.83},
			{30.00,19.96,7.94,6.73,6.56,30.00,30.00,30.00,7.61,25.43,17.83},
			{30.00,19.69,8.11,6.90,6.67,30.00,30.00,30.00,7.69,24.70,17.80},
			{30.00,19.38,8.44,7.00,6.48,30.00,30.00,30.00,7.82,24.27,17.65},
			{30.00,19.23,8.66,6.96,5.92,30.00,30.00,30.00,7.90,24.30,17.45},
			{30.00,19.13,8.83,6.73,5.96,30.00,30.00,30.00,7.96,24.44,17.24},
			{30.00,19.02,8.98,6.18,6.42,30.00,30.00,30.00,8.01,24.57,16.99},
			{30.00,18.93,9.03,6.14,6.29,30.00,30.00,30.00,8.03,24.48,16.86},
			{30.00,18.82,9.06,6.47,6.06,30.00,30.00,30.00,8.05,24.17,16.77},
			{30.00,18.64,9.07,6.85,6.08,30.00,30.00,30.00,8.07,23.44,16.66},
			{30.00,18.43,9.06,6.73,6.03,30.00,30.00,30.00,8.08,22.75,16.55},
			{30.00,18.15,9.02,3.81,3.72,30.00,30.00,30.00,8.09,22.09,16.37},
			{30.00,17.67,8.89,4.51,4.47,30.00,30.00,30.00,8.12,21.44,15.90},
			{30.00,17.30,8.71,4.84,4.51,30.00,30.00,30.00,8.17,21.21,15.36},
			{30.00,17.00,8.51,4.92,4.20,30.00,30.00,30.00,8.25,21.17,14.81},
			{30.00,16.76,8.35,4.85,4.60,30.00,30.00,30.00,8.38,21.21,14.29},
			{30.00,16.64,8.34,4.65,4.90,30.00,30.00,30.00,8.47,21.18,14.06},
			{30.00,16.54,8.41,4.65,4.69,30.00,30.00,30.00,8.53,21.03,13.88},
			{29.64,16.41,8.53,4.97,4.79,30.00,30.00,30.00,8.57,20.66,13.68},
			{29.25,16.33,8.60,4.86,4.77,30.00,30.00,30.00,8.56,20.29,13.55},
			{28.88,16.27,8.66,4.73,4.91,30.00,30.00,30.00,8.54,19.90,13.46},
			{28.36,16.18,8.69,4.67,4.78,30.00,30.00,30.00,8.48,19.47,13.39},
			{27.93,16.10,8.63,4.87,4.48,30.00,30.00,30.00,8.27,19.27,13.36},
			{27.39,15.99,8.18,4.80,4.59,30.00,30.00,30.00,6.87,19.16,13.35}};

}


// The Beginning
// The Step is 1 seconds.
// The structure of any matrix is follow: the clowns are the section at the graph (1-4;3-4;4-5;5-7;7-8;5-6;2-6;6-8;8-9;9-10;9-11), summary 11 sections
// Input data:
// dMatrixPreEvac[1][11] is the matrix which calculated as a ratio people square (0.125 m2) to section's square.
// dFinalMatrixOFP[300][11] got from FDS and show the values of fire hazards at each section at each seconds. Line is times moment.
// dFinalLength[1][11] is the matrix which calculated as a ratio current section to the maximal section in the building. This matrix is constant and do not changed.
// curEvacTime is a current evacuation time.






// Inter media start. Input data for this cycle: 'curEvacTime'.
//Processing the EvacMatrix. During a simulation a processes of an evacuation we re-pit this cycle with the Step.
int SafestPathRouter::main_4()
{

	// peopleAtSection[1][11] is a matrix where 1 is at first seconds. We get it by measuring the count of people at the sections.

	double peopleAtSection[1][11]={300, 211, 1212, 324, 456, 567, 677, 343, 233, 345, 345};
	double dMatrixPreEvac[1][11]={0.000573,0.000328,0.000589,0.000651,0.000486,0.003574,0.003575,0.001171,0.000976,0.000221,0.000385};
	double dFinalLineEvac[1][11]={0,0,0,0,0,0,0,0,0,0,0};
	int i=0;


	for(int j = 0; j < 11; j ++) //Вывод элементов заданной строки
	{
		dFinalLineEvac[i][j]= peopleAtSection[i][j] * dMatrixPreEvac[i][j];
	}


	return 0;
}
// Inter media finish. Output data from this cycle: dFinalLineEvac[curEvacTime][11]={};
//Processing the EvacMatrix.


// Inter media start. Input data for this cycle: 'curEvacTime'. During a simulation a processes of an evacuation we re-pit this cycle with the Step.
//Processing the OFP's matrix. Here we get necessary line from dFinalMatrixOFP based on 'curEvacTime'
int SafestPathRouter::main_3()
{

	for(int cnt = 0; cnt < 11; cnt ++) //Getting necessary line from dFinalMatrixOFP
		//cout << dFinalLineOFP[curEvacTime][cnt] << "\t";

		return 0;
}
// Inter media finish. Output data from this cycle: dFinalLineOFP [curEvacTime][11]={};
//Processing the OFP's matrix.


// Inter media start. Input data for this cycle: 'dFinalLineEvac', 'dFinalLineOFP', 'dFinalLength'.
// Here we calculate the the 'Fi' optimization index for Floyd-Warchal's algorithm.
int SafestPathRouter::main_2 ()
{

	double dFinalLineEvac[1][11]={1, 4, 5, 8, 3, 5, 7, 9, 1, 3, 5};
	double dFinalLineOFP[1][11]={4, 5, 7, 9, 2, 0, 3, 5, 6, 4, 1};
	double dFinalLength[1][11]={5, 6, 8, 2, 1, 5, 6, 7, 8, 9, 9};
	double rR[1][11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double iNt1[1][11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double iNt2[1][11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double iNt3[1][11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double iNt4[1][11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int i=0;
	int K=0;

	for (int j=0; j<11; j++)
	{
		iNt1[i][j]= dFinalLineEvac[i][j] * dFinalLineEvac[i][j];
		iNt2[i][j]= dFinalLineOFP[i][j] * dFinalLineOFP[i][j];
		iNt3[i][j]= dFinalLength[i][j] * dFinalLength[i][j];
	}

	for (int j=0; j<11; j++)
	{
		iNt4[i][j]=iNt1[i][j] + iNt2[i][j] + iNt3[i][j];
	}

	for (int j=0; j<11; j++)
	{
		rR[i][j]=sqrt(iNt4[i][j]);
	}

	// Output Matrix to a screen

	for(int i = 0; i < 11; i ++) //Вывод элементов заданной строки
		cout << rR[K][i] << "\t";

	return 0;
}

// Inter media finish. Output data from this cycle: rR[curEvacTime][11] is a matrix which content the 'Fi' optimization index.



// Inter media start. Input data for this cycle: 'rR', 'curPosition'. The 'curPosition' is a variable content the position of people.
// Here we calculate the Safest route matrix by Floyd-Warchal's algorithm.

int SafestPathRouter::main_1(){

	int curPosition;
	cout << "Input Current Position: ";
	cin >> curPosition;


	// Initialize
	int vertices = 11;
	vector<vector<int> > a(vertices, vector<int>(vertices,999));
	int rR[1][11]={37,33,31,24,34,19,19,58,16,44,43};
	// initialize diagonal
	for(int i=0; i < vertices; i++)
		a[i][i]=0;

	// initialize distances
	a[0][3]=rR[0][0];
	a[2][3]=rR[0][1];
	a[3][4]=rR[0][2];
	a[4][6]=rR[0][3];
	a[6][7]=rR[0][4];
	a[4][5]=rR[0][5];
	a[1][5]=rR[0][6];
	a[5][7]=rR[0][7];
	a[7][8]=rR[0][8];
	a[8][9]=rR[0][9];
	a[8][10]=rR[0][10];
	//
	a[3][0]=rR[0][0];
	a[3][2]=rR[0][1];
	a[4][3]=rR[0][2];
	a[6][4]=rR[0][3];
	a[7][6]=rR[0][4];
	a[5][4]=rR[0][5];
	a[5][1]=rR[0][6];
	a[7][5]=rR[0][7];
	a[8][7]=rR[0][8];
	a[9][8]=rR[0][9];
	a[10][8]=rR[0][10];

	// Floyd-Warshal
	// Add nodes between (first 1 then 2, 3 till n) and look if
	// distance is shorter
	for(int k = 0; k < vertices; k++)
		for(int i = 0; i < vertices; i++)
			for(int j = 0; j < vertices; j++)
				if(a[i][j]>a[i][k]+a[k][j])
					a[i][j]=a[i][k]+a[k][j];

	// Print out final distance matrix
	//for(int i = 0; i < vertices; i++){
	//for(int j = 0; j < vertices; j++)
	//cout << a[i][j] << " ";
	//cout << endl;
	//}

	int g1=0;
	int g2=0;

	g1=a[0][curPosition];
	g2=a[1][curPosition];


	if (g1>g2)
	{
		//goal 1
		//cout << "The safest rout is by rout to Exit 2 \n";
		//cout << "Distance from current position to the Exit 2: ";
		//cout <<g2;
	}
	else
	{
		//goal 0
		//cout << "The safest rout is by rout to Exit 1 \n";
		//cout << "Distance from current position to the Exit 1: ";
		//cout <<g1;
	}
	return 0;
}

// Inter media finish. Output data from this cycle: goal 1 or goal 2 for pedestrians.
