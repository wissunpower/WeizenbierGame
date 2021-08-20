#pragma once


#include	"../../pch.h"

#include	"WzbException.h"


struct DECLSPEC WzbContentsException : public WzbException
{
	// resultCode는 wzbgame::type::result::ResultType 정의를 따름. 의존성을 생략하기 위해 int 로 대체.
	// 기본값은 UnknownFailure(1)
	WzbContentsException(const char* whereFile, const int whereLine, const int resultCode = 1, const std::string& message = "WzbContentsException");
};


#define	WZB_CONTENTS_EXCEPTION							WzbContentsException(__FILE__, __LINE__)
#define	WZB_CONTENTS_EXCEPTION_R( RESULT )				WzbContentsException(__FILE__, __LINE__, (RESULT))
#define	WZB_CONTENTS_EXCEPTION_RM( RESULT, MESSAGE )	WzbContentsException(__FILE__, __LINE__, (RESULT), (MESSAGE))
