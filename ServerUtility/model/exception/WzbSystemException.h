#pragma once


#include	"../../pch.h"

#include	"WzbException.h"


struct DECLSPEC WzbSystemException : public WzbException
{
	// resultCode�� wzbgame::type::result::ResultType ���Ǹ� ����. �������� �����ϱ� ���� int �� ��ü.
	// �⺻���� UnknownFailure(1)
	WzbSystemException(const char* whereFile, const int whereLine, const int resultCode = 1, const std::string& message = "WzbSystemException");
};


#define	WZB_SYSTEM_EXCEPTION							WzbSystemException(__FILE__, __LINE__)
#define	WZB_SYSTEM_EXCEPTION_R( RESULT )				WzbSystemException(__FILE__, __LINE__, (RESULT))
#define	WZB_SYSTEM_EXCEPTION_RM( RESULT, MESSAGE )		WzbSystemException(__FILE__, __LINE__, (RESULT), (MESSAGE))
