#include "philo.h"

#define TH 200

uint64_t		ledger = 0;
pthread_mutex_t	ledger_lock;

void	*update_ledger(void)
{
	pthread_mutex_lock(&ledger_lock);
	ledger++;
	pthread_mutex_unlock(&ledger_lock);
	return (NULL);
}

int	main(void)
{
	pthread_t	waiters[TH];
	int			i;

	if (pthread_mutex_init(&ledger_lock, NULL) != 0)
	{
		printf("Mutex initialization failed\n");
		exit(1);
	}
	i = 0;
	while (i < TH)
	{
		if (pthread_create(waiters + i, NULL, (void *)update_ledger, NULL))
			exit(1);
		++i;
	}
	i = 0;
	while (i < TH)
	{
		pthread_join(waiters[i], NULL);
		++i;
	}
	printf("Ledger: %llu\n", ledger);
	pthread_mutex_destroy(&ledger_lock);
}
