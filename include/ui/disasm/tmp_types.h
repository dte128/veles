namespace veles {
namespace ui {
namespace disasm {

using BinData = QByteArray;

class Repacker {
  virtual void* Repack(const BinData& data) = 0;
};

}  // namespace disasm
}  // namespace ui
}  // namespace veles
