// UEFIVar.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <Windows.h>

static bool SetPrivilege( LPCTSTR privilegeName )
{
	bool retVal = false;
	HANDLE token = 0;
	TOKEN_PRIVILEGES tokenPrivileges;

	if ( 0 == OpenProcessToken( GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY), &token ) )
	{
		printf("OpenProcessToken() fail(0x%X).\n", GetLastError() );
		retVal = false;
	}
	else
	{
		memset( &tokenPrivileges, 0, sizeof(TOKEN_PRIVILEGES) );
		if ( 0 == LookupPrivilegeValue( NULL, privilegeName,
										&(tokenPrivileges.Privileges[0].Luid) ) )
		{
			printf("LookupPrivilegeValue() fail(0x%X).\n", GetLastError() );
			retVal = false;
		}
		else
		{
			tokenPrivileges.PrivilegeCount = 1;
			tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			if ( 0 == AdjustTokenPrivileges( token, FALSE, &tokenPrivileges,
											  sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, NULL ) )
			{
				printf("AdjustTokenPrivileges() fail(0x%X).\n", GetLastError() );
				retVal = false;
			}
			else
			{
				retVal = true;
			}
		}
	}

	if ( token )
	{
		CloseHandle( token );
	}

	return retVal;
}


#define EFIVAR_GLOBAL_GUID_STR		L"{8BE4DF61-93CA-11d2-AA0D-00E098032B8C}"
#define EFIVAR_GLOBAL_VAR_NAME		L"Timeout"
#define EFIVAR_GLOBAL_VAR_LEN		(2)

static void LoadGlobalEFIVar( void )
{
	char value[EFIVAR_GLOBAL_VAR_LEN];
	int i = 0;

	memset( value, 0, sizeof(char) * EFIVAR_GLOBAL_VAR_LEN );

	if ( 0 == GetFirmwareEnvironmentVariable( EFIVAR_GLOBAL_VAR_NAME, EFIVAR_GLOBAL_GUID_STR, value, EFIVAR_GLOBAL_VAR_LEN ) )
	{
		printf("GetFirmwareEnvironmentVariable(%ls) fail(0x%X).\n", EFIVAR_GLOBAL_VAR_NAME, GetLastError() );
	}
	else
	{
		printf("%ls value: ", EFIVAR_GLOBAL_VAR_NAME );
		for ( i = 0; i < EFIVAR_GLOBAL_VAR_LEN; i++ )
		{
			printf("%c (0x%X) ", value[i], value[i] );
		}
		printf("\n");
	}

	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("UEFI Variable Test\n");
	
	if ( true == SetPrivilege( SE_SYSTEM_ENVIRONMENT_NAME ) )
	{
		LoadGlobalEFIVar();
	}
	else
	{
		printf("SetPrivilege() fail.\n");
	}

	return 0;
}

