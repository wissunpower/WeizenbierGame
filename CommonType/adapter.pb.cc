// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: adapter.proto

#include "adapter.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace wzbgame {
namespace message {
constexpr WrappedMessage::WrappedMessage(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : message_(nullptr)
  , type_(0)
{}
struct WrappedMessageDefaultTypeInternal {
  constexpr WrappedMessageDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~WrappedMessageDefaultTypeInternal() {}
  union {
    WrappedMessage _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT WrappedMessageDefaultTypeInternal _WrappedMessage_default_instance_;
}  // namespace message
}  // namespace wzbgame
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_adapter_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_adapter_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_adapter_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_adapter_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::WrappedMessage, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::WrappedMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::WrappedMessage, type_),
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::WrappedMessage, message_),
  ~0u,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::wzbgame::message::WrappedMessage)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wzbgame::message::_WrappedMessage_default_instance_),
};

const char descriptor_table_protodef_adapter_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\radapter.proto\022\017wzbgame.message\032\031google"
  "/protobuf/any.proto\"t\n\016WrappedMessage\022*\n"
  "\004type\030\001 \001(\0162\034.wzbgame.message.MessageTyp"
  "e\022*\n\007message\030\002 \001(\0132\024.google.protobuf.Any"
  "H\000\210\001\001B\n\n\010_message*\203\001\n\013MessageType\022\026\n\022Unk"
  "nownMessageType\020\000\022\017\n\013ChatRequest\020\n\022\020\n\014Ch"
  "atResponse\020\013\022\024\n\020ChatNotification\020\014\022\020\n\014Lo"
  "ginRequest\020\024\022\021\n\rLoginResponse\020\025b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_adapter_2eproto_deps[1] = {
  &::descriptor_table_google_2fprotobuf_2fany_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_adapter_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_adapter_2eproto = {
  false, false, 319, descriptor_table_protodef_adapter_2eproto, "adapter.proto", 
  &descriptor_table_adapter_2eproto_once, descriptor_table_adapter_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_adapter_2eproto::offsets,
  file_level_metadata_adapter_2eproto, file_level_enum_descriptors_adapter_2eproto, file_level_service_descriptors_adapter_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_adapter_2eproto_getter() {
  return &descriptor_table_adapter_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_adapter_2eproto(&descriptor_table_adapter_2eproto);
namespace wzbgame {
namespace message {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MessageType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_adapter_2eproto);
  return file_level_enum_descriptors_adapter_2eproto[0];
}
bool MessageType_IsValid(int value) {
  switch (value) {
    case 0:
    case 10:
    case 11:
    case 12:
    case 20:
    case 21:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class WrappedMessage::_Internal {
 public:
  using HasBits = decltype(std::declval<WrappedMessage>()._has_bits_);
  static const PROTOBUF_NAMESPACE_ID::Any& message(const WrappedMessage* msg);
  static void set_has_message(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const PROTOBUF_NAMESPACE_ID::Any&
WrappedMessage::_Internal::message(const WrappedMessage* msg) {
  return *msg->message_;
}
void WrappedMessage::clear_message() {
  if (message_ != nullptr) message_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
WrappedMessage::WrappedMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wzbgame.message.WrappedMessage)
}
WrappedMessage::WrappedMessage(const WrappedMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_message()) {
    message_ = new PROTOBUF_NAMESPACE_ID::Any(*from.message_);
  } else {
    message_ = nullptr;
  }
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:wzbgame.message.WrappedMessage)
}

inline void WrappedMessage::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&message_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&type_) -
    reinterpret_cast<char*>(&message_)) + sizeof(type_));
}

WrappedMessage::~WrappedMessage() {
  // @@protoc_insertion_point(destructor:wzbgame.message.WrappedMessage)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void WrappedMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete message_;
}

void WrappedMessage::ArenaDtor(void* object) {
  WrappedMessage* _this = reinterpret_cast< WrappedMessage* >(object);
  (void)_this;
}
void WrappedMessage::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void WrappedMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void WrappedMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:wzbgame.message.WrappedMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(message_ != nullptr);
    message_->Clear();
  }
  type_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* WrappedMessage::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .wzbgame.message.MessageType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::wzbgame::message::MessageType>(val));
        } else goto handle_unusual;
        continue;
      // optional .google.protobuf.Any message = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_message(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* WrappedMessage::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wzbgame.message.WrappedMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .wzbgame.message.MessageType type = 1;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  // optional .google.protobuf.Any message = 2;
  if (_internal_has_message()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::message(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wzbgame.message.WrappedMessage)
  return target;
}

size_t WrappedMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wzbgame.message.WrappedMessage)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional .google.protobuf.Any message = 2;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *message_);
  }

  // .wzbgame.message.MessageType type = 1;
  if (this->_internal_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData WrappedMessage::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    WrappedMessage::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*WrappedMessage::GetClassData() const { return &_class_data_; }

void WrappedMessage::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<WrappedMessage *>(to)->MergeFrom(
      static_cast<const WrappedMessage &>(from));
}


void WrappedMessage::MergeFrom(const WrappedMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wzbgame.message.WrappedMessage)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_message()) {
    _internal_mutable_message()->PROTOBUF_NAMESPACE_ID::Any::MergeFrom(from._internal_message());
  }
  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void WrappedMessage::CopyFrom(const WrappedMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wzbgame.message.WrappedMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WrappedMessage::IsInitialized() const {
  return true;
}

void WrappedMessage::InternalSwap(WrappedMessage* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(WrappedMessage, type_)
      + sizeof(WrappedMessage::type_)
      - PROTOBUF_FIELD_OFFSET(WrappedMessage, message_)>(
          reinterpret_cast<char*>(&message_),
          reinterpret_cast<char*>(&other->message_));
}

::PROTOBUF_NAMESPACE_ID::Metadata WrappedMessage::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_adapter_2eproto_getter, &descriptor_table_adapter_2eproto_once,
      file_level_metadata_adapter_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace message
}  // namespace wzbgame
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wzbgame::message::WrappedMessage* Arena::CreateMaybeMessage< ::wzbgame::message::WrappedMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wzbgame::message::WrappedMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
