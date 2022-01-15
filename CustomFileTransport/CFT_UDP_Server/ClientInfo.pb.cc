// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ClientInfo.proto

#include "ClientInfo.pb.h"

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
namespace ServerPacket {
constexpr ClientInfo::ClientInfo(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : nickname_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , socket_(0){}
struct ClientInfoDefaultTypeInternal {
  constexpr ClientInfoDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~ClientInfoDefaultTypeInternal() {}
  union {
    ClientInfo _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT ClientInfoDefaultTypeInternal _ClientInfo_default_instance_;
}  // namespace ServerPacket
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ClientInfo_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_ClientInfo_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ClientInfo_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ClientInfo_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ServerPacket::ClientInfo, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ServerPacket::ClientInfo, socket_),
  PROTOBUF_FIELD_OFFSET(::ServerPacket::ClientInfo, nickname_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::ServerPacket::ClientInfo)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ServerPacket::_ClientInfo_default_instance_),
};

const char descriptor_table_protodef_ClientInfo_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020ClientInfo.proto\022\014ServerPacket\".\n\nClie"
  "ntInfo\022\016\n\006Socket\030\001 \001(\005\022\020\n\010NickName\030\002 \001(\t"
  "b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ClientInfo_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ClientInfo_2eproto = {
  false, false, 88, descriptor_table_protodef_ClientInfo_2eproto, "ClientInfo.proto", 
  &descriptor_table_ClientInfo_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_ClientInfo_2eproto::offsets,
  file_level_metadata_ClientInfo_2eproto, file_level_enum_descriptors_ClientInfo_2eproto, file_level_service_descriptors_ClientInfo_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_ClientInfo_2eproto_getter() {
  return &descriptor_table_ClientInfo_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_ClientInfo_2eproto(&descriptor_table_ClientInfo_2eproto);
namespace ServerPacket {

// ===================================================================

class ClientInfo::_Internal {
 public:
};

ClientInfo::ClientInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:ServerPacket.ClientInfo)
}
ClientInfo::ClientInfo(const ClientInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  nickname_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_nickname().empty()) {
    nickname_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_nickname(), 
      GetArenaForAllocation());
  }
  socket_ = from.socket_;
  // @@protoc_insertion_point(copy_constructor:ServerPacket.ClientInfo)
}

void ClientInfo::SharedCtor() {
nickname_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
socket_ = 0;
}

ClientInfo::~ClientInfo() {
  // @@protoc_insertion_point(destructor:ServerPacket.ClientInfo)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void ClientInfo::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  nickname_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ClientInfo::ArenaDtor(void* object) {
  ClientInfo* _this = reinterpret_cast< ClientInfo* >(object);
  (void)_this;
}
void ClientInfo::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ClientInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ClientInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:ServerPacket.ClientInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  nickname_.ClearToEmpty();
  socket_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ClientInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 Socket = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          socket_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string NickName = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_nickname();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "ServerPacket.ClientInfo.NickName"));
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

::PROTOBUF_NAMESPACE_ID::uint8* ClientInfo::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServerPacket.ClientInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 Socket = 1;
  if (this->_internal_socket() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_socket(), target);
  }

  // string NickName = 2;
  if (!this->_internal_nickname().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_nickname().data(), static_cast<int>(this->_internal_nickname().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ServerPacket.ClientInfo.NickName");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_nickname(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServerPacket.ClientInfo)
  return target;
}

size_t ClientInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServerPacket.ClientInfo)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string NickName = 2;
  if (!this->_internal_nickname().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_nickname());
  }

  // int32 Socket = 1;
  if (this->_internal_socket() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_socket());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ClientInfo::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    ClientInfo::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ClientInfo::GetClassData() const { return &_class_data_; }

void ClientInfo::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<ClientInfo *>(to)->MergeFrom(
      static_cast<const ClientInfo &>(from));
}


void ClientInfo::MergeFrom(const ClientInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ServerPacket.ClientInfo)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_nickname().empty()) {
    _internal_set_nickname(from._internal_nickname());
  }
  if (from._internal_socket() != 0) {
    _internal_set_socket(from._internal_socket());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ClientInfo::CopyFrom(const ClientInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServerPacket.ClientInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClientInfo::IsInitialized() const {
  return true;
}

void ClientInfo::InternalSwap(ClientInfo* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &nickname_, lhs_arena,
      &other->nickname_, rhs_arena
  );
  swap(socket_, other->socket_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ClientInfo::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ClientInfo_2eproto_getter, &descriptor_table_ClientInfo_2eproto_once,
      file_level_metadata_ClientInfo_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace ServerPacket
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ServerPacket::ClientInfo* Arena::CreateMaybeMessage< ::ServerPacket::ClientInfo >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerPacket::ClientInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
