relaxed shared [5] int *shared shared_ptr_to_shared;
strict shared [5] int y[100 * THREADS];
strict shared [5] int z[100 * THREADS];
int x[100];
shared int shared_int;
int local_int = 99;
shared int *ptr_to_shared_int;

int
main ()
{
  int i;
  size_t size;
  upc_lock_t *lock;
  lock = upc_global_lock_alloc ();
  upc_barrier 1;
  upc_forall (i = 0; i < 100 * THREADS; ++i; &z[i])
    {
      int j;
      for (j = 0; j < 100; ++j)
	{
#pragma upc strict
	  if (x[i] < x[j])
	    {
	      upc_lock (lock);
	      z[i][j] = x[i] * y[j];
	      upc_unlock (lock);
	    }
	  else
	    {
	      upc_fence;
	      z[i][j] = -x[i] * y[j];
	      upc_fence;
	    }
	}
      upc_notify 10;
      upc_wait 10;
    }
  size = upc_blocksizeof (z);
  size = upc_localsizeof (z);
  size = upc_elemsizeof (z);
  upc_lock_free (lock);
}
