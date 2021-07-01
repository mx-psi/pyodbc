#include "pyodbc.h"
#include "sqlthreading.h"
#include <datetime.h>
#include <pthread.h>

int timePlusTimeout(long timeout, struct timespec* ts) {
    if (clock_gettime(CLOCK_REALTIME, ts) == -1) {
        return -1;
    }
    ts->tv_sec += timeout;
    return 0;
}

int threadFunc(void* (*f)(void*), long timeout, void* args) {
    pthread_t tid;
    pthread_create(&tid, nullptr, f, args);
    struct timespec ts;
    timePlusTimeout(timeout, &ts);
    int thread_ret = pthread_timedjoin_np(tid, nullptr, &ts);

    if(thread_ret == EINVAL) {
        int err = pthread_cancel(tid);
        if (err == ESRCH) {
            return 3;
        }
        return 2;
    } else if (thread_ret == ETIMEDOUT) {
        int err = pthread_cancel(tid);
        if (err == ESRCH) {
            return 3;
        }
        return 1;
    }
    return 0;
}

void* sqlThreadSQLFreeStmt(void *arg) {
    struct SQLFreeStmtArgs* sqlArgs = (struct SQLFreeStmtArgs *) arg;
    sqlArgs->reachedEnd = false;
    sqlArgs->ret = SQLFreeStmt(*(sqlArgs->hstmt), sqlArgs->opt);
    sqlArgs->reachedEnd = true;
    void* ret = (void *) sqlArgs->ret;
    return ret;
}


void* sqlThreadSQLFreeHandle(void *arg) {
    struct SQLFreeHandleArgs* sqlArgs = (struct SQLFreeHandleArgs *) arg;
    sqlArgs->reachedEnd = false;
    sqlArgs->ret = SQLFreeHandle(sqlArgs->htype, *(sqlArgs->hstmt));
    sqlArgs->reachedEnd = true;
    void* ret = (void *) sqlArgs->ret;
    return ret;
}

void* sqlThreadSQLExecute(void *arg) {
    struct SQLExecuteArgs* sqlArgs = (struct SQLExecuteArgs *) arg;
    sqlArgs->reachedEnd = false;
    sqlArgs->ret = SQLExecute(*(sqlArgs->hstmt));
    sqlArgs->reachedEnd = true;
    void* ret = (void *) sqlArgs->ret;
    return ret;
}

void* sqlThreadSQLExecDirectW(void *arg) {
    struct SQLExecDirectWArgs* sqlArgs = (struct SQLExecDirectWArgs *) arg;
    sqlArgs->reachedEnd = false;
    sqlArgs->ret = SQLExecDirectW(*(sqlArgs->hstmt), sqlArgs->pch, sqlArgs->cch);
    sqlArgs->reachedEnd = true;
    void* ret = (void *) sqlArgs->ret;
    return ret;
}

void* sqlThreadSQLExecDirect(void *arg) {
    struct SQLExecDirectArgs* sqlArgs = (struct SQLExecDirectArgs *) arg;
    sqlArgs->reachedEnd = false;
    sqlArgs->ret = SQLExecDirect(*(sqlArgs->hstmt), sqlArgs->pch, sqlArgs->cch);
    sqlArgs->reachedEnd = true;
    void* ret = (void *) sqlArgs->ret;
    return ret;
}

void* sqlThreadSQLFetch(void *arg) {
    struct SQLFetchArgs* sqlArgs = (struct SQLFetchArgs *) arg;
    sqlArgs->reachedEnd = false;
    sqlArgs->ret = SQLFetch(*(sqlArgs->hstmt));
    sqlArgs->reachedEnd = true;
    void* ret = (void *) sqlArgs->ret;
    return ret;
}

void* sqlThreadSQLEndTran(void *arg) {
    struct SQLEndTranArgs* sqlArgs = (struct SQLEndTranArgs *) arg;
    sqlArgs->reachedEnd = false;
    sqlArgs->ret = SQLEndTran(sqlArgs->htype, sqlArgs->handle, sqlArgs->completionType);
    sqlArgs->reachedEnd = true;
    void* ret = (void *) sqlArgs->ret;
    return ret;
}