// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UDPFileSend.proto

#include "UDPFileSend.pb.h"

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
namespace UDP {
constexpr FileData::FileData(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , index_(0){}
struct FileDataDefaultTypeInternal {
  constexpr FileDataDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~FileDataDefaultTypeInternal() {}
  union {
    FileData _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT FileDataDefaultTypeInternal _FileData_default_instance_;
constexpr DataRcvAck::DataRcvAck(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : index_(0){}
struct DataRcvAckDefaultTypeInternal {
  constexpr DataRcvAckDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~DataRcvAckDefaultTypeInternal() {}
  union {
    DataRcvAck _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT DataRcvAckDefaultTypeInternal _DataRcvAck_default_instance_;
constexpr DataRcvDone::DataRcvDone(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct DataRcvDoneDefaultTypeInternal {
  constexpr DataRcvDoneDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~DataRcvDoneDefaultTypeInternal() {}
  union {
    DataRcvDone _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT DataRcvDoneDefaultTypeInternal _DataRcvDone_default_instance_;
}  // namespace UDP
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_UDPFileSend_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_UDPFileSend_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_UDPFileSend_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_UDPFileSend_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::UDP::FileData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::UDP::FileData, index_),
  PROTOBUF_FIELD_OFFSET(::UDP::FileData, data_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::UDP::DataRcvAck, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::UDP::DataRcvAck, index_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::UDP::DataRcvDone, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::UDP::DataRcvDone, data_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::UDP::FileData)},
  { 8, -1, -1, sizeof(::UDP::DataRcvAck)},
  { 15, -1, -1, sizeof(::UDP::DataRcvDone)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::UDP::_FileData_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::UDP::_DataRcvAck_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::UDP::_DataRcvDone_default_instance_),
};

const char descriptor_table_protodef_UDPFileSend_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021UDPFileSend.proto\022\003UDP\"\'\n\010FileData\022\r\n\005"
  "index\030\001 \001(\005\022\014\n\004data\030\002 \001(\t\"\033\n\nDataRcvAck\022"
  "\r\n\005index\030\001 \001(\005\"\033\n\013DataRcvDone\022\014\n\004data\030\001 "
  "\001(\tb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_UDPFileSend_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_UDPFileSend_2eproto = {
  false, false, 131, descriptor_table_protodef_UDPFileSend_2eproto, "UDPFileSend.proto", 
  &descriptor_table_UDPFileSend_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_UDPFileSend_2eproto::offsets,
  file_level_metadata_UDPFileSend_2eproto, file_level_enum_descriptors_UDPFileSend_2eproto, file_level_service_descriptors_UDPFileSend_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_UDPFileSend_2eproto_getter() {
  return &descriptor_table_UDPFileSend_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_UDPFileSend_2eproto(&descriptor_table_UDPFileSend_2eproto);
namespace UDP {

// ===================================================================

class FileData::_Internal {
 public:
};

FileData::FileData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:UDP.FileData)
}
FileData::FileData(const FileData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_data().empty()) {
    data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_data(), 
      GetArenaForAllocation());
  }
  index_ = from.index_;
  // @@protoc_insertion_point(copy_constructor:UDP.FileData)
}

void FileData::SharedCtor() {
data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
index_ = 0;
}

FileData::~FileData() {
  // @@protoc_insertion_point(destructor:UDP.FileData)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void FileData::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  data_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void FileData::ArenaDtor(void* object) {
  FileData* _this = reinterpret_cast< FileData* >(object);
  (void)_this;
}
void FileData::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void FileData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void FileData::Clear() {
// @@protoc_insertion_point(message_clear_start:UDP.FileData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmpty();
  index_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* FileData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 index = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string data = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_data();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "UDP.FileData.data"));
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

::PROTOBUF_NAMESPACE_ID::uint8* FileData::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:UDP.FileData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 index = 1;
  if (this->_internal_index() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_index(), target);
  }

  // string data = 2;
  if (!this->_internal_data().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data().data(), static_cast<int>(this->_internal_data().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "UDP.FileData.data");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_data(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:UDP.FileData)
  return target;
}

size_t FileData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:UDP.FileData)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string data = 2;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data());
  }

  // int32 index = 1;
  if (this->_internal_index() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_index());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData FileData::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    FileData::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*FileData::GetClassData() const { return &_class_data_; }

void FileData::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<FileData *>(to)->MergeFrom(
      static_cast<const FileData &>(from));
}


void FileData::MergeFrom(const FileData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:UDP.FileData)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_data().empty()) {
    _internal_set_data(from._internal_data());
  }
  if (from._internal_index() != 0) {
    _internal_set_index(from._internal_index());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void FileData::CopyFrom(const FileData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:UDP.FileData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FileData::IsInitialized() const {
  return true;
}

void FileData::InternalSwap(FileData* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &data_, lhs_arena,
      &other->data_, rhs_arena
  );
  swap(index_, other->index_);
}

::PROTOBUF_NAMESPACE_ID::Metadata FileData::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_UDPFileSend_2eproto_getter, &descriptor_table_UDPFileSend_2eproto_once,
      file_level_metadata_UDPFileSend_2eproto[0]);
}

// ===================================================================

class DataRcvAck::_Internal {
 public:
};

DataRcvAck::DataRcvAck(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:UDP.DataRcvAck)
}
DataRcvAck::DataRcvAck(const DataRcvAck& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  index_ = from.index_;
  // @@protoc_insertion_point(copy_constructor:UDP.DataRcvAck)
}

void DataRcvAck::SharedCtor() {
index_ = 0;
}

DataRcvAck::~DataRcvAck() {
  // @@protoc_insertion_point(destructor:UDP.DataRcvAck)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void DataRcvAck::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void DataRcvAck::ArenaDtor(void* object) {
  DataRcvAck* _this = reinterpret_cast< DataRcvAck* >(object);
  (void)_this;
}
void DataRcvAck::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void DataRcvAck::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void DataRcvAck::Clear() {
// @@protoc_insertion_point(message_clear_start:UDP.DataRcvAck)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  index_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* DataRcvAck::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 index = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* DataRcvAck::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:UDP.DataRcvAck)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 index = 1;
  if (this->_internal_index() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_index(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:UDP.DataRcvAck)
  return target;
}

size_t DataRcvAck::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:UDP.DataRcvAck)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 index = 1;
  if (this->_internal_index() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_index());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData DataRcvAck::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    DataRcvAck::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*DataRcvAck::GetClassData() const { return &_class_data_; }

void DataRcvAck::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<DataRcvAck *>(to)->MergeFrom(
      static_cast<const DataRcvAck &>(from));
}


void DataRcvAck::MergeFrom(const DataRcvAck& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:UDP.DataRcvAck)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_index() != 0) {
    _internal_set_index(from._internal_index());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void DataRcvAck::CopyFrom(const DataRcvAck& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:UDP.DataRcvAck)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DataRcvAck::IsInitialized() const {
  return true;
}

void DataRcvAck::InternalSwap(DataRcvAck* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(index_, other->index_);
}

::PROTOBUF_NAMESPACE_ID::Metadata DataRcvAck::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_UDPFileSend_2eproto_getter, &descriptor_table_UDPFileSend_2eproto_once,
      file_level_metadata_UDPFileSend_2eproto[1]);
}

// ===================================================================

class DataRcvDone::_Internal {
 public:
};

DataRcvDone::DataRcvDone(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:UDP.DataRcvDone)
}
DataRcvDone::DataRcvDone(const DataRcvDone& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_data().empty()) {
    data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_data(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:UDP.DataRcvDone)
}

void DataRcvDone::SharedCtor() {
data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

DataRcvDone::~DataRcvDone() {
  // @@protoc_insertion_point(destructor:UDP.DataRcvDone)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void DataRcvDone::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  data_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void DataRcvDone::ArenaDtor(void* object) {
  DataRcvDone* _this = reinterpret_cast< DataRcvDone* >(object);
  (void)_this;
}
void DataRcvDone::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void DataRcvDone::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void DataRcvDone::Clear() {
// @@protoc_insertion_point(message_clear_start:UDP.DataRcvDone)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* DataRcvDone::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string data = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_data();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "UDP.DataRcvDone.data"));
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

::PROTOBUF_NAMESPACE_ID::uint8* DataRcvDone::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:UDP.DataRcvDone)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string data = 1;
  if (!this->_internal_data().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data().data(), static_cast<int>(this->_internal_data().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "UDP.DataRcvDone.data");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_data(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:UDP.DataRcvDone)
  return target;
}

size_t DataRcvDone::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:UDP.DataRcvDone)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string data = 1;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData DataRcvDone::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    DataRcvDone::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*DataRcvDone::GetClassData() const { return &_class_data_; }

void DataRcvDone::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<DataRcvDone *>(to)->MergeFrom(
      static_cast<const DataRcvDone &>(from));
}


void DataRcvDone::MergeFrom(const DataRcvDone& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:UDP.DataRcvDone)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_data().empty()) {
    _internal_set_data(from._internal_data());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void DataRcvDone::CopyFrom(const DataRcvDone& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:UDP.DataRcvDone)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DataRcvDone::IsInitialized() const {
  return true;
}

void DataRcvDone::InternalSwap(DataRcvDone* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &data_, lhs_arena,
      &other->data_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata DataRcvDone::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_UDPFileSend_2eproto_getter, &descriptor_table_UDPFileSend_2eproto_once,
      file_level_metadata_UDPFileSend_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace UDP
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::UDP::FileData* Arena::CreateMaybeMessage< ::UDP::FileData >(Arena* arena) {
  return Arena::CreateMessageInternal< ::UDP::FileData >(arena);
}
template<> PROTOBUF_NOINLINE ::UDP::DataRcvAck* Arena::CreateMaybeMessage< ::UDP::DataRcvAck >(Arena* arena) {
  return Arena::CreateMessageInternal< ::UDP::DataRcvAck >(arena);
}
template<> PROTOBUF_NOINLINE ::UDP::DataRcvDone* Arena::CreateMaybeMessage< ::UDP::DataRcvDone >(Arena* arena) {
  return Arena::CreateMessageInternal< ::UDP::DataRcvDone >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
