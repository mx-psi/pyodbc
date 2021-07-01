#ifndef _SQLTHREADING_H
#define _SQLTHREADING_H

#include "pyodbc.h"
#include <datetime.h>
#include <pthread.h>

int timePlusTimeout(long timeout, struct timespec* ts);
int threadFunc(void* (*f)(void*), long timeout, void* args);

struct SQLFreeStmtArgs
{
    HSTMT* hstmt;
    SQLUSMALLINT opt;
    SQLRETURN ret;
    bool reachedEnd;
};

struct SQLFreeHandleArgs
{
    SQLSMALLINT htype;
    HSTMT* hstmt;
    SQLRETURN ret;
    bool reachedEnd;
};

struct SQLExecuteArgs
{
    HSTMT* hstmt; 
    SQLRETURN ret;
    bool reachedEnd;
};

struct SQLExecDirectWArgs 
{
    HSTMT* hstmt;
    SQLWCHAR* pch;
    SQLINTEGER cch;
    SQLRETURN ret;
    bool reachedEnd;
};

struct SQLExecDirectArgs 
{
    HSTMT* hstmt;
    SQLCHAR* pch;
    SQLINTEGER cch;
    SQLRETURN ret;
    bool reachedEnd;
};

struct SQLFetchArgs
{
    HSTMT* hstmt;
    SQLRETURN ret;
    bool reachedEnd;
};

struct SQLEndTranArgs 
{
    SQLSMALLINT htype;
    HDBC handle;
    SQLSMALLINT completionType;
    SQLRETURN ret;
    bool reachedEnd;
};

void* sqlThreadSQLFreeStmt(void *arg);

void* sqlThreadSQLFreeHandle(void *arg);

void* sqlThreadSQLExecute(void *arg);

void* sqlThreadSQLExecDirectW(void *arg);

void* sqlThreadSQLExecDirect(void *arg);

void* sqlThreadSQLFetch(void *arg);

void* sqlThreadSQLEndTran(void *arg);

#endif // SQLTHREADING_H