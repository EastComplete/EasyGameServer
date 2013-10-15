#include "stdafx.h"
#include "EasyServer.h"
#include "DatabaseJobManager.h"
#include "SQLStatement.h"
#include "DbHelper.h"

DatabaseJobManager* GDatabaseJobManager = nullptr ;



/// �Ʒ� �Լ��� DB ó�� �����忡�� �ҷ��� �Ѵ�
bool DatabaseJobManager::ExecuteDatabaseJobs()
{
	assert( LThreadType == THREAD_DATABASE ) ;

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

	/* TEST

	static int testid = 1000 ;
	char testbuf[16] ; 
	sprintf_s(testbuf, "player%d", testid) ;
	DbHelper dbhelper(SQL_InsertTest) ;
	dbhelper.BindParamInt(testid) ;
	dbhelper.BindParamText(testbuf, strlen(testbuf)) ;
	dbhelper.BindParamDouble(rand()) ;
	dbhelper.BindParamDouble(rand()) ;
	dbhelper.BindParamDouble(rand()) ;
	dbhelper.BindParamText(testbuf, strlen(testbuf)) ;

	dbhelper.FetchRow() ;

	testid++ ;
	
	*/

	/*
	static int testid = 1000 ;

	DbHelper dbhelper(SQL_SelectTest) ;
	dbhelper.BindParamInt(testid) ;

	while ( RESULT_ROW == dbhelper.FetchRow() )
	{
		const unsigned char* name = dbhelper.GetResultParamText() ;
		double x = dbhelper.GetResultParamDouble() ;
		double y = dbhelper.GetResultParamDouble() ;
		double z = dbhelper.GetResultParamDouble() ;

		printf("ROW: %s, %f, %f, %f \n", name, x, y, z) ;
	}

	testid++ ;
	

	

	char testbuf[20] ; 
	sprintf_s(testbuf, "abc_comment_TEST") ;

	DbHelper dbh2(SQL_UpdateTest) ;
	dbh2.BindParamText(testbuf, strlen(testbuf)) ;
	dbh2.BindParamInt(1238) ;
	if ( RESULT_DONE != dbh2.FetchRow() )
	{
		printf("error.........\n") ;
	}
	*/

	/*
	DbHelper dbh3(SQL_DeleteTest) ;
	dbh3.BindParamInt(1237) ;
	dbh3.FetchRow() ;
	*/
	

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