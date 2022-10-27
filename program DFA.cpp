#include<iostream>
using namespace std;

bool cek(string a, int b, int c, int d){
	if(b<c-1){
		b++;
		if(d==0){
			if(a[b]=='1'){
				d=1;
				return cek(a,b,c,d);
			}else{
				d=3;
				return cek(a,b,c,d);
			}
		}
		if(d=3){
			if(a[b]=='1'){
				d=1;
				return cek(a,b,c,d);
			}else{
				d=3;
				return cek(a,b,c,d);
			}
		}else if(d=2){
			if(a[b]=='1'){
				d=2;
				return cek(a,b,c,d);
			}else{
				d=1;
				return cek(a,b,c,d);
			}
		}else if(d=1){
			if(a[b]=='1'){
				d=3;
				return cek(a,b,c,d);
			}else{
				d=2;
				return cek(a,b,c,d);
			}
		}
	}else{
		if(d==3 || d==0){
			return 1;
		}else{
			return 0;
		}
	}
}

//Yuwanda indra Gunawan 14116001
//TBFO RD
//Tugas Kecil 1

int main(){
	string biner;
	int q=0;
	bool cek2;
	cin>>biner;
	int a=-1, b=biner.length();
	cek2=cek(biner, a, b, q);
	if(cek2==1){
		cout<<"Habis bagi 3";
	}else{
		cout<<"Tidak habis bagi 3";
	}
}
