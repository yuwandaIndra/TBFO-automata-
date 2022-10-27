#include <iostream>
#include <conio.h>
#include <string.h>
#include <cstdlib>


using namespace std;


typedef char infotype;
typedef int temptype;
typedef struct TElmtList *address;
typedef struct TElmtList{
 bool bolean;
 infotype info;
 temptype temp;
 address next;
 address prev;
} ElmtList;

typedef struct {
 address first;
 address last;
}List ;

 //SELEKTOR 
#define Temp(P) (P)->temp
#define Bool(P) (P)->bolean
#define Info(P) (P)->info
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) ((L).first)
#define Last(L) ((L).last)

//KONSTANTA
#define Nil NULL
#define Infinity 99999


/****************** TEST LIST KOSONG ******************/
bool IsEmpty(List L) {
/* Mengirim true jika list kosong. Lihat definisi di atas. */
 return (First(L) == NULL && Last(L) == NULL);
}


/****************** PEMBUATAN LIST KOSONG ******************/
void createList(List *L) {
 First(*L) = NULL;
 Last(*L) = NULL;
}

/****************** Manajemen Memori ******************/
address Allocation(infotype x,bool b,temptype t) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
 address NewElmt;
 NewElmt = (ElmtList*) malloc (sizeof(ElmtList));
 Info(NewElmt) = x;
 Bool(NewElmt) = b;
 Temp(NewElmt) = t;
 Next(NewElmt) = Nil;
 Prev(NewElmt) = Nil;
 return NewElmt;
}

void Deallocation(address hapus) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
 free(hapus);
}


/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L){
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
	address P = First(L);
	bool flag=false;
	int sum=0;
	
	while (P != Nil){
		if (Info(P) == '*' && Bool(P)==false||Info(P) == '/' && Bool(P)==false){	
			
			Bool(P)=true;
			flag=true;
			return P;
		}
		
		P = Next(P);
	}
//	if(flag!=true){
	P=First(L);
		while (P != Nil){
		if (Info(P) == '+' && Bool(P)==false||Info(P) == '-' && Bool(P)==false){	
			
			Bool(P)=true;
			flag=true;
			return P;
		}
		
		P = Next(P);
	}
//	}
	return Nil;
}


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsertFirst(List *L, infotype x,bool b,temptype t) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
 address NewElmt;
 NewElmt = Allocation(x,b,t);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 First(*L) = NewElmt;
 Last(*L) = NewElmt;
 } else{
 Next(NewElmt) = First(*L);
 Prev(First(*L)) = NewElmt;
 First(*L) = NewElmt;
 }
 }
}

void InsertLast(List *L, infotype x,bool b,temptype t) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
 address NewElmt;
 NewElmt = Allocation(x,b,t);
 if (NewElmt != NULL) {
 if(IsEmpty(*L)){
 InsertFirst(L,x,b,t);
 } else{
 Next(Last(*L)) = NewElmt;
 Prev(NewElmt) = Last(*L);
 Last(*L) = NewElmt;
 }
 }
}


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
	if(IsEmpty(*L)){
 First(*L) = P;
 Last(*L) = P;
 } else{
 Next(P) = First(*L);
 Prev(First(*L)) = P;
 First(*L) = P;
 }
}

void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	if(IsEmpty(*L)){
 InsertFirst(L,P);
 } else{
 Next(Last(*L)) = P;
 Prev(P) = Last(*L);
 Last(*L) = P;
 }
}

void InsertAfter (List *L, address P, address Prec){
/* I.S. Prec pastilah elemen list; P sudah dialokasi */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	if(Next(Prec) == Nil){
	InsertLast(L,P);
	}else{
	Next(P) = Next(Prec);
	Prev(P) = Prec;
	Prev(Next(Prec))= P;
	Next(Prec) = P;
	}
}

void InsertBefore (List *L, address P, address Succ){
/* I.S. Succ pastilah elemen list; P sudah dialokasi */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */
	if(Succ == First(*L)){
	InsertFirst(L,P);
	}else{
	Next(Prev(Succ)) = P;
	Prev(P) = Prev(Succ);
	Next(P) = Succ;
	Prev(Succ) = P;
	}
}


/*** PENGHAPUSAN SEBUAH ELEMEN ***/

void DelFirst (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	*P = First(*L);
	First(*L) = Next(*P);
	Prev(First(*L)) = Nil;
	Deallocation(*P);
}

void DelLast (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */
	*P = Last(*L);
	Last(*L) = Prev(*P);
	Next(Last(*L)) = Nil;
	Prev(*P) = Nil;
	Deallocation(*P);
}



void DelAfter (List *L, address *Pdel, address Prec){
/* I.S. List tidak kosong. Prec adalah anggota list. */
/* F.S. Menghapus Next(Prec): */
/* Pdel adalah alamat elemen list yang dihapus */
	*Pdel = Next(Prec);
	Next(Prec) = Next(*Pdel);
	Prev(Next(*Pdel)) = Prec;
	Prev(*Pdel) = Nil;
	Next(*Pdel)= Nil;
	Deallocation(*Pdel);
}

void DelBefore (List *L, address *Pdel, address Succ){
/* I.S. List tidak kosong. Succ adalah anggota list. */
/* F.S. Menghapus Prev(Succ): */
/* Pdel adalah alamat elemen list yang dihapus */
	*Pdel = Prev(Succ);
	Next(Prev(*Pdel)) = Succ;
	Prev(Succ) = Prev(*Pdel);
	Prev(*Pdel) = Nil;
	Next(*Pdel) = Nil;
	Deallocation(*Pdel);
}

void DelP (List *L, infotype X,bool b){
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X */
/* maka P dihapus dari list dan didealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
	address P = Search(*L);
	address prec = Prev(P);
	if (P != Nil){
		if(P == First(*L)){
			DelFirst(L,&P);
		}else if(P == Last(*L)){
			DelLast(L,&P);
		}else{
			DelAfter(L,&P,prec);
		}
	}
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintForward (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen pertama */
/* ke elemen terakhir secara horizontal ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	cout<<"[";
	if(!IsEmpty(L)){
	address temp =First(L);
	while(Next(temp)!=NULL){
	cout<<Info(temp) <<" bool:"<<Bool(temp)<<" temp:"<<Temp(temp)<<" , ";
	temp = Next(temp);
	}
	cout<<Info(temp)<<" bool:"<<Bool(temp)<<" temp:"<<Temp(temp);
	}
	cout<<"]"<<endl;
}

void PrintBackward (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen terakhir */
/* ke elemen pertama secara horizontal ke kanan: [en,en-1,...,e2,e1] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [30,20,1] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	cout<<"[";
	if(!IsEmpty(L)){
	address temp =Last(L);
	while(Prev(temp)!=NULL){
	cout<<Info(temp) <<", ";
	temp = Prev(temp);
	}
	cout<<Info(temp);
	}
	cout<<"]"<<endl;
}

void PrintSearch (List L,address *P){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen terakhir */
/* ke elemen pertama secara horizon tal ke kanan: [en,en-1,...,e2,e1] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [30,20,1] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	if(P!=Nil){
		cout<<Info(*P)<<" Bool:"<<Bool(*P)<<"  ";
	}
	else{
		cout<<"tidak ditemukan";
	}
}

address proseskiri(List L,address *P){
	address prev;
	if(P!=Nil && Bool(Prev(*P))!=true){
		Bool(Prev(*P))=true;
//		Info(Prev(*P))='C';
//		Bool(Next(*P))=true;
		prev=Prev(*P);
//		cout<<Info(Prev(*P))<<Info(*P)<<Info(Next(*P));
	}
	else{
		prev=Prev(Prev(*P));
	}
		return prev;
}
address proseskanan(List L,address *P){
	address next;
	if(P!=Nil && Bool(Next(*P))!=true){
		Bool(Next(*P))=true;
//		Info(Next(*P))='C';
//		Bool(Next(*P))=true;
		next=Next(*P);
//		cout<<Info(Prev(*P))<<Info(*P)<<Info(Next(*P));
	}
	else{
		next=Next(Next(*P));
	}
		return next;
}
void proses(List L, address Prev,address Next,address P){
	if(Info(P)=='*'){
		if((Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/') && (Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/')){
			int x=Temp(Prev);
//			cout<<"x:"<<x;
			int y=Temp(Next);
//			cout<<"y:"<<y;
			Temp(P)=x*y;
		}
		else if(Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/'){
			int x=Temp(Prev);
			int y=Info(Next)-'0';
			Temp(P)=x*y;
		}
		else if(Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/'){
			int y=Temp(Next);
			int x=Info(Prev)-'0';
			Temp(P)=x*y;
		}
		else{
			int x=Info(Prev)-'0';
			int y=Info(Next)-'0';
			Temp(P)=x*y;
		
		}
	}
	if(Info(P)=='/'){
		if((Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/') && (Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/')){
			int x=Temp(Prev);
//			cout<<"x:"<<x;
			int y=Temp(Next);
//			cout<<"y:"<<y;
			Temp(P)=x/y;
		}
		else if(Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/'){
			int x=Temp(Prev);
			int y=Info(Next)-'0';
			Temp(P)=x/y;
		}
		else if(Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/'){
			int y=Temp(Next);
			int x=Info(Prev)-'0';
			Temp(P)=x/y;
		}
		else{
			int x=Info(Prev)-'0';
			int y=Info(Next)-'0';
			Temp(P)=x/y;
		
		}
	}
	if(Info(P)=='+'){
		if((Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/') && (Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/')){
			int x=Temp(Prev);
//			cout<<"x:"<<x;
			int y=Temp(Next);
//			cout<<"y:"<<y;
			Temp(P)=x+y;
		}
		else if(Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/'){
			int x=Temp(Prev);
			int y=Info(Next)-'0';
			Temp(P)=x+y;
		}
		else if(Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/'){
			int y=Temp(Next);
			int x=Info(Prev)-'0';
			Temp(P)=x+y;
		}
		else{
			int x=Info(Prev)-'0';
			int y=Info(Next)-'0';
			Temp(P)=x+y;
		
		}
	}
	if(Info(P)=='-'){
		if((Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/') && (Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/')){
			int x=Temp(Prev);
//			cout<<"x:"<<x;
			int y=Temp(Next);
//			cout<<"y:"<<y;
			Temp(P)=x-y;
		}
		else if(Info(Prev)=='*'||Info(Prev)=='+'||Info(Prev)=='-'||Info(Prev)=='/'){
			int x=Temp(Prev);
			int y=Info(Next)-'0';
			Temp(P)=x-y;
		}
		else if(Info(Next)=='*'||Info(Next)=='+'||Info(Next)=='-'||Info(Next)=='/'){
			int y=Temp(Next);
			int x=Info(Prev)-'0';
			Temp(P)=x-y;
		}
		else{
			int x=Info(Prev)-'0';
			int y=Info(Next)-'0';
			Temp(P)=x-y;
		
		}
	}
}


int main (){
	
	
	bool z=true;
	do{
		
	//2	
	List L;
	address P;
	createList(&L);
	int x, y, hasil,t=Nil;
	bool b=false;
	//1
	int k;
	int matrix[10][176];
	int currentState = 0;
	int lastState=0;	
	char s[256];
	
	
	
	
	
	cout<<"> ";
	
//	error
	for(int i=0; i<9; i++){
            for(int j=0; j<176; j++){
                matrix[i][j] = 0;
            }
        }

//	matrix[state][string]=next state;	
//	C
	matrix[0][99]=1;
//	E
	matrix[1][101]=2;
//	T
	matrix[2][116]=3;
//	A
	matrix[3][97]=4;
//	K
	matrix[4][107]=5;
//	c
	matrix[0][67]=1;
//	e
	matrix[1][69]=2;
//	t
	matrix[2][84]=3;
//	a
	matrix[3][65]=4;
//	k
	matrix[4][75]=5;
//	spasi
	matrix[5][32]=6;
//	kutip
	matrix[6][34]=7;
	
	for(int i=48;i<57;i++){
	matrix[6][i]=10;
	}
//	*
	matrix[6][42]=10;
//	+
	matrix[6][43]=10;
//	-
	matrix[6][45]=10;
//	/
	matrix[6][47]=10;
	
	matrix[10][59]=11;	
	
	
	
	
//	ascii total
	for(int j=32; j<126; j++){
			if(j==34){
				matrix[7][j]=8;
        	}
        	else{
        		matrix[7][j] = 7;
			}
		}
		
//	kutip
//	;
	matrix[8][59]=9;
	
//	input
 	cin.getline(s,256);

 	
	currentState=matrix[currentState][int(s[0])];
 	currentState=matrix[currentState][int(s[1])];
 	currentState=matrix[currentState][int(s[2])];
 	currentState=matrix[currentState][int(s[3])];
 	currentState=matrix[currentState][int(s[4])];
 	currentState=matrix[currentState][int(s[5])];
// 	cout<<currentState;
//cout<<endl<<s[5];
 	currentState=matrix[currentState][int(s[6])];
 	
// 	cout<<currentState;
	if(currentState==7){
	currentState=matrix[currentState][int(s[strlen(s)-2])];
	}

// 	cout<<currentState;
	currentState=matrix[currentState][int(s[strlen(s)-1])];
	
// 	cout<<currentState;

 		if(currentState==0){
 				cout<<"Kode tidak sesuai aturan"<<endl;
		 }
 		
 		if(currentState!=9&&currentState!=0&&currentState!=11){
 				cout<<"Kode tidak sesuai aturan"<<endl;
		 }
//		 cout<<currentState;
 	if(currentState==11){
// 		for(int i=7;i<strlen(s)-2;i++){
// 		cout<<"berhasil"<<endl;	
 		int i=1;
 		
 		while (s[strlen(s)-i]!=' '){
 			InsertFirst(&L,s[strlen(s)-i],b,t);
 			i++;
 			
 		} 
 		
// 		cout<<"i :"<<i;
		for(int j=0;j<((i/2)-1);j++){
			P=Search(L);
//	PrintSearch(L,&P);
//	cout<<endl;
//	PrintForward(L);
	
			address Prev=proseskiri(L,&P);
//	PrintSearch(L,&Prev);
	
//	cout<<endl;
//	PrintForward(L);
	
			address Next=proseskanan(L,&P);
//	PrintSearch(L,&Next);
	
//	cout<<endl;
//	PrintForward(L);
	
			proses(L,Prev,Next,P);
	
//	cout<<endl;
//	PrintForward(L);
//	P=Nil;
//	cout<<i;
		}

		hasil=Temp(P);
		cout<<"hasil: "<<hasil;
 	
// 		}
 		cout<<endl;
 		
	 }
 	
 	if(currentState==9){
 		for(int i=7;i<strlen(s)-2;i++){
 		cout<<s[i];	
 		}
 		cout<<endl;
 		
	 }
	}
	while(z==true);
}
