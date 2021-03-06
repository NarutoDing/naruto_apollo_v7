// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: modules/audio/proto/audio.proto

#include "modules/audio/proto/audio.pb.h"

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
extern PROTOBUF_INTERNAL_EXPORT_modules_2fcommon_2fproto_2fheader_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Header_modules_2fcommon_2fproto_2fheader_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_modules_2fcommon_2fproto_2fgeometry_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Point3D_modules_2fcommon_2fproto_2fgeometry_2eproto;
namespace apollo {
namespace audio {
class AudioDetectionDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<AudioDetection> _instance;
} _AudioDetection_default_instance_;
}  // namespace audio
}  // namespace apollo
static void InitDefaultsscc_info_AudioDetection_modules_2faudio_2fproto_2faudio_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::apollo::audio::_AudioDetection_default_instance_;
    new (ptr) ::apollo::audio::AudioDetection();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<2> scc_info_AudioDetection_modules_2faudio_2fproto_2faudio_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 2, 0, InitDefaultsscc_info_AudioDetection_modules_2faudio_2fproto_2faudio_2eproto}, {
      &scc_info_Header_modules_2fcommon_2fproto_2fheader_2eproto.base,
      &scc_info_Point3D_modules_2fcommon_2fproto_2fgeometry_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_modules_2faudio_2fproto_2faudio_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_modules_2faudio_2fproto_2faudio_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_modules_2faudio_2fproto_2faudio_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_modules_2faudio_2fproto_2faudio_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::apollo::audio::AudioDetection, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::apollo::audio::AudioDetection, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::apollo::audio::AudioDetection, header_),
  PROTOBUF_FIELD_OFFSET(::apollo::audio::AudioDetection, is_siren_),
  PROTOBUF_FIELD_OFFSET(::apollo::audio::AudioDetection, moving_result_),
  PROTOBUF_FIELD_OFFSET(::apollo::audio::AudioDetection, position_),
  PROTOBUF_FIELD_OFFSET(::apollo::audio::AudioDetection, source_degree_),
  0,
  2,
  3,
  1,
  4,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 10, sizeof(::apollo::audio::AudioDetection)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::apollo::audio::_AudioDetection_default_instance_),
};

const char descriptor_table_protodef_modules_2faudio_2fproto_2faudio_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\037modules/audio/proto/audio.proto\022\014apoll"
  "o.audio\032&modules/audio/proto/audio_commo"
  "n.proto\032#modules/common/proto/geometry.p"
  "roto\032!modules/common/proto/header.proto\""
  "\306\001\n\016AudioDetection\022%\n\006header\030\001 \001(\0132\025.apo"
  "llo.common.Header\022\020\n\010is_siren\030\002 \001(\010\022:\n\rm"
  "oving_result\030\003 \001(\0162\032.apollo.audio.Moving"
  "Result:\007UNKNOWN\022(\n\010position\030\004 \001(\0132\026.apol"
  "lo.common.Point3D\022\025\n\rsource_degree\030\005 \001(\001"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_modules_2faudio_2fproto_2faudio_2eproto_deps[3] = {
  &::descriptor_table_modules_2faudio_2fproto_2faudio_5fcommon_2eproto,
  &::descriptor_table_modules_2fcommon_2fproto_2fgeometry_2eproto,
  &::descriptor_table_modules_2fcommon_2fproto_2fheader_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_modules_2faudio_2fproto_2faudio_2eproto_sccs[1] = {
  &scc_info_AudioDetection_modules_2faudio_2fproto_2faudio_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_modules_2faudio_2fproto_2faudio_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_modules_2faudio_2fproto_2faudio_2eproto = {
  false, false, descriptor_table_protodef_modules_2faudio_2fproto_2faudio_2eproto, "modules/audio/proto/audio.proto", 360,
  &descriptor_table_modules_2faudio_2fproto_2faudio_2eproto_once, descriptor_table_modules_2faudio_2fproto_2faudio_2eproto_sccs, descriptor_table_modules_2faudio_2fproto_2faudio_2eproto_deps, 1, 3,
  schemas, file_default_instances, TableStruct_modules_2faudio_2fproto_2faudio_2eproto::offsets,
  file_level_metadata_modules_2faudio_2fproto_2faudio_2eproto, 1, file_level_enum_descriptors_modules_2faudio_2fproto_2faudio_2eproto, file_level_service_descriptors_modules_2faudio_2fproto_2faudio_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_modules_2faudio_2fproto_2faudio_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_modules_2faudio_2fproto_2faudio_2eproto)), true);
namespace apollo {
namespace audio {

// ===================================================================

class AudioDetection::_Internal {
 public:
  using HasBits = decltype(std::declval<AudioDetection>()._has_bits_);
  static const ::apollo::common::Header& header(const AudioDetection* msg);
  static void set_has_header(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_is_siren(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_moving_result(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static const ::apollo::common::Point3D& position(const AudioDetection* msg);
  static void set_has_position(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_source_degree(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
};

const ::apollo::common::Header&
AudioDetection::_Internal::header(const AudioDetection* msg) {
  return *msg->header_;
}
const ::apollo::common::Point3D&
AudioDetection::_Internal::position(const AudioDetection* msg) {
  return *msg->position_;
}
void AudioDetection::clear_header() {
  if (header_ != nullptr) header_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
void AudioDetection::clear_position() {
  if (position_ != nullptr) position_->Clear();
  _has_bits_[0] &= ~0x00000002u;
}
AudioDetection::AudioDetection(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:apollo.audio.AudioDetection)
}
AudioDetection::AudioDetection(const AudioDetection& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_header()) {
    header_ = new ::apollo::common::Header(*from.header_);
  } else {
    header_ = nullptr;
  }
  if (from._internal_has_position()) {
    position_ = new ::apollo::common::Point3D(*from.position_);
  } else {
    position_ = nullptr;
  }
  ::memcpy(&is_siren_, &from.is_siren_,
    static_cast<size_t>(reinterpret_cast<char*>(&source_degree_) -
    reinterpret_cast<char*>(&is_siren_)) + sizeof(source_degree_));
  // @@protoc_insertion_point(copy_constructor:apollo.audio.AudioDetection)
}

void AudioDetection::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_AudioDetection_modules_2faudio_2fproto_2faudio_2eproto.base);
  ::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
      reinterpret_cast<char*>(&header_) - reinterpret_cast<char*>(this)),
      0, static_cast<size_t>(reinterpret_cast<char*>(&source_degree_) -
      reinterpret_cast<char*>(&header_)) + sizeof(source_degree_));
}

AudioDetection::~AudioDetection() {
  // @@protoc_insertion_point(destructor:apollo.audio.AudioDetection)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void AudioDetection::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  if (this != internal_default_instance()) delete header_;
  if (this != internal_default_instance()) delete position_;
}

void AudioDetection::ArenaDtor(void* object) {
  AudioDetection* _this = reinterpret_cast< AudioDetection* >(object);
  (void)_this;
}
void AudioDetection::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void AudioDetection::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const AudioDetection& AudioDetection::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_AudioDetection_modules_2faudio_2fproto_2faudio_2eproto.base);
  return *internal_default_instance();
}


void AudioDetection::Clear() {
// @@protoc_insertion_point(message_clear_start:apollo.audio.AudioDetection)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      GOOGLE_DCHECK(header_ != nullptr);
      header_->Clear();
    }
    if (cached_has_bits & 0x00000002u) {
      GOOGLE_DCHECK(position_ != nullptr);
      position_->Clear();
    }
  }
  if (cached_has_bits & 0x0000001cu) {
    ::memset(&is_siren_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&source_degree_) -
        reinterpret_cast<char*>(&is_siren_)) + sizeof(source_degree_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* AudioDetection::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional .apollo.common.Header header = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_header(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool is_siren = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_is_siren(&has_bits);
          is_siren_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional .apollo.audio.MovingResult moving_result = 3 [default = UNKNOWN];
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::apollo::audio::MovingResult_IsValid(val))) {
            _internal_set_moving_result(static_cast<::apollo::audio::MovingResult>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(3, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // optional .apollo.common.Point3D position = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr = ctx->ParseMessage(_internal_mutable_position(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional double source_degree = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 41)) {
          _Internal::set_has_source_degree(&has_bits);
          source_degree_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
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

::PROTOBUF_NAMESPACE_ID::uint8* AudioDetection::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:apollo.audio.AudioDetection)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional .apollo.common.Header header = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::header(this), target, stream);
  }

  // optional bool is_siren = 2;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(2, this->_internal_is_siren(), target);
  }

  // optional .apollo.audio.MovingResult moving_result = 3 [default = UNKNOWN];
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      3, this->_internal_moving_result(), target);
  }

  // optional .apollo.common.Point3D position = 4;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        4, _Internal::position(this), target, stream);
  }

  // optional double source_degree = 5;
  if (cached_has_bits & 0x00000010u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(5, this->_internal_source_degree(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:apollo.audio.AudioDetection)
  return target;
}

size_t AudioDetection::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:apollo.audio.AudioDetection)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    // optional .apollo.common.Header header = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *header_);
    }

    // optional .apollo.common.Point3D position = 4;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *position_);
    }

    // optional bool is_siren = 2;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 + 1;
    }

    // optional .apollo.audio.MovingResult moving_result = 3 [default = UNKNOWN];
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_moving_result());
    }

    // optional double source_degree = 5;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 + 8;
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AudioDetection::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:apollo.audio.AudioDetection)
  GOOGLE_DCHECK_NE(&from, this);
  const AudioDetection* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AudioDetection>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:apollo.audio.AudioDetection)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:apollo.audio.AudioDetection)
    MergeFrom(*source);
  }
}

void AudioDetection::MergeFrom(const AudioDetection& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:apollo.audio.AudioDetection)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_header()->::apollo::common::Header::MergeFrom(from._internal_header());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_mutable_position()->::apollo::common::Point3D::MergeFrom(from._internal_position());
    }
    if (cached_has_bits & 0x00000004u) {
      is_siren_ = from.is_siren_;
    }
    if (cached_has_bits & 0x00000008u) {
      moving_result_ = from.moving_result_;
    }
    if (cached_has_bits & 0x00000010u) {
      source_degree_ = from.source_degree_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void AudioDetection::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:apollo.audio.AudioDetection)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AudioDetection::CopyFrom(const AudioDetection& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:apollo.audio.AudioDetection)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AudioDetection::IsInitialized() const {
  return true;
}

void AudioDetection::InternalSwap(AudioDetection* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(AudioDetection, source_degree_)
      + sizeof(AudioDetection::source_degree_)
      - PROTOBUF_FIELD_OFFSET(AudioDetection, header_)>(
          reinterpret_cast<char*>(&header_),
          reinterpret_cast<char*>(&other->header_));
}

::PROTOBUF_NAMESPACE_ID::Metadata AudioDetection::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace audio
}  // namespace apollo
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::apollo::audio::AudioDetection* Arena::CreateMaybeMessage< ::apollo::audio::AudioDetection >(Arena* arena) {
  return Arena::CreateMessageInternal< ::apollo::audio::AudioDetection >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
