#include <memory>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QtGlobal>

#include "tmp_types.h"

#pragma once

namespace veles {
namespace ui {
namespace disasm {

using Bookmark = QByteArray;
using Address = uint64_t;
using ChunkID = QByteArray;

struct Chunk {
  ChunkID id;
  ChunkID parent_id;

  Bookmark pos_begin;
  Bookmark pos_end;

  Address addr_begin;
  Address addr_end;

  QString display_name;
  QString type;
  QString text_repr;
  QString comment;
  uint64_t flags;
};

struct Entry {
  Bookmark pos;
  virtual ~Entry() = 0;
};

struct EntryChunkBegin : Entry {
  Chunk chunk;
};

struct EntryChunkEnd : Entry {
  Chunk chunk;
};

struct EntryOverlap : Entry {
  Address begin;
  Address end;
};

struct EntryLooseData : Entry {
  Address begin;
  Address end;
  BinData data;
};

enum class FieldType {
  UNKNOWN,
  FIXED,
  FLOAT,
  STRING,
  REF,
  COMPOSED
  // TODO ENUM
};

struct FieldValue {};
struct FieldValueInt : FieldValue {};
struct FieldValueFloat : FieldValue {};
struct FieldValueString : FieldValue {};
struct FieldValueRef : FieldValue {};

struct EntryField : Entry {
  QString name;
  Address begin;
  Address end;
  size_t num_elements;
  FieldType type;
  BinData raw_bytes;

  Repacker repacker;
  std::unique_ptr<FieldValue> value;
};

struct EntryComputedField : Entry {
  std::unique_ptr<FieldValue> value;
};

struct EntryBitField : Entry {
  std::unique_ptr<FieldValue> value;
};

using ScrollbarIndex = uint64_t;

class Window {
 public:
  virtual void seek(const Bookmark& pos, unsigned prev_n, unsigned next_n) = 0;
  virtual Bookmark currentPosition() = 0;
  virtual ScrollbarIndex currentScrollbarIndex() = 0;
  virtual ScrollbarIndex maxScrollbarIndex() = 0;
  virtual const std::vector<Chunk>& breadcrumbs() = 0;
  virtual const std::vector<std::unique_ptr<Entry>>& entries() = 0;

  virtual ~Window() {};

 signals:
  virtual void updateScrollbar() = 0;
  virtual void dataChanged() = 0;
};

class Blob {
 public:
  virtual std::unique_ptr<Window> createWindow(const Bookmark& pos,
                                               unsigned prev_n,
                                               unsigned next_n) = 0;
  virtual QFuture<Bookmark> getEntrypoint() = 0;
  virtual QFuture<Bookmark> getPosition(ScrollbarIndex index) = 0;
  virtual QFuture<Bookmark> getPositionByChunk(const ChunkID& chunk) = 0;

  virtual ~Blob() {};
};

}  // namespace disasm
}  // namespace ui
}  // namespace veles
