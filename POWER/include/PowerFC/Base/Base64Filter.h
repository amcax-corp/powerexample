#pragma once
#include <iostream>
#include <memory>
#include <filesystem>
#include <PFCGlobal.h>

namespace base {

class PFC_BASE_API Base64Filter {

  public:
  enum class ErrorHandling { Throws, Silent };
  static constexpr auto DefaultBufferSize = 80;
public:
  /**
   * @brief Create an output stream that transforms the input binary data to
   * base64 strings source->base64->out
   * @param out the downstream output stream that will be fed with base64 string
   * @param line_size
   * @return std::unique_ptr<std::ostream> a unique pointer to an output stream
   * that can transforms the input binary data to base64 strings
   */
  static std::unique_ptr<std::ostream>
  MakeEncoder(std::ostream &out, std::size_t line_size = DefaultBufferSize);

  /**
   * @brief Create an output stream that stores the input binay data to file as
   * base64 strings source->base64->file[open(filepath)]
   * @param filepath the output file path
   * @param line_size
   * @return std::unique_ptr<std::ostream> a unique pointer to an output stream
   * that can transforms the input binary data to base64 strings
   */
  static std::unique_ptr<std::ostream>
  MakeEncoder(std::filesystem::path filepath, std::size_t line_size = DefaultBufferSize);

  /**
   * @brief Create an input stream that can transform base64 strings to binary
   * in->ibase64->destination
   * @param in input upstream
   * @param line_size
   * @param error_handling
   * @return std::unique_ptr<std::istream> A unique pointer to an input stream
   * that read from the given upstream and transform the read base64 strings
   * into binary data.
   */
  static std::unique_ptr<std::istream>
  MakeDecoder(std::istream &in, std::size_t line_size = DefaultBufferSize,
              ErrorHandling error_handling = ErrorHandling::Silent);

  /**
   * @brief Create an input stream that can transform base64 into binary
   * file[open(filepath)]->ibase64->destination
   * @param filepath input file
   * @param line_size
   * @param error_handling
   * @return std::unique_ptr<std::istream> A unique pointer to an input stream
   * that read from the given file and transform the read base64 strings into
   * binary data.
   */
  static std::unique_ptr<std::istream>
  MakeDecoder(std::filesystem::path filepath, std::size_t line_size = DefaultBufferSize,
              ErrorHandling error_handling = ErrorHandling::Silent);
};

} // namespace base
