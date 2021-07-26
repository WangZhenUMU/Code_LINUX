#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <queue>

using namespace std;

#define THREAD_NUM 5

// 定义线程安全队列类型
typedef void (*HANDLER)(int);
class QueueType
{
    public:
        QueueType()
        {}
        QueueType(int data,HANDLER handler)
        {
            data_ = data;
            handler_ = handler;
        }
        void DealData()
        {
            handler_(data_);
        }
    private:
        int data_;
        HANDLER handler_;
};
class ThreadPool
{
    public:
        ThreadPool() // 线程池构造函数
        {
            capacity_=THREAD_NUM;
            pthread_mutex_init(&que_lock_,NULL);
            pthread_cond_init(&cons_cond_,NULL);
            pthread_cond_init(&prod_cond_,NULL);
            thread_num_=THREAD_NUM;
            is_quit_=false;
        }

        ~ThreadPool() //线程池析构函数
        {
            pthread_mutex_destroy(&que_lock_);
            pthread_cond_destroy(&cons_cond_);
            pthread_cond_destroy(&prod_cond_);
        }

        int Start()
        {
            // 创建线程
            for(int i = 0; i < THREAD_NUM; i++)
            {
                int ret = pthread_create(&tid_[i],NULL,ThreadPoolStart,(void*)this);
                if(ret<0) //判断是否创建成功
                {
                    perror("Pthread_create:");
                    thread_num_--;
                    continue;
                }
            }
            return thread_num_;
        }
        static void* ThreadPoolStart(void* arg)
        {
            pthread_detach(pthread_self());
            ThreadPool* tp = (ThreadPool*)arg;
            while(true)
            {
                pthrad_mutex_lock(&tp->que_lock_);
                while(tp->que_.empty())
                {   if(tp->is_quit_)
                    {
                        tp->thread_num_--;
                        pthread_mutex_unlock(&tp->que_lock_);
                        pthread_exit(NULL);
                    }
                    pthread_cond_wait(&tp->cons_cond_,&tp->que_lock_);
                }
                QueueType qt;
                tp->Pop(&qt);
                pthread_mutex_unlock(&tp->que_lock_);
                pthread_cond_signal(&tp->prod_cond_);
                qt.DealData();
            }
            return NULL;
        }
        void Push(QueueType& qt)
        {
            pthread_mutex_lock(&que_lock_);
            while(que_.size()>=capacity_)
            {
                pthread_cond_wait(&prod_cond_,&que_lock_);
            }
            que_.push(qt);
            pthread_mutex_unlock(&que_lock_);
            pthread_cond_signal(&cons_cond_);
        }
        void Pop(QueueType *qt)
        {
            *qt = que_.front();
            que_.pop();
        }
        void eixtThreadPool()
        {
            is_quit_ = true;
            while(thread_num_)
            {
                pthread_cond_signal(&cons_cond_);
            }
        }

    private:
        queue<QueueType> que_;
        size_t capacity_;
        pthread_mutex_t que_lock_;
        pthread_cond_t cons_cond_;
        pthread_cond_t prod_cond_;
        pthread_t tid_[THREAD_NUM];
        int thread_num_;
        bool is_quit_;
};
int main()
{
    /////////////////////////////////////////////////////////////
}
