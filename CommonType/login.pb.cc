// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: login.proto

#include "login.pb.h"

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
namespace login {
constexpr LoginRequest::LoginRequest(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : account_id_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct LoginRequestDefaultTypeInternal {
  constexpr LoginRequestDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~LoginRequestDefaultTypeInternal() {}
  union {
    LoginRequest _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT LoginRequestDefaultTypeInternal _LoginRequest_default_instance_;
constexpr LoginResponse::LoginResponse(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : result_(0){}
struct LoginResponseDefaultTypeInternal {
  constexpr LoginResponseDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~LoginResponseDefaultTypeInternal() {}
  union {
    LoginResponse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT LoginResponseDefaultTypeInternal _LoginResponse_default_instance_;
}  // namespace login
}  // namespace message
}  // namespace wzbgame
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_login_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_login_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_login_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_login_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::login::LoginRequest, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::login::LoginRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::login::LoginRequest, account_id_),
  0,
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::login::LoginResponse, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::login::LoginResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::wzbgame::message::login::LoginResponse, result_),
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 6, sizeof(::wzbgame::message::login::LoginRequest)},
  { 7, 13, sizeof(::wzbgame::message::login::LoginResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wzbgame::message::login::_LoginRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::wzbgame::message::login::_LoginResponse_default_instance_),
};

const char descriptor_table_protodef_login_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013login.proto\022\025wzbgame.message.login\"6\n\014"
  "LoginRequest\022\027\n\naccount_id\030\001 \001(\014H\000\210\001\001B\r\n"
  "\013_account_id\"/\n\rLoginResponse\022\023\n\006Result\030"
  "\001 \001(\005H\000\210\001\001B\t\n\007_Resultb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_login_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_login_2eproto = {
  false, false, 149, descriptor_table_protodef_login_2eproto, "login.proto", 
  &descriptor_table_login_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_login_2eproto::offsets,
  file_level_metadata_login_2eproto, file_level_enum_descriptors_login_2eproto, file_level_service_descriptors_login_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_login_2eproto_getter() {
  return &descriptor_table_login_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_login_2eproto(&descriptor_table_login_2eproto);
namespace wzbgame {
namespace message {
namespace login {

// ===================================================================

class LoginRequest::_Internal {
 public:
  using HasBits = decltype(std::declval<LoginRequest>()._has_bits_);
  static void set_has_account_id(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

LoginRequest::LoginRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wzbgame.message.login.LoginRequest)
}
LoginRequest::LoginRequest(const LoginRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  account_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_account_id()) {
    account_id_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_account_id(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:wzbgame.message.login.LoginRequest)
}

inline void LoginRequest::SharedCtor() {
account_id_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

LoginRequest::~LoginRequest() {
  // @@protoc_insertion_point(destructor:wzbgame.message.login.LoginRequest)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void LoginRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  account_id_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void LoginRequest::ArenaDtor(void* object) {
  LoginRequest* _this = reinterpret_cast< LoginRequest* >(object);
  (void)_this;
}
void LoginRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void LoginRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void LoginRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:wzbgame.message.login.LoginRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    account_id_.ClearNonDefaultToEmpty();
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* LoginRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional bytes account_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_account_id();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
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

::PROTOBUF_NAMESPACE_ID::uint8* LoginRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wzbgame.message.login.LoginRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional bytes account_id = 1;
  if (_internal_has_account_id()) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_account_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wzbgame.message.login.LoginRequest)
  return target;
}

size_t LoginRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wzbgame.message.login.LoginRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional bytes account_id = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_account_id());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData LoginRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    LoginRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*LoginRequest::GetClassData() const { return &_class_data_; }

void LoginRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<LoginRequest *>(to)->MergeFrom(
      static_cast<const LoginRequest &>(from));
}


void LoginRequest::MergeFrom(const LoginRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wzbgame.message.login.LoginRequest)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_account_id()) {
    _internal_set_account_id(from._internal_account_id());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void LoginRequest::CopyFrom(const LoginRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wzbgame.message.login.LoginRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LoginRequest::IsInitialized() const {
  return true;
}

void LoginRequest::InternalSwap(LoginRequest* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &account_id_, GetArenaForAllocation(),
      &other->account_id_, other->GetArenaForAllocation()
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata LoginRequest::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_login_2eproto_getter, &descriptor_table_login_2eproto_once,
      file_level_metadata_login_2eproto[0]);
}

// ===================================================================

class LoginResponse::_Internal {
 public:
  using HasBits = decltype(std::declval<LoginResponse>()._has_bits_);
  static void set_has_result(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

LoginResponse::LoginResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:wzbgame.message.login.LoginResponse)
}
LoginResponse::LoginResponse(const LoginResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  result_ = from.result_;
  // @@protoc_insertion_point(copy_constructor:wzbgame.message.login.LoginResponse)
}

inline void LoginResponse::SharedCtor() {
result_ = 0;
}

LoginResponse::~LoginResponse() {
  // @@protoc_insertion_point(destructor:wzbgame.message.login.LoginResponse)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void LoginResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void LoginResponse::ArenaDtor(void* object) {
  LoginResponse* _this = reinterpret_cast< LoginResponse* >(object);
  (void)_this;
}
void LoginResponse::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void LoginResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void LoginResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:wzbgame.message.login.LoginResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  result_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* LoginResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional int32 Result = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_result(&has_bits);
          result_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* LoginResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:wzbgame.message.login.LoginResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional int32 Result = 1;
  if (_internal_has_result()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_result(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:wzbgame.message.login.LoginResponse)
  return target;
}

size_t LoginResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:wzbgame.message.login.LoginResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional int32 Result = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_result());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData LoginResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    LoginResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*LoginResponse::GetClassData() const { return &_class_data_; }

void LoginResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<LoginResponse *>(to)->MergeFrom(
      static_cast<const LoginResponse &>(from));
}


void LoginResponse::MergeFrom(const LoginResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:wzbgame.message.login.LoginResponse)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_result()) {
    _internal_set_result(from._internal_result());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void LoginResponse::CopyFrom(const LoginResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:wzbgame.message.login.LoginResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LoginResponse::IsInitialized() const {
  return true;
}

void LoginResponse::InternalSwap(LoginResponse* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(result_, other->result_);
}

::PROTOBUF_NAMESPACE_ID::Metadata LoginResponse::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_login_2eproto_getter, &descriptor_table_login_2eproto_once,
      file_level_metadata_login_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace login
}  // namespace message
}  // namespace wzbgame
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::wzbgame::message::login::LoginRequest* Arena::CreateMaybeMessage< ::wzbgame::message::login::LoginRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wzbgame::message::login::LoginRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::wzbgame::message::login::LoginResponse* Arena::CreateMaybeMessage< ::wzbgame::message::login::LoginResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::wzbgame::message::login::LoginResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>