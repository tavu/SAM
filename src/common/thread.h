#ifndef THREAD_H
#define THREAD_H
#include<pthread.h>


class Thread
{
    public:
        Thread(){};
        virtual ~Thread(){};

        void start()
        {
            pthread_create(&thr,NULL,thr_run,this);
        }

        virtual int cancel()
        {
            return pthread_cancel(thr);
        }

        int join()
        {
            return pthread_join(thr, NULL);
        }

    protected:
        virtual int run()=0;

    private:
        static void* thr_run(void *r);

        pthread_t thr;
};

#endif