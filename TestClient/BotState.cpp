
#include    "caf/all.hpp"

CAF_PUSH_WARNINGS
#include    "WeizenbierProto.h"
CAF_POP_WARNINGS

#include	"BotState.h"
#include    "AtomDef.h"


std::string GetCharacterName()
{
    return std::string("botcharacter_") + std::to_string(rand());
}


template <typename MT>
wzbgame::message::WrappedMessage MakeWrappedMessage(wzbgame::message::MessageType type, MT data)
{
    wzbgame::message::WrappedMessage wrapped;
    wrapped.set_type(type);
    wrapped.mutable_message()->PackFrom(data);

    return wrapped;
}


BotState::BotState(caf::event_based_actor* self)
	: self(self)
{
}

BotState::~BotState()
{
}

caf::behavior BotState::make_behavior()
{
	return {
        [=](login_request_atom, std::string accountID)
    {
        caf::aout(self) << "Try Login -> Account ID : " << accountID << std::endl;

        wzbgame::message::login::LoginRequest p;
        p.set_account_id(accountID);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::LoginRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](login_response_atom, int result)
    {
        caf::aout(self) << "Login Result : " << result << std::endl;

        currentCharacterName = GetCharacterName();

        caf::aout(self) << "Try Character Create -> Character ID : " << currentCharacterName << std::endl;
        wzbgame::message::lobby::CharacterCreateRequest p;
        p.set_character_id(currentCharacterName);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterCreateRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](character_create_response_atom, int result)
    {
        caf::aout(self) << "Character Create Result : " << result << std::endl;

        caf::aout(self) << "Try Character Select -> Character ID : " << currentCharacterName << std::endl;

        wzbgame::message::lobby::CharacterSelectRequest p;
        p.set_character_id(currentCharacterName);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::CharacterSelectRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](character_select_response_atom, int result)
    {
        caf::aout(self) << "Character Select Result : " << result << std::endl;

        caf::aout(self) << "Try InGame Enter -> Character ID : " << currentCharacterName << std::endl;

        wzbgame::message::lobby::InGameEnterRequest p;
        p.set_character_id(currentCharacterName);
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::InGameEnterRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](ingame_enter_response_atom, int result, wzbgame::model::Position startingPosition)
    {
        caf::aout(self) << "InGame Enter Result : " << result << std::endl;
        caf::aout(self) << "Starting Position -> X : " << startingPosition.point_x() << ", Y : " << startingPosition.point_y() << ", Z : " << startingPosition.point_z() << std::endl;

        caf::aout(self) << "Try Play Character Move." << std::endl;

        wzbgame::message::battle::PositionMoveRequest p;
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::PositionMoveRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
        [=](position_move_response_atom, int result, wzbgame::model::Position startingPosition)
    {
        caf::aout(self) << "Position Move Result : " << result << std::endl;
        caf::aout(self) << "Current Position -> X : " << startingPosition.point_x() << ", Y : " << startingPosition.point_y() << ", Z : " << startingPosition.point_z() << std::endl;

        caf::aout(self) << "Try Play Character Move." << std::endl;

        wzbgame::message::battle::PositionMoveRequest p;
        auto wrapped = MakeWrappedMessage(wzbgame::message::MessageType::PositionMoveRequest, p);

        return caf::make_message(send_to_server_atom_v, wrapped.SerializeAsString());
    },
    };
}
