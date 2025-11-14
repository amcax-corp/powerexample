#pragma once
#include <Base/BaseClass.h>
#include <PFCConfig.h>
#include <cstdint>
#include <string>
#include <sstream>

namespace base {
class XMLWriter;
class XMLReader;
class Reader;

class PFC_BASE_API Persistence : public base::BaseClass
{
    PFC_TYPESYSTEM_DECL_WITH_OVERRIDE();

  public:
    ~Persistence() override = default;

    //!@brief 消耗内存的估计值
    virtual std::size_t GetEstimatedSize() const = 0;

    //!@brief 重载该方法，把属性数据保存到xml文档中
    virtual void Store(XMLWriter&, std::uint32_t version) const {}

    //!@brief 重载该方法，把属性数据从xml文档中恢复
    virtual void Restore(XMLReader&, std::uint32_t version) {}

    //encodes an attribute upon saving
    static std::string EncodeAttribute(std::string const&);

#ifdef PFC_OS_WINDOWS
    static std::string EncodeAttribute(std::size_t value);
#endif

    static std::string EncodeAttribute(int value);
    static std::string EncodeAttribute(double value);
    static std::string EncodeAttribute(bool value);
    static std::string EncodeAttribute(unsigned long value);
    static unsigned long DecodeAttributeUnsignedLong(std::string const& value);
    static int DecodeAttributeInt(std::string const& value);
    static std::size_t DecodeAttributeSizeT(std::string const& value);
    static double DecodeAttributeDouble(std::string const& value);
    static bool DecodeAttributeBool(std::string const& value);

    //dump the binary persistence data into the stream
    void DumpToStream(std::ostream&, int compression);

    //restore the binary persistence data from a stream, must have the format used by DumpToStream
    void RestoreFromStream(std::istream&);

  protected:
    /** This method is used at the end of restoreFromStream()
     * after all data files have been read in.
     * A subclass can set up some internals. The default
     * implementation does nothing.
     */
    virtual void RestoreFinished() {}
};
}  // namespace base