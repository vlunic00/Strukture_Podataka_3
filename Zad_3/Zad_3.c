#define _CRT_SECURE_NO_WARININGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 50

struct osoba;
typedef struct osoba* Pozicija;

typedef struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
}_os;

Pozicija novaOsoba();
void ispis(Pozicija);
void unosPocetak(Pozicija, Pozicija);
void unosKraj(Pozicija, Pozicija);
Pozicija pronadji(Pozicija, char[MAX]);
void izbrisi(Pozicija, char[MAX]);
void unesiIspred(Pozicija, Pozicija, char[MAX]);
void unesiIza(Pozicija, Pozicija, char[MAX]);
void sortiraj(Pozicija);
void citaj(char[MAX]);
void upisi(Pozicija, char[MAX]);
Pozicija novaOsobaAnonimno();

int main() {

	_os head;
	head.next = NULL;
	Pozicija p = NULL;
	Pozicija trazen = NULL;
	char op = ' ';
	char pom[MAX] = " ";

	printf("Opcije:\nNova osoba na pocetak - P\nNova osoba na kraj - K\nIspis - I\nPretraga - T\nIzbrisi - D\nIzadji - E\n"
		"Dodaj iza - A\nDodaj ispred - B\nSortiraj - S\nUpisi u datoteku - W\nProcitaj iz datoteke - R\n");
	while (1) {
		printf("Unesite sto zelite\n");

		scanf(" %c", &op);
		op = toupper(op);
		switch (op) {

		case 'P':
			p = novaOsoba();
			unosPocetak(&head, p);
			printf("Unos na pocetak obavljen\n");
			break;

		case 'K':
			p = novaOsoba();
			unosKraj(&head, p);
			printf("Unos na kraj obavljen\n");
			break;

		case 'I':
			ispis(&head);
			break;

		case 'T':
			printf("Unesite prezime trazene osobe\n");
			scanf("%s", pom);
			trazen = pronadji(&head, pom);
			if (trazen == NULL)
				printf("\nGreska; nema te osobe\n");
			else
				printf("%s %s %d\n", trazen->ime, trazen->prezime, trazen->god);
			break;

		case 'D':
			printf("Unesite ime osobe koju zelite izbrisati\n");
			scanf("%s", pom);
			izbrisi(&head, pom);
			printf("Osoba (%s) uspijesno izbrisana\n", pom);
			break;

		case 'A':
			printf("Unesite prezime osobe iza koje zelite dodati novi element:\n");
			scanf("%s", pom);
			p = novaOsoba();
			unesiIza(&head, p, pom);
			break;

		case'B':
			printf("Unesite ime osobe ispred koje zelite dodati novi element:\n");
			scanf("%s", pom);
			p = novaOsoba();
			unesiIspred(&head, p, pom);
			break;

		case 'S':
			sortiraj(&head);
			break;

		case 'W':
			printf("Upisite ime datoteke u koju zelite upisati listu:\n");
			scanf("%s", pom);
			upisi(&head, pom);
			break;

		case'R':
			printf("Upisite ime datoteke iz koje zelite iscitati listu:\n");
			scanf("%s", pom);
			citaj(pom);

		case 'E':
			return 0;
			break;

		default:
			printf("Greska; upisite jedno od gore zadanih slova");
			break;

		}
	}
	return 0;
}
//stvara novog clana, ali ne stavlja ga u listu
//------------------------------
Pozicija novaOsoba() {

	Pozicija p = NULL;

	p = (Pozicija)malloc(sizeof(struct osoba));
	printf("Unesite ime, prezime i godinu rodjenja\n");
	scanf(" %s %s %d", &p->ime, &p->prezime, &p->god);
	p->next = NULL;
	return p;
}

//stavlja poslanu osobu na pocetak liste
//------------------------------
void unosPocetak(Pozicija head, Pozicija p) {

	p->next = head->next;
	head->next = p;
}

//stavlja poslanu osobu na kraj liste
//------------------------------
void unosKraj(Pozicija q, Pozicija p) {

	//pronalazi zadnji clan
	while (q->next != NULL) {
		q = q->next;
	}
	unosPocetak(q, p);
}

//pronalazi i vraca adresu trazene osobe
//------------------------------
Pozicija pronadji(Pozicija q, char prez[MAX]) {

	//vrti sve clanove dok ne nadje prezime koje se podudara(strcmp tad vraca 0) ili dok ne dodje do kraja liste(while se vrti dok nesto ne bude 0)
	while (q->next != NULL && strcmp(q->prezime, prez))
		q = q->next;

	return q;
}

//pretrazuje clana po prezimenu i pamti adresu clana prije (prev). Kad nadje clana izbrise ga
//------------------------------
void izbrisi(Pozicija p, char name[MAX]) {
	Pozicija prev;
	prev = p;
	p = p->next;

	while (p->next != NULL && strcmp(p->ime, name)) {
		prev = p;
		p = p->next;
	}

	if (prev->next != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}

//ispisuje svakog clana liste
//------------------------------
void ispis(Pozicija p) {

	p = p->next;

	printf("---------------------------\n");
	while (p != NULL) {
		printf("%s %s, %d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}
}
//pronalazi trazeni clan pomocu funkcije pronadji i onda dodaje novi clan iza njega
//------------------------------
void unesiIza(Pozicija head, Pozicija p, char prez[MAX]) {
	Pozicija trazen;
	trazen = pronadji(head, prez);
	printf("%s\n", trazen->ime);
	if (trazen == NULL) {
		printf("Osoba nije pronadjena\n");
		return -2;
	}

	unosPocetak(trazen, p);
	printf("Osoba uspijesno unesena\n");
}
//pronalazi trazeni clan i clan ispred(kao u funkciji izbrisi) te dodaje clan nakon "prijasnjeg" (prev)
//------------------------------
void unesiIspred(Pozicija head, Pozicija p, char name[MAX]) {
	Pozicija prev;
	prev = head;
	head = head->next;

	while (head->next != NULL && strcmp(head->ime, name)) {
		prev = head;
		head = head->next;
	}
	if (prev->next != NULL) {
		unosPocetak(prev, p);
		printf("Osoba uspijesno unesena\n");
	}
	else
		printf("Osoba nije pronadjena\n");
}
//sortira listu po prezimenu(p_pom koristim jer ce se pozicija clana p u listi mjenjati ovisno o rezultatu usporedbe)
//------------------------------
void sortiraj(Pozicija head) {
	int i = 0; 
	int j = 0;
	int n = 0;
	int k = 0;
	Pozicija p = head->next;
	Pozicija q = p->next;
	Pozicija pom = head->next;
	Pozicija prev = head;

	//prebrojava clanove liste
	while (head != NULL) {
		head = head->next;
		n++;
	}

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {

			//provjerava jesu li prva slova ista
			while (pom->prezime[k] == q->prezime[k])
					k++;

			if (pom->prezime[k] > q->prezime[k]) {
				p->next = q->next;
				q->next = p;
				prev->next = q;
			}
			q = q->next;
			p = prev->next;
			k = 0;
		}
		pom = pom->next;
	}
}
//upisuje listu u datoteku(ime datoteke poslano u varijabli pom)
//------------------------------
void upisi(Pozicija head, char dat[MAX]) {
	FILE* ulz = fopen(dat, "w");
	if (dat == NULL) {
		printf("Greska pri otvaranju datoteke\n");
		return -1;
	}

	Pozicija p = head;
	Pozicija q = head->next;
	int i = 0;
	int n = 0;

	while (p != NULL) {
		p = p->next;
		n++;
	}

	for (i = 0; i < n; i++) {
		fprintf(ulz, "%s %s %d\n", q->ime, q->prezime, q->god);
		q = q->next;
	}
}
//iscitava listu iz datoteke i stvara ju u memoriji racunala
//------------------------------
void citaj(char dat[MAX]) {
	_os head;
	Pozicija p = NULL;
	p->next = NULL;
	(&head)->next = p;
	Pozicija q = p;
	char pom[100];
	FILE* izl = fopen(dat, "r");

	if (izl == NULL) {
		printf("Greska u otvarnaju datoteke\n");
		return -1;
	}

	int i = 0;
	int n = 0;

	while (!feof) {
		fgets(izl, sizeof(char) * 100, pom);
		n++;
	}
	rewind(izl);
	for (i = 0; i < n; i++) {
		q = novaOsobaAnonimno();
	}
	scanf(izl, "%s %s %d", &q->ime, &q->prezime, &q->god);
	p = q;
	q = q->next;
}
Pozicija novaOsobaAnonimno() {
	Pozicija p = NULL;

	p = (Pozicija)malloc(sizeof(struct osoba));
	p->next = NULL;
	return p;
}