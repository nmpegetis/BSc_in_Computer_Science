#ifndef RECORD_H_
#define RECORD_H_

#define MAXNAME 30

typedef struct{
	int id;
	char name[MAXNAME];
	char surname[MAXNAME];
	float avgPoints;
}Record;


#endif /* RECORD_H_ */
