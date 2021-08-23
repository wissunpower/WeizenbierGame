// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: result.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_result_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_result_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_result_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_result_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_result_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace wzbgame {
namespace type {
namespace result {

enum ResultType : int {
  Succeed = 0,
  UnknownFailure = 1,
  AlreadyExistCharacter = 10000,
  NotFoundCharacter = 10001,
  InvalidCurrentCharacter = 10002,
  ResultType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ResultType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ResultType_IsValid(int value);
constexpr ResultType ResultType_MIN = Succeed;
constexpr ResultType ResultType_MAX = InvalidCurrentCharacter;
constexpr int ResultType_ARRAYSIZE = ResultType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ResultType_descriptor();
template<typename T>
inline const std::string& ResultType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ResultType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ResultType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ResultType_descriptor(), enum_t_value);
}
inline bool ResultType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ResultType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ResultType>(
    ResultType_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace result
}  // namespace type
}  // namespace wzbgame

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::wzbgame::type::result::ResultType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::wzbgame::type::result::ResultType>() {
  return ::wzbgame::type::result::ResultType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_result_2eproto
