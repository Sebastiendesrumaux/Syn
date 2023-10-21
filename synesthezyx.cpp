// -*- coding: utf-8 -*-
//emacs M-g g goto-line
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim go to bookmark 'a
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
//vim bookmark ma
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//#define do_le_plus_grave 24
#define lala 1
#define do_le_plus_grave 0
#define do_le_plus_aigu 108
#define etendue_piano do_le_plus_aigu-do_le_plus_grave
float ztranslate=-4;
long int moteur=0;
#define MIKADO -7
#define ORBITATION -10
#define TETRAMAUVEM16 -16

long int moteur1=0;
long int moteur2=0;
long int moteur3=0;
long int inc_moteur=1;
long int inc_moteur1=1;
long int inc_moteur2=0;
long int inc_moteur3=0;
long int *inc_moteur_en_cours=&inc_moteur1;
char txt_video_clip[256];
char otxt_video_clip[256];
int new_txt_video_clip=0;
#define setcolor(i) glColor3ub(comp(i))
int dbg=0;
int affiche_pastilles=1;	
int affiche_poles=0;	
int auto_change=0;
int leds=0; //parce que quand on lance gdb, on ne lance pas la partie python et donc le programme ne décolle pas
//on pourrait tester en lançant la partie python avec un exec mais on a la flemme
//donc si tu veux remettre les leds quand le programme est debugué, n'hésite pas à repasser ça a 1
int wordsdisplay=0;
#define firstpart -17
#define lastpart 13
//int partnum=firstpart;
int partnum=-17; //-16;
int prevpart=-300000;
//0 : la courbe en 3D
unsigned long int vbl=0;
int sound=0;
#include <alsa/asoundlib.h>
#include <X11/Xlib.h>
//#include <SDL/SDL.h>
#define rprintf(VAR,PAR) if (myrand() < 0.01) printf(VAR,PAR);
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include <stdint.h>

#include <limits.h>
#include <unistd.h>
#include <math.h>
#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <getopt.h>
//#include "/usr/include/alsa/asoundlib.h"
#include <sys/time.h>
#include <float.h>
SDL_Event event;

#define false 0
#define true 1

int no_begin_lights=0;
void change_part();
void calcul_matrice_deplacement_en_fonction_des_notes_et_de_la_partnum();
void pvec(float u1,float u2,float u3,float v1,float v2,float v3,float *nor);
void pvecv(float v1[3], float v2[3], float *nor);
void vsub(float A[3], float B[3], float *R);
void normalize(float *v);
void aff_txt_at_pos(char *txt, float x, float y); 
char *note_name(int val);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int canvas_id;

unsigned char *canvas;

int dimX=0;//1360
int dimY=0;//768
int gargc;
int haptique=0;

int debug=0;

int midi_simulation=0; // pour jouer automatiquement 
int midi_simulation_sleep_time=5;//20; // le temps entre chaque note random

char **gargv;
#define OGL 1
#define comp(i) composantes[i].r,composantes[i].v,composantes[i].b
#define compub(i) composantes[i].r,composantes[i].v,composantes[i].b
#define compaub(i) composantes[i].r,composantes[i].v,composantes[i].b,128

int load_png(int numdirpar);
typedef struct {
	int name;
	int intensity;
	long time;
	long duree;
	int touche;
} notes;
int nb_notes=0;
notes *tab_notes;
#define nb_notes_max 2*65535
#define piano_max_keys etendue_piano
int notes_num[piano_max_keys];
int notes_vals[piano_max_keys]; 
int nb_notes_since_last_change=0;
int nb_notes_to_change;
int XXX=0;
float nor[3];
int numdir=1;
int gltourne=0;
int dpmsoff=0;
void read_numdir();
void change_parametres();
int init_aff_bmp();
pthread_t gl_thread;
pthread_t keyboard_thread;
void *gl_animate(void *ptr);
int initsdl();
int randomized_twelve[12]={0,1,2,3,4,5,6,7,8,9,10,11};
int note=-1; // le numéro de la note sur le piano
int last_note_on = -1;
int aucune_note=1;
int touche_en_cours = -1; // la note en cours pas modulo 12
int touche_precedente = -1; // la note precedente pas modulo 12
int touche_avant_la_precedente = -1; // la note avant la precedente pas modulo 12 ...
int touche_avant_avant_la_precedente = -1;
int note_en_cours() {
	return(tab_notes[nb_notes-1].name);
}
int note_en_cours_time() {
	return(tab_notes[nb_notes-1].time);
}
#define note_piano() last_note_on_num

int last_note_off = -1;
int onote_on_off[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int note_on_off[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int note_nb[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int notes_val_dans_l_octave[12];
int touche_on_off_vals[etendue_piano]; // double emploi avec notes_val mais j'ai préféré rajouter quelquechose 
										// plutôt que d'en changer une parce qu'il y avait une légère bizarrerie
										// car notes_val travaille sur une étendue démesurée et donc bon...
										// c'est comme compteurp et dcompteurp, en fait l'index est le numéro
										// de la note midi alors que dans touche_on_off_vals on soustrait 
										// la valeur midi de l	

float compteur[12]= {0,0,0, 0,0,0, 0,0,0, 0,0,0};
float dcompteur[12]={0,0,0, 0,0,0, 0,0,0, 0,0,0};

float compteurp[etendue_piano];
float dcompteurp[etendue_piano];

class Init { 
	public: 
		Init() {
			for (int i=0;i<etendue_piano;i++) {
				compteurp[i]=0; dcompteurp[i]=0;
				touche_on_off_vals[i]=0;
			}
		}
};
Init *init = new Init();

int maxcompteur=100;
int randompos;
int randomized_pos_de_note[12]={-1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1};
int massage_board_has_been_reset=0;
int last_note_played_time=0;
int newnotes_val[12]={0,0,0, 0,0,0, 0,0,0, 0,0,0};
int premierevbl=1;
int test_matN();
#define hauteur_triangle_equilateral sqrt(3)/2

#define DO 0
#define DOD 1
#define RE 2
#define RED 3
#define MI 4
#define FA 5
#define FAD 6
#define SOL 7
#define SOLD 8
#define LA 9
#define LAD 10
#define SI 11

static int gammes[12][12]={
	{DO,RE,MI,FA,SOL,LA,SI},
	{DOD,RED,FA,FAD,SOLD,LAD,DO},
	{RE,MI,FAD,SOL,LA,SI,DOD},
	{RED,FA,SOL,SOLD,LAD,DO,RE},
	{MI,FAD,SOLD,LA,SI,DOD,RED},
	{FA,SOL,LA,LAD,DO,RE,MI},
	{FAD,SOLD,LAD,SI,DOD,RED,FA},
	{SOL,LA,SI,DO,RE,MI,FAD},
	{SOLD,LAD,DO,DOD,RED,FA,SOL},
	{LA,SI,DOD,RE,MI,FAD,SOLD},
	{LAD,DO,RE,RED,FA,SOL,LA},
	{SI,DOD,RED,MI,FAD,SOLD,LAD}
};
static int pentatoniques[12][12]={
	{DO,  RE,  FA,  SOL, LA},
	{DOD, RED, FAD, SOLD,LAD},
	{RE,  MI,  SOL, LA,  SI},
	{RED, FA,  SOLD,LAD, DO},
	{MI,  FAD, LA,  SI,  DOD},
	{FA,  SOL, LAD, DO,  RE},
	{FAD, SOLD,SI,  DOD, RED},
	{SOL, LA  ,DO,  RE,  MI},
	{SOLD,LAD ,DOD, RED, FA},
	{LA,  SI  ,RE,  MI,  FAD},
	{LAD, DO,  RED, FA,  SOL},
	{SI,  DOD, MI,  FAD, SOLD}
};
float sqr(float x) {
	return x*x;
}

vector<int> cribleEratosthene(int n) {
	vector<bool> premiers(n + 1, true);
	premiers[1] = false;
		    
	for (int i = 2; i <= sqrt(n); ++i) {
		if (premiers[i]) {
			for (int j = i * i; j <= n; j += i) {
                premiers[j] = false;
            }
		}
	}
		    
	vector<int> result;
	for (int i = 2; i <= n; ++i) {
		if (premiers[i]) {
			result.push_back(i);
		}
	}
																													    
	return result;
}

int are_les_chaines_egales(char *chain1, char *chain2) {
	int tailles1;
	int tailles2;
	int i=0;
	int j=0;
	while (chain1[i]!=0) i++; // à la fin on aura i qui est égal à la taille de la chaine
	while (chain2[j]!=0) j++; // à la fin on aura j qui est égal à la taille de la chaine
	if (i!=j) return 0;
	int elles_sont_egales=1;
	for (int n=0;n<i;n++) {
		elles_sont_egales=chain1[n]==chain2[n];
		if (!elles_sont_egales) break;
	}
	return elles_sont_egales;

}
void test_if_trenteseptTok() {
    FILE *f,*g;
    char s[64],t[64];
    int ret=0;
    if ((f=fopen("/home/pi/prg/colormusic/37","r"))!=NULL) {
        fclose(f);
        g=fopen("/home/pi/prg/colormusic/37T","r");
        fgets( s, 64, g );
        fclose(g);

        g=fopen("/home/pi/prg/aff_oled/examples/parsing_ifconfig_result","r");

        fgets( t, 64, g );

        fclose(g);

        if (strcmp(s,t)!=0) {
            exit(0);
        }
    }
}

class Vecteur {
public:
  float x;
  float y;
  float z;
  Vecteur() {
			
  }
  Vecteur(float x, float y, float z) {
    this->x=x;
    this->y=y;
    this->z=z;
  }
  Vecteur(Vecteur *v) {
    this->x=v->x;
    this->y=v->y;
    this->z=v->z;
  }
  Vecteur* set(float x, float y, float z) {
    this->x=x;
    this->y=y;
    this->z=z;
    return(this);
  }
};
// ne pas lire la foutue structure suivante
typedef struct {
  float x;
  float y;
  char couleur;
  int touched;
} pastilles;

// en revanche celle là, elle est tellement COLOREE !!!!
typedef struct {
  double r;       // a fraction between 0 and 1
  double g;       // a fraction between 0 and 1
  double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
  double h;       // angle in degrees
  double s;       // a fraction between 0 and 1
  double v;       // a fraction between 0 and 1
} hsv;

//static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);


hsv rgb2hsv(rgb in) {
  
  hsv         out;
  double      min, max, delta;

  min = in.r < in.g ? in.r : in.g;
  min = min  < in.b ? min  : in.b;
  max = in.r > in.g ? in.r : in.g;
  max = max  > in.b ? max  : in.b;

  out.v = max;                                // v
  delta = max - min;
  if (delta < 0.00001) {
    out.s = 0;
    out.h = 0; 
    
    return out;
  }
  
  if ( max > 0.0 ) { 
    out.s = (delta / max);                  // s
  } else {
    // if max is 0, then r = g = b = 0
    // s = 0, h is undefined
    out.s = 0.0;
    out.h = NAN;                           
    return out;
  }
  
  if( in.r >= max ) {                         
    out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
  } else {
    if( in.g >= max ) {
      out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    } else {
      out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan
    }
    
  }
  
  out.h *= 60.0;                              // degrees
  if ( out.h < 0.0 )
    out.h += 360.0;

  return out;
}


rgb hsv2rgb(hsv in) {
  double      hh, p, q, t, ff;
  long        i;
  rgb         out;
	
  if(in.s <= 0.0) {      
    out.r = in.v;
    out.g = in.v;
    out.b = in.v;
    return out;
  }
  
  hh = in.h;
  if(hh >= 360.0) hh = 0.0;
  hh /= 60.0;
  i = (long)hh;
  ff = hh - i;
  p = in.v * (1.0 - in.s);
  q = in.v * (1.0 - (in.s * ff));
  t = in.v * (1.0 - (in.s * (1.0 - ff)));
  
  switch(i) {
  case 0:
    out.r = in.v;
    out.g = t;
    out.b = p;
    break;
  case 1:
    out.r = q;
    out.g = in.v;
    out.b = p;
    break;
  case 2:
    out.r = p;
    out.g = in.v;
    out.b = t;
    break;
    
  case 3:
    out.r = p;
    out.g = q;
    out.b = in.v;
    break;
    
  case 4:
    out.r = t;
    out.g = p;
    out.b = in.v;
    break;
  case 5:
  default:
    out.r = in.v;
    out.g = p;
    out.b = q;
    break;
  }
  
  return out;
}  













































//une couleur
typedef struct {
  unsigned char r; 
  unsigned char v;  
  unsigned char b;  
  unsigned char w;  
} couleur;

couleur composantes[12];
float tabcomposantes[12][3];
float tabcomposantesa[12][4];
void make_tabcomposantes() {
  for (int i=0;i<12;i++) {    
    tabcomposantes[i][0]=composantes[i].r/255.0;    
    tabcomposantes[i][1]=composantes[i].v/255.0;    
    tabcomposantes[i][2]=composantes[i].b/255.0;    
  }
  for (int i=0;i<12;i++) {
    tabcomposantesa[i][0]=composantes[i].r/255.0;    
    tabcomposantesa[i][1]=composantes[i].v/255.0;    
    tabcomposantesa[i][2]=composantes[i].b/255.0;
    tabcomposantesa[i][3]=128/255.0;
  }
}

void make_composantes_rainbow() {  
  rgb colrgb;  
  hsv colhsv;  
  for (int i=0;i<12;i++) {    
///////////////////////////////////////
    colhsv.h=360.0*((float)(i)/12);    
///////////////////////////////////////////
    colhsv.s=1.0;    
    colhsv.v=1.0;    
    colrgb = hsv2rgb(colhsv);    
    composantes[i].r=(unsigned char)(255.0*colrgb.r);    
    composantes[i].v=(unsigned char)(255.0*colrgb.g);
    composantes[i].b=(unsigned char)(255.0*colrgb.b);
  }
}

class Palette {
public:
  int nb_couleurs;
  unsigned char (*couleurs)[4];
  Palette(float debuth, float finh, int nb_couleurs, unsigned char alpha) {			
  ////////////////////////////////////////////////////////////
    /* crée une palette en prenant une portion de h dans hsv */
	///////////////////////////////////////////////////////////////
    rgb colrgb;
    hsv colhsv;
    this->nb_couleurs=nb_couleurs;
    this->couleurs=(unsigned char (*)[4])malloc(this->nb_couleurs*4*sizeof(unsigned char));
    // la ligne suivante calcule et place dans une variable un incrément de la composante hue
    // de la couleur 
    float inch=(finh-debuth) / nb_couleurs;
    for (int i=0;i < this->nb_couleurs;i++) {
      // la ligne précédente fait boucler nb_couleurs fois le bloc suivant en augmentant de 1
      // à chaque fois la valeur de i
      colhsv.h = 360.0 * (debuth+i*inch);
      // la ligne précédente calcule la valeur de hue en multipliant 360 par la valeur initiale
      // de h à laquelle on ajoute i * la valeur de l'incrément de h
      colhsv.s = 1;
      colhsv.v = 1;
      colrgb = hsv2rgb(colhsv);
      couleurs[i][0] = (unsigned char)(colrgb.r*255);
      couleurs[i][1] = (unsigned char)(colrgb.g*255);
      couleurs[i][2] = (unsigned char)(colrgb.b*255);
      couleurs[i][3] = alpha;
    }
  }
  ~Palette() {
    free(couleurs);
  }
  void affiche() {
    glMatrixMode(GL_PROJECTION);
    // alors si on définit la matrice de projection comme une matrice identité alors on affiche directement
    // sur un écran de -1 à 1 en x et de -1 à 1 en y
    
    glPushMatrix();
    
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_LINES);
    {
      float incx = 2.0 / this->nb_couleurs;
      // pareil que la dernière fois, on a un incrément, cette fois en x, parce qu'on veut 
      // tracer le long d'une ligne autant de segments horizontaux qu'il y a de couleurs,
      // chaque segment étant dans une des couleurs de la palette, successivement
      // autrement dit, en langage informatique beaucoup plus précis et clair
      float x = -1;
      for (int i=0; i< this->nb_couleurs; i++) {
		// on définit la couleur du segment à la ligne suivante
		glColor4ub(couleurs[i][0], couleurs[i][1], couleurs[i][2], couleurs[i][3]);
		glVertex2f(x, 0.3);
		glVertex2f(x,-0.3); 
		x += incx;
      }
    }
    glEnd();

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
  }
};

//0 do re mi fa sol la si
//1 do# re# fa fa# sol# la# do
//2 re mi fa# sol la si do#
//3 re# fa sol sol# la# do re
//4 mi fa# sol# la si do# re#
//5 fa sol la la# do re mi
//6 fa# sol# la# si do# re# fa
//7 sol la si do ré mi fa#
//8 sol# la# do do# re# fa sol
//9 la si do# re mi fa# sol#
//10 la# do re re# fa sol la  
//11 si do# re# mi fa# sol# la#

int gamme_en_cours=0;
int indexgamme=0;
void init_gammes() {
/*
  gammes[DO]={DO,RE,MI,FA,SOL,LA,SI};
  gammes[DOD]={DOD,RED,FA,FAD,SOLD,LAD,DO};
  gammes[RE]={RE,MI,FAD,SOL,LA,SI,DOD};
  gammes[RED]={RED,FA,SOL,SOLD,LAD,DO,RE};
  gammes[MI]={MI,FAD,SOLD,LA,SI,DOD,RED};
  gammes[FA]={FA,SOL,LA,LAD,DO,RE,MI};
  gammes[FAD]={FAD,SOLD,LAD,SI,DOD,RED,FA};
  gammes[SOL]={SOL,LA,SI,DO,RE,MI,FAD};
  gammes[SOLD]={SOLD,LAD,DO,DOD,RED,FA,SOL};
  gammes[LA]={LA,SI,DOD,RE,MI,FAD,SOLD};
  gammes[LAD]={LAD,DO,RE,RED,FA,SOL,LA};
  gammes[SI]={SI,DOD,RED,MI,FAD,SOLD,LAD};
*/
}

// ne pas s'en faire, jusque là, tout va bien


























float myrand() {
  return (float)rand() / RAND_MAX;
}



































/*
  gammes[DO]={DO,RE,MI,FA,SOL,LA,SI};
  gammes[DOD]={DOD,RED,FA,FAD,SOLD,LAD,DO};
  gammes[RE]={RE,MI,FAD,SOL,LA,SI,DOD};
  gammes[RED]={RED,FA,SOL,SOLD,LAD,DO,RE};
  gammes[MI]={MI,FAD,SOLD,LA,SI,DOD,RED};
  gammes[FA]={FA,SOL,LA,LAD,DO,RE,MI};
  gammes[FAD]={FAD,SOLD,LAD,SI,DOD,RED,FA};
  gammes[SOL]={SOL,LA,SI,DO,RE,MI,FAD};
  gammes[SOLD]={SOLD,LAD,DO,DOD,RED,FA,SOL};
  gammes[LA]={LA,SI,DOD,RE,MI,FAD,SOLD};
  gammes[LAD]={LAD,DO,RE,RED,FA,SOL,LA};
  gammes[SI]={SI,DOD,RED,MI,FAD,SOLD,LAD};
*/

int gamme_relative(int note) {
  if (note==DO) return LA;
  if (note==DOD) return LAD;
  if (note==RE) return SI;
  if (note==RED) return DO;
  if (note==MI) return DOD;
  if (note==FA) return RE;
  if (note==FAD) return RED;
  if (note==SOL) return MI;
  if (note==SOLD) return FA;
  if (note==LA) return FAD;
  if (note==LAD) return SOL;
  if (note==SI) return SOLD;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
int are_anagrammes(int *g1, int *g2, int n) {
  int *deja_trouvee = (int*) malloc(n*sizeof(int));
  for (int i=0;i<n;i++) deja_trouvee[i]=0;
  for (int i=0;i<n;i++) {
    int ok=0;
    for (int j=0;j<n;j++) {
      if ((g1[i]==g2[j]) && (!deja_trouvee[j])) {
		deja_trouvee[j]=1;
		ok=1;
		break;
      }
    }
    if (!ok) { free(deja_trouvee); return 0; }
  }
  free(deja_trouvee);
  return 1;
}
////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

class DetecteurDeGamme {
public:
  int gammes_possibles[12];
  int nb_gammes_possibles;
  int gamme;
  int muted=0;
  char *notes_gamme_cat(int gamme, char *s) {
    for (int i=0;i<7;i++) {
      strcat(s,note_name(gammes[gamme][i]));
      strcat(s," ");
    }
    return s;	
  }

  DetecteurDeGamme() {
    for (int i=0;i<12;i++) {
      gammes_possibles[i]=1;
    }
  }
  int une_gamme_possible_ou_DO() {
    if (nb_gammes_possibles==0) return DO;
    if (nb_gammes_possibles==1) return gamme;
    for (int i=0;i<12;i++) 
      if (gammes_possibles[i]) return(i);
  }
  void processMuted() {
    muted=0;//hop
    process();
    muted=1;
  }
  // est ce que la note fait passer la gamme dans une autre gamme,
  // sinon la note est dite mauve et la méthode retourne -1
  
  int is_cette_note_fait_passer_la_gamme_dans_une_autre_gamme(int gamme, int note) {
    int gamme_a_tester[7];
    //autrement dit
    for (int i=0;i<7;i++) {
		// on va remplacer la ième note de la gamme en cours par la note et 
		// regarder si on obtient une gamme
		if (gammes[gamme][i]!=note) {
			// on commence par créer la "gamme" à tester
			for (int j=0;j<7;j++) {
			  gamme_a_tester[j]=gammes[gamme][j];										
			}
			gamme_a_tester[i]=note;
			// et maintenant on regarde si la gamme 
			// à tester est un anagramme d'une gamme
			for (int k=0;k<12;k++) {
			  if (are_anagrammes(gamme_a_tester,gammes[k],7)) return k;
			  // si la radio ne me touchait pas, je ne l'écouterais pas, donc je l'écoute parce qu'elle me touche
			}
		}
	}
	return -1;
  }
  void process() {
///////////////////////////////////////////////////////////////////////////////////////
/////////// MON PLUS BEAU CODE DE TOUS LES TEMPS
///////////////////////////////////////////////////////////////////////////////////////

    int note=note_en_cours();

    if (note==-1) return;
    
    for (int i=0;i<12;i++) { // pour chaque gammes
      int note_absente=1;
      for (int j=0;j<7;j++) { // pour chaque note de la gamme
		if (note==gammes[i][j]) {
		  note_absente=0;
		  break;
		}
	}
	if (note_absente)
		gammes_possibles[i]=0;
    }
    
    int aucune_gamme_n_est_possible=1;

    for (int i=0;i<12;i++) {
      if (gammes_possibles[i]) {
		aucune_gamme_n_est_possible=0;
		break;
      }
    }

    if (aucune_gamme_n_est_possible) {
      for (int i=0;i<12;i++) {// on reset la tab des games possibles
		gammes_possibles[i]=1;
      }
    }
    
    char s[128];
    float xaff;
    if (!muted) {
		sprintf(s,"- ");
		for (int i=0;i<12;i++) {
			if (gammes_possibles[i]) {
				strcat(s,note_name(i));
				strcat(s,"/");
				strcat(s,note_name(gamme_relative(i)));
				strcat(s," ");
			}
		}
		xaff=1.1;
		aff_txt_at_pos(s,xaff,1.5);
    }

	nb_gammes_possibles=0;

	for (int i=0;i<12;i++) {
		if (gammes_possibles[i]) nb_gammes_possibles++;
	}
    
	if (nb_gammes_possibles==1) {

		for (int i=0;i<12;i++) {
			if (gammes_possibles[i]) gamme=i;
		}

		if (!muted) {
			sprintf(s," ");
			for (int i=0;i<7;i++) {
				strcat(s,note_name(gammes[gamme][i]));
				strcat(s," ");
			}
			aff_txt_at_pos(s,xaff,1.3);
		}
	} if (nb_gammes_possibles==0) {
		gamme=-1;
	} else {
			if (!muted) {
				if (nb_gammes_possibles<=3) {
					char *s=(char*)malloc(sizeof(char)*125);
					sprintf(s," ");
					for (int i=0;i<12;i++) {
						if (gammes_possibles[i]) {
							s=notes_gamme_cat(i,s);
							strcat(s," ");
					    }
					}
	  
					aff_txt_at_pos(s,xaff,1.3);
					free(s);

				}
			}
		}	
	}
};
class DetecteurDeGammePentatonique {
public:
  int gammes_possibles[12];
  char *notes_pentatonique_cat(int gamme, char *s) {
    for (int i=0;i<5;i++) {
      strcat(s,note_name(pentatoniques[gamme][i]));
      strcat(s," ");
    }
    return s;
  }
  DetecteurDeGammePentatonique() {
    for (int i=0;i<12;i++) {
      gammes_possibles[i]=1;
    }
  }
  void process(int note) {
    if (note==-1) return;
    for (int i=0;i<12;i++) { // pour chaque gammes
      int note_absente=1;
      for (int j=0;j<5;j++) { // pour chaque note de la gamme
	if (note==pentatoniques[i][j]) {
	  note_absente=0;
	  break;
	}
      }
      if (note_absente)
	gammes_possibles[i]=0;
				
    }
			
    int aucune_gamme_n_est_possible=1;
    for (int i=0;i<12;i++) {
      if (gammes_possibles[i]) {
	aucune_gamme_n_est_possible=0;
	break;
      }
    }
    if (aucune_gamme_n_est_possible) {
      for (int i=0;i<12;i++) {// on reset la tab des games possibles
	gammes_possibles[i]=1;
      }
    } 
    char s[228];
			
    sprintf(s,"- ");
    for (int i=0;i<12;i++) {
      if (gammes_possibles[i]) {
	strcat(s,note_name(i));
	strcat(s,"/");
	strcat(s,note_name(gamme_relative(i)));
	strcat(s," ");
      }
    }
    float xaff=0;
    aff_txt_at_pos(s,xaff,1.7);
			
    int nb_gammes_possibles=0;
    for (int i=0;i<12;i++) {
      if (gammes_possibles[i]) nb_gammes_possibles++;
    }
    int gamme;
    if (nb_gammes_possibles==1) {
      for (int i=0;i<12;i++) {
	if (gammes_possibles[i]) gamme=i;
      }
			
      sprintf(s," ");
      for (int i=0;i<5;i++) {
	strcat(s,note_name(pentatoniques[gamme][i]));
	strcat(s," ");
      }
      aff_txt_at_pos(s,xaff,2.0);
    }
    else {
      if ((nb_gammes_possibles<=3) || (1)) {
	char *ss=(char*)malloc(sizeof(char)*225);
	sprintf(ss," ");
	for (int i=0;i<12;i++) {
	  if (gammes_possibles[i]) {
	    ss=notes_pentatonique_cat(i,ss);
	    strcat(ss," ");
	  }
	}

	aff_txt_at_pos(ss,xaff,1.5);
	free(ss);
      }
    }
			
    //	aff_txt_at_pos("",0,1.1);
  }

};
// la même

// Constructor
DetecteurDeGamme *detecteurDeGamme=new DetecteurDeGamme();
DetecteurDeGammePentatonique *detecteurDeGammePentatonique=new DetecteurDeGammePentatonique();

void def_mot(char *s) {
  char cmd[64];
  sprintf(cmd,"echo %s >/home/pi/prg/colormusic/random_word",s);
  system("/usr/bin/killall -USR1 python3_def"); 
}

long mstime() {
  struct timespec spec;
  clock_gettime(CLOCK_REALTIME, &spec);
  unsigned long s=spec.tv_sec- 1552763777;
  unsigned long ns=spec.tv_nsec;
    
  unsigned long ms = s * 1000 + ns / 1000000;

  return ms;  
}

typedef struct mailles mailles;

struct mailles {
  unsigned long val;
  mailles *next;
};

typedef struct {
  mailles *first;
  mailles *last;
} lists;

lists *list_create(int val) {
  lists *list = (lists*)malloc(sizeof(lists));
  list->first = (mailles *)malloc(sizeof(mailles));
  list->first -> next = NULL;
  list->first -> val = val;
  list->last = list->first;
  return list;
}

void list_add(lists *list,unsigned long val) {
  list->last->next = (mailles*)malloc(sizeof(mailles));
  list->last=list->last->next;
  list->last->val=val;
  list->last->next=NULL;
}

mailles *get_prec(lists *list,mailles *e) {
  mailles *p;
  mailles *prec;
  p=list->first;
  prec=p;
  while (p!=e) {
    prec=p;
    p=p->next;
  }
  return prec;
}

void list_del(lists *list,mailles *e) {
  if (e==list->first) {
    list->first=list->first->next;
    free(e);
  } else {
    mailles *prec = get_prec(list,e);
    prec->next=e->next;
    if (e==list->last) list->last=prec;
    free(e);
  }
}

mailles *list_get(lists *list,int num) {
  mailles *p=list->first;
  for (int i=0;i<num;i++) {
    p=p->next;
  }
  return p;
}

void list_aff(lists *list) {
  printf("liste_aff\n");
  mailles *p=list->first;
  while (p!=NULL) {
    printf("%d ",p->val);
    p=p->next;
  }
  printf("\n");
}

int list_size(lists *list) {
  mailles *p=list->first;
  int n=0;
  while (p!=NULL) {
    n=n+1;
    p=p->next;
  }
  return n;
}

lists **tab_notes_on;
// tableau des num des notes on lorsque la ième note est jouée, on a donc un superbe tableau de toutes les notes en cours 
// lorsque la nième note est jouée ! je me demande à quel endroit je crée ce tab_notes_on, c'est un tableau de listes

void readdimX() {
  FILE *fichier;
  char s[128];
  fichier = fopen("/home/pi/prg/colormusic/dimX","r");
  fgets( s, 128, fichier );
  dimX=atoi(s); //dimension en X de l'écran - width
  fclose(fichier);
}

void readdimY() {
  FILE *fichier;
  char s[128];
  fichier = fopen("/home/pi/prg/colormusic/dimY","r");
  fgets( s, 128, fichier );
  dimY=atoi(s);
  fclose(fichier);
}

void *do_something_periodically(void *data)
{
  int interval = *(int *)data;
  for (;;) {
    sleep(60); //appelé toutes les minutes
    if (((time(NULL) - last_note_played_time) > 60) && (!massage_board_has_been_reset)) {
      if (haptique) {
	system("/home/pi/prg/colormusic/setPololuDualPort");
      }
      //fprintf(stdout,"Reset de la feuille de massage.\n");
      fprintf(stdout,"do something periodically\n");
      massage_board_has_been_reset=1;
      //system("/usr/bin/xset dpms force off");
      dpmsoff=1;
      //gltourne=0; // c'est ici qu'on active ou désactive l'économiseur d'écran 
    }
  }
}

void update_compteur() {
  // pour chaque note on a un compteur qui permet de procéder à des variations, exemple : pour l'octogone, quand on appuie sur une note 
  // ça modifie dcompteur pour le rendre positif ce qui augmente ensuite la valeur de compteur jusqu'à une valeur max, et il est 
  // évident que quand la note est relachée, le dcompteur est placé en négatif et ça fonctionne bien aussi parce qu'il descend jusqu'à
  // zéro
  for (int i=0;i<12;i++) {
    compteur[i]=compteur[i]+dcompteur[i];
    if (compteur[i]>maxcompteur) {
      compteur[i]=maxcompteur;
    }
    if (compteur[i]<0) {
      compteur[i]=0;
    }
  }
  for (int i=0;i<etendue_piano;i++) {
    compteurp[i]=compteurp[i]+dcompteurp[i];
    if (compteurp[i]>maxcompteur) {
      compteurp[i]=maxcompteur;
    }
    if (compteurp[i]<0) {
      compteurp[i]=0;
    }
  }
}

// donc ici c'est le change_dcompteur pour changer la direction de variation du compteur
void change_dcompteur(int note, int on) {
  float kinc=+1;
  float kdec=-2;
  if (partnum==ORBITATION) {
    kinc=0.5;
    kdec=-0.5;
  }

  if (on) {
    dcompteur[note % 12]=kinc;
  } else {
    dcompteur[note % 12]=kdec;
  }
}
void change_dcompteurp(int note, int on) {
  if (on) {
    dcompteurp[note % etendue_piano]=+1;
  } else {
    dcompteurp[note % etendue_piano]=-2;
  }
}


int get_file_nb_lines(char *nf) {

}

int random_read_dico_initialized[2]={0,0};
char *random_read_dico_dico[2][197000];
char random_read_dico_mot[2][128]; // le mot lu du fichier
long random_read_dico_nbmots[2]={0,0};
#define FRANCAIS 0
#define ANGLAIS 1
char *random_read_dico(int langue) {
  if (!random_read_dico_initialized[langue]) {
    long nbmots=0;
    FILE *fichier;
    char nf[128];
    if (langue==ANGLAIS) {
      sprintf(nf,"/home/pi/prg/colormusic/DICOALL.DAT");
    } else if (langue == FRANCAIS) {
      sprintf(nf,"/home/pi/prg/colormusic/DICOF.DAT");
    }
    fichier = fopen(nf,"r");
    int over=0;
    while (!over) {
      if (fgets( random_read_dico_mot[langue], 128, fichier ) != NULL) {	
	random_read_dico_dico[langue][nbmots]=(char*) malloc(sizeof(char)*(1+strlen(random_read_dico_mot[langue])));
	sprintf(random_read_dico_dico[langue][nbmots],"%s",random_read_dico_mot[langue]);
	nbmots++;
      } else {
	random_read_dico_nbmots[langue]=nbmots;
	over = 1;
      }
    }
    random_read_dico_initialized[langue]=1;
  }
  unsigned long rr=rand() + rand() + rand() + rand();

  return random_read_dico_dico[langue][rr % random_read_dico_nbmots[langue]];

}

// Uses POSIX functions to send and receive data from a Maestro.
// NOTE: The Maestro's serial mode must be set to "USB Dual Port".

//The window we'll be rendering to
SDL_Window* gWindow, *glwin = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Texture* newTexture[13] =
  {NULL, NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL, NULL};

void renderTexture(SDL_Texture* texture, int x, int y, SDL_Rect* clip ) { // appelé pour afficher les photos !
  //Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, 640, 480 };

  //Set clip rendering dimensions
  if( clip != NULL )
    {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }

  //Render to screen
  SDL_RenderCopy( gRenderer, texture, clip, &renderQuad );
}

SDL_Texture *file2texture(char *path) { // appelé pour la lecture des fichiers jpg
  
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = NULL;
  loadedSurface = IMG_Load(path);
  
  if( loadedSurface == NULL ) {
    printf( "Unable to load image %s; SDL_image Error: %s\n", path, IMG_GetError() );
  }
  //Color key image
  SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
  
  //Create texture from surface pixels
  newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
  
  //Get rid of old loaded surface
  SDL_FreeSurface( loadedSurface );

  return newTexture;

}

int load_png(int numdirpar) { // qui est en fait du jpg

  char s[128];
  for (int i=1;i<13;i++) {
    sprintf(s,"/home/pi/prg/colormusic/img/i%d/%d.jpg",numdirpar,i);
    newTexture[i]=file2texture(s); 
  }
}

// Gets the position of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.

int maestroGetPosition(int fd, unsigned char channel) {  
  unsigned char command[] = {0x90, channel};
  
  if(write(fd, command, sizeof(command)) == -1) {    
    perror("error writing");
    return -1;    
  }

  unsigned char response[2];
  if(read(fd,response,2) != 2) {
    perror("error reading");
    return -1;
  }

  return response[0] + 256*response[1];

}

// Sets the target of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.
// The units of 'target' are quarter-microseconds.

int maestroSetTarget(int fd, unsigned char channel, unsigned short target) {
  
  unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
  
  if (write(fd, command, sizeof(command)) == -1) {      
    perror("error writing");
    return -1;      
  }
  
  return 0;  
}

int fd;

int initMaestro() {
  
  // Open the Maestro's virtual COM port.
  //const char * device = "\\\\.\\USBSER000";  // Windows, "\\\\.\\COM6" also works
  const char * device = "/dev/ttyACM0";  // Linux
  //const char * device = "/dev/cu.usbmodem00034567";  // Mac OS X
  fd = open(device, O_RDWR | O_NOCTTY);
  printf("dev opened\n");
  
  if (fd == -1) {
    
    perror(device);
    haptique=0;
    //return 1;
      
  } else {
    
    haptique=1;
    
  }
  
  if (haptique) {
    
#ifdef _WIN32
    _setmode(fd, _O_BINARY);
#else
    struct termios options;
    tcgetattr(fd, &options);
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tcsetattr(fd, TCSANOW, &options);
#endif
    
  }
  
  // printf("obtention de la position\n");
  // int position = maestroGetPosition(fd, 0);
  //  int position = 0;

  //printf("Current position is %d.\n", position);

  //int target = (position == 4500 ? 5000 : 4500);
  //int target = 1500;
  //printf("Setting target to %d (%d us).\n", target, target/4);
  
  return 0;
  
}

static snd_seq_t *seq_handle;
static int in_port;
char * myfifop2c = "/tmp/fifop2c";
FILE  *fdp2c;
char * myfifoc2p = "/tmp/fifoc2p";
int fdc2p;

void write_tube(char *s) {
  //printf("Write tube : %s",s);
  write(fdc2p, s, strlen(s));
}

void wait_tube() {
  char buf[128];
  fgets(buf, 100, fdp2c);
}

char rbuf[128];
char *read_tube() {
  fgets(rbuf, 100, fdp2c);
  return rbuf;
}

void open_tubes() {
  /* create the FIFO (named pipe) */
  // struct stat buf;
  printf("Création du tube c2p\n");
  if (access(myfifoc2p,F_OK) == -1) {
    // if (fopen(myfifo,"r") == NULL) {
    printf("Le tube c2p n'existe pas déjà\n");
    mkfifo(myfifoc2p, 0666);
  }
  printf("Tube crée.\n");
  printf("Création du tube p2c\n");
  if (access(myfifop2c,F_OK) == -1) {
    // if (fopen(myfifo,"r") == NULL) {
    printf("Le tube p2c n'existe pas déjà\n");
    mkfifo(myfifop2c,0666);
  }
  printf("Tube crée.\n");
  fdc2p = open(myfifoc2p, O_WRONLY); //bloque tant que pas de lecteur
  printf("Tube c2p ouvert.\n");
  fdp2c = fopen(myfifop2c, "r");
  printf("Tube p2c ouvert.\n");
}

void close_tube() {
  if (!leds) return;
  printf("Fermeture des tubes.\n");
  unlink(myfifop2c);
  unlink(myfifoc2p);
  close(fdc2p);
  fclose(fdp2c);
  printf("Tubes fermés.\n");
}



int pinMapping[] = { //autrement dit val2wpi 
  
  0, //0
  22, //1
  1, //2
  23, //3
  2, //4
  3, //5
  3, //6
  4, //7
  24, //8
  7, //9
  25,//10
  21 //11
  
};

int wPi2Physical[] = {
  
  11,12,13,15,16,18,22,7,3,5,24,26,19,21,23,8,10,-1,-1,-1,-1,29,31,33,35,37,32,36,38,40

};

// la fonction fondamentale qui allume la lumière pix avec les composantes rvb qui vont bien
void setPixelColor(int pix, int r, int v, int b) {
  if (!leds) return;
  char s[256];
  float k=0.05;
  k=1;
  sprintf(s,"setPixelColor %d %d %d %d\n", pix, (int)(k*r), (int)(k*v),(int)(k*b)); 
  write_tube(s);
  wait_tube();
	
}
// la même mais pour une plage de lumières
void setPixelRangeColor(int deb, int fin, int r, int v, int b) {  
  char s[256];  
  sprintf(s,"setPixelRangeColor %d %d %d %d %d\n", deb, fin, r, v, b);  
  write_tube(s);  
  wait_tube();  
}


void read_numdir() {  
  FILE *fichier;  
  char s[128];  
  fichier = fopen("/home/pi/prg/colormusic/numdir","r");  
  fgets( s, 128, fichier );  
  numdir=atoi(s);  
  fprintf(stderr,"les images sont lues dans i%d\n",numdir);  
  fclose(fichier);  
}

void write_numdir() {  
  FILE *fichier;  
  char s[128];  
  fichier = fopen("/home/pi/prg/colormusic/numdir","w");  
  sprintf(s,"%d",numdir);  
  fputs(s,fichier );  
  fclose(fichier);  
}

void genere_composantes() {  
  make_composantes_rainbow();    
  // après avoir précédemment généré les composantes dans une structure de couleurs on les place aussi dans un tableau
  make_tabcomposantes();     

  if (no_begin_lights==0) {      
    for (int i=0;i<12;i++) {
      setPixelColor(i,composantes[i].r,composantes[i].v,composantes[i].b);	
    }      
    sleep(1);      
    for (int i=0;i<12;i++) {		
      if (leds) setPixelColor(i,0,0,0);	
    }      
  }    
}
void calcul_un_point_random_sur_une_sphere(float xpos, float ypos, float zpos, float r, float *rpos) {
  float theta=-0.5*M_PI+M_PI*myrand();
  float alpha=2*M_PI*myrand();
  float z=zpos+r*cos(theta)*sin(alpha);
  float x=xpos-r*cos(theta)*cos(alpha);
  float y=ypos+r*sin(theta);
  rpos[0]=x;
  rpos[1]=y;
  rpos[2]=z;
	
}
void esquisse(float xa, float ya, float za, float xb, float yb, float zb, int r, int v, int b, int a) {
  // on va commencer par calculer la longueur du segment, c'est toujours agréable une petite longueur de segment
  float l=sqrt(sqr(xb-xa)+sqr(yb-ya)+sqr(zb-za));
  // ensuite on va dire qu'on fait des tronçons de 
  float tt=0.1;
  // combien y a t'il de tronçons de tt dans l ?
  float nt=l/tt;
  // il y en a nt
  // et donc l'incx=
  float incx=(xb-xa)/nt;
  // de même
  float incy=(yb-ya)/nt;
  // et
  float incz=(zb-za)/nt;
  // donc là on va parcourir tous les points-1 correspondant au début de chaque tronçon 
  float xencours=xa;
  float yencours=ya;
  float zencours=za;
  float rpos1[3];
  float rpos2[3];
  float random_rayon=0.02;

  //glLineWidth(2);
  for (int i=0;i<nt-1;i++) {

    // pour chaquepoint et l'autre extremité du segment on va 
    calcul_un_point_random_sur_une_sphere(xencours,yencours,zencours,random_rayon*myrand(),rpos1);
    calcul_un_point_random_sur_une_sphere(xencours+incx,yencours+incy,zencours+incz,random_rayon*myrand(),rpos2);
	
    glBegin(GL_LINES);
    glColor4ub(r,v,b,a);
    glVertex3f(rpos1[0],rpos1[1],rpos1[2]);
    glVertex3f(rpos2[0],rpos2[1],rpos2[2]);
    glEnd();
	
		
    xencours+=incx;
    yencours+=incy;
    zencours+=incz;
  }
}
int servos_vals_max[12];
int read_valeurs(void) {
  FILE *fichier = NULL;
  char s[1024];
  fichier = fopen("/home/pi/prg/colormusic/valeurs_servo_max.txt","r+");
  fgets(s, 1024, fichier );
  char ch[10];
  int ivals=0;
  int ich=0;  
  printf("Valeurs des servos %s : \n",s);
  for (int i=0; i<strlen(s); i++) {    
    if (s[i]==' ') {      
      ch[ich]='\0';      
      int val = atoi(ch);      
      servos_vals_max[ivals]=val;      
      ich=0;      
      ivals=ivals+1;      
    } else {      
      ch[ich]=s[i];
      ich=ich+1;   
    }    
  }
  
  for (int i=0; i<12; i++) {    
    printf("%d\n", servos_vals_max[i]);    
  }
  
  return 0;
  
}
// renvoie de 0 à 11 dans le désordre, pour fixer des valeurs de quantité de déplacement pour les petits moteurs

void randomize_twelve() {  
  int r;  
  for (int i=0; i<12; i++) { // je fais l'opération pour chaque note    
    if (i==0) randomized_twelve[i]=rand() % 12; // si c'est la première, je mets d'office le premier random    
    else { // sinon      
    loop:      
      r = rand() % 12 ; // je tire un nombre au hasard
      for (int j=i-1; j>=0; j--) { // et je regarde si il a déjà été tiré
	if (r==randomized_twelve[j]) { // si il a déjà été tiré
	  goto loop; // je loop
	}
      }
      randomized_twelve[i]=r;      
    }    
  }  
}

int netfunctions=0;
int test_if_netfunctions() {  
  FILE *f;  
  int ret=0;  
  if ((f=fopen("/home/pi/prg/colormusic/netfunctions","r"))!=NULL) {    
    if (netfunctions == 0) {      
      netfunctions=1;      
      fprintf(stdout,"Net functions activated.\n");      
      ret=1;      
    }    
    fclose(f);    
  } else {    
    if (netfunctions == 1) {      
      netfunctions=0;      
      fprintf(stdout,"Net functions desactivated.\n");      
      ret=1;    
    }    
  }
  return ret;
}

int lmmode=0;

int test_if_lmmode() {  
  FILE *f;  
  int ret=0;
  
  if ((f=fopen("/tmp/lmmode","r"))!=NULL) {    
    if (lmmode == 0) {      
      lmmode=1;      
      fprintf(stdout,"Lmmode activated.\n");      
      ret=1;      
    }    
    fclose(f);    
  } else {   
    if (lmmode == 1) {      
      lmmode=0;      
      fprintf(stdout,"Lmmode desactivated.\n");      
      ret=1;      
    }    
  }  
  for (int i=0;i<12;i++) {
    note_nb[i]=0;
  }  
  for (int i=0;i<24+30;i++) {
    setPixelColor(i,0,0,0);
  }
  
  return ret;
}

int oglfull=1;

int test_if_oglfull() {  
  FILE *f;  
  int ret=0;
  
  if ((f=fopen("/home/pi/prg/colormusic/oglfull","r"))!=NULL) {    
    oglfull=1;      
    fprintf(stdout,"Oglfull activated.\n");      
    ret=1;        
    fclose(f);    
  } else {
    oglfull=0;      
    fprintf(stdout,"Oglfull desactivated.\n");      
    ret=1;      
  }
  
  if (oglfull) {
    
    
    
    SDL_HideWindow(gWindow);
    
  } else {
    

    
    SDL_ShowWindow(gWindow);
    
  }
  
  if (!debug)
    
    system("/home/pi/prg/colormusic/focusreglage");
    
  return ret;

}

int imgwinfull=0;

// i dans reglage pour désactiver l'afficheur 3D  
int test_if_imgwinfull() {  
  FILE *f;  
  int ret=0; 
  if ((f=fopen("/tmp/imgwinfull","r"))!=NULL) {    
    if (imgwinfull == 0) {      
      imgwinfull=1;      
      fprintf(stdout,"Imgwinfull activated.\n");      
      ret=1;      
    }    
    fclose(f);    
  } else {    
    if (imgwinfull == 1) {      
      imgwinfull=0;      
      fprintf(stdout,"Imgwinfull desactivated.\n");      
      ret=1;      
    }    
  }
  
  if (imgwinfull) {    
    //SDL_SetWindowFullscreen(glwin,SDL_WINDOW_FULLSCREEN_DESKTOP);    
    SDL_HideWindow(glwin);   
  } else {    
    //SDL_SetWindowFullscreen(glwin,0);    
    SDL_ShowWindow(glwin);    
  }
  
  if (!debug) system("/home/pi/prg/colormusic/focusreglage");
  
  return ret;

}
// mode "flottant" 
int test_if_randompos() {  
  FILE *f;  
  int ret=0;
  
  if ((f=fopen("/tmp/randompos","r"))!=NULL) {    
    if (randompos == 0) {      
      randompos=1;      
      fprintf(stdout,"Randompos activated.\n");      
      ret=1;      
    }    
    fclose(f);    
  } else {    
    if (randompos == 1) {      
      randompos=0;      
      fprintf(stdout,"Randompos desactivated.\n");      
      ret=1;      
    }    
  }
  
  if (!randompos) 
    for (int i=0;i<12;i++) {      
      randomized_pos_de_note[i]=i;      
    }
  
  return ret;
}

void sig_handler(int signo) {  
  FILE *f;
  char s[10];
  
  
  if (signo == SIGINT) {    
    printf("received SIGINT\n");    
    //system("/usr/bin/sudo /usr/bin/killall -9 pythonthon");    
    system("rm /home/pi/prg/colormusic/nesestpasarretecorrectement");    
    pthread_cancel(gl_thread);    
    pthread_cancel(keyboard_thread);
    close(fd);   
    close_tube();

    exit(0);

    
    if (XXX) {
      printf("désinit d'opengl\n"); 
      for (int i=1;i<13;i++) {	
	if (newTexture[i]!=NULL) SDL_DestroyTexture( newTexture[i] );	
      }
      printf("on a détruit les textures\n");
      if (glwin != NULL) SDL_DestroyWindow(glwin);
      printf("on a détruit glwin\n");
      SDL_DestroyWindow(gWindow);    
      printf("on a détuit glWindow\n");
      SDL_Quit();
      printf("on vient de quitter SDL.\n");
    }
    exit(0); 
  }

  if (signo == SIGHUP) {
    
    printf("received SIGHUP\n");
    
    if (test_if_lmmode()) {
      
    } else if (test_if_netfunctions()) {
      
    } else if (test_if_imgwinfull()) {
      
    } else if (test_if_oglfull()) {
      
    } else if (test_if_randompos()) {
      
    } else if ((f=fopen("/tmp/clear","r"))!=NULL) {
      
      fclose(f);
      
      for (int i=0;i<12;i++) {
	
	note_nb[i]=0;
	
      }
      
      for (int i=0;i<24+30;i++) {
	
	setPixelColor(i,0,0,0);
	
      }
      
      system("/usr/bin/sudo rm /tmp/clear");
								
    } else if ((f=fopen("/tmp/chgparametres","r"))!=NULL) {
      fclose(f);
      change_parametres();
      system("/usr/bin/sudo rm /tmp/chgparametres");
      
    } else if ((f=fopen("/tmp/partchange","r"))!=NULL) {
      
      fclose(f);
      
      change_part();
      
      system("/usr/bin/sudo rm /tmp/partchange");
    } else if ((f=fopen("/tmp/switchautochange","r"))!=NULL) {
		
      fclose(f);
      auto_change=!auto_change;	
								
      system("/usr/bin/sudo rm /tmp/switchautochange");
    } else if ((f=fopen("/home/pi/prg/colormusic/switchwordsdisplay","r"))!=NULL) {
		
      fclose(f);
      wordsdisplay=!wordsdisplay;	

      //system("/usr/bin/sudo rm /tmp/switchwordsdisplay");
    } else if ((f=fopen("/tmp/exitandrerun","r"))!=NULL) {
		
      fclose(f);
									
								
      system("/usr/bin/sudo rm /tmp/exitandrerun");

      exit(0);
    } else if ((f=fopen("/tmp/chgnumdir","r"))!=NULL) {

      fgets( s, 5, f );
      
      numdir=atoi(s);
      
      write_numdir();
      
      if (XXX) load_png(numdir);
      
      fprintf(stderr,"les images sont lues dans i%d\n",numdir);
      
      fclose(f);
      
      system("/usr/bin/sudo rm /tmp/chgnumdir");
      
    } else {

      read_valeurs(); // relecture des valeurs des servos activés
      
    }
    
  }
  
  if (signo == SIGUSR1) {
    	
    printf("received SIGUSR1\n");
    
    randomize_twelve();
    
  }
  
  if (signo == SIGUSR2) {
    
    fprintf(stderr,"received SIGUSR2\n");
    
    if ((XXX==0)) {
      
      if (XOpenDisplay(":0")!=NULL) {
	
	fprintf(stderr,"XXX==0 et y a un display\n");

	if (initsdl()) { //read_numdir et load_png y sont
	  // bookUSR2
	  								
	  test_if_oglfull();
	  fprintf(stderr,"initsdled\n");
      
	  XXX=1;
	  
	} else {
	  
	  fprintf(stderr,"err\n");
	  
	}
	
      } else {
	
	fprintf(stderr,"XXX==0 mais y a pas de display on ne fait rien\n");
	
      }
      
    } else {
      
      fprintf(stderr,"xxx était déja chargé on incrémente numdir\n");
      
      read_numdir();
      
      fprintf(stderr,"numdir read\n");
      
      numdir=numdir+1;
      
      if (numdir>9) numdir=1;
      
      write_numdir();
      
      fprintf(stderr,"numdir written\n");
      
      load_png(numdir);
      
      fprintf(stderr,"jpg_loaded\n");
      
    }
    
  }
  
}

#define TOTAL_PINS 12
#define THRUPORTCLIENT 14
#define THRUPORTPORT 0

void midi_open(void) {
  snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0);
  snd_seq_set_client_name(seq_handle, "synesthezyx");
  in_port = snd_seq_create_simple_port(seq_handle, "listen:in",
				       SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
				       SND_SEQ_PORT_TYPE_APPLICATION);
  if( snd_seq_connect_from(seq_handle, in_port, THRUPORTCLIENT, THRUPORTPORT) == -1) {
    perror("Can't connect to thru port");
    exit(-1);
  } 
}

// la fonction qui lit le dernier évènement midi
snd_seq_event_t *midi_read(void) {
  snd_seq_event_t *ev = NULL;
  snd_seq_event_input(seq_handle, &ev);
  return ev;
}

//Currently playing note, by pin
int pinNotes[TOTAL_PINS];

//Currently playing channel, by pin
int pinChannels[TOTAL_PINS];

//Enabled channels
int playChannels[16];

void clearPinNotes() {
  
  int i;
  
  for(i=0; i< TOTAL_PINS; i++) {
    pinNotes[i] = -1;
  }
}

int maxi(int v[12]) {
  int index=0;
  for (int i=0;i<12;i++) {
    if (v[i]>v[index]) {
      index=i;
    }
  }
  return index;
}


int val_min=992*4+128;


int vecr[12]={0,0,0,0,0,0,0,0,0,0};
int vecv[12]={0,0,0,0,0,0,0,0,0,0};
int vecb[12]={0,0,0,0,0,0,0,0,0,0};

int ofondamentale=0;
int note2freq[12]={16915,2227,38058,5011,660,11276,1485,25372,3341,440,7517,990};
int init_freq() {
  float racinedouziemededeux;
  racinedouziemededeux=pow(2.0,(1.0/12.0));
  note2freq[0]=440;
  note2freq[1]=note2freq[0]*racinedouziemededeux;
  note2freq[2]=note2freq[1]*racinedouziemededeux;
  note2freq[3]=note2freq[2]*racinedouziemededeux;
  note2freq[4]=note2freq[3]*racinedouziemededeux;
  note2freq[5]=note2freq[4]*racinedouziemededeux;
  note2freq[6]=note2freq[5]*racinedouziemededeux;
  note2freq[7]=note2freq[6]*racinedouziemededeux;
  note2freq[8]=note2freq[7]*racinedouziemededeux;
  note2freq[9]=note2freq[8]*racinedouziemededeux;
  note2freq[10]=note2freq[9]*racinedouziemededeux;
  note2freq[11]=note2freq[10]*racinedouziemededeux;

}
int myDigitalWrite(int note, int val) {
  if (val!=0) {
    char s3001[3001];
    //	play_frequency(note2freq(note));
    sprintf(s3001,"/home/pi/prg/colormusic/signal %d | aplay -f cd\n",note2freq[note]);
    //fprintf(stderr,s3001);

    //system(s3001);
	//bookk
  }
  
  
  
  int fondamentale=maxi(note_nb);

  if (lmmode && fondamentale!=ofondamentale) {
    
    //fprintf(stdout,"Changement de fondamentale : %d \n",fondamentale);
    
    for (int i=0;i<12;i++) {

      setPixelColor(i,0,0,0);
      setPixelColor(i+12,0,0,0);
      setPixelColor(2*i,0,0,0);
      setPixelColor(2*i+1,0,0,0);
      setPixelColor(2*i+24,0,0,0);
      setPixelColor(2*i+24+1,0,0,0);
      onote_on_off[i]=0;
      
    }
    
    ofondamentale=fondamentale;
    
  }
  
  {
    
    ofondamentale=fondamentale;
    
    double k=val / 255.0;
    
    setPixelColor(2*note,
		  
		  (int)(round(k*composantes[note].r)),
		  (int)(round(k*composantes[note].v)),
		  (int)(round(k*composantes[note].b)));
    
    setPixelColor(2*note+1,
		  
		  (int)(round(k*composantes[note].r)),
		  (int)(round(k*composantes[note].v)),
		  (int)(round(k*composantes[note].b)));

    if (randompos) {
      
      if (randomized_pos_de_note[note]==-1) {
	
	int found=0;
	
	int r;
	
	while (!found) {
	  
	  r = rand() % 12;
	  
	  int deja_utilise = 0;
	  
	  for (int i=0;i<12;i++) {
	    
	    if (randomized_pos_de_note[i]==r) {
	      
	      deja_utilise = 1;
	      
	    }
	    
	  }
	  
	  if (!deja_utilise) found=1;
	  
	}
	
	randomized_pos_de_note[note]=r;
	
      }
      
    }
    
    setPixelColor(24+2*randomized_pos_de_note[note],
		  
		  (int)(round(k*composantes[note].r)),
		  (int)(round(k*composantes[note].v)),
		  (int)(round(k*composantes[note].b)));
    
    setPixelColor(24+2*randomized_pos_de_note[note]+1,
		  
		  (int)(round(k*composantes[note].r)),
		  (int)(round(k*composantes[note].v)),
		  (int)(round(k*composantes[note].b)));
    
    if ((val == 0) && (randompos))
      
      randomized_pos_de_note[note] = -1;
    
    //printf("note_nb : \n");
    
    for (int i=0;i<12;i++) {
      
      //printf("%d ", note_nb[i]);
      
    }
    
    //printf("\n");
    
    
    //printf("rang fondamentale %d, note %d (soit %s)\n", fondamentale, fondamentale + 1, note_name(fondamentale));
    
    float k_petite_intensite=0.002*10;
        
    //printf("    note_on_off "); for (int i=0;i<12;i++) printf("%d ", note_on_off[i] ); printf("\n");
    
    //printf("old_note_on_off "); for (int i=0;i<12;i++) printf("%d ", onote_on_off[i] ); printf("\n");
    
    if (lmmode) {
      
      for (int i=0;i<12;i++) {
	
	if ( (note_on_off[i]==0) && (onote_on_off[i]==1) ) {
	  
	  setPixelColor(2*i,
			
			(int)(round(k_petite_intensite*composantes[fondamentale].r)),
			(int)(round(k_petite_intensite*composantes[fondamentale].v)),
			(int)(round(k_petite_intensite*composantes[fondamentale].b))
			);
	}
	
      }
      
    }
    
  }
  
 la:
  
  if (haptique) {

    note = randomized_twelve[note];

    if (val==0) {
      
      maestroSetTarget(fd, note, val_min);
      
    } else {
      
      int v = (int)(100.0 * (float)(val) / 128.0);
      
      if (v>=100) {v=100;}
      
      int servo_val=(int)(val_min + 0.01*v * (servos_vals_max[note] - val_min));
      
      printf("v : %d\n",v);
      
      printf("servo %d : %d avec val : %d\n", note, servos_vals_max[note], servo_val);
      
      maestroSetTarget(fd, note, servo_val);
      
      /*
	if (note == 6) val_max=6000;
	if (note == 5) val_max=6000;
	if (note == 7) val_max=5500;
	if (note == 1) val_max=6400;
	if (note == 2) val_max=6900;
	if (note == 10) val_max=6000;
	if (note == 8) val_max=6000;
	maestroSetTarget(fd, note, val_max);
      */
      
    }
    
  }
  
  
  if ((XXX)) {
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear( gRenderer );

    int alphas[12];
    int intensitemax=0;
    //recherche de l'intensité max
    for (int i=0;i<12;i++) {
      if (notes_val_dans_l_octave[i]>intensitemax)
	intensitemax=notes_val_dans_l_octave[i];
    }
    int nb_couches=0;
    for (int i=0;i<12;i++) {
      if (note_on_off[i])
	nb_couches=nb_couches+1;
    }

    if (nb_couches>0) {
      // on va commencer par trier ces couches
      int i=0;
      int ptr[12]={0,1,2,3,4,5,6,7,8,9,10,11};
      int echange;
      do {
	i=0;
	echange=0;
	do {
	  if (notes_val_dans_l_octave[ptr[i]] < notes_val_dans_l_octave[ptr[i+1]]) {
	    int aux=ptr[i];
	    ptr[i]=ptr[i+1];
	    ptr[i+1]=aux;
	    echange=1;
	  }
	  i=i+1;
	} while ((i!=11) && (echange==0));
      } while (echange==1);
      //on normalise pour que la couche avec le val max soit avec un alpha de 255 et que les autres aient des alphas proportionnels
      for (int i=0;i<12;i++) {
	alphas[i]=(int)(255*((float)(notes_val_dans_l_octave[i]))/((float)(intensitemax)) /*/nb_couches*/ );
      }/*
	 fprintf(stderr,"alphas : ");
	 for (int i=0;i<12;i++) {
	 fprintf(stderr,"%d ",alphas[i]);
	 }
	 fprintf(stderr,"\n");
       */
      // c'est une merveilleuse petite machine, tout est sauvé, 
      //c 'est un terrain de jeu formidable je vais créer un
      // triangle, juste un petit triangle
      for (int i=0;i<12;i++) {
	alphas[ptr[i]]=alphas[ptr[i]] / pow(2,i+1-1);
      }
      //int a=255/nb_couches;
      for (int i=0;i<12;i++) {
	if ((note_on_off[ptr[i]])) {
	  SDL_SetTextureAlphaMod( newTexture[ptr[i]+1], alphas[ptr[i]] );
	  renderTexture(newTexture[ptr[i]+1], 0, 0, NULL );
	}
      }
    }
    //Update screen
    SDL_RenderPresent( gRenderer );
  }
}

void clearPinChannels() {
  int i;
  for(i=0; i< TOTAL_PINS; i++) {
    pinChannels[i] = INT_MAX;
  }
}

void clearPinsState() {
  
  clearPinNotes();
  clearPinChannels();
  
}

void pinsOn() {
  int i;
  for(i=0; i< TOTAL_PINS; i++) {
    myDigitalWrite(i, 255);
  }
}

void pinsOff() {
  int i;
  for(i=0; i< TOTAL_PINS; i++) {
    myDigitalWrite(i, 0);
  }
}


void setChannelInstrument(int channel, int instr) {
  printf("setting channel %i to instrument %i\n", channel, instr);
  playChannels[channel] = instr;
}


int isPercussion(int instrVal) {
  return instrVal >= 8 && instrVal <= 15;
}

int isPercussionChannel(int channel) {
  int instr = playChannels[channel];
  return isPercussion(instr);
}




int pinMapping2BCM(int n) { // correspond à un gpio2bcm
  switch (n) {
  case 0:
    return(17);
    break;
  case 1:
    return(18);
    break;
  case 2:
    return(27);
    break;
  case 3:
    return(22);
    break;
  case 4:
    return(23);
    break;
  case 5:
    return(24);
    break;
  case 6:
    return(25);
    break;
  case 7:
    return(4);
    break;
  case 21:
    return(5);
    break;
  case 22:
    return(6);
    break;
  case 23:
    return(13);
    break;
  case 24:
    return(19);
    break;
  case 25:
    return(26);
    break;
  case 26:
    return(12);
    break;
  case 27:
    return(16);
    break;
  case 28:
    return(20);
    break;
  case 29:
    return(21);
    break;
  default:
    return(-1);
  }
}

int BCM2GPIO(int bcm) {
  switch (bcm) {
  case 17:
    return(0);
  case 4:
    return(7);
    break;
  case 5:
    return(21);
    break;
  case 6:
    return(22);
    break;
  case 21:
    return(29);
    break;
  case 22:
    return(3);
    break;
  case 23:
    return(4);
    break;
  case 24:
    return(5);
    break;
  case 25:
    return(6);
    break;
  case 26:
    return(25);
    break;
  case 27:
    return(2);
    break;
  default:
    return(-1);
  }  
}
char *note_name(int val) {
  val = val % 12;
  switch (val) {
  case 0:
    return("do");
    break;
  case 1:
    return("do#");
    break;
  case 2:
    return("re");
    break;
  case 3:
    return("re#");
    break;
  case 4:
    return("mi");
    break;
  case 5:
    return("fa");
    break;
  case 6:
    return("fa#");
    break;
  case 7:
    return("sol");
    break;
  case 8:
    return("sol#");
    break;
  case 9:
    return("la");
    break;
  case 10:
    return("la#");
    break;
  case 11:
    return("si");
    break;
  default:
    return NULL;
  }
  return NULL;
}

void aff_string(char *s) {
  //  char ss[128];
  //  sprintf(ss,"/home/pi/prg/aff_oled/examples/aff_string %s",s);
  //system(ss);
 
}

int choosePinIdx(int note, int channel) {
  int dbg=0; 
  //Return the note modulated by the number of melody pins
  int val = note  % (TOTAL_PINS );
  //printf("total_pins : %d\n",TOTAL_PINS);
  if (dbg) printf("note : %s\n",note_name(val));
  
  //printf("val : %d\n",val);
  aff_string(note_name(val));
  //printf("WPi : %d\n",pinMapping[val]);
  //printf("physical : %d\n",wPi2Physical[pinMapping[val]]);  
  //printf("bcm : %d\n",pinMapping2BCM(pinMapping[val]));
  //printf("gpio : %d\n",BCM2GPIO(pinMapping2BCM(pinMapping[val])));
  return val;
 
}

int allumage=1;
int config=0;

int note_a_config=-1;
int note_a_config_red=-1;
//int note_a_config_vert=-1;
int note_a_config_bleu=-1;

void midi_process(snd_seq_event_t *ev)
{
  int intensity = 0;
  if( ev->type == SND_SEQ_EVENT_PGMCHANGE )  {
    clearPinsState();
    setChannelInstrument(ev->data.control.channel, ev->data.control.value);
  }
  
  //Note on/off event
  else if ( ((ev->type == SND_SEQ_EVENT_NOTEON)||(ev->type == SND_SEQ_EVENT_NOTEOFF)) ) {
    int note;	
    if (dbg) printf("velocity : %d/127\n",ev->data.note.velocity);
    note=ev->data.note.note;

    
    
    if (dbg) printf("note : %d\n", note);
    int note_dans_l_octave = note % 12;

    if (dbg) printf("%d note dans l'octave\n",note_dans_l_octave);

    if (ev->type == SND_SEQ_EVENT_NOTEON) last_note_played_time=time(NULL);
    if (dpmsoff==1) {
      // system("/usr/bin/xset dpms force on");
      //system("/usr/bin/xset -dpms");
      dpmsoff=0;
    }
    gltourne=1;
    massage_board_has_been_reset=0;

    
    //choose the output pin based on the pitch of the note
    int pinIdx = choosePinIdx(ev->data.note.note, ev->data.note.channel);
    if (dbg) printf("pinIdx : %d\n", pinIdx);
    
    if(1 || !isPercussionChannel(ev->data.note.channel) ) { 
      int isOn = 1;
      //Note velocity == 0 means the same thing as a NOTEOFF type event
      if( ev->data.note.velocity == 0 || ev->type == SND_SEQ_EVENT_NOTEOFF) {
	isOn = 0;
      }


      if( isOn ) {
	aucune_note=0;
	change_dcompteur(note, 1); 
	change_dcompteurp(note, 1);

	nb_notes_since_last_change++;

	last_note_on = note_dans_l_octave;
	touche_avant_avant_la_precedente = touche_avant_la_precedente;
	touche_avant_la_precedente = touche_precedente;
	touche_precedente = touche_en_cours;
	touche_en_cours = note;
	notes_vals[note]=2*ev->data.note.velocity;
				
	tab_notes[nb_notes].time=mstime();
	if (dbg) printf("mstime() %ld\n",mstime());
	if (dbg) printf("numéro de la note : %d, time de la note : %ld\n", nb_notes, tab_notes[nb_notes].time);
	tab_notes[nb_notes].intensity=notes_vals[note];
	tab_notes[nb_notes].name=note_dans_l_octave;
	tab_notes[nb_notes].duree=-1;
	tab_notes[nb_notes].touche=touche_en_cours;
	notes_num[note]=nb_notes; // pour numéroter les notes dans l'ensemble de notes jouées
	
	if (dbg) printf("list_create\n");
	tab_notes_on[nb_notes]=list_create(nb_notes);
	if (nb_notes!=0) {
	  if (dbg) printf("first\n");
	  mailles *p=tab_notes_on[nb_notes-1]->first;
	  while (p!=NULL) {
	    if (dbg) printf("p->val : %d\n",p->val);
	    notes note=tab_notes[p->val];
	    if (dbg) printf("p->valed, note duree %d\n",note.duree);
	    if (note.duree==-1) {
	      // si la durée de la note est égale à -1, on met d'office 
	      list_add(tab_notes_on[nb_notes], p->val);
	    }
	    p=p->next;
	  }
	}
	
	nb_notes++;
	if (nb_notes>=nb_notes_max) {
	  if (dbg) printf("on est arrivé à note max\n");
	  for (int j=0; j<100; j++) {
	    if (dbg) printf("************\n");
	  }
	  // on va free des trucs
	  // on va free tab_notes_on
	  // alors tab_notes_on c'est un tableau de lists
	  // et lists c'est une liste chainée
	  // alors
	  for (int i=0;i<nb_notes_max;i++) {
		    
	    mailles *p=tab_notes_on[i]->first;
	    while (p!=NULL) {
	      mailles *next=p->next;
	      free(p);
	      p=next;
	    }
	    free(tab_notes_on[i]);
	  }
	  nb_notes = 0;
	  //exit(1);
	}
	
	for (int i=0; i<piano_max_keys ; i++) {
	  if (i % 12 == note_dans_l_octave) {
	    intensity = intensity + notes_vals[i];
	  }	  
	}

	notes_val_dans_l_octave[note_dans_l_octave]=intensity;
	newnotes_val[note_dans_l_octave]=intensity; // pour savoir si il faut produire un nouveau tétraedre et de quelle
	// couleur il est par exemple, je veux savoir pourquoi je le reset à chaque vbl

	// alt-alt-gr-# pour afficher les numéros de ligne
	// alt-s commutateur de défilement progressif ou brutal
	
	note_nb[note_dans_l_octave]=note_nb[note_dans_l_octave]+1;

	if (dbg) printf("note dans l'octave : %d\n", note_dans_l_octave);
	if (dbg) printf("quantité de cette note : %d\n", note_nb[note_dans_l_octave]);
	
	for (int i=0;i<12;i++) 
	  onote_on_off[i]=note_on_off[i]; // o, c'est pour old
	if (intensity>0) {
	  note_on_off[note_dans_l_octave]=1; // on maintient un tableau de l'état des notes 
	}
	

	myDigitalWrite(pinIdx, intensity); // le pinIdx correspond forcément au numéro de la note
	pinNotes[pinIdx] = ev->data.note.note; 
	pinChannels[pinIdx] =  ev->data.note.channel;
	   
      } else { //Pin is to be turned off if there's no more note of this name

	if (dbg) printf("note dans l'octave : %d\n",note_dans_l_octave);
	if (dbg) printf("quantité de cette note : %d\n",note_nb[note_dans_l_octave]);

	int old_vals = notes_vals[note];
	if (notes_num[note] != -1) { 
	  // notes_num[note] renvoie le numéro de la note, on peut 
	  // donc accéder à la note par une liste et un tableau                       
	  // autrement dit : si la note n'a pas été appuyée avant le lancement du programme
	  // alors on calcule la différence entre le temps actuel et le moment où la note
	  // a été jouée
	  int dureeduree=mstime() - tab_notes[notes_num[note]].time;
	  tab_notes[notes_num[note]].duree=
	    mstime() - tab_notes[notes_num[note]].time;
	  if (dbg) printf("durée à l'off : %ld\n", tab_notes[notes_num[note]].duree);
	  if (tab_notes[notes_num[note]].duree < -1) {
	    if (dbg) printf("houla : duree négative pour la note %d\n", notes_num[note]);
	    if (dbg) printf("mstime en cours : %d\n",mstime());
	    fprintf(stderr,"on sort\n");
	    exit(0);
	  }
	  notes_num[note]=-1; // on libère le notes_num qui est en fait un index de la note
	}
	
	notes_vals[note]=0;
	for (int i=0; i<piano_max_keys; i++) {
	  if ( i%12 == note_dans_l_octave) {
	    intensity = intensity + notes_vals[i]; // si on joue un accord ça augmente l'intensité lumineuse de la l.e.d.
	  }	  
	}
	
	notes_val_dans_l_octave[note_dans_l_octave]=intensity;
	newnotes_val[note_dans_l_octave]=intensity;
	for (int i=0;i<12;i++) 
	  onote_on_off[i]=note_on_off[i];

	if (intensity>0) note_on_off[note_dans_l_octave]=1;
	else {
	  change_dcompteur(note, 0);
	  note_on_off[note_dans_l_octave]=0;
	  last_note_off = note_dans_l_octave;
	}
	aucune_note=1;
	for (int i=0;i<12;i++) {
	  if (note_on_off[i]) {
	    aucune_note=0;
	    break;
	  }
	}
	change_dcompteurp(note,0);	
	myDigitalWrite(pinIdx, intensity); 

	
	
      }
      
    } else {
      printf("Unhandled event %2d\n", ev->type);
    }
    if (!midi_simulation) {
      snd_seq_free_event(ev);
    }
  }
}

void simulate_midi_event() {
  haptique = 0;
  snd_seq_event_t *ev=(snd_seq_event_t *)malloc(sizeof(snd_seq_event_t));

  //ev->data.note = (snd_seq_ev_note_t*)malloc(sizeof(snd_seq_ev_note_t));
  ev->data.note.note = rand() % 12;
  if (note_on_off[ev->data.note.note]) {
    ev->type = SND_SEQ_EVENT_NOTEOFF;
  } else {
    ev->type = SND_SEQ_EVENT_NOTEON;
  }
  ev->data.note.velocity = rand() % 255; // où l'on apprend que la velocité de la note max est de 255
  ev->data.note.channel = 0;
  midi_process(ev);
  //free(ev->data.note);  
  free(ev);
  sleep(midi_simulation_sleep_time);
}

int run=1;
void stop(int signum)
{
  run = 0;
}




int nbPixels;
pthread_t resetting_masseuse_timer;
int interval = 60*3;
void masseuse_reseter_installer() {

  pthread_create(&resetting_masseuse_timer,NULL, do_something_periodically,&interval);
  
}
SDL_GLContext contexteOpenGL;

void *keyboard_animate(void *ptr) {
  /*	while (1) {
	printf("fdsfdslkdlkfjsd\n");
	printf("%c\n",getchar());
	}
  */
}

// initialize sdl, opengl et lance les threads d'animations graphiques et de lecture clavier
int initsdl() { //et opengl
  
  int success=1;
  
  fprintf(stderr,"initsdl()\n");
  
  system("/home/pi/prg/colormusic/putDimXinDimX");
  readdimX();
  
  system("/home/pi/prg/colormusic/putDimYinDimY");
  readdimY();
  
  //Initialize SDL
  
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

    fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
      
  } else {
    
    //Set texture filtering to linear
    
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
      fprintf(stderr, "Warning: Linear texturering not enabled!" );
    }

    //Create window
    
    gWindow = SDL_CreateWindow("-",
			       dimX/2 - 320 /*dimX - 640*//*SDL_WINDOWPOS_UNDEFINED*/,
			       dimY/2 - 240 /*dimY - 480*//* SDL_WINDOWPOS_UNDEFINED*/,
			       SCREEN_WIDTH,
			       SCREEN_HEIGHT,
			       SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN );
    
    if (OGL) {//OpenGL
      
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
      
      glwin = SDL_CreateWindow("o",
			       0,
			       0,
			       dimX/*SCREEN_WIDTH*/,
			       dimY/*SCREEN_HEIGHT*/,
			       SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
      
      if (glwin == NULL) {
	
	fprintf(stderr, "glwin could not be created! SDL Error : %s\n", SDL_GetError() );
	success = false;
      }
      SDL_SetWindowPosition(gWindow, dimX/2 - 320, dimY/2 - 240);		  
      
      //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
      contexteOpenGL =  SDL_GL_CreateContext(glwin);
      if( contexteOpenGL == NULL )
	{
	  printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
	  success = false;
	}
      
      glutInit( &gargc, gargv );
      
      if( SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
	  printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
	}
      
    }
    
    if( gWindow == NULL )
      {
	fprintf(stderr, "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	success = false;
      }
    
    else
      
      {
	//Create renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC );
	if( gRenderer == NULL ) {
	  fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	  success = false;
	} else {
	  //Initialize renderer color
	  SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	  
	  //Initialize JPG loading
	  int imgFlags = IMG_INIT_JPG;
	  if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
	    fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	    success = false;
	  }
	}
      }
  }
  
  if (!success) return 0;
  
  read_numdir();
  load_png(numdir);
  
  canvas = (unsigned char*)malloc(512*4*512*sizeof(unsigned char));
  

  


    
  if (!debug)
    system("/home/pi/prg/colormusic/focusreglage");

  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  
  SDL_GL_MakeCurrent(glwin, contexteOpenGL);
  
  // Permet de fixer la taille et la position de l'image sur la fenêtre d'affichage.
  printf("dimX:%d dimY:%d\n",dimX,dimY);
  glViewport(0,0,dimX /*1920*//*640*/,dimY /*1080*//*480*/);

  //	Permet de fixer les caractéristiques optiques de la caméra de visualisation (type de projection, ouverture, ...).
  glMatrixMode(GL_PROJECTION);            // 2
  glLoadIdentity();                       // 2
  //glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);  // 2
  gluPerspective(60,(float)dimX/dimY,0.01f,100.0f); // pour que les angles droits aient l'air droits à l'écran !

  int error;
  
  //Check for error
  error = glGetError();
  
  if( error != GL_NO_ERROR )
    {
      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
    
    }
	
  const char*message1 = "Thread 1";
	
  pthread_create(&gl_thread,NULL,gl_animate, (void *)message1);
  pthread_create(&keyboard_thread,NULL,keyboard_animate, NULL);
  return 1;

}

//passage par adresse
vector<int> decomposerEnNombresPremiers(int n, const vector<int>& premiers) {
  vector<int> facteurs;
	    
  for (int i = 0; i < premiers.size(); ++i) {
    while (n % premiers[i] == 0) {
      facteurs.push_back(premiers[i]);
      n /= premiers[i];
    }
													        
    if (n == 1)
      break;
  }
																					    
  return facteurs;
}
/*
  Fonction genererCombinations(result, current, n, r, index):
  Si la taille de current est égale à r:
  Ajouter current à result
  Retourner
  Fin Si
						    
  Pour i allant de index à n:
  Ajouter i à current
  Appeler genererCombinations(result, current, n, r, i)
  Retirer le dernier élément de current
  Fin Pour

  Fonction principale:
  Lire n depuis l'entrée standard
  Lire r depuis l'entrée standard
																	    
  result = liste de listes d'entiers
  current = liste d'entiers
																		    
  Appeler genererCombinations(result, current, n, r, 1)
																						    
  Pour chaque combination dans result:
  Pour chaque num dans combination:
  Afficher num suivi d'un espace
  Fin Pour
  Afficher une nouvelle ligne
  Fin Pour
  Fin Fonction
*/
// Fonction pour générer les combinaisons avec remise
// ici le & indique que result est passé par référence autrement dit result est un alias
// de la variable qui sera passé en parametre, un alias, un synonyme.
void generateCombinations(vector<vector<int>>& result, vector<int>& current, int n, int r, int index) {
  if (current.size() == r) {
    result.push_back(current);
    return;
  }

  for (int i = index; i <= n; ++i) {
    current.push_back(i);
    generateCombinations(result, current, n, r, i); // Utilise récursivité pour ajouter les éléments suivants
    current.pop_back();
  }
}	
// retourne -1 si la sequence n'est pas périodique
// la sequence ne doit pas faire plus de 1024 notes
int periodiqueur_initialized=0;
vector<int> periodiqueur_premiers;
int cherche_et_retourne_la_plus_petite_periode_dans_sequence_si_presente(int *sequence, int taille_sequence) {
  if (!periodiqueur_initialized) {
    periodiqueur_premiers=cribleEratosthene(1024);
    periodiqueur_initialized=1;
  }
  vector<int> periodes;
	
  vector<int> facteurs_premiers = decomposerEnNombresPremiers(taille_sequence, periodiqueur_premiers);
  facteurs_premiers.insert(facteurs_premiers.begin(),1);
  vector<vector<int>> tirages;
  vector<int> currentCombination;
		
  generateCombinations(tirages, currentCombination, facteurs_premiers.size(), facteurs_premiers.size(), 1);
  for (const vector<int>& tirage : tirages) { // le const indique que le vector n'est pas modifiable à travers la bouche
    int produit=1;
    for (int num:tirage) {
      produit = produit * facteurs_premiers[num-1];
    }
    // tester si ce produit est une période de la séquence autrement dit :
    int est_une_periode=1;
    for (int i=0;i<taille_sequence;i++) {
      if (sequence[i]!=sequence[(i+produit) % taille_sequence]) {
	est_une_periode = 0;
	break;
      }
    }
    if (est_une_periode) {
      periodes.push_back(produit);
    }
  }
  if (periodes.size() != 0) {
    int plus_petite_periode=1024;
    int periode;
    for (int periode : periodes ) {
      if (periode<plus_petite_periode) 
	plus_petite_periode=periode;
    }
    if (plus_petite_periode!=taille_sequence)
      return plus_petite_periode;
    else return -1;
  } else {
    return -1;
  }
}


// on a passé cette zone un peu douloureuse à appréhender, on peut maintenant
// y retourner si on le souhaite ou continuer jusque l'arbre

int test_periodiqueur() {
  char s[1024];
  cout << "Entrer la chaine : ";
  cin >> s;
  int seq[1024];
  for (int i=0;i<strlen(s);i++) {
    seq[i]=(int)s[i];
  } 
  int periode=cherche_et_retourne_la_plus_petite_periode_dans_sequence_si_presente(seq,strlen(s));
  if (periode!=-1) {
    cout << periode << endl;
  } else {
    cout << "Apériodique";
  }
  return 0;
  int n; // Nombre total d'éléments
  int r; // Nombre d'éléments par combinaison
  cout << "Entrez le nombre total d'éléments (n) : ";
  cin >> n;
  cout << "Entrez le nombre d'éléments par combinaison (r) : ";
  cin >> r;
  vector<vector<int>> combinations;
  vector<int> currentCombination;
  generateCombinations(combinations, currentCombination, n, r, 1);
  // Affiche les combinaisons
  for (const vector<int>& combination : combinations) {
    for (int num : combination) {
      cout << num << " ";
    }
    cout << endl;
  }

  int nombre;
  cout << "Entrez un nombre : ";
  cin >> nombre;
																										    
  vector<int> premiers = cribleEratosthene(nombre);
  vector<int> facteurs = decomposerEnNombresPremiers(nombre, premiers);
																													    
  cout << "La décomposition de " << nombre << " en facteurs premiers est : ";
  for (int facteur : facteurs) {
    cout << facteur << " ";
  }
  cout << endl;
																																			    
  return 0;


}
int main(int argc, char **argv) {


  init_gammes();  
  gargc=argc;
  gargv=argv;
  printf("Nombre d'arguments : %d\n",argc);
  for (int i=0;i<argc;i++) {
    printf("argument : %s\n",argv[i]);
    if (strcmp(argv[i],"debug")==0) debug=1;
    if (strcmp(argv[i],"gltourne")==0) gltourne=1;
    if (strcmp(argv[i],"midi_simulation")==0) midi_simulation=1;
    if (strcmp(argv[i],"no_begin_lights")==0) no_begin_lights=1;
  }
  system("touch /home/pi/prg/colormusic/nesestpasarretecorrectement");
  srand(time(NULL));
  if (XOpenDisplay(":0")!=NULL) XXX=1;
  if (XXX) initsdl(); // initialise sdl et opengl et lance les threads d'animation graphique et de lecture du clavier d'ordi


  for (int i=0; i<piano_max_keys ; i++) {
    notes_vals[i]=0; // les valeurs d'intensité de chaque note du piano
  }
  // j'aime tellement me déplacer dans mon code, me déplacer de commandes en commandes pour enquêter sur leur fonctionnement
  // le tableau de structure de note dans lequel on a le nom de la note, sa durée, sa date de début, et son intensité	
  tab_notes = (notes*)malloc(sizeof(notes)*nb_notes_max); 



  for (int i=0;i<piano_max_keys;i++) {
    notes_num[i]=-1; 
    // un index qui permet de savoir quel note relacher quand 
    // elle est relaché donc c'est un index dans le tableau tab_notes
  }

  tab_notes_on = (lists**)malloc(sizeof(lists*)*nb_notes_max); // tableau d'une liste de toutes les notes on à un instant précis
  nb_notes=0;
  
  read_valeurs(); // relecture des valeurs des servos activés
  initMaestro();  
  for (int i=0;i<12; i++) maestroSetTarget(fd, i, val_min);
  printf("main\n");
  signal(SIGINT, sig_handler);
  signal(SIGHUP, sig_handler);
  signal(SIGUSR1, sig_handler);
  signal(SIGUSR2, sig_handler);
  system("/usr/bin/touch /home/pi/prg/colormusic/synesthezyxAEteLancedAuBoot"); 
  printf("ouverture des tubes\n");
  if (leds) {
	
    open_tubes();
    printf("tubes ouvert\n");
    write_tube("Bonjour\n");
    wait_tube();
    printf("write tube wait tube ok\n");
    write_tube("getNbPixels\n");
    char *s = read_tube();
    char *endptr;
    s[strlen(s)-1]='\0';
    nbPixels=strtol(s,&endptr,10);
    printf("nbPixels : %d\n",nbPixels);
    wait_tube(); // vide probablement le pipe au cas où de l'aute côté on enverrait des choses inutiles
  }

  printf("control C to stop.\n");
     
  printf("Input Alsa Ports\n");
  system("/usr/bin/aconnect -i");
  printf("Output Alsa Ports\n");
  system("/usr/bin/aconnect -o");
  system("/usr/bin/aconnect -d `cat /home/pi/prg/colormusic/img/midinum.txt` 128"); // 
  printf("Previous subscription between midi and synesthezyx disconnected\n");
   
  //Open a midi port, connect to thru port also
  midi_open();
 
  printf("Midi Opened\n");
  system("/usr/bin/aconnect `cat /home/pi/prg/colormusic/img/midinum.txt` 128"); 
  // à garder précieusement pour voir si ça fonctionne avec le miditech par exemple
  printf("New subscription between midi and synesthezyx done\n");
  
  clearPinsState(); // reset probablement l'état des pin gpio
  genere_composantes();
  FILE *f;
  if ((f=fopen("/home/pi/prg/colormusic/switchwordsdisplay","r"))!=NULL) {
    fclose(f);
    wordsdisplay=1;	
  }

  test_if_trenteseptTok();
  test_if_netfunctions();
  test_if_randompos();
  test_if_lmmode();
  test_if_oglfull();
  test_if_imgwinfull();
  masseuse_reseter_installer(); // probablement un workaround pour pas que les petits moteurs déconnent
  while(run) {
    
    if (midi_simulation) {
      simulate_midi_event();
    } else {
      midi_process(midi_read());
    }
  }


  return(0);
}

// probablement l'espèce de jeu de cartes

void cubar() {
  glEnable(GL_DEPTH_TEST);
  int c=0;
  int ii=0;
  for (int i=-12;i<12;i+=2) {
    glPushMatrix();

    glRotatef( 360.0*compteur[ii]/100, 1,0,0);
    glScalef(0.5,0.5,0.5);
    ii++;
    glBegin( GL_QUADS );
    {
      glColor3b(composantes[c].r / 2 ,composantes[c].v / 2,composantes[c].b / 2);
      int k=2;
      glVertex3f( -0.5f*k, -0.5f*k, i/10.0 );
      glVertex3f(  0.5f*k, -0.5f*k, i/10.0 );
      glVertex3f(  0.5f*k,  0.5f*k, i/10.0 );
      glVertex3f( -0.5f*k,  0.5f*k, i/10.0 );
    }
    glEnd();
    glPopMatrix();
    c=c+1;
  }
}

// le jeu de carte éclairé

void cubar2() {
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  float lightpos[4]={0,0,0,1};
  float lightambientcolor[4]={0,0,0,1};
  float lightdiffusecolor[4]={1,1,1,1};
  float lightspecularcolor[4]={1,1,1,1};
  glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
  //glLightfv(GL_LIGHT0,GL_AMBIENT,lightambientcolor);
  //glLightfv(GL_LIGHT0,GL_SPECULAR,lightspecularcolor);
  glEnable(GL_LIGHTING);
  //glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);  
  float materialspecularcolor[4]={1,1,1,1};
  float materialemissioncolor[4]={0,0,0,1};
  int c=0;
  int ii=0;
  for (int i=-12;i<12;i+=2) {
    glPushMatrix();

    glRotatef(0.5* 360.0*compteur[ii]/100, 1,0,0);
    glRotatef(0.5* 360.0*compteur[ii]/100, 0,1,0);
    glScalef(0.5,0.5,0.5);
    int kk=2*12+24;//la main gauche est souvent à 2 octaves du début du piano+24 la note la plus basse sur mon piano
    glScalef(1+1*2*compteurp[ii+kk]/100,1+1*2*compteurp[ii+kk]/100,1);// la main gauche scale
    glScalef(1/(1+compteurp[ii+kk+2*12]/100),1/(1+2*compteurp[ii+kk+2*12]/100),1);//la main droite descale

    glBegin( GL_QUADS );
    {
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,tabcomposantesa[ii]);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,tabcomposantesa[ii]);
      //glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,materialspecularcolor);
      //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,materialemissioncolor);
      int k=2;
      float A[3]={ -0.5f*k, -0.5f*k, i/10.0};
      float B[3]={ 0.5f*k, -0.5f*k, i/10.0 };
      float C[3]={ 0.5f*k,  0.5f*k, i/10.0 };
      float D[3]={-0.5f*k,  0.5f*k, i/10.0 };
      float AB[3]; vsub(B,A,AB);
      float AD[3]; vsub(D,A,AD);
      float nor[3]; pvecv(AB,AD,nor);
      normalize(nor);
			
      glNormal3fv(nor);
      glVertex3fv(A);
      glVertex3fv(B);
      glVertex3fv(C);
      glVertex3fv(D);
	
    }
    ii++;
    glEnd();
    glPopMatrix();
    c=c+1;
  }
  glDisable(GL_LIGHTING);
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
}


int angle = 0;
float rotx = 0;
float roty = 0;
float rotz = 0;
float rotxy = 0;
float rotxz = 0;
float rotyz = 0;
float rotxa = 0;
float rotya = 0;
float rotza = 0;
float rotxya = 0;
float rotxza = 0;
float rotyza = 0;

// un effet

void pcube(float x, float y, float z, float size) {
  float s2=size / 2;
	
  //	glMatrixMode(GL_MODELVIEW);
  //	glPushMatrix();
  //	glLoadIdentity();
  //gluLookAt(0,0,-3, 0,0,0, 0,1,0);
  glPointSize(5);
  glBegin(GL_POINTS);
  {
    glColor3ub(128,0,0);        //Rouge
    glVertex3f(x-s2,y-s2,z-s2);
    glColor3ub(0,128,0);        //Vert 
    glVertex3f(x-s2,y-s2,z+s2);
    glColor3ub(0,0,128);        //Bleu
    glVertex3f(x-s2,y+s2,z-s2);
    glColor3ub(0,128,128);      //Cyan
    glVertex3f(x-s2,y+s2,z+s2);
    glColor3ub(128,128,0);      //Jaune
    glVertex3f(x+s2,y-s2,z-s2);
    glColor3ub(128,0,128);      //Magenta
    glVertex3f(x+s2,y-s2,z+s2);
    glColor3ub(128,128,128);    //Blanc
    glVertex3f(x+s2,y+s2,z-s2);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2,z+s2);
  }
  glEnd();
  glPopMatrix();
  
}

float blanc[3]={1.0,1.0,1.0};
float rouge[3]={1.0,0,0};
float vert[3]={0,1.0,0};
float bleu[3]={0,0,1.0};
float jaune[3]={1.0,1.0,0};
float orange[3]={1.0,0.5,0};
float fushia[3]={1.0,0.0,0.5};
float mauve[3]={0.5,0.0,1.0};
float vert_d_eau[3]={0.0,1.0,0.5};
float citron_vert[3]={0.5,1.0,0.0};
float turquoise[3]= {0.0,0.5,1.0};  

// cube de couleurs ambiance phong avec faces déportées
void cube(float x, float y, float z, float size) {
  float s2=size / 2;
  float d=size / 10;

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);  
  glPushMatrix();
  glRotatef( 360.0*compteur[0]/100, 1,0,0);
  glRotatef(-360.0*compteur[1]/100, 1,0,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(-1,0,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,rouge);
    //droite
    glVertex3f(x-s2-d,y-s2,z-s2);
    glVertex3f(x-s2-d,y-s2,z+s2);
    glVertex3f(x-s2-d,y+s2,z+s2);
    glVertex3f(x-s2-d,y+s2,z-s2);
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[2]/100,  1,0,0);
  glRotatef(-360.0*compteur[3]/100,  1,0,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(1,0,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,vert);
    //gauche
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2+d,y-s2,z-s2);
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2+d,y+s2,z-s2);
    
    //glColor3ub(255,255,255);    //Blanc
    //glVertex3f(x+s2+d,y+s2,z-s2);
    //glColor3ub(0,0,0);          //Noir
    //glVertex3f(x+s2+d,y+s2,z+s2);
    
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2+d,y+s2,z+s2);
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2+d,y-s2,z+s2);

    //glColor3ub(255,0,255);      //Magenta
    //glVertex3f(x+s2+d,y-s2,z+s2);
    //glColor3ub(255,255,0);      //Jaune
    //glVertex3f(x+s2+d,y-s2,z-s2);
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[4]/100, 0,0,1);
  glRotatef(-360.0*compteur[5]/100, 0,0,1);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,0,1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,jaune);
    //back
    glVertex3f(x+s2,y+s2,z+s2+d);
    glVertex3f(x-s2,y+s2,z+s2+d);
    glVertex3f(x-s2,y-s2,z+s2+d);
    glVertex3f(x+s2,y-s2,z+s2+d);
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glRotatef( 360.0*compteur[6]/100, 0,0,1);
  glRotatef(-360.0*compteur[7]/100, 0,0,1);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,0,-1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,bleu);
    //front
    glVertex3f(x-s2,y+s2,z-s2-d);
    glVertex3f(x+s2,y+s2,z-s2-d);
    
    glVertex3f(x+s2,y-s2,z-s2-d);
    glVertex3f(x-s2,y-s2,z-s2-d);
    
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[8]/100, 0,1,0);
  glRotatef(-360.0*compteur[9]/100, 0,1,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,1,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,orange);
    //dessus
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2+d,z+s2);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2+d,z+s2);

    //glColor3ub(0,0,0);          //Noir
    //glVertex3f(x+s2,y+s2+d,z+s2);
    //glColor3ub(255,255,255);    //Blanc
    //glVertex3f(x+s2,y+s2+d,z-s2);

    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2+d,z-s2);
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2+d,z-s2);

    //glColor3ub(0,0,255);        //Bleu
    //glVertex3f(x-s2,y+s2+d,z-s2);
    //glColor3ub(0,255,255);      //Cyan
    //glVertex3f(x-s2,y+s2+d,z+s2);

    //C-SPC C-SPC
    //C-U C-CPC
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[10]/100.0,  0, 1,0);
  glRotatef(-360.0*compteur[11]/100.0,  0, 1,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,-1,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,fushia);
    //dessous
    glVertex3f(x-s2,y-s2-d,z-s2);
    glVertex3f(x+s2,y-s2-d,z-s2);
    glVertex3f(x+s2,y-s2-d,z+s2);
    glVertex3f(x-s2,y-s2-d,z+s2);


  }
  
  glEnd();
  glPopMatrix();
  glDisable(GL_LIGHTING);
  //M-% query-replace
  
}
// j'aimerais bien un cube déformable avec des coins homotéthisable depuis le centre des faces
// ce serait cool, ça me mettrait de bonne humeur, je pourrais penser à ma merveilleuse journée
// à la plage, ce serait cool. et puis pendant ce temps là, ils gazouillent sur internet
// 
// j'ai fait de l'assembleur et j'aime avoir une idée exacte de ce que fait chaque fonction que j'appelle
// et en fait glMaterielfv c'est un glcolor auquel on peut passer un tableau pour les parametres de couleur
// inside cube de couleurs ambiance phong avec faces déportées
void insidecube(float x, float y, float z, float size) {
  float s2=size / 2;
  float d=size / 10;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glScalef(1,1,1);
  glPushMatrix();
  glRotatef( 360.0*compteur[0]/100, 1,0,0);
  glRotatef(-360.0*compteur[1]/100, 1,0,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(1,0,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,rouge);
    //droite
    glVertex3f(x-s2-d,y-s2,z-s2);
    glVertex3f(x-s2-d,y-s2,z+s2);
    glVertex3f(x-s2-d,y+s2,z+s2);
    glVertex3f(x-s2-d,y+s2,z-s2);
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[2]/100,  1,0,0);
  glRotatef(-360.0*compteur[3]/100,  1,0,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(-1,0,0);
    //  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,vert);
    //gauche
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2+d,y-s2,z-s2);
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2+d,y+s2,z-s2);
    
    //glColor3ub(255,255,255);    //Blanc
    //glVertex3f(x+s2+d,y+s2,z-s2);
    //glColor3ub(0,0,0);          //Noir
    //glVertex3f(x+s2+d,y+s2,z+s2);
    
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2+d,y+s2,z+s2);
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2+d,y-s2,z+s2);

    //glColor3ub(255,0,255);      //Magenta
    //glVertex3f(x+s2+d,y-s2,z+s2);
    //glColor3ub(255,255,0);      //Jaune
    //glVertex3f(x+s2+d,y-s2,z-s2);
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[4]/100, 0,0,1);
  glRotatef(-360.0*compteur[5]/100, 0,0,1);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,0,-1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,jaune);
    //back
    glVertex3f(x+s2,y+s2,z+s2+d);
    glVertex3f(x-s2,y+s2,z+s2+d);
    glVertex3f(x-s2,y-s2,z+s2+d);
    glVertex3f(x+s2,y-s2,z+s2+d);
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glRotatef( 360.0*compteur[6]/100, 0,0,1);
  glRotatef(-360.0*compteur[7]/100, 0,0,1);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,0,1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,bleu);
    //front
    glVertex3f(x-s2,y+s2,z-s2-d);
    glVertex3f(x+s2,y+s2,z-s2-d);
    
    glVertex3f(x+s2,y-s2,z-s2-d);
    glVertex3f(x-s2,y-s2,z-s2-d);
    
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[8]/100, 0,1,0);
  glRotatef(-360.0*compteur[9]/100, 0,1,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,-1,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,orange);
    //dessus
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2+d,z+s2);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2+d,z+s2);

    //glColor3ub(0,0,0);          //Noir
    //glVertex3f(x+s2,y+s2+d,z+s2);
    //glColor3ub(255,255,255);    //Blanc
    //glVertex3f(x+s2,y+s2+d,z-s2);

    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2+d,z-s2);
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2+d,z-s2);

    //glColor3ub(0,0,255);        //Bleu
    //glVertex3f(x-s2,y+s2+d,z-s2);
    //glColor3ub(0,255,255);      //Cyan
    //glVertex3f(x-s2,y+s2+d,z+s2);

    //C-SPC C-SPC
    //C-U C-CPC
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*compteur[10]/100.0,  0, 1,0);
  glRotatef(-360.0*compteur[11]/100.0,  0, 1,0);
  glBegin(GL_QUADS);
  {
    glNormal3f(0,1,0);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,fushia);
    //dessous
    glVertex3f(x-s2,y-s2-d,z-s2);
    glVertex3f(x+s2,y-s2-d,z-s2);
    glVertex3f(x+s2,y-s2-d,z+s2);
    glVertex3f(x-s2,y-s2-d,z+s2);


  }
  
  glEnd();
  glPopMatrix();
  //M-% query-replace
  glDisable(GL_LIGHTING);  
}


// cube avec les faces qui tournent
void nlcube(float x, float y, float z, float size, float deport, float amorti_vitesse_de_rotation_des_faces) {
  float s2=size / 2;
  float d=deport; //size / 10;
  float k=1; //amorti_vitesse_de_rotation_des_faces;	
  glLineWidth(5);

	
  glPushMatrix();
  glRotatef( 360.0*k*compteur[0]/100, 1,0,0);
  glRotatef(-360.0*k*compteur[1]/100, 1,0,0);
  glBegin(GL_LINES);
  {
    //droite
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y-s2,z-s2);
    glColor3ub(0,255,0);        //Vert
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y-s2,z+s2);
    
    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y-s2,z+s2);
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y+s2,z+s2);
    
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y+s2,z+s2);
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y+s2,z-s2);

    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y+s2,z-s2);
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2-d*(compteur[0]/100-compteur[1]/100),y-s2,z-s2);
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*k*compteur[2]/100,  1,0,0);
  glRotatef(-360.0*k*compteur[3]/100,  1,0,0);
  glBegin(GL_LINES);
  {
    //gauche
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y-s2,z-s2);
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y+s2,z-s2);
    
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y+s2,z-s2);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y+s2,z+s2);
    
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y+s2,z+s2);
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y-s2,z+s2);

    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y-s2,z+s2);
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2+d*(compteur[2]/100-compteur[3]/100),y-s2,z-s2);
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*k*compteur[4]/100, 0,0,1);
  glRotatef(-360.0*k*compteur[5]/100, 0,0,1);
  glBegin(GL_LINES);
  {
    //back
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2,z+s2+d*(compteur[4]/100-compteur[5]/100));
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2,z+s2+d*(compteur[4]/100-compteur[5]/100));

    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2,z+s2+d*(compteur[4]/100-compteur[5]/100));
    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2,z+s2+d*(compteur[4]/100-compteur[5]/100));

    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2,z+s2+d*(compteur[4]/100-compteur[5]/100));
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2,z+s2+d*(compteur[4]/100-compteur[5]/100));

    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2,z+s2+d*(compteur[4]/100-compteur[5]/100));
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2,z+s2+d*(compteur[4]/100-compteur[5]/100));
  }
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glRotatef( 360.0*k*compteur[6]/100, 0,0,1);
  glRotatef(-360.0*k*compteur[7]/100, 0,0,1);
  glBegin(GL_LINES);
  {
    //front
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2,z-s2-d*(compteur[6]/100-compteur[7]/100));
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2,z-s2-d*(compteur[6]/100-compteur[7]/100));

    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2,z-s2-d*(compteur[6]/100-compteur[7]/100));
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2,z-s2-d*(compteur[6]/100-compteur[7]/100));

    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2,z-s2-d*(compteur[6]/100-compteur[7]/100));
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2,z-s2-d*(compteur[6]/100-compteur[7]/100));

    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2,z-s2-d*(compteur[6]/100-compteur[7]/100));
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2,z-s2-d*(compteur[6]/100-compteur[7]/100));
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*k*compteur[8]/100, 0,1,0);
  glRotatef(-360.0*k*compteur[9]/100, 0,1,0);
  glBegin(GL_LINES);
  {
    //dessus
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z+s2);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z+s2);

    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z+s2);
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z-s2);

    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z-s2);
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z-s2);

    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z-s2);
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2+d*(compteur[8]/100-compteur[9]/100),z+s2);

    //C-SPC C-SPC
    //C-U C-CPC
  }
  glEnd();
  glPopMatrix();
  
  glPushMatrix();
  glRotatef( 360.0*k*compteur[10]/100.0,  0, 1,0);
  glRotatef(-360.0*k*compteur[11]/100.0,  0, 1,0);
  glBegin(GL_LINES);
  {
    //dessous
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z-s2);
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z-s2);

    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z-s2);
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z+s2);

    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z+s2);
    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z+s2);

    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z+s2);
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2-d*(compteur[10]/100-compteur[11]/100),z-s2);
  }
  
  glEnd();
  glPopMatrix();
  //M-% query-replace
  
}

// je crois bien que c'est l'hyper hyper cube mais je n'en suis pas
// tout à fait sûr
void cubesdanscubes(float x, float y, float z, float size) {
	
  float k=0.1;
  float kk=0.4;
  float d=1;
  glPushMatrix();
  glRotatef( 360.0*kk*compteur[0]/100, 1,0,0);
  glRotatef(-360.0*kk*compteur[1]/100, 1,0,0);
  glRotatef( 360.0*kk*compteur[2]/100, 1,1,0);
  glRotatef(-360.0*kk*compteur[3]/100, 1,1,0);
  nlcube(0,0,0,1,d,k);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.6,0.6,0.6);
  glRotatef( 360.0*kk*compteur[4]/100, 0,1,0);
  glRotatef(-360.0*kk*compteur[5]/100, 0,1,0);
  glRotatef( 360.0*kk*compteur[6]/100, 0,1,1);
  glRotatef(-360.0*kk*compteur[7]/100, 0,1,1);
  nlcube(0,0,0,1,d,k);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.3,0.3,0.3);
  glRotatef( 360.0*kk*compteur[8]/100, 0,0,1);
  glRotatef(-360.0*kk*compteur[9]/100, 0,0,1);
  glRotatef( 360.0*kk*compteur[10]/100, 1,0,1);
  glRotatef(-360.0*kk*compteur[11]/100, 1,0,1);
  nlcube(0,0,0,1,d,k);
  glPopMatrix();
}

// cube avec les faces déportées qu'on aperçoit au dessus
// du tapis de points

void tcube(float x, float y, float z, float size) {
  float s2=size / 2;
  float d=size / 10;

  glLineWidth(2);
  glEnable(GL_DEPTH_TEST);



  glBegin(GL_QUADS);
  {
    //droite
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2-d,y-s2,z-s2);
    glColor3ub(0,255,0);        //Vert
    glVertex3f(x-s2-d,y-s2,z+s2);
    
    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2-d,y-s2,z+s2);
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2-d,y+s2,z+s2);
    
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2-d,y+s2,z+s2);
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2-d,y+s2,z-s2);

    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2-d,y+s2,z-s2);
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2-d,y-s2,z-s2);

    //gauche
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2+d,y-s2,z-s2);
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2+d,y+s2,z-s2);
    
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2+d,y+s2,z-s2);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2+d,y+s2,z+s2);
    
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2+d,y+s2,z+s2);
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2+d,y-s2,z+s2);

    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2+d,y-s2,z+s2);
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2+d,y-s2,z-s2);
    
    //back
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2,z+s2+d);
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2,z+s2+d);

    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2,z+s2+d);
    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2,z+s2+d);

    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2,z+s2+d);
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2,z+s2+d);

    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2,z+s2+d);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2,z+s2+d);
    
    //front
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2,z-s2-d);
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2,z-s2-d);

    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2,z-s2-d);
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2,z-s2-d);

    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2,z-s2-d);
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2,z-s2-d);

    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2,z-s2-d);
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2,z-s2-d);

    //dessus
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2+d,z+s2);
    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2+d,z+s2);

    glColor3ub(0,0,0);          //Noir
    glVertex3f(x+s2,y+s2+d,z+s2);
    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2+d,z-s2);

    glColor3ub(255,255,255);    //Blanc
    glVertex3f(x+s2,y+s2+d,z-s2);
    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2+d,z-s2);

    glColor3ub(0,0,255);        //Bleu
    glVertex3f(x-s2,y+s2+d,z-s2);
    glColor3ub(0,255,255);      //Cyan
    glVertex3f(x-s2,y+s2+d,z+s2);

    //C-SPC C-SPC
    //C-U C-CPC
    
    //dessous
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2-d,z-s2);
    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2-d,z-s2);

    glColor3ub(255,255,0);      //Jaune
    glVertex3f(x+s2,y-s2-d,z-s2);
    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2-d,z+s2);

    glColor3ub(255,0,255);      //Magenta
    glVertex3f(x+s2,y-s2-d,z+s2);
    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2-d,z+s2);

    glColor3ub(0,255,0);        //Vert 
    glVertex3f(x-s2,y-s2-d,z+s2);
    glColor3ub(255,0,0);        //Rouge
    glVertex3f(x-s2,y-s2-d,z-s2);
  }
  
  glEnd();
  //M-% query-replace
  
}
float myabs(float p) {
  if (p<0) return -p;
  return p;
}



/* debut du starfield2 dans le code source */

int starfield2_initiated=0;
#define nb_etoiles2 500
float st2x[nb_etoiles2];
float st2y[nb_etoiles2];
float st2z[nb_etoiles2];

float startz2=20;
float endz2=2;


void starfield2() {

  float size=myabs(startz2-endz2);

  if (!starfield2_initiated) {
    for (int i=0;i<nb_etoiles2;i++) {
      st2z[i]=startz2-myrand()*size;
      st2y[i]=-size/2.0+myrand()*size;
      st2x[i]=-size/2.0+myrand()*size;
    }
    starfield2_initiated=1;
  }
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glTranslatef(0,0,-ztranslate);
  glPointSize(3);
  glBegin(GL_POINTS);
  {

    for (int i=0;i<nb_etoiles2;i++) {
      int cc=255*(startz2-st2z[i])/size;
      glColor3ub(cc,cc,cc);


      glVertex3f(st2x[i],st2y[i],st2z[i]);
      st2z[i]-=0.05;
      if (st2z[i]<endz2) {
	st2z[i]=st2z[i]+size;
	st2y[i]=-size/2.0+myrand()*size;
	st2x[i]=-size/2.0+myrand()*size;
      }
    }
  }
  glEnd(); 
  glPopMatrix();
}




int starfield_initiated=0;
#define nb_etoiles 500
float stx[nb_etoiles];
float sty[nb_etoiles];
float stz[nb_etoiles];

float startz=40;
float endz=20;

void starfield() {

  float size=myabs(startz-endz);

  if (!starfield_initiated) {
    for (int i=0;i<nb_etoiles;i++) {
      stz[i]=startz-myrand()*size;
      sty[i]=-size/2.0+myrand()*size;
      stx[i]=-size/2.0+myrand()*size;
    }
    starfield_initiated=1;
  }
  glPointSize(3);
	
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(0,0,endz-3, 0,0,endz, 0,1,0); // pos, point qu'il regarde, up
	
	
  glBegin(GL_POINTS);
  {

    for (int i=0;i<nb_etoiles;i++) {
	
      int cc=255*(startz-stz[i])/size;
      glColor3ub(cc,cc,cc);

			
      if (myrand()>0.05) glVertex3f(stx[i],sty[i],stz[i]);
      stz[i]-=0.05;
      if (stz[i]<endz) {
	stz[i]=stz[i]+size;
	sty[i]=-size/2.0+myrand()*size;
	stx[i]=-size/2.0+myrand()*size;
      }
    }
  }
  glEnd();
  glPopMatrix();
 
 
}
#define PSF_NB_ETOILES_MAX 500
class ProgStarfield {
public:
  int onote=-1;
  int onote_time=0;
  int starfield_initiated=0;
  int nbre_etoiles=0;
  float stx[PSF_NB_ETOILES_MAX];
  float sty[PSF_NB_ETOILES_MAX];
  float stz[PSF_NB_ETOILES_MAX];

  float startz=40;
  float endz=20;
  float size;
  int croissance=1;
  ProgStarfield() {
    size=myabs(startz-endz);
  }
  void add_etoile() {
    stz[nbre_etoiles]=startz-myrand()*size;
    sty[nbre_etoiles]=-size/2.0+myrand()*size;
    stx[nbre_etoiles]=-size/2.0+myrand()*size;
    nbre_etoiles++;
  }
  void process() {
    int note=tab_notes[nb_notes-1].name;
    int note_time=tab_notes[nb_notes-1].time;
    if ((note!=onote) || (note_time!=onote_time)) {
      if (croissance) {
	if (nbre_etoiles<PSF_NB_ETOILES_MAX) {
	  add_etoile();
	} else croissance=0;
      } else { // if decroissance
	if (nbre_etoiles>0) {
	  nbre_etoiles--;
	} else {
	  croissance=1;
	}
      }
    }
    onote=note;
    onote_time=note_time;

    glPointSize(3);
	
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0,0,endz-3, 0,0,endz, 0,1,0); // pos, point qu'il regarde, up
	
	
    glBegin(GL_POINTS);
    {

      for (int i=0;i<nbre_etoiles;i++) {
	
	int cc=255*(startz-stz[i])/size;
	glColor3ub(cc,cc,cc);

			
	if (myrand()>0.05) glVertex3f(stx[i],sty[i],stz[i]);
	stz[i]-=0.05;
	if (stz[i]<endz) {
	  stz[i]=stz[i]+size;
	  sty[i]=-size/2.0+myrand()*size;
	  stx[i]=-size/2.0+myrand()*size;
	}
      }
    }
    glEnd();
    glPopMatrix();
 
 
  }
	
};
ProgStarfield *progstarfield = new ProgStarfield();
/*
  int fabriquer_cuboid(float hauteur_cuboid,float longueur_cuboid,float largeur_cuboid) {
  }
  int fabriquer_face_cuboid_ouverte_xmin() {
  }
  int fabriquer_face_cuboid_ouverte_xmax() {
  }
  int fabriquer_face_cuboid_ouverte_ymin() {
  }
  int fabriquer_face_cuboid_ouverte_ymax() {
  }
  int
*/ 
// les lignes parallèles
void sdamier() {
  float sizex=12;
  float sizey=12;
  float sizez=12;
  int i=0;
  float scale=2.5;

  for (float x=-0.5;x<=0.5;x+=1.0/11.0) {
    
    if (note_on_off[i]) glLineWidth(3);
    else glLineWidth(1);
    glBegin(GL_LINES);
    {
      glColor3ub(composantes[i].r,composantes[i].v,composantes[i].b);
      glVertex3f(scale*x,-1,-scale); glVertex3f(scale*x,-1,+scale);
    }  
    glEnd();
    i++;
  }
  /*
    for (float z=-0.5;z<=0.5;z+=1.0/11.0) {
    glLineWidth(1);
    glBegin(GL_LINES);
    {
    glColor3ub(255,255,255);
    glVertex3f(-scale,-1,z*scale); glVertex3f(+scale,-1,z*scale);
    }
    glEnd();
    i++;
    }
  */
  

  
}
class DamierData {
public:
  int damier_initiated;
  int wmap;// 40
  int lmap;// 40
  float **map1;
  float **map2;
  float deltai;
  float deltaj;
  DamierData(int wmap, int lmap) {
    this->wmap=wmap;
    this->lmap=lmap;

    map1=(float**)malloc(sizeof(float*)*wmap);
    map2=(float**)malloc(sizeof(float*)*wmap);
    for (int i=0;i<this->wmap;i++) {
      map1[i]=(float*)malloc(this->lmap*sizeof(float));
      map2[i]=(float*)malloc(this->lmap*sizeof(float));
    }
    this->deltai=0;
    this->deltaj=0;
    this->damier_initiated = 0;

  }
}; // dp : de points et sp : solid polygon

float moyenne_point(DamierData *dd, float **map,int i,int j) {
  int ii=i;
  int jj=j;
  float somme=0;
  for (int c=0;c<8;c++) {
    if (c==0) {
      // gauche
      if ((i-1) < 0) ii=dd->wmap-1; else ii=i-1;
      jj=j;
    }
    if (c==1) {
      //droite
      if ((i+1) > dd->wmap-1) ii=0; else ii=i+1;
      jj=j;
    }
    if (c==2) {
      //bas
      ii=i;
      if ((j+1) > dd->lmap-1) jj=0; else jj=j+1;
    }
    if (c==3) {
      //haut
      ii=i;
      if ((j-1) < 0) jj=dd->lmap-1; else jj=j;
    }
    if (c==4) {
      // gauche-haut
      if ((i-1) < 0) ii=dd->wmap-1; else ii=i-1;
      if ((j-1) < 0) jj=dd->lmap-1; else jj=j;
    }
    if (c==5) {
      // droite-haut
      if ((i+1) > dd->wmap-1) ii=0; else ii=i+1;
      if ((j-1) < 0) jj=dd->lmap-1; else jj=j;
    }
    if (c==6) {
      // gauche-bas
      if ((i-1) < 0) ii=dd->wmap-1; else ii=i-1;
      if ((j+1) > dd->lmap-1) jj=0; else jj=j+1;
    }
    if (c==7) {
    
      //droite-bas
      if ((i+1) > dd->wmap-1) ii=0; else ii=i+1;
      if ((j+1) > dd->lmap-1) jj=0; else jj=j+1;
    }
    somme = somme + map[ii][jj];
  }
  return (map[ii][jj] + somme) / 9.0;
}
float mappage(DamierData *dd,float **map, int i, int j, int di, int dj) {
  int ii=i+di;
  int jj=j+dj;
  while (ii<0) ii=ii+dd->wmap; // cette ligne n'a de cesse de m'intriguer et c'est v pour visual select block
  while (jj<0) jj=jj+dd->lmap; // en fait on wrap et on ne veut pas que ce soit négatif
  ii = ii % dd->wmap;
  jj = jj % dd->lmap;
  return map[i][j];
}
//Constructeur
DamierData *dp = new DamierData(40,40);
// le damier de point... 
void damier_de_points() {
  //float sizex=12;
  //float sizey=12;
  //float sizez=12;
  glPointSize(5);
  float scale=4;
  if (!dp->damier_initiated) {
    // on commence par randomizer une map
    for (int i=0;i<dp->wmap;i++) {
      for (int j=0;j<dp->lmap;j++) {
	dp->map1[i][j]=myrand();
      }
    }
    // ensuite on va la lisser
    for (int i=0;i<dp->wmap; i++) {
      for (int j=0;j<dp->lmap;j++) {
	
	dp->map2[i][j]=moyenne_point(dp,dp->map1,i,j);
				
      }
    }
    // ensuite on va encore la lisser
    for (int i=0;i<dp->wmap; i++) {
      for (int j=0;j<dp->lmap;j++) {
	
	dp->map1[i][j]=moyenne_point(dp,dp->map2,i,j);
				
      }
    }
    for (int i=0;i<dp->wmap; i++) {
      for (int j=0;j<dp->lmap;j++) {
	dp->map2[i][j]=moyenne_point(dp,dp->map1,i,j);
				
      }
    }

    // ensuite on va la lisser
    for (int i=0;i<dp->wmap; i++) {
      for (int j=0;j<dp->lmap;j++) {
	dp->map1[i][j]=moyenne_point(dp,dp->map2,i,j);
      }
    }
    for (int i=0;i<dp->wmap; i++) {
      for (int j=0;j<dp->lmap;j++) {
	dp->map2[i][j]=moyenne_point(dp,dp->map1,i,j);
      }
    }
    // ensuite on va la lisser
    for (int i=0;i<dp->wmap; i++) {
      for (int j=0;j<dp->lmap;j++) {
	dp->map1[i][j]=moyenne_point(dp,dp->map2,i,j);
      }
    }
    for (int i=0;i<dp->wmap; i++) {
      for (int j=0;j<dp->lmap;j++) {
	dp->map2[i][j]=moyenne_point(dp,dp->map1,i,j);
      }
    }
    dp->deltai=0;
    dp->deltaj=0;
    dp->damier_initiated=1;
  }
  glPushMatrix();
	
  glScalef(8.0,4.0,4.0);
	

 
  glTranslatef(0, -0.1, +0.7);

  glRotatef(90,1,0,0);

  if (note_en_cours() % 2 == 0) inc_moteur=+1;
  else inc_moteur=-1;
	
  glRotatef(moteur % 360, 0, 0, 1);


  int i;
  int j;
  
  i=0;
  for (float x=-0.5;i<dp->wmap;x+=1.0/(dp->wmap-1)) {
    j=0;
    for (float y=-0.5;j<dp->lmap;y+=1.0/(dp->lmap-1)) {
      
      glBegin(GL_POINTS);
      {
	glColor3ub(dp->map2[i][j]*255, 0, 0);
	glVertex3f(x,y,mappage(dp,dp->map2, i,j, (int)dp->deltai, (int)dp->deltaj));
      }
      glEnd();
      
      j++;
    }
    i++;
  }
  dp->deltai+=0.1;
  dp->deltaj+=0.1;
  glPopMatrix();
}
void vsub(float A[3], float B[3], float *R) {
  R[0]=A[0]-B[0];
  R[1]=A[1]-B[1];
  R[2]=A[2]-B[2];
}

float pvec1(float u1,float u2,float u3,float v1,float v2,float v3) {
  return u2*v2-u3*v2; 
}

float pvec2(float u1,float u2,float u3,float v1,float v2,float v3) {
  return -u1*v3+u3*v1;
}

float pvec3(float u1,float u2,float u3,float v1,float v2,float v3) {
  return u1*v2-u2*v1;
}

float vecteur[3];
void pvec(float u1,float u2,float u3,float v1,float v2,float v3,float *nor) {
  nor[0]=u2*v3-u3*v2;
  nor[1]=-u1*v3+u3*v1;
  nor[2]=u1*v2-u2*v1;
}
void pvecv(float v1[3], float v2[3], float *nor) {
  pvec(v1[0],v1[1],v1[2], v2[0],v2[1],v2[2], nor);
}
float norme(float u1,float u2,float u3) {
  return sqrt(u1*u1+u2*u2*u3*u3);
}
float vnorme(float *v) {
  return(norme(v[0],v[1],v[2]));
}
void normalize(float *v) {
  float d=vnorme(v);
  v[0]=v[0]/d;
  v[1]=v[1]/d;
  v[2]=v[2]/d;
}
//Constructeur
DamierData *sp=new DamierData(10,10);

void damier() {


  float scale=4;
  if (!sp->damier_initiated) {
    printf("on initie le damier\n");
    // on commence par randomizer une map
    for (int i=0;i<sp->wmap;i++) {
      for (int j=0;j<sp->lmap;j++) {
	sp->map1[i][j]=myrand();
      }
    }
    // ensuite on va la lisser
    for (int i=0;i<sp->wmap; i++) {
      for (int j=0;j<sp->lmap;j++) {
	sp->map2[i][j]=moyenne_point(sp,sp->map1,i,j);
      }
    }
    // ensuite on lisse le résultat
    for (int i=0;i<sp->wmap; i++) {
      for (int j=0;j<sp->lmap;j++) {
	sp->map1[i][j]=moyenne_point(sp,sp->map2,i,j);

      }
    }
    for (int i=0;i<sp->wmap; i++) {
      for (int j=0;j<sp->lmap;j++) {	
	sp->map2[i][j]=moyenne_point(sp,sp->map1,i,j);
      }
    }
    // ensuite on va la lisser
    for (int i=0;i<sp->wmap; i++) {
      for (int j=0;j<sp->lmap;j++) {	
	sp->map1[i][j]=moyenne_point(sp,sp->map2,i,j);
      }
    }
    for (int i=0;i<sp->wmap; i++) {
      for (int j=0;j<sp->lmap;j++) {	
	sp->map2[i][j]=moyenne_point(sp,sp->map1,i,j);
      }
    }

    // ensuite on va la lisser
    for (int i=0;i<sp->wmap; i++) {
      for (int j=0;j<sp->lmap;j++) {
	
	sp->map1[i][j]=moyenne_point(sp,sp->map2,i,j);

      }
    }
    for (int i=0;i<sp->wmap; i++) {
      for (int j=0;j<sp->lmap;j++) {
	
	sp->map2[i][j]=moyenne_point(sp,sp->map1,i,j);

      }
    }

    sp->deltai=0;
    sp->deltaj=0;
    sp->damier_initiated=1;
  }
  glPushMatrix();
  glScalef(8.0/2,4.0/2,4.0/2);
  glTranslatef(0,-0.1,+0.7);

  glRotatef(90,1,0,0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDisable(GL_BLEND);
  int i;
  int j;
  float incx=1.0/(sp->wmap-1);
  float incy=1.0/(sp->lmap-1);
  float ix=incx;
  float iy=incy;
  float x=-0.5+1/(sp->wmap-1);
  float n1,n2,n3;
  float d;

  for (i=1;i<sp->wmap-1;i+=2) {
    float y=-0.5+1/(sp->lmap-1);
    for (j=1;j<sp->lmap-1;j+=2) {

      //8 triangles

      //          ^y
      //          |
      //     x    |
      //     <----
      glBegin(GL_TRIANGLES);
      //glBegin(GL_LINES);
      {

	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,orange);
	// 1
	pvec(0  ,iy ,mappage(sp,sp->map2,i  ,j+1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     ix ,iy ,mappage(sp,sp->map2,i+1,j+1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);
		  
	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j,   (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x   ,y+iy,mappage(sp,sp->map2,i  ,j+1, (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x+ix,y+iy,mappage(sp,sp->map2,i+1,j+1, (int)sp->deltai, (int)sp->deltaj));
	// 2
	
	pvec(ix ,iy ,mappage(sp,sp->map2,i+1,j+1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     ix ,0  ,mappage(sp,sp->map2,i+1,j  ,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);

	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x+ix,y+iy,mappage(sp,sp->map2,i+1,j+1, (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x+ix,y   ,mappage(sp,sp->map2,i+1,j  , (int)sp->deltai, (int)sp->deltaj));
	//3
	pvec(ix ,iy ,mappage(sp,sp->map2,i+1,j+1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     ix ,-iy,mappage(sp,sp->map2,i+1,j-1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);
	
	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x+ix,y+iy,mappage(sp,sp->map2,i+1,j+1, (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x+ix,y-iy,mappage(sp,sp->map2,i+1,j-1, (int)sp->deltai, (int)sp->deltaj));
	//4
	pvec(ix ,-iy,mappage(sp,sp->map2,i+1,j-1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     0  ,-iy,mappage(sp,sp->map2,i  ,j-1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);

	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x+ix,y-iy,mappage(sp,sp->map2,i+1,j-1, (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x   ,y-iy,mappage(sp,sp->map2,i  ,j-1, (int)sp->deltai, (int)sp->deltaj));
	//5
	pvec(0  ,-iy,mappage(sp,sp->map2,i  ,j-1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     -ix,-iy,mappage(sp,sp->map2,i-1,j-1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);

	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x   ,y-iy,mappage(sp,sp->map2,i  ,j-1, (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x-ix,y-iy,mappage(sp,sp->map2,i-1,j-1, (int)sp->deltai, (int)sp->deltaj));

	//6
	pvec(-ix,-iy,mappage(sp,sp->map2,i-1,j-1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     -ix,0  ,mappage(sp,sp->map2,i-1,j  ,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);

	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x-ix,y-iy,mappage(sp,sp->map2,i-1,j-1, (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x-ix,y   ,mappage(sp,sp->map2,i-1,j  , (int)sp->deltai, (int)sp->deltaj));
	//7
	pvec(-ix,0  ,mappage(sp,sp->map2,i-1,j  ,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     -ix,iy ,mappage(sp,sp->map2,i-1,j+1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);

	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x-ix,y   ,mappage(sp,sp->map2,i-1,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x-ix,y+iy,mappage(sp,sp->map2,i-1,j+1, (int)sp->deltai, (int)sp->deltaj));
	//8
	pvec(-ix,iy ,mappage(sp,sp->map2,i-1,j+1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj),
	     0  ,iy ,mappage(sp,sp->map2,i  ,j+1,(int)sp->deltai,(int)sp->deltaj)-mappage(sp,sp->map2,i,j,(int)sp->deltai,(int)sp->deltaj)
	     ,nor);
	d=norme(nor[0],nor[1],nor[2]);
	glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);

	glVertex3f(x   ,y   ,mappage(sp,sp->map2,i  ,j  , (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x-ix,y+iy,mappage(sp,sp->map2,i-1,j+1, (int)sp->deltai, (int)sp->deltaj));
	glVertex3f(x   ,y+iy,mappage(sp,sp->map2,i  ,j+1, (int)sp->deltai, (int)sp->deltaj));
	
      }
      glEnd();
      y+=2*iy;
    }
    x+=2*ix;
  }
		
  i=0;
  for (float x=-0.5;i<sp->wmap;x+=1.0/(sp->wmap-1)) {
    j=0;
    for (float y=-0.5;j<sp->lmap;y+=1.0/(sp->lmap-1)) {

      glBegin(GL_POINTS);
      {

	glColor3ub(sp->map2[i][j]*255, 0, 0);
	//glVertex3f(x,y,mappage(sp,sp->map2, i,j, (int)sp->deltai, (int)sp->deltaj));
      }

      glEnd();
      
      j++;
    }
    i++;
		
  }
  
  sp->deltai+=0.01;
  sp->deltaj+=0.01;
  glPopMatrix();
  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);  
}

#define PI 3.14159265

void octogone() {
  float r2s2=sqrt(2.0) / 2.0;
  glPointSize(5);
  glLineWidth(3);
  for (int i=0;i<12;i++) {
    float z=compteur[i]/100.0;
    glPushMatrix();
    //    glScalef(1.0/(i+1),1.0/(i+1),1.0);
    glScalef( 1-(i/12.0),(1-i/12.0),1.0);
    glRotatef((compteur[i]/100.0) * 360, 0,0,1);
    glBegin(GL_LINE_STRIP);
    {
      glColor3ub(comp(i));       
      glVertex3f(0,1,z);
      glVertex3f(-r2s2,r2s2,z);
      glVertex3f(-1,0,z);
      glVertex3f(-r2s2,-r2s2,z);
      glVertex3f(0,-1,z);
      glVertex3f(r2s2,-r2s2,z);
      glVertex3f(1,0,z);
      glVertex3f(r2s2,r2s2,z);
      glVertex3f(0,1,z);
    }
    glEnd();
    glPopMatrix();
  }
}

int babalballon() { 

  float nb=4*12;
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glPointSize(1);
  glPushMatrix();
  glTranslatef(0.2,-0.3,0);
  float theta=-PI/2;
  for (int i=0;i<=nb;i++) {

    float alpha=0;
    for (int j=0;j<nb;j++) {
      glBegin(GL_POINTS);
      {
	float z=cos(theta)*sin(alpha);
	float x=-cos(theta)*cos(alpha);
	float y=sin(theta);
	float d=sqrt(x*x+y*y+z*z);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,rouge);
	glNormal3f(x/d,y/d,z/d);
	glVertex3f(x,y,z);
      }
      glEnd();
      alpha+=2*PI/(nb);
    }
    theta+=PI/nb;
    
  }
  glPopMatrix();
  glDisable(GL_LIGHTING);
}

#define nbbalballon 24
int rmp(int j) {
  if (j==-1) return nbbalballon-1;
  else return j;
}

float ablanc[4]={1.0,1.0,1.0,0.5};
float ablanc1[4]={1.0,1.0,1.0,1.0};
float arouge[4]={1.0,0,0,0.5};
float avert[4]={0,1.0,0,0.5};
float ableu[4]={0,0,1.0,0.75};
float ajaune[4]={1.0,1.0,0,0.75};
float aorange[4]={1.0,0.5,0,0.5};
float afushia[4]={1.0,0.0,0.5,0.5};
float amauve[4]={0.5,0.0,1.0,0.5};
float avert_d_eau[4]={0.0,1.0,0.5,0.5};
float acitron_vert[4]={0.5,1.0,0.0,0.5};
float aturquoise[4]={0.0,0.5,1.0,0.75};  

int balballon() {
  float nb=nbbalballon;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_BLEND);
  glDisable(GL_BLEND);
  //glDepthMask(GL_FALSE);
  glPointSize(2);
  glPushMatrix();


  float lastix[nbbalballon+1];
  float lastiy[nbbalballon+1];
  float lastiz[nbbalballon+1];
  float nextlastix[nbbalballon+1];
  float nextlastiy[nbbalballon+1];
  float nextlastiz[nbbalballon+1];
  float *plastix;
  float *plastiy;
  float *plastiz;
  float *pnextlastix;
  float *pnextlastiy;
  float *pnextlastiz;
  float *auxx;
  float *auxy;
  float *auxz;
  float d;


  plastix=lastix;
  plastiy=lastiy;
  plastiz=lastiz;
  pnextlastix=nextlastix;
  pnextlastiz=nextlastiz;
  pnextlastiy=nextlastiy;
  float theta=-PI/2;
  for (int n=0;n<nb;n++) {
    lastix[n]=0;
    lastiy[n]=-1;
    lastiz[n]=0;
  }
  glRotatef(45,1,0,0);
  glScalef(0.7, 0.7, 0.3);
  //C-x-x to exchange mark and point
  for (int i=0;i<nb+1;i+=1) {

    float alpha=0;
    float da=0; //(2.0*PI/24)*compteur[(int)(i/2.0)]/100;
    float kx=(1+0*0.2*compteur[(int)(i/2.0)]/100);
    float kz=(1+0*0.2*compteur[(int)(i/2.0)]/100);
    plastix[nbbalballon]=-kx*cos(theta)*cos(2*PI-2*PI/nb+da);;
    plastiy[nbbalballon]=sin(theta);
    plastiz[nbbalballon]=kz*cos(theta)*sin(2*PI-2*PI/nb+da);
    for (int j=0;j<nb;j++) {
      float z=kz*cos(theta)*sin(alpha+da);
      float x=-kx*cos(theta)*cos(alpha+da);
      float y=sin(theta);
      float nor[3];
      glBegin(GL_TRIANGLES);
      {

	/*
	  if (i==1) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mauve);
	  } else if (i==2) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,rouge);
	  } else if (i==3) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,jaune);
	  } else if (i==4) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,turquoise);
	  } else if (i==5) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,citron_vert);
	  } else if (i==6) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,vert_d_eau);
	  } else if (i==7) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,fushia);
	  } else if (i==8) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,orange);
	  } else if (i==9) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,bleu);
	  } else if (i==9) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,vert);
	  }
	*/
	if (i!=0) {
	  if (i==nb) glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,fushia);
	  else glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,aturquoise);
	  
	  pvec(plastix[rmp(j-1)]-x,plastiy[rmp(j-1)]-y,plastiz[rmp(j-1)]-z,
	       plastix[rmp(j)]-x,plastiy[rmp(j)]-y,plastiz[rmp(j)]-z,nor);
	    
	  d=sqrt(nor[0]*nor[0]+nor[1]*nor[1]+nor[2]*nor[2]);
	    
	  glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);
	  //         x  
	  //         -
	  //        /|
	  //       / |
	  //      /  |
	  //     /   |
	  //    /    |
	  //   -------
          //             
	  glVertex3f(x,y,z);
	  glVertex3f(plastix[rmp(j)],plastiy[rmp(j)],plastiz[rmp(j)]);
	  glVertex3f(plastix[rmp(j-1)],plastiy[rmp(j-1)],plastiz[rmp(j-1)]);

	}

	if (i!=nb) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,jaune);
	  float lastjx=-kx*cos(theta)*cos(alpha-2.0*PI/nb+da);
	  float lastjy=sin(theta);
	  float lastjz=cos(theta)*sin(alpha-2.0*PI/nb+da);
	  pvec(lastjx-x,lastjy-y,lastjz-z,plastix[rmp(j-1)]-x,plastiy[rmp(j-1)]-y,plastiz[rmp(j-1)]-z,nor); // calcul d'un petit produit vectoriel des familles et on met le résultat dans nor
	       
	  d=sqrt(nor[0]*nor[0]+nor[1]*nor[1]+nor[2]*nor[2]);
	  glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);
	  //if (i==1) glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,rouge);
	  //else {
	  /*
	    if (note_on_off[i/2])  //&& note_on_off[j/2])
	    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,tabcomposantes[i/2]);
	    else
	    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,ajaune);
	  */
	  //}
	  glVertex3f(x,y,z);
	  glVertex3f(lastjx,lastjy,lastjz);	  
	  glVertex3f(plastix[rmp(j-1)],plastiy[rmp(j-1)],plastiz[rmp(j-1)]);
	  //         x 
	  //   -------
	  //   |    /|
	  //   |   / |
	  //   |  /  |
	  //   | /   |
	  //   |/    |
	  //   -------
          //          
	}	  
	pnextlastix[j]=x;
	pnextlastiy[j]=y;
	pnextlastiz[j]=z;

      }
      glEnd();
      alpha+=2*PI/(nb);
    }
    auxx=plastix;
    auxy=plastiy;
    auxz=plastiz;
    plastix=pnextlastix;
    plastiz=pnextlastiz;
    plastiy=pnextlastiy;
    pnextlastix=auxx;
    pnextlastiy=auxy;
    pnextlastiz=auxz;
      
    theta+= PI/(nb);
    
  }
  
  glPopMatrix();
  glDepthMask(GL_TRUE);
  glDisable(GL_LIGHTING);
}
int insidebalballon() {
  float nb=nbbalballon;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_BLEND);
  glDisable(GL_BLEND);
  //glDepthMask(GL_FALSE);
  glPointSize(2);
  glPushMatrix();


  float lastix[nbbalballon+1];
  float lastiy[nbbalballon+1];
  float lastiz[nbbalballon+1];
  float nextlastix[nbbalballon+1];
  float nextlastiy[nbbalballon+1];
  float nextlastiz[nbbalballon+1];
  float *plastix;
  float *plastiy;
  float *plastiz;
  float *pnextlastix;
  float *pnextlastiy;
  float *pnextlastiz;
  float *auxx;
  float *auxy;
  float *auxz;
  float d;


  plastix=lastix;
  plastiy=lastiy;
  plastiz=lastiz;
  pnextlastix=nextlastix;
  pnextlastiz=nextlastiz;
  pnextlastiy=nextlastiy;
  float theta=-PI/2;
  for (int n=0;n<nb;n++) {
    lastix[n]=0;
    lastiy[n]=-1;
    lastiz[n]=0;
  }
  glRotatef(45,1,0,0);
  glScalef(2.7, 2.7, 2.7);
  //C-x-x to exchange mark and point
  for (int i=0;i<nb+1;i+=1) {

    float alpha=0;
    float da=0; //(2.0*PI/24)*compteur[(int)(i/2.0)]/100;
    float kx=(1+0*0.2*compteur[(int)(i/2.0)]/100);
    float kz=(1+0*0.2*compteur[(int)(i/2.0)]/100);
    plastix[nbbalballon]=-kx*cos(theta)*cos(2*PI-2*PI/nb+da);;
    plastiy[nbbalballon]=sin(theta);
    plastiz[nbbalballon]=kz*cos(theta)*sin(2*PI-2*PI/nb+da);
    for (int j=0;j<nb;j++) {
      float z=kz*cos(theta)*sin(alpha+da);
      float x=-kx*cos(theta)*cos(alpha+da);
      float y=sin(theta);
      float nor[3];
      glBegin(GL_TRIANGLES);
      {

	/*
	  if (i==1) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mauve);
	  } else if (i==2) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,rouge);
	  } else if (i==3) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,jaune);
	  } else if (i==4) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,turquoise);
	  } else if (i==5) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,citron_vert);
	  } else if (i==6) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,vert_d_eau);
	  } else if (i==7) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,fushia);
	  } else if (i==8) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,orange);
	  } else if (i==9) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,bleu);
	  } else if (i==9) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,vert);
	  }
	*/
	if (i!=0) {
	  if (i==nb) glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,fushia);
	  else glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,aturquoise);
	  
	  pvec(plastix[rmp(j-1)]-x,plastiy[rmp(j-1)]-y,plastiz[rmp(j-1)]-z,
	       plastix[rmp(j)]-x,plastiy[rmp(j)]-y,plastiz[rmp(j)]-z,nor);
	    
	  d=sqrt(nor[0]*nor[0]+nor[1]*nor[1]+nor[2]*nor[2]);
	  nor[0]=-nor[0]; nor[1]=-nor[1]; nor[2]=-nor[2];  
	  glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);
	  //         x  
	  //         -
	  //        /|
	  //       / |
	  //      /  |
	  //     /   |
	  //    /    |
	  //   -------
          //             
	  glVertex3f(x,y,z);
	  glVertex3f(plastix[rmp(j)],plastiy[rmp(j)],plastiz[rmp(j)]);
	  glVertex3f(plastix[rmp(j-1)],plastiy[rmp(j-1)],plastiz[rmp(j-1)]);

	}

	if (i!=nb) {
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,jaune);
	  float lastjx=-kx*cos(theta)*cos(alpha-2.0*PI/nb+da);
	  float lastjy=sin(theta);
	  float lastjz=cos(theta)*sin(alpha-2.0*PI/nb+da);
	  pvec(lastjx-x,lastjy-y,lastjz-z,plastix[rmp(j-1)]-x,plastiy[rmp(j-1)]-y,plastiz[rmp(j-1)]-z,nor); // calcul d'un petit produit vectoriel des familles et on met le résultat dans nor
	       
	  d=sqrt(nor[0]*nor[0]+nor[1]*nor[1]+nor[2]*nor[2]);
	  nor[0]=-nor[0]; nor[1]=-nor[1]; nor[2]=-nor[2];  
	  glNormal3f(nor[0]/d,nor[1]/d,nor[2]/d);
	  //if (i==1) glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,rouge);
	  //else {
	  /*
	    if (note_on_off[i/2])  //&& note_on_off[j/2])
	    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,tabcomposantes[i/2]);
	    else
	    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,ajaune);
	  */
	  //}
	  glVertex3f(x,y,z);
	  glVertex3f(lastjx,lastjy,lastjz);	  
	  glVertex3f(plastix[rmp(j-1)],plastiy[rmp(j-1)],plastiz[rmp(j-1)]);
	  //         x 
	  //   -------
	  //   |    /|
	  //   |   / |
	  //   |  /  |
	  //   | /   |
	  //   |/    |
	  //   -------
          //          
	}	  
	pnextlastix[j]=x;
	pnextlastiy[j]=y;
	pnextlastiz[j]=z;

      }
      glEnd();
      alpha+=2*PI/(nb);
    }
    auxx=plastix;
    auxy=plastiy;
    auxz=plastiz;
    plastix=pnextlastix;
    plastiz=pnextlastiz;
    plastiy=pnextlastiy;
    pnextlastix=auxx;
    pnextlastiy=auxy;
    pnextlastiz=auxz;
      
    theta+= PI/(nb);
    
  }
  
  glPopMatrix();
  glDepthMask(GL_TRUE);
  glDisable(GL_LIGHTING);
}

typedef struct {
  float x;
  float y;
  float z;
} points;
void sub(points p1, points p2, points *r) {
  r->x=p1.x-p2.x;
  r->y=p1.y-p2.y;
  r->z=p1.z-p2.z;
}
void mul(float k, points p, points *r) {
  r->x=k*p.x;
  r->y=k*p.y;
  r->z=k*p.z;
}
void add(points p1, points p2, points *r) {
  r->x=p1.x+p2.x;
  r->y=p1.y+p2.y;
  r->z=p1.z+p2.z;
}
void barycentre3(float *p1,float *p2,float *p3, float bary[3]) {
  bary[0]=(p1[0]+p2[0]+p3[0]) / 3.0;
  bary[1]=(p1[1]+p2[1]+p3[1]) / 3.0;
  bary[2]=(p1[2]+p2[2]+p3[2]) / 3.0;
}
void setvec(float x, float y, float z, float v[3]) {

}
void tetraedre(float x,float y,float z, float a, int numcol) {
  float b=a / (2.0*sqrt(2));
  glPointSize(5);
  glLineWidth(3);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_LIGHT1);  
  glDisable(GL_BLEND);
  glTranslatef(x,y,z);
  glBegin(GL_TRIANGLES);
  {
    //glColor3ub(comp(numcol));
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol]);
    
    pvec(2*b,-2*b,0, 2*b,0,-2*b,nor);

    // j'ai mes précieuses normales, donc maintenant, ce qui est sûr c'est que je vais avoir besoin du barycentre

    normalize(nor);
    glNormal3f(nor[0],nor[1],nor[2]);

    float d=sqrt(b*b+b*b+b*b);
    //glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
    float dhf[3]; setvec(-b,b,b,dhf);
    glVertex3f(-b, b, b); //à droite en haut au fond
    //glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
    float gbf[3]; setvec(b,-b,b,gbf);
    glVertex3f( b,-b, b); //à gauche en bas au fond
    //glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
    float ghd[3]; setvec(b,b,-b,ghd);
    glVertex3f( b, b,-b); //à gauche en haut devant

    pvec(2*b,0,-2*b,0,-2*b,-2*b,nor);
    normalize(nor);
    glNormal3f(nor[0],nor[1],nor[2]);
    //vert


    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol+1]);
    //glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
    glVertex3f(-b, b, b); //à droite en haut au fond
    //glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
    glVertex3f( b, b,-b); //à gauche en haut devant
    //glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
    float dbd[3]; setvec(-b,-b,-b,dbd);
    glVertex3f(-b,-b,-b); //à droite en bas devant

    pvec(-2*b,0,-2*b,0,2*b,-2*b,nor);
    normalize(nor);
    glNormal3f(nor[0],nor[1],nor[2]);
    //marron

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol+2]);
    //glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
    glVertex3f( b,-b, b); //à gauche en bas au fond
    //glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
    glVertex3f(-b,-b,-b); //à droite en bas devant
    //glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
    glVertex3f( b, b,-b); //à gauche en haut devant

    pvec(-2*b,2*b,0,-2*b,0,-2*b,nor);
    normalize(nor);
    glNormal3f(nor[0],nor[1],nor[2]);
    //rouge

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol+3]);
    //glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
    glVertex3f( b,-b, b); //à gauche en bas au fond
    //glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
    glVertex3f(-b, b, b); //à droite en haut au fond
    //glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
    glVertex3f(-b,-b,-b); //à droite en bas devant
  }
  glEnd();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  
}

void tetra(float x,float y,float z, float a, int numcol) {
  float b=a / (2.0*sqrt(2));
  glPointSize(5);
  glLineWidth(3);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);  
  glDisable(GL_BLEND);
  glTranslatef(x,y,z);
  glBegin(GL_TRIANGLES);
  {
    //glColor3ub(comp(numcol));
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol]);
    
    //    pvec(2*b,-2*b,0, 2*b,0,-2*b,nor);
    //glNormal3f(nor[0],nor[1],nor[2]);

    float d=sqrt(b*b+b*b+b*b);
    glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
    glVertex3f(-b, b, b); //à droite en haut au fond
    glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
    glVertex3f( b,-b, b); //à gauche en bas au fond
    glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
    glVertex3f( b, b,-b); //à gauche en haut devant

    //pvec(2*b,0,-2*b,0,-2*b,-2*b,nor);
    //glNormal3f(nor[0],nor[1],nor[2]);
    //vert
    glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
    glVertex3f(-b, b, b); //à droite en haut au fond
    glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
    glVertex3f( b, b,-b); //à gauche en haut devant
    glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
    glVertex3f(-b,-b,-b); //à droite en bas devant

    //pvec(-2*b,0,-2*b,0,2*b,-2*b,nor);
    //glNormal3f(nor[0],nor[1],nor[2]);
    //marron
    glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
    glVertex3f( b,-b, b); //à gauche en bas au fond
    glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
    glVertex3f(-b,-b,-b); //à droite en bas devant
    glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
    glVertex3f( b, b,-b); //à gauche en haut devant

    //pvec(-2*b,2*b,0,-2*b,0,-2*b,nor);
    //glNormal3f(nor[0],nor[1],nor[2]);
    //rouge
    glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
    glVertex3f( b,-b, b); //à gauche en bas au fond
    glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
    glVertex3f(-b, b, b); //à droite en haut au fond
    glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
    glVertex3f(-b,-b,-b); //à droite en bas devant
  }
  glEnd();
  glDisable(GL_LIGHTING);
  
}
void make_palette(int angle1, int angle2, int nbcouleurs, float (*palette)[3]) {
  rgb colrgb;
  hsv colhsv;
  for (int i=0;i<nbcouleurs;i++) {
    
    colhsv.h=angle1+(angle2-angle1)*((float)(i)/nbcouleurs);
    colhsv.s=1.0;
    colhsv.v=1.0;
    colrgb = hsv2rgb(colhsv);
    palette[i][0]=colrgb.r;
    palette[i][1]=colrgb.g;
    palette[i][2]=colrgb.b;

  }
}


int *ptetra_rand_tab;

int ptetra_initialized=0;
int ptetra_nbc=32;//nombre de couleurs
float (*ptetra_palette)[3];
void ptetra(float x, float y, float z, float a,int numcomp) {

  if (!ptetra_initialized) {
    ptetra_palette = (float (*)[3])malloc(3*ptetra_nbc*sizeof(ptetra_palette));
    
    make_palette(35,73,ptetra_nbc,ptetra_palette);
    ptetra_initialized=1;
  }

  tetra(x,y,z,a,numcomp);
  float b=a / (2.0*sqrt(2));
  points p[4];
  int nbp=128;
  p[0] = (points) {-b, b, b}; //à droite en haut au fond
  p[1] = (points) { b,-b, b}; //à gauche en bas au fond
  p[2] = (points) { b, b,-b}; //à gauche en haut devant
  p[3] = (points) {-b,-b,-b}; //à droite en bas devant

  for (int i=0;i<nbp;i++) {
    
    // on randomize 0,1,2,3
    
    int done = 0; 
    int nbf=0;
    int qr[4]={-1,-1,-1,-1};
    while (!done) {
      int r=rand() % 4;
      int deja_choisi=0;
      // on regarde si le nombre compris entre 0 et 3 a déjà été choisi
      for (int j=0;j<4;j++) {
	if (qr[j]==r) { deja_choisi=1; break; }	
      }
      // si ce n'est pas le cas, on le range
      if (!deja_choisi) {
	for (int j=0;j<4;j++) {
	  if (qr[j]==-1) {qr[j]=r; break;}
	}
	// et on augmente de 1 le nombre de numéros choisis
	nbf++;
      }
      if (nbf==4) done=1;
    }

    
    //for (int k=0;k<4;k++) printf("%d\n",qr[k]);
    //printf("\n");

    // maintenant dans qr[4] on a 0,1,2,3 randomizés
    // et on est dans une boucle qui le fait nbp fois
    // on va prendre le premier point, créer 2 autres points v1 et V2
    // en faisant une homotéthie avec les deux suivants
    points v1;
    points v2;
    points v1tmp;
    points kv1tmp;
    float k=(2.1*myrand());
    sub(p[qr[1]],p[qr[0]],&v1tmp);
    mul(k,v1tmp,&kv1tmp);
    add(p[qr[0]],kv1tmp,&v1);

    //glDisable(GL_LIGHTING);
    glPointSize(3);
    glBegin(GL_POINTS);
    {
      // glColor3ub(255,0,0);
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,ptetra_palette[rand() % ptetra_nbc]);      
      glVertex3f(v1.x,v1.y,v1.z);
    }
    glEnd();
  }
}


typedef struct {
  int life;
  double x;       // a fraction between 0 and 1
  double y;       // a fraction between 0 and 1
  double z;       // a fraction between 0 and 1
  float rotx;
  float roty;
  float rotz;
  float irotx;
  float iroty;
  float irotz;
  float taille;
  float itaille;
  double vx;
  double vy;
  double vz;
  int numcomp;
} tparticules; /* la vieille structure de particule qu'on aime quand même et qui sert pour les tétraèdres en particules */

int tetrapart_initialized=0;
#define nbpmax 32
int nbp=0;
int lifemax=125;

tparticules tpart[nbpmax];
tparticules *get_newpart() {
  // scanne le tableau des particules à la recherche d'une particule morte et la retourne
  for (int i=0;i<nbpmax;i++) {
    if (tpart[i].life==0) return &tpart[i];
  }
}

void tetrapart() {
  
  glEnable(GL_DEPTH_TEST);
  if (!tetrapart_initialized) {
    for (int i=0;i<nbpmax;i++) {
      tpart[i].life=0;
    }
    tetrapart_initialized=1;
  }
  
  for (int i=0;i<12;i++) {
    if (newnotes_val[i]!=0) {
      if (nbp<nbpmax-1) {
	tparticules *p=get_newpart();
	nbp++;
	p->x=0;
	p->y=0;
	p->z=0;
	p->taille=1.0;
	p->itaille=0;//0.01*myrand();
	p->life=lifemax;
	p->rotx=rand() % 360;
	p->roty=rand() % 360;
	p->rotz=rand() % 360;
	p->irotx=(180 - rand() % 360) / lifemax;
	p->iroty=(180 - rand() % 360) / lifemax;
	p->irotz=(180 - rand() % 360) / lifemax;
	p->vx=(-0.5 + myrand())*0.05;
	p->vy=(-0.5 + myrand())*0.05;
	p->vz=0;//-0.03; //(-0.5 + myrand())*vmax;
	p->numcomp=i;
	
      }
    }
  }
  for (int i=0;i<nbp;i++) {
    if (tpart[i].life!=0) {
      glPushMatrix();
      glRotatef((int)tpart[i].rotx,1,0,0);
      glRotatef((int)tpart[i].roty,0,1,0);
      glRotatef((int)tpart[i].rotz,0,0,1);
      tetra(tpart[i].x,tpart[i].y,tpart[i].z,tpart[i].taille,tpart[i].numcomp);
      
      glPopMatrix();
    }
  }
  for (int i=0;i<nbp;i++) {
    if (tpart[i].life!=0) {
      tpart[i].taille+=tpart[i].itaille;
      tpart[i].rotx+=tpart[i].irotx;
      tpart[i].roty+=tpart[i].iroty;
      tpart[i].rotz+=tpart[i].irotz;
      tpart[i].x+=tpart[i].vx;
      tpart[i].y+=tpart[i].vy;
      tpart[i].z+=tpart[i].vz;
      tpart[i].life--;
      if (tpart[i].life == 0) nbp--;
    } 
  }
}

int get_nb_notes_on(long time) {
  for (int i=0;i<nb_notes;i++) {
    
  }
}

int texteur_last_note_texted[2]={0,0};
char *texteur_txt[2]={NULL,NULL};
char *texteur_last_word_defed[2]={NULL,NULL};


void aff_txt_at_pos(char *txt, float x, float y) {


  glColor3ub(255,255,255);
  glRasterPos2f(x, y);
  
  int len = (int) strlen(txt);
  for (int i = 0; i < len; i++){
    
    //glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, txt[i] );
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, txt[i] );
    //glutStrokeCharacter( GLUT_STROKE_ROMAN, txt[i] );

  }
  
  glColor3f(1,1,1);

}

void texteur(int langue, float x, float y) {

  //glMatrixMode( GL_PROJECTION );
  //glPushMatrix();
  //glLoadIdentity();

  //glOrtho( -400.0,  400.0,     -300.0,  300.0,      1.0,  100.0 );
  if ((last_note_on!=texteur_last_note_texted[langue]) || (texteur_txt[langue]==NULL)) {
    texteur_txt[langue] = random_read_dico(langue);
		
    texteur_last_note_texted[langue]=last_note_on;
  }

  glColor3ub(255,255,255);
  glRasterPos2f(x, y);
  
  int len = (int) strlen(texteur_txt[langue]);
  for (int i = 0; i < len; i++){
    
    //glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, texteur_txt[i] );
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, texteur_txt[langue][i] );
    //glutStrokeCharacter( GLUT_STROKE_ROMAN, texteur_txt[i] );

  }
  // je mange une saucisse
  //glColor3f(1,1,1);

  if ((netfunctions) && (langue==ANGLAIS)) {
    if (((time(NULL) - last_note_played_time) > 3) && (texteur_last_word_defed[langue]!=texteur_txt[langue])){
      char cmd[127];
      sprintf(cmd,"/bin/echo \"%s\" >/home/pi/prg/colormusic/random_word",texteur_txt[langue]);
      system(cmd);
      system("/usr/bin/killall -USR1 python3_def");
      texteur_last_word_defed[langue]=texteur_txt[langue];
    }
  }
}


float partoche_dz=0;
float partoche_dzmax=1;
float partoche_idz=0.005;

void partoche() {
  
  glLineWidth(3);
	
  long timetime=mstime();
  long firsttime=tab_notes[0].time;
  
  int nb_notes_on=0;
  
  float x=-1;
  float y=0;
  float z=1;

  float ky=1/10.0; //ten fingers
  float kx=1/10000.0;
  float kz=1/16.0;
  

  partoche_dz = partoche_dz + partoche_idz;


  for (int i=0;i<nb_notes;i++) {
    z=1;
    x=1-kx*(tab_notes[i].time-firsttime);
    while (x<-1) {
      x=x+2.0;
      z=z-kz;
    }
    z = z - partoche_dz;
    while (z<-2) {
      z=z+3;
    }
   
    int duree;
    if (tab_notes[i].duree==-1) {
      duree=timetime - tab_notes[i].time;
    } else {
      duree=tab_notes[i].duree;
    }
    nb_notes_on=list_size(tab_notes_on[i]);
    
    glBegin(GL_LINES);
    {
      glColor3ub(comp(tab_notes[i].name));
      glVertex3f(x,-1+y+ky*nb_notes_on,z);
      glVertex3f(x-kx*duree,-1+y+ky*nb_notes_on,z);
    }
    glEnd();

  }
  
}

void change_part() {
  prevpart=partnum;	
  partnum++;
  if (partnum > lastpart) {
	
    partnum = firstpart;
  }

  nb_notes_since_last_change=0;
}




#define NB_PASTILLES 6
#define RAYON_DE_PERCUSSION_VAISSEAU_PASTILLE 0.02


int pastillage_initialized=0;
pastilles tab_pastilles[NB_PASTILLES];
float hauteur_triangle_vaisseau = sqrt(3)/3;
float echelle_reduction_vaisseau=1.0/5;
struct {
  struct {
    float x;
    float y;
  } position;
  struct {
    float x;
    float y;
  } cercle_de_percussion;
  struct {
    float x;
    float y;
  } posnmoins1;
  struct {
    float x;
    float y;
  } posn;
  struct {
    float x;
    float y;
  } vitesse;
  struct {
    float x;
    float y;
  } vn;
  struct {
    float x;
    float y;
  } vnmoins1;
  struct {
    float x;
    float y;
  } force_appliquee;
  struct {
    float x;
    float y;
  } resistance_fluide;
  struct {
    float z;
  } rot;
  unsigned long int time_last_shoot;
} vaisseau;

void cercle(float x0, float y0, float r, int nb_de_segments) {
	
  glBegin(GL_LINE_STRIP); 
  {
    glColor3ub(comp(1));
    for (int i=0; i<nb_de_segments; i++) {
      glVertex3f( x0+r*cos(i*M_PI*2/nb_de_segments), y0+r*sin(i*M_PI*2/nb_de_segments), 0);
    }
    glVertex3f( x0+r*cos(0*M_PI*2/nb_de_segments), y0+r*sin(0*M_PI*2/nb_de_segments), 0);
				
  }
  glEnd();
}
float **polygone(float x0, float y0, float r, int nb_de_segments) {
  float **poly;
  poly = (float**)malloc(sizeof(float*)*nb_de_segments);
  for (int i=0;i<nb_de_segments;i++) {
    poly[i]=(float*)malloc(sizeof(float)*3);
  }
  for (int i=0; i<nb_de_segments;i++) {
    poly[i][0]=x0+r*cos(i*M_PI*2/nb_de_segments);
    poly[i][1]=y0+r*sin(i*M_PI*2/nb_de_segments);
    poly[i][2]=0;
  }
  return poly;	
}
// fonction sign qui renvoit +1 si x est positif et -1 si x est négatif
int sgn(float x) {
  if (x>=0) return +1;
  else return -1;
}


class AfficheurDeSquircles {
  void squircle(float x0, float y0, float z0, float r, int nb_segments, int numcolor) {
    glBegin(GL_POLYGON);
			
    glDisable(GL_BLEND);
    glColor3ub(compub(numcolor));
    for (int i=0;i<nb_segments;i++) {
      float theta=i*M_PI*2/nb_segments;
      glVertex3f( x0+r*cos(theta),
		  y0+r*sin(theta),
		  z0);
    }
    glVertex3f(	x0+r*cos(0),
		y0+r*sin(0),
		z0);
    glEnd();
  }
public:
  void ta(unsigned char** col,int i,unsigned char r,unsigned char v,unsigned char b,unsigned char a) {
    col[i][0]=r; col[i][1]=v; col[i][2]=b; col[i][3]=a;
  }

  int makeCube(unsigned char **col) {
    int lc=glGenLists(1);
    glNewList(lc,GL_COMPILE);
    glBegin(GL_QUADS);
    glColor4ub(col[0][0],col[0][1],col[0][2],col[0][3]); // face de droite
    glVertex3f(-1,-1,-1); 
    glVertex3f(-1,-1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1,-1);

    glColor4ub(col[1][0],col[1][1],col[1][2],col[1][3]); // face de gauche 
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1,-1);
    glVertex3f(1, -1,-1);
    glVertex3f(1, -1, 1);

    glColor4ub(col[2][0],col[2][1], col[2][2], col[2][3]); // face du dessus
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);

    glColor4ub(col[3][0],col[3][1],col[3][2],col[3][3]); // face du dessous
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);

    glColor4ub(col[4][0],col[4][1],col[4][2],col[4][3]); // face de devant
    glVertex3f(-1,1,-1);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);

    glColor4ub(col[5][0],col[5][1],col[5][2],col[5][3]); // face de derrière
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glEnd();
    glEndList();
    return lc;
  }


  float taille_du_squircle=0.3;
  float taille_du_cube=0.1;
  float ecart_entre_les_squircles=0.05;
  int listcube;
  AfficheurDeSquircles() {
    unsigned char **col=(unsigned char**)malloc(sizeof(unsigned char*)*6);
    for (int i=0;i<6;i++) {
      col[i]=(unsigned char*)malloc(sizeof(unsigned char)*4);
    }
    for (int i=0;i<6;i++) {
      ta(col,i,compaub(i));
      /*
	ta(col,0,128,128,0,128);
	ta(col,1,0,128,128,128);
	ta(col,2,128,0,128,128);
	ta(col,3,0,128,0,128);
	ta(col,4,0,0,128,128);
	ta(col,5,128,0,0,0);
      */
    }
    listcube=makeCube(col);
  }
  void modify() {
			
  }
  void affiche3squircles(float x0, float y0, float z0, int ibase) {
    for (int i=0;i<3;i++) {
      float offsx=i*(taille_du_squircle+ecart_entre_les_squircles);
      squircle(x0+offsx,y0,z0,0.01*compteur[i+ibase]*taille_du_squircle,32,ibase+i);
      glPushMatrix();
      glTranslatef(x0+offsx,y0,z0);
      glScalef(0.01*compteur[i+ibase]*taille_du_cube,0.01*compteur[i+ibase]*taille_du_cube,0.01*compteur[i+ibase]*taille_du_cube);
      glRotatef(0.01*compteur[i+ibase]*360,1,1,1);
      glCallList(listcube);
      glPopMatrix();
    }
  }
  void affiche() {
		
    printf("afficheur de squircles\n");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,2 , 0,0,0, 0,1,0); // pos, point qu'il regarde, up

    float dx=taille_du_squircle+ecart_entre_les_squircles;

    float ofsx=-1;
		
    //squircle(0,0,0,0.1,32,1);
    affiche3squircles(ofsx,0.1,0,0);
    affiche3squircles(0.3,0.3,0,3);
    affiche3squircles(ofsx,0.5,0,6);
    affiche3squircles(0.3,0.7,0,9);
  }
  ~AfficheurDeSquircles() {
  }
};
AfficheurDeSquircles *afficheurDeSquircles;
void zcercle(float x0, float y0, float z0, float r, int nb_de_segments) {
	
  glBegin(GL_LINE_STRIP); 
  {
    glColor3ub(comp(1));
    for (int i=0; i<nb_de_segments; i++) {
      glVertex3f( x0+r*cos(i*M_PI*2/nb_de_segments), y0+r*sin(i*M_PI*2/nb_de_segments), z0);
    }
    glVertex3f( x0+r*cos(0*M_PI*2/nb_de_segments), y0+r*sin(0*M_PI*2/nb_de_segments), z0);
				
  }
  glEnd();
}
void axes() {

  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  gluLookAt(0,0,-4,0,0,0, 0,1,0); // pos, point qu'il regarde, up

  glEnable(GL_LINE_SMOOTH);
  glPushMatrix();


  glTranslatef(-0.7,- 0.7, -1);
  glLineWidth(5);
  glBegin(GL_LINES);

  glColor3b(127,0,0); // le vecteur x
  glVertex3f( 0,0,0);
  glVertex3f( 1,0,0);
    
  glColor3b(0,127,0); // le vecteur y
  glVertex3f(0,0,0);
  glVertex3f(0,1,0);
  
  glColor3b(0,0,127); // le vecteur z
  glVertex3f(0,0,0);
  glVertex3f(0,0,1);

  glEnd();

  zcercle(0,0,0,0.1,6);
  glPopMatrix();
}

void aff_vaisseau() {


  glLineWidth(3);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();


  // et alors pour la petite croquette, il est possible en travaillant donc comme on le fait ici avec des matrices homogènes 4x4 de faire la matrice de projection avec perspective de base et donc juste de diviser les composantes x et y par z avec la matrice suivante
  // 1  0  0   0
  // 0  1  0   0
  // 0  0 -1  -1
  // 0  0  0   0

  // avec cette matrice on a :
  // x'=x/(-z)
  // y'=y/(-z)
  // z'=1
  // mais là on va juste travailler avec une matrice identité vu qu'il n'y a pas de profondeur dans ce petit jeu
  glLoadIdentity();

  
  glMatrixMode(GL_MODELVIEW); //specifies which matrix stack is the arget for matrix operations, ça peut être GL_MODELVIEW, GL_PROJECTION, GL_TEXTURE ou GL_COLOR
  glPushMatrix();

  glLoadIdentity(); // on met l'identité
  glEnable(GL_DEPTH_TEST);

	
	


   
  // alors normalement une ligne de x=-1 à x=1 couvre tout l'écran en largeur et une ligne de y=-1 à y=1 couvre tout l'écran en hauteur


  cercle(vaisseau.cercle_de_percussion.x, vaisseau.cercle_de_percussion.y, RAYON_DE_PERCUSSION_VAISSEAU_PASTILLE, /*nombre de segments du cercle=*/20);
  glTranslatef(vaisseau.position.x, vaisseau.position.y, 0);
  glRotatef(vaisseau.rot.z,0.0,0.0,1.0);
  glScalef(echelle_reduction_vaisseau, echelle_reduction_vaisseau, 0);
  //glDisable(GL_LIGHTING);
  glBegin(GL_LINE_STRIP);
  {

    glColor3b(127,0,0);        //Rouge
    
    glVertex3f(-(1.0/2),0.0,0);
    glVertex3f( (1.0/2),0.0,0);
    glVertex3f( 0.0, hauteur_triangle_vaisseau, 0);
    glVertex3f(-(1.0/2),0.0,0);
  }
  glEnd();

  glMatrixMode(GL_PROJECTION);

  glPopMatrix();



  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

}
void cree_un_nuage_de_particules_autour_du_point(float x0, float y0, int couleur);

const float resistance_fluide_rot_k=0; //0.1; 
const float force_de_rappel_rot_k=0;//0.001;
const int duree_de_vie_a_la_naissance=10000;

template <class T,class R> 
class A {
private:
  T *ptr;
  R var;
private:
  A() {
  }
  char virtual B() {
    return 'z';
  }
};
template <class Q,class R>
class C : protected A<Q,R> {
private:
  Q *ptr;
  R var;
protected:
  Q *ptr2;
  R var2;
public:
  char B() {
    return 'a';
  }
  C() {}
};
class ObjetRotule {
  //float *
  //O
  //theta[i]
};
class Particule {

public:
  Vecteur *pos0;
  Vecteur *pos0S;			/* la position du corps attirant en kS*1/r*/
  Vecteur *pos;
  Vecteur *posn;
  Vecteur *posnmoins1;
  Vecteur *vit;
  Vecteur *vitn;
  Vecteur *vitnmoins1;

  Vecteur *rot;
  Vecteur *rotn;
  Vecteur *rotnmoins1;
  Vecteur *vrot;
  Vecteur *vrotn;
  Vecteur *vrotnmoins1;

  Vecteur *force_appliquee;
  Vecteur *force_appliquee_rot;
  Palette *palette;
  float scale;
  int couleur;
  unsigned char alpha;
  int vie;
  int lifetime;
  float force_de_rappel_k;
  float resistance_fluide_k;
  float inc_pos_palette;
  float kS;
  Particule(Vecteur *pos, Vecteur *vit, Vecteur *rot, Vecteur *vrot, 
	    int couleur, unsigned char alpha, float resistance_fluide_k, float force_de_rappel_k, int lifetime, 
	    float scale, Palette *palette, Vecteur *pos0S=NULL, float kS=0) {

    this->pos = pos;
    this->pos0 = new Vecteur(pos);
			
    this->pos0S = pos0S;
    if (this->pos0S == NULL) {
      this->pos0S = new Vecteur(0,0,0);
    }
    this->kS = kS;

    this->posn = new Vecteur(pos);
    this->posnmoins1 = new Vecteur(pos);
    this->vit = vit;
    this->vitn = new Vecteur(vit);
    this->vitnmoins1 = new Vecteur(vit);

    this->rot = rot;
    this->rotn = new Vecteur(rot);
    this->rotnmoins1 = new Vecteur(rot);

    this->vrot = vrot;
    this->vrotn = new Vecteur(vrot);
    this->vrotnmoins1 = new Vecteur(vrot);

    this->lifetime=lifetime;
    this->vie=lifetime;

    this->force_appliquee = new Vecteur(0,0,0);
    this->force_appliquee_rot = new Vecteur(0,0,0);
    this->couleur=couleur;
    this->alpha=alpha;
    this->resistance_fluide_k=resistance_fluide_k;
    this->force_de_rappel_k=force_de_rappel_k;
    this->scale = scale;			
    this->palette = palette;
    if (this->palette != NULL) {
      this->inc_pos_palette = (float)this->palette->nb_couleurs / (float)(this->lifetime);
    }
  }
  ~Particule() {
    delete(this->pos);
    delete(this->pos0);
    delete(this->posn);
    delete(this->posnmoins1);
    delete(this->vit);
    delete(this->vitn);
    delete(this->vitnmoins1);
    delete(this->rot);
    delete(this->rotn);
    delete(this->rotnmoins1);
    delete(this->vrot);
    delete(this->vrotn);
    delete(this->vrotnmoins1);
    delete(this->force_appliquee);
    delete(this->force_appliquee_rot);
    delete(this->pos0S);
  }
  /*
			
   */ 
  virtual int particule_evolue() { // book5
    if (this->vie == 0) {
      return 0;
    }

    this->vitn->x = this->vit->x;
    this->vitn->y = this->vit->y;
    this->vitn->z = this->vit->z;

    this->rotn->x = this->rot->x;
    this->rotn->y = this->rot->y;
    this->rotn->z = this->rot->z;  
    /* on va rajouter tranquillement une petite force sympa */
    float rrr = 1;	
    float rr = 1;
    float r = 1;
    if (kS!=0) {
      rr = sqr(pos->x - pos0S->x) + sqr(pos->y - pos0S->y) + sqr(pos->z - pos0S->z);
      r = sqrt( sqr(pos->x - pos0S->x) + sqr(pos->y - pos0S->y) + sqr(pos->z - pos0S->z) );
      rrr = r*rr;
    }

    this->vit->x = this->vitn->x + this->force_appliquee->x - 
      this->resistance_fluide_k*this->vitnmoins1->x - 
      this->force_de_rappel_k*(this->posnmoins1->x - this->pos0->x) 
      + this->kS*(1/rr)*(this->pos0S->x - this->posnmoins1->x); 
    /* on divise une fois par r pour normaliser le vecteur et une autre fois pour avoir une force en 1/r */
						
    this->vit->y = this->vitn->y + this->force_appliquee->y - 
      this->resistance_fluide_k*this->vitnmoins1->y - 
      this->force_de_rappel_k*(this->posnmoins1->y - this->pos0->y)
      + this->kS*(1/rr)*(this->pos0S->y - this->posnmoins1->y);
						
    this->vit->z = this->vitn->z + this->force_appliquee->z - 
      this->resistance_fluide_k*this->vitnmoins1->z - 
      this->force_de_rappel_k*(this->posnmoins1->z - this->pos0->z)
      + this->kS*(1/rr)*(this->pos0S->z - this->posnmoins1->z);

    // la force en S nous donne donc une force de rappel en 1/r qui devrait être intéressante
		
    this->vrot->x = this->vrotn->x + 
      this->force_appliquee_rot->x 
      - resistance_fluide_rot_k*this->vrotnmoins1->x 
      - force_de_rappel_rot_k*this->rotnmoins1->x;
    this->vrot->y = this->vrotn->y + 
      this->force_appliquee_rot->y 
      - resistance_fluide_rot_k*this->vrotnmoins1->y 
      - force_de_rappel_rot_k*this->rotnmoins1->y;
    this->vrot->z = this->vrotn->z + 
      this->force_appliquee_rot->z 
      - resistance_fluide_rot_k*this->vrotnmoins1->z 
      - force_de_rappel_rot_k*this->rotnmoins1->z;

    this->posnmoins1->x = this->posn->x;  
    this->posnmoins1->y = this->posn->y;
    this->posnmoins1->z = this->posn->z;

    this->rotnmoins1->x = this->rotn->x;
    this->rotnmoins1->y = this->rotn->y;
    this->rotnmoins1->z = this->rotn->z;

    this->posn->x = this->pos->x;
    this->posn->y = this->pos->y;
    this->posn->z = this->pos->z;

    this->rotn->x = this->rot->x;
    this->rotn->y = this->rot->y;
    this->rotn->z = this->rot->z;
		
    this->vitnmoins1->x = this->vitn->x;
    this->vitnmoins1->y = this->vitn->y;
    this->vitnmoins1->z = this->vitn->z;

    this->vrotnmoins1->x = this->vrotn->x;
    this->vrotnmoins1->y = this->vrotn->y;
    this->vrotnmoins1->z = this->vrotn->z;

    this->pos->x = this->pos->x + this->vit->x;
    this->pos->y = this->pos->y + this->vit->y;
    this->pos->z = this->pos->z + this->vit->z;

    this->rot->x = this->rot->x + this->vrot->x;
    this->rot->y = this->rot->y + this->vrot->y;
    this->rot->z = this->rot->z + this->vrot->z;

    if (this->rot->x > 360) this->rot->x -= 360;
    if (this->rot->y > 360) this->rot->y -= 360;
    if (this->rot->z > 360) this->rot->z -= 360;

    if (lifetime!=-1) this->vie--;

    return 1;
  }
  virtual void particule_affiche() {

    glPushMatrix();

    glTranslatef(this->pos->x, this->pos->y, this->pos->z);

    glRotatef(this->rot->x, 1, 0, 0 );
    glRotatef(this->rot->y, 0, 1, 0 );
    glRotatef(this->rot->z, 0, 0, 1 );
    glScalef(scale, scale, scale);
    glBegin(GL_TRIANGLES);
    {
      if (this->palette != NULL) {
	int ii=(int)(this->inc_pos_palette * this->vie);
	// une sorcière uburu
	glColor4ub(this->palette->couleurs[ii][0],
		   this->palette->couleurs[ii][1],
		   this->palette->couleurs[ii][2],
		   this->palette->couleurs[ii][3]);
      } else {
	glColor4ub(	(unsigned char)composantes[this->couleur].r,
			(unsigned char)composantes[this->couleur].v,
			(unsigned char)composantes[this->couleur].b, this->alpha);
      }
      glVertex3f(-0.5, -1.0/3, 0);
      glVertex3f( 0.5, -1.0/3, 0);
      glVertex3f( 0.0, hauteur_triangle_equilateral-1.0/3, 0);
    }
    glEnd();

    glPopMatrix();

  }	

}; 
#define RAYON_DE_PERCUSSION_TIR_PASTILLE 0.02
class Particule_Tir : public Particule {
public:
  Particule_Tir(Vecteur *pos, Vecteur *vit, Vecteur *rot, Vecteur *vrot, int couleur, unsigned char alpha, float resistance_fluide_k, float force_de_rappel_k, int lifetime, float scale, Palette *palette ) 
    : Particule(pos, vit, rot, vrot, couleur, alpha, resistance_fluide_k,force_de_rappel_k, lifetime, scale, palette) {
    /*	alors cette petites sous-classe appelle le constructeur de la classe mère en passant les paramètres qu'on souhaite passer, en l'occurence tous, 
	pour le moment.
    */
  }
  int particule_evolue() {
  	if (!Particule::particule_evolue()) return 0; /* on appelle bien tranquillement la méthode de la classe mère */
    /* et ensuite on fait ce qu'il faut faire comme par exemple gérer les hits de pastilles */
		for (int i=0;i<NB_PASTILLES;i++) {
			if (sqrt(sqr(tab_pastilles[i].x-this->pos->x)+sqr(tab_pastilles[i].y-this->pos->y))<RAYON_DE_PERCUSSION_TIR_PASTILLE) {
			if (!tab_pastilles[i].touched) {
				tab_pastilles[i].touched=1;
	  /*	donc là, ce qui serait bien c'est de tester si la méthode fonctionne toujours mais j'ai méga la flemme 
		je veux être dans un appartement new yorkais, ou dans un loft berlinois, non en fait je ne veux pas être alleurs qu'ici,
		le plaisir de tester c'est le plaisir de débugger
	  */
				cree_un_nuage_de_particules_autour_du_point(tab_pastilles[i].x, tab_pastilles[i].y, random() % 12 );
			}
		}
	}
  }
  void particule_affiche() {
    /* la petite méthode d'affichage qui va bien et qui remplace la méthode virtuelle de la classe mère */
    glPushMatrix();
    glPointSize(8);

    glTranslatef(this->pos->x, this->pos->y, -1);
    /*
      glRotatef(this->rot->x, 1, 0, 0 );
      glRotatef(this->rot->y, 0, 1, 0 );
      glRotatef(this->rot->z, 0, 0, 1 );
    */
    glScalef(scale,scale,scale);
    glBegin(GL_POINTS);
    {
      //glColor4b(0,127,0, 4);        // vert, green, une merveilleuse petite couleur parisienne, faubourg st honoré avec le petit alpha qui va
      glColor4ub(	(unsigned char)composantes[this->couleur].r,
			(unsigned char)composantes[this->couleur].v,
			(unsigned char)composantes[this->couleur].b, this->alpha);
      glVertex3f( 0, 0, 0);
    }
    glEnd();

    glPopMatrix();
			
  }
};

template <class T>
class Maille {
public:
  T *ptr;
  Maille<T> *suivant;
  Maille<T> *precedent;
  Maille<T>(T *ptr) {
    this->ptr=ptr;
  }
  ~Maille() {
    delete(ptr);
  }
};


template <class T>
class Liste {
public:
  Maille<T> *premier;
  Maille<T> *dernier;
  int nb_elements=0;
  T *element(int i) {
    Maille<T> *p=premier;
    int c=0;
    while (p!=NULL) {
      if (c==i) return p->ptr;
      c++;
      p=p->suivant;
    }
    return NULL;
  }
  T *operator[](int i) {
    return element(i);
  }
  T *element_adresse_du_ptr(int i) {
    Maille<T> *p=premier;
    int c=0;
    while (p!=NULL) {
      if (c==i) return &(p->ptr);
      c++;
      p=p->suivant;
    }
    return NULL;
  }
  
  int is_vide() {
    return nb_elements == 0;
  }
  /* on va très tranquillement faire retourner le paramètre à la fonction */
  Maille<T> *liste_ajouter(Maille<T> *m) { //book6
    if (this->nb_elements==0) { this->premier=m; this->dernier=m; m->precedent=NULL; m->suivant=NULL; }
    else {
      this->dernier->suivant=m;
      m->precedent=this->dernier;
      this->dernier=m;
      m->suivant=NULL;
    }
    this->nb_elements++;
    return m;
  }
  void liste_inserer_first(Maille<T> *m) {
    if (this->nb_elements==0) {this->premier=m; this->dernier=m; m->precedent=NULL; m->suivant=NULL; }
    else {
      Maille<T> *paux=this->premier;
      this->premier=m; 
      m->suivant=paux; 
      paux->precedent=m; 
      m->precedent=NULL; 
    }
    this->nb_elements++;
  }
  void liste_inserer_first(T *element) {//insere en première position
    liste_inserer_first(new Maille<T>(element));
  }
  void ajouter(T *element) {
    liste_ajouter(new Maille<T>(element));
  }
  void liste_enlever(T *o) {
    Maille<T> *maille=this->premier;
    T *objet_trouved = NULL;
    while (maille != NULL) {
      if (o==maille->ptr) { objet_trouved = maille->ptr; break; }
      maille = maille->suivant;
    }
    if (objet_trouved!=NULL) {
      liste_enlever(maille);
    }
  }
  void liste_enlever(Maille<T> *m) { // enleve la maille de la liste mais ne supprime pas l'élément
    if (m->precedent == NULL) {
      this->premier = m->suivant;
    } else {
      m->precedent->suivant = m->suivant; 
    }
    if (m->suivant == NULL) {
      this->dernier = m->precedent;
    } else {
      m->suivant->precedent = m->precedent;
    }
    // delete(m);
    this->nb_elements--;
  }
		
};
class MatriceN {
public:
  int m;
  int n;
  float *val;
  float *mi; /* bel et bien la matrice augmentée */
  float *res;
  float *ligne_aux;
  float *mi_ligne_aux;
  float *val_bak;
  float *x;
  MatriceN(int m, int n, float *val) {
    /* m : nombre de lignes */
    /* n : nombre de colonnes */
    this->m = m;
    this->n = n;
    this->val = val;
    this->val_bak = (float*)malloc(m*n*sizeof(float));
    this->res = (float*)malloc(m*n*sizeof(float));

    this->ligne_aux=(float*)malloc(n*sizeof(float));
    this->mi_ligne_aux=(float*)malloc(2*n*sizeof(float));
    this->mi=(float*)malloc(2*n*m*sizeof(float));
    this->x=(float*)malloc(m*sizeof(float));
  }
  void echanger_lignes(int ligne1, int ligne2) {
    for (int c=0;c<n;c++) {
      ligne_aux[c]=val[ligne1*n+c];
    }
    for (int c=0;c<n;c++) {
      val[ligne1*n+c]=val[ligne2*n+c];
    }
    for (int c=0;c<n;c++) {
      val[ligne2*n+c]=ligne_aux[c];
    }
  }
  void soustraire_ligne_de_ligne(int ligne1, int ligne2) {
    for (int c=0;c<n;c++) {
      val[ligne2*n+c]-=val[ligne1*n+c];
    }			
  }
  void extraire_ligne_aux_de_ligne(int ligne) {
    for (int c=0;c<n;c++) {
      ligne_aux[c]=val[ligne*n+c];
    }						
  }

  void dans_mi_extraire_ligne_aux_de_ligne(int ligne) {
    for (int c=0;c<2*n;c++) {
      mi_ligne_aux[c]=mi[ligne*2*n+c];
    }						
  }
  void mul_ligne_aux_par_k(float k) {
    for (int c=0;c<n;c++) {
      ligne_aux[c]*=k;
    }
  }
  void dans_mi_mul_ligne_aux_par_k(float k) {
    for (int c=0;c<2*n;c++) {
      mi_ligne_aux[c]*=k;
    }
  }
  void soustraire_ligne_aux_de_ligne(int ligne) {
    for (int c=0;c<n;c++) {
      val[ligne*n+c]-=ligne_aux[c];
    }			
  }
  void dans_mi_soustraire_ligne_aux_de_ligne(int ligne) {
    for (int c=0;c<2*n;c++) {
      mi[ligne*2*n+c]-=mi_ligne_aux[c];
    }			
  }
  void afficher() {
    printf("Affichage MatriceN\n");
    for (int l=0;l<m;l++) {
      for (int c=0;c<n;c++) {
	printf("%e\t",val[l*n+c]);
      }
      printf("\n");
    }
    printf("\n");
  }
  void mul_ligne_par_k(int ligne, float k) {
    for (int c=0;c<n;c++) {
      val[ligne*n+c]=k*val[ligne*n+c];
    }
  }
  int trouve_ligne_du_pivot_a_partir_de_la_ligne_et_pour_la_colonne(int r, int c) {
    /* c est la colonne en cours */
    /* r est la ligne minimale du pivot */
    float valeur_max=DBL_MIN;
    int lp;
    for (int l = r ; l < m ; l++) {
      if (val[l*n+c]>valeur_max) {
	valeur_max=val[l*n+c];
	lp = l;
      }
    }
    return lp;
  }
  /*	si tu travailles pour de l'argent tu travailles en étant mécontent car tu travailles en n'étant pas satisfait de ta condition
	si tu sais jouer en travaillant tu peux aller très loin, cultive l'analogie petit homme 
  */
  void sauvegarder() {
    for (int i=0;i<m*n;i++) {
      val_bak[i] = val[i]; 
    }				
  }
  /*	et maintenant on va calculer les solutions du système
   */
  void matricen_calculer_solutions() {
    int dbg=0;
    // alors pour k=m on a 1 terme x[m] = val[m][n]
    // pour k=m-1 on a  x[m-1] = val[m-1][n] - val[m-1][n-1]*x[m];
    // 					x[m-2] = val[m-2][n] - val[m-2][n-1]*x[m] - val[m-2][n-2]*x[m-1];
			
    //x[m-k]=val[(m-k)*n+n] - (x[m-k+1]*val[(m-k)*n+(n-k)]+x[m-k+2]*val[(m-k)*n+n-k+1]);	
    if (dbg) printf("m=%d\n",m);
    for (int k=1;k<=m;k++) {
      if (dbg) printf("k=%d\n",k);
      if (dbg) printf("x[%d]=val[%d][%d]",m-k,m-k,n-1);
      x[m-k]=val[(m-k)*n+(n-1)];
      for (int i=1;i<=k-1;i++) {
	//printf("i=%d\n", i);

	if (dbg) printf("-val[%d][%d]*x[%d]",m-k,n-(i+1),m-i);
	x[m-k]-=val[(m-k)*n+(n-(i+1))]*x[m-i];
      }
      if (dbg) printf("\n");
    }		
  }
  void afficher_solutions() {
    for (int i=0;i<m;i++) {
      printf("x[%d]=%f\n",i,x[i]);
    }
  }
  void verifier() {
    //val[n*l+c]
    //val_bak[n*l+c]
    //x[m]
    //x[0] + x[1]*val[0*m+1*n] + x[2]*val[0*m+2*n] = val[0*m+3*n];
    //x[1] + x[2]*val[[1*m+2*n] = val[1*m+3*n]
    //x[2] = val[2*m+3*n]

    x[2] =        val[2*n+3];
    x[1] = - x[2]*val[1*n+2] +      val[1*n+3];
    x[0] = - x[1]*val[0*n+1] - x[2]*val[0*n+2] + val[0*n+3];

    printf("les solutions du système\n");			
    printf("x0 %f\n",x[0]);
    printf("x1 %f\n",x[1]);
    printf("x2 %f\n",x[2]);

    printf("les valeurs obtenues en utilisant la matrice initiale\n");
    printf("%f\n", x[0]*val_bak[0*n+0] + x[1]*val_bak[0*n+1] + x[2]*val_bak[0*n+2]);
    printf("%f\n", x[0]*val_bak[1*n+0] + x[1]*val_bak[1*n+1] + x[2]*val_bak[1*n+2]);
    printf("%f\n", x[0]*val_bak[2*n+0] + x[1]*val_bak[2*n+1] + x[2]*val_bak[2*n+2]);
    printf("\n");

    printf("les valeurs obtenues en utilisant la matrice triangulée\n");
    printf("%f\n", x[0]*val[0*n+0] + x[1]*val[0*n+1] + x[2]*val[0*n+2]);
    printf("%f\n", x[0]*val[1*n+0] + x[1]*val[1*n+1] + x[2]*val[1*n+2]);
    printf("%f\n", x[0]*val[2*n+0] + x[1]*val[2*n+1] + x[2]*val[2*n+2]);
    printf("\n");

    matricen_calculer_solutions();			
    afficher_solutions();
  }
  int ligne_i_est_nulle(int i) {
    for (int k=0;k<m;k++) {
      if (abs(val[i*n+k]-0.0000000000000000000000001)>0) return 0;
    }
    return 1;
  }
  void trianguler() {
    int r=0;
    for (int j=0;j<m;j++) { // j décrit tous les indices de colonne, mais comme on veut pouvoir travailler avec une matrice non carré, on va juste 
      // aller jusqu'à m, ça devrait aller
      int lp=trouve_ligne_du_pivot_a_partir_de_la_ligne_et_pour_la_colonne(r,j);
      float pivot=val[lp*n+j];
      if (pivot!=0) {
	//afficher();
	mul_ligne_par_k(lp, 1.0/pivot); // on normalise la ligne du pivot de façon que le pivot prenne la valeur 1
					//printf("après multiplication par 1/%f\n",pivot);
					//afficher();  
	if (lp!=r) {
	  echanger_lignes(lp,r); // on place la ligne du pivot en position r						
	  //printf("après multiplication par 1/%f\n",pivot);
	}
	//afficher();

	for (int i=r+1;i<m;i++) { // on soustrait chaque ligne sous la ligne en cours de la ligne du pivot multipliée par la valeur de la colonne j
	  //printf("ligne %d moins ligne du pivot (%d qui est maintenant en %d) multipliée par la valeur en %d %d\n",i,lp,r,i,j);
	  extraire_ligne_aux_de_ligne(r);
	  mul_ligne_aux_par_k(val[i*n+j]);
	  soustraire_ligne_aux_de_ligne(i);
	  if (ligne_i_est_nulle(i)) {
	    printf("la matrice est singulière !\n");
	    exit(-1);
	  }
	  //printf("après soustraction de la ligne %d par la ligne du pivot correctement multipliée\n", i);
	  //afficher();
	}
	//afficher();

      }
      r++;

    }
  }
  void afficher_mi() {
    printf("afficher_mi\n");
    // on va l'afficher
    for (int l=0;l<m;l++) {
      for (int c=0;c<2*m;c++) {
	printf("%f\t",mi[l*2*n+c]);
      }
      printf("\n");
    }
  }
  void multiplier(float *mul) { // multiplier par matrice
    for (int l=0;l<m;l++) {
      for (int c=0;c<n;c++) {
	res[l*n+c]=0;
	for (int i=0;i<n;i++) {
	  res[l*n+c]+=val[l*n+i]*mul[i*n+c];
	}
      }
    }
    for (int l=0;l<m;l++) {
      for (int c=0;c<n;c++) {
	val[l*n+c]=res[l*n+c];
      }
    }
			
  }
  void vmul(float *mul, float *res) { // multiplier par vecteur
    for (int l=0; l<m; l++) {
      res[l]=0;
      for (int c=0; c<n; c++) {
	res[l]+=val[l*n+c]*mul[c];
      }
    }
  }
  void inverser() {
    /* on va pouvoir inverser la matrice */
    // on va rajouter 
    for (int l=0; l<m; l++) {
      for (int c=0; c<n; c++) {
	mi[l*2*n+c]=val[l*n+c];
      }
      for (int c=n; c<2*n; c++) {
	if (c-n == l) mi[l*2*n+c] = 1;
	else mi[l*2*n+c] = 0;
      }
    }
    printf("mi\n");	afficher_mi(); printf("\n");
		
    MatriceN *mati = new MatriceN(m,2*n,mi);
    mati->trianguler();
    printf("mi triangulé\n");	afficher_mi(); printf("\n");
    delete(mati);
    for (int j=m-2;j>=0;j--) {
      for (int i=m-1; i>j; i--) {
	dans_mi_extraire_ligne_aux_de_ligne(i);
	dans_mi_mul_ligne_aux_par_k(mi[j*2*n+i]);
	dans_mi_soustraire_ligne_aux_de_ligne(j);
	printf("mi en cours j:%d i:%d\n",j,i);	afficher_mi(); printf("\n");
      }
    }
    sauvegarder();
    for (int l=0;l<m;l++) {
      for (int c=0;c<n;c++) {
	val[l*n+c]=mi[l*2*n+c+n];
      }
    }
    //printf("mi inversé\n");	afficher_mi(); printf("\n");
    //printf("matrice inversée\n");	afficher(); printf("\n");
    MatriceN *matmul = new MatriceN(m,n,val_bak);
    matmul->multiplier(val);
    //matmul->afficher();
    delete(matmul);
  }
  void transposer() {
    for (int l=0;l<m;l++) {
      for (int c=0;c<n;c++) {
	val_bak[l*n+c]=val[c*n+l];
      }
    }
			
    for (int l=0;l<m;l++) {
      for (int c=0;c<n;c++) {
	val[l*n+c]=val_bak[l*n+c];
      }
    }
  }
  ~MatriceN() {
    free(ligne_aux);
    free(mi_ligne_aux);
    free(val_bak);
    free(res);
    free(x);
    free(mi);
  }	
};
class Spliner;
class Spliner {
public:
  int n;
  float *val;
  float *val_augmentee;
  MatriceN *mat;
  float *y; /* on a n points */
  float *yp; /* pour obtenir les n yp */

  float *aa; /* et en déduire */
  float *bb; /* les */
  float *cc; /* n-1 */
  float *dd; /* coefficients */


  void spliner_calcule_solutions() { // book7
    int dbg=0;
    // on va commencer par utiliser la matrice qui va bien et qu'on a trouvé sur le net, elle 
    // a été forgée par de grands forgerons formalistes

    val[0*n+0]=2; val[0*n+1]=1; for (int i=2;i<n;i++) val[0*n+i]=0; // voilà pour la première ligne

    int i=1;
    for (int offset=0;offset<n-2;offset ++) {
      for (int j=0;j<offset;j++) {
	val[i*n+j]=0;
      }
      val[(i*n)+offset]=1; val[(i*n)+offset+1]=4; val[(i*n)+offset+2]=1; 
      for (int j=offset+3;j<n;j++) {
	val[i*n+j]=0;
      }
      for (int i=0;i<n-2;i++) val[(n-1)*n+i]=0;	val[(n-1)*n+n-1-1]=1; val[(n-1)*n+n-1]=2;  //voilà pour la dernière ligne			
      i++;
    }
    /*	dans la série j'ai la flemme de réécrire le code précédent pour rajouter la dernière colonne, je vais 
	me faire un petit plaisir et ne pas optimiser ce code qui n'a même pas besoin de l'être  
	bien plaisir et hop je rajoute la colonne 
    */
    if (dbg) {
      printf("la matrice crée par des maitres forgerons.\n");
      for (int l=0;l<n;l++) {
	for (int c=0;c<n;c++) {
	  printf("%e\t",val[l*n+c]);
	}
	printf("\n");
      }
      printf("\n");
    }
    for (int l=0;l<n;l++) {
      for (int c=0;c<n;c++) {
	val_augmentee[l*(n+1)+c]=val[l*n+c];
      }
      if (l==0) {
	val_augmentee[l*(n+1)+n]=3*(y[1]-y[0]);
      } else 
	if (l==n-1) {
	  val_augmentee[l*(n+1)+n]=3*(y[n-1]-y[n-2]);					
	} else				
	  val_augmentee[l*(n+1)+n]=3*(y[l+1]-y[l-1]);
    }
    mat = new MatriceN(n,n+1,val_augmentee);
    if (dbg) {
      printf("la matrice augmentée de taille %d\n",n);
      mat->afficher();
    }
    // maintenant on va calculer les solutions grâce au trigonalisateur de matrice qu'on a fabriqué
    // sur les plans de génies anciens
    mat->matricen_calculer_solutions();

    /*	les solutions correspondent donc aux dérivés aux points de jonctions
     */
    for (int i=0;i<n;i++) {
      yp[i]=mat->x[i];
    }
    /*	on va mettre la dernière dérivé à zéro, ça ne gâche rien et c'est tranquille 
     */
    //yp[n]=0;
    /*	on a 2 courbes pour 3 points, on a donc n points pour n-1 courbes et n yp 
     */

    for (int i=0;i<n-1;i++) {
      aa[i]=y[i];
      bb[i]=yp[i];
      cc[i]=3*(y[i+1]-y[i]) - 2*yp[i]-yp[i+1];
      dd[i]=2*(y[i]-y[i+1]) + yp[i] + yp[i+1];
    }
    /*	et voilà on a les coefficients, les coefficients tant souhaités, les coefficients bien solides pour forger 
	des courbes, de superbes courbes, belles comme des femmes, solides comme l'éternité, belles comme des 
	aventures au paradis, de belles valeurs extraites du plus profond de la réalité
    */
  }
  Spliner(int nb_de_points, float *y) {
    //printf("Spliner \n");
    this->n=nb_de_points;
    this->y=y;
    this->yp=(float*)malloc(n*sizeof(float));			
    this->val_augmentee = (float *)malloc(n*(n+1)*sizeof(float));
    this->val = (float *)malloc(n*n*sizeof(float));
    this->aa=(float*)malloc((n-1)*sizeof(float));
    this->bb=(float*)malloc((n-1)*sizeof(float));
    this->cc=(float*)malloc((n-1)*sizeof(float));
    this->dd=(float*)malloc((n-1)*sizeof(float));

  }
  ~Spliner() {
    free(val);
    free(val_augmentee);
    free(yp);
    free(aa);
    free(bb);
    free(cc);
    free(dd);
  }
};

class SplinerXY {
public:

  Spliner *splX;
  Spliner *splY;
  int nb_de_points;
  float *x;
  float *y;
  float *tableau_des_distances_chordales;
  float *tableau_des_distances;
  SplinerXY(int nb_de_points, float *x, float *y) {
    /* alors on va créer la petite spline en X et en Y */
    splX = new Spliner(nb_de_points,x);
    splY = new Spliner(nb_de_points,y);
    splX->spliner_calcule_solutions();
    splY->spliner_calcule_solutions();
    this->nb_de_points=nb_de_points;
    this->x=x;
    this->y=y;
    this->tableau_des_distances=(float*)malloc((nb_de_points-1)*sizeof(float));
    this->tableau_des_distances_chordales=(float*)malloc((nb_de_points-1)*sizeof(float));						
  }
  void splinerxy_affiche() { // book8

    float distance_totale=0;
    float distance_max=FLT_MIN;
    for (int i=0;i<nb_de_points-1; i++) {
      tableau_des_distances[i]=sqrt( sqr(x[i+1]-x[i]) + sqr(y[i+1]-y[i]) );
      if (tableau_des_distances[i]>distance_max) {
	distance_max=tableau_des_distances[i];
      }
      distance_totale+=tableau_des_distances[i];
    }
    float distance_moyenne = distance_totale / (nb_de_points - 1);
    for (int i=0;i<nb_de_points-1; i++) {
      tableau_des_distances_chordales[i]=tableau_des_distances[i]/distance_max;// on ne s'en sert pas pour le moment				
    }
    for (int i=0;i<nb_de_points-1; i++) {
      int nb_de_points_par_portion_de_courbe=32;
      float inct = /*tableau_des_distances_chordales[i]*/ 1.0 / nb_de_points_par_portion_de_courbe;
      glBegin(GL_LINE_STRIP);
      glVertex3f(x[i], y[i], 0);
      for (float t=0;t<1;t+=inct) {
	float xt=splX->aa[i]+splX->bb[i]*t+splX->cc[i]*sqr(t)+splX->dd[i]*t*t*t;
	float yt=splY->aa[i]+splY->bb[i]*t+splY->cc[i]*sqr(t)+splY->dd[i]*t*t*t;
	glColor3ub(255, 255, 255 );
	glVertex3f(xt, yt, 0);
      }
      glVertex3f(x[i+1], y[i+1], 0);
      glEnd();
    }			
  }
  ~SplinerXY() {

    delete(splX);
    delete(splY);
    delete(tableau_des_distances);

    delete(tableau_des_distances_chordales);

  }
};
// alors un type vient de débarquer, il est méchant
class SplinerXYZ : public SplinerXY {	// book9
public:
  Spliner *splZ;
  float *z;
  const static int nb_de_points_par_portion_de_courbe=64;
  float **xt;
  float **yt;
  float **zt;
  float *xcoords;
  float *ycoords;
  float *zcoords;
  float *xcoordsnt;//xcoords not transformed
  float *ycoordsnt;
  float *zcoordsnt;
  int nb_de_points_de_la_courbe;
		
  float yplan=-1.7;

  float lightpos[3]={0,3,0};
  int numcolor; // la couleur du plan où l'on projette l'ombre
  int numcolorquadrillage;
  //book
	
  void calcule_splinerXYZ(GLfloat modelview[16]) { // Calculateur de Spline en 3D
    //modelview = {1,0,0,0,  0,1,0,0  0,0,1,0};
    MatriceN *mat = new MatriceN(4,4,modelview); // Trampoline
    mat->transposer(); // Mon cher transposeur
    float coord[4];
    float res[4];
    int j=0;
    for (int i=0;i<nb_de_points-1; i++) {
      float inct = 1.0 / nb_de_points_par_portion_de_courbe;
      float vec[3];
      vec[0]=x[i];
      vec[1]=y[i];
      vec[2]=z[i];
      mat->vmul(vec, res);
      xcoords[j]=res[0];
      ycoords[j]=res[1];
      zcoords[j]=res[2];

      // faudra que je m'explique l'intérêt de ces 3 lignes, je pense les virer
      //xcoords[j]=vec[0];
      //ycoords[j]=vec[1];
      //zcoords[j]=vec[2];
      //

      xcoordsnt[j]=vec[0];
      ycoordsnt[j]=vec[1];
      zcoordsnt[j]=vec[2];

      int ti=0;
      float t=0;

      for (int k=0;k<nb_de_points_par_portion_de_courbe-1; k++) {
	coord[0]=splX->aa[i]+splX->bb[i]*t+splX->cc[i]*sqr(t)+splX->dd[i]*t*t*t;
	coord[1]=splY->aa[i]+splY->bb[i]*t+splY->cc[i]*sqr(t)+splY->dd[i]*t*t*t;
	coord[2]=splZ->aa[i]+splZ->bb[i]*t+splZ->cc[i]*sqr(t)+splZ->dd[i]*t*t*t;
	coord[3]=1;
	mat->vmul(coord, res);
	xt[i][ti]=res[0];
	yt[i][ti]=res[1];
	zt[i][ti]=res[2];
	
	xcoords[j]=res[0];
	ycoords[j]=res[1];
	zcoords[j]=res[2];
					
	xcoordsnt[j]=coord[0];
	ycoordsnt[j]=coord[1];
	zcoordsnt[j]=coord[2];
	//xcoords[j]=coord[0];
	//ycoords[j]=coord[1];
	//zcoords[j]=coord[2];

	ti++;
	j++;
	t+=inct;
      }
    }
    delete(mat);	
  }
  void affiche_splinerXYZ() {
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    for (int i=0;i<(nb_de_points-1)*(nb_de_points_par_portion_de_courbe-1); i++) {
      glColor3ub(255, 255, 255 );
      glVertex3f(xcoords[i], ycoords[i], zcoords[i]);
    }
    glEnd();
    // pourquoi je fais ça ? parce que ça me rend heureux. à la différence du joueur, celui qui construit
    // n'envoie pas en permanence la même intention autour de lui : perds. 
    glPointSize(2);
    affiche_plan_splinerXYZ();
    affiche_ombre_splinerXYZ();
    //glLoadIdentity();

  }
  void affiche_ombre_splinerXYZ() {
    glLineWidth(2);
    glDisable(GL_BLEND);
    // l'ombre
    glBegin(GL_LINE_STRIP); //book4
    for (int i=0;i<(nb_de_points-1)*(nb_de_points_par_portion_de_courbe-1); i++) {
      glColor3ub(0, 0, 0 );			
      float vecx = xcoords[i] - lightpos[0];
      float vecy = ycoords[i] - lightpos[1];
      float vecz = zcoords[i] - lightpos[2];
      float norm = sqrt(vecx*vecx + vecy*vecy + vecz*vecz);//kdp frein de differentiel de potentiel, tandis que l'autre est une force de rappel sur le potentiel donc c'est un -kp autre dit un -kV et le premier un k1*dV autrement dit le premier est un k1*dV/dt et le 2eme un -k2*V/dt, V=RI à nouveau dans tout le circuit donc le premier qui est la nouvelle tension autrement Vn+1=-k2*Vn et le 2ème Vn+1=k1*dVn on a donc une force de rappel de la tension et une force de freinage donc Vn+1=V0-k2*Vn et dVn+1=dV0+k1*dVn avec dV0 l'amplitude du signal oscillant
      if (norm > 0.00000000001) {
	float kx = vecx / norm;
	float ky = vecy / norm;
	float kz = vecz / norm;
	float tsol = (yplan / ky);
	float xp = kx * tsol;
	float yp = yplan;
	float zp = kz * tsol;
				
	glVertex3f(xp, yp+0.01, zp);

      } else {
	glVertex3f(xcoords[i], ycoords[i], zcoords[i]);
      }
					
    }
    glEnd();
    glEnable(GL_BLEND);

  }
  void affiche_plan_splinerXYZ() {
    float xmin=-10;
    float zmin=-5;
    float xmax=10;
    float zmax=4;
    float yval=yplan-0.1;
    glPushMatrix();
    glTranslatef(0,0,ztranslate-1);
    glBegin(GL_QUADS);  // Le plan
    glColor3ub(255,255,255);
    glVertex3f(xmin,yplan-0.1,zmax);
    glColor3ub(255,255,255);
    glVertex3f(xmax,yplan-0.1,zmax);
    glColor3ub(comp(numcolor));
    glVertex3f(xmax,yplan-0.1,zmin);
    glColor3ub(comp(numcolor));
    glVertex3f(xmin,yplan-0.1,zmin);
    glEnd();
    // Quadrillage
    float nx=25;
    float nz=10;
    float y=yval+0.01;
    float incx=(xmax-xmin)/nx;
    float incz=(zmax-zmin)/nz;
    float x=xmin;
    for (int i=0;i<nx;i++) {
      float z=zmin;	
      for (int j=0;j<nz;j++) {
	if ((i+j)%2 == 0) {
	  glBegin(GL_QUADS);
	  //glColor3ub(compub(int(12*myrand())));
	  glColor3ub(compub(numcolorquadrillage));
	  glVertex3f(x,y,z);
	  glVertex3f(x+incx,y,z);
	  glVertex3f(x+incx,y,z+incz);
	  glVertex3f(x,y,z+incz);
	  glEnd();
	}
	z+=incz;
      }
      x+=incx;
    }
    glPopMatrix();
  }
  SplinerXYZ(int nb_de_points, float *x, float *y, float *z) : SplinerXY(nb_de_points, x, y) {

    nb_de_points_de_la_courbe=(nb_de_points-1)*(nb_de_points_par_portion_de_courbe-1);
    splX = new Spliner(nb_de_points,x);
    splY = new Spliner(nb_de_points,y);
    splZ = new Spliner(nb_de_points,z);
    splX->spliner_calcule_solutions();
    splY->spliner_calcule_solutions();
    splZ->spliner_calcule_solutions();
    this->nb_de_points=nb_de_points;
    this->x = x;
    this->y = y;
    this->z = z;
    xt = (float**)malloc(sizeof(float*)*nb_de_points);
    yt = (float**)malloc(sizeof(float*)*nb_de_points);
    zt = (float**)malloc(sizeof(float*)*nb_de_points);

    for (int i=0;i<nb_de_points;i++) {
      xt[i]=(float*)malloc(sizeof(float)*nb_de_points_par_portion_de_courbe);
      yt[i]=(float*)malloc(sizeof(float)*nb_de_points_par_portion_de_courbe);
      zt[i]=(float*)malloc(sizeof(float)*nb_de_points_par_portion_de_courbe);
    }
    // je vais être tellement bien à calculer mes cuboïds, avec d'abord une petite version sans détection des collisions et ensuite des comparaisons
    // amoureusement craftées pour icelles

    // Accordéon
    xcoords = (float*)malloc(sizeof(float)*nb_de_points*(nb_de_points_par_portion_de_courbe-1));
    ycoords = (float*)malloc(sizeof(float)*nb_de_points*(nb_de_points_par_portion_de_courbe-1));
    zcoords = (float*)malloc(sizeof(float)*nb_de_points*(nb_de_points_par_portion_de_courbe-1));
	
    xcoordsnt = (float*)malloc(sizeof(float)*nb_de_points*(nb_de_points_par_portion_de_courbe-1));
    ycoordsnt = (float*)malloc(sizeof(float)*nb_de_points*(nb_de_points_par_portion_de_courbe-1));
    zcoordsnt = (float*)malloc(sizeof(float)*nb_de_points*(nb_de_points_par_portion_de_courbe-1));
	
    numcolor=int(12*myrand());
    numcolorquadrillage=numcolor;
    while (numcolor==numcolorquadrillage) {
      numcolorquadrillage=int(12*myrand());
    }

  }

  ~SplinerXYZ() {
    for (int i=0;i<nb_de_points;i++) {
      delete(xt[i]);
      delete(yt[i]);
      delete(zt[i]);
    }
    delete(xt);
    delete(yt);
    delete(zt);
    delete(xcoords);
    delete(ycoords);
    delete(zcoords);
    delete(xcoordsnt);
    delete(ycoordsnt);
    delete(zcoordsnt);
	
  }
  /*
    programmer, je veux dire jouer à créer pour un ordinateur, je veux dire, pour une machine de turing apporte 
    toujours quelquechose : du bonheur
  */
};
class Courbe3D { // book10
public:
  float *valx;
  float *valy;
  float *valz;
  float xmin,xmax,ymin,ymax,znear,zfar;

  int nb_de_points;
  SplinerXYZ *spliner;
  Courbe3D(int nb_de_points) {
    this->nb_de_points=nb_de_points;
    valx = (float*)malloc(nb_de_points*sizeof(float));
    valy = (float*)malloc(nb_de_points*sizeof(float));
    valz = (float*)malloc(nb_de_points*sizeof(float));
    for (int i=0;i<nb_de_points;i++) {
      valx[i] = (1-2*myrand());
      valy[i] = (1-2*myrand());
      valz[i] = (1-2*myrand());
    }
    spliner = new SplinerXYZ(nb_de_points, valx, valy, valz);
    this->xmin = -1;
    this->xmax = 1;
    this->ymin = -1;
    this->ymax = 1;
    this->znear = 1;
    this->zfar = 10;

  }
  /* erreur de débutant, dériver les classes au lieu de passer leur instance en paramètres */
  void set_modelview_matrix(int immobile=0) {
    glLoadIdentity();

    glTranslatef(0.0, 0.0, ztranslate-1); // on déplace le monde vers l'avant 
    // c'était tellement bon ce moment
    // alors on a un moteur et bientôt on en aura 3 de plus, donc allons faire 3 moteurs, hop hop hop
    // voilà, on a fait les 3 moteurs supplémentaire, alors bon maintenant il s'agirait de s'en
    // servir, on va les initialiser à l'arrêt
    // donc chaque moteur est associé à une rotation selon un axe
    // si on joue une note paire il tourne dans un sens,
    // si on joue une note impaire il tourne dans l'autre sens
    // si random de 1 > 0.8 alors on éteint ces 3 moteurs et on rallume aleatoirement l'un 
    // d'eux, on a un pointeur sur l'increment de moteur actif en cours
    // je veux que l'objet tourne en permanence selon un axe, dans un sens ou dans un autre
    // en fonction de la parité de la note en cours

    if (!immobile) {

      calcul_matrice_deplacement_en_fonction_des_notes_et_de_la_partnum();
      if (0) {
	float vx,vy,vz;
	if (myrand()>0.99) {
	  inc_moteur1=0; inc_moteur2=0; inc_moteur3=0;
	  float rr=myrand();
	  if (rr>0.6) {
	    inc_moteur_en_cours=&inc_moteur1;
	  } else if (rr>0.3) {
	    inc_moteur_en_cours=&inc_moteur2;
	  } else if (rr>0) {
	    inc_moteur_en_cours=&inc_moteur3;
	  }
	}
	int n=note_en_cours();
	if ((n==0) || (n==4) || (n==7) || (n==11)) {
	  *inc_moteur_en_cours=+1;
	} else if ((n==2) || (n==5) || (n==9)) {
	  *inc_moteur_en_cours=-1;
	}
	glRotatef(moteur1 % 360, 1, 0, 0);
	glRotatef(moteur2 % 360, 0, 1, 0);
	glRotatef(moteur3 % 360, 0, 0, 1);
      }
    }
  }
  void calcule_courbe3D(int immobile) {
    GLfloat mm[16];
    //book2 appel de la fonction de calcul du splinerXYZ, on veut mettre ici le "moteur"
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    set_modelview_matrix(immobile);
    glGetFloatv(GL_MODELVIEW_MATRIX,mm);  
    spliner->calcule_splinerXYZ(mm); //Escargot
    glPopMatrix();
  }
  void affiche_courbe3D() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glFrustum(xmin, xmax, ymin, ymax, znear, zfar);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
 

    // pour voir depuis le point (0,0,0) qui est là où se trouve la caméra
    //bookmodelview
			
    glPointSize(8);

    spliner->affiche_splinerXYZ();
    spliner->affiche_plan_splinerXYZ();
    spliner->affiche_ombre_splinerXYZ();
			

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

  }

  ~Courbe3D() {
    delete(valx);
    delete(valy);
    delete(valz);
    delete(spliner);
  }
};
void normaliser(float *V) {
  float n=sqrt(sqr(V[0])+sqr(V[1])+sqr(V[2]));
  V[0]=V[0]/n;
  V[1]=V[1]/n;
  V[2]=V[2]/n;
}
void affiche_vecteur(float x0,float y0, float z0, float *v, float rr, float vv, float bb) {
  glBegin(GL_LINES);
  glColor3f(rr,vv,bb);
  glVertex3f(x0,y0,z0);
  glVertex3f(x0+v[0], y0+v[1], z0+v[2]);
  glEnd();
}
class Sweeper {
  int nb_points_chemin_par_segment=3;

  int nb_segments;
  float xmin,xmax,ymin,ymax,znear,zfar;
  int nb_points_contour;
  Courbe3D *chemin;
  float **contour;
  float *xcoords;
  float *ycoords;
  float *zcoords;
  float *thetaB;
  float *distancesBarycentreSommets;
  int nb_points_chemin;
  float xbarycentrecontour;
  float ybarycentrecontour;
  float zbarycentrecontour;
  float **coordspipelastcontour;
  float **coordspipe;
  float *V1;
  float *V2;
  float *V3;
  int nb_coordspipe;

public:
  Sweeper(float **contour, int nb_coords_contour, Courbe3D *chemin) {
    this->xmin = -1;
    this->xmax = 1;
    this->ymin = -1;
    this->ymax = 1;
    this->znear = 1;
    this->zfar = 10;


    this->contour=contour;
    this->chemin=chemin;
    this->nb_points_contour=nb_coords_contour;
    this->xcoords=this->chemin->spliner->xcoordsnt;
    this->ycoords=this->chemin->spliner->ycoordsnt;
    this->zcoords=this->chemin->spliner->zcoordsnt;
    this->nb_points_chemin=this->chemin->spliner->nb_de_points_de_la_courbe;
    this->nb_segments=nb_points_chemin / nb_points_chemin_par_segment;
    this->thetaB=(float*)malloc(sizeof(float)*this->nb_points_contour);
    this->distancesBarycentreSommets=(float*)malloc(sizeof(float)*this->nb_points_contour);
    this->coordspipe=(float**)malloc((nb_segments+1)*nb_points_contour*sizeof(float*));
    this->coordspipelastcontour=(float**)malloc(nb_points_contour*sizeof(float*));
    for (int i=0;i<(nb_segments+1)*nb_points_contour;i++) {
      this->coordspipe[i]=(float*)malloc(sizeof(float)*3);
    }
    for (int i=0;i<nb_points_contour;i++) {
      this->coordspipelastcontour[i]=(float*)malloc(sizeof(float)*3);
    }
    printf("Alors, j'ai juste envie de savoir si la machine arrive à cet endroit là.\n");
    V1=(float*)malloc(3*sizeof(float));
    V2=(float*)malloc(3*sizeof(float));
    V3=(float*)malloc(3*sizeof(float));

    calculer_coordonnees_barycentre_contour();

    calculer_thetaB();
    calculer_distancesBarycentreSommets();
    printf("Xor le sheriff, sheriff de l'espace\n");
  }
  int calculer_distancesBarycentreSommets() {
    for (int i=0;i<nb_points_contour;i++) {
      distancesBarycentreSommets[i]=sqrt( sqr(contour[i][0]-xbarycentrecontour) + 
					  sqr(contour[i][1]-ybarycentrecontour) + 
					  sqr(contour[i][2]-zbarycentrecontour));
    }
  }
  // et maintenant je dois aller chercher dans mon coffre aux trésors la précieuse information
  int calculer_coordonnees_barycentre_contour() {
    float sommeX=0;
    float sommeY=0;
    float sommeZ=0;
    for (int i=0;i<nb_points_contour;i++) {
      sommeX+=this->contour[i][0];
      sommeY+=this->contour[i][1];
      sommeZ+=this->contour[i][2];
    }
    this->xbarycentrecontour=sommeX / nb_points_contour;
    this->ybarycentrecontour=sommeY / nb_points_contour;
    this->zbarycentrecontour=sommeZ / nb_points_contour;
    printf("barycentre : %f %f %f\n",this->xbarycentrecontour,this->ybarycentrecontour,this->zbarycentrecontour);
  }
  int calculer_thetaB() {
    float xB=xbarycentrecontour;
    float yB=ybarycentrecontour;
    float zB=zbarycentrecontour;
    float xA,yA,zA;
    float xC,yC,zC;
    for (int i=0;i<nb_points_contour;i++) {
      xA=contour[i][0];
      yA=contour[i][1];
      zA=contour[i][2];
      if (i==nb_points_contour-1) {
	xC=contour[0][0];
	yC=contour[0][1];
	zC=contour[0][2];
      } else {
	xC=contour[i+1][0];
	yC=contour[i+1][1];
	zC=contour[i+1][2];
      }
      thetaB[i]=acos( ((xA-xB)*(xC-xB)+(yA-yB)*(yC-yB)+(zA-zB)*(zC-zB)) / 
		      (sqrt(sqr(xA-xB)+sqr(yA-yB)+sqr(zA-zB))*sqrt(sqr(xC-xB)+sqr(yC-yB)+sqr(zC-zB))));
      //	printf("thetaB %i %f\n",i,thetaB[i]);
    }
  }

  void pushincoordspipe(float xsommet, float ysommet, float zsommet) {
    coordspipe[nb_coordspipe][0]=xsommet;
    coordspipe[nb_coordspipe][1]=ysommet;
    coordspipe[nb_coordspipe][2]=zsommet;
    nb_coordspipe++;
  }
		 
  void calculer_sweeper() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glFrustum(xmin, xmax, ymin, ymax, znear, zfar);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
	
    nb_coordspipe=0;
    //alors il faut calculer une équation du plan donc on prend 2 points de la courbe
    //préalablement on divise la courbe en un certain nombre de portions
    //on prend 2 points, on crée un vecteur,
    float nb_points_par_portion_de_courbe=(float)nb_points_chemin / nb_segments;
    printf("nb points par portion de courbe %f\n",nb_points_par_portion_de_courbe);
    for (int i=0;i<nb_segments;i++) {
      float xB,yB,zB;
      float xA=xcoords[(int)(nb_points_par_portion_de_courbe*i)];
      float yA=ycoords[(int)(nb_points_par_portion_de_courbe*i)];
      float zA=zcoords[(int)(nb_points_par_portion_de_courbe*i)];
      if (i==nb_segments-1) {
	xB=xcoords[nb_points_chemin-1];
	yB=ycoords[nb_points_chemin-1];
	zB=zcoords[nb_points_chemin-1];
      } else {
	xB=xcoords[(int)(nb_points_par_portion_de_courbe*(i+1))];
	yB=ycoords[(int)(nb_points_par_portion_de_courbe*(i+1))];
	zB=zcoords[(int)(nb_points_par_portion_de_courbe*(i+1))];
      }
      // nb points par portion de courbe
      V2[0]=xB-xA;
      V2[1]=yB-yA;
      V2[2]=zB-zA;
      normaliser(V2);
	
      V1[0]=V2[2];
      V1[1]=0;
      //le merveilleux point qui appartient au plan auquel le vecteur est normal
      V1[2]=-V2[0];//(xA*xB-xA*xA+yA*yB-yA*yA+zA*zB-zA*zA)/(zB-zA);
      if (abs(zB-zA)<0.01) {					
	V1[0]=0;
	V1[1]=V2[2];
	V1[2]=-V2[1];
      }
      normaliser(V1);
      //affiche_vecteur(xA,yA,zA,V1,1,0,0);
      //affiche_vecteur(xA,yA,zA,V2,0,1,0);
      V3[0]= (V1[1]*V2[2] - V1[2]*V2[1]);
      V3[1]=-(V1[0]*V2[2] - V1[2]*V2[0]);
      V3[2]= (V1[0]*V2[1] - V1[1]*V2[0]);
      normaliser(V3);
      //affiche_vecteur(xA,yA,zA,V3,0,0,1);
      float thetatotal=0;
			
      for (int j=0;j<nb_points_contour;j++) {
	float d=distancesBarycentreSommets[j];
	thetatotal+=thetaB[j];

	float xsommet=d*cos(thetatotal)*V1[0]+d*sin(thetatotal)*V3[0]+xA;
	float ysommet=d*cos(thetatotal)*V1[1]+d*sin(thetatotal)*V3[1]+yA;
	float zsommet=d*cos(thetatotal)*V1[2]+d*sin(thetatotal)*V3[2]+zA;
	pushincoordspipe(xsommet,ysommet,zsommet);
				
	if (i==nb_segments-1) {
	  coordspipelastcontour[j][0]=xsommet+(xB-xA);
	  coordspipelastcontour[j][1]=ysommet+(yB-yA);
	  coordspipelastcontour[j][2]=zsommet+(zB-zA);
	}
      }
      //	printf("thetatotal final : %f\n", thetatotal*360.0 / (2*PI)); 
    }
    for (int j=0;j<nb_points_contour;j++) {
      pushincoordspipe(coordspipelastcontour[j][0],coordspipelastcontour[j][1],coordspipelastcontour[j][2]);
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
  }
  float cpx(int i, int j) {
    if (j>nb_points_contour-1)
      return(coordspipe[i*nb_points_contour+0][0]);
    else
      return(coordspipe[i*nb_points_contour+j][0]);
  }
  float cpy(int i, int j) {
    if (j>nb_points_contour-1)
      return(coordspipe[i*nb_points_contour+0][1]);
    else
      return(coordspipe[i*nb_points_contour+j][1]);
  }
  float cpz(int i, int j) {
    if (j>nb_points_contour-1)
      return(coordspipe[i*nb_points_contour+0][2]);
    else
      return(coordspipe[i*nb_points_contour+j][2]);
  }
  void afficher_sweeper(int immobile, int dontmodifymodelview) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glFrustum(xmin, xmax, ymin, ymax, znear, zfar);


    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    if (!dontmodifymodelview) {
      this->chemin->set_modelview_matrix(immobile);//ça rotate et translate de la même maniere pour que les deux formes coincident
    }
    //ça rotate et ça translate mais ça le fait en fonction des entrées piano si on ne veut pas que cette foutue 
    //courbe reste immobile, donc on va 

			 
    glLineWidth(2);
    //la machine me donne quelquechose à faire, comme une maitresse, objectifs sur objectifs, 
    //et elle m'offre un espace de créativité et de résolutions de défis sans limites
    //donc là je cherche où le programme plante
    for (int i=0;i<nb_segments;i++) {
			
      glBegin(GL_LINE_STRIP);
      glColor3f(1,0,0);
      for (int j=0;j<nb_points_contour;j++) {
	glVertex3f(cpx(i,j),cpy(i,j),cpz(i,j));
      }
      glVertex3f(cpx(i,0),cpy(i,0),cpz(i,0));	
      glEnd();
			
      // le gens ont envie de causer, j'ai envie de causer afin d'atteindre un objectif précis
      // les gens qui n'ont pas d'objectif précis ont tendance à vivre dans leurs souvenirs
      // ma copine que je tatoue, elle a un corps très vaste, plein d'organes, j'y suis nomade
      // je m'y déplace, j'y place des repères, je peux meme m'y téléporter en y recherchant
      // quelquechose
      // les gens veulent qu'on leur apporte quelquechose, on m'apporte de l'argent, ma machine
      // m'apporte ce que je lui demande de m'apporter
      glDisable(GL_BLEND);
      glEnable(GL_LIGHTING);
      for (int j=0;j<nb_points_contour;j++) {
	glBegin(GL_QUADS);
	glColor3f(1,0,0);

	float nor[3];
	float A[3];
	A[0]=cpx(i,j);
	A[1]=cpy(i,j);
	A[2]=cpz(i,j);
	float B[3];
	B[0]=cpx(i,j+1);
	B[1]=cpy(i,j+1);
	B[2]=cpz(i,j+1);
	float D[3];
	D[0]=cpx(i+1,j);
	D[1]=cpy(i+1,j);
	D[2]=cpy(i+1,j);
	
	// ma machine tatouée me réserve une surprise, c'est un cyborg, on travaille
	// tous les deux, je dois tester si la nouvelle modification que je lui ai apporté
	// fonctionne. j'ai peur
	pvec(B[0]-A[0],B[1]-A[1],B[2]-A[2], D[0]-A[0], D[1]-A[1], D[2]-A[2], nor);

	glNormal3f(nor[0],nor[1],nor[2]);
	glVertex3f(cpx(i,j),cpy(i,j),cpz(i,j));
	glVertex3f(cpx(i,j+1),cpy(i,j+1),cpz(i,j+1));
	glVertex3f(cpx(i+1,j+1),cpy(i+1,j+1),cpz(i+1,j+1));
	glVertex3f(cpx(i+1,j),cpy(i+1,j),cpz(i+1,j));						
	glEnd();
      }
      glDisable(GL_LIGHTING);
				
    }
    //
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
  }
  ~Sweeper() {
    for (int i=0;i<(nb_segments+1)*nb_points_contour;i++) {
      free(coordspipe[i]);
    }
    for (int i=0;i<nb_points_contour;i++) {
      free(coordspipelastcontour[i]);
    }
    free(coordspipe);
    free(thetaB);
    free(distancesBarycentreSommets);
    free(V1);
    free(V2);
    free(V3);

  }
};
Sweeper *sweeper;
Courbe3D *courbe3Dtosweep;

// retourne la position en x,y,z d'un point en x,y (z=0) à l'écran 
Vecteur get3Dpos(int x, int y, int z, Vecteur *v) {
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLfloat winX, winY, winZ;
  GLdouble posX, posY, posZ;

  GLfloat m[16];
  GLfloat mp[16];
  GLfloat mm[16];
  glMatrixMode(GL_PROJECTION);

  glPushMatrix();

  glLoadIdentity();
  glFrustum(-1, 1, -1, 1,  1/*-znear*/, 3/*-zfar*/); 

  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
	
  glLoadIdentity();
  glGetFloatv(GL_PROJECTION_MATRIX,mp);
  /*
    printf("projection matrix\n");
    printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
    mp[0],mp[1],mp[2],mp[3],mp[4],mp[5],mp[6],mp[7],mp[8],mp[9],mp[10],mp[11],mp[12],mp[13],mp[14],mp[15]);
  */
  glGetFloatv(GL_MODELVIEW_MATRIX,mm);  
  /*
    printf("modelview matrix\n");
    printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
    mm[0],mm[1],mm[2],mm[3],mm[4],mm[5],mm[6],mm[7],mm[8],mm[9],mm[10],mm[11],mm[12],mm[13],mm[14],mm[15]);
  */
  /* on va les multiplier, ça va être incroyable, c'est le bonheur cette multiplication */
  /* alors tout d'abord on va créer une instance de MatriceN */
  MatriceN *matn = new MatriceN(4, 4, mp);
  /* alors on va multiplier par quoi, c'est le mv en premier sur les modeles donc mp*mv */
  matn->multiplier(mm);
  matn->inverser();
  float vec[4];
  /* on a un petit vecteur qui va correspondre à un point à l'écran */
  /* les blaireaux qui veulent quelquechose d'impossible à atteindre comme par exemple un plan à y constant, chaud de se dire que c'est 
     possible sauf que c'est impossible
     donc maintenant on veut juste afficher le plan 
  */
  /*
    GLdouble md[16];
    glGetDoublev(GL_MODELVIEW_MATRIX,md);  
    printf("modelview matrix en double par md\n");
    printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
    md[0],md[1],md[2],md[3],md[4],md[5],md[6],md[7],md[8],md[9],md[10],md[11],md[12],md[13],md[14],md[15]);
  */


  //	printf("modelview matrix en double\n");
  //	MatriceN *mat = new MatriceN(4,4,(float *)modelview);
  //	mat->afficher();
  //	delete(mat);



  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);
  winX = (float)x;
  winY = (float)viewport[3] - (float)y;
  winZ = (float)z;
  // alors j'ai un jouet, c'est cette fonction, mais je ne sais pas bien ce qu'elle fait, il me semble
  // qu'on lui passe 3 coordonnées à l'écran, avec un winZ qui doit être la coordonnée du point
  // dans le depthbuffer, et elle retourne à quoi correspond ces coordonnées dans l'espace en 3D

  gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);


  //	gluUnProject(0, 0, 0, modelview, projection, viewport, &posX, &posY, &posZ); // => -1, -1, -1

  //	gluUnProject(0, 0,-1, modelview, projection, viewport, &posX, &posY, &posZ); // => -1, -1, -3

  //	gluUnProject(0, 0,-2, modelview, projection, viewport, &posX, &posY, &posZ); // => -1, -1, -5

  //	gluUnProject(0, 0,-3, modelview, projection, viewport, &posX, &posY, &posZ); // => -1, -1, -7

  //	gluUnProject(0, 0,-4, modelview, projection, viewport, &posX, &posY, &posZ); // => -1, -1, -7

  //	gluUnProject(0, 0,-5, modelview, projection, viewport, &posX, &posY, &posZ); // => -1, -1, -11

  //	gluUnProject(viewport[2], 0, 0, modelview, projection, viewport, &posX, &posY, &posZ); // => -1, -1, -11

  rprintf("posX:%f\n",posX);	rprintf("posY:%f\n",posY); rprintf("posZ:%f\n",posZ);

  //	rprintf("posX:%d\n",v.x);	rprintf("v.y:%d\n",v.y); rprintf("v.z:%d\n",v.z);			

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  return v->set(posX, posY, posZ);
}
int test_matN() {
  //	double val[] = {1, 2, 3, 4,  1, 2, 3, 4,  9, 11, 10, 15}; //,  13, 14, 15, 16};
  //float val[] = {1, 2, 3, 4,  8, 6, 7, 5,  9, 11, 10, 15}; //,  13, 14, 15, 16};

  float val[] = {1, 2, 3,  8, 6, 18,  19, 11, 10}; //,  13, 14, 15, 16};
  //	float val[] = {1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1}; //,  13, 14, 15, 16};
  //	float val[] = {1, 1, 1, 2,  0, 1, 0, 3,  0, 0, 1, 4}; //,  13, 14, 15, 16};

  MatriceN *mat = new MatriceN(3, 3, val);
  mat->sauvegarder();
  printf("la matrice initiale\n");
  mat->afficher();
  mat->inverser();
  exit(-1);
  /*
    mat->echanger_lignes(0,1);
    mat->afficher();
    mat->mul_ligne_par_k(0,2);
    mat->afficher();
    mat->soustraire_ligne_de_ligne(0,1);
    mat->afficher();
    int *i = (int*)malloc(sizeof(int));
    (*i) = 2;
    int *j;
    int ligne_du_pivot=mat->trouve_ligne_du_pivot_a_partir_de_la_ligne_et_pour_la_colonne(3,1);
    printf("%d\n", ligne_du_pivot);
  */
  mat->trianguler();
  printf("la matrice triangulée\n");
  mat->afficher();
  mat->verifier();
	
  //	Spliner *spl=new Spliner(3);
  //	spl->make_matrice();
  exit(-1);
}
class Gestionnaire_de_particules {
public:
  Liste<Particule> *l_particules_vivantes;
  Gestionnaire_de_particules() {
    l_particules_vivantes = new Liste<Particule>();
  }
				
  void ajouter_particule(Particule *p) {
    l_particules_vivantes->liste_ajouter(new Maille<Particule>(p));
  }
  void enlever_particule(Particule *p) {
    l_particules_vivantes->liste_enlever(p);
  }
  void evolue() {
    /* on va simplement parcourir la liste des particules vivantes et faire évoluer chacune d'entre elle, sachant que si la particule n'évolue pas c'est qu'elle est morte, auquel cas, on l'enlève de la liste des particules vivantes et on l'ajoue à la liste des particules mortes */
    Maille<Particule> *p=l_particules_vivantes->premier;
    while (p!=NULL) {
      if (!p->ptr->particule_evolue()) {
	l_particules_vivantes->liste_enlever(p);
	delete(p);
      }
      p=p->suivant;
    }
  }
  virtual void affiche() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    if (premierevbl) {GLfloat m[16]; glGetFloatv(GL_PROJECTION_MATRIX,m); printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);}
  
    glMatrixMode(GL_MODELVIEW); 
    glPushMatrix();
    glLoadIdentity();
    //glRotatef(vbl % 360, 0, 1, 0); // qui marche donc on a pas besoin de translater le monde

    glDisable(GL_LIGHTING);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Maille<Particule> *p=l_particules_vivantes->premier;

    while (p!=NULL) {
      p->ptr->particule_affiche(); /* la superbe methode surchargeable */				
      p=p->suivant; 
    }

    glDisable(GL_BLEND); 
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

  }

};
Gestionnaire_de_particules *gp; 

/*
  la petite sous-classe du gestionnaire de particules avec une méthode d'affichage surchargeante qui ne modifie pes les
  matrices d'affichage
*/

/*
  et donc on a le petit gestionnaire de particule version 2.0
*/
// une sous classe du gestionnaire de particule qui ne redefinit pas les matrices de projection
// et de transformation lors de l'affichage. il sert pour la sphere de particule et pour le pastillage autrement dit
// le vaisseau qui tire dans des pastilles 
class Gestionnaire_de_particules_free_display : public Gestionnaire_de_particules {
public:
  //Gestionnaire_de_particules_free_display();
  void affiche() {
    glEnable(GL_BLEND);
    Maille<Particule> *p=l_particules_vivantes->premier;
    if (myrand() < 0.001) printf("nombre de particules :%d\n",l_particules_vivantes->nb_elements);
    while (p!=NULL) {
      p->ptr->particule_affiche(); /* la superbe methode surchargeable */				
      p=p->suivant; 
    }
    glDisable(GL_BLEND);
  }
		
};
Gestionnaire_de_particules_free_display *gpfd;
void ballon_ajoute_de_la_particule_en(float x0, float y0, float z0, Palette *palette, int lifetime, float scale, Gestionnaire_de_particules_free_display *gpfd) {
  gpfd->ajouter_particule(new Particule(
					new Vecteur(/*posx*/x0+0.1*(0.5-myrand()),/*posy*/y0+0.1*(0.5-myrand()),/*posz*/z0+0.1*(0.5-myrand())), 
					new Vecteur(/*vitx*/0*(0.5-myrand()),/*vity*/0*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/360*myrand()), 
					new Vecteur(/*vrotx*/0*1*(0.5-myrand()),/*vroty*/0*1*(0.5-myrand()), /*vrotz*/0*(0.5-myrand())), 
					/*couleur*/4,/*alpha*/16,/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,/*lifetime*/lifetime,/*scale*/scale,/*palette*/palette)
			  );
}
class Matrice4 {
public:
  float *m;
  Matrice4() {
  }
  Matrice4(float *m) {
    this->m=m;
  }
  void mul(float *vec, float *res) {
    res[0]=m[0]*vec[0]+ m[1]* vec[1]+m[2]* vec[2]+m[3]* vec[3];
    res[1]=m[4]*vec[0]+ m[5]* vec[1]+m[6]* vec[2]+m[7]* vec[3];
    res[2]=m[8]*vec[0]+ m[9]* vec[1]+m[10]*vec[2]+m[11]*vec[3];
    res[3]=m[12]*vec[0]+m[13]*vec[1]+m[14]*vec[3]+m[15]*vec[3];
  }
  void transpose() {
    float t[16];
    t[0]= m[0]; t[1]=m[4]; t[2]= m[8];   t[3]=m[12];
    t[4]= m[1]; t[5]=m[5]; t[6]= m[9];   t[7]=m[13];
    t[8]= m[2]; t[9]=m[6]; t[10]=m[10]; t[11]=m[14];
    t[12]=m[3];t[13]=m[7]; t[14]=m[11]; t[15]=m[15];
    for (int i=0;i<15;i++) {
      m[i]=t[i];
    }
  }
  void set(float *m) {
    this->m=m;
  }
};

int ballon_initialized=0;
Palette *palballon;
/*
  alors tout cela va être très bien, tout cela va être très bien. on glget la matrice de modelview et on multiplie les coordonnées	
*/
Matrice4 mat4;

int ballon() {
  /*	donc si je ne m'abuse, il s'agit de la sphère de particules
   */
  if (!ballon_initialized) {
    gpfd = new Gestionnaire_de_particules_free_display();
    palballon = new Palette(/*debuth*/0.001,/*finh*/0.7,/*nb_couleurs*/32,/*opacity*/12);  
    ballon_initialized=1;		

  }
  //	palballon->affiche(); // affichage de la palette
  float scale=0.1;
  int lifetime=50;
  float nb=12/2;
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //	glEnable(GL_BLEND);
  glPointSize(3);
  glPushMatrix();
  //	glTranslatef(0.2,-0.3,0); // ça à la limite, on le garde
  //	glScalef(0.7,0.2,0.7);

  GLfloat m[16];
  float vec4[4];
  float res4[4];
  glGetFloatv(GL_MODELVIEW_MATRIX,m);
  /*
    m[0]=1;  m[1]=0;  m[2]=0;  m[3]=0;
    m[4]=0;  m[5]=1;  m[6]=0;  m[7]=0;
    m[8]=0;  m[9]=0;  m[10]=1; m[11]=0;
    m[12]=0; m[13]=0; m[14]=0; m[15]=1;
  */ 
  mat4.set(m);
  mat4.transpose();
  int affiche_points = 0;	


  float theta=-PI/2;
  for (int i=0;i<=nb;i++) {
    if (i==0) {
      glBegin(GL_POINTS);
      {
	if (affiche_points) {
	  glColor3ub(255,255,255);
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,blanc);
	  glNormal3f(0,-1,0);
	  glVertex3f(0,-1,0);
	}
	vec4[0]=0; vec4[1]=-1; vec4[2]=0; vec4[3]=1; mat4.mul(vec4,res4);
	ballon_ajoute_de_la_particule_en(/*x*/res4[0],/*y*/res4[1],/*z*/res4[2],/*palette*/palballon,/*lifetime*/lifetime,/*scale*/scale,/*gestionnaire de particules*/gpfd);
	//ballon_ajoute_de_la_particule_en(/*x*/res4[0],/*y*/res4[1],/*z*/res4[2],/*palette*/palballon,/*lifetime*/lifetime,/*scale*/1.0,/*gestionnaire de particules*/gpfd);

      }
      glEnd();
    } else if (i==nb) {
      glBegin(GL_POINTS);
      {
	if (affiche_points) {
	  glColor3ub(255,255,255);
	  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,blanc);
	  glNormal3f(0,1,0);
	  glVertex3f(0,1,0);
	}
	vec4[0]=0; vec4[1]=1; vec4[2]=0; vec4[3]=1; mat4.mul(vec4,res4);
	ballon_ajoute_de_la_particule_en(/*x*/res4[0],/*y*/res4[1],/*z*/res4[2],/*palette*/palballon,/*lifetime*/lifetime,/*scale*/scale,/*gestionnaire de particules*/gpfd);
      }
      glEnd();
    } else {
      float alpha=0;
      for (int j=0;j<=nb*cos(theta);j++) {
	glBegin(GL_POINTS);
	{
	  float z=cos(theta)*sin(alpha);
	  float x=-cos(theta)*cos(alpha);
	  float y=sin(theta);
	  if (affiche_points) {
	    float d=sqrt(x*x+y*y+z*z);		
	    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,blanc);
	    glNormal3f(x/d,y/d,z/d);
	    glVertex3f(x,y,z);
	  }
	  vec4[0]=x; vec4[1]=y; vec4[2]=z; vec4[3]=1; mat4.mul(vec4,res4);
	  ballon_ajoute_de_la_particule_en(/*x*/res4[0],/*y*/res4[1],/*z*/res4[2],/*palette*/palballon,/*lifetime*/lifetime,/*scale*/scale,/*gestionnaire de particules*/gpfd);

	  //					ballon_ajoute_de_la_particule_en(x,y,z,palballon,8,0.2,gpfd);
	}
	glEnd();
	alpha+=2*PI/(nb*cos(theta));
      }
      theta+=PI/nb;
    }
  }
	
  /* et maintenant on va tenter d'afficher les particules */
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glLoadIdentity();
  gpfd->evolue();
  gpfd->affiche();	
  glPopMatrix();

  glPopMatrix();
  glDisable(GL_BLEND);
}


int test_and_process_si_vaiseau_hit_pastille() {
  int num_de_la_pastille_touchee=-1;
  for (int i=0;i<NB_PASTILLES;i++) {
	
    if (sqrt(sqr(tab_pastilles[i].x-vaisseau.cercle_de_percussion.x)+sqr(tab_pastilles[i].y-vaisseau.cercle_de_percussion.y))<RAYON_DE_PERCUSSION_VAISSEAU_PASTILLE) {
      tab_pastilles[i].couleur=(tab_pastilles[i].couleur + 1) % 12;
      if (!tab_pastilles[i].touched) {
	tab_pastilles[i].touched=1;
	cree_un_nuage_de_particules_autour_du_point(tab_pastilles[i].x, tab_pastilles[i].y, random() % 12);
      }		
      return(i);	
    }
  }
  return(-1);
}
void move_vaisseau() {
  float kr=120; // on divise la note_val_dans_l_octave par ce nombre et on l'ajoute aux valeurs de rotations du vaisseau
  // ça correspond donc à un amortissement du moment rotatif appliqué au vaisseau quand on appuie sur do et ré
  vaisseau.rot.z = (int)(vaisseau.rot.z + (notes_val_dans_l_octave[0] / (kr))) % 360;
  vaisseau.rot.z = (int)(vaisseau.rot.z - (notes_val_dans_l_octave[2] / (kr))) % 360;
  // on a 2 forces qui sont appliquées au vaisseau pour le moment, on a la force qui est appliquée par l'utilisateur au cul du vaisseau et dans la direction de l'angle de rotation du vaisseau et on a
  // a une force de resistance fluide

  float k=300000;

  float vaisseau_force_appliquee_val = 0;

  if (notes_val_dans_l_octave[4]!=0) {
    vaisseau_force_appliquee_val += notes_val_dans_l_octave[4] / k;
  }
  if (notes_val_dans_l_octave[5]!=0) {
    vaisseau_force_appliquee_val -= notes_val_dans_l_octave[5] / k;
  }
  vaisseau.force_appliquee.x = vaisseau_force_appliquee_val*cos(M_PI*2*vaisseau.rot.z/360+M_PI/2);
  vaisseau.force_appliquee.y = vaisseau_force_appliquee_val*sin(M_PI*2*vaisseau.rot.z/360+M_PI/2);

  // on rajoute donc ensuite une résistance fluide en -r*Vn-1 qui va diminuer la valeur de la vitesse à chaque tour jusqu'à la ramener à zéro
  float resistance_fluide_k=0.1;

  vaisseau.vn.x = vaisseau.vitesse.x;
  vaisseau.vn.y = vaisseau.vitesse.y;
  
  float force_de_rappel_k=0.001;
  

  vaisseau.vitesse.x = vaisseau.vn.x + vaisseau.force_appliquee.x - resistance_fluide_k*vaisseau.vnmoins1.x - force_de_rappel_k*vaisseau.posnmoins1.x;
  vaisseau.vitesse.y = vaisseau.vn.y + vaisseau.force_appliquee.y - resistance_fluide_k*vaisseau.vnmoins1.y - force_de_rappel_k*vaisseau.posnmoins1.y;
  
  vaisseau.posnmoins1.x = vaisseau.posn.x;
  vaisseau.posnmoins1.y = vaisseau.posn.y;

  vaisseau.posn.x = vaisseau.position.x;
  vaisseau.posn.y = vaisseau.position.y;

  vaisseau.vnmoins1.x = vaisseau.vn.x;
  vaisseau.vnmoins1.y = vaisseau.vn.y;


  vaisseau.position.x = vaisseau.position.x + vaisseau.vitesse.x;
  vaisseau.position.y = vaisseau.position.y + vaisseau.vitesse.y;

  vaisseau.cercle_de_percussion.x=vaisseau.position.x+hauteur_triangle_vaisseau*echelle_reduction_vaisseau*cos(2*M_PI*vaisseau.rot.z/360+M_PI/2);
  vaisseau.cercle_de_percussion.y=vaisseau.position.y+hauteur_triangle_vaisseau*echelle_reduction_vaisseau*sin(2*M_PI*vaisseau.rot.z/360+M_PI/2);


}
void pastillage();

int vaisseau_game_initialized=0;
void vaisseau_game() {
  if (!vaisseau_game_initialized) {
    vaisseau.position.x=0;
    vaisseau.position.y=0;
    vaisseau.vitesse.x=0;
    vaisseau.vitesse.y=0;
    vaisseau.vn.x=0;
    vaisseau.vn.y=0;
    vaisseau.vnmoins1.x=0;	
    vaisseau.vnmoins1.y=0;
    vaisseau.posn.x=0;
    vaisseau.posn.y=0;
    vaisseau.posnmoins1.x=0;
    vaisseau.posnmoins1.y=0;
    vaisseau.force_appliquee.x=0;
    vaisseau.force_appliquee.y=0;
    vaisseau.rot.z=0;
    vaisseau.time_last_shoot=0;

    vaisseau_game_initialized=1;
  }

  move_vaisseau();

  if ((notes_val_dans_l_octave[7] /*sol*/ != 0)) {
    struct timeval t;
    gettimeofday(&t, 0);
    unsigned long int temps_en_ms = mstime(); //t.tv_sec * 1000 + t.tv_usec / 1000;

    if (temps_en_ms - vaisseau.time_last_shoot > 50) {
      gp->ajouter_particule(
			    new Particule_Tir(
					      new Vecteur(vaisseau.cercle_de_percussion.x, vaisseau.cercle_de_percussion.y, 0), // position
					      new Vecteur(0.05*cos(M_PI*2*vaisseau.rot.z/360+M_PI/2), 0.05*sin(M_PI*2*vaisseau.rot.z/360+M_PI/2), 0), // vitesse
					      new Vecteur(0, 0, 0), // rotation
					      new Vecteur(0, 0, 0), // vrotation
					      /*couleur*/1, 
					      /*alpha*/255,
					      /*resistance_fluide_k*/0,
					      /*force_de_rappel_k*/0,
					      /*lifetime*/60,
					      /*scale*/1,
					      /*palette*/NULL)
			    );
      vaisseau.time_last_shoot = temps_en_ms;			
    }
  }
  /*1 = vert */
  aff_vaisseau();
  pastillage();
  test_and_process_si_vaiseau_hit_pastille();
}

float tab_dxsurdt[NB_PASTILLES];
float tab_dysurdt[NB_PASTILLES];
SplinerXY *splXY;
int last_note_pastilled;
float pastillage_zoom=0.35;
float *valx;
float *valy;
void set_pastille(int i) {
  tab_pastilles[i].x=pastillage_zoom*(1-2*((float)(random()) / RAND_MAX));
  tab_pastilles[i].y=pastillage_zoom*(1-2*((float)(random()) / RAND_MAX));
  tab_pastilles[i].couleur=0;
  tab_pastilles[i].touched=0;		
  //printf("tab_pastilles : %f %f\n", tab_pastilles[i].x, tab_pastilles[i].y);
}
Gestionnaire_de_particules_free_display *gpfd1;
Particule **tab_pastilles_particules;
Particule *la_particule_orbitant_autour_de_la_pastille_en(float x0, float y0) {
  Particule *r=new Particule(
			     new Vecteur(/*posx*/x0+0.1*(0.5-(float)random() / RAND_MAX),/*posy*/y0+0.1*(0.5-(float)random() / RAND_MAX),/*posz*/0), 
			     new Vecteur(/*vitx*/0.1*(0.5-(float)random() / RAND_MAX),/*vity*/0.1*(0.5-(float)random() / RAND_MAX),/*vitz*/0), 
			     new Vecteur(/*rotx*/0*(float)random() / RAND_MAX,/*roty*/0*(float)random() / RAND_MAX,/*rotz*/360*(float)random() / RAND_MAX), 
			     new Vecteur(/*vrotx*/0*(0.5-(float)random() / RAND_MAX),/*vroty*/0*(0.5-(float)random() / RAND_MAX), /*vrotz*/1*(0.5-(float)random() / RAND_MAX)), 
			     /*couleur*/2,/*alpha*/0,/*resistance_fluide_k*/0.05,/*force_de_rappel_k*/0.001,/*lifetime*/-1, 
			     /*scale*/0.1,/*palette*/NULL, 
			     /*pos0S*/new Vecteur(x0+1*(0.5-myrand()), y0+1*(0.5-myrand()), 0),
			     /*kS*/0/*.000005*/);
  return r;
}

void pastilles_particules_to_spline() {

  for (int i=0;i<NB_PASTILLES;i++) {
    valx[i]=tab_pastilles_particules[i]->pos->x;
    //valx[i]=tab_pastilles[i].x;
  }
  for (int i=0;i<NB_PASTILLES;i++) {
    valy[i]=tab_pastilles_particules[i]->pos->y;
    //valy[i]=tab_pastilles[i].y;
  }
  if (splXY!=NULL) delete(splXY);
  splXY=new SplinerXY(NB_PASTILLES, valx, valy);
}
//parfois on part sur une quête annexe comme par exemple permettre la rotation de la courbe3D
//selon d'autres axes que l'axe des y
void pastillage() {
	
  if (!pastillage_initialized) {

    valx=(float *)malloc(NB_PASTILLES*sizeof(float));
    valy=(float *)malloc(NB_PASTILLES*sizeof(float));

    gpfd1=new Gestionnaire_de_particules_free_display();
    // on a un joli gestionnaire de particule
    tab_pastilles_particules = (Particule**)malloc(NB_PASTILLES*sizeof(Particule*));
    // on a maintenant un joli tableau de particules, chacune d'entre elle devra tourner
    // autour d'une pastille
    for (int i=0;i<NB_PASTILLES;i++) {
      set_pastille(i); // ça randomize des valeurs de la pastille i du tableau des pastilles

      /*
	alors on va maintenant mettre une petite particule autour de la pastille
      */


      float x0=tab_pastilles[i].x;
      float y0=tab_pastilles[i].y;

      Particule *par=la_particule_orbitant_autour_de_la_pastille_en(x0,y0);

      // on ajoute la particule qu'on vient de créer au gestionnaire de particule
      gpfd1->ajouter_particule(par);
      // et on ajoute la particule à un tableau pour pouvoir y accéder ensuite pour en faire un paramètre du spliner
      tab_pastilles_particules[i] = par;
    }

    // la fonction place les coordonnées des pastilles
    // dans 2 tableaux et crée ensuite le splinerxy avec les 2 tableaux en paramètres 
    // si le spliner existe déjà on l'efface et on en recrée un
    // on appelle cette fonction pour qu'au premier passage, et avant que l'utilisateur ne joue la moindre note
    // la courbe reliant les pastilles soient calculée
    pastilles_particules_to_spline();

    last_note_pastilled = -1; 
    pastillage_initialized=1;
  }

  if (last_note_on!=last_note_pastilled) {
    // si on a une nouvelle note
    int numpastille = last_note_on % NB_PASTILLES;
    // on enlève la particule associée à la pastille de la note du gestionnaire de particule
    gpfd1->enlever_particule(tab_pastilles_particules[numpastille]);
    // on efface la particule
    delete(tab_pastilles_particules[numpastille]);
    // on recalcule la position de la pastille associée à la note
    set_pastille(numpastille);

    float x0=tab_pastilles[numpastille].x;
    float y0=tab_pastilles[numpastille].y;
    // on crée une nouvelle particule autour de la pastille
    Particule *par=la_particule_orbitant_autour_de_la_pastille_en(x0, y0);

    // on ajoute la particule au gestionnaire de particule
    gpfd1->ajouter_particule(par);
    // on conserve l'adresse de la particule 
    tab_pastilles_particules[numpastille] = par;
    // et on indique que la dernière note traitée est la note en cours afin de savoir quand rappeler cette partie 
    // autrement dit quand une nouvelle note sera jouée
    last_note_pastilled = last_note_on;
  }

	
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
 
  glTranslatef(0.0, 0.0, -1); // on déplace le monde vers l'avant pour voir depuis le point (0,0,0) qui est là où se trouve la caméra (normalement)

  glPointSize(8);
  if (affiche_pastilles) {
    // on affiche les pastilles
    glBegin(GL_POINTS);
    {
      for (int i=0; i<NB_PASTILLES; i++) {
	if (!tab_pastilles[i].touched) {
	  glColor3ub(comp(tab_pastilles[i].couleur));
	  glVertex3f(tab_pastilles[i].x, tab_pastilles[i].y, 0);
	}
      }
    }
    glEnd();
  }
  if (affiche_poles) {
    // on va afficher aussi les pos0S aussi
    // alors
    glBegin(GL_POINTS);
    {
      for (int i=0; i<NB_PASTILLES; i++) {
	glColor3ub(255,255,0);
	glVertex3f(tab_pastilles_particules[i]->pos0S->x, tab_pastilles_particules[i]->pos0S->y, 0);
      }
    }
    glEnd();
  }
  // calcul de l'évolution des particules autour des pastilles
  gpfd1->evolue();
  // on recrée la spline
  pastilles_particules_to_spline();
  // affichage de la spline reliant les particules
  splXY->splinerxy_affiche();


  // affichage des particules
  gpfd1->affiche();


  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

}

int particules_de_fumee_verte_pour_commencer_initialized=0; 
void particules_de_fumee_verte_pour_commencer() {
  if (!particules_de_fumee_verte_pour_commencer_initialized) {
    /* alors on va commencer par générer tout un tas de particules avec des directions et des vitesses aléatoires partant du centre */

    float x0=0;
    float y0=0;
    for (int i=0;i<64;i++) {
      gp->ajouter_particule(new Particule(
					  new Vecteur(/*posx*/x0+0.5*(0.5-(float)random() / RAND_MAX),/*posy*/y0+0.5*(0.5-(float)random() / RAND_MAX),/*posz*/0), 
					  new Vecteur(/*vitx*/0.1*(0.5-(float)random() / RAND_MAX),/*vity*/0.1*(0.5-(float)random() / RAND_MAX),/*vitz*/0), 
					  new Vecteur(/*rotx*/0*(float)random() / RAND_MAX,/*roty*/0*(float)random() / RAND_MAX,/*rotz*/360*(float)random() / RAND_MAX), 
					  new Vecteur(/*vrotx*/0*(0.5-(float)random() / RAND_MAX),/*vroty*/0*(0.5-(float)random() / RAND_MAX), /*vrotz*/1*(0.5-(float)random() / RAND_MAX)), 
					  /*couleur*/0,/*alpha*/32,/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,/*lifetime*/-1, /*scale*/0.2,/*palette*/NULL)
			    );


    }
    particules_de_fumee_verte_pour_commencer_initialized=1;
  }

}
void test_liste() {
  Liste<int> l=Liste<int>();
  printf("on est là\n");
  int n1=1;
  /* on va très tranquillement récupérer un pointeur sur le premier élément de la liste */
  Maille<int> *premier=l.liste_ajouter(new Maille<int>(&n1));
  int n2=2;
  Maille<int> *deuxieme=l.liste_ajouter(new Maille<int>(&n2));
  int n3=3;
  /* on va très tranquillement récupérer un pointeur sur le troisième élement de la liste */
  Maille<int> *troisieme=l.liste_ajouter(new Maille<int>(&n3));

  printf("Affichage de la liste de test\n");
  Maille<int> *p=l.premier;
  while (p!=NULL) {
    printf("%d\n",*(p->ptr));
    p=p->suivant;
  }
  /* on va très tranquillement enlever le premier élément de la liste et ensuite afficher toute la liste */
  l.liste_enlever(premier);
  p=l.premier;
  printf("Affichage de la liste de test\n");
  while (p!=NULL) {
    printf("%d\n",*(p->ptr));
    p=p->suivant;
  }
  l.liste_enlever(troisieme);
  p=l.premier;
  printf("Affichage de la liste de test\n");
  while (p!=NULL) {
    printf("%d\n",*(p->ptr));
    p=p->suivant;
  }
  l.liste_enlever(deuxieme);
  p=l.premier;
  printf("Affichage de la liste de test\n");
  while (p!=NULL) {
    printf("%d\n",*(p->ptr));
    p=p->suivant;
  }
}

void cree_un_nuage_de_particules_autour_du_point(float x0, float y0, int couleur) {
  for (int i=0;i<12;i++) {
    gp->ajouter_particule(new Particule(
					new Vecteur(/*posx*/x0+0.5*(0.5-(float)random() / RAND_MAX),/*posy*/y0+0.5*(0.5-(float)random() / RAND_MAX),/*posz*/0), 
					new Vecteur(/*vitx*/0.1*(0.5-(float)random() / RAND_MAX),/*vity*/0.1*(0.5-(float)random() / RAND_MAX),/*vitz*/0), 
					new Vecteur(/*rotx*/0*(float)random() / RAND_MAX,/*roty*/0*(float)random() / RAND_MAX,/*rotz*/360*(float)random() / RAND_MAX), 
					new Vecteur(/*vrotx*/0*(0.5-(float)random() / RAND_MAX),/*vroty*/0*(0.5-(float)random() / RAND_MAX), /*vrotz*/1*(0.5-(float)random() / RAND_MAX)), 
					/*couleur*/couleur,/*alpha*/16,/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,/*lifetime*/2000, 
					/*scale*/0.5,/*palette*/NULL)
			  );
  }
}
#define CUBOID_FACE_BASE_DEVANT 0
#define CUBOID_FACE_DEVANT 1
#define CUBOID_FACE_DROITE 2
#define CUBOID_FACE_ARRIERE 3
#define CUBOID_FACE_GAUCHE 4
float positivation(float val) {
  if (val>0) return val;
  else return 0;
}
class Cuboid {
public:
  float xgauche;
  float xdroit;
  float yhaut;
  float ybas;
  float zz;
  float normev;
  float x0;
  float y0;
  float k;
  float normv;
  float xghole;
  float yhhole;
  float xdhole;
  float ybhole;
  float ***coords;
  int sommet_du_tableau;
  void pushintab(int face,float x, float y, float z) {
    coords[face][sommet_du_tableau][0]=x;
    coords[face][sommet_du_tableau][1]=y;
    coords[face][sommet_du_tableau][2]=z;
    sommet_du_tableau++;
  }
  // un k de 0 c'est un mur
  void make_cuboid_face_base_devant(float k) {
    sommet_du_tableau=0;
    xgauche=1.0;
    xdroit=-1.0;
    yhaut=1.0;
    ybas=-1.0;
    zz=1.0;
    normev;
    x0=0;
    y0=0;
    normv = sqrt(sqr(xgauche-x0)+sqr(yhaut-y0));
    xghole = x0 + k*(xgauche - x0) / normv;
    yhhole = y0 +k*(yhaut-y0)/normv;
    normv=sqrt(sqr(xdroit-x0)+sqr(yhaut-y0));
    xdhole = x0 + k*(xdroit-x0)/normv;
    normv=sqrt(sqr(xdroit-x0)+sqr(ybas-y0));
    ybhole = y0+k*(ybas-y0)/normv;
    normv=sqrt(sqr(xgauche-x0)+sqr(ybas-y0));
    /* pour enregistrer une macro dans le registre a, taper qa taper la série de commandes 
       puis taper q pour indiquer la fin de la macro taper ensuite @a pour éxecuter la macro a et 
       taper @@ pour l'executer à nouveau, si on souhaite l'executer n fois on tape n@a*/
    // alors on a les cheres coordonnees du trou, on va peut être creer 2 cuboids, 1 à gauche et 1 à droite mais d'abord on
    // va aller retourner voir le Sweeper qui est en fait un extrudeur
    pushintab(CUBOID_FACE_BASE_DEVANT,xgauche,yhaut , zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xgauche,ybas ,zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xghole,ybhole, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xghole,yhhole, zz);

    pushintab(CUBOID_FACE_BASE_DEVANT,xghole,ybhole, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xgauche,ybas, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xdroit,ybas, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xdhole,ybhole, zz);

    pushintab(CUBOID_FACE_BASE_DEVANT,xdhole,ybhole, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xdroit,ybas, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xdroit,yhaut, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xdhole,yhhole, zz);

    pushintab(CUBOID_FACE_BASE_DEVANT,xdroit,yhaut, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xgauche,yhaut, zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xghole,yhhole,zz);
    pushintab(CUBOID_FACE_BASE_DEVANT,xdhole,yhhole, zz);

			 

  }
  void make_cuboid() {
    // la valeur absolue c'est grosso modo la distance entre deux choses donc par exemple si je regarde mon bonheur de maintenant par rapport à mon bonheur d'alors je peux en faire la différence est considéré à un moment que les deux sont égaux dans ce cas là l'écart est nul, égal à zéro
    // alors je ne vais pas me clochardiser car j'aime trop ce moment où j'apprends de mes erreurs et où j'envisage quand même de vendre mon application à un moment ou à un autre, même peut être très tard, même peut être jamais car ce que j'aime avant tout c'est ce moment où j'affiche des données et j'aime même plus manger qu'écrire au clavier, j'ai la flemme descendre mes escaliers, je veux dormir maintenant, d'un sommeil lourd car en fait ce que j'aime le plus dans ma vie c'est me suicider de sommeil ou bien ne plus survivre du tout car je ne trouverais pas mieux aujourd'hui car je suis devenu stupide et paranoiaque a cause de la musique et maintenant la fenetre de ma chambre est ouverte et je pense à christian bigo qui est cool et chez lui et il fait des trucs avec ses mains et il ne se clochardise pas et il vit bien et il n'a pas de problème de santé sauf qu'il est gros et je n'ai pas envie de devenir gros et donc voilà pourquoi je veux passer le plus longtemps possible dehors et ne pas mengueuler sur libre antenne mais j'ai eu du mal à retrouver mon portefeuille et je l'avais laissé dans mon blouson et j'aurais plutôt envie d'écrire sur une feuille et je n'ai pas envie de faire d'effort et je me dis que je remonte la pente que je l'ai échappé belle et je suis bien derrière un écran sauf que ça me nique les yeux et que je serais mieux dehors à jouer de l'accordéon plutôt que de réfléchir à des problèmes mais en fait je m'ennuirais au bout d'un moment dehors
    make_cuboid_face_base_devant(positivation(compteur[0]/100-compteur[2]/100));

    for (int i=0;i<16;i++) {
      for (int j=0;j<3;j++) {
	coords[CUBOID_FACE_DEVANT][i][j]=coords[CUBOID_FACE_BASE_DEVANT][i][j];
	//printf("%f\n",coords[CUBOID_FACE_BASE_DEVANT][i][j]);
      }
      //printf("\n");
    }
			  
    // pour le challenge et le plaisir d'être plongé dans une activité

    GLfloat mm[16];
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(90, 0, 1, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,mm);
    /*printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
      mm[0],mm[1],mm[2],mm[3],mm[4],mm[5],mm[6],mm[7],mm[8],mm[9],mm[10],mm[11],mm[12],mm[13],mm[14],mm[15]);*/
	
    MatriceN *mat = new MatriceN(4,4,mm);
    //mat->afficher();
    mat->transposer(); // Mon cher transposeur
    make_cuboid_face_base_devant(positivation(compteur[4]/100-compteur[5]/100));
    for (int i=0;i<16;i++) {
      mat->vmul(coords[CUBOID_FACE_BASE_DEVANT][i], coords[CUBOID_FACE_DROITE][i]);
      for (int j=0;j<3;j++) {
	//printf("%f \n",coords[CUBOID_FACE_DROITE][i][j]);
      }
      //printf("\n");
    }
    glRotatef(90, 0, 1, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,mm); 
    mat->transposer(); // Mon cher transposeur
    //mat->afficher();
    make_cuboid_face_base_devant(positivation(compteur[7]/100-compteur[9]/100));
    for (int i=0;i<16;i++) {
      mat->vmul(coords[CUBOID_FACE_BASE_DEVANT][i], coords[CUBOID_FACE_ARRIERE][i]);
    }

    glRotatef(90, 0, 1, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX,mm);  
    mat->transposer(); // Mon cher transposeur
    make_cuboid_face_base_devant(compteur[11]/100);
    for (int i=0;i<16;i++) {
      mat->vmul(coords[CUBOID_FACE_BASE_DEVANT][i], coords[CUBOID_FACE_GAUCHE][i]);
    }

    delete(mat);
    // je pourrais me branler mais je n'ai pas envie pour le moment, pour le moment je n'ai envie de rien sauf que c'est un tic de langage et en fait j'ai envie de finir cette phrase et je crois qu'elle est finie donc maintenant je peux retourner coder et je veux une motivation supplémentaire, coder me permettra de maintenant ma dignité et de ne pas intervenir dans leur débat et de me plonger dans quelquechose qui me plait beaucoup parce conceptuellement ça va très loin et je commence à aimer mon clavier je sais que là je veux aller un peu plus haut ou un peu plus bas pour voir pourquoi il n'affiche pas les faces suivantes car j'aime bien la face telle qu'elle est maintenant et là maintenant je dois aller regarder ou simplement afficher les données des faces rotationnées et je veux voir si c'est zéro ou pas
    glPopMatrix();
    //exit(0);
	
  }
  Cuboid() {
    printf("Constructeur Cuboid\n");	
    coords=(float ***)malloc(5*sizeof(float**));

    for (int i=0;i<5;i++) {
      coords[i]=(float **)malloc(16*sizeof(float*));
      for (int j=0;j<16;j++) {
	coords[i][j]=(float*)malloc(sizeof(float)*3);
      }	
    }
			
  }
  void afficher_cuboid() {
    make_cuboid();
    /*
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      gluLookAt(0,0,-4, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
    */
    /*
      if (note_en_cours() % 2 == 0) inc_moteur=+1;
      else inc_moteur=-1;

      glRotatef(moteur % 360, 0, 1, 0);
    */

    /*
      glBegin(GL_QUADS);
      glColor3f(0,0,1);
      glVertex3f(xgauche,yhaut , zz);
      glVertex3f(xgauche,ybas ,zz);
      glVertex3f(xghole,ybhole, zz);
      glVertex3f(xghole,yhhole, zz);

      glVertex3f(xghole,ybhole, zz);
      glVertex3f(xgauche,ybas, zz);
      glVertex3f(xdroit,ybas, zz);
      glVertex3f(xdhole,ybhole, zz);

      glVertex3f(xdhole,ybhole, zz);
      glVertex3f(xdroit,ybas, zz);
      glVertex3f(xdroit,yhaut, zz);
      glVertex3f(xdhole,yhhole, zz);

      glVertex3f(xdroit,yhaut, zz);
      glVertex3f(xgauche,yhaut, zz);
      glVertex3f(xghole,yhhole,zz);
      glVertex3f(xdhole,yhhole, zz);
      glEnd();
    */
    /*
      alors, donc les patrons de restaurants, ils peuvent manger toute la journée, ils peuvent toucher les 
      serveuses toute la journée, et sinon ils vivent dans le gras toute la journée
      ils mangent des poignées de frites et après ils vont roter sur la plage
      les écrivains ont pas mal la belle vie, toute la journée devant leur écran, à leur clavier, ils écrivent
      des choses, ce qui leur passe par la tête en fait, et ils sont bien, ils expriment tout ce qu'ils veulent
      c'est bien tranquille, ils le font sans peur du jugement, sans peur de se faire enfermer, surtout 
      les écrivains parfaitement anonymes, ils peuvent dire ce qu'ils veulent, comme par exemple on a souvent
      tendance à exagérer les conséquences de nos actions surtout quand on a été sévèrement puni dans le passé,
      on ne fait plus grand chose qui puisse risquer une sanction... on est peinard, chez soi, avec soi même
      et on est bien, on n'emmerde personne, personne nous emmerde. et c'est vraiment ça le plus beau, on
      peut même simplement programmer un petit effet graphique du meilleur goût et on repense à notre vie quand 
      on était avec le trs80 dans la chambre des parents et on ne veut pas parler sur internet, on aimerait bien
      un bouton pour qu'ils commencent à parler et encore c'est bizarre quand ils parlent non ? on est juste heureux
      d'être soi et pas eux et là maintenant on se demande ce qu'il fait le type qui lisait des mangas, on se demande
      si il s'ennuie, peut être qu'il s'ennuie, on aimerait bien les déclencher comme des petits robots, on 
      aimerait bien pouvoir mettre une pièce et qu'ils se mettent à parler, ce serait tellement amusant,
      ce serait nos petits esclaves, ils parleraient sur commande, et on serait comme ça à les écouter en se
      sachant toujours supérieurs, car ils parlent et pas nous et on sait qu'il vaut toujours mieux garder le silence
      c'est toujours moins dangereux que de parler, ce sont les fous qui parlent quand il est possible d'écrire bien
      caché, et ceci sera peut être lu à ma mort, je n'en sais rien mais ce serait bien, je ne risquerais plus rien,
      donc j'écris tout ceci pour que ce soit lu après ma mort, mon précieux code source, il sera peut être lu par
      un codeur ou je ne sais qui parce que bon ils nous apprennent et ils insistent pour qu'il y ait toujours une raison
      de faire quelquechose mais parfois on ne connait pas cette raison et c'est là tout le problème et c'est là que 
      ça peut devenir angoissant parce quand on ne connait pas la ou les raisons pour lesquelles on fait quelquechose
      est ce que ça signifie qu'on ignore pour autant l'endroit où l'on va, alors ça pas du tout, je sais très bien vers
      quoi je me dirige, je vais sans doute chez mes parents puis à la plage et discuter avec une infirmière et écouter
      des conversations internet en programmant et j'écris tout en cherchant vaguement quelquechose à vouloir et donc 
      c'est délicieux car je pourrais imaginer que je suis dans un manga et arrêter de me demander dans quel but je le fais
      car je ne sais pas encore dans quel but je le fais, les gens qui avancent sans but précis font ils peur aux autres gens
      oui sans doute, encore que non, ce n'est pas ça mais je me dis que peut être, je ne veux pas avancer sans but précis, 
      alors sauf que là, j'avance sans but précis autre qu'écrire mais ce n'est pas le but en soi donc oui j'avance sans but
      précis si ce n'est avoir une nouvelle idée dans mon code
    */
    glScalef(0.4,0.4,0.4);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBegin(GL_QUADS);
				
    for (int j=1;j<5;j++) {
      glColor4ub(compub(j+1),196);
      for (int i=0;i<16;i++) {
	//printf("%f %f %f\n",coords[j][i][0], coords[j][i][1], coords[j][i][2]);
	glVertex3f(coords[j][i][0],coords[j][i][1],coords[j][i][2]);
      }
    }
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    //	glPopMatrix();
  }
};
class Voyager {
public:
  int nb_points_voyage=0;
  float posi;
  float incposi;
  Sweeper *sweepervoyage;
  Courbe3D *courbe;
  int immobile=1;
  Voyager() {
    courbe=new Courbe3D(12);
    int nb_sommets_du_contour=6;
    float **contour = polygone(0,0,0.1,nb_sommets_du_contour);
    sweeper=new Sweeper(contour, nb_sommets_du_contour, courbe);
	
    courbe->calcule_courbe3D(immobile);
    sweeper->calculer_sweeper();
	

    nb_points_voyage=courbe->spliner->nb_de_points_de_la_courbe;
    printf("nb points voyage %d\n",nb_points_voyage);
    //exit(0);
    this->incposi=(float)(nb_points_voyage)/3200;
    this->posi=0;
  }
  int do_voyager() {
    //Excellent
    posi=posi+incposi;
    if ((incposi>0) && (posi>=nb_points_voyage-incposi-1)) {incposi=-incposi; posi=nb_points_voyage-1;}
    else if ((incposi<0) && (posi<=incposi)) {incposi=-incposi; posi=0;}
    printf("voyons si on arrive ici\n");
		
    printf("posi:%f\n",posi);
    printf("incposi:%f\n",incposi);
    //if (posi<incposi) {printf("posi<incposi\n"); exit(0);}
    //if (posi>=nb_points_voyage-incposi) {printf("posi>=nb_points_voyage-incposi\n"); exit(0);}
    float xcam=courbe->spliner->xcoords[int(posi)];
    float ycam=courbe->spliner->ycoords[int(posi)];
    float zcam=courbe->spliner->zcoords[int(posi)];
    printf("je suis une petite chenille cybernétique\n");
    printf("alors je n'ai pas très envie d'écrire en bleu alors j'écris en rose et je dis franchement ");
    int index;
    if (incposi>0) index = int(posi)+1;
    else index = int(posi)-1;
    float xpoint=courbe->spliner->xcoords[index];
    float ypoint=courbe->spliner->ycoords[index];
    float zpoint=courbe->spliner->zcoords[index];
    if ((xpoint==xcam) && (ypoint==ycam) && (zpoint==zcam)) {
      printf("ahah!\n"); 
      printf("posi:%f\n",posi);
      printf("incposi:%f\n",incposi);
      printf("ceil(posi+incposi) (index dans le cas où incposi est positif) :%f\n",ceil(posi+incposi));
      printf("floor(posi+incposi) (index dans le cas où incposi est négatif):%f\n",floor(posi+incposi));
      exit(0);
    }
    printf("j'aime paufiner mon code\n");
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();                       
    glFrustum(-1, 1, -1, 1, 0, 15);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    gluLookAt(xcam,ycam,zcam, xpoint,ypoint,zpoint, 0,1,0); // pos, point qu'il regarde, up
    //gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
    printf("j'aime manger\n");
    courbe->spliner->affiche_splinerXYZ();
    sweeper->afficher_sweeper(immobile,1);
    printf("je cherche à me détendre\n");
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
  }
};			

int notinitialized(int numpart) {
  if (prevpart!=numpart) {
    prevpart=numpart;
    return 1;
  } else {
    //prevpart=numpart;
    return 0;
  }
	
}
int inside(int num) {
  if (num==9) return 1;
}

/* ici, viendront se placer toutes les initialisations d'objets en variables globales car en c++, il est possible
   d'appeler les constructeurs des instances en global, ce qui n'est pas possible en c, où il faut appeler la fonction 
   dans le main (ou dans une fonction appelée par le main) qui initialise une variable globale 
   donc on a :
*/

Voyager *voyager;
//Constructeur
Courbe3D *courbe3D = new Courbe3D(12);
Cuboid *cuboid;
int sweeperinitialized=0;
int voyagerinitialized=0;
int esquisseinitialized=0;
int esquisselist;
class Mikado {
public:
  int *tableau_des_baguettes;
  int nb_de_baguettes=12;
  Mikado() {
    tableau_des_baguettes=(int*)malloc(nb_de_baguettes*sizeof(int));
    float incz=1/12.0;
    float z=-6*incz;
	
    for (int i=0;i<12;i++) {
      tableau_des_baguettes[i]=glGenLists(1);
      glNewList(tableau_des_baguettes[i],GL_COMPILE);
      // on construit les plateaux
      esquisse(-0.8,0,0, 0.8,0,0, compub(i),128);
      glEndList();
      z+=incz;
    }
  }

  void affiche_mikado() {
    glEnable(GL_BLEND);
    //glMatrixMode(GL_MODELVIEW);             
    //glLoadIdentity();                       
    //gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
    //glRotatef(int(0.5*moteur) % 360,-1 , 1, 1);

    //glTranslatef(0.6*sin(2*M_PI*(moteur % 180)/180),0.0,0.6*sin(2*M_PI*(moteur % 270)/270));
    //glLineWidth(5);

    float incy=1/7.0;
    float y=-3.5*incy;
    int touche=0;
    for (int j=0;j<7;j++) {
      float incz=1/12.0;
      float z=-6*incz;


      for (int i=0;i<12;i++) {
	glPushMatrix();

	int kk=2*12;
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(5+int(150*compteurp[touche]/100));
	glDisable(GL_LINE_SMOOTH);
	glTranslatef(0,y,z);
	//glRotatef(360*compteurp[touche]/100, 1,0,0 );
				
	glRotatef( 360.0*compteurp[touche]/100, 1,0,0);
	glTranslatef(0,0,sgn(z)*0.7*compteurp[touche]/100);
	float scale=0.1+compteurp[touche]/100;
	glScalef(scale,scale,scale);
	//		glScalef(1/(1+0.5*compteurp[touche]/100),1,1);


	glCallList(tableau_des_baguettes[i]);	
	glPopMatrix();
	z+=incz;
	touche++;
      }
      y+=incy;
    }
    glDisable(GL_BLEND);
  }

  ~Mikado() {
    delete(tableau_des_baguettes);
  }
};

#define pushlighting int lsav; glGetIntegerv(GL_LIGHTING,&lsav);
#define poplighting if (lsav) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);

Mikado *mikado;
class Landscaper {
public:
  int tailletx=15;
  int xtm=tailletx-1;
  int tailletz=8;
  int ztm=tailletz-1;
  float xemin=-3.5; //-5;
  float zemin= 3.5;
  float yemin=-4.2;
  float **tab;
  float **tab2;
  int zbegin=0;
  int ozbegin=0;
  float zbeginf=0;
  int nb_lissages=3; //il faut un nombre impair
  float amplitude_random=30;
  float amplitude_random_zend=30;
  int zend;
  float incofsze;
  float ofsze;
  float inczbeginf=0.07;
  float incxe;
  float incze;

  int affiche_normales=0;
  Landscaper() {
    printf("Landscaper()\n");
    tab = (float**)malloc(sizeof(float*)*tailletz);
    for (int i=0;i<tailletz;i++) {
      tab[i]=(float*)malloc(sizeof(float)*tailletx);
    }
    tab2 = (float**)malloc(sizeof(float*)*tailletz);
    for (int i=0;i<tailletz;i++) {
      tab2[i]=(float*)malloc(sizeof(float)*tailletx);
    }
    landscaper_randomtab();
    lissage();
    incxe=2*abs(xemin)/tailletx;
    incze=4.0/tailletz;
    incofsze= incze/(1.0/inczbeginf);
  }
  void landscaper_modify() {
    zbeginf+=inczbeginf;
    ofsze+=incofsze;
		
    // quand on se déplace de 1 sur les zt on s'est déplacé de incze sur l'écran
    // quand on s'est déplacé de zbeginf sur les zt on s'est déplacé de -ofsze sur l'écran
    zbegin=int(zbeginf);
    if (zbegin==tailletz) {zbegin=0; zbeginf=0;}
    zend=zbegin-1;
    if (zend<0) zend=ztm;
	
    if (zbegin!=ozbegin) {random_et_lisse_zend(); ozbegin=zbegin;ofsze=0;}
  }
  int xl(int x) { //xleft
    if (x-1 == -1) return xtm;
    else return x-1;
  }
  int xr(int x) { //xright
    if (x+1 == tailletx) return 0;
    else return x+1;
  }
  int zd(int z) { //zdown
    if (z-1 == -1) return ztm;
    else return z-1;
  }
  int zu(int z) { //zup
    if (z+1 == tailletz) return 0;
    else return z+1;
  }
  void landscaper_affiche() {
	
    glMatrixMode(GL_MODELVIEW);             
    glLoadIdentity();                       
    gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  

    float ze=zemin;
    int zt=zbegin;
    for (int i=0;i<tailletz-1;i++) {
      float xe=xemin;
      for (int xt=0;xt<tailletx-1;xt++) {

	glBegin(GL_QUADS);

	float spec_color[4]={0.5,0.3,0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,spec_color);
	//glMaterialfv(GL_FRONT,GL_SPECULAR,spec_color);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_color);

	float nor[3];
	float A[3];
	A[0]=xe;
	A[1]=yemin+tab[zt][xt];
	A[2]=ze-ofsze;
	float B[3];
	B[0]=xe;
	B[1]=yemin+tab[zu(zt)][xt];
	B[2]=ze+incze-ofsze;
	float D[3];
	D[0]=xe+incxe;
	D[1]=yemin+tab[zt][xr(xt)];
	D[2]=ze-ofsze;
	pvec(B[0]-A[0],B[1]-A[1],B[2]-A[2], D[0]-A[0], D[1]-A[1], D[2]-A[2], nor);
					
	glNormal3f(-nor[0],-nor[1],nor[2]);
	glVertex3f(xe,yemin+tab[zt][xt],ze-ofsze);//coin en bas à droite = A
	glVertex3f(xe,yemin+tab[zu(zt)][xt],ze+incze-ofsze);//coin en haut à droite = B
	glVertex3f(xe+incxe,yemin+tab[zu(zt)][xr(xt)],ze+incze-ofsze);//coin en haut à gauche = C
	glVertex3f(xe+incxe,yemin+tab[zt][xr(xt)],ze-ofsze);//coin en bas à gauche = D
	glEnd();
	if (affiche_normales) {
	  glDisable(GL_LIGHTING);
	  glBegin(GL_LINES);
	  glColor3ub(255,0,0);
	  glVertex3f(A[0],A[1],A[2]);
	  glVertex3f(A[0]+nor[0],A[1]+nor[1],A[2]+nor[2]);
	  glEnd();
	  glEnable(GL_LIGHTING);
	}
	xe+=incxe;
      }
      ze+=incze;
			
      zt++;
      if (zt==tailletz) zt=0;
    }

    glDisable(GL_LIGHTING);

  }
  void landscaper_randomtab() {
    int zt=0;
    for (int i=0;i<tailletz;i++) {
      int xt=0;
      for (int j=0;j<tailletx;j++) {
	tab[zt][xt]=-0.5*amplitude_random+amplitude_random*myrand();
	xt++;
      }
      zt++;
    }
  }
  void lisse(int xt, int zt, float **tabs, float **tabr) {
    float sval=0;
    //au dessus 
    int ztup=zt+1;
    if (ztup==tailletz) ztup=0;
    sval+=tabs[ztup][xl(xt)];
    sval+=tabs[ztup][xt];
    sval+=tabs[ztup][xr(xt)];
    //à droite
    sval+=tabs[zt][xr(xt)];
    //au dessous
    int ztdown=zt-1;
    if (ztdown<0) ztdown=ztm;
    sval+=tabs[ztdown][xr(xt)];
    sval+=tabs[ztdown][xt];
    sval+=tabs[ztdown][xl(xt)];
    //à gauche
    sval+=tabs[zt][xl(xt)];
    //au centre
    sval+=tabs[zt][xt];

    tabr[zt][xt]=sval / 9;
  }
  void lissage() {
    float **tabs=tab;
    float **tabr=tab2;
    for (int i=0;i<nb_lissages;i++) {
      int zt=0;
      for (int i=0;i<tailletz;i++) {
	int xt=0;
	for (int j=0;j<tailletx;j++) {
	  lisse(xt,zt,tabs,tabr);
	  xt++;
	}
	zt++;
	float **tabaux;
	tabaux=tabs;
	tabs=tabr;
	tabr=tabaux;
      }
    }
  }
  void random_et_lisse_zend() {
    for (int xt=0;xt<tailletx;xt++) 
      tab[zend][xt]=-0.5*amplitude_random_zend+amplitude_random_zend*myrand();
		
		
    float **tabs=tab;
    float **tabr=tab2;
    for (int i=0;i<nb_lissages;i++) {
      int xt=0;
      for (int j=0;j<tailletx;j++) {
	lisse(xt,zend,tabs,tabr);
	xt++;
      }
      float **tabaux;
      tabaux=tabs;
      tabs=tabr;
      tabr=tabaux;
    }
  }
  ~Landscaper() {
    for (int i=0;i<tailletz;i++) {
      free(tab[i]);
    }
    free(tab);
    for (int i=0;i<tailletz;i++) {
      free(tab2[i]);
    }
    free(tab2);
		
  }

};

//Constructor
Landscaper *landscaper=new Landscaper();
class Cube {
public:
  int list,list2;
  Cube() {
		
    make_cube();
  }
  void make_cube() {
    list=glGenLists(1);
    glNewList(list,GL_COMPILE);
    glBegin(GL_QUADS);
    glColor4ub(compaub(0)); // face de droite

    glVertex3f(-1,-1,-1); 
    glVertex3f(-1,-1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1,-1);

    glColor4ub(compaub(1)); // face de gauche donc
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1,-1);
    glVertex3f(1, -1,-1);
    glVertex3f(1, -1, 1);
    glEnd();
    glEndList();

    list2=glGenLists(1);
    glNewList(list2,GL_COMPILE);
    glBegin(GL_QUADS);
    glColor4ub(compaub(2)); // face du dessus
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);

    glColor4ub(compaub(3)); // face du dessous
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glEnd();
    glEndList();
  }
  void affiche_cube() {
		
    glEnable(GL_BLEND);	
    glMatrixMode(GL_MODELVIEW);             
    glLoadIdentity();                       
    gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up

    glRotatef(int(0.1*moteur) % 360,1 , -1, 1);

    glPushMatrix();
    glTranslatef(   0.01*compteur[0]*sin(2*M_PI*(moteur % 55)/55),
		    0.01*compteur[2]*sin(2*M_PI*(moteur % 65)/65),
		    0.01*compteur[4]*sin(2*M_PI*(moteur % 45)/45));
    glScalef(0.3,0.3,0.3);	
    glCallList(list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(   0.01*compteur[5]*sin(2*M_PI*(moteur % 55)/55),
		    0.01*compteur[7]*sin(2*M_PI*(moteur % 65)/65),
		    0.01*compteur[9]*sin(2*M_PI*(moteur % 45)/45));

    glScalef(0.3,0.3,0.3);	
    glCallList(list2);
    glPopMatrix();
    glDisable(GL_BLEND);

  }
};
Cube *simplecube;
// y$ yank to the end of line
class RandomCanvas {
  // alors on a dimX, dimY
  // on a un blaireau qui parle sur libre antenne, on veut qu'il meurt
  // on a peur de croire qu'on pourrait faire quelquechose de mal
  // on ne veut pas se faire interner
  // on a peur de tout ça
  // on ne sait pas bien comment faire pour rester sain d'esprit
  // on se dit que l'info pourrait nous faire plonger parce que la derniere fois on a plongé à cause de quoi exactement
  // on était devenu trop sûr de soi, on allait voir les filles dans la rue et on leur parlait, on sortait la nuit
  // et on pissait un peu n'importe où, on voulait une copine, maintenant on ne veut plus de copine, on veut juste
  // parler à ces connards et ne pas faire autre chose
  float **tab;	
  float hg[4]; //haut à gauche
  float hd[4]; //haut à droite
  float bg[4]; //bas à gauche
  float bd[4]; //bas à droite
  int olast_note_on=-1;
  int olast_note_played_time=-1;
  Gestionnaire_de_particules_free_display *gp;
  Palette *pal;  
public:
  RandomCanvas() {
    printf("RandomCanvas\n");
    gp = new Gestionnaire_de_particules_free_display();
    pal = new Palette(/*debuth*/0.001,/*finh*/0.9,/*nb_couleurs*/64,/*opacity*/128);  
  }
  void ndc2sc(float *pos) { //from normalized device coordinates to screen coordinates
    pos[0]=dimX*(pos[0]+1) / 2;
    pos[1]=dimY*(pos[1]+1) / 2;
  }
  void affiche() {
    printf("RandomCanvas->affiche()\n");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,-2, 0,0,0, 0,1,0 );//pos, point qu'il regarde, up
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor4ub(255,0,0,0);
    glVertex3f(-1,-1,0);
    glVertex3f( 1,-1,0);
    glVertex3f( 1, 1,0);
    glVertex3f(-1, 1,0);
    glVertex3f(-1,-1,0);
    glEnd();
    glBegin(GL_POINTS);
    glColor4ub(255,0,0,0);
    glVertex3f(0,0,0);
    glEnd();
	

    GLfloat mp[16];
    GLfloat mv[16];


    glGetFloatv(GL_PROJECTION_MATRIX,mp);

    printf("projection matrix\n");
    printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
	   mp[0],mp[1],mp[2],mp[3],mp[4],mp[5],mp[6],mp[7],mp[8],mp[9],mp[10],mp[11],mp[12],mp[13],mp[14],mp[15]);

    glGetFloatv(GL_MODELVIEW_MATRIX,mv);  
    printf("modelview matrix\n");
    printf("%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n",
	   mv[0],mv[1],mv[2],mv[3],mv[4],mv[5],mv[6],mv[7],mv[8],mv[9],mv[10],mv[11],mv[12],mv[13],mv[14],mv[15]);
	


    MatriceN *matn = new MatriceN(4, 4, mp);
    matn->multiplier(mv);
    matn->transposer();	
    float vec[4];
    vec[0]=-1; vec[1]=-1; vec[2]=0; vec[3]=1;
    matn->vmul(vec,bg);
    ndc2sc(bg);
    vec[0]=1; vec[1]=-1; vec[2]=0; vec[3]=1;
    matn->vmul(vec,bd);
    ndc2sc(bd);
    vec[0]=1; vec[1]=1; vec[2]=0; vec[3]=1;
    matn->vmul(vec,hd);
    ndc2sc(hd);
    vec[0]=-1; vec[1]=1; vec[2]=0; vec[3]=1;
    matn->vmul(vec,hg);
    ndc2sc(hg);

    printf("bas gauche : %f %f \n",bg[0],bg[1]);
    printf("bas droite : %f %f \n",bd[0],bd[1]);
    printf("haut droit : %f %f \n",hd[0],hd[1]);
    printf("haut gauche: %f %f \n",hg[0],hg[1]);
    gp->affiche();
  }
  void modify() {
    if ((last_note_on!=olast_note_on) || (last_note_played_time!=olast_note_played_time)) {
      olast_note_on=last_note_on;
      olast_note_played_time=last_note_played_time;
      float x0=-1+2*myrand();
      float y0=-1+2*myrand();
      float z0=0;
      // alors on a des petites particules, allons voir ce merveilleux programme, sautons grace à notre cher
      // téléporteur pour aller dans ce cher terrain, ce cher territoire, à l'intérieur de cet organe 
      // ce cher organe qui gère l'évolution des particules, cela va être bien, nous devons attendre que le 
      // quebecois ait fini de parler, il parle, c'est embêtant, c'est comme si il y avait une zone pleine 
      // d'astéroides, alors bon donc est passé et maintenant quoi, supposons qu'une particule sorte du bord
      // de l'écran
      gp->ajouter_particule(new Particule(
					  new Vecteur(/*posx*/x0,/*posy*/y0,/*posz*/z0), 
					  new Vecteur(/*vitx*/0.05*(0.5-myrand()),/*vity*/0.05*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					  new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/0*myrand()), 
					  new Vecteur(/*vrotx*/0*(0.5-myrand()),/*vroty*/0*(0.5-myrand()), /*vrotz*/10*(0.5-myrand())), 
					  /*couleur*/4,/*alpha*/255,/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,/*lifetime*/500,
					  /*scale*/0.1,/*palette*/pal)
			    );
      // Bookmark : ma set a bookmark named a, 'a jump to bookmark
      // on va aller chercher dans Particule, l'organe qui s'occupe de l'affichage en utilisant un petit
      // téléporteur mais pour cela on a besoin de connaitre un tatouage sur l'organe, on va y aller en passant 
      // par Particule


    }
    // Terminal
    Liste<Particule> *l=gp->l_particules_vivantes;
    if (l->nb_elements>=2) {
      Maille<Particule> *maille=l->premier->suivant;
      while (maille != NULL) {
	Particule *une=maille->precedent->ptr;
	Particule *deux=maille->ptr;
	float x1=une->pos->x;
	float y1=une->pos->y;
	float x2=deux->pos->x;
	float y2=deux->pos->y;
	esquisse(x1,y1,0,x2,y2,0, compaub(last_note_on));

	maille = maille->suivant;
      }
    }
	
    gp->evolue();
  }
  ~RandomCanvas() {

  }
};
RandomCanvas *randomcanvas;
int ecart_max=0;
int resetted=0;
int ecart_precedent=-1;
// génère une particule quand un intervalle plus grand que le plus grand intervalle joué jusque là, est joué
// quand l'intervalle fait 7 octaves ou plus, l'intervalleur est resetted
void intervalleur() {
	
	
  if ((touche_precedente==-1)) //lancement du programme, aucun intervalle à traiter
    return;
  int ecart=abs(touche_en_cours-touche_precedente);
  if (ecart==ecart_precedent) //on ne génère qu'une seule particule par nouvel écart
    return;
  if (ecart > ecart_max) {
    printf("note : %d\n",touche_en_cours);
    printf("note precedente : %d\n",touche_precedente);
    printf("ecart en cours %d\n",abs(touche_en_cours-touche_precedente));
    ecart_max = abs(touche_en_cours-touche_precedente);
    fprintf(stderr,"ecart max : %d\n",ecart_max);
    if (ecart_max>7*12) {//
      printf("intervalleur resetted\n");
      ecart_max=0; // au prochain passage, l'écart sera forcément plus grand donc une nouvelle particule sera générée, voilà pourquoi, 
    } else {				// pour ne générer qu'une seule particule à ce moment là on else, 
      gp->ajouter_particule(new Particule(
					  new Vecteur(/*posx*/0.1*(0.5-myrand()),/*posy*/0.1*(0.5-myrand()),/*posz*/0*(0.5-myrand())), 
					  new Vecteur(/*vitx*/0*(0.5-myrand()),/*vity*/0*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					  new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/360*myrand()), 
					  new Vecteur(/*vrotx*/0*1*(0.5-myrand()),/*vroty*/0*1*(0.5-myrand()), /*vrotz*/1*(0.5-myrand())), 
					  /*couleur*/(ecart_max % 12),/*alpha=opacite*/128,/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,
					  /*lifetime*/500,/*scale*/0.3,/*palette*/NULL)
			    );
    }			
    ecart_precedent=ecart;
		
  }
	
}

class Intervalleur2 {
public:
  // donc des intervalles de 12 notes donc c'est dans un tableau sauf que ce ne sont pas des intervalles de 12 notes
  // mais tous les intervalles possibles sur 7 octaves donc j'ai un tableau

  int intervalles[7*12];
  Intervalleur2() {
    for (int i=0;i<7*12;i++) {
      // et je l'initialise à 0;
      intervalles[i]=0;
    }
  }
  // et j'ai un qui est appelé à chaque frame
  void process() {
    // et qui regarde la touche_en_cours et la touche_precédente
    // donc ça commence pareil que l'intervalleur simple
    // on regarde si on a au moins 2 touches de jouées pour pouvoir calculer
    if (touche_precedente==-1) 
      return;
    // un écart
    int ecart=abs(touche_en_cours-touche_precedente);
    // au lieu de regarder si il est égal à l'écart précédent, et par écart je veux dire intervalle c'est plus classe
    // et ça me permettra de pas avoir de problème avec ma terminologie, je regarde si il est présent dans le 
    // tableau des intervalles. ou plutôt si il est absent
    if (intervalles[ecart]==0) {
      // si c'est le cas, on l'y place, je parle de l'écart, et pas de ma fille à la dass
      intervalles[ecart]=1;
      // et on génère une particule
      gp->ajouter_particule(new Particule(
					  new Vecteur(/*posx*/0.1*(0.5-myrand()),/*posy*/0.1*(0.5-myrand()),/*posz*/0*(0.5-myrand())), 
					  new Vecteur(/*vitx*/0*(0.5-myrand()),/*vity*/0*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					  new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/360*myrand()), 
					  new Vecteur(/*vrotx*/0*1*(0.5-myrand()),/*vroty*/0*1*(0.5-myrand()), /*vrotz*/1*(0.5-myrand())), 
					  /*couleur*/(ecart % 12),/*alpha=opacite*/128,/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,
					  /*lifetime*/500,/*scale*/0.3,/*palette*/NULL)
			    );
      // de la couleur de l'écart % 12	
    }
  }
};
// alors maintenant c'est technique, je crée l'intervalleur et comme son constructeur ne nécéssite pas
// l'initialisation d'open gl, je peux le faire librement en tout bonheur en me disant que je trippe totalement
// parce que je peux créer cette intervalleur2 comme une variable globale
Intervalleur2 *intervalleur2=new Intervalleur2();
// ensuite je me téléporte dans mon programme
// et maintenant je crée un intervalleur3
class Intervalleur3 {// dedans j'ai un tableau à 2 entrée
public:
  int intervalles[7*12][7*12];
  // je me téléporte dans mon programme pour ajouter une touche_avant_la_precedente, donc ça va
  // être près de touche_precedente et de touche_en_cours
  Intervalleur3() {// j'initialise mon tableau 
    for (int i=0;i<7*12;i++) {	
      for (int j=0;j<7*12;j++) {
	// je garde dans un coin de ma teuté que on pourrait afficher une plus grande
	// particule comme achievement quand tous les intervalles ont été joué mais aprés bon c'est sympa aussi
	// de se dire qu'on peut profiter de l'objet sans particules supplémentaires qui s'affichent
	intervalles[i][j]=0;
      }
    }
  }
  // et j'ai un qui est appelé à chaque frame
  void process() {
    if (touche_avant_la_precedente==-1) 
      return;
    int ecart1=abs(touche_en_cours-touche_precedente);
    int ecart0=abs(touche_avant_la_precedente-touche_precedente);
    if (intervalles[ecart0][ecart1]==0) {
      // si c'est le cas, on l'y place, je parle de l'écart, et pas de ma fille à la dass
      intervalles[ecart0][ecart1]=1;
      // et on génère une particule
      gp->ajouter_particule(new Particule(
					  new Vecteur(/*posx*/0.1*(0.5-myrand()),/*posy*/0.1*(0.5-myrand()),/*posz*/0*(0.5-myrand())), 
					  new Vecteur(/*vitx*/0*(0.5-myrand()),/*vity*/0*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					  new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/360*myrand()), 
					  new Vecteur(/*vrotx*/0*1*(0.5-myrand()),/*vroty*/0*1*(0.5-myrand()), /*vrotz*/1*(0.5-myrand())), 
					  /*couleur*/(ecart0 % 12),/*alpha=opacite*/64,/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,
					  /*lifetime*/500,/*scale*/0.1*(ecart1 % 12),/*palette*/NULL)
			    );
    }
  }
};

Intervalleur3 *intervalleur3=new Intervalleur3();
class Intervalleur4 {
public:
  int intervalles[7*12][7*12][7*12];
  Intervalleur4() { 
    for (int i=0;i<7*12;i++) {	
      for (int j=0;j<7*12;j++) {
	for (int k=0;k<7*12;k++) {
	  intervalles[i][j][k]=0;
	}
      }
    }
  }
  // et j'ai un qui est appelé à chaque frame
  void process() {
    if (touche_avant_avant_la_precedente==-1) 
      return;
    int ecart1=abs(touche_en_cours-touche_precedente);
    int ecart0=abs(touche_avant_la_precedente-touche_precedente);
    int ecartm1=abs(touche_avant_avant_la_precedente-touche_avant_la_precedente);
    if (intervalles[ecartm1][ecart0][ecart1]==0) {
      intervalles[ecartm1][ecart0][ecart1]=1;
      // et on génère une particule
      gp->ajouter_particule(new Particule(
					  new Vecteur(/*posx*/0.4*(0.5-myrand()),/*posy*/0.4*(0.5-myrand()),/*posz*/0*(0.5-myrand())), 
					  new Vecteur(/*vitx*/0.2*(0.5-myrand()),/*vity*/0.2*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					  new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/360*myrand()), 
					  new Vecteur(/*vrotx*/0*1*(0.5-myrand()),/*vroty*/0*1*(0.5-myrand()), /*vrotz*/1*(0.5-myrand())), 
					  /*couleur*/(ecart0 % 12),/*alpha=opacite*/32*(1+(ecartm1 % 12)/12),/*resistance_fluide_k*/0.01,/*force_de_rappel_k*/0.0005,
					  /*lifetime*/20,/*scale*/0.1*(ecart1 % 12),/*palette*/NULL)
			    );
    }
  }
};
#define dts_nb_notes_max 512
class DetecteurDeSequences {
public:
  Liste<int> *tableau_des_listes_des_positions_des_occurences_des_notes_dans_le_tableau_des_notes[12];
  int tableau_des_notes[dts_nb_notes_max];
  int nombre_de_notes_dans_le_tableau_des_notes=0;
  int index_de_la_derniere_note_dans_le_tableau_des_notes;
  int sequence[512];
  int sequence_max[512];
  int sequence_trouvee[512];
  int onote=-1;
  int onote_time=0;
  int taille_sequence_max=0;
  int taille_sequence_trouvee=0;
  int nouvelle_sequence_trouvee=0;
  int nouvelle_sequence_maximale_trouvee=0;
  DetecteurDeSequences() {		
    for (int i=0;i<12;i++) 
      tableau_des_listes_des_positions_des_occurences_des_notes_dans_le_tableau_des_notes[i]=new Liste<int>();
  }
  void process(int note, int note_time) {

    if ((note==onote) && (note_time==onote_time))
      return;
    if (nombre_de_notes_dans_le_tableau_des_notes==dts_nb_notes_max) {
      nombre_de_notes_dans_le_tableau_des_notes=0;
      for (int i=0;i<12;i++) {
	delete tableau_des_listes_des_positions_des_occurences_des_notes_dans_le_tableau_des_notes[i];
	tableau_des_listes_des_positions_des_occurences_des_notes_dans_le_tableau_des_notes[i]=new Liste<int>();
      }
      taille_sequence_max=0;
    }

    tableau_des_notes[nombre_de_notes_dans_le_tableau_des_notes]=note;
    nombre_de_notes_dans_le_tableau_des_notes=nombre_de_notes_dans_le_tableau_des_notes+1;

    index_de_la_derniere_note_dans_le_tableau_des_notes=nombre_de_notes_dans_le_tableau_des_notes-1;
    Maille<int> *p=tableau_des_listes_des_positions_des_occurences_des_notes_dans_le_tableau_des_notes[note]->premier;
    while (p!=NULL) {
      int position_de_l_occurence_en_cours_de_la_note_dans_le_tableau_des_notes=*(p->ptr);
      int l=0;
      int taille_sequence=0;
      while ((position_de_l_occurence_en_cours_de_la_note_dans_le_tableau_des_notes-l>=0) && 
	     (tableau_des_notes[index_de_la_derniere_note_dans_le_tableau_des_notes-l]==
	      tableau_des_notes[position_de_l_occurence_en_cours_de_la_note_dans_le_tableau_des_notes-l])) {
	sequence[taille_sequence]=
	  tableau_des_notes[position_de_l_occurence_en_cours_de_la_note_dans_le_tableau_des_notes-l];
	taille_sequence=taille_sequence+1;
	l=l+1;
      } /*endwhile*/
      if ((index_de_la_derniere_note_dans_le_tableau_des_notes-l) == 
	  position_de_l_occurence_en_cours_de_la_note_dans_le_tableau_des_notes) {
	// delete new-line in vim : J to append next line to current line
	// alors dans ce cas là c'est intéressant
	printf("il se pourrait bien que ce soit le seul cas où il y a une séquence composée d'une répétition de séquences \n");
      }
      // alors c'est amusant mais le problème c'est quand parfois je me dis que je suis un enfoiré
      // qui travaille trop parce qu'on m'a dit de ne pas travailler parce que c'est nul de 
      // travailler sauf que je ne travaille pas vraiment, je passe le temps, enfin je ne sais pas
      // exactement ce que je fais je m'en fous, mon ordi me rend fou, je ferais mieux d'aller me
      // coucher et pleurer parce que je suis incapable de formuler clairement pourquoi en fait
      // quand je repete la même note c'est détecté comme une séquence et je ne veux pas que ce soit
      // détecté comme une séquence 
      // je suis maintenant dans le détecteur de séquence, c'est comme un voyage dans un endroit 
      // où il n'y a personne, il n'y a personne mais il y a un but et ce but est clair : 
      // on ne veut pas retenir les séquences de répétitions de triplés par exemple,
      // alors quand est ce que ça se passe par exemple, alors on ne sait pas bien, pour le moment
      // on est dans un film, on est dans hacker et on est au clavier et les mots arrivent comme cela
      // et on peut corriger, on peut se déplacer dans le programme et on vit dangereusement, houlàlà
      // alors quoi... que faire... on trouve une séquence, on la trouve comment, on la trouve d'une 
      // certaine façon, et on plonge dans l'algo et plus personne ne peut nous rejoindre car nous y
      // sommes encore plus profond que dans l'eau...on trouve une séquence donc et la séquence va 
      // se répéter dans un cas bien précis et on aime ce cas bien précis, on l'aime tellement
      // ce cas bien précis, on veut le chérir, on veut l'extraire de la réalité des idées, c'est mal dit
      // mais c'est ainsi, on veut l'extraire, c'est le cas (1)
      if (taille_sequence>12) { // nombre arbitraire minimal de notes d'une séquence pour qu'elle soit retenue
	taille_sequence_trouvee=taille_sequence;
	for (int i=0;i<taille_sequence;i++) {
	  sequence_trouvee[i]=sequence[taille_sequence-1-i];

	}
	printf("nouvelle répétition\n");
	nouvelle_sequence_trouvee=1;
      } /*endif*/
	
      if (taille_sequence>=taille_sequence_max) {
	taille_sequence_max=taille_sequence;
	for (int i=0;i<taille_sequence;i++) {
	  sequence_max[i]=sequence[taille_sequence-1-i];
	}
	nouvelle_sequence_maximale_trouvee=1;
	printf("nouvelle répétition plus grande\n");
      } /*endif*/
      p=p->suivant;
    } /*endwhile*/
    if (nouvelle_sequence_trouvee) {
      for (int i=0;i<taille_sequence_trouvee;i++) {
	gp->ajouter_particule(new Particule(
					    new Vecteur(/*posx*/-0.5+0.4*(0.5-myrand()),/*posy*/0.5+0.1*(0.5-myrand()),/*posz*/0*(0.5-myrand())), 
					    new Vecteur(/*vitx*/0.02*(0.5-myrand()),/*vity*/0.02*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					    new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/360*myrand()), 
					    new Vecteur(/*vrotx*/0*1*(0.5-myrand()),/*vroty*/0*1*(0.5-myrand()), /*vrotz*/1*(0.5-myrand())), 
					    /*couleur*/sequence_trouvee[i],/*alpha=opacite*/128,/*resistance_fluide_k*/0.01,
					    /*force_de_rappel_k*/0,
					    /*lifetime*/20,/*scale*/0.01,/*palette*/NULL)
			      );
	// on changera après le scale

      } /*endfor*/
      nouvelle_sequence_trouvee=0;
    }
	
    if (nouvelle_sequence_maximale_trouvee) {
      for (int i=0;i<taille_sequence_max;i++) {
	gp->ajouter_particule(new Particule(
					    new Vecteur(/*posx*/0.4*(0.5-myrand()),/*posy*/0.4*(0.5-myrand()),/*posz*/0*(0.5-myrand())), 
					    new Vecteur(/*vitx*/0.02*(0.5-myrand()),/*vity*/0.02*(0.5-myrand()),/*vitz*/0*(0.5-myrand())), 
					    new Vecteur(/*rotx*/0*myrand(),/*roty*/0*myrand(),/*rotz*/360*myrand()), 
					    new Vecteur(/*vrotx*/0*1*(0.5-myrand()),/*vroty*/0*1*(0.5-myrand()), /*vrotz*/1*(0.5-myrand())), 
					    /*couleur*/sequence_max[i],/*alpha=opacite*/128,/*resistance_fluide_k*/0.01,
					    /*force_de_rappel_k*/0,
					    /*lifetime*/20,/*scale*/0.5,/*palette*/NULL)
			      );
	// on changera après le scale
      } /*endfor*/
      nouvelle_sequence_maximale_trouvee=0;
    }
    tableau_des_listes_des_positions_des_occurences_des_notes_dans_le_tableau_des_notes[note]->
      ajouter(new int(index_de_la_derniere_note_dans_le_tableau_des_notes));

    onote=note;
    onote_time=note_time;
  }

};
DetecteurDeSequences *detecteurdesequences=new DetecteurDeSequences();
const int numSlices = 5;//50;
const int numStacks = 5;//50;
const float R1 = 0.4f; // Rayon intérieur du tore
const float R2 = 1.0f; // Rayon extérieur du tore

void drawTorus(int composante) {



  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  float lightpos[4]={0,0,0,1};
  float lightambientcolor[4]={0,0,0,1};
  float lightdiffusecolor[4]={1,1,1,1};
  float lightspecularcolor[4]={1,1,1,1};
  glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
  //glLightfv(GL_LIGHT0,GL_AMBIENT,lightambientcolor);
  //glLightfv(GL_LIGHT0,GL_SPECULAR,lightspecularcolor);
  glEnable(GL_LIGHTING);
  //glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);  
  float materialspecularcolor[4]={1,1,1,1};
  float materialemissioncolor[4]={0,0,0,1};

  for (int i = 0; i < numSlices; ++i) {
    float theta1 = (static_cast<float>(i) / numSlices) * 2 * M_PI;
    float theta2 = (static_cast<float>(i + 1) / numSlices) * 2 * M_PI;

    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= numStacks; ++j) {
      float phi = (static_cast<float>(j) / numStacks) * 2 * M_PI;

      // Calcul des coordonnées des sommets
      float x1 = (R2 + R1 * cos(phi)) * cos(theta1);
      float y1 = (R2 + R1 * cos(phi)) * sin(theta1);
      float z1 = R1 * sin(phi);

      float x2 = (R2 + R1 * cos(phi)) * cos(theta2);
      float y2 = (R2 + R1 * cos(phi)) * sin(theta2);
      float z2 = R1 * sin(phi);
      // Calcul des normales
      float normal1X = cos(theta1) * cos(phi);
      float normal1Y = sin(theta1) * cos(phi);
      float normal1Z = sin(phi);
      float normal2X = cos(theta2) * cos(phi);
      float normal2Y = sin(theta2) * cos(phi);
      float normal2Z = sin(phi);
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,tabcomposantesa[composante]);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,tabcomposantesa[composante]);
	
      glNormal3f(normal1X, normal1Y, normal1Z);
      glVertex3f(x1, y1, z1);
      glNormal3f(normal2X, normal2Y, normal2Z);
      glVertex3f(x2, y2, z2);
    }
    glEnd();
  }
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
}
class Orbitation {
public:
  int initialized = 0;
  int l[12];
  // les axes de rotations associés à chaques notes
  float rot[12][3]={{0,0,1},{0,0,-1},{0,1,0},{0,-1,0},{1,0,0},{-1,0,0}, 
		    {0,1,1},{0,1,-1},{1,1,0},{1,-1,0},{1,0,1},{-1,0,1}};
  // les axes de translations associés à chaques notes
  float tran[12][3]={{1,0,0},{0,1,0},{-1,0,0},{0,0,1},{0,-1,0},{0,0,-1}, 
		     {1,1,0},{0,1,1},{-1,1,0},{0,1,1},{0,-1,1},{0,1,-1}};


  Orbitation () {}
  void Torus(int composante, int numSlices, int numStacks, float rayon_interieur, float rayon_exterieur) {
    float R1=rayon_interieur;
    float R2=rayon_exterieur;
    //glDisable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    float lightpos[4]={0,0,0,1};
    float lightambientcolor[4]={0,0,0,1};
    float lightdiffusecolor[4]={1,1,1,1};
    float lightspecularcolor[4]={1,1,1,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    //glLightfv(GL_LIGHT0,GL_AMBIENT,lightambientcolor);
    //glLightfv(GL_LIGHT0,GL_SPECULAR,lightspecularcolor);
    glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);  
    float materialspecularcolor[4]={1,1,1,1};
    float materialemissioncolor[4]={0,0,0,1};

    for (int i = 0; i < numSlices; ++i) {
      float theta1 = (static_cast<float>(i) / numSlices) * 2 * M_PI;
      float theta2 = (static_cast<float>(i + 1) / numSlices) * 2 * M_PI;

      glBegin(GL_QUAD_STRIP);
      for (int j = 0; j <= numStacks; ++j) {
	float phi = (static_cast<float>(j) / numStacks) * 2 * M_PI;

	// Calcul des coordonnées des sommets
	float x1 = (R2 + R1 * cos(phi)) * cos(theta1);
	float y1 = (R2 + R1 * cos(phi)) * sin(theta1);
	float z1 = R1 * sin(phi);

	float x2 = (R2 + R1 * cos(phi)) * cos(theta2);
	float y2 = (R2 + R1 * cos(phi)) * sin(theta2);
	float z2 = R1 * sin(phi);
	// Calcul des normales
	float normal1X = cos(theta1) * cos(phi);
	float normal1Y = sin(theta1) * cos(phi);
	float normal1Z = sin(phi);
	float normal2X = cos(theta2) * cos(phi);
	float normal2Y = sin(theta2) * cos(phi);
	float normal2Z = sin(phi);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,tabcomposantesa[composante]);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,tabcomposantesa[composante]);
	
	glNormal3f(normal1X, normal1Y, normal1Z);
	glVertex3f(x1, y1, z1);
	glNormal3f(normal2X, normal2Y, normal2Z);
	glVertex3f(x2, y2, z2);
      }
      glEnd();
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

  }
  int process () {
    if (!initialized) {
      for (int i=0;i<12;i++) {
	l[i]=glGenLists(1);
	glNewList(l[i],GL_COMPILE);
	float k=0.3;
	Torus(i/*composante*/,15/*numslices*/,15/*numstacks*/,k*0.1/*rayon interieur*/,k*1.0/*rayon exterieur*/);
	glEndList();
      }
      initialized = 1;

    }
    //glDisable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    float lightpos[4]={0,0,0,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  
    for (int i=0;i<12;i++) {
      float r=0.1;
      glRotatef(i*360/12.0+360.0*compteur[i]/100,rot[i][0],rot[i][1],rot[i][2]);
      float k=0.02*compteur[i]/100;
      float d=0.2;
      glTranslatef((k+d)*tran[i][0],(k+d)*tran[i][1],(k+d)*tran[i][2]);
      glPushMatrix();
      glScalef(1+compteur[i]/100,1+compteur[i]/100,1+compteur[i]/100);
      glCallList(l[i]);
      glPopMatrix();
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);


  }
};
Orbitation *orbitation = new Orbitation();
// pour indenter automatiquement une partie de code, la sélectionner avec v, puis taper =
class HomotheticCube {
private:
  GLfloat vertices[8][3] = {
    {-0.5, -0.5, -0.5},
    {0.5, -0.5, -0.5},
    {0.5, 0.5, -0.5},
    {-0.5, 0.5, -0.5},
    {-0.5, -0.5, 0.5},
    {0.5, -0.5, 0.5},
    {0.5, 0.5, 0.5},
    {-0.5, 0.5, 0.5}
  };

  int faces[6][4] = {
    {0, 1, 2, 3},
    {1, 5, 6, 2},
    {5, 4, 7, 6},
    {4, 0, 3, 7},
    {4, 5, 1, 0},
    {3, 2, 6, 7}
  };

  GLfloat homotheties[6] = {1.2, 0.8, 1.5, 0.7, 1.3, 0.9};
  GLfloat transformedVertices[8][3];
  GLfloat normales[8][3];
  void initHomotheties() {
    for (int i=0;i<6;i++) {
      homotheties[i]=(1+compteur[i]/100.0-compteur[2*i+1]/100.0);
    }
    for (int i=0;i<8;i++) {
      transformedVertices[i][0]=vertices[i][0];
      transformedVertices[i][1]=vertices[i][1];
      transformedVertices[i][2]=vertices[i][2];
    }
  }
  void applyHomotheties() {
    initHomotheties();
    for (int i = 0; i < 6; ++i) {
      GLfloat centerX = 0.0f;
      GLfloat centerY = 0.0f;
      GLfloat centerZ = 0.0f;
      for (int j = 0; j < 4; ++j) {
	int vertexIndex = faces[i][j];
	centerX += transformedVertices[vertexIndex][0];
	centerY += transformedVertices[vertexIndex][1];
	centerZ += transformedVertices[vertexIndex][2];
      }

      centerX /= 4.0f;
      centerY /= 4.0f;
      centerZ /= 4.0f;

      for (int j = 0; j < 4; ++j) {
	int vertexIndex = faces[i][j];
	GLfloat xOffset = transformedVertices[vertexIndex][0] - centerX;
	GLfloat yOffset = transformedVertices[vertexIndex][1] - centerY;
	GLfloat zOffset = transformedVertices[vertexIndex][2] - centerZ;
	transformedVertices[vertexIndex][0] = centerX + xOffset * homotheties[i];
	transformedVertices[vertexIndex][1] = centerY + yOffset * homotheties[i];
	transformedVertices[vertexIndex][2] = centerZ + zOffset * homotheties[i];
      }
    }
  }

  void calculateNormals() {
    for (int i = 0; i < 8; ++i) {
      GLfloat normalX = 0.0f;
      GLfloat normalY = 0.0f;
      GLfloat normalZ = 0.0f;
      for (int j = 0; j < 6; ++j) {
	for (int k = 0; k < 4; ++k) {
	  int vertexIndex = faces[j][k];
	  if (vertexIndex == i) {
	    normalX += homotheties[j] * (faces[j][k] / 4.0f - 0.5f);
	    normalY += homotheties[j] * (faces[j][k] / 4.0f - 0.5f);
	    normalZ += homotheties[j] * (faces[j][k] / 4.0f - 0.5f);
	  }
	}
      }
      GLfloat length = std::sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
      if (length != 0.0f) {
	normalX /= length;
	normalY /= length;
	normalZ /= length;
      }
      normales[i][0] = normalX;
      normales[i][1] = normalY;
      normales[i][2] = normalZ;
    }
  }

public:
  void draw() {
    applyHomotheties();
    calculateNormals();

    float lightpos[4]={0,0,0,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL); // si ça marche je vais pouvoir définir la couleur de l'objet
    // sans passer par glMaterialfv
    // ok on est cool, on est dans une ambiance médiévale, petit dulcimer...
    for (int i = 0; i < 6; ++i) {
      glBegin(GL_TRIANGLES);
      for (int j = 0; j < 3; ++j) {
	int vertexIndex = faces[i][j];
	glColor4ub(compub(i),192);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,tabcomposantesa[i]);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,tabcomposantesa[i]);
	glNormal3f(normales[vertexIndex][0], normales[vertexIndex][1], normales[vertexIndex][2]);
	glVertex3f(transformedVertices[vertexIndex][0], transformedVertices[vertexIndex][1], transformedVertices[vertexIndex][2]);
      }
      glEnd();

      glBegin(GL_TRIANGLES);
      for (int j = 1; j < 4; ++j) {
	int vertexIndex = faces[i][(j + 1) % 4];
	glColor4ub(compub(i),192);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,tabcomposantesa[i]);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,tabcomposantesa[i]);
	glNormal3f(normales[vertexIndex][0], normales[vertexIndex][1], normales[vertexIndex][2]);
	glVertex3f(transformedVertices[vertexIndex][0], transformedVertices[vertexIndex][1], transformedVertices[vertexIndex][2]);
      }
      glEnd();
    }
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
  }
};

HomotheticCube *hcube=new HomotheticCube();
class Dodecaedre {
public:

  GLfloat phi = (1 + sqrt(5)) / 2; // Nombre d'or

  GLfloat verts[20][3] = {
    {-1, phi, 0}, {1, phi, 0}, {-1, -phi, 0}, {1, -phi, 0},
    {0, -1, phi}, {0, 1, phi}, {0, -1, -phi}, {0, 1, -phi},
    {phi, 0, -1}, {phi, 0, 1}, {-phi, 0, -1}, {-phi, 0, 1},
    {0, -phi, 1}, {0, phi, 1}, {0, -phi, -1}, {0, phi, -1},
    {1, phi, 0}, {-1, phi, 0}, {0, -1, -phi}, {0, 1, -phi}
  };

  GLint faces[12][5] = {
    {0, 11, 5, 1, 4}, {0, 5, 10, 6, 11},
    {1, 5, 9, 2, 4}, {1, 9, 3, 8, 10},
    {0, 1, 10, 8, 7}, {0, 7, 6, 9, 5},
    {3, 9, 6, 7, 2}, {3, 2, 7, 8, 8},
    {11, 6, 10, 8, 1}, {11, 1, 4, 2, 9},
    {10, 5, 11, 9, 6}, {4, 2, 7, 3, 8}
  };
  void drawVertexNumbers() {
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(1.1f, 1.1f, 1.1f);
    for (int i = 0; i < 20; ++i) {
      string vertexNumber = std::to_string(i);
      for (char c : vertexNumber) {
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
      }
      glRasterPos3fv(verts[i]);
    }
    glEnable(GL_DEPTH_TEST);
  }
  void draw() {
    float lightpos[4]={0,0,0,1};
    glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
	
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glScalef(0.5,0.5,0.5);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 12; ++i) {
      glColor4ub(compub(i),196);
      for (int j = 0; j < 5; ++j) {
	// on va calculer cette chère normale
	float nor[3];
	nor[0]=verts[faces[i][j]][0];
	nor[1]=verts[faces[i][j]][1];
	nor[2]=verts[faces[i][j]][2];
	normalize(nor);
	glNormal3f(nor[0], nor[1], nor[2]);
	glVertex3fv(verts[faces[i][j]]);
      }
    }
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    drawVertexNumbers();
  }
};
Dodecaedre *dodeca = new Dodecaedre ();
class MemVideo {
public:

  // Définition des dimensions de l'image
  static const int iw = 2*64;
  static const int ih = 2*64;
  int k1;
  int k2;
  int k3;
  int k4;
  int k5;
  int k6;
  int k7;
  int k8;
  // Tableau de pixels (utilisé comme exemple)
  unsigned char imageData[ih][iw][3];
  // alors on va avoir une table de sinus d'une certaine taille disons combien
  // disons 1024 valeurs
  int sintabinitialized=0;
  float sintab[1024];
  float mysin(float x) {
    if (!sintabinitialized) {
      float x=0;
      float incx=2*M_PI/1024;
      for (int i=0;i<1024;i++) {
	sintab[i]=sin(x);
	x+=incx;
      }
      sintabinitialized=1;
    }
    return sintab[ int(1024 * (x / (2 * M_PI))) % 1024 ];
  }
  unsigned int mytexture;
  void effect_number_one() {
    for (int y=0;y<64;y++) {
      for (int x=0;x<64;x++) {
	float k=2*M_PI/64;
	float kv=(vbl % 360)/360.0;
	imageData[y][x][0]=255*mysin((x+mysin(y*k1*k))*k3*k)*mysin(y*k2*k+((5*2*M_PI)*kv));
	imageData[y][x][1]=255*mysin((x+mysin(y*k7*k))*k*k5+(k8*2*M_PI)*(vbl % 360)/360.0)*mysin(y*k*k5);
	imageData[y][x][2]=255*mysin(y*k4*k+(2*M_PI)*(vbl % 360)/360.0)*mysin(y*k*k6);
      }
    }
	
  }
  float fonkx(int i, int x) {
    return (i+1)*note_on_off[i]*x/10;
  }
  float fonky(int i, int y) {
    return (i+1)*note_on_off[i]*y/10;
  }
  void effect_number_two() {
    for (int y=0;y<64;y++) {
      for (int x=0;x<64;x++) {
	float k=2*M_PI/64;
	float kv=(vbl % 360)/360.0;
	/* alors on a 12 notes et 24 bits très bien et donc... on allume les 2 bits du plan quand la note 
	   est jouée ? donc bah ça va faire un truc... alors quoi ben bof pas cool... pas très envie ?
	   alors quoi ... je ne sais pas de quoi ils parlent, il fait bon ici... alors que va t on faire
	   tout cela est bien tranquille ... les femmes, enfin, certaines femmes disent qu'elles sont
	   géniales et en fait c'est bizarre parce que si elles le disent c'est qu'elles ne le pensent pas
	   vraiment ? je ne sais pas... ce serait pas génial en fait, je veux 
	*/
	float sx1=0;
	float sy1=0;
	float sx2=0;
	float sy2=0;
	float sx3=0;
	float sy3=0;
	for (int i=0;i<12;i++) {
	  if ((i==0) || (i==3) || (i==6) || (i==9)) {
	    sx1+=fonkx(i,x);
	    sy1+=fonky(i,y);
	  }
	  if ((i==1) || (i==4) || (i==7) || (i==10)) {
	    sx2+=fonkx(i,x);
	    sy2+=fonky(i,y);
	  }
	  if ((i==2) || (i==5) || (i==8) || (i==11)) {
	    sx3+=fonkx(i,x);
	    sy3+=fonky(i,y);
	  }
	}
	imageData[y][x][0]=255*mysin(sx1)*mysin(sy1);
	imageData[y][x][1]=255*mysin(sx2)*mysin(sy2);
	imageData[y][x][2]=255*mysin(sx3)*mysin(sy3);
      }
    }
	
  }
  void display() {

    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadIdentity();
    //glTranslatef(0,0,-3);
    //effect_number_one();
    effect_number_two();
    glTexImage2D(GL_TEXTURE_2D, 0/*mipmap level*/, GL_RGB, iw, ih, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex2f( 1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex2f( 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0);
    glEnd();

    glFlush();
    glPopMatrix();
  }
  MemVideo() {
    glGenTextures(1,&mytexture);
    glBindTexture(GL_TEXTURE_2D,mytexture);
    // ce qui suit doit être aprés ce qui précède
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /*filtre à utiliser lorsque l'image est dézoomée*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /*pas d'interpolation, le pixel le plus prés est pris*/
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /*filtre à utiliser lorsque l'image est zoomée*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /*pas d'interpolation, le pixel le plus prés est pris*/
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);/*comportement quand la coordonnée de texture n'est pas */
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);/*comprise entre 0 et 1, donc on s'en fout*/
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);



    k1=1+int(7*myrand());
    k2=1+int(7*myrand());
    k3=1+int(7*myrand());
    k4=1+int(7*myrand());
    k5=1+int(7*myrand());
    k6=1+int(7*myrand());
    k7=1+int(7*myrand());
    k8=1+int(7*myrand());
	
  }
};
MemVideo *memvideo;
class Mandelbrot {
public:
  unsigned char *pix;
#define pix(i,j,k) pix[3*i+3*w*j+k]
  int w;
  int h;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  Palette *pal;
  int nmax=160;
  void set_palette() {
    float debuth=myrand();
    float finh=debuth+0.3+myrand()*(1-debuth-0.3);
    pal = new Palette(/*debuth*/debuth,/*finh*/finh,/*nb_couleurs*/nmax,/*opacity*/0); 
  }
  Mandelbrot(int w,int h) {
    set_palette();
    pix = (unsigned char *)malloc(h*w*3*sizeof(unsigned char));
    this->w=w;
    this->h=h;
    randomize();	
  }
  Mandelbrot(int w,int h,int nmax) {
    this->nmax=nmax;
    Mandelbrot(w,h);
  }
  void randomize() {
    float mxmin=-1;
    float mxmax=1;
    float mymin=-1;
    float mymax=1;
    float xmin=mxmin+myrand()*(mxmax-mxmin);
    float xmax=xmin+myrand()*(mxmax-xmin);
    float ymin=mymin+myrand()*(mymax-mymin);
    float ymax=ymin+myrand()*(mymax-ymin);
    calcule(xmin,xmax,ymin,ymax);
  }
  Mandelbrot(float xmin, float xmax, float ymin, float ymax, int w, int h) {
    set_palette();
    pix = (unsigned char *)malloc(h*w*3*sizeof(unsigned char));
    this->w=w;
    this->h=h;
    calcule(xmin,xmax,ymin,ymax);
  }
  Mandelbrot(float xmin, float xmax, float ymin, float ymax, int w, int h, Palette *pal) {
    this->pal=pal;
    pix = (unsigned char *)malloc(h*w*3*sizeof(unsigned char));
    this->w=w;
    this->h=h;
    calcule(xmin,xmax,ymin,ymax);
  }

  int is_monochrome() {
    unsigned char r=pix[0];
    unsigned char v=pix[1];
    unsigned char b=pix[2];
    int oui=1;
    for (int ofs=0;ofs<3*w*h;ofs+=3) {
      if ((pix[ofs+0]!=r) || (pix[ofs+1]!=v) || (pix[ofs+2]!=b)) {
	oui=0;
	break;
      }
    }
    return oui;
  }
  void calcule(float xmin, float xmax, float ymin, float ymax) {
    /*
      zn+1=zn^2+c
      avec c=x+yi
      (xn+yin)^2=xn^2-yn^2+2xnyni
      zn+1=xn+1+yin+1=xn^2-yn^2+2xnyni+x+yi
      xn+1=xn^2-yn^2+x
      yn+1=2xn*yn+y
    */

    float y=ymin;
    float incy=(ymax-ymin) / h;
    float incx=(xmax-xmin) / w;
    int ofs=0;
    for (int j=0;j<h;j++) {
      float x=xmin;
      for (int i=0;i<w;i++) {
	float xn=0;
	float yn=0;
	float xnp1;
	float ynp1;
	float norm;
	int n=0;
	do {
	  xnp1=sqr(xn) - sqr(yn) + x;
	  ynp1=2*xn*yn + y;
	  xn=xnp1;
	  yn=ynp1;
	  norm=sqr(xnp1)+sqr(ynp1);
	  n++;
	  if (n>nmax) break;
	} while (norm < 4);
	if (n>=nmax) {
	  pix[ofs+0] = 0;
	  pix[ofs+1] = 0;
	  pix[ofs+2] = 0;
	} else {
	  pix[ofs+0] = pal->couleurs[n][0];
	  pix[ofs+1] = pal->couleurs[n][1];
	  pix[ofs+2] = pal->couleurs[n][2];
	}
	ofs+=3;
	x+=incx;
      }
      y+=incy;
    }
    this->xmin=xmin;
    this->xmax=xmax;
    this->ymin=ymin;
    this->ymax=ymax;
  }
  void zoom(float zoomfactor) {
    if (is_monochrome()) {
      randomize();
    } else {
      float newxmin=xmin+(xmax-xmin)/zoomfactor;
      float newxmax=xmax-(xmax-xmin)/zoomfactor;
      float newymin=ymin+(ymax-ymin)/zoomfactor;
      float newymax=ymax-(ymax-ymin)/zoomfactor;
      calcule(newxmin,newxmax,newymin,newymax);
    }
  }
};


class MandelMap {
public:

	static const int iw = 128;//2*64;
	static const int ih = 128;//2*64;
	unsigned int textures[12];
	int onote=-1;
	int nb_repetitions_de_la_note_en_cours=0;
	int nb_repetitions_de_la_note_en_cours_avant_zoom=7;
	void display() {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		int alphas[12];
		int intensitemax=0;
		//recherche de l'intensité max
		for (int i=0;i<12;i++) {
			if (notes_val_dans_l_octave[i]>intensitemax)
				intensitemax=notes_val_dans_l_octave[i];
		}
		int nb_couches=0;
		for (int i=0;i<12;i++) {
			if (note_on_off[i])
				nb_couches=nb_couches+1;
		}

		if (nb_couches>0) {
			// on va commencer par trier ces couches
			int i=0;
			int ptr[12]={0,1,2,3,4,5,6,7,8,9,10,11};
			int echange;
			do {
				i=0;
				echange=0;
				do {
					if (notes_val_dans_l_octave[ptr[i]] < notes_val_dans_l_octave[ptr[i+1]]) {
						int aux=ptr[i];
						ptr[i]=ptr[i+1];
						ptr[i+1]=aux;
						echange=1;
					}
					i=i+1;
				} while ((i!=11) && (echange==0));
			} while (echange==1);
			//on normalise pour que la couche avec le val max soit avec un alpha de 255 et que les autres aient des alphas proportionnels
			//on met tous les alphas des couches
	
			for (int i=0;i<12;i++) {
				alphas[i]=(int)(255*((float)(notes_val_dans_l_octave[i]))/((float)(intensitemax)) / nb_couches );
			}
			/*
			for (int i=0;i<12;i++) {
				alphas[ptr[i]]= alphas[ptr[i]] / pow(2,i);
			}*/
			for (int i=0;i<12;i++) {
				if ((note_on_off[ptr[i]])) {
					if (note_on_off[ptr[i]]) {
					    glBindTexture(GL_TEXTURE_2D,textures[ptr[i]]);
					    glBegin(GL_QUADS);
						glColor4ub(255,255,255,alphas[ptr[i]]); // sinon le starfield en changeant le glcolor modifie la luminosité de la texture
						glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1);
						glTexCoord2f(1.0, 0.0); glVertex3f( 1.0, -1.0, 1);
						glTexCoord2f(1.0, 1.0); glVertex3f( 1.0, 1.0, 1);
						glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0,1);
						glEnd();
					}
				}
			}	
		}
	    glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	
	}




  MandelMap() {
    glGenTextures(12,textures);
    for (int i=0;i<12;i++) {
		SDL_Surface *surface;
		char s[128];
		int numdirpar=1;
	    sprintf(s,"/home/pi/prg/colormusic/img/i%d/%d.jpg",numdirpar,i+1);

		surface = IMG_Load(s);


      glBindTexture(GL_TEXTURE_2D,textures[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR/*GL_NEAREST*/); /*pas d'interpolation, le pixel le plus prés est pris*/
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR/*GL_NEAREST*/); /*pas d'interpolation, le pixel le plus prés est pris*/
      glTexImage2D(GL_TEXTURE_2D, 
		   0/*mipmap level*/, 
		   GL_RGB,// internal format 
		   surface->w, 
		   surface->h, 
		   0/*width of border*/, 
		   GL_RGB, 
		   GL_UNSIGNED_BYTE, 
		   surface->pixels);
		SDL_FreeSurface(surface);
    }

  }
};
MandelMap *mandelmap;
class Cercle {

public:
  int nb_de_segments;
  float x,y,z;
  float rayon;
  int couleur;
  int l;
  void genere() {
    glLineWidth(1);
    glBegin(GL_LINE_STRIP); 
    {
      glColor3ub(comp(couleur));
      for (int i=0; i<nb_de_segments; i++) {
	glVertex3f(rayon*cos(i*M_PI*2/nb_de_segments),rayon*sin(i*M_PI*2/nb_de_segments),0);
      }
      glVertex3f(rayon*cos(0*M_PI*2/nb_de_segments),rayon*sin(0*M_PI*2/nb_de_segments),0);
				
    }
    glEnd();
  }
  void pushcoords(float x, float y, float z, float **ptab, int *n) {
    ptab[*n][0]=x;
    ptab[*n][1]=y;
    ptab[*n][2]=z;
    (*n)++;
  }
  void produit(float **ptab) {
    int n=0;
    for (int i=0; i<nb_de_segments; i++) {
      pushcoords(x+rayon*cos(i*M_PI*2/nb_de_segments),y+rayon*sin(i*M_PI*2/nb_de_segments),z,ptab,&n);
    }
    //pushcoords(x+rayon*cos(0*M_PI*2/nb_de_segments),y+rayon*sin(0*M_PI*2/nb_de_segments),z,ptab,&n);
  }
  Cercle(float x, float y, float z, float rayon, int nb_de_segments, float couleur) {
    this->x=x;
    this->y=y;
    this->z=z;
    this->rayon=rayon;
    this->nb_de_segments=nb_de_segments;
    this->couleur=couleur;
    l=glGenLists(1);
    glNewList(l,GL_COMPILE);
    genere();
    glEndList();
  }
  void affiche() {
    glLineWidth(1);
    glBegin(GL_LINE_STRIP); 
    {
      glColor3ub(comp(couleur));
      for (int i=0; i<nb_de_segments; i++) {
	glVertex3f(x+rayon*cos(i*M_PI*2/nb_de_segments),y+rayon*sin(i*M_PI*2/nb_de_segments),z);
      }
      glVertex3f(x+rayon*cos(0*M_PI*2/nb_de_segments),y+rayon*sin(0*M_PI*2/nb_de_segments),z);
				
    }
    glEnd();
	
  }
};
class CirclesTunnel {
public:
  float incz=0.05;
  float rrd=0.4; // changement de directions du worm
  float rayon=1;
  float maxz=1;
  int nbs=12; // nombre de segments des cercles
  Liste<Cercle> *ldcdc; //liste des centres des cercles
  float lastx=0;
  float lasty=0;
  float zmin=-10;
  int onote=-1;
  int onote_time=0;
  float viewx=0;
  float viewy=0;
  float lastz=maxz;
  float stepx;
  float stepy;
  Maille<Cercle> *dernier_en_cours=NULL;
  float **tabcoords1;
  float **tabcoords2;
  float **pcoordsactu;
  float **pcoordsprec;
  CirclesTunnel() {
    ldcdc = new Liste<Cercle>();
    tabcoords1=(float**)malloc(sizeof(float*)*nbs);
    tabcoords2=(float**)malloc(sizeof(float*)*nbs);
    for (int i=0;i<nbs;i++) {
      tabcoords1[i]=(float*)malloc(sizeof(float)*3);
      tabcoords2[i]=(float*)malloc(sizeof(float)*3);
    }
    pcoordsactu=tabcoords1;
    pcoordsprec=tabcoords2;
  }
  ~CirclesTunnel() {
    for (int i=0;i<nbs;i++) {
      free(tabcoords1[i]);
      free(tabcoords2[i]);
    }
    free(tabcoords1);
    free(tabcoords2);
  }
  void process() {
    Maille<Cercle> *p;
    p=ldcdc->premier;
    while (p!=NULL) {
      Cercle *c=p->ptr;
      c->z+=incz;
      if (c->z > maxz) {
	lastz=c->z;
	if (p->precedent != NULL) {
	  p->precedent->suivant=p->suivant;
	} else {
	  ldcdc->premier=p->suivant;
	}
	if (p->suivant!=NULL) {
	  p->suivant->precedent=p->precedent;
	} else {
	  ldcdc->dernier=p->precedent;
	}
	ldcdc->nb_elements--;
	Maille<Cercle> *paux=p->suivant;
	delete(p);
	p=paux;
      } else {
	p=p->suivant;
      }
    }
    if ((note_en_cours()!=onote) || (note_en_cours_time()!=onote_time)) {
      float theta=myrand()*M_PI*2;
      float rd=myrand()*rrd;
      float x=lastx+rd*cos(theta);
      float y=lasty+rd*sin(theta);
      Cercle *c=new Cercle(x,y,zmin,rayon,nbs,note_en_cours());
      ldcdc->liste_inserer_first(c);
      lastx=x;
      lasty=y;
      onote=note_en_cours();
      onote_time=note_en_cours_time();
    }


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    Maille<Cercle> *dernier=ldcdc->dernier;
    if (dernier==NULL) {
    } else {
      if (dernier!=dernier_en_cours) {
	dernier_en_cours=dernier;
	float nbsteps=abs((dernier->ptr->z - lastz)/incz);
	stepx = (dernier->ptr->x - viewx) / nbsteps;
	stepy = (dernier->ptr->y - viewy) / nbsteps;
      } else {
	viewx+=stepx;
	viewy+=stepy;
      }
    }
    if (dernier!=NULL) {
      gluLookAt(viewx, viewy, maxz,
		viewx, viewy, 0,
		0,1,0);
      p=ldcdc->premier;
      if (ldcdc->nb_elements==1) 
	p->ptr->affiche();
      else while (p!=NULL) {
	  Cercle *c=p->ptr;
	  c->produit(pcoordsactu);
	  if (p->precedent != NULL) {
	    tisse(pcoordsactu,pcoordsprec,c->couleur);
	  } else {
	  }
	  float **paux=pcoordsprec;
	  pcoordsprec=pcoordsactu;
	  pcoordsactu=paux;
	  p=p->suivant;
	}
    }
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
  }
  void tisse(float **pactu, float **pprec, int couleur) {
    float **pa=pactu;
    float **pp=pprec;

    for (int i=0;i<nbs-1;i++) {
      glBegin(GL_LINE_STRIP);
      glColor4ub(comp(couleur),255);	
      glVertex3f(pa[i][0],pa[i][1],pa[i][2]);
      glVertex3f(pp[i][0],pp[i][1],pp[i][2]);
      glVertex3f(pp[i+1][0],pp[i+1][1],pp[i+1][2]);
      glVertex3f(pa[i+1][0],pa[i+1][1],pa[i+1][2]);
      glVertex3f(pa[i][0],pa[i][1],pa[i][2]);
      glEnd();
    }
    glBegin(GL_LINE_STRIP);
    glColor4ub(comp(couleur),255);	
    glVertex3f(pa[nbs-1][0],pa[nbs-1][1],pa[nbs-1][2]);
    glVertex3f(pp[nbs-1][0],pp[nbs-1][1],pp[nbs-1][2]);
    glVertex3f(pp[0][0],pp[0][1],pp[0][2]);
    glVertex3f(pa[0][0],pa[0][1],pa[0][2]);
    glVertex3f(pa[nbs-1][0],pa[nbs-1][1],pa[nbs-1][2]);
    glEnd();
	
  }
};
CirclesTunnel *circlesTunnel;
class Lissajou {
public:
  Lissajou() {
  }
  float active(int i, int j) {
    /* appelle et renvoit la valeur de compteur[i] si i=j */
    if (i==j) return compteur[i]/100;
    else return 0;
  }
  void process() {
    float t=vbl;
    float o=2*M_PI/(25*10);
    float *c=compteur;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,-3);
    glPointSize(10);
	
    for (int i=0;i<12;i++) {
      float x=0;
      float y=0;
      if (i==0) {
	x=0.01*compteur[i]*0.5*(cos(o*t)+sin(o*t));
	y=0.01*compteur[i]*0.5*(cos(o*t)+cos(o*t));
      }
      if (i==1) {
	x=0.01*compteur[i]*(cos(o*t/2+(cos(o*t/2)*2*M_PI))*sin(o*t));
	y=0.01*compteur[i]*(cos(o*t/2+(cos(o*t/2)*2*M_PI))*cos(o*t));
      }
      if (i==2) {
	x=0.01*compteur[i]*0.5*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*cos(o*t);
	y=0.01*compteur[i]*0.5*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*sin(o*t);
      }
      if (i==3) {
	x=0.01*compteur[i]*0.5*sin(o*t)*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*cos(o*t);
	y=0.01*compteur[i]*0.5*cos(o*t)*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*sin(o*t);
      }
      if (i==4) {
	x=0.01*compteur[i]*0.5*sin(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*cos(o*t);
	y=0.01*compteur[i]*0.5*cos(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*sin(o*t);
      }
      if (i==5) {
	x=0.01*compteur[i]*0.5*sin(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(sin(o*t+(cos(o*t/2)*2*M_PI)))*cos(o*t);
	y=0.01*compteur[i]*0.5*cos(o*t+sin(o*t+(sin(o*t/2)*2*M_PI)))*(sin(o*t+(cos(o*t/2)*2*M_PI)))*sin(o*t);
      }
      if (i==6) {
	x=0.01*compteur[i]*(cos(o*t/2+(cos(o*t/2)*2*M_PI))*sin(o*t));
	y=0.01*compteur[i]*(cos(o*t/2+(cos(o*t/2)*2*M_PI)+2*M_PI/3)*cos(o*t));
      }
      if (i==7) {
	x=0.01*compteur[i]*(cos(o*t/2+(cos(o*t/2)*2*M_PI))*sin(o*t));
	y=0.01*compteur[i]*(cos(o*t/2+(cos(o*t/2)*2*M_PI))*cos(o*t+2*M_PI/3));
      }
      if (i==8) {
	x=0.01*compteur[i]*sin(o*t)*(cos(o*t/2+(cos(o*t/2)*2*M_PI))*sin(o*t));
	y=0.01*compteur[i]*cos(o*t)*(cos(o*t/2+(cos(o*t/2)*2*M_PI))*cos(o*t+2*M_PI/3));
      }
      if (i==9) {
	x=0.01*compteur[i]*0.5*sin(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*cos(o*t);
	y=0.01*compteur[i]*0.5*cos(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*sin(o*t+M_PI/3);
      }
      if (i==10) {
	x=0.01*compteur[i]*0.5*sin(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*cos(o*t);
	y=0.01*compteur[i]*0.5*cos(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI+M_PI/3)))*sin(o*t);
      }
	
      if (i==11) {
	x=0.01*compteur[i]*0.5*sin(o*t+sin(o*t+(cos(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*cos(o*t);
	y=0.01*compteur[i]*0.5*cos(o*t+sin(o*t+(sin(o*t/2)*2*M_PI)))*(cos(o*t)+sin(o*t+(cos(o*t/2)*2*M_PI)))*sin(o*t);
      }
      if ((x!=0) && (y!=0)) {
	glBegin(GL_POINTS);
	glColor3ub(comp(i));
	glVertex2f(x,y);
	glEnd();
      }
    }
    glPopMatrix();
  }
};
float psca2(float *v1, float *v2) {
  return (v1[0]*v2[0]+v1[1]*v2[1]);
}
void normalize2(float *v) {
  float l=sqrt(v[0]*v[0]+v[1]*v[1]);
  v[0]=v[0]/l;
  v[1]=v[1]/l;
}

Lissajou *lissajou;
class SegObst {
public:
  float A[2];
  float B[2];
  float O[2];
  float nor[2];
  float dir[2];
  int couleur;
  SegObst(float xA, float yA, float xB, float yB,int couleur) {
    A[0]=xA;
    A[1]=yA;
    B[0]=xB;
    B[1]=yB;
    O[0]=(xA+xB) / 2;
    O[1]=(yA+yB) / 2;
    nor[0]=(yB-yA);
    nor[1]=-(xB-xA);
    dir[0]=xB-xA;
    dir[1]=yB-yA;
    normalize2(dir);
    printf("dir : %f %f\n",dir[0],dir[1]);
    printf("nor : %f %f\n",nor[0],nor[1]);
    printf("psca2 : %f\n",psca2(dir,nor));
    normalize2(nor);
    this->couleur=couleur;
  }
  void affiche() {
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(comp(this->couleur));
    glVertex3f(A[0],A[1],0);
    glVertex3f(B[0],B[1],0);
    glEnd();
  }
  void affiche_normale() {

    glBegin(GL_LINES);
    glColor3ub(comp(3));
    glVertex3f(O[0],O[1],0);
    glVertex3f(O[0]+nor[0],O[1]+nor[1],0);
    glEnd();
  }
  void affiche_AB() {
    glBegin(GL_LINES);
    glColor3ub(comp(4));
    glVertex3f(A[0],A[1],0);
    glVertex3f(A[0]+dir[0],A[1]+dir[1],0);
    glEnd();
  }
};
int appartient_segments(float xa, float xb, float xc, float xd, float ya, float yb, float yc, float yd, float xi, float yi) {
  return ((((xi>=xc) && (xi<=xd)) || ((xi>=xd) && (xi<=xc))) && 
	  (((xi>=xa) && (xi<=xb)) || ((xi>=xb) && (xi<=xa))) &&
	  (((yi>=yc) && (yi<=yd)) || ((yi>=yd) && (yi<=yc))) &&
	  (((yi>=ya) && (yi<=yb)) || ((yi>=yb) && (yi<=ya))));
}
float *intersection(float xa, float xb, float xc, float xd, float ya, float yb, float yc, float yd) {
  // putain cette fonction, craftée avec amour par mes soins, je veux qu'elle marche, je veux tellement qu'elle marche
  // mais ça ne sert à rien de vouloir si on n'agit pas, et donc je vais l'utiliser et je saurai si elle marche,
  // c'est tout aussi simple que ça. 
  float *I=(float *)malloc(sizeof(float)*2);
  float emin=0.000000000001;
  float yi,xi;
  // si a et b sont sur la même verticale et que d et c ne sont pas sur la même verticale
  if ((abs(xb-xa)<emin) && (abs(xd-xc)>emin)) {
    yi=(yd-yc)*xa/(xd-xc)+yc-xc*(yd-yc)/(xd-xc);
    xi=xa;
  } else
    if ((abs(xd-xc)<emin)&&(abs(xb-xa)>emin)) {
      // dc verticale et ab pas verticale
      yi=(yb-ya)*xc/(xb-xa)+ya-xa*(yb-ya)/(xb-xa);
      xi=xc;
    } else
      if ((abs(xb-xa) < emin) && (abs(xd-xc)<emin)) {
	// dc et ab verticales
	if ((xb-xd)<emin) {
	  //xa==xb et xd==xc et xb==xd, autrement dit tous les x sont alignés verticalement pas d'intersection
	  free(I);
	  return NULL;
	} else {
	  free(I);
	  return NULL;
	}
      } else
	if ((abs(xb-xa)>emin)&&(abs(xd-xc)>emin)) {
	  double k1=(yd-yc)/(xd-xc);
	  double k2=yc-xc*(yd-yc)/(xd-xc);
	  double k3=(yb-ya)/(xb-xa);
	  double k4=yb-xb*(yb-ya)/(xb-xa);
	  if (abs(k3-k1)<emin) { free(I); return NULL; }
	  xi=(k2-k4)/(k3-k1);
	  yi=k1*(k2-k4)/(k3-k1)+k2;
	}
  if (appartient_segments(xa,xb,xc,xd,ya,yb,yc,yd,xi,yi)) {	
    I[0]=xi; I[1]=yi; 
    return I;
  } else {
    free(I); 
    return NULL;
  }
	
}
class RebPix {
public:
  float posn[2];
  float posnp1[2];
  float vitn[2]={0,0};
  float vitnp1[2]={0,0};
  float force_a_appliquer[2]={0,0};
  float alpha=0.003; // coefficient de rappel de force de frottement fluide
  float gravite=0.0001;
  float kreb=1;
  int vie=-1;
  int couleur;
  int taille;
  RebPix(float x, float y, int vie, int couleur, int taille) {
    posn[0]=x;
    posn[1]=y;
    //posnp1[0]=x;
    //posnp1[1]=y;
    this->vie=vie;
    this->couleur=couleur;
    this->taille=taille;
    vitn[0]=0;
    vitn[1]=0;
	
  }
  RebPix(float x, float y, int vie, int couleur, int taille, float vx, float vy) {
    posn[0]=x;
    posn[1]=y;
    //posnp1[0]=x;
    //posnp1[1]=y;
    this->vie=vie;
    this->couleur=couleur;
    this->taille=taille;

    vitn[0]=vx;
    vitn[1]=vy;
  }
  int evolue(SegObst **segobst, int nbsegobst) {

    vitnp1[0]=vitn[0]+force_a_appliquer[0]-alpha*vitn[0];
    vitnp1[1]=vitn[1]+force_a_appliquer[1]-alpha*vitn[1]-gravite;
    force_a_appliquer[0]=0;
    force_a_appliquer[1]=0;
    posnp1[0]=posn[0]+vitnp1[0];
    posnp1[1]=posn[1]+vitnp1[1];
    for (int i=0;i<nbsegobst;i++) {
      float *I=intersection(posnp1[0],posn[0],segobst[i]->A[0],segobst[i]->B[0],
			    posnp1[1],posn[1],segobst[i]->A[1],segobst[i]->B[1]);
      //I=NULL;						
      if (I!=NULL) {
	float P[2];
	P[0]=posn[0];
	P[1]=posn[1];
	float IP[2];
	IP[0]=P[0]-I[0];
	IP[1]=P[1]-I[1];
	float snor[2];
	if (psca2(IP,segobst[i]->nor)>0) {
	  snor[0]=segobst[i]->nor[0];
	  snor[1]=segobst[i]->nor[1];
	} else {
	  snor[0]=-segobst[i]->nor[0];
	  snor[1]=-segobst[i]->nor[1];
	}
	float sdir[2];
	if (psca2(IP,segobst[i]->dir)>0) {
	  sdir[0]=segobst[i]->dir[0];
	  sdir[1]=segobst[i]->dir[1];
	} else {
	  sdir[0]=-segobst[i]->dir[0];
	  sdir[1]=-segobst[i]->dir[1];
	}
	
	posnp1[0]=I[0]+0.005*snor[0];
	posnp1[1]=I[1]+0.005*snor[1];

	vitnp1[0]=psca2(vitn,sdir)*sdir[0]-kreb*psca2(vitn,snor)*snor[0];
	vitnp1[1]=psca2(vitn,sdir)*sdir[1]-kreb*psca2(vitn,snor)*snor[1];
				
      }
				

    }
    posn[0]=posnp1[0];
    posn[1]=posnp1[1];
    vitn[0]=vitnp1[0];
    vitn[1]=vitnp1[1];
	
    if (vie!=-1) vie--;
    if (vie==0) return 0; else return 1;
  }

  void affiche() {
    glPointSize(this->taille);
    glBegin(GL_POINTS);
    glColor3ub(comp(this->couleur));
    glVertex3f(posn[0],posn[1],0);
    glEnd();
  }
};
RebPix *rebpix;
int gamme2degres(int fondamentale, int note) {
  for (int i=0;i<7;i++) {
    if (gammes[fondamentale][i]==note)
      return i;
  }
  return -1;
}
unsigned char subpos(unsigned char a, unsigned char b) {
  int r=a - b;
  if (r<0) r=0;
  return (unsigned char)(r);
}
// en gamme de do majeur détecte si do,ré,mi,fa,sol,la,si a été joué par exemple
int has_gamme_been_played(int gamme) {
  int ok=1;
  for (int i=0;i<7;i++) {
    if (gammes[gamme][7-1-i]!=tab_notes[nb_notes-1-i].name) {
      ok=0;
      break;
    }
  }
  return ok;
}
int has_gamme_been_played_reversed(int gamme) {
  int ok=1;
  for (int i=0;i<7;i++) {
    if (gammes[gamme][i]!=tab_notes[nb_notes-1-i].name) {
      ok=0;
      break;
    }
  }
  return ok;
}
void assombrit(unsigned char *pix, int iw,int ih) {
  // ici on va assombrir la texture 
  unsigned int ofs=0;
  for (int x=0;x<iw;x++) {
    for (int y=0;y<ih;y++) {
      unsigned char r=pix[ofs];
      unsigned char v=pix[ofs+1];
      unsigned char b=pix[ofs+2];
      unsigned char d=0;
      /*
	r=subpos(r,d);
	v=subpos(v,d);
	b=subpos(b,d);
      */
			
      float k=4;
      r = (unsigned char)(r/k);
      v = (unsigned char)(v/k);
      b = (unsigned char)(b/k);
			
      pix[ofs]=r;
      pix[ofs+1]=v;
      pix[ofs+2]=b;
      ofs+=3;
    }
  }
}
void *balls_manager_calcul_mandel(void *ptr);
// Alors pour le moment, cette excellente petite classe prend une chaine de caractère en entrée de 
// construction et génère un tableau de pixels, représentation graphique de la chaine
class Pixmaps {
public:
  int width;
  int height;
  unsigned char *val;
  Pixmaps(char *string) {
    glColor3ub(255,255,255);
    glRasterPos2f(0,0);
    int len = (int) strlen(string);
    for (int i = 0; i < len; i++){
      glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
    int xmax=24*len;
    int ymax=24;
    this->width=xmax;
    this->height=ymax;
    val=(unsigned char*)malloc(width*height*3*sizeof(unsigned char));
    glReadPixels(dimX/2,dimY/2,xmax,ymax,GL_RGB,GL_UNSIGNED_BYTE,val);
  }
};

class BallsManager {
	
public:
  int nbsegobsts=50;
  RebPix *rebpix;
  Liste<RebPix> *lpix;
  int onote=-1;
  int onote_time=0;
  float ly=1.7;//ymax
  float lx=3;//xmax
  float lxs;
  float lys;
  float pastillex;
  float pastilley;
  SegObst **segobsts;
  Palette *mandelpal;
  void cercle(float x0, float y0,float r, int nb_de_segments) {
    glBegin(GL_LINE_STRIP); 
    {
      glColor3ub(255,255,255);
      for (int i=0; i<nb_de_segments; i++) {
	glVertex3f( x0+r*cos(i*M_PI*2/nb_de_segments), y0+r*sin(i*M_PI*2/nb_de_segments), 0);
      }
      glVertex3f( x0+r*cos(0*M_PI*2/nb_de_segments), y0+r*sin(0*M_PI*2/nb_de_segments), 0);
    }
    glEnd();
  }
  float scalescroll=3.5;//3.5;
  SegObst **bordsminiwin;
  RebPix *centrescroll;
  void ScrollScreenInit() {
    // alors ce qu'on veut, c'est un scroll screen, quand on joue plus de 3 notes en même temps
    // on prend la note la plus basse et on scroll l'écran dans la direction correspondante
    // donc comment on le scroll, en fait on applique une force dans cette direction à un objet solide invisible
    // qui rebondit contre les bords d'une fenetre afin qu'à l'écran on ne sorte jamais des bords du monde
    //  monde, alors déjà il faut les coordonnées de cette miniwin 
    // on a ly et lx qui sont les demi-tailles de l'écran, une fois scalé l'écran devient plus grand
    lys=scalescroll*ly;
    lxs=scalescroll*lx;
    // les différences entre ces tailles sont importantes, elles vont definir une fenetre dans lequel
    // évolue l'objet invisible blabla bref
    float miniwinlx=lxs-lx;
    float miniwinly=lys-ly;
    // donc on a 4 bords, des segobst
    bordsminiwin = (SegObst**)malloc(4*sizeof(SegObst*));
    float dd=0.001;
    bordsminiwin[0]=new SegObst(-miniwinlx-dd,miniwinly,+miniwinlx+dd,miniwinly,2);//bord haut
    bordsminiwin[1]=new SegObst(+miniwinlx,miniwinly+dd,+miniwinlx,-miniwinly-dd,2);//bord droit
    bordsminiwin[2]=new SegObst(-miniwinlx-dd,-miniwinly,+miniwinlx+dd,-miniwinly,2);//bord bas
    bordsminiwin[3]=new SegObst(-miniwinlx,-miniwinly-dd,-miniwinlx,+miniwinly+dd,2);//bord gauche
    // et on a un rebpix qu'on va appeler centrescroll
    centrescroll=new RebPix(0,0,-1,0,1);//x,y,vie,couleur,taille
    centrescroll->gravite=0;
    centrescroll->kreb=0.3;

  }
  void ScrollScreen() {
    int nb_notes_on=0;
    int note_la_plus_basse=65535;
    for (int i=0;i<etendue_piano;i++) {
      if (notes_vals[i]!=0) {
	nb_notes_on++;
	if (i<note_la_plus_basse) {
	  note_la_plus_basse=i;
	}
      }
    }
    if (nb_notes_on>=2) {
      float nf=0.001*myrand();
				
      int deg=gamme2degres(detecteurDeGamme->une_gamme_possible_ou_DO(),note_la_plus_basse % 12)+1;
      float a;
#define direction(n) M_PI/2+n*M_PI*2/7;
      switch (deg) {
      case 4:
	a=direction(0); break;
      case 1:
	a=direction(1); break;
      case 5:
	a=direction(-1); break;
      case 2:
	a=direction(2); break;
      case 6:
	a=direction(-2); break;
      case 3:
	a=direction(3); break;
      case 7:
	a=direction(-3); break;
      default: break;
      }

      //printf("%d %d\n",detecteurDeGamme->une_gamme_possible_ou_DO(),deg);
      float fx=nf*cos(a);
      float fy=nf*sin(a);
      centrescroll->force_a_appliquer[0]=fx;
      centrescroll->force_a_appliquer[1]=fy;

    }
    centrescroll->evolue(bordsminiwin,4);
    glTranslatef(-centrescroll->posn[0],-centrescroll->posn[1],0);

  }
  void genSegObsts() {
    for (int i=4;i<nbsegobsts;i++) {
      float l=0.3+0.8*myrand();
      float a=M_PI*myrand();
      float x1=-lx+2*lx*myrand();
      float y1=-ly+2*ly*myrand();
      float x2=x1+l*cos(a);
      float y2=y1+l*sin(a);
      segobsts[i]=new SegObst(x1,y1,x2,y2,int(12*myrand()));
    }
  }
  void delSegObsts() {
    for (int i=4;i<nbsegobsts;i++) {
      delete(segobsts[i]);
    }
  }
  void drop_pastille() {
    pastillex=myrand()*(lx-0.001);
    pastilley=myrand()*(ly-0.001);
  }
  unsigned int texture;
  int iw=2048;
  int ih=768;

  pthread_t calcul_mandel_thread;
  pthread_t mandel_zoom_thread;
  int mandel_calculating=0;
  int mandel_new=0;
  int mandel_ready=0;
  float zoomfactor;
  Mandelbrot *pmandel_en_cours=NULL;
  Mandelbrot *pmandel_back=NULL;
  static void *mandel_zoom(void *ptr) {
    BallsManager *t=(BallsManager*)ptr;
    t->mandel_new = 0;
    t->mandel_calculating=1;
    Mandelbrot *p;
    p=t->pmandel_en_cours;
    float tx=t->centrescroll->posn[0]; 
    float ty=t->centrescroll->posn[1];
    //2*lxs     (p->xmax - p->xmin)
    //tx		txm

    float txm=tx*(p->xmax - p->xmin) / (2*t->lxs);
    float tym=ty*(p->ymax - p->ymax) / (2*t->lys);
    //		txm=0;
    //		tym=0;
    float newxmin=p->xmin+(p->xmax-p->xmin)*t->zoomfactor+txm;
    float newxmax=p->xmax-(p->xmax-p->xmin)*t->zoomfactor+txm;
    float newymin=p->ymin+(p->ymax-p->ymin)*t->zoomfactor+tym;
    float newymax=p->ymax-(p->ymax-p->ymin)*t->zoomfactor+tym;
	
    if (t->pmandel_back==NULL) {
      t->pmandel_back=new Mandelbrot(newxmin,newxmax,newymin,newymax,t->iw,t->ih,t->mandelpal);
    } else {
      t->pmandel_back->calcule(newxmin,newxmax,newymin,newymax);
    }
    assombrit(t->pmandel_back->pix,t->iw,t->ih);
    Mandelbrot *paux=t->pmandel_en_cours;
    t->pmandel_en_cours=t->pmandel_back;
    t->pmandel_back=paux;
    t->mandel_new = 1;
    t->mandel_calculating=0;
  }
  BallsManager() {
    rebpix = new RebPix(0,1,-1,0,15);//x,y,vie,couleur,taille
    rebpix->vitn[0]=0.001;
    segobsts = (SegObst**)malloc(nbsegobsts*sizeof(SegObst*));
    segobsts[0] = new SegObst(-lx,ly,lx,ly, 0); //(float xA, float yA, float xB, float yB) 
    segobsts[1] = new SegObst(lx,ly,lx,-ly, 1); //(float xA, float yA, float xB, float yB) 
    segobsts[2] = new SegObst(lx,-ly,-lx,-ly, 2); //(float xA, float yA, float xB, float yB)
    segobsts[3] = new SegObst(-lx,-ly,-lx,ly, 3); //(float xA, float yA, float xB, float yB) 
    lpix = new Liste<RebPix>();
    lpix->ajouter(rebpix);
    genSegObsts();
    drop_pastille();
    ScrollScreenInit();
    if (detecteurDeGamme==NULL) detecteurDeGamme=new DetecteurDeGamme();
    mandelpal=new Palette(/*debuth*/0.1,/*finh*/0.8,/*nb_couleurs*/160,/*opacity*/0);
    // lancement du calcul d'un mandel
    pthread_create(&calcul_mandel_thread,NULL, balls_manager_calcul_mandel,this);

    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR/*GL_NEAREST*/); /*pas d'interpolation, le pixel le plus prés est pris*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR/*GL_NEAREST*/); /*pas d'interpolation, le pixel le plus prés est pris*/
  }
  // expulsion d'un pixel 
  void pixexp(float x, float y, int couleur) {
    float nv=0.001*myrand();
    float theta=2*M_PI*myrand();
    float vx=nv*cos(theta);
    float vy=nv*sin(theta);
    lpix->ajouter(new RebPix(x,y,300,couleur,5,vx,vy));		
  }
  void pixploid(float x, float y, int couleur) {
    int n=7;
    for (int i=0;i<n;i++) {
      float nv=0.001;//*myrand();
      float theta=i*2*M_PI/n;//I*myrand();
      float vx=nv*cos(theta);
      float vy=nv*sin(theta);
      lpix->ajouter(new RebPix(x,y,300,couleur,5,vx,vy));		
    }
  }
  Pixmaps *pixnote=NULL;
  int asked_note=-1;
  int asked_note_duree=10000;
  int asked_note_end_time=-1;
  void create_asked_note() {
    asked_note=int(12*myrand());
    asked_note_end_time=mstime()+asked_note_duree;
  }

  void pixfuse_asked_note(float x, float y, int couleur) {
    // bon alors pour commencer, tout cela est fort intéressant, mais je me dis quand même
    // que pour que ce soit bien gratifiant, il faut une belle réalisation alors donc
    // voilà. le nv, ce serait bien cool en fait qu'il dépende du pixmap
    float nv=0.001*myrand();
    float theta=2*M_PI*myrand();
    float vx=nv*cos(theta);
    float vy=nv*sin(theta);
    lpix->ajouter(new RebPix(x,y,300,couleur,5,vx,vy));		
  }
  void artifice_note(int note) {
    if (pixnote!=NULL) 	delete(pixnote);
    pixnote=new Pixmaps(note_name(note));
    // on veut créer des RebPix, des pixels rebondissants comme on les appelle, à partir de cet excellent
    // tableau de points, on veut que ces pixels soient préalablement soumis à une force qui les projette
    // vers le haut, donc on a besoin de cette formidable petite ligne qu'on a crafté avec amour, et qu'on
    // vendra le plus tard possible
    float k=25;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,-3);

    //	glBegin(GL_POINTS);
    //		glColor3ub(255,255,255);
    int ofs=0;
    for (int y=0;y<pixnote->height;y++) {
      for (int x=0;x<pixnote->width;x++) {
	if (pixnote->val[ofs]!=0) {
	  //glVertex3f(x/k,y/k,0);
	  // donc c'est un merveilleux pixfuse, et le blaireau sur internet, est
	  // à nouveau en boucle, je me fous de mes racines, je suis un produit
	  // de mes discussions avec chatgpt et avec tristan convert et avec mes parents
	  // et en fait bien souvent on est le produit de ses discussions
	  float nv=0.01;
	  // voilà maintenant les coordonnées par rapport au centre de la map
	  float xb=x-pixnote->width/2;
	  float yb=y-pixnote->height/2;
	  float x0b=pixnote->width/2;
	  float y0b=-3*(pixnote->height);
	  float vx=xb-x0b;
	  float vy=yb-y0b;
	  // on normalise
	  float l=sqrt(vx*vx+vy*vy);
	  vx=vx/l;
	  vy=vy/l;
	  vx=nv*vx;
	  vy=nv*vy;
	  //		lpix->ajouter(new RebPix(centrescroll->posn[0]+x0b/k,centrescroll->posn[1]+y0b/k,300,asked_note,1,vx,vy));
	  if (myrand()>0.0) 
	    lpix->ajouter(new RebPix((centrescroll->posn[0]+xb/k)/scalescroll,
				     (centrescroll->posn[1]+yb/k)/scalescroll,300,asked_note,5,vx,vy));
	  printf("%f %f\n",centrescroll->posn[0],centrescroll->posn[1]);

	}
	ofs+=3;
      }
    }
    //	glEnd();
    glPopMatrix();
  }
	
  void process() {
    detecteurDeGamme->process();
    // process du ask note
    if (asked_note==-1) create_asked_note();
    if (mstime()>asked_note_end_time) {
      create_asked_note();
    }
    // affichage de la nouvelle note
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,-1);
    glColor3ub(255,255,255);// C-ESPACE M-F C-ESPACE M-W C-S C-Y ENTREE : pour rechercher le mot sous le curseur
    glRasterPos2f(-1, 0);

    char *string = note_name(asked_note); 
    int len = (int) strlen(string);
    for (int i = 0; i < len; i++){
      glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
	
    glPopMatrix();
    // fin du process du ask note

    if ((note_en_cours()!=onote) || (note_en_cours_time()!=onote_time)) {
      int note=note_en_cours();
      if (note==asked_note) {
	artifice_note(note);
	create_asked_note();
      }
      // une force est appliquée au pixel principal dans une direction correspondant à la note jouée
      float nf=0.003;
      float theta=M_PI-(M_PI/4+gamme2degres(detecteurDeGamme->une_gamme_possible_ou_DO(),note)*((M_PI-(2*M_PI/4))/7));
      float fx=nf*cos(theta);
      float fy=nf*sin(theta);
      rebpix->force_a_appliquer[0]=fx;
      rebpix->force_a_appliquer[1]=fy;
      // il expulse un pixel
      pixexp(rebpix->posn[0],rebpix->posn[1],note);
      // si une gamme est jouée dans l'ordre alors pixploid
      int gamme=detecteurDeGamme->une_gamme_possible_ou_DO();
      if (has_gamme_been_played(gamme)) {

	pixploid(rebpix->posn[0],rebpix->posn[1],gamme);
	if ((mandel_ready) && (!mandel_calculating)) {
	  zoomfactor=0.1;
	  pthread_create(&mandel_zoom_thread,NULL,BallsManager::mandel_zoom,this);
	}
      }
      if (has_gamme_been_played_reversed(gamme)) {

	pixploid(rebpix->posn[0],rebpix->posn[1],gamme);
	if ((mandel_ready) && (!mandel_calculating)) {
	  zoomfactor=-0.1;
	  pthread_create(&mandel_zoom_thread,NULL,BallsManager::mandel_zoom,this);
	}
      }


      onote=note_en_cours();
      onote_time=note_en_cours_time();
	
    }
    // evolution des pixels et enlevage de la liste des pixels morts
    Maille<RebPix> *p = lpix->premier;
    while (p!=NULL) {
      if (!p->ptr->evolue(segobsts,nbsegobsts)) {
	Maille<RebPix> *paux=p->suivant;
	lpix->liste_enlever(p->ptr);
	p=paux;
      } else {
	p=p->suivant;
      }
    }
    // gestion de la pastille de regenération du terrain
    float dpastillemin=0.04;
    if ((abs(lpix->premier->ptr->posnp1[0]-pastillex)<dpastillemin) && 
	(abs(lpix->premier->ptr->posnp1[1]-pastilley)<dpastillemin)) {
      drop_pastille();
      delSegObsts();
      genSegObsts();
    }
	
    // affichage 

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,-3);
    // scrollage de l'écran
    ScrollScreen();

    // si un nouveau mandel a été calculé, création de la texture
    if (mandel_new) {
      glTexImage2D(GL_TEXTURE_2D, 
		   0/*mipmap level*/, 
		   GL_RGB,// internal format 
		   iw, 
		   ih, 
		   0/*width of border*/, 
		   GL_RGB, 
		   GL_UNSIGNED_BYTE, 
		   pmandel_en_cours->pix);
      mandel_new=0;
    }

    // affichage de mandelbrot en fg
    if (mandel_ready) {
      glEnable(GL_TEXTURE_2D);
      glBegin(GL_QUADS);
      glColor3ub(255,255,255); // sinon le starfield en changeant le glcolor modifie la luminosité de la texture
      float z=-0.4;
      glTexCoord2f(0.0, 0.0); glVertex3f(-lxs, -lys,z);
      glTexCoord2f(1.0, 0.0); glVertex3f( lxs, -lys,z);
      glTexCoord2f(1.0, 1.0); glVertex3f( lxs, lys, z);
      glTexCoord2f(0.0, 1.0); glVertex3f(-lxs, lys, z);

      glEnd();
      glDisable(GL_TEXTURE_2D);
    }
    // scroll de l'écran
    glScalef(scalescroll,scalescroll,1);
    // affichage des bords de l'écran
    for (int i=0;i<4;i++) {
      bordsminiwin[i]->affiche();
    }
    // affichage des passerelles
    for (int i=0;i<nbsegobsts;i++) {
      segobsts[i]->affiche();
    }
    // affichage des pixels
    p = lpix->premier;
    while (p!=NULL) {
      p->ptr->affiche();
      p=p->suivant;
    }
    // affichage de la pastille de changement de niveau
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3ub(255,255,255);
    glVertex3f(pastillex,pastilley,0);
    glEnd();
    cercle(pastillex,pastilley,dpastillemin,5);

    glBegin(GL_POINTS);
    glColor3ub(255,255,255);
    glVertex3f(centrescroll->posn[0]/scalescroll,centrescroll->posn[1]/scalescroll,0);
    glEnd();
	
    glPopMatrix();

  }
  ~BallsManager() {
    delete lpix;
  }

};
BallsManager *ballsmanager;
// alors randomasknote est appelé par le ballsmanager, comment on fait... comment on fait...
// comment on fait... comment on fait...alors, on a randomasknote qui va devenir une methode
// du ballsmanager, il n'y a pas moyen de faire autrement...et ce n'est pas génant que ballsmanager 
// s'appelle ballsmanager, non, ce n'est pas génant, c'est un nom comme un autre, alors maintenant
// comment va t'on faire, on repense à pas mal de choses 
void *balls_manager_calcul_mandel(void *ptr) {

  BallsManager *p=(BallsManager*)ptr;
  // alors on va commencer simple...
  p->pmandel_back = new Mandelbrot(-1,1,-1,1,p->iw,p->ih,p->mandelpal); //xmin,xmax,ymin,max,iw,ih
  assombrit(p->pmandel_back->pix,p->iw,p->ih);
  p->pmandel_en_cours=p->pmandel_back;
  p->mandel_new=1;
  p->mandel_ready=1;
}
template <class T>
class Node {
public:
  Node<T> **children;
  Node<T> *parent;
  T *element;

  Node<T>(Node<T> *parent) {
    this->element=NULL;
    this->parent=parent;
  }
  Node<T>(Node<T> *parent, T *element) {
    this->element=element;
    this->parent=parent;
    //this->children=new Liste<Node<T>>();
  }
  ~Node() {
    for (int i=0;i<4;i++) {
      delete(this->children[i]);
    }    
    delete(element);
  }
  void create_rameau() {
    printf("create rameau\n");
    this->children=(Node<T> **)malloc(4*sizeof(Node<T>*));
    for (int i=0;i<4;i++) {
      this->children[i]=new Node<T>(this);
    }    
  }
  int is_rameau() {// un rameau c'est un noeud dont les 4 enfants ont des éléments nuls
    int ok=1;
    for (int i=0;i<4;i++) {
      ok=((ok) && (this->children[i]->element==NULL));//donc children->element(i), je rappelle qu'il renvoit le ptr de la ième maille
      // et ce ptr dans le cas présent donne vers une node dont l'élément est nul 4 fois dans le cas d'un rameau
      if (!ok) break;
    }
    return ok;
  }
  

};
namespace tetree {
  template <class T> 
  class Tree {//je code un buisson plutôt qu'un arbre, car à chaque noeud et donc à la base il y a 4 branches
  public:
    Node<T> *current;
    Node<T> *base;
    int profondeur=0;    
    Tree<T>(T *element) {
      this->base=new Node<T>(NULL, element);
      this->base->create_rameau();
      this->current=this->base;
    }
    void down(int numchildren) {
      if (!current->is_rameau()) {// on ne peut pas descendre d'un rameau
	current = current->children[numchildren];//descend par la numchildren ième node
	profondeur++;
	printf("profondeur : %d\n", profondeur);
      } else {
	printf("current is rameau\n");
      }
    
    }
    void add(int num, T *element) {
      current->children[num]->element=element;
      current->children[num]->parent=current;
      current->children[num]->create_rameau();
    }
    void up() {
      if (current->parent!=NULL) {
	current=current->parent;
	profondeur--;
      } else {
	printf("on ne peut pas remonter dans l'arbre, on est à la base\n");
      }
      printf("profondeur : %d\n",profondeur);
    }


    void affiche() {
      parcours_affiche(base, 0);
    }

  };

  class VecteurB {
  public:
    float x;
    float y;
    float z;
    float xb;
    float yb;
    float zb;
    float xe;
    float ye;
    float ze;
    int couleur;
    VecteurB(float xb,float yb,float zb,float x,float y,float z, int couleur) {
      this->xb=xb;
      this->yb=yb;
      this->zb=zb;
      this->x=x;
      this->y=y;
      this->z=z;
      this->xe=xb+x;
      this->ye=yb+y;
      this->ze=zb+z;
      this->couleur=couleur;
    }
  };
  class Arbre {
    int onote=-1;
    int onote_time=0;
    Node<VecteurB> *base;
    Tree<VecteurB> *tree;
  public:
    // emacs bookmark set : C-x r m
    // emacs bookmark jump : C-x r b
    Arbre() {
#define COULEUR(i) i
      tree=new Tree<VecteurB>(new VecteurB(0,0,0,0,0.1,0,COULEUR(0)));
      base=tree->base;

                                     
      // le add ajoute des enfants et cree le rameau, mais
      // bien sûr il ne faut pas rajouter à un noeud plusieurs fois
      // des enfants partant d'une de ses branches, encore qu'on
      // puisse mais dans ce cas là, il faudrait penser
      // à delete l'ancien
      
      tree->add(0,degtovecb(0, tree->current->element,COULEUR(2)));
      tree->add(1,degtovecb(1, tree->current->element,COULEUR(2)));
      tree->add(2,degtovecb(2, tree->current->element,COULEUR(2)));
      
      tree->down(1);
      
      tree->add(3,degtovecb(3,tree->current->element,COULEUR(3)));
      
      tree->down(3);
      
      tree->add(3,degtovecb(3,tree->current->element,COULEUR(4)));
      
      tree->down(3);
      
      tree->add(2,degtovecb(2, tree->current->element,COULEUR(5)));
      tree->add(0,degtovecb(0, tree->current->element,COULEUR(5)));

      tree->up();
      
      tree->add(3,degtovecb(3,tree->current->element,COULEUR(4)));
     
    };
      

    
    void process() {
      if ((note_en_cours()!=onote) && (note_en_cours_time()!=onote_time)) {
	
      }
    }
    
    void compute() {
      
    }
    void affiche() {
      /*	
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0,0,-3);
      */
      parcours_affiche(base, 0); // je développe mon code
      /*
	float theta=M_PI/4;
	float alpha[4]={0,M_PI/2,2*M_PI/2,3/M_PI/2};
	float x,y,z;
	glBegin(GL_LINES);      
	{
	for (int i=0;i<4;i++) {
	glColor3f(0,3*64,0);
	glVertex3f(0,0,0);
	x=(sqrt(2)/2)*cos(alpha[i]);
	y=sin(theta);
	z=(sqrt(2)/2)*sin(alpha[i]);
	glVertex3f(x,y,z);
	}
	
	}
	glEnd();
      */
      //glPopMatrix();
      //      exit(0);
    }





      

      

  private:
    // C-w : emacs kill-region
    // M-w : emacs copy-region
    VecteurB *degtovecb(int i, VecteurB *parent, int couleur) {
      float alpha[4]={0,M_PI/2,2*M_PI/2,3/M_PI/2};
      float x,y,z;
      float theta=M_PI/4;
      x=(sqrt(2)/2)*cos(alpha[i]);
      y=sin(theta);
      z=(sqrt(2)/2)*sin(alpha[i]);
      VecteurB *retvec;
      if (parent==NULL)
	retvec=new VecteurB(0,0,0,x,y,z,couleur);
      else
	retvec=new VecteurB(parent->xe,parent->ye,parent->ze,x,y,z,couleur);
      return retvec;
    }

    //emacs : ctrl-x u pour undo
    void parcours_affiche(Node<VecteurB> *node, Node<VecteurB> *parent) {
      printf("je développe mon code, la suite...\n");

      if (parent!=NULL) {
	glBegin(GL_LINES);
	VecteurB *vbcurrent=(VecteurB*)(node->element);	
	glColor3ub(comp(vbcurrent->couleur));
	//printf("%d\n",(int)(*(node->element)));

	VecteurB *vbparent=(VecteurB*)(parent->element);//à chaque noeud de l'arbre (qui n'est pas une feuille
	printf("quel drôle d'animal\n");
	float xep=vbparent->xe;
	float yep=vbparent->ye;
	float zep=vbparent->ze;
	glVertex3f(xep,yep,zep);

	printf("quel étonnante créature\n");
	// "je veux que tu saches qu'à chaque fois que je pense à toi, je me sens beaucoup mieux, je me déleste de tous mes soucis et ça me fait vraiment du bien"
	float xvc=vbcurrent->x;
	float yvc=vbcurrent->y;
	float zvc=vbcurrent->z;
	glVertex3f(xep+xvc,yep+yvc,zep+zvc);
        
	
	glEnd();
	
      }

      Node<VecteurB> *children_tab[4];

      
      //if (node->is_rameau()) return;// alors un rameau c'est un noeud dont émerge 4 branches qui donnent sur des noeuds dont les éléments pointent vers null au lieu de VecteurB

      
      // p est une maille
      // p->ptr est une node
      //

      for (int i=0;i<4;i++) {
	printf("je développe une méthode, cette ligne est elle atteinte ? %f\n",((VecteurB*)(node->element))->xe);
	if (node->children[i]->children!=NULL)
	  parcours_affiche(node->children[i],node);
      }
      printf("je développe mon code, le déroulement l'a t'il amené jusque là, à priori non\n");

    }
    
  };
}
using namespace tetree;
//Arbre *arbre=new Arbre();



    

float *vec(float x, float y) {
  float *ret = (float *)malloc(sizeof(float)*2);
  ret[0]=x;
  ret[1]=y;
  return ret;
}

//emacs C-M b et C-M f : goto begin et end expression  
void calcul_matrice_deplacement_en_fonction_des_notes_et_de_la_partnum() {
  float roulotte;
  if (partnum==0) {
    roulotte = 450;
  } else 
    if (partnum==-5) { // LE TROU
      roulotte = 650;
    } else if (partnum==-3) { // CUBE DANS CUBE
      roulotte = 350;
      // CTRL S CTRL W : pour rechercher le mot sous le curseur
    } else if ((partnum==MIKADO) || (partnum==TETRAMAUVEM16)) {
      roulotte = 350;
    } else {
      roulotte = 420.1; // le facteur divisant l'intensité des notes pour en faire des incréments de rotations
    }
  rotx = rotx + notes_val_dans_l_octave[0]/roulotte;
  rotxy = rotxy + notes_val_dans_l_octave[1]/roulotte;
  rotxya = rotxya + notes_val_dans_l_octave[2]/roulotte;
  rotxa = rotxa + notes_val_dans_l_octave[3]/roulotte;

  if (rotx>360) rotx=rotx-360;
  if (rotxy>360) rotxy=rotxy-360;
  if (rotxya>360) rotxya=rotxya-360;
  if (rotxa>360) rotxa=rotxa-360;
	 
  roty = roty + notes_val_dans_l_octave[4]/roulotte;
  rotyz = rotyz + notes_val_dans_l_octave[5]/roulotte;
  rotyza = rotyza + notes_val_dans_l_octave[6]/roulotte;
  rotya = rotya + notes_val_dans_l_octave[7]/roulotte;

  if (roty>360) roty=roty-360;
  if (rotyz>360) rotyz=rotyz-360;
  if (rotyza>360) rotyza=rotyza-360;
  if (rotya>360) rotya=rotya-360;

  rotz = rotz + notes_val_dans_l_octave[8]/roulotte;
  rotxz = rotxz + notes_val_dans_l_octave[9]/roulotte;
  rotxza = rotxza + notes_val_dans_l_octave[10]/roulotte;
  rotza = rotza + notes_val_dans_l_octave[11]/roulotte;

  if (rotz>360) rotz=rotz-360;
  if (rotxz>360) rotxz=rotxz-360;
  if (rotxza>360) rotxza=rotxza-360;
  if (rotza>360) rotza=rotza-360;

  if (partnum==-3)  { 
    glTranslatef(0,0,0);
  }
  if (partnum==-4) { // Inside Cube qui va plus être à l'intérieur
    glTranslatef(0,0,0);
  }
  // on fait tourner l'objet autour des axes
  glRotatef((int)rotx,1.0,0.0,0.0);            
  glRotatef((int)roty,0.0,1.0,0.0);            
  glRotatef((int)rotz,0.0,0.0,1.0);
  if (1) {
    float k;
    if (partnum==-5) k=1.5;
    else if (partnum==-3) k=1.0;
    else if (partnum==-9) k=0.8;
    else if (partnum==MIKADO) k=0.8;
    else k=1.2;
    glTranslatef(k*0.01*compteur[1],0,0);
    glTranslatef(-k*0.01*compteur[2],0,0);
    glTranslatef(0,k*0.01*compteur[5],0);
    glTranslatef(0,-k*0.01*compteur[6],0);
    glTranslatef(0,0,k*0.01*compteur[9]);
    glTranslatef(0,0,-k*0.01*compteur[10]);
  } else {
    glRotatef((int)rotxy,1.0,1.0,0.0);            
    glRotatef((int)rotyz,0.0,1.0,1.0);            
    glRotatef((int)rotxz,1.0,0.0,1.0);
  }
  if (partnum!=-4) glTranslatef(0.2,-0.3,0);
  // on tourne

  glRotatef((int)rotxa,1.0,0.0,0.0);
  glRotatef((int)rotya,0.0,1.0,0.0);            
  glRotatef((int)rotza,0.0,0.0,1.0);
  if (0) {	
    glRotatef((int)rotxya,1.0,1.0,0.0);            
    glRotatef((int)rotyza,0.0,1.0,1.0);            
    glRotatef((int)rotxza,1.0,0.0,1.0);
  }

}
void *gl_animate(void *ptr) {
  printf("gl_animate\n");
  //  canvas_id = SOIL_load_OGL_texture("image.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
  //	init();

  init_freq();

  gp = new Gestionnaire_de_particules();
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  
  //glTexSubImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas);
  //glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData); 

  while(1) {
    while (SDL_PollEvent(&event)) {
      switch( event.type) {
      case SDL_KEYDOWN:

	break;
      case SDL_KEYUP:
	break;
      case SDL_TEXTINPUT:
	if (event.text.text[0] == '+') {
	  new_txt_video_clip=1;
	} else if (event.text.text[0] == '-') {	
	  int l=strlen(txt_video_clip);
	  if (l>0) txt_video_clip[l-1]=0;

	  new_txt_video_clip=0;
	} else {
	  new_txt_video_clip=0;

	  int l=strlen(txt_video_clip);
	  txt_video_clip[l]=event.text.text[0];
	  txt_video_clip[l+1]=0;


	} 
	
	break;
      default:
	break;
      }
    }

    if (gltourne) {
			
      update_compteur();
      SDL_GL_MakeCurrent(glwin, contexteOpenGL);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glMatrixMode(GL_MODELVIEW);             
      glLoadIdentity();                       

      gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
	
      if (premierevbl) {
	nb_notes_to_change=50+100*(1-2*myrand());
	cuboid=new Cuboid();
	mikado=new Mikado();

	simplecube=new Cube();
	//afficheurDeSquircles=new AfficheurDeSquircles();
	randomcanvas=new RandomCanvas();
      }

      glEnable(GL_DEPTH_TEST);
      //glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA); // merci Internet
	
      float lpx=0.3;//5*cos(2*M_PI*((moteur%360)/360.0));
      float lpz=-0.3;//5*sin(2*M_PI*((moteur%360)/360.0));
      float lpy=1;
      //float lightpos[4]={0,0,-3,1};
      //glEnable(GL_LIGHTING);
      float lightpos[4]={lpx,lpy,lpz,1};
      glLightfv(GL_LIGHT0,GL_POSITION, lightpos);
      if (partnum==-15) { // MandelBalls
	if (ballsmanager==NULL) {
	  ballsmanager=new BallsManager();
	}
	ballsmanager->process();
      }
      if (partnum==-14) {
	if (wordsdisplay) {
	  texteur(ANGLAIS,1.8,1.7);
	  texteur(FRANCAIS,-1,1.7);
	}

			
	if (circlesTunnel==NULL) {
	  circlesTunnel=new CirclesTunnel();
	}
	starfield();
	circlesTunnel->process();
	if (lissajou==NULL) {
	  lissajou=new Lissajou();
	}
	lissajou->process();
      }
      if (partnum==-9) {
	if (detecteurDeGamme==NULL) detecteurDeGamme=new DetecteurDeGamme();	
	detecteurDeGamme->process();
	//detecteurDeGammePentatonique->process(note_en_cours());
	intervalleur();
	intervalleur2->process();
	intervalleur3->process();
      }
      if (partnum==-8) {

	detecteurDeGamme->process();
	randomcanvas->modify();
	randomcanvas->affiche();
      }



      // axes();
			
      if (auto_change && (nb_notes_since_last_change>=nb_notes_to_change)) {
	change_part();	    
      }
 


      //gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
      //gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
      //starfield();
      if (partnum==-6) {
	if (!voyagerinitialized) {
	  voyager=new Voyager();
	  voyagerinitialized=1;
	}
	voyager->do_voyager();
      }
      if (partnum==-5) {
	if (wordsdisplay) {
	  texteur(ANGLAIS,1.8,1.7);
	  texteur(FRANCAIS,-1,1.7);
	}


	if (!sweeperinitialized) {
	  courbe3Dtosweep=new Courbe3D(3+int(6*myrand()));
	  int nb_sommets_du_contour=6;
	  float **triangle = polygone(0, 0, 0.3, nb_sommets_du_contour);
	  sweeper=new Sweeper(triangle, nb_sommets_du_contour, courbe3Dtosweep);
	  sweeperinitialized=1;
	}
	if (nb_notes_since_last_change % 140 == 0) {
	  delete courbe3Dtosweep;
	  courbe3Dtosweep=new Courbe3D(3+int(6*myrand()));
	  int nb_sommets_du_contour=6;
	  float **triangle = polygone(0,0,0.3,nb_sommets_du_contour);
	  sweeper=new Sweeper(triangle, nb_sommets_du_contour, courbe3Dtosweep);
	  nb_notes_since_last_change++;
	}
	
	int immobile=0;
	courbe3Dtosweep->calcule_courbe3D(immobile);
															
															
	//courbe3Dtosweep->affiche_courbe3D();
	sweeper->calculer_sweeper();
	sweeper->afficher_sweeper(immobile,0);
				
      }
	

      if (partnum==-1) {
	starfield();
	gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up				
	pastillage();  
      }
	

      if (partnum==0) { // la courbe en 3D
	if (wordsdisplay) {
	  texteur(ANGLAIS,1.8,1.7);
	  texteur(FRANCAIS,-1,1.7);
	}


	if (nb_notes_since_last_change % 140 == 0) {
	  delete courbe3D;
	  courbe3D=new Courbe3D(12);
	  nb_notes_since_last_change++;
	}
	courbe3D->calcule_courbe3D(0);
	courbe3D->affiche_courbe3D();
			
      }
	
      if (partnum==13) {

	if (wordsdisplay) {
	  texteur(ANGLAIS,1.8,1.7);
	  texteur(FRANCAIS,-1,1.7);
	}


	//gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up			
	//damier();
	starfield();
	partoche();
      }	

	
      gp->evolue(); // evolution et 
			
      //gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
      gp->affiche(); // affichage des particules du pastillage et des particules de fumee verte (qui sont rouges)

      angle = angle + 1; if (angle == 360) angle = 0;
      calcul_matrice_deplacement_en_fonction_des_notes_et_de_la_partnum();
      //if (partnum==-17) {
	//arbre->affiche();
      //}
      if (partnum==TETRAMAUVEM16) {
	if (circlesTunnel==NULL) {
	  circlesTunnel=new CirclesTunnel();
	}
	circlesTunnel->process();
	tetraedre(0,0,0,1,0);	
      }
	
      if (partnum==-2) {
	if (wordsdisplay) {
	  texteur(ANGLAIS,1.8,1.7);
	  texteur(FRANCAIS,-1,1.7);
	}


	starfield();
	glEnable(GL_BLEND);
	cuboid->afficher_cuboid();
	glDisable(GL_BLEND);
      }
      if (partnum==-13) {


















  unsigned int textures[12];
  Mandelbrot *mandel[12];
  int iw=640;
  int ih=480;
if (premierevbl) {

  glGenTextures(12,textures);
    for (int i=0;i<12;i++) {
      glBindTexture(GL_TEXTURE_2D,textures[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR/*GL_NEAREST*/); /*pas d'interpolation, le pixel le plus prés est pris*/
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR/*GL_NEAREST*/); /*pas d'interpolation, le pixel le plus prés est pris*/
      printf("lala\n");
      mandel[i] = new Mandelbrot(iw,ih,40);
      glTexImage2D(GL_TEXTURE_2D, 
		   0/*mipmap level*/, 
		   GL_RGB,// internal format 
		   iw, 
		   ih, 
		   0/*width of border*/, 
		   GL_RGB, 
		   GL_UNSIGNED_BYTE, 
		   mandel[i]->pix);
      printf("lala2");
	
    }
  }


{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear( gRenderer );

	int alphas[12];
	int intensitemax=0;
	//recherche de l'intensité max
	for (int i=0;i<12;i++) {
		if (notes_val_dans_l_octave[i]>intensitemax)
			intensitemax=notes_val_dans_l_octave[i];
	}
	int nb_couches=0;
	for (int i=0;i<12;i++) {
		if (note_on_off[i])
			nb_couches=nb_couches+1;
	}

	if (nb_couches>0) {
		// on va commencer par trier ces couches
		int i=0;
		int ptr[12]={0,1,2,3,4,5,6,7,8,9,10,11};
		int echange;
		do {
			i=0;
			echange=0;
			do {
				if (notes_val_dans_l_octave[ptr[i]] < 
					notes_val_dans_l_octave[ptr[i+1]]) {
						int aux=ptr[i];
						ptr[i]=ptr[i+1];
						ptr[i+1]=aux;
						echange=1;
					}
				i=i+1;
			} while ((i!=11) && (echange==0));
		} while (echange==1);
			//on normalise pour que la couche avec le val max soit avec un alpha de 255 et que les autres aient des alphas proportionnels
		for (int i=0;i<12;i++) {
			alphas[i]=(int)(255*((float)(notes_val_dans_l_octave[i]))/((float)(intensitemax)) /*/nb_couches*/ );
		}/*
					fprintf(stderr,"alphas : ");
					for (int i=0;i<12;i++) {
					fprintf(stderr,"%d ",alphas[i]);
					}
					fprintf(stderr,"\n");
				*/
				// c'est une merveilleuse petite machine, tout est sauvé, 
				//c 'est un terrain de jeu formidable 
		for (int i=0;i<12;i++) {
			alphas[ptr[i]]=alphas[ptr[i]] / pow(2,i+1-1);
		}
				//int a=255/nb_couches;
		for (int i=0;i<12;i++) {
			if ((note_on_off[ptr[i]])) {
				SDL_SetTextureAlphaMod( newTexture[ptr[i]+1], alphas[ptr[i]] );
				renderTexture(newTexture[ptr[i]+1], 0, 0, NULL );
			}
		}
	}
    //Update screen
	SDL_RenderPresent( gRenderer );
	}




































































































































}
if (partnum==-17) {

	if (mandelmap==NULL) 
		mandelmap=new MandelMap();
	starfield();
	//progstarfield->process();
	mandelmap->display();
      }

      if (partnum==-12) {
	dodeca->draw();
      }
      if (partnum==-11) {
	hcube->draw();
      }
      if (partnum==ORBITATION) {
	
	//drawTorus(0);
	progstarfield->process();
	orbitation->process();
	detecteurdesequences->process(tab_notes[nb_notes-1].name,tab_notes[nb_notes-1].time);
      }	
				
      if (partnum==MIKADO) {

	starfield();
	mikado->affiche_mikado();
				
	//simplecube->affiche_cube();
	//landscaper->landscaper_modify();
	//landscaper->landscaper_affiche();
	//afficheurDeSquircles->affiche();
	/*
	  if (!esquisselist = glGenLists(1);
	  glNewList(esquisselist,GL_COMPILE);
	  printf("hum\n");
	  float incz=1/12.0;
	  float z=-6*incz;
	  for (int i=0;i<12;i++) {
	  esquisse(-0.8,0,z, 0.8,0,z);
	  z+=incz;
	  }
	  printf("hop\n");
	  glEndList();
	  esquisseinitialized=1;


	  //glRotatef( 360.0*compteur[ii]/100, 1,0,0);
	  }
				
	  glRotatef(moteur % 360, 1, 1, 1);

	  glTranslatef(0,0.0,0.6);
	  int lsav; glGetIntegerv(GL_LIGHTING,&lsav);
	  glDisable(GL_LIGHTING);
	  glCallList(esquisselist);
	  if (lsav) glEnable(GL_LIGHTING);else glDisable(GL_LIGHTING);
	*/
				
      }


      // on décentre un peu
      if (partnum==12) {
	//gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);             
	glLoadIdentity();                       
	gluLookAt(0,0,-3, 0,0,0, 0,1,0); // pos, point qu'il regarde, up
	starfield();
	damier_de_points();
	glPopMatrix();
	tcube(0,0,0,1);

      }	
	
      if (partnum==-3) {
	if (wordsdisplay) {
	  texteur(ANGLAIS,1.8,1.7);
	  texteur(FRANCAIS,-1,1.7);
	}


	starfield();
	cubesdanscubes(0,0,0,0.5);
      }
      if (partnum==-4) {
	starfield();
	insidecube(0,0,0,1);
      }
      /*	
		je peux faire varier des paramètres du programme
		en temps réel dans le fichier parametres.cfg et appuyer sur ^P dans reglage pour les valider
      */


      if (1) {
	
	if (partnum==1) {
	  tcube(0,0,0,1);
	}
	if (partnum==2) {
	  cubar();
	}
	if (partnum==-9) {
	  starfield();
	  cubar2();   
	}
	if (partnum==3) {
	  if (wordsdisplay) {
	    texteur(ANGLAIS,1.8,1.7);
	    texteur(FRANCAIS,-1,1.7);
	  }
	

	  nlcube(0,0,0,1,0.1,1);
	}
	if (partnum==4) {
	  if (wordsdisplay) {
	    texteur(ANGLAIS,1.8,1.7);
	    texteur(FRANCAIS,-1,1.7);
	  }
	
	  starfield();
	  ballon(); // la sphère de particules
	}
	if (partnum==5) {
	  balballon();
	}
	if (partnum==6) {



	  tetrapart();
	}
	if (partnum==7) {
	  octogone();
	}
	if (partnum==8) {
	  affiche_pastilles=1;	
	  pastillage(); 
	  vaisseau_game();
	  affiche_pastilles=0;	
	}
	if (partnum==9) {
	  affiche_pastilles=1;	
	  pastillage(); 
	  vaisseau_game();
	  affiche_pastilles=0;	
	}	
	if (partnum==10) {
	  sdamier();
	}	
	if (partnum==11) {
	  damier();
	}	

  }
      SDL_GL_SwapWindow(glwin);
      if (premierevbl) {premierevbl=0;} else {
	vbl++;
	moteur += inc_moteur;
	moteur1 += inc_moteur1;
	moteur2 += inc_moteur2;
	moteur3 += inc_moteur3;
      }
    } else {

      sleep(1);

    }
    for (int i=0;i<12;i++) {

      newnotes_val[i]=0; // je me demande si cette ligne est bien utile mais c'est peut être une sécurité dans certains cas
    }
  }
}

void change_parametres() {
  FILE *fichier = NULL;
  char s[1024];
  char var[64];
  char val[64];

  fichier = fopen("/home/pi/prg/colormusic/parametres.cfg","r+");
	
  int over=0;

  printf("le pédiluve avec un animal qu'on vient de retrouver en australie, est-ce une expérience génétique ou un poisson d'avril\n");


  while (!over) {
    if (fgets( s, 128, fichier ) != NULL) {	// donc on a récupéré une nouvelle chaine du fichier
      // on va parcourir la chaine pour obtenir la variable et la valeur
      int i=0;
      printf("est-ce qu'on passe par la douche italienne\n");
			
      while (s[i]!=':') {
	var[i]=s[i];
	i++;
      }
      //i--;
      printf("le petit train amphibie du programme est arrivé jusque là\n");
      var[i]='\0'; // le merveilleux petit caractère indiquant qu'on est à la fin de la chaine
      int offset = strlen(var)+1;
      i=0;
      // on recommence pour avoir la valeur (comme un chevalier !)
      while (s[i+offset]!='\n') {
	val[i]=s[i+offset];
	i++;
      }
      val[i]='\0';
      printf("%s/%s\n",var,val);
      if (strcmp(var,"chevalière")==0) {
	printf("on a trouvé une fille !\n");
      }
      if (strcmp(var,"force_de_rappel_k")==0) {
	for (int i=0;i<NB_PASTILLES;i++) {
	  tab_pastilles_particules[i]->force_de_rappel_k=atof(val);
	}
      }
      if (strcmp(var,"resistance_fluide_k")==0) {
	for (int i=0;i<NB_PASTILLES;i++) {
	  tab_pastilles_particules[i]->resistance_fluide_k=atof(val);
	}
      }
      if (strcmp(var,"kS")==0) {
	for (int i=0;i<NB_PASTILLES;i++) {
	  tab_pastilles_particules[i]->kS=atof(val);
	}
      }
    } else {
      over = 1;
    }
  }
}
/*
  class Tetraedre {
  public:
  float A[3];
  float B[3];
  float C[3];
  float D[3];

  Tetraedre() {
  float b=a / (2.0*sqrt(2));

  float dhf[3]; setvec(-b,b,b,dhf);
  float gbf[3]; setvec(b,-b,b,gbf);
  float ghd[3]; setvec(b,b,-b,ghd);
  float dbd[3]; setvec(-b,-b,-b,dbd);
  glPointSize(5);
  glLineWidth(3);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_LIGHT1);  
  glDisable(GL_BLEND);
  glTranslatef(x,y,z);
  glBegin(GL_TRIANGLES);
  {
  //glColor3ub(comp(numcol));
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol]);
    
  pvec(2*b,-2*b,0, 2*b,0,-2*b,nor);

  // j'ai mes précieuses normales, donc maintenant, ce qui est sûr c'est que je vais avoir besoin du barycentre

  normalize(nor);
  glNormal3f(nor[0],nor[1],nor[2]);

  float d=sqrt(b*b+b*b+b*b);
  //glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
  float dhf[3]; setvec(-b,b,b,dhf);
  glVertex3f(-b, b, b); //à droite en haut au fond
  //glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
  float gbf[3]; setvec(b,-b,b,gbf);
  glVertex3f( b,-b, b); //à gauche en bas au fond
  //glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
  float ghd[3]; setvec(b,b,-b,ghd);
  glVertex3f( b, b,-b); //à gauche en haut devant

  pvec(2*b,0,-2*b,0,-2*b,-2*b,nor);
  normalize(nor);
  glNormal3f(nor[0],nor[1],nor[2]);
  //vert


  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol+1]);
  //glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
  glVertex3f(-b, b, b); //à droite en haut au fond
  //glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
  glVertex3f( b, b,-b); //à gauche en haut devant
  //glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
  float dbd[3]; setvec(-b,-b,-b,dbd);
  glVertex3f(-b,-b,-b); //à droite en bas devant

  pvec(-2*b,0,-2*b,0,2*b,-2*b,nor);
  normalize(nor);
  glNormal3f(nor[0],nor[1],nor[2]);
  //marron

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol+2]);
  //glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
  glVertex3f( b,-b, b); //à gauche en bas au fond
  //glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
  glVertex3f(-b,-b,-b); //à droite en bas devant
  //glNormal3f(b/d,b/d,-b/d); //à gauche en haut devant
  glVertex3f( b, b,-b); //à gauche en haut devant

  pvec(-2*b,2*b,0,-2*b,0,-2*b,nor);
  normalize(nor);
  glNormal3f(nor[0],nor[1],nor[2]);
  //rouge

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,tabcomposantes[numcol+3]);
  //glNormal3f(b/d,-b/d,b/d); //à gauche en bas au fond
  glVertex3f( b,-b, b); //à gauche en bas au fond
  //glNormal3f(-b/d,b/d,b/d); //à droite en haut au fond
  glVertex3f(-b, b, b); //à droite en haut au fond
  //glNormal3f(-b/d,-b/d,-b/d); //à droite en bas devant
  glVertex3f(-b,-b,-b); //à droite en bas devant
  }
  glEnd();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  
  }		
  }
  };
*/


	
