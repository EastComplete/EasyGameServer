#pragma once

#include <WinSock2.h>
#include "SPSCQueue.h"

struct DatabaseJobRequest
{
	DatabaseJobRequest() : mSockKey(NULL) 
	{}

	SOCKET mSockKey ; ///< ��� Ŭ���̾�Ʈ���� ��û�ߴ��� Ȯ���ϴ� Ű�� ���
} ;

struct DatabaseJobResult
{
	DatabaseJobResult() : mSockKey(NULL), mSuccess(false) 
	{}

	SOCKET	mSockKey ;
	bool	mSuccess ;
} ;


class DatabaseJobManager
{
public:
	DatabaseJobManager() {}


	bool ExecuteDatabaseJobs() ;

	
	bool PushDatabaseJobRequest(const DatabaseJobRequest& request) ;
	bool PopDatabaseJobResult(DatabaseJobResult& result) ;

private:
	enum  
	{
		MAX_DB_JOB = 1023 
	} ;

	SPSCQueue<DatabaseJobRequest,MAX_DB_JOB>	mDbJobRequestQueue ;
	SPSCQueue<DatabaseJobResult,MAX_DB_JOB>		mDbJobResultQueue ;

	
} ;

extern DatabaseJobManager* GDatabaseJobManager ;