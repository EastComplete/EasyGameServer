#include "stdafx.h"
#include "EasyServer.h"
#include "DatabaseJobManager.h"

DatabaseJobManager* GDatabaseJobManager = nullptr ;


bool DatabaseJobManager::Initialize()
{
	//TODO: DB �����ϰ� �ʱ�ȭ ���

	return true ;
}

void DatabaseJobManager::Finalize()
{
	//TODO: DB ���� ���� �ڿ����� ���
}


/// �Ʒ� �Լ��� DB ó�� �����忡�� �ҷ��� �Ѵ�
bool DatabaseJobManager::ExecuteDatabaseJobs()
{
	assert( LThreadType == THREAD_DATABASE ) ;

	/// Request�� �ִ��� ó���� �ϰ� ����

	DatabaseJobRequest requestJob ;
	while ( mDbJobRequestQueue.PopFront(requestJob) )
	{
		/// ���⼭ DBȣ���ؼ� ó���ϰ� 


		/// �� ����� result queue�� ��� ����
		DatabaseJobResult result ;
		result.mSockKey = requestJob.mSockKey ;

		//TODO ... ...

		result.mSuccess = true ;
		mDbJobResultQueue.PushBack(result) ;
	}
	
	
	return true ;
}

/// �Ʒ� �Լ��� Ŭ���̾�Ʈ ó�� �����忡�� �ҷ��� �Ѵ�
bool DatabaseJobManager::PushDatabaseJobRequest(const DatabaseJobRequest& request)
{
	assert( LThreadType == THREAD_CLIENT ) ;
	return mDbJobRequestQueue.PushBack(request) ;
}

/// �Ʒ� �Լ��� Ŭ���̾�Ʈ ó�� �����忡�� �ҷ��� �Ѵ�
bool DatabaseJobManager::PopDatabaseJobResult(DatabaseJobResult& result)
{
	assert( LThreadType == THREAD_CLIENT ) ;
	return mDbJobResultQueue.PopFront(result) ;
}