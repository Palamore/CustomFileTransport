// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtocolTag.proto

#include "ProtocolTag.pb.h"

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
namespace PacketTag {
constexpr Chat_Normal::Chat_Normal(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : message_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , type_(0)
{}
struct Chat_NormalDefaultTypeInternal {
  constexpr Chat_NormalDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~Chat_NormalDefaultTypeInternal() {}
  union {
    Chat_Normal _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT Chat_NormalDefaultTypeInternal _Chat_Normal_default_instance_;
constexpr Chat_Whisper::Chat_Whisper(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : targetnickname_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , message_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , type_(0)
{}
struct Chat_WhisperDefaultTypeInternal {
  constexpr Chat_WhisperDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~Chat_WhisperDefaultTypeInternal() {}
  union {
    Chat_Whisper _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT Chat_WhisperDefaultTypeInternal _Chat_Whisper_default_instance_;
constexpr Room_User_List::Room_User_List(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : type_(0)
{}
struct Room_User_ListDefaultTypeInternal {
  constexpr Room_User_ListDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~Room_User_ListDefaultTypeInternal() {}
  union {
    Room_User_List _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT Room_User_ListDefaultTypeInternal _Room_User_List_default_instance_;
constexpr Exit_Request::Exit_Request(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : type_(0)
{}
struct Exit_RequestDefaultTypeInternal {
  constexpr Exit_RequestDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~Exit_RequestDefaultTypeInternal() {}
  union {
    Exit_Request _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT Exit_RequestDefaultTypeInternal _Exit_Request_default_instance_;
}  // namespace PacketTag
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ProtocolTag_2eproto[4];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_ProtocolTag_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ProtocolTag_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ProtocolTag_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Chat_Normal, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Chat_Normal, type_),
  PROTOBUF_FIELD_OFFSET(::PacketTag::Chat_Normal, message_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Chat_Whisper, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Chat_Whisper, type_),
  PROTOBUF_FIELD_OFFSET(::PacketTag::Chat_Whisper, targetnickname_),
  PROTOBUF_FIELD_OFFSET(::PacketTag::Chat_Whisper, message_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Room_User_List, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Room_User_List, type_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Exit_Request, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::PacketTag::Exit_Request, type_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::PacketTag::Chat_Normal)},
  { 8, -1, -1, sizeof(::PacketTag::Chat_Whisper)},
  { 17, -1, -1, sizeof(::PacketTag::Room_User_List)},
  { 24, -1, -1, sizeof(::PacketTag::Exit_Request)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::PacketTag::_Chat_Normal_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::PacketTag::_Chat_Whisper_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::PacketTag::_Room_User_List_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::PacketTag::_Exit_Request_default_instance_),
};

const char descriptor_table_protodef_ProtocolTag_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021ProtocolTag.proto\022\tPacketTag\"C\n\013Chat_N"
  "ormal\022#\n\004type\030\001 \001(\0162\025.PacketTag.PacketTy"
  "pe\022\017\n\007message\030\002 \001(\t\"\\\n\014Chat_Whisper\022#\n\004t"
  "ype\030\001 \001(\0162\025.PacketTag.PacketType\022\026\n\016targ"
  "etNickname\030\002 \001(\t\022\017\n\007message\030\003 \001(\t\"5\n\016Roo"
  "m_User_List\022#\n\004type\030\001 \001(\0162\025.PacketTag.Pa"
  "cketType\"3\n\014Exit_Request\022#\n\004type\030\001 \001(\0162\025"
  ".PacketTag.PacketType*U\n\nPacketType\022\017\n\013C"
  "HAT_NORMAL\020\000\022\020\n\014CHAT_WHISPER\020\001\022\022\n\016ROOM_U"
  "SER_LIST\020\002\022\020\n\014EXIT_REQUEST\020\003b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ProtocolTag_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ProtocolTag_2eproto = {
  false, false, 396, descriptor_table_protodef_ProtocolTag_2eproto, "ProtocolTag.proto", 
  &descriptor_table_ProtocolTag_2eproto_once, nullptr, 0, 4,
  schemas, file_default_instances, TableStruct_ProtocolTag_2eproto::offsets,
  file_level_metadata_ProtocolTag_2eproto, file_level_enum_descriptors_ProtocolTag_2eproto, file_level_service_descriptors_ProtocolTag_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_ProtocolTag_2eproto_getter() {
  return &descriptor_table_ProtocolTag_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_ProtocolTag_2eproto(&descriptor_table_ProtocolTag_2eproto);
namespace PacketTag {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PacketType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_ProtocolTag_2eproto);
  return file_level_enum_descriptors_ProtocolTag_2eproto[0];
}
bool PacketType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class Chat_Normal::_Internal {
 public:
};

Chat_Normal::Chat_Normal(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:PacketTag.Chat_Normal)
}
Chat_Normal::Chat_Normal(const Chat_Normal& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_message().empty()) {
    message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_message(), 
      GetArenaForAllocation());
  }
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:PacketTag.Chat_Normal)
}

void Chat_Normal::SharedCtor() {
message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
type_ = 0;
}

Chat_Normal::~Chat_Normal() {
  // @@protoc_insertion_point(destructor:PacketTag.Chat_Normal)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Chat_Normal::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  message_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Chat_Normal::ArenaDtor(void* object) {
  Chat_Normal* _this = reinterpret_cast< Chat_Normal* >(object);
  (void)_this;
}
void Chat_Normal::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Chat_Normal::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Chat_Normal::Clear() {
// @@protoc_insertion_point(message_clear_start:PacketTag.Chat_Normal)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  message_.ClearToEmpty();
  type_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Chat_Normal::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .PacketTag.PacketType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::PacketTag::PacketType>(val));
        } else
          goto handle_unusual;
        continue;
      // string message = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_message();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "PacketTag.Chat_Normal.message"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Chat_Normal::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PacketTag.Chat_Normal)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  // string message = 2;
  if (!this->_internal_message().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_message().data(), static_cast<int>(this->_internal_message().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "PacketTag.Chat_Normal.message");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_message(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PacketTag.Chat_Normal)
  return target;
}

size_t Chat_Normal::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PacketTag.Chat_Normal)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string message = 2;
  if (!this->_internal_message().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_message());
  }

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Chat_Normal::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Chat_Normal::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Chat_Normal::GetClassData() const { return &_class_data_; }

void Chat_Normal::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Chat_Normal *>(to)->MergeFrom(
      static_cast<const Chat_Normal &>(from));
}


void Chat_Normal::MergeFrom(const Chat_Normal& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PacketTag.Chat_Normal)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_message().empty()) {
    _internal_set_message(from._internal_message());
  }
  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Chat_Normal::CopyFrom(const Chat_Normal& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PacketTag.Chat_Normal)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Chat_Normal::IsInitialized() const {
  return true;
}

void Chat_Normal::InternalSwap(Chat_Normal* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &message_, lhs_arena,
      &other->message_, rhs_arena
  );
  swap(type_, other->type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Chat_Normal::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ProtocolTag_2eproto_getter, &descriptor_table_ProtocolTag_2eproto_once,
      file_level_metadata_ProtocolTag_2eproto[0]);
}

// ===================================================================

class Chat_Whisper::_Internal {
 public:
};

Chat_Whisper::Chat_Whisper(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:PacketTag.Chat_Whisper)
}
Chat_Whisper::Chat_Whisper(const Chat_Whisper& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  targetnickname_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_targetnickname().empty()) {
    targetnickname_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_targetnickname(), 
      GetArenaForAllocation());
  }
  message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_message().empty()) {
    message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_message(), 
      GetArenaForAllocation());
  }
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:PacketTag.Chat_Whisper)
}

void Chat_Whisper::SharedCtor() {
targetnickname_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
type_ = 0;
}

Chat_Whisper::~Chat_Whisper() {
  // @@protoc_insertion_point(destructor:PacketTag.Chat_Whisper)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Chat_Whisper::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  targetnickname_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  message_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Chat_Whisper::ArenaDtor(void* object) {
  Chat_Whisper* _this = reinterpret_cast< Chat_Whisper* >(object);
  (void)_this;
}
void Chat_Whisper::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Chat_Whisper::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Chat_Whisper::Clear() {
// @@protoc_insertion_point(message_clear_start:PacketTag.Chat_Whisper)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  targetnickname_.ClearToEmpty();
  message_.ClearToEmpty();
  type_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Chat_Whisper::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .PacketTag.PacketType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::PacketTag::PacketType>(val));
        } else
          goto handle_unusual;
        continue;
      // string targetNickname = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_targetnickname();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "PacketTag.Chat_Whisper.targetNickname"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string message = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_message();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "PacketTag.Chat_Whisper.message"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Chat_Whisper::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PacketTag.Chat_Whisper)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  // string targetNickname = 2;
  if (!this->_internal_targetnickname().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_targetnickname().data(), static_cast<int>(this->_internal_targetnickname().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "PacketTag.Chat_Whisper.targetNickname");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_targetnickname(), target);
  }

  // string message = 3;
  if (!this->_internal_message().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_message().data(), static_cast<int>(this->_internal_message().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "PacketTag.Chat_Whisper.message");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_message(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PacketTag.Chat_Whisper)
  return target;
}

size_t Chat_Whisper::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PacketTag.Chat_Whisper)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string targetNickname = 2;
  if (!this->_internal_targetnickname().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_targetnickname());
  }

  // string message = 3;
  if (!this->_internal_message().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_message());
  }

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Chat_Whisper::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Chat_Whisper::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Chat_Whisper::GetClassData() const { return &_class_data_; }

void Chat_Whisper::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Chat_Whisper *>(to)->MergeFrom(
      static_cast<const Chat_Whisper &>(from));
}


void Chat_Whisper::MergeFrom(const Chat_Whisper& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PacketTag.Chat_Whisper)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_targetnickname().empty()) {
    _internal_set_targetnickname(from._internal_targetnickname());
  }
  if (!from._internal_message().empty()) {
    _internal_set_message(from._internal_message());
  }
  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Chat_Whisper::CopyFrom(const Chat_Whisper& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PacketTag.Chat_Whisper)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Chat_Whisper::IsInitialized() const {
  return true;
}

void Chat_Whisper::InternalSwap(Chat_Whisper* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &targetnickname_, lhs_arena,
      &other->targetnickname_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &message_, lhs_arena,
      &other->message_, rhs_arena
  );
  swap(type_, other->type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Chat_Whisper::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ProtocolTag_2eproto_getter, &descriptor_table_ProtocolTag_2eproto_once,
      file_level_metadata_ProtocolTag_2eproto[1]);
}

// ===================================================================

class Room_User_List::_Internal {
 public:
};

Room_User_List::Room_User_List(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:PacketTag.Room_User_List)
}
Room_User_List::Room_User_List(const Room_User_List& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:PacketTag.Room_User_List)
}

void Room_User_List::SharedCtor() {
type_ = 0;
}

Room_User_List::~Room_User_List() {
  // @@protoc_insertion_point(destructor:PacketTag.Room_User_List)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Room_User_List::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Room_User_List::ArenaDtor(void* object) {
  Room_User_List* _this = reinterpret_cast< Room_User_List* >(object);
  (void)_this;
}
void Room_User_List::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Room_User_List::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Room_User_List::Clear() {
// @@protoc_insertion_point(message_clear_start:PacketTag.Room_User_List)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  type_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Room_User_List::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .PacketTag.PacketType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::PacketTag::PacketType>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Room_User_List::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PacketTag.Room_User_List)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PacketTag.Room_User_List)
  return target;
}

size_t Room_User_List::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PacketTag.Room_User_List)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Room_User_List::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Room_User_List::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Room_User_List::GetClassData() const { return &_class_data_; }

void Room_User_List::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Room_User_List *>(to)->MergeFrom(
      static_cast<const Room_User_List &>(from));
}


void Room_User_List::MergeFrom(const Room_User_List& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PacketTag.Room_User_List)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Room_User_List::CopyFrom(const Room_User_List& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PacketTag.Room_User_List)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Room_User_List::IsInitialized() const {
  return true;
}

void Room_User_List::InternalSwap(Room_User_List* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(type_, other->type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Room_User_List::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ProtocolTag_2eproto_getter, &descriptor_table_ProtocolTag_2eproto_once,
      file_level_metadata_ProtocolTag_2eproto[2]);
}

// ===================================================================

class Exit_Request::_Internal {
 public:
};

Exit_Request::Exit_Request(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:PacketTag.Exit_Request)
}
Exit_Request::Exit_Request(const Exit_Request& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:PacketTag.Exit_Request)
}

void Exit_Request::SharedCtor() {
type_ = 0;
}

Exit_Request::~Exit_Request() {
  // @@protoc_insertion_point(destructor:PacketTag.Exit_Request)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Exit_Request::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Exit_Request::ArenaDtor(void* object) {
  Exit_Request* _this = reinterpret_cast< Exit_Request* >(object);
  (void)_this;
}
void Exit_Request::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Exit_Request::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Exit_Request::Clear() {
// @@protoc_insertion_point(message_clear_start:PacketTag.Exit_Request)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  type_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Exit_Request::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .PacketTag.PacketType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::PacketTag::PacketType>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Exit_Request::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:PacketTag.Exit_Request)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PacketTag.Exit_Request)
  return target;
}

size_t Exit_Request::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PacketTag.Exit_Request)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .PacketTag.PacketType type = 1;
  if (this->_internal_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Exit_Request::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Exit_Request::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Exit_Request::GetClassData() const { return &_class_data_; }

void Exit_Request::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Exit_Request *>(to)->MergeFrom(
      static_cast<const Exit_Request &>(from));
}


void Exit_Request::MergeFrom(const Exit_Request& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PacketTag.Exit_Request)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_type() != 0) {
    _internal_set_type(from._internal_type());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Exit_Request::CopyFrom(const Exit_Request& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PacketTag.Exit_Request)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Exit_Request::IsInitialized() const {
  return true;
}

void Exit_Request::InternalSwap(Exit_Request* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(type_, other->type_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Exit_Request::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ProtocolTag_2eproto_getter, &descriptor_table_ProtocolTag_2eproto_once,
      file_level_metadata_ProtocolTag_2eproto[3]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace PacketTag
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::PacketTag::Chat_Normal* Arena::CreateMaybeMessage< ::PacketTag::Chat_Normal >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PacketTag::Chat_Normal >(arena);
}
template<> PROTOBUF_NOINLINE ::PacketTag::Chat_Whisper* Arena::CreateMaybeMessage< ::PacketTag::Chat_Whisper >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PacketTag::Chat_Whisper >(arena);
}
template<> PROTOBUF_NOINLINE ::PacketTag::Room_User_List* Arena::CreateMaybeMessage< ::PacketTag::Room_User_List >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PacketTag::Room_User_List >(arena);
}
template<> PROTOBUF_NOINLINE ::PacketTag::Exit_Request* Arena::CreateMaybeMessage< ::PacketTag::Exit_Request >(Arena* arena) {
  return Arena::CreateMessageInternal< ::PacketTag::Exit_Request >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>