//============================================================================
// Author      : Sora Sugiyama
//============================================================================

#include <bits/stdc++.h>
#include "GeneticAlgorithm.h"
#include "matrix.h"
#include "actFunc.h"
using namespace std;

double q[5]={0.5,1.25,2.5,5.0};
int main(){
	mat data={{0,0,1},{0,1,1},{1,0,1},{1,1,1}},b={{0},{1},{1},{0}};

	GA Ws;
	Ws.makeObject(100,60);

	int maxGen=50;
	for(int gen=0;gen<=maxGen;gen++){
		vector<pair<double,int> >vp;

		for(int i=0;i<100;i++){
			mat w1={{0,0,0},{0,0,0},{0,0,0}},w2={{0},{0},{0}};

			int ii=0,jj=0;
			for(int j=0;j<45;j++){
				if(j%5<4)w1[ii][jj]+=(Ws.Obj[i][j]?q[j%5]:0);
				if(j%5==4&&Ws.Obj[i][j])w1[ii][jj]*=-1;
				if(j%5==4)jj++;
				if(jj>2){
					ii++;
					jj=0;
				}
			}
			int kk=0;
			for(int j=45;j<60;j++){
				if(j%5<4)w2[kk][0]+=(Ws.Obj[i][j]?q[j%5]:0);
				if(j%5==4&&Ws.Obj[i][j])w2[kk][0]*=-1;
				if(j%5==4)kk++;
			}

			mat tmp=Product(data,w1);
			for(auto &u:tmp){
				for(auto &v:u)v=Sigmoid(v);
			}
			tmp=Product(tmp,w2);
			for(auto &u:tmp){
				for(auto &v:u)v=Sigmoid(v);
			}

			mat r=Subtract(b,tmp);
			r=Product(Trans(r),r);
			double loss=r[0][0];
			vp.push_back({loss,i});
		}

		sort(vp.begin(),vp.end());

		if(gen%10==0){
			cout<<"Generation : "<<gen<<"\n";
			cout<<"Loss of best 4 genes___\n";
			for(int i=0;i<4;i++)cout<<vp[i].first<<"\n";
			cout<<endl;
		}

		vector<int>suitGenes;
		for(int i=0;i<6;i++)suitGenes.push_back(vp[i].second);

		Ws.nextGeneration(suitGenes,15);
	}

	return 0;
}
