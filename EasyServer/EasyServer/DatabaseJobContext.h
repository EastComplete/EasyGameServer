#pragma once

#include <WinSock2.h>
#include "ObjectPool.h"


struct DatabaseJobRequest : public ObjectPool<DatabaseJobRequest>
{
	DatabaseJobRequest() : mSockKey(NULL) 
	{}

	SOCKET mSockKey ; ///< ��� Ŭ���̾�Ʈ���� ��û�ߴ��� Ȯ���ϴ� Ű�� ���
} ;

struct DatabaseJobResult : public ObjectPool<DatabaseJobResult>
{
	DatabaseJobResult() : mSockKey(NULL), mSuccess(false) 
	{}

	SOCKET	mSockKey ;
	bool	mSuccess ;
	
} ;
