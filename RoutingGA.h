/*
 * RoutingGA.h
 *
 *  Created on: 2023. 10. 23.
 *      Author: Sora Sugiyama
 */

#ifndef ROUTINGGA_H_
#define ROUTINGGA_H_

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
using namespace std;

struct RoutGA{
	int geneLen=0,NumOfObjs=0;
	unsigned int seed=2914;
	vector<vector<int> >Obj;
	void CLEAR(){
		geneLen=NumOfObjs=0;
		Obj.clear();
		seed=2914;
	}
	void SetCode(int gL,int nob,int sd){
		geneLen=gL;
		NumOfObjs=nob;
		seed=sd;
	}
	void Generate(){
		srand(seed);
		for(int i=0;i<NumOfObjs;i++){
			Obj.push_back(vector<int>());
			for(int j=0;j<geneLen;j++){
				Obj.back().push_back(j);
			}
			random_shuffle(Obj.back().begin(),Obj.back().end());
		}
	}
	void nextGeneration(vector<int>sups){
		if((int)sups.size()<=1){
			cout<<"The number of superior objects should bigger than 1.";
			return;
		}

		vector<vector<int> >supObj;
		for(int x:sups){
			supObj.push_back(Obj[x]);
		}
		Obj.clear();

		int n=sups.size();
		for(int i=0;i<n/2;i++){
			Obj.push_back(supObj[i]);
		}

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> disb(0,n-1),disb2(0,geneLen-1);
		vector<int>seq;
		while((int)Obj.size()<NumOfObjs){
			int u=disb(gen),v=disb(gen);
			int k=disb2(gen);
			vector<int>code;
			vector<bool>used(geneLen+2,false);
			for(int i=0;i<k;i++){
				code.push_back(supObj[u][i]);
				used[supObj[u][i]]=true;
			}
			for(int x:supObj[v]){
				if(used[x])continue;
				code.push_back(x);
			}

			Obj.push_back(code);
		}
	}
};


#endif /* ROUTINGGA_H_ */
