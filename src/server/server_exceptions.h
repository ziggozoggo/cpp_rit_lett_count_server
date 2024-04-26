#ifndef SRC_SERVER_EXCEPTIONS_H_
#define SRC_SERVER_EXCEPTIONS_H_

#include <exception>
#include <string>

class ServerBindSocketError: public std::exception {
  public:
    ServerBindSocketError(const std::string &message) : message_(message) {};
    const char * what() const noexcept override {
      return message_.c_str();
    }

  private:
    std::string  message_;
};

class ServerBindPortIPError: public std::exception {
  public:
    ServerBindPortIPError(const std::string &message) : message_(message) {};
    const char * what() const noexcept override {
      return message_.c_str();
    }

  private:
    std::string  message_;
};

class ServerListenError: public std::exception {
  public:
    ServerListenError(const std::string &message) : message_(message) {};
    const char * what() const noexcept override {
      return message_.c_str();
    }

  private:
    std::string  message_;
};

#endif // SRC_SERVER_EXCEPTIONS_H_