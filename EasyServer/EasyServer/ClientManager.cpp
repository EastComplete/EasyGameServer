#include "stdafx.h"
#include "EasyServer.h"
#include "..\..\PacketType.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "DatabaseJobContext.h"
#include "DatabaseJobManager.h"

ClientManager* GClientManager = nullptr ;

ClientSession* ClientManager::CreateClient(SOCKET sock)
{
	ClientSession* client = new ClientSession(sock) ;
	mClientList.insert(ClientList::value_type(sock, client)) ;

	return client ;
}



void ClientManager::BroadcastPacket(ClientSession* from, PacketHeader* pkt)
{
	///FYI: C++ STL iterator ��Ÿ���� ����
	for (ClientList::const_iterator it=mClientList.begin() ; it!=mClientList.end() ; ++it)
	{
		ClientSession* client = it->second ;
		
		if ( from == client )
			continue ;
		
		client->Send(pkt) ;
	}
}

void ClientManager::OnPeriodWork()
{
	/// ������ ���� ���ǵ� �ֱ������� ���� (1�� ���� ���� ������)
	DWORD currTick = GetTickCount() ;
	if ( currTick - mLastGCTick >= 1000 )
	{
		CollectGarbageSessions() ;
		mLastGCTick = currTick ;
	}

	/// ���ӵ� Ŭ���̾�Ʈ ���Ǻ��� �ֱ������� ����� �ϴ� �� (�ֱ�� �˾Ƽ� ���ϸ� �� - ������ 1�ʷ� ����)
	if ( currTick - mLastClientWorkTick >= 1000 )
	{
		ClientPeriodWork() ;
		mLastClientWorkTick = currTick ;
	}

	/// ó�� �Ϸ�� DB �۾��� ������ Client�� dispatch
	DispatchDatabaseJobResults() ;
		
}

void ClientManager::CollectGarbageSessions()
{
	std::vector<ClientSession*> disconnectedSessions ;
	
	///FYI: C++ 11 ���ٸ� �̿��� ��Ÿ��
	std::for_each(mClientList.begin(), mClientList.end(),
		[&](ClientList::const_reference it)
		{
			ClientSession* client = it.second ;

			if ( false == client->IsConnected() && false == client->DoingOverlappedOperation() )
				disconnectedSessions.push_back(client) ;
		}
	) ;
	

	///FYI: C��� ��Ÿ���� ����
	for (size_t i=0 ; i<disconnectedSessions.size() ; ++i)
	{
		ClientSession* client = disconnectedSessions[i] ;
		mClientList.erase(client->mSocket) ;
		delete client ;
	}

}

void ClientManager::ClientPeriodWork()
{
	/// FYI: C++ 11 ��Ÿ���� ����
	for (auto& it : mClientList)
	{
		ClientSession* client = it.second ;
		client->OnTick() ;
	}
}

void ClientManager::DispatchDatabaseJobResults()
{
	/// �׿� �ִ� DB �۾� ó�� ������� ������ Ŭ�󿡰� �ѱ��
	DatabaseJobContext* dbResult = nullptr ;
	while ( GDatabaseJobManager->PopDatabaseJobResult(dbResult) )
	{
		auto& it = mClientList.find(dbResult->mSockKey) ;

		if ( it != mClientList.end() && it->second->IsConnected() )
		{
			/// dispatch here....
			it->second->DatabaseJobDone(dbResult) ;
		}
	}
}