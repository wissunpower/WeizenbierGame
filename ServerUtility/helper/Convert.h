#pragma once

#include	"../pch.h"


template <typename AT>
AT ToActorMessageArg(const std::string& stream)
{
	google::protobuf::Any am;
	am.ParseFromArray(stream.data(), static_cast<int>(stream.size()));

	AT message;
	am.UnpackTo(&message);

	return message;
}
