
//#include "stdafx.h"
//#include <iostream>
#include "stdio.h"
#include "io.h"
#include "process.h"
#include "string.h"
#include "fcntl.h"
#include <stdlib.h>

#define filename1 "pelates.dbs"
#define filename2 "details.dbs"
#define filename3 "report.txt"
#define filename4 "codes.dbs"

FILE *f3;           //αρχικοποίηση για ASCII αρχεία
int fn1,fn2,fn4;   //αρχικοποίηση για μη ASCII αρχεία

struct pelatis
{
    int kodikos;
	char name[51];
	char address[61];
	char telephone[51];
	int code;
};

struct details
{
	float xreostiko;
	char lastdate[9];
	char pname[21];
	int kids;
};

struct code
{
    int temp_code;
};

void openfiles()
{
	fn1=open(filename1,0);	  //(0 για διάβασμα, 1 για γράψιμο, 2 για apend)
	fn2=open(filename2,0);
	f3=fopen(filename3,"w");
	fn4=open(filename4,0);  //(r για διάβασμα, w για γράψιμο, a για apend)

		if(fn1==-1)
		{
			printf("pelates.dbs not opened");
			exit(-1);
		}
		if(fn2==-1)
		{
			printf("details.dbs not opened");
			exit(-1);
		}
		if(f3==NULL)
		{
			printf("report.txt not opened");
			exit(-1);
		}
		if(fn4==-1)
		{
			printf("codes.txt not opened");
			exit(-1);
		}
}

void closefiles()
{
	close(fn1);
	close(fn2);
	fclose(f3);
	close(fn4);
}

void ofiletes()
{
	int position1,position2,g1,g2,g4,cod;
	struct pelatis pel;  //δίνουμε όνομα στο struct pelatis
	struct details det;	 //δίνουμε όνομα στο struct detail
	struct code c;
	long pos1,pos2;  // Τα pos1 pos2 pos3 είναι μεταβλητές τύπου μεγάλου ακεραίου
	float xrewsh;

	//στη while χρησιμοποιώ μονο το αρχείο f4 γιατί αυτό περιέχει τους κωδικούς των πελατών οι οποίοι είναι ίδιοι με τους κωδικούς του struct pel
	while(!eof(fn4))
	{
		//read from codes.dbs
		g4=read(fn4, &c, sizeof c);

		//read from pelates.dbs
		pos1=(long)((c.temp_code-1)* sizeof pel);//pos1->θέση του αρχείου,(θεση-1)*->άυξων αριθμός κάθε εγγραφης, sizeof->Μέγεθος εγγραφής (συνολικός όγκος)
		position1=lseek(fn1,pos1,0);    //στο αρχείο fn1,μετακινείται ο δείκτης του αρχείου από τη θέση 0,έως τη θέση pos1
		g1=read(fn1, &pel, sizeof pel); //διαβάζει το αρχείο fn1, και αποθηκεύει στο struct pel(στην ουσια αποθηκεύει στη μνήμη) τα δεδομένα

		//read from details.dbs
		pos2=(long)((pel.code-1)* sizeof det); //ορίζει τη θέση του αρχείου σε σχέση με τον κωδικό που είναι αποθηκευμένος στο struct pel
		position2=lseek(fn2,pos2,0);        //μετακινει τον δείκτη στη συγκεκριμένη θέση στο δεύτερο αρχείο
		g2=read(fn2, &det, sizeof det);     //διαβάζει το αρχείο fn2, και αποθηκεύει στο struct det

		if((det.xreostiko>10000)&&(det.kids==1))
		{
		    xrewsh=det.xreostiko*1.10;
			fprintf(f3, "\n %s%s%f", pel.name, pel.telephone, xrewsh); //αποθηκεύει στο ASCII αρχείο (f3) τα αποτελέσματα
		}
		c.temp_code++;
	}
}


int main()
{
	openfiles();
	ofiletes();
	closefiles();
	return 0;
}
