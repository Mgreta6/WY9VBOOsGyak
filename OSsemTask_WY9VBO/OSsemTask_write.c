// Ír
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10
  
// Struktúra az üzenetsorhoz
struct msg_buffer {
    long msg_tipus;
    char msg_uzenet[100];
} uzenet;



int main()
{
    key_t kulcs;
    int msgid, szam;
  
    // Kulcsgenerálás
    kulcs = ftok("beadando", 10);
  
    // Az msget() megcsinálja az üzenetsort,
    // az msgid pedig ennek az üzenetsornak az azonosítóját tárolja
    msgid = msgget(kulcs, 0666 | IPC_CREAT);
    uzenet.msg_tipus = 1;
  
    
    szam=getpid();
	printf("Kezdoérték: %d\n\n", szam);
	
    while (szam < 100000) {
    printf("Adat irasa folyamatban...\n");
    sprintf(uzenet.msg_uzenet, "%d", szam);
    
	
    // Az msgsnd() elküldi az üzenetet
    msgsnd(msgid, &uzenet, sizeof(uzenet), 0);
  

    szam=szam+2;
    sleep(1);
  }
  
    return 0;
}