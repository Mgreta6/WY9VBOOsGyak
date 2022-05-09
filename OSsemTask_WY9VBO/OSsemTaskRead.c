// Olvas
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
  
// Struktúra az üzenetsorhoz
struct msg_buffer {
    long msg_tipus;
    char msg_uzenet[100];
} uzenet;


int main()
{
    key_t kulcs;
    int msgid, beszam;
  
    // Kulcsgenerálás
    kulcs = ftok("beadando", 10);
  
    // Az msget() megcsinálja az üzenetsort,
    // az msgid pedig ennek az üzenetsornak az azonosítóját tárolja
    msgid = msgget(kulcs, 0666 | IPC_CREAT);
    

    // A kapott üzenetet (string) számmá alakítjuk (int)
    beszam=atoi(uzenet.msg_uzenet);
    
    // Amíg az üzenet kisebb mint 100000, folytatjuk az olvasást (ugyan ez van az írásnál is, így egyszerre fejezik be)
    while (beszam < 100000) {

    beszam=atoi(uzenet.msg_uzenet);

    // Az msgrcv() beolvassa az adott azonosítójú üzenetsorból az üzenetet
    msgrcv(msgid, &uzenet, sizeof(uzenet), 1, 0);
  
    // Kiíratjuk a kapott üzenetet
    printf("Beerkezett adat: %s \n", uzenet.msg_uzenet);

    }

    // Amint a while ciklus befejeződik, töröljük az üzenetsort
    msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}