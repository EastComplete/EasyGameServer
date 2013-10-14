#pragma once

struct sqlite3 ;
struct sqlite3_stmt ;

class DbHelper
{
public:
	DbHelper(const char* sql) ;
	~DbHelper() ;

	static bool Initialize(const char* connInfoStr) ;
	static void Finalize() ;

	static bool Execute(const char* format, ...) ;
	
	/// �Ʒ��� DbHelper ��ü�� �����ϰ� ����ؾ� ��

	bool BindParamInt(int param) ;
	bool BindParamDouble(double param) ;
	bool BindParamText(const char* text, int count) ;

	bool FetchRow() ;

	/// FetchRow�� �����Ͱ� �ִٸ� �ݵ�� ���ʴ�� ȣ���ؾ���
	int GetResultParamInt() ;
	double GetResultParamDouble() ;
	const unsigned char* GetResultParamText() ;


private:

	static sqlite3* mSqlite ;

	static int		mDoingCount ; ///< ��ø ���� üũ��

	/// ���� �������� SQL���� ���� ����
	sqlite3_stmt*	mResult ;
	int				mResultColCount ;

	int				mBindColCount ;
	int				mResultCurrentCol ;

} ;