#pragma once


#include	"../pch.h"


template <typename MT>
void WriteProtobufMessage(caf::io::broker* self, caf::io::connection_handle hdl, wzbgame::message::MessageType type, MT data)
{
	wzbgame::message::WrappedMessage wm;
	wm.set_type(type);
	wm.mutable_message()->PackFrom(data);

	auto buf = wm.SerializeAsString();
	auto bufSize = htonl(static_cast<uint32_t>(buf.size()));
	self->write(hdl, sizeof(uint32_t), &bufSize);
	self->write(hdl, buf.size(), buf.data());
	self->flush(hdl);
}
