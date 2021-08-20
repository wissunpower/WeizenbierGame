#pragma once


#include	<stdexcept>

#include	"../../pch.h"


struct DECLSPEC WzbException : public std::runtime_error
{
	// resultCode�� wzbgame::type::result::ResultType ���Ǹ� ����. �������� �����ϱ� ���� int �� ��ü.
	// �⺻���� UnknownFailure(1)
	WzbException(const char* whereFile, const int whereLine, const int resultCode = 1, const std::string& message = "WzbException");

	const int ResultCode;
};


#define	WZB_EXCEPTION							WzbException(__FILE__, __LINE__)
#define	WZB_EXCEPTION_R( RESULT )				WzbException(__FILE__, __LINE__, (RESULT))
#define	WZB_EXCEPTION_RM( RESULT, MESSAGE )		WzbException(__FILE__, __LINE__, (RESULT), (MESSAGE))
