
#include	"CAF_Atom.h"


bool SendContentsMessage(caf::io::broker* broker, const caf::actor& dest,
	const wzbgame::message::WrappedMessage& message)
{
	switch (message.type())
	{
	case wzbgame::message::LoginRequest:
	{
		broker->send(dest, login_request_atom_v, message.message().SerializeAsString());
	}
	break;

	case wzbgame::message::ChatRequest:
	{
		broker->send(dest, chat_request_atom_v, message.message().SerializeAsString());
	}
	break;

	case wzbgame::message::CharacterCreateRequest:
	{
		broker->send(dest, character_create_request_atom_v, message.message().SerializeAsString());
	}
	break;

	case wzbgame::message::CharacterDeleteRequest:
	{
		broker->send(dest, character_delete_request_atom_v, message.message().SerializeAsString());
	}
	break;

	case wzbgame::message::CharacterSelectRequest:
	{
		broker->send(dest, character_select_request_atom_v, message.message().SerializeAsString());
	}
	break;

	//case wzbgame::message::UnknownMessageType:
	default:
		return false;
	}

	return true;
}
