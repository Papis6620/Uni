#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "kolejka.h"

mqd_t q_create(const char *name, struct mq_attr *newattr){
    mqd_t q_desk = mq_open(name, O_CREAT | O_EXCL | O_RDWR, 0666, newattr);
    if(q_desk == -1){
        perror("mq_open error");
        exit(EXIT_FAILURE);
    }
    return q_desk;
}

mqd_t q_open(const char *name, int oflag){
    mqd_t q_desk = mq_open(name, oflag);
    if(q_desk == -1){
        perror("mq_open error");
        exit(EXIT_FAILURE);
    }
    return q_desk;
}

void q_close(mqd_t q_desk){
    if(mq_close(q_desk) == -1){
        perror("mq_close error");
        exit(EXIT_FAILURE);
    }
}

void q_del(const char *name){
    if(mq_unlink(name) == -1){
        perror("mq_unlink error");
        exit(EXIT_FAILURE);
    }
}

void q_atr_get(mqd_t q_desk, struct mq_attr *attr){
    if(mq_getattr(q_desk, attr) == -1){
        perror("mq_getattr error");
        exit(EXIT_FAILURE);
    }
}
void q_atr_set(mqd_t q_desk, struct mq_attr *newattr, struct mq_attr *oldattr){
    if(mq_setattr(q_desk, newattr, oldattr) == -1){
        perror("mq_setattr error");
        exit(EXIT_FAILURE);
    }
}

void q_send(mqd_t q_desk, const char *msg, int buffer, int order){
    if(mq_send(q_desk, msg, buffer, order) == -1){
        perror("mq_send error");
        exit(EXIT_FAILURE);
    }
}
void q_receive(mqd_t q_desk, char *buffer, int buffer_size){
    if(mq_receive(q_desk, buffer, buffer_size, NULL) == -1){
        perror("mq_receive error");
        exit(EXIT_FAILURE);
    }
}
