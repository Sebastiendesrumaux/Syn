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


#include <sys/stat.h>

char * myfifop2c = "/tmp/fifol2i";
FILE  *fdp2c;
char * myfifoc2p = "/tmp/fifoi2l";
int fdc2p;
void write_tube(char *s) {
  printf("Write tube : %s %d\n", s, strlen(s));
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
    mkfifo(myfifop2c,0666);
  }
  printf("Tube crée.\n");

  
  fdc2p = open(myfifoc2p, O_WRONLY); //bloque tant que pas de lecteur
  printf("Tube i2l ouvert (tube d'écriture).\n");

  fdp2c = fopen(myfifop2c, "r");
  printf("Tube l2i ouvert (tube de lecture).\n");
}
void close_tube() {
  printf("Fermeture des tubes.\n");
  unlink(myfifop2c);
  unlink(myfifoc2p);
  
  close(fdc2p);
  fclose(fdp2c);
  printf("Tubes fermés.\n");
}
void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("on se fait kill, on envoie usr1 à reglage pour dire qu'il n'y a plus de clavier\n");
    system("/usr/bin/sudo /usr/bin/killall -USR1 reglage"); //on envoie usr1 pour dire qu'il n'y a plus de clavier
    exit(1);
  }
  if (signo == SIGUSR2) { //
    printf("on reçoit usr2 de reglage\n, on envoie un sigusr2 pour dire qu'il y a bien un clavier\n");
    system("/usr/bin/sudo /usr/bin/killall -USR2 reglage");
    
  }
  if (signo == SIGHUP) {
    printf("reglage envoie un sighup\n");
  }
}


void main(int argc, char **argv) {

  //open_tubes();
  signal(SIGINT, sig_handler);
  signal(SIGUSR2, sig_handler);
  signal(SIGHUP, sig_handler);
  
  system("/usr/bin/sudo /usr/bin/killall -USR2 reglage"); //on envoie usr2 pour dire qu'il y a à nouveau un clavier

  while (1) {
    sleep(1);
  }
}
