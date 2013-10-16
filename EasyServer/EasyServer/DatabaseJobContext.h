#pragma once

#include <WinSock2.h>
#include "Config.h"
#include "ObjectPool.h"


/// ��� DB���� �۾��� �Ʒ��� �߻� Ŭ������ ��ӹ޾� ����ؾ� ��
struct DatabaseJobContext
{
	DatabaseJobContext(SOCKET socketKey) :  mSockKey(socketKey), mSuccess(false) 
	{}
	virtual ~DatabaseJobContext() {}

	virtual bool OnExecute() = 0 ;

	void SetSuccess(bool success) { mSuccess = success ; }

	SOCKET	mSockKey ;
	bool	mSuccess ;
} ;


/// player load �۾�
struct LoadPlayerDataContext : public DatabaseJobContext, public ObjectPool<LoadPlayerDataContext>
{
	LoadPlayerDataContext(SOCKET socketKey, int playerId) : DatabaseJobContext(socketKey)
		, mPlayerId(playerId), mPosX(0), mPosY(0), mPosZ(0)
	{
		memset(mPlayerName, 0, sizeof(mPlayerName)) ;
	}


	virtual bool OnExecute() ;


	int		mPlayerId ;

	double	mPosX ;
	double	mPosY ;
	double	mPosZ ;
	char	mPlayerName[MAX_PLAYER_NAME_LEN] ;

} ;
