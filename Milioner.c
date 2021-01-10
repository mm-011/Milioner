//Milioner

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

void razmakX1(){ //pravi \n jedanput
	printf("\n");
} 

void razmakX2(){ //pravi \n dvaput
	printf("\n");
	printf("\n");
}

void razmakX3(){ //pravi \n triput
	printf("\n");
	printf("\n");
	printf("\n");
}

void rbr_pitanja_glasi(int rbr){
	printf("%d. pitanje glasi: ",rbr);
}

int nasum_broj(){//kreiranje nasumicnog broja
	int nasumicni_broj;

	nasumicni_broj=rand() % 3;

	return nasumicni_broj;
}

char* kreira_rbr(int br,int nasumicni_broj){ //kreira string sa rednim brojem pitanja
	char rbrPitanja_kreirano[5],p[81];
	//int nasumicni_broj;

	//nasumicni_broj=nasum_broj();
	itoa(br,rbrPitanja_kreirano,10);			
	strcat(rbrPitanja_kreirano,".");			
	itoa(nasumicni_broj,p,10);	
	strcat(rbrPitanja_kreirano,p);
	return rbrPitanja_kreirano;
}

struct str_odgovor{ 
	char tekst[81];
	int tnt;
};

struct str_pitanje{
	char tekst[81];
	struct str_odgovor odgovor[4];
};

struct str_pomoc{
	
	int iskoriscena_pola_pola,iskoriscena_zamena,izbor_pomoci;

};

int zelis_ili_ne(int br){ 

	char *da_ne;
	int i;
	char poruka[][81]={"Zelite li da postanete milioner ? ( DA / NE )",
						"Zelite li da zapamtite svoj rezultat ? ( DA / NE )",
						"Zelite li da pocnete novu igru ? ( DA / NE )"
	};

	//dodela mem. i provera
	da_ne=(char*)malloc(2*sizeof(da_ne));
	if(da_ne==NULL){
		printf("Neuspela dodela memorije");
		exit(1);
	}

	//pita korisnika da li zeli da udje u igru
	razmakX3();
	puts(poruka[br]);
	razmakX1();
	fgets(da_ne,3,stdin);
	fflush(stdin);
	razmakX1();
	//pretvara u mala slova
	for(i=0;i<strlen(da_ne);i++){
		*(da_ne+i)=tolower(*(&da_ne[i]));
	}

	//pita sve dok ne unese u pravilnom formatu 
	while(strcmp(da_ne,"da")!=0 && strcmp(da_ne,"ne")!=0){
			printf("!!! NISTE UNELI DA ILI NE !!!");
			razmakX1();

			//printf("Zelite li da postanete milioner ? ( Odgovorite sa DA ili NE )");
			puts(poruka[br]);
			razmakX1();
			fgets(da_ne,3,stdin);
			fflush(stdin);
			razmakX1();	
			//pretvara slova u mala slova
			for(i=0;i<strlen(da_ne);i++){
				*(da_ne+i)=tolower(*(&da_ne[i]));
			}			
	}

	if(strcmp(da_ne,"da")==0){
		free(da_ne);
		return 1;
	}

	else if(strcmp(da_ne,"ne")==0){
		free(da_ne);
		return 0;
	}
		
}

void ispis_tabele(){//ispisuje tabelu sa rezultatima
	FILE *fajl_rezultati;
	char brpoena[3],ime[81];
	int i,duz;
	//otvara datoteku i proverava ispravnost
	fajl_rezultati=fopen("rezultati.txt","r");
	if(fajl_rezultati == NULL){
		fprintf(stderr,"Greska pri otvaranju datoteke");
		exit(1);
	}
	printf("********************************\n");
	printf("* BROJ POENA *       IME       *");
	razmakX1();
	printf("*==============================*");
	razmakX1();
	//ispisjue br poena i ime
	while(fscanf(fajl_rezultati,"%s ",brpoena)!=EOF ){
		fgets(ime,80,fajl_rezultati);
		ime[strlen(ime)-1]='\0';
		duz=strlen(ime);
		for(i=0;i<=15-duz;i++){
			strcat(ime," ");}
		printf("*     %s      * %s*",brpoena,ime);
		razmakX1();
	}
	printf("********************************");
	fclose(fajl_rezultati);

}

int glavni_meni(){//glavni meni igre
	int indik;	
	razmakX1();
	printf("====================MILIONER====================");	
	razmakX2();
	printf("    1                  2                   3    ");
	razmakX1();
	printf("NOVA IGRA          REZULTATI             IZLAZ  ");	
	razmakX3();
	printf("UNESITE OPCIJU :");
	scanf("%d",&indik);
	fflush(stdin);
	//dok korisnik ne unese ispravnu opcuju while se ponavlja
	while(indik!=1 && indik!=2 && indik!=3){
		razmakX1();
		printf("!!! UNESITE NEKU OD PONUDJENIH OPCIJA !!!");
		razmakX1();
		scanf("%d",&indik);
		fflush(stdin);
	}
	return indik;
}

void igra(){
	FILE *fajl_pitanja,*fajl_rezultati;
	int rbr_pitanja=1,i,tren_rez;//brojaci
	int tnt=1,dane_0,odgovor,r_da_ne,zamena=0,pola_pola,nasum_br,zam_br,tacno_pitanje;//indikatori
	struct str_pitanje pitanje;
	struct str_pomoc pomoc;
	char rbrPitanja_dokument[81],rbrPitanja_kreirano[5],*ime;
	srand(time(NULL));
	pomoc.iskoriscena_pola_pola=0;
	pomoc.iskoriscena_zamena=0;

	fajl_pitanja=fopen("pitanja.txt","r");
	if(fajl_pitanja == NULL){
		fprintf(stderr, "Greska pri otvaranju datoteke");
		exit(1);
	}
	//dodela memorije
	ime=(char*)malloc(81*sizeof(ime));
	if(ime==NULL){
		printf("Neuspela dodela memorije");
		exit(1);
	}

	dane_0=zelis_ili_ne(0);

	while(tnt==1 && rbr_pitanja<=7 && dane_0==1){
		if(zamena==1){
			while(nasum_br==zam_br)
				nasum_br=nasum_broj();
			zamena=0;
		}
		else{
			nasum_br=nasum_broj();
		}
		//trazi se redni broj pitanja u dokumentu
		strcpy(rbrPitanja_kreirano,kreira_rbr(rbr_pitanja,nasum_br));
		fscanf(fajl_pitanja,"%s",rbrPitanja_dokument);
		while(strcmp(rbrPitanja_kreirano,rbrPitanja_dokument)!=0){
			fscanf(fajl_pitanja,"%s",rbrPitanja_dokument);
		}
		//uzima se tekst pitanja
		fgets(pitanje.tekst,81,fajl_pitanja);
		strcpy(pitanje.tekst,&pitanje.tekst[1]);
		//uzimaju se odgovori
		for(i=0;i<4;i++){
			fscanf(fajl_pitanja,"%d",&pitanje.odgovor[i].tnt);
			fgets(pitanje.odgovor[i].tekst,80,fajl_pitanja);
		}
		//ispis pitanja i ponudjenih odgovora
		razmakX1();
		printf("********************************");
		razmakX1();
		printf("* ODGOVORE DAJETE SA 1|2|3|4|5 *");
		razmakX1();
		printf("********************************");
		razmakX3();
		rbr_pitanja_glasi(rbr_pitanja);
		razmakX2();
		puts(pitanje.tekst);
		for(i=0;i<4;i++){
			printf("%d)",i+1);
			puts(pitanje.odgovor[i].tekst);
		}
		printf("5)");
		puts("  POMOC");
		razmakX1();
		odgovor=0;
		printf("ODGOVOR: ");//prihvata odgovor
		scanf("%d",&odgovor);

		if(odgovor==5){
			if(pomoc.iskoriscena_pola_pola==1 && pomoc.iskoriscena_zamena==1){
				razmakX1();
				printf("************************************");
				razmakX1();
				puts("*!!! ISKORISTILI STE OBE POMOCI !!!*");
				printf("************************************");
				razmakX1();
			}
			else{
				while(1){
					razmakX1();
					puts("IZABERITE JEDNU OD PREOSTALIH POMOCI:");
					razmakX1();
					puts("1) 50-50");
					puts("2) ZAMENA PITANJA");
					scanf("%d",&pomoc.izbor_pomoci);
					if(pomoc.izbor_pomoci==1){
						if(pomoc.iskoriscena_pola_pola==0){
							razmakX2();
							puts(pitanje.tekst);
							for(i=0;i<4;i++){
								if(pitanje.odgovor[i].tnt==1)
									tacno_pitanje=i;
							}
							printf("%d)",tacno_pitanje+1);
							puts(pitanje.odgovor[tacno_pitanje].tekst);
							nasum_br=rand() % 4;
							while(nasum_br==tacno_pitanje)
								nasum_br=rand() % 4;
							printf("%d)",nasum_br+1);
							puts(pitanje.odgovor[nasum_br].tekst);
							printf("5)");
							puts("  POMOC");
							razmakX1();
							odgovor=0;
							printf("ODGOVOR: ");
							scanf("%d",&odgovor);
							while(odgovor!=nasum_br+1 && odgovor!=tacno_pitanje+1 && odgovor!=5){
								razmakX1();
								printf("!!! UNESITE NEKU OD PONUDJENIH OPCIJA !!!");
								razmakX1();
								fflush(stdin);
								scanf("%d",&odgovor);			
							}
							pomoc.iskoriscena_pola_pola=1;
							if(odgovor==5)
								continue;
							break;
							
						}
						else{
							razmakX1();
							puts("*********************************");
							puts("* VEC STE ISKORISTILI OVU POMOC *");
							puts("*********************************");
							continue;
						}
					}	
					if(pomoc.izbor_pomoci==2){
						if(pomoc.iskoriscena_zamena==0){
							zamena=1;
							pomoc.iskoriscena_zamena=1;
							zam_br=nasum_br;
							break;
						}
						else{
							razmakX1();
							puts("*********************************");
							puts("* VEC STE ISKORISTILI OVU POMOC *");
							puts("*********************************");
							continue;
						}
					}
					else{
						razmakX1();
						puts("!!! IZABERITE OPCIJU 1 | 2 !!!");
					}					
				}
			}				
		}

		if(zamena==1){
			rewind(fajl_pitanja);
			continue;
		}

		while(odgovor!=1 && odgovor!=2 && odgovor!=3 && odgovor!=4 ){
			razmakX1();
			printf("!!! UNESITE NEKU OD PONUDJENIH OPCIJA !!!");
			razmakX1();
			fflush(stdin);
			razmakX1();
			printf("ODGOVOR: ");
			scanf("%d",&odgovor);			
		}
		if(pitanje.odgovor[odgovor-1].tnt==1){
			razmakX1();
			printf("************************");
			razmakX1();
			puts("* Vas odgovor je tacan *");
			printf("************************");
			razmakX1();
			tnt=1;
			rbr_pitanja++;
			tren_rez=rbr_pitanja-1;
		}
		else{
			razmakX1();
			printf("**************************");
			razmakX1();
			puts("* Vas odgovor nije tacan *");
			printf("**************************");
			tnt=0;
			rbr_pitanja--;
			tren_rez=rbr_pitanja;
		}
	}
	fclose(fajl_pitanja);
	fflush(stdin);

	if(dane_0==1){
		r_da_ne=zelis_ili_ne(1);
		if(r_da_ne==1){
			fajl_rezultati=fopen("rezultati.txt","a");
			if(fajl_rezultati == NULL){
				fprintf(stderr,"Greska pri otvaranju datoteke");
				exit(1);
			}
			puts("Unesite svoje ime");
			fgets(ime,17,stdin);
			ime[strlen(ime)-1]='\0';
			//puts(ime);
			fflush(stdin);
			fprintf(fajl_rezultati,"\n%d %s ",tren_rez,ime);
			fclose(fajl_rezultati);
		}
	}
	free(ime);


}

main(){
	//upravlja igrom
	int indik_1;
	indik_1=glavni_meni();
	while(indik_1!=3){//sve dok korisnik ne unese 3 program se ponavlja
		if(indik_1==2){//kada korinik unese 2 ispisuje se tabela
			razmakX1();
			ispis_tabele();
			razmakX2();
		}
		if(indik_1==1){//kada korinik unese 1 pocinje igra
			igra();
		}
	
		indik_1=glavni_meni();
	}	
}
