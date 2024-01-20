# Philosophers - Threads and Mutexes

### Installation

```bash
git clone https://github.com/tlouro-c/philosophers.git
cd philosophers
make
```
### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Allowed External Functions

<ul>
  <li>memset</li>
  <li>printf</li>
  <li>malloc</li>
  <li>free</li>
  <li>write</li>
  <li>usleep</li>
  <li>gettimeofday</li>
  <li>pthread_create</li>
  <li>pthread_detach</li>
  <li>pthread_join</li>
  <li>pthread_mutex_init</li>
  <li>pthread_mutex_destroy</li>
  <li>pthread_mutex_lock</li>
  <li>pthread_mutex_unlock</li>
</ul>

### Learning Outcome
<ul>
  <li>Threads and mutexes implementation</li>
  <li>Solving logic problems inspired by the dining philosophers' scenario</li>
</ul>

