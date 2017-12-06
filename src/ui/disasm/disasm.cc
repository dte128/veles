#include "ui/disasm/disasm.h"

#include <cstring>

namespace veles {
namespace ui {
namespace disasm {
namespace mocks {

Bookmark MockBookmark() { return QByteArray(); }

QString GenerateQString() { return "something random"; }

class ChunkGenerator {
 private:
  static uint64_t chunk_id = 0;

  static uint64_t pos_begin = 0;
  static uint64_t pos_end = 0;

  static uint64_t addr_begin = 0;
  static uint64_t addr_end = 0;

  const QByteArray chunkID(uint64_t id) {
    return QByteArray(std::to_string(id).c_str());
  }

  const QString displayName(uint64_t id) {
    auto sid = std::string("chunk") + std::to_string(id);
    return QString(sid.c_str());
  }

  const Bookmark nextPosBegin() {
    return QByteArray(std::to_string(pos_begin++).c_str());
  }
  const Bookmark nextPosEnd() {
    return QByteArray(std::to_string(pos_end++).c_str());
  }

  const Address nextAddrBegin() { return addr_begin++; }
  const Address nextAddrEnd() { return addr_end++; }

 public:
  ChunkGenerator() {}

  Chunk generate(const QByteArray parentID = QByteArray(), const QString& type = "",
                 const QString& text_repr = "", const QString& comment = "",
                 uint64_t flags = 0) {
    uint64_t id = chunk_id;
    chunk_id++;

    return (Chunk){
        .id = chunkID(id),
        .parent_id = parentID,

        .pos_begin = nextPosBegin(),
        .pos_end = nextPosEnd(),

        .addr_begin = nextAddrBegin(),
        .addr_end = nextAddrEnd(),

        .display_name = displayName(id),
        .type = type,
        .text_repr = text_repr,
        .comment = comment,
        .flags = flags,
    };
  }
};

class MockBlob : public Blob {

 private:
  ChunkGenerator chunk_generator_;

 public:
  MockBlob(){};
  ~MockBlob(){};

  std::unique_ptr<Window> createWindow(const Bookmark& pos, unsigned prev_n,
                                       unsigned next_n) override {
    return std::make_unique<Window>();
  };

  QFuture<Bookmark> getEntrypoint() override {
    QFuture<Bookmark> qf = QtConcurrent::run(MockBookmark);
    return qf;
  }

  QFuture<Bookmark> getPosition(ScrollbarIndex index) override {
    QFuture<Bookmark> qf = QtConcurrent::run(MockBookmark);
    return qf;
  };

  QFuture<Bookmark> getPositionByChunk(const ChunkID& chunk) override {
    QFuture<Bookmark> qf = QtConcurrent::run(MockBookmark);
    return qf;
  };
};

}  // namespace mocks
}  // namespace disasm
}  // namespace ui
}  // namespace veles