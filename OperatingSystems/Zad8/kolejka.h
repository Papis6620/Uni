#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_Q "/serwer_q"
#define MSG_LENGTH 50

mqd_t q_create(const char *name, struct mq_attr *newattr);
mqd_t q_open(const char *name, int oflag);
void q_close(mqd_t q_desk);
void q_del(const char *name);
void q_atr_get(mqd_t q_desk, struct mq_attr *attr);
void q_atr_set(mqd_t q_desk, struct mq_attr *newattr, struct mq_attr *oldattr);
void q_send(mqd_t q_desk, const char *msg, int buffer, int order);
void q_receive(mqd_t q_desk, char *buffer, int buffer_size);

