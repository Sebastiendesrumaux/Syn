#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <termio.h>
#include <signal.h>
#include <fcntl.h>

#include <limits.h>
#include <unistd.h>



#include <stdlib.h>

int aff_key=1;
// on va avoir un fichier de paramètres et quand on appuie sur la touche p, ça envoie au programme l'ordre de le relire
#include <sys/stat.h>
int l_getched=0;
int pas_de_clavier=1;

char * myfifop2c = "/tmp/fifoi2l";
FILE  *fdp2c;
char * myfifoc2p = "/tmp/fifol2i";
int fdc2p;
void write_tube(char *s) {
  //  printf("Write tube : %s %d\n", s, strlen(s));
  write(fdc2p, s, strlen(s));
  //printf("tube written: %s %d\n", s, strlen(s));
}
void wait_tube() {
  char buf[128];
  //printf("wait tube\n");
  fgets(buf, 100, fdp2c);
  //printf("tube waited\n");
}
char rbuf[128];
char *read_tube() {
  
  fgets(rbuf, 100, fdp2c);
  return rbuf;
}
void open_tubes() {
  /* create the FIFO (named pipe) */
  // struct stat buf;
  printf("Création du tube i2l\n");
  if (access(myfifoc2p,F_OK) == -1) {
    // if (fopen(myfifo,"r") == NULL) {
    printf("Le tube i2l n'existe pas déjà\n");
    mkfifo(myfifoc2p, 0666);
  }
  printf("Tube crée.\n");

  printf("Création du tube l2i\n");
  if (access(myfifop2c,F_OK) == -1) {
    // if (fopen(myfifo,"r") == NULL) {
    printf("Le tube l2i n'existe pas déjà\n");
    mkfifo(myfifop2c, 0666);
  }
  printf("Tube crée.\n");

  fdp2c = fopen(myfifop2c, "r");
  printf("Tube l2i ouvert (tube en lecture).\n");

  fdc2p = open(myfifoc2p, O_WRONLY); //bloque tant que pas de lecteur
                                     
  printf("Tube i2l ouvert (tube en écriture).\n");

}
void close_tube() {
  printf("Fermeture des tubes.\n");
  unlink(myfifop2c);
  unlink(myfifoc2p);
  
  close(fdc2p);
  fclose(fdp2c);
  printf("Tubes fermés.\n");
}


#define RING_SIZE 10
int ring[RING_SIZE];
int i_ring=0;
void init_ring() {
  for (int i=0;i<RING_SIZE;i++) {
    ring[i]=0;
  }
}
int get_ring() {
  return ring[i_ring];
}
void put_ring(int val) {
  i_ring=i_ring+1;
  if (i_ring==RING_SIZE) {
    i_ring=0;
  }
  ring[i_ring]=val;
}
int ring_avant() {
  if (i_ring-1 < 0) {
    return ring[RING_SIZE-1];
  } else {
    return ring[i_ring-1];
  }
}
int ring_avant_avant() {
  if (i_ring-2 == -1) return ring[RING_SIZE-1];
  if (i_ring-2 == -2) return ring[RING_SIZE-1-1];
  return ring[i_ring-2];
}
int ring_avant_avant_avant() {
  if (i_ring-3 == -1) return ring[RING_SIZE-1];
  if (i_ring-3 == -2) return ring[RING_SIZE-1-1];
  if (i_ring-3 == -3) return ring[RING_SIZE-1-2];
  return ring[i_ring-3];
}
int ring_avant_avant_avant_avant() {
  if (i_ring-4 == -1) return ring[RING_SIZE-1];
  if (i_ring-4 == -2) return ring[RING_SIZE-1-1];
  if (i_ring-4 == -3) return ring[RING_SIZE-1-2];
  if (i_ring-4 == -4) return ring[RING_SIZE-1-3];
  return ring[i_ring-4];
}
int ring_avant_avant_avant_avant_avant() {
  if (i_ring-5 == -1) return ring[RING_SIZE-1];
  if (i_ring-5 == -2) return ring[RING_SIZE-1-1];
  if (i_ring-5 == -3) return ring[RING_SIZE-1-2];
  if (i_ring-5 == -4) return ring[RING_SIZE-1-3];
  if (i_ring-5 == -5) return ring[RING_SIZE-1-4];
  return ring[i_ring-5];
}
static struct termios term, back;

int ret = -1;

int l_getch (void) {

  tcgetattr (0, &term); //get term info
  memcpy (&back, &term, sizeof(term));

  term.c_lflag &= ~(ICANON|ECHO);//change term attr
  term.c_cc[VTIME] = 1; //latency
   term.c_cc[VMIN] = 1; //nb char

  tcsetattr(0, TCSANOW, &term); //change stdin attr
  l_getched=1;
  // ret = getchar();
  //  tcsetattr(0, TCSANOW, &back); //restore attr

  return ret;
}
void sig_handler(int signo) {
  printf("signal received : %d\n",signo);
  if (signo == SIGINT) {
    printf("receive sigint\n");
    if (l_getched) 
      tcsetattr(0, TCSANOW, &back); //restore attr
    //    close_tube();
    exit(1);
  }
  if (signo == SIGUSR2) {
    //    printf("receive sigusr2, à nouveau un clavier\n");
    //l_getch();
    pas_de_clavier=0;
  }
  if (signo == SIGUSR1) {
    //printf("receive sigusr1, plus de clavier\n");
    pas_de_clavier=1;
  }

}



int haptique=0;
int fd;
int maestroSetTarget(int fd, unsigned char channel, unsigned short target)
{
  unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
  if (write(fd, command, sizeof(command)) == -1)
    {
      perror("error writing");
      return -1;
    }
  return 0;
}

int initMaestro()
{
  // Open the Maestro's virtual COM port.
  //const char * device = "\\\\.\\USBSER000";  // Windows, "\\\\.\\COM6" also works
  const char * device = "/dev/ttyACM0";  // Linux
  //const char * device = "/dev/cu.usbmodem00034567";  // Mac OS X
  fd = open(device, O_RDWR | O_NOCTTY);
  //  printf("dev opened\n");
  if (fd == -1)
    {
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
  // int position = 0;

  //printf("Current position is %d.\n", position);

  //int target = (position == 4500 ? 5000 : 4500);
  //int target = 1500;
  //printf("Setting target to %d (%d us).\n", target, target/4);


  
  return 0;
}

int fd_valeurs = -1;
int servo_en_cours = 0;
int servos_vals[12];

int read_valeurs(void) {
  FILE *fichier = NULL;
  char s[1024];
  fichier = fopen("/home/pi/prg/colormusic/valeurs_servo_max.txt","r+");
  fgets(s, 1024, fichier );
  fclose(fichier);
  char ch[10];
  int ivals=0;
  int ich=0;
  //  printf("%s\n",s);
  for (int i=0; i<strlen(s); i++) {
    if (s[i]==' ') {
      ch[ich]='\0';
      int val = atoi(ch);
      servos_vals[ivals]=val;
      ich=0;
      ivals=ivals+1;
    } else {
      ch[ich]=s[i];
      ich=ich+1;
    }
  }
  for (int i=0; i<12; i++) {
    // printf("%d\n", servos_vals[i]);
  }
  return 0;
}

int write_valeurs(void) {
  FILE *fichier = NULL;
  char s[1024];
  char t[10];
  sprintf(s,"");
  fichier = fopen("/home/pi/prg/colormusic/valeurs_servo_max.txt","w");
  for (int i=0; i<12; i++) {
    sprintf(t,"%d ",servos_vals[i]);
    strcat(s,t);
    //sprintf(s, "%s %d ",s,servos_vals[i]);
  }
  printf("write valeur : %s\n",s);
  fputs(s,fichier);
  fclose(fichier);
  //fgets(s, 1024, fichier );
  return 0;
}

int val_min=992*4+128;
int val_nor=6000;
int val_max=12000;
int increment = 40;

int ring_aa() {
  return ring_avant_avant();
}

int ring_aaa() {
  return ring_avant_avant_avant();
}

int ring_aaaa() {
  return ring_avant_avant_avant_avant();
}

int ring_aaaaa() {
  return ring_avant_avant_avant_avant_avant();
}
int aff_ring() {
  fprintf(stdout,"%d %d %d %d %d %d\n",
	  get_ring(),
	  ring_avant(),
	  ring_avant_avant(),
	  ring_avant_avant_avant(),
	  ring_avant_avant_avant_avant(),
	  ring_avant_avant_avant_avant_avant()); 
}

#define FR 1
#define EN 2

void aff_msg(int langue, char *msgfr, char *msgen) {
  if (langue==FR) fprintf(stdout,msgfr);
  if (langue==EN) fprintf(stdout,msgen);
}

/*int etoile;
int read_conf() {
  FILE *fichier = NULL;
  char s[1024];
  fichier = fopen("/home/pi/prg/colormusic/conf.txt","r");
  if (fichier == NULL) {
    etoile=1;
  }
  fgets(s, 1024, fichier);
  fclose(fichier);
  strcmp(s,"1\n");
}

int write_conf() {
  FILE *fichier = NULL;
  char s[1024];
  char t[10];
  sprintf(s,"");
  fichier = fopen("/home/pi/prg/colormusic/conf.txt","w");
  //for (int i=0; i<12; i++) {
  //sprintf(t,"%d ",servos_vals[i]);
  //strcat(s,t);
    //sprintf(s, "%s %d ",s,servos_vals[i]);
  //}
  sprintf(s, "%s\n", atoi(etoile));
  printf("write conf : %s\n",s);
  fputs(s,fichier);
  fclose(fichier);
  //fgets(s, 1024, fichier );
  return 0;

}
*/

char *servo2note(int servo, int langue) {
  
  if (langue == FR) {
    if (servo == 0) return("do");
    if (servo == 1) return("do#");
    if (servo == 2) return("ré");
    if (servo == 3) return("ré#");
    if (servo == 4) return("mi");
    if (servo == 5) return("fa");
    if (servo == 6) return("fa#");
    if (servo == 7) return("sol");
    if (servo == 8) return("sol#");
    if (servo == 9) return("la");
    if (servo == 10) return("la#");
    if (servo == 11) return("si");    		  
  } else if (langue == EN) {
    if (servo == 0) return("C");
    if (servo == 1) return("C#");
    if (servo == 2) return("D");
    if (servo == 3) return("D#");
    if (servo == 4) return("E");
    if (servo == 5) return("F");
    if (servo == 6) return("F#");
    if (servo == 7) return("G");
    if (servo == 8) return("G#");
    if (servo == 9) return("A");
    if (servo == 10) return("A#");
    if (servo == 11) return("B");    		  
  }
  return "servo2note";
}

char stemp1[256];
char stemp2[256];
int langue=FR;

void aff_menu() {
  
  if (langue == FR) fprintf(stdout,"Press l to get the english menu.\n");
  
  if (langue == EN) fprintf(stdout,"Appuyer sur l pour avoir ce menu en français.\n");
  
  aff_msg(langue,"ESPACE : pour afficher ce menu.\n","SPACE BAR : to display this menu.\n");
  
  // aff_msg(langue,"Flèche à droite/flèche à gauche : pour augmenter/diminuer la pression maximale exercée par la note en cours.\n","Right arrow/left arrow : to increase/decrease the maximal pressure put by the current note.\n");
  
  //aff_msg(langue,"F1 F2 F3 F4 F5 F6 F7 F8 F9 F0 F11 F12 : pour changer la note en cours.\n","F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12 : to change the current note.\n");
  
  //aff_msg(langue,"0 : pour mettre toutes les pressions à 0.\n","0 : to reset all the pressures.\n");
  
  //aff_msg(langue,"Entrée : pour valider votre réglage en cours.\n","Enter : to validate current settings.\n");
  //aff_msg(langue,"r : pour reset la masseuse (en cas d'activité intempestive de ses petits moteurs).\n","r : to reset the massage board (if it's making noise while resting.\n");
  //aff_msg(langue,"c : pour éteindre les lumières.\n","c : to switch off the lights.\n");
  //aff_msg(langue,"f : pour activer/désactiver le mode ""flottant"" d'affichage sur une guirlande de leds.\n","f : to activate/desactivate floating mode on leds-strip.\n");
  aff_msg(langue,"s : pour sauvegarder.\n","s : to save.\n");
  aff_msg(langue,"i : pour cacher/afficher l'afficheur 3D.\n","i : to show/hide 3D display.\n");
  aff_msg(langue,"o : pour cacher/afficher l'afficheur d'images.\n","o : to show/hide pictures display.\n");
  aff_msg(langue,"1 2 3 4 5 6 7 8 9 : pour choisir dans quel répertoire sont chargées les images.\n","1 2 3 4 5 6 7 8 9 : to choose which folder is used to load the pictures.\n");
 //aff_msg(langue,"m : pour changer le mode d'affichage des lumières sur le cercle lumineux.\n","m : To change lighting mode of light circle.\n");
  aff_msg(langue,"u : pour copier les images jpg 640x480 présentes dans les répertoires i d'une clé usb préalablement insérée.\n","u : to copy jpg 640x480 images from i folders of an inserted usb key.\n");
  aff_msg(langue,"v : pour convertir les images copiées par réseau à la bonne résolution.\n","v : to convert network copied images resolutions.\n");
  aff_msg(langue,"n : pour changer de partie dans l'afficheur 3D.\n","m : To change of part in the 3D display.\n");
  aff_msg(langue,"a : pour afficher dans quel répertoire sont chargées les images.\n","a : to display images's folder num.\n");
  aff_msg(langue,"A : pour toggle l'autochange de parties.\n","A : To toggle autochange of parts in the 3D display.\n");
  aff_msg(langue,"B : Exit and rerun.\n","B : Exit and rerun.\n");
  aff_msg(langue,"L : pour toggle l'affichage des mots.\n","L : To toggle l'affichage des mots.\n");
  aff_msg(langue,"w : pour activer/désactiver les fonctions faisant appel à l'internet.\n","w : to activate/desactivate net functions.\n");
}
int main(int argc, char **argv) {
  FILE *f;
  //printf("lancement de reglage\n");
  //printf("%s %d* %d\n",argv[1], argc, strcmp(argv[1],"-k")  );
  if ((argc==2) && (!strcmp(argv[1],"-k"))) {
    printf("ok, prise en compte d'un clavier réseau\n");
    pas_de_clavier=0;
  }

  initMaestro();
  read_valeurs();
  //  open_tubes();
  //printf("try to write tube\n");
  //write_tube("?\n");
  //printf("tube writed\n");
  //wait_tube();
  signal(SIGINT,  sig_handler);
  signal(SIGUSR1, sig_handler);
  signal(SIGUSR2, sig_handler);

  //printf("l_getch est désactivé, penser à le remettre\n");
  l_getch();
  //  printf("on envoie usr2 à is_keyboard, il doit nous renvoyer usr2 pour indiquer qu'il y a un clavier\n");
  system("/usr/bin/sudo /usr/bin/killall -USR2 is_keyboard");
  //  system("/usr/bin/killall -USR2 sudo ./is_keyboard");

  init_ring();
  aff_menu();
  while (1) {
    if (!pas_de_clavier) {
      //      write_tube("?\n");
      //wait_tube();
      //printf("tube waited\n");

      ret = getchar();
      put_ring(ret);
      if (aff_key) {
	printf("%d\n---\n", ret);
	aff_ring();
	printf("get_ring() : %d \n",get_ring());
      }
      int last_servo_en_cours=servo_en_cours;

      if ((get_ring()==80) && (ring_avant()==79) && (ring_aa()==27)) {
	aff_msg(langue,"Note en cours : do\n","Current note : C\n");
	servo_en_cours=0;
      } else if ((get_ring()==81) && (ring_avant()==79) && (ring_aa()==27)) {
        aff_msg(langue,"Note en cours : do#\n","Current note : C#\n");
	servo_en_cours=1;
      } else if ((get_ring()==82) && (ring_avant()==79) && (ring_aa()==27)) {
	aff_msg(langue,"Note en cours : ré\n","Current note : D\n");
	servo_en_cours=2;
      } else if ((get_ring()==83) && (ring_avant()==79) && (ring_aa()==27)) {
	aff_msg(langue,"Note en cours : ré#\n","Current note : D#\n");
	servo_en_cours=3;
      } else if ((get_ring()==126) && (ring_avant()==53) && (ring_aa()==49) && ring_aaa()==91 && ring_aaaa()==27)  {
	aff_msg(langue,"Note en cours : mi\n","Current note : E\n");
	servo_en_cours=4;
      } else if ((get_ring()==126) && (ring_avant()==55) && (ring_aa()==49) && (ring_aaa()==91) && ring_aaaa()==27) {
	aff_msg(langue,"Note en cours : fa\n","Current note : F\n");
	servo_en_cours=5;
      } else if ((get_ring()==126) && (ring_avant()==56) && (ring_aa()==49) && (ring_aaa()==91) && ring_aaaa()==27) {
	aff_msg(langue,"Note en cours : fa#\n","Current note : F#\n");
	servo_en_cours=6;
      } else if ((get_ring()==126) && (ring_avant()==57) && (ring_aa()==49) && (ring_aaa()==91) && ring_aaaa()==27) {
	aff_msg(langue,"Note en cours : sol\n","Current note : G\n");
	servo_en_cours=7;
      } else if ((get_ring()==126) && (ring_avant()==48) && (ring_aa()==50) && (ring_aaa()==91) && ring_aaaa()==27) {
	aff_msg(langue,"Note en cours : sol#\n","Current note : G#\n");
	servo_en_cours=8;
      } else if ((get_ring()==126) && (ring_avant()==49) && (ring_aa()==50) && (ring_aaa()==91) && ring_aaaa()==27) {
	aff_msg(langue,"Note en cours : la\n","Current note : A\n");
	servo_en_cours=9;
      } else if ((get_ring()==126) && (ring_avant()==51) && (ring_aa()==50) && (ring_aaa()==91) && ring_aaaa()==27) {
	aff_msg(langue,"Note en cours : la#\n","Current note : A#\n");
	servo_en_cours=10;
      } else if ((get_ring()==33)) { // !
	if ((f=fopen("/home/pi/prg/colormusic/37","r"))==NULL) {
	  system("/usr/bin/sudo /usr/bin/touch /home/pi/prg/colormusic/37");
	  if (aff_key) {
	    aff_msg(langue,"Activate.\n","Activate.\n");
	  }
	} else {
	  fclose(f);
	  system("/usr/bin/sudo rm /home/pi/prg/colormusic/37");
	  if (aff_key) {
	    aff_msg(langue,"Desactivate.\n","Desactivate.\n");
	  }
	}
      } else if ((get_ring()==46)) { // .
	  system("/usr/bin/sudo cp /home/pi/prg/aff_oled/examples/parsing_ifconfig_result /home/pi/prg/colormusic/37T");
	   if (aff_key) {
	    aff_msg(langue,"Dumped.\n","Dumped.\n");
	  }
      }  else if ((get_ring()==126) && (ring_avant()==52) && (ring_aa()==50) && (ring_aaa()==91) && ring_aaaa()==27) {
	aff_msg(langue,"Note en cours : si#\n","Current note : B\n");
	servo_en_cours=11;
      } else if ((get_ring()==65) && (ring_avant()==91) && (ring_aa()==27))  {
	//printf("flèche en haut\n");
	servo_en_cours=servo_en_cours-1;
	if (servo_en_cours==-1) {
	  servo_en_cours=11;	  
	}
	sprintf(stemp1,"Note en cours : %s\n",servo2note(servo_en_cours,FR));
	sprintf(stemp2,"Current note : %s\n",servo2note(servo_en_cours,EN));
	aff_msg(langue,stemp1,stemp2);
      } else if ((get_ring()==66) && (ring_avant()==91) && (ring_aa()==27))  {
	//printf("flèche en bas\n");
	servo_en_cours=servo_en_cours+1;
	if (servo_en_cours==12) {
	  servo_en_cours = 0;
	}
	sprintf(stemp1,"Note en cours : %s\n",servo2note(servo_en_cours,FR));
	sprintf(stemp2,"Current note : %s\n",servo2note(servo_en_cours,EN));
	aff_msg(langue,stemp1,stemp2);
      } else if ((get_ring()==67) && (ring_avant()==91) && (ring_aa()==27))  {
	  //printf("flèche à droite\n");
	  servos_vals[servo_en_cours]=servos_vals[servo_en_cours]+increment;
	  if (servos_vals[servo_en_cours]>=val_max+increment) servos_vals[servo_en_cours]=val_max;
	  fprintf(stdout,"%d %d\n", servo_en_cours, servos_vals[servo_en_cours]);
	  maestroSetTarget(fd, servo_en_cours, servos_vals[servo_en_cours]);
      } else if ((get_ring()==68) && (ring_avant()==91) && (ring_aa()==27))  {
	  //printf("flèche à gauche\n");
	  servos_vals[servo_en_cours]=servos_vals[servo_en_cours]-increment;
	  if (servos_vals[servo_en_cours]<=val_min-increment) servos_vals[servo_en_cours]=val_min;
	  printf("%d %d\n", servo_en_cours, servos_vals[servo_en_cours]);
	  maestroSetTarget(fd, servo_en_cours, servos_vals[servo_en_cours]);
      } else if ((get_ring()==48) && (ring_avant()!=50)) {
	//printf("0\n");
	for (int i=0; i<12; i++) {
	  servos_vals[i]=val_min;
	  maestroSetTarget(fd, i, servos_vals[i]);
	  fprintf(stdout, "%d %d\n", i, servos_vals[i]);
	}
      } else if ((get_ring()==10)) {
	//printf("Enter\n");
	write_valeurs();
	for (int i=0; i<12; i++) {
	  maestroSetTarget(fd, i, val_min);
	}
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
      } else if ((get_ring()==99)) { //C
	system("/usr/bin/sudo /usr/bin/touch /tmp/clear");
	
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
      } else if ((get_ring()==102)) { //F
	if ((f=fopen("/tmp/randompos","r"))==NULL) {
	  system("/usr/bin/sudo /usr/bin/touch /tmp/randompos");
	  aff_msg(langue,"Activation du mode ""flottant"" pour l'affichage sur guirlande.\n","Floating-mode activated on leds-strip.\n");
	} else {
	  fclose(f);
	  system("/usr/bin/sudo rm /tmp/randompos");
	  aff_msg(langue,"Désactivation du mode ""flottant"" pour l'affichage sur guirlande.\n","Floating-mode unactivated on leds-strip.\n");
	}
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
      } else if ((get_ring()==111)) { //O
	if ((f=fopen("/home/pi/prg/colormusic/oglfull","r"))==NULL) {
	  system("/usr/bin/sudo /usr/bin/touch /home/pi/prg/colormusic/oglfull");
	  aff_msg(langue,"Désactivation de l'afficheur de photos.\n","Pictures display desactivated.\n");
	} else {
	  fclose(f);
	  system("/usr/bin/sudo rm /home/pi/prg/colormusic/oglfull");
	  aff_msg(langue,"Activation de l'afficheur de photos.\n","Pictures display activated.\n");
	}
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
      } else if ((get_ring()==105)) { //I
	if ((f=fopen("/tmp/imgwinfull","r"))==NULL) {
	  system("/usr/bin/sudo /usr/bin/touch /tmp/imgwinfull");
	  aff_msg(langue,"Désactivation de l'afficheur 3D.\n","3D display desactivated.\n");
	} else {
	  fclose(f);
	  system("/usr/bin/sudo rm /tmp/imgwinfull");
	  aff_msg(langue,"Activation de l'afficheur 3D.\n","3D screen activated.\n");
	}
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
      } else if (get_ring()==104) {//H
	system("/usr/bin/sudo /usr/bin/killall -USR1 synesthezyx");
      } else if (get_ring()==112) {//p
	system("/usr/bin/sudo /usr/bin/killall -USR2 synesthezyx");
      } else if (get_ring()==107) {//k
	aff_key=1;
      } else if (get_ring()==97) {//a
	aff_msg(langue,"Les images sont chargées dans le répertoire numéro : ","Images are loaded in directory number : ");
	system("cat /home/pi/prg/colormusic/numdir");
	printf("\n");
      } else if (get_ring()==65) {//A
	aff_msg(langue,"Toggle autochange.","Toggle autochange.");
	system("/usr/bin/sudo /usr/bin/touch /tmp/switchautochange");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	printf("\n");
      } else if (get_ring()==66) {//B
	aff_msg(langue,"Exit and rerun.","Exit and rerun.");
	system("/usr/bin/sudo /usr/bin/touch /tmp/exitandrerun");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	printf("\n");
      } else if (get_ring()==76) {//L

	if ((f=fopen("/home/pi/prg/colormusic/switchwordsdisplay","r"))==NULL) {
		system("/usr/bin/sudo /usr/bin/touch /home/pi/prg/colormusic/switchwordsdisplay");
	} else {
		fclose(f);
		system("/usr/bin/sudo rm /home/pi/prg/colormusic/switchwordsdisplay");
	}
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Toggle words.","Toggle words.");

	printf("\n");
	
      } else if (get_ring()==109) {//M
	if ((f=fopen("/tmp/lmmode","r"))==NULL) {
	  system("/usr/bin/sudo /usr/bin/touch /tmp/lmmode");
	} else {
	  fclose(f);
	  system("/usr/bin/sudo rm /tmp/lmmode");
	}
	aff_msg(langue,"Changement du mode d'affichage sur le cercle lumineux.\n","Lighting mode changed on lights circle.\n");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	
      } else if (get_ring()==114) {//R	
	system("/home/pi/prg/colormusic/setPololuDualPort");
	aff_msg(langue,"Reset de la feuille de massage effectué\n","The massage board has been reset.\n");
      } else if (get_ring()==110) {//n	
	system("/usr/bin/sudo /usr/bin/touch /tmp/partchange");
	aff_msg(langue,"Changement de partie.\n","Part change.\n");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	  } else if (get_ring()==16) { //^p
			system("/usr/bin/sudo /usr/bin/touch /tmp/chgparametres");
			aff_msg(langue,"Relecture de /home/pi/prg/colormusic/parametres.cfg\n","Parameters reading.\n");
			system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
      } else if (get_ring()==117) {//u
	aff_msg(langue,"Copie des images depuis la clé usb. Veuillez patienter.\n","Copying images from usb key. Please wait.\n");
	system("/bin/mkdir /media/key");
	system("/bin/mount /dev/sda1 /media/key -o nofail");
	system("/home/pi/prg/colormusic/autocopyusbkey");
	system("/bin/umount /media/key");
	system("/bin/rmdir /media/key");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Copie effectuée.\n","Copy done.\n");
       
      } else if (get_ring()==118) {//v
	aff_msg(langue,"Conversion des résolutions.\n","Resolutions converting.\n");
	system("/home/pi/prg/colormusic/autocopyusbkey");
	aff_msg(langue,"Conversion effectuée.\n","Conversio done.\n");
      } else if (get_ring()==115) {//s
	if ((f=fopen("/home/pi/prg/colormusic/sauve","r"))==NULL) {
	  system("/usr/bin/sudo /usr/bin/touch /home/pi/prg/colormusic/sauve");
	  aff_msg(langue,"Sauvegarde.\n","Saving.\n");
	} else {
	  fclose(f);
	  system("/usr/bin/sudo rm /home/pi/prg/colormusic/save");
	  aff_msg(langue,"Fin de la sauvegarde.\n","End of saving.\n");
	}
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
      }
      else if (get_ring()==119) {//w
	if ((f=fopen("/home/pi/prg/colormusic/netfunctions","r"))==NULL) {
	  system("/usr/bin/sudo /usr/bin/touch /home/pi/prg/colormusic/netfunctions");
	  aff_msg(langue,"Activation des fonctions faisant appel au net.\n","Net functions activated.\n");
	} else {
	  fclose(f);
	  system("/usr/bin/sudo rm /home/pi/prg/colormusic/netfunctions");
	  aff_msg(langue,"Désactivation des fonctions faisant appel au net.\n","Net functions desactivated.\n");
	}
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");

       

      } else if ((get_ring()==49) && (ring_avant()!=91)) {//1
	system("sudo /bin/echo \"1\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i1\n","Images are now loaded from i1\n");
      } else if ((get_ring()==50) && (ring_avant()!=91)) {//2
	system("sudo /bin/echo \"2\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i2\n","Images are now loaded from i2\n");
      } else if (get_ring()==51) {//3
	system("sudo /bin/echo \"3\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i3\n","Images are now loaded from i3\n");	
      } else if (get_ring()==52) {//4
	system("sudo /bin/echo \"4\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i4\n","Images are now loaded from i4\n");	
      } else if ((get_ring()==53) && (ring_avant()!=49)) {//5
	system("sudo /bin/echo \"5\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i5\n","Images are now loaded from i5\n");	
      } else if (get_ring()==54) {//6
	system("sudo /bin/echo \"6\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i6\n","Images are now loaded from i6\n");	
      } else if ((get_ring()==55) && (ring_avant()!=49)){//7
	system("sudo /bin/echo \"7\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i7\n","Images are now loaded from i7\n");	
      } else if ((get_ring()==56) && (ring_avant()!=49)) {//8
	system("sudo /bin/echo \"8\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i8\n","Images are now loaded from i8\n");		
      } else if ((get_ring()==57) && (ring_avant()!=49)){//9
	system("sudo /bin/echo \"9\" >/tmp/chgnumdir");
	system("/usr/bin/sudo /usr/bin/killall -HUP synesthezyx");
	aff_msg(langue,"Les images sont maintenant lues dans i9\n","Images are now loaded from i9\n");			
      } else if (get_ring()==32) {
	aff_menu();
      } else if (get_ring()==108) {
	if (langue==FR) langue=EN; else langue=FR;
	aff_menu();
      }

    } else { // pas de clavier
      // printf("pas de clavier\n");
      sleep(1);
    }
  }
}
